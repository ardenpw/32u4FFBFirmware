#include "include.h"

uint8_t bursting = 0;

void MT6835_burstBegin(void) { bursting = 1; }
void MT6835_burstEnd(void) { bursting = 0; }

uint32_t MT6835_burst(void) {
    static uint32_t capture = 0;
    if (!bursting) {
        // 0b10100000 + 00000011 
        SPItx(0xA0, 0, &PORTB, MT6835_CS_PIN);  
        SPItx(0x03, 0, &PORTB, MT6835_CS_PIN);
        bursting = 1;
        return 0;
    }
    capture |= (SPItx(0x00, 1, &PORTB, MT6835_CS_PIN) << 24);
    capture |= (SPItx(0x00, 1, &PORTB, MT6835_CS_PIN) << 16);
    capture |= (SPItx(0x00, 1, &PORTB, MT6835_CS_PIN) << 8);
    capture |= (SPItx(0x00, 1, &PORTB, MT6835_CS_PIN));
    return capture;
}