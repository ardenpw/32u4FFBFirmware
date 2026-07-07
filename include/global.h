#ifndef global_h
#define global_h

#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define MIN(a,b) ((a) < (b) ? (a) : (b))

uint8_t udCfgStatus;
uint8_t idleLimit; 

#define STAY 1
#define FLIP 0

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