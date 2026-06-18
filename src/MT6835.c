#include "include.h"

uint8_t bursting = 0;
static uint32_t capture = 0;

void MT6835_burstBegin(void) { bursting = 1; }
void MT6835_burstEnd(void) { bursting = 0; }

uint32_t MT6835_burstRead(void) {
    capture = 0;
    SPItx(0xA0, 0, &PORTB, MT6835_CS_PIN, STAY);        
    SPItx(0x03, 0, &PORTB, MT6835_CS_PIN, STAY);
    capture |= ((uint32_t)SPItx(0x00, 0, &PORTB, MT6835_CS_PIN, STAY) << 24);
    capture |= ((uint32_t)SPItx(0x00, 0, &PORTB, MT6835_CS_PIN, STAY) << 16);
    capture |= ((uint32_t)SPItx(0x00, 0, &PORTB, MT6835_CS_PIN, STAY) << 8);
    capture |= ((uint32_t)SPItx(0x00, 0, &PORTB, MT6835_CS_PIN, FLIP));
    return capture;
}

/*
uint32_t MT6835_sequentialRead(void) {
    capture = 0;
    SPItx(0b00110000, 0, &PORTB, MT6835_CS_PIN, STAY);
    capture |= (SPItx(0x03, 0, &PORTB, MT6835_CS_PIN, STAY) << 24);
    SPItx(0b00110000, 0, &PORTB, MT6835_CS_PIN, STAY);
    capture |= (SPItx(0x04, 0, &PORTB, MT6835_CS_PIN, STAY) << 16);
    SPItx(0b00110000, 0, &PORTB, MT6835_CS_PIN, STAY);
    capture |= (SPItx(0x05, 0, &PORTB, MT6835_CS_PIN, STAY) << 8);
    SPItx(0b00110000, 0, &PORTB, MT6835_CS_PIN, STAY);
    capture |= (SPItx(0x06, 0, &PORTB, MT6835_CS_PIN, FLIP));
    return capture;
}
*/
    
    /*
uint32_t MT6835_sequentialRead(void) {
    uint32_t capture = 0;
    
    PORTB &= ~(1 << MT6835_CS_PIN);

    SPItx(0xA0, 0, &PORTB, MT6835_CS_PIN, STAY); // 1010 + upper 4 bits of 0x003
    SPItx(0x03, 0, &PORTB, MT6835_CS_PIN, STAY); // lower 8 bits of address
    
    uint8_t b3 = SPItx(0x00, 0, &PORTB, MT6835_CS_PIN, STAY); // reg 0x003
    uint8_t b4 = SPItx(0x00, 0, &PORTB, MT6835_CS_PIN, STAY); // reg 0x004
    uint8_t b5 = SPItx(0x00, 0, &PORTB, MT6835_CS_PIN, STAY); // reg 0x005
    uint8_t b6 = SPItx(0x00, 0, &PORTB, MT6835_CS_PIN, FLIP); // reg 0x006

    capture |= ((uint32_t)b3 << 16);
    capture |= ((uint32_t)b4 << 8);
    capture |= ((uint32_t)b5 << 0);
    
    return capture;
}
*/

/*
uint32_t MT6835_burst(void) {
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
*/