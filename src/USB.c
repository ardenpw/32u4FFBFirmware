#include "include.h"

void _blink(uint8_t delayMS) {
    while (1) {
        PORTB ^= (1 << PB0);
        _delay_ms(delayMS);
    }
}

void usbInit(void) {
    cli();

    UERST = 127;
    UDCON |= (1 << DETACH);

    DDRB |= (1 << PB0);

    UHWCON |= (1 << UVREGE);
    
    PLLFRQ = 0b01001010;
    PLLCSR = 0b00010010;
    while(!(PLLCSR & (1 << PLOCK))) {;}
    
    USBCON = 0b10110000;
    UDCON = 0b00000001;
    USBCON &= ~(1 << FRZCLK);
    
    UDIEN = 0b00001100;
    
    UDCON &= ~(1 << DETACH);

    
    sei(); 
    return;
}

int16_t count = 0;
uint8_t reportRDY = 0;
uint8_t unknownPacket = 0;
uint8_t sofTick = 0;
static uint8_t buf[64];
uint8_t inputFlags = 1;
/*
7:
6:
5:
4:
3:
2:
1: PID Device Control Report
0: Input Report
*/

typedef struct {
    uint8_t reportID;
    int16_t x;
    int16_t y;
} HIDInputReport;

typedef struct {
    uint8_t reportID;
    uint8_t effectBlockIndex;
    uint8_t state;
} HIDPIDStateReport;

HIDInputReport pendHIDInRept;
HIDPIDStateReport pendHIDStateInRept;

void prepUSBReport(void) {
    if (!udCfgStatus) { return; }
    
    static uint32_t curr = 0; 
    static uint32_t last = 0;
    static int32_t delta = 0;
    static int32_t total = 0; 
    static int16_t output;
    static const uint32_t encoderMax = 2097151;
    static const uint32_t encoderMid = (encoderMax >> 1);
    
    cli(); // dissable interrupts so we get a non-malformed data struct

    if (inputFlags & (1 << 1)) {
        pendHIDStateInRept.reportID = 2;
        pendHIDStateInRept.effectBlockIndex = 1;
        pendHIDStateInRept.effectBlockIndex &= ~(1 << 7); // set bit 7 to 0 for RAM. 
                                                          //setting to 1 already does this but whatever
        pendHIDStateInRept.state &= ~(1 << 0);
        pendHIDStateInRept.state &= ~(1 << 0);
        pendHIDStateInRept.state &= ~(1 << 0);
        pendHIDStateInRept.state &= ~(1 << 0);
        pendHIDStateInRept.state &= ~(1 << 0);
        pendHIDStateInRept.state &= ~(1 << 0);
        reportRDY = 1;
    } 
    else {
        curr = (MT6835_burstRead() >> 11);
        delta = (int32_t)(curr - last);
        
        if (delta > (int32_t)encoderMid) {
            total += (encoderMax + 1);
        }
        else if (delta < (int32_t)-encoderMid) {
        total -= (encoderMax + 1);
        }
        
        total -= delta;
        last = curr;
        /*
        2520 degrees over 16b equates to 9362pts/rev. 3.5 revolutions in each direction
        */
        output = (int16_t)(MIN(32767, MAX(-32768, ((int64_t)total * 9362) / encoderMax)));
        //output = (int16_t)(((int64_t)total * 9362) / encoderMax);
        
        pendHIDInRept.reportID = 1;
        pendHIDInRept.x = output;
        pendHIDInRept.y = 0;
        reportRDY = 1;
    }
    
    sei();
}

void ep1RDY(void) {
    // TODO: implement delay from SET_IDLE
    UENUM = 1;
    if (UENUM != 1) { return; }
    if (!reportRDY) { return; }
    if (!(UEINTX & (1 << RWAL))) { return; }
    UEINTX &= ~(1 << TXINI);
    if (inputFlags & (1 << 1)) {
        UEDATX = pendHIDStateInRept.reportID;
        UEDATX = pendHIDStateInRept.effectBlockIndex;
        UEDATX = pendHIDStateInRept.state;
        inputFlags &= ~(1 << 1);
    }
    else {
        UEDATX = pendHIDInRept.reportID;
        UEDATX = (pendHIDInRept.x & 0xFF);
        UEDATX = (pendHIDInRept.x >> 8);
        UEDATX = (pendHIDInRept.y & 0xFF);
        UEDATX = (pendHIDInRept.y >> 8);
    }
    while (!(UEINTX & (1 << RWAL)));
    UEINTX &= ~(1 << FIFOCON); // push fifo
    reportRDY = 0;
}

void ep2Dump(void) {
    UENUM = 2;
    if (!(UEINTX & (1 << RXOUTI))) { return; }  // no packet waiting
    
    uint8_t byteCount = UEBCLX;
    
    for (uint8_t i = 0; i < byteCount; i++) {
        buf[i] = UEDATX;
    }
    
    if (buf[0] == 0x06) {
        inputFlags |= (1 << 1);
    }
    
    
    SH1107_drawString(0,10,1,"%u",++count);

    UEINTX &= ~(1 << RXOUTI);   // acknowledge receipt
    UEINTX &= ~(1 << FIFOCON);  // release bank back to SIE
}   

ISR(INT3_vect){
    usbInit();
}

ISR(USB_GEN_vect) {
    uint8_t flags = UDINT;
    UDINT = 0;
    if (flags & (1 << EORSTI)) {
        UENUM = 0;
        UECONX = (1 << EPEN);
        UECFG0X = 0;
        UECFG1X = 0b00110010;
        if (!(UESTA0X & (1 << CFGOK))) {
            cli();
            _blink(100);
            return;
        }
        
        UERST = 1;
        UERST = 0;

        udCfgStatus = 0;
        
        UEIENX = (1 << RXSTPE);
    }
    /*
    if (flags & (1 << SOFI)) {
        if (udCfgStatus) {
            UENUM = 1;
            // add a sof tick, only when this is set in main loop, do we send
        }
    }
    */
}

ISR(USB_COM_vect) {
    /*
    When writing or reading a FIFO, since they are not memory mapped, so you do everything
    through UEDATX (there is no descrirbed procedure for moving data). Basically, when you 
    setup your endpoint, the ALLOC command allocates stuff required for your ep config., 
    including your bank. When the USB controller receives a new packet, it fires the required 
    interrupt, in which we begin to read (or write) to UEDATX. Any subsiquent read or write 
    to UEDATX, increments an internal pointer to point UEDATX at the next byte in our DPRAM 
    bank for processing. 
    */
    UENUM = 0;    
    if (UEINTX & (1 << RXSTPI)) {
        //UEINTX &= ~(1 << RXSTPI);
        // Setup packet 
        volatile uint8_t bmRequestType = UEDATX;
        volatile uint8_t bRequest = UEDATX; // All USB defined traffic is encoded in little endian order.
        volatile uint16_t wValue = UEDATX;  // Since little endian, LSB is the first byte, 
        wValue |= UEDATX << 8;     // then we move MSB to the left by 8b to get our 2B per 'w.'
        volatile uint16_t wIndex = UEDATX;
        wIndex |= UEDATX << 8;
        volatile uint16_t wLength = UEDATX;
        wLength |= UEDATX << 8;

        UEINTX &= ~((1 << RXSTPI) | (1 << RXOUTI) | (1 << TXINI)); // Clear UEINTX flags to handshake

        PORTB ^= (1 << PB0);

        // temporary logging
        if (!unknownPacket) {
            SH1107_drawString(0, 0, 1, "bmRequestType: %u   ", bmRequestType);
            SH1107_drawString(0, 1, 1, "bRequest: %u   ", bRequest);
            SH1107_drawString(0, 2, 1, "wValue: %u (bD)  ", wValue);
            SH1107_drawString(0, 3, 1, "wIndex: %u   ", wIndex);
            SH1107_drawString(0, 4, 1, "wLength: %u   ", wLength);
        }


        // send device descriptor
        if (bRequest == GET_DESCRIPTOR) { // bmRequestType == 128 && ...
            // host sent GET_DESCRIPTOR, requesting only (wLength/8) bytes of the descriptor, 
            // of type (wValue >> 8)
            uint16_t descLen; // = sizeof(udDeviceDescriptor);
            const uint8_t *descriptor;
            uint16_t requestLen = wLength; // > 512 ? 512 : wLength;
            uint16_t bytesSent = 0;
            switch (wValue) {
                case 0x0100: // getDescriptor(device)
                    descriptor = udDeviceDescriptor;
                    descLen = sizeof(udDeviceDescriptor);
                    break;
                case 0x0200: // getDescriptor(configuration)
                    descriptor = udConfigurationDescriptor;
                    descLen = sizeof(udConfigurationDescriptor);
                    break;
                case 0x0300: // getDescriptor(string, index 0) it wants the language (US)
                    descriptor = udStringLanguageDescriptor;
                    descLen = sizeof(udStringLanguageDescriptor);
                    break;
                case 0x0301: // getDescriptor(string, index 1) it wants the manufacturer String
                    descriptor = udStringManufacturerDescriptor;
                    descLen = sizeof(udStringManufacturerDescriptor);
                    break;
                case 0x0302: // getDescriptor(string, index 2) it wants the product String
                    descriptor = udStringDeviceDescriptor;
                    descLen = sizeof(udStringDeviceDescriptor);
                    break;
                case 0x0600: // getDescriptor(deviceQualifier)
                    UECONX |= (1 << STALLRQ);
                    break;
                case 0x2200: // getDescriptor(HIDReport)
                    descriptor = udHIDReportDescriptor;
                    descLen = sizeof(udHIDReportDescriptor);
                    break;
                default: // Unknown bDescriptorType
                    UECONX |= (1 << STALLRQ);
                    cli();
                    unknownPacket = 1;
                    SH1107_drawString(0, 15, 1, "STALL, unk wVal %u", wValue);
                    break;
            }
            descLen = requestLen > descLen ? descLen : requestLen;
            while (descLen > 0) {
                while(!(UEINTX & (1 << TXINI))); // wow
                uint8_t packetLen = descLen > UD_EP0_SIZE ? UD_EP0_SIZE : descLen;
                for (uint8_t i = 0; i < packetLen; i++) {
                    UEDATX = pgm_read_byte(descriptor + bytesSent++);
                }
                descLen -= packetLen;
                UEINTX &= ~(1 << TXINI);
            }
            return;
        }

        if (bRequest == SET_ADDRESS) {
            UEINTX &= ~(1 << TXINI); //handshake
            while(!(UEINTX & (1 << TXINI)));
            UDADDR = wValue | (1 << ADDEN);
            SH1107_drawString(0, 5, 1, "deviceID: %u", wValue);
            return;
        }

        if (bRequest == SET_CONFIGURATION) {
            if (bmRequestType == 0 && !udCfgStatus) {
                /*
                Host sent a configuration request for endpoint wValue,
                specified by the low byte in wValue.
                bmRequestType: 0
                bRequest: 9
                wValue: 1
                wIndex: 0
                wLength: 0
                */
                UEINTX &= ~(1 << TXINI); //handshake
               
                // ep1
                UENUM = 1; // = wValue
                UECONX = (1 << EPEN);
                UECFG0X = 0b11000001; // interrupt, in
                UECFG1X = 0b00110010; // One Bank: 64B, Allocate
                if (!(UESTA0X & (1 << CFGOK))) {
                    cli();
                    _blink(100);
                    return;
                }
                
                // ep2
                UENUM = 2;
                UECONX = (1 << EPEN);
                UECFG0X = 0b11000000; // interrupt, out
                UECFG1X = 0b00110010; // One Bank: 64B, Allocate
                if (!(UESTA0X & (1 << CFGOK))) {
                    cli();
                    _blink(100);
                    return;
                }
                
                UERST = 0x7E; // 0b01111110
                UERST = 0;
                
                udCfgStatus = 1;
                SH1107_drawString(0, 6, 1, "udConfigured", 0);
                //unknownPacket = 1;
                return;
            }
            /*
            if (bmRequestType == 33 && wValue == 0x204 && udCfgStatus) {
                PID Device Control Request (actuators)

                bmRequestType: 33
                bRequest: 9
                wValue: 516 or 0x0204
                wIndex: 0
                wLength: 2
                if (UEINTX & (1 << RXOUTI)) {
                    SH1107_drawString(0,8,1,"pooper",0);
                }
                UEINTX &= ~(1 << RXOUTI);
                UEINTX &= ~(1 << TXINI);
                
                uint8_t reportID = UEDATX;
                uint8_t dcControl = UEDATX;
                
                UEINTX &= ~(1 << FIFOCON);
                
                switch (dcControl) {
                    case 0x01: // DC Enable Actuators
                    break;
                    case 0x02: // DC Disable Actuators
                    break;
                    case 0x03: // DC Stop All Effects
                    break;
                    case 0x04: // DC Reset
                    // Clear effect state, zero RAM pool, re-enable actuators
                    break;
                    case 0x05: // DC Pause
                    break;
                    case 0x06: // DC Continue
                    break;
                }
                
                return;
            }
            */
        }
        
        if (bRequest == SET_IDLE) {
            /* TODO: this
            If there is no data change within the idle period,
            resend the previous packet. If 0, only send data
            when there is a change (no resends).
            */
            UEINTX &= ~(1 << TXINI);
            return;
        }

        if (bRequest == GET_REPORT) {
            if (wValue == 0x030A) {
                // Type: Feature, Report ID: (12)
                // This is the PID Pool Report
                while(!(UEINTX & (1 << TXINI)));
                for (uint8_t i = 0; i < wLength; i++) {
                    UEDATX = pgm_read_byte(udPIDPoolReport + i);
                }
                UEINTX &= ~(1 << TXINI);
                return;
            }
        }   
    }

    UECONX |= (1 << STALLRQ);
    unknownPacket = 1;
    SH1107_drawString(0, 15, 1, "unkown", 0);
}