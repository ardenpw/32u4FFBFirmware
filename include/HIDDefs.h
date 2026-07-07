#ifndef HIDDefs_h
#define HIDDefs_h

#include <stdint.h>

uint8_t inputFlags;

typedef struct {
    uint8_t reportID;
    int16_t x;
    int16_t y;
} HIDInputReport;

typedef struct {
    uint8_t reportID;
    uint8_t state;
} HIDPIDStateReport;

HIDInputReport pendHIDInRept;
HIDPIDStateReport pendHIDStateInRept;

#endif // #ifndef HIDDefs_h