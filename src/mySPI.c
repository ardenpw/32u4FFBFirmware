#include "include.h"

void dWait(void) { while(!(SPSR & (1 << SPIF))); }

void SPIinit(void) {
    // SPI mode 3 (CPHA = 1, CPOL = 1)
    // master init
    PRR0 &= ~(1 << PRSPI); //dissable power limit
    DDRB |= (1 << MOSI_PIN) | (1 << SCK_PIN);
    DDRB &= ~(1 << MISO_PIN);

    DDRF |= (1 << GLOB_DC_PIN) | (1 << SH1107_CS_PIN) | (1 << SH1107_RST_PIN);
    DDRB |= (1 << MT6835_CS_PIN) | (1 << MT6835_CAL_EN_PIN);

    //SPCR = (1 << SPE) | (1 << MSTR) | (1 << CPOL) | (1 << CPHA) | (1 << SPR0); //cfg
    SPCR = 0b01011101;

    //idles
    //SH1107
    PORTF |= (1 << SH1107_RST_PIN); // pull high rst

    //globals
    PORTF |= (1 << SH1107_CS_PIN); //pull chip select high
    PORTF |= (1 << MT6835_CS_PIN); //pull chip select high
    PORTF &= ~(1 << GLOB_DC_PIN); //start in command mode
}

uint8_t SPItx(char data, uint8_t DC, volatile uint8_t *port, uint8_t cs_pin, uint8_t postState) { // DC: 1 data, 0 cmd
    *port &= ~(1 << cs_pin);
    if (DC) { PORTF |= (1 << GLOB_DC_PIN); }
    else    { PORTF &= ~(1 << GLOB_DC_PIN); }
    SPDR = data;
    dWait();
    uint8_t rx = SPDR;
    if (!postState) { *port |= (1 << cs_pin); }
    return rx;
}

void SPIReset(void) {
    PORTF |= (1 << SH1107_RST_PIN);
    _delay_us(10);
    PORTF &= ~(1 << SH1107_RST_PIN);
    _delay_us(10);
    PORTF |= (1 << SH1107_RST_PIN);  
}