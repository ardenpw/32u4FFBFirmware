#ifndef global_h
#define global_h

#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define MIN(a,b) ((a) < (b) ? (a) : (b))

volatile uint8_t udCfgStatus;
uint8_t idleLimit; 

#define STAY 1
#define FLIP 0

// usb stuff
#define GET_STATUS 0x00
#define CLEAR_FEATURE 0x01
#define SET_FEATURE 0x03
#define SET_ADDRESS 0x05
#define GET_DESCRIPTOR 0x06
#define GET_CONFIGURATION 0x08
#define SET_CONFIGURATION 0x09
#define GET_INTERFACE 0x0A
#define SET_INTERFACE 0x0B2

// HID stuff
#define GET_REPORT 0x01
#define GET_IDLE 0x02
#define GET_PROTOCOL 0x03
#define SET_REPORT 0x09
#define SET_IDLE 0x0A
#define SET_PROTOCOL 0x0B

#define UD_EP0_SIZE 0x40 // 64

// SPI stuff
#define MOSI_PIN PB2
#define MISO_PIN PB3
#define SCK_PIN  PB1
#define GLOB_DC_PIN   PF7

// debug display stuff (sh1107)
#define SH1107_CS_PIN   PF6
#define SH1107_RST_PIN  PF5

// MT6835 stuff
#define MT6835_CS_PIN     PB6
#define MT6835_CAL_EN_PIN PB5

#endif //#ifndef global_h