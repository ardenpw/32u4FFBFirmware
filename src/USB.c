#include "include.h"

static const uint8_t udDeviceDescriptor[] PROGMEM = {
   18, // bLength
    1, // bDescriptorType
    0x00,
    0x02, // bcdUSB (2.0)
    0, // bDeviceClass (defined in interface [in cfg. descriptor])
    0, // bDeviceSubclass (above is 0)
    0, 
    UD_EP0_SIZE, // 64
    (0x1209 & 255),
    ((0x1209 >> 8) & 255), // idVendor, https://pid.codes
    (0x0001 & 255),
    ((0x0001 >> 8) & 255), // idProduct https://pid.codes
    0x00,
    0x01, // bcdDevice release number
    0,
    0, // TODO: this. 1, // (iProduct at index 1)
    0,
    1
};

static const uint8_t udHIDReportDescriptor[] PROGMEM = {
    0x05, 0x01, // Usage Page:  Generic Desktop Page
    0x09, 0x04, // Usage: Joystick 
    0xA1, 0x01, // Collection: Application
    0x09, 0x30, //      Usage: X
    0x09, 0x31, //      Usage: Y
    0x15, 0x81, //      Logical Min: -127
    0x25, 0x7F, //      Logical Max: 127
    0x75, 0x08, //      Retport Size: 8 (bits)
    0x95, 0x02, //      Report Count: 2
    0x81, 0x02, //      Input Report (Data, Variable, Absolute)
    0xC0        // End Collection
};

static const uint8_t udConfigurationDescriptor[] PROGMEM = {
    //configuration descriptor
    9, //bLength
    0x02, //const CONFIGURATION
    34, 0x00, //bytes configuration descriptor TOTAL (everything)
    1, // num interfaces
    1, // bConfigurationValue
    0, // iConfiguration
    0b10000000, // bmAttributes
    50, // bMaxPower

    // interface descriptor
    9, // bLength
    0x04, // const INTERFACE
    0x00, // 0th interface
    0x00, // no alternates
    1, // additional endpoints
    0x03, // HID device (yay! [bInterfaceClass]) 
    0x00, // bInterfaceSubClass
    0x00, // bInterfaceProtocol (defined in HID)
    0x00, // iInterface

    // HID descriptor
    9, // bLength
    0x21, // class descriptor type
    0x11, 0x01, // bcdHID release number
    0x00, // country code
    0x01, // num. descriptors
    0x22, // bDescriptorType
    sizeof(udHIDReportDescriptor), 0,

    // endpoint descriptor (IN)
    7,
    0x05, // bDescriptorType
    0b10000001, // bEndpointAddress (ep 1, in)
    0b00000011, // bmAttributes
    64, 0, // wMaxPacketSize (in B) (size of bank [ep1 will be 64B])
    1 // once every ms
};

static const uint8_t udStringLanguageDescriptor[] PROGMEM = {
    4, // bLength
    0x03, // bDescriptorType (string)
    0x09, 0x04, // wLANGID (0x0409 = English US)
};

static const uint8_t udStringDeviceDescriptor[] PROGMEM = {
    42, // bLength
    0x03, // bDescriptorType (string)
    0x54, 0x00, 
    0x73, 0x00, 
    0x20, 0x00, 
    0x69, 0x00, 
    0x73, 0x00, 
    0x20, 0x00, 
    0x66, 0x00, 
    0x75, 0x00, 
    0x63, 0x00, 
    0x6B, 0x00, 
    0x65, 0x00, 
    0x64, 0x00, 
    0x20, 0x00, 
    0x66, 0x00, 
    0x72, 0x00, 
    0x20, 0x00, 
    0x4C, 0x00, 
    0x4D, 0x00, 
    0x41, 0x00, 
    0x4F, 0x00
    // TODO: why doesn't this work
};

void _blink(uint8_t delayMS) {
    while (1) {
        PORTB ^= (1 << PB0);
        _delay_ms(delayMS);
    }
}

void usbInit(void) {
    cli();

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

int8_t count = 0;

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
    if (flags & (1 << SOFI)) {
        if (udCfgStatus) {
            UENUM = 1;
            if (UEINTX & (1 << RWAL)) {
                UECONX |= (1 << STALLRQ);
                /*
                UEDATX = count;
                UEDATX = count++;
                */
            // ?????????????
            }
        }
    }
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

        for (uint8_t i = 0; i < 5; i++) {
            SH1107_clearPage(i, 0, 127); 
            /*
            TODO: TEMPORARY FIX. FLASHING BAD. 
            The values on the screen dont clear propperly,leading to what seem 
            like random values that dont make sense. Looping through each line 
            and clearing it so the formatter can print the new correct number 
            fixes this.
            */
        }
        SH1107_drawString(0, 0, 1, "bmRequestType: %u", bmRequestType);
        SH1107_drawString(0, 1, 1, "bRequest: %u", bRequest);
        SH1107_drawString(0, 2, 1, "wValue: %u (bD)", wValue);
        SH1107_drawString(0, 3, 1, "wIndex: %u", wIndex);
        SH1107_drawString(0, 4, 1, "wLength: %u", wLength);


        // send device descriptor
        if (bRequest == GET_DESCRIPTOR) { // bmRequestType == 128 && ...
            // host sent GET_DESCRIPTOR, requesting only (wLength/8) bytes of the descriptor, 
            // of type (wValue >> 8)
            uint8_t descLen; // = sizeof(udDeviceDescriptor);
            const uint8_t *descriptor;
            uint16_t requestLen = wLength > 512 ? 512 : wLength;
            uint8_t bytesSent = 0;
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
                case 0x0301: // getDescriptor(string, index 1) it wants the product String
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
                    SH1107_drawString(0, 15, 1, "STALL, unk wVal %u", wValue);
                    break;
            }
            while(!(UEINTX & (1 << TXINI)));
            /*
            if (UEINTX & (1 << RXOUTI)) {
                UEINTX &= ~(1 << RXOUTI); //TODO: check if having this if block even does anything
                return;
                }
                */
            descLen = requestLen > descLen ? descLen : requestLen;
            while (descLen > 0) {
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
            /*
            Host sent a configuration request for endpoint wValue,
            specified by the low byte in wValue.
            */
            UEINTX &= ~(1 << TXINI); //handshake
            UENUM = wValue;
            UECONX = (1 << EPEN);
            UECFG0X = 0b11000001; // in, interrupt
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
            return;
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
    }
    UECONX |= (1 << STALLRQ);
    cli();
    SH1107_drawString(0, 15, 1, "unkown", 0);
}