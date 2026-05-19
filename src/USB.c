#include "include.h"

static const uint8_t udDeviceDescriptor[] PROGMEM = {
   18, // bLength
    1, // bDescriptorType
    0x00,
    0x02, // bcdUSB (2.0)
    0, // bDeviceClass (defined in interface)
    0, // bDeviceSubclass (above is 0)
    0, 
    UD_EP0_SIZE, // 64
    (1234 & 255),
    ((1234 >> 8) & 255), // idVendor, 
    (5678 & 255),
    ((5678 >> 8) & 255), // idProduct
    0x00,
    0x01, // bcdDevice release number
    0,
    0,
    0,
    1
};

static const uint8_t udConfigurationDescriptor[] PROGMEM = {
    9, //bLength
    0x02, //const CONFIGURATION
    0x09,
    0x00, //bytes configuration descriptor
    1, // num interfaces
    1, // bConfigurationValue
    0, // iConfiguration
    0b10000000, // bmAttributes
    50 // bMaxPower
};

 
void _blink(void) {
    while (1) {
        PORTB ^= (1 << PB0);
        _delay_ms(250);
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

ISR(USB_GEN_vect) {
    if (UDINT & (1 << EORSTI)) {
        UDINT &= ~(1 << EORSTI);
        UENUM = 0;
        UECONX = (1 << EPEN);
        UECFG0X = 0;
        UECFG1X = 0b00110010;
        if (!(UESTA0X & (1 << CFGOK))) {
            return;
        }
        
        UERST = 1;
        UERST = 0;
        
        UEIENX = (1 << RXSTPE);
    }
    if (UDINT & (1 << SOFI)) {
        UDINT &= ~(1 << SOFI);
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

        SH1107_drawString(0, 0, 1, "bmRequestType: %u", bmRequestType);
        SH1107_drawString(0, 1, 1, "bRequest: %u", bRequest);
        SH1107_drawString(0, 2, 1, "wValue: %u (bDesc)", wValue);
        SH1107_drawString(0, 3, 1, "wIndex: %u", wIndex);
        SH1107_drawString(0, 4, 1, "wLength: %u", wLength);
        SH1107_clearPage(15, 0, 127);


        // send device descriptor
        if (bRequest == GET_DESCRIPTOR) { // bmRequestType == 128 && ...
            // host sent GET_DESCRIPTOR, requesting only (wLength/8) bytes of the descriptor, 
            // of type (wValue >> 8)
            uint8_t descLen; // = sizeof(udDeviceDescriptor);
            const uint8_t *descriptor;
            uint16_t requestLen = wLength > 512 ? 512 : wLength;
            uint8_t bytesSent = 0;
            switch (wValue) {
                case 0x0100:
                    descriptor = udDeviceDescriptor;
                    descLen = sizeof(udDeviceDescriptor);
                    break;
                case 0x0200:
                    descriptor = udConfigurationDescriptor;
                    descLen = sizeof(udConfigurationDescriptor);
                    break;
                default:
                    UECONX |= (1 << STALLRQ) | (1 << EPEN); // TODO: delete the (1 << EPEN) later, it shouldn't do anything.
                    //SH1107_clearScreen();
                    SH1107_drawString(0, 15, 1, "e: STALL, unk bDesc", 0);
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
        }

        if (bRequest == SET_ADDRESS) {
            UEINTX &= ~(1 << TXINI); //handshake
            while(!(UEINTX & (1 << TXINI)));
            UDADDR = wValue | (1 << ADDEN);
            SH1107_drawString(0, 5, 1, "deviceID: %u", wValue);
        }
    }

}