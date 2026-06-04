#include "include.h"

const uint8_t font5x8[][5] = {
    { 0x00, 0x00, 0x00, 0x00, 0x00 }, // 32 ' '
    { 0x00, 0x00, 0x5F, 0x00, 0x00 }, // 33 '!'
    { 0x00, 0x07, 0x00, 0x07, 0x00 }, // 34 '"'
    { 0x14, 0x7F, 0x14, 0x7F, 0x14 }, // 35 '#'
    { 0x24, 0x2A, 0x7F, 0x2A, 0x12 }, // 36 '$'
    { 0x23, 0x13, 0x08, 0x64, 0x62 }, // 37 '%'
    { 0x36, 0x49, 0x55, 0x22, 0x50 }, // 38 '&'
    { 0x00, 0x05, 0x03, 0x00, 0x00 }, // 39 '''
    { 0x00, 0x1C, 0x22, 0x41, 0x00 }, // 40 '('
    { 0x00, 0x41, 0x22, 0x1C, 0x00 }, // 41 ')'
    { 0x08, 0x2A, 0x1C, 0x2A, 0x08 }, // 42 '*'
    { 0x08, 0x08, 0x3E, 0x08, 0x08 }, // 43 '+'
    { 0x00, 0x50, 0x30, 0x00, 0x00 }, // 44 ','
    { 0x08, 0x08, 0x08, 0x08, 0x08 }, // 45 '-'
    { 0x00, 0x60, 0x60, 0x00, 0x00 }, // 46 '.'
    { 0x20, 0x10, 0x08, 0x04, 0x02 }, // 47 '/'
    { 0x3E, 0x51, 0x49, 0x45, 0x3E }, // 48 '0'
    { 0x00, 0x42, 0x7F, 0x40, 0x00 }, // 49 '1'
    { 0x42, 0x61, 0x51, 0x49, 0x46 }, // 50 '2'
    { 0x21, 0x41, 0x45, 0x4B, 0x31 }, // 51 '3'
    { 0x18, 0x14, 0x12, 0x7F, 0x10 }, // 52 '4'
    { 0x27, 0x45, 0x45, 0x45, 0x39 }, // 53 '5'
    { 0x3C, 0x4A, 0x49, 0x49, 0x30 }, // 54 '6'
    { 0x01, 0x71, 0x09, 0x05, 0x03 }, // 55 '7'
    { 0x36, 0x49, 0x49, 0x49, 0x36 }, // 56 '8'
    { 0x06, 0x49, 0x49, 0x29, 0x1E }, // 57 '9'
    { 0x00, 0x36, 0x36, 0x00, 0x00 }, // 58 ':'
    { 0x00, 0x56, 0x36, 0x00, 0x00 }, // 59 ';'
    { 0x00, 0x08, 0x14, 0x22, 0x41 }, // 60 '<'
    { 0x14, 0x14, 0x14, 0x14, 0x14 }, // 61 '='
    { 0x41, 0x22, 0x14, 0x08, 0x00 }, // 62 '>'
    { 0x02, 0x01, 0x51, 0x09, 0x06 }, // 63 '?'
    { 0x32, 0x49, 0x79, 0x41, 0x3E }, // 64 '@'
    { 0x7E, 0x11, 0x11, 0x11, 0x7E }, // 65 'A'
    { 0x7F, 0x49, 0x49, 0x49, 0x36 }, // 66 'B'
    { 0x3E, 0x41, 0x41, 0x41, 0x22 }, // 67 'C'
    { 0x7F, 0x41, 0x41, 0x22, 0x1C }, // 68 'D'
    { 0x7F, 0x49, 0x49, 0x49, 0x41 }, // 69 'E'
    { 0x7F, 0x09, 0x09, 0x01, 0x01 }, // 70 'F'
    { 0x3E, 0x41, 0x41, 0x51, 0x32 }, // 71 'G'
    { 0x7F, 0x08, 0x08, 0x08, 0x7F }, // 72 'H'
    { 0x00, 0x41, 0x7F, 0x41, 0x00 }, // 73 'I'
    { 0x20, 0x40, 0x41, 0x3F, 0x01 }, // 74 'J'
    { 0x7F, 0x08, 0x14, 0x22, 0x41 }, // 75 'K'
    { 0x7F, 0x40, 0x40, 0x40, 0x40 }, // 76 'L'
    { 0x7F, 0x02, 0x04, 0x02, 0x7F }, // 77 'M'
    { 0x7F, 0x04, 0x08, 0x10, 0x7F }, // 78 'N'
    { 0x3E, 0x41, 0x41, 0x41, 0x3E }, // 79 'O'
    { 0x7F, 0x09, 0x09, 0x09, 0x06 }, // 80 'P'
    { 0x3E, 0x41, 0x51, 0x21, 0x5E }, // 81 'Q'
    { 0x7F, 0x09, 0x19, 0x29, 0x46 }, // 82 'R'
    { 0x46, 0x49, 0x49, 0x49, 0x31 }, // 83 'S'
    { 0x01, 0x01, 0x7F, 0x01, 0x01 }, // 84 'T'
    { 0x3F, 0x40, 0x40, 0x40, 0x3F }, // 85 'U'
    { 0x1F, 0x20, 0x40, 0x20, 0x1F }, // 86 'V'
    { 0x7F, 0x20, 0x18, 0x20, 0x7F }, // 87 'W'
    { 0x63, 0x14, 0x08, 0x14, 0x63 }, // 88 'X'
    { 0x03, 0x04, 0x78, 0x04, 0x03 }, // 89 'Y'
    { 0x61, 0x51, 0x49, 0x45, 0x43 }, // 90 'Z'
    { 0x00, 0x7F, 0x41, 0x41, 0x00 }, // 91 '['
    { 0x02, 0x04, 0x08, 0x10, 0x20 }, // 92 '\'
    { 0x00, 0x41, 0x41, 0x7F, 0x00 }, // 93 ']'
    { 0x04, 0x02, 0x01, 0x02, 0x04 }, // 94 '^'
    { 0x40, 0x40, 0x40, 0x40, 0x40 }, // 95 '_'
    { 0x00, 0x01, 0x02, 0x04, 0x00 }, // 96 '`'
    { 0x20, 0x54, 0x54, 0x54, 0x78 }, // 97 'a'
    { 0x7F, 0x48, 0x44, 0x44, 0x38 }, // 98 'b'
    { 0x38, 0x44, 0x44, 0x44, 0x20 }, // 99 'c'
    { 0x38, 0x44, 0x44, 0x48, 0x7F }, // 100 'd'
    { 0x38, 0x54, 0x54, 0x54, 0x18 }, // 101 'e'
    { 0x08, 0x7E, 0x09, 0x01, 0x02 }, // 102 'f'
    { 0x08, 0x54, 0x54, 0x54, 0x3C }, // 103 'g'
    { 0x7F, 0x08, 0x04, 0x04, 0x78 }, // 104 'h'
    { 0x00, 0x44, 0x7D, 0x40, 0x00 }, // 105 'i'
    { 0x20, 0x40, 0x44, 0x3D, 0x00 }, // 106 'j'
    { 0x7F, 0x10, 0x28, 0x44, 0x00 }, // 107 'k'
    { 0x00, 0x41, 0x7F, 0x40, 0x00 }, // 108 'l'
    { 0x7C, 0x04, 0x18, 0x04, 0x78 }, // 109 'm'
    { 0x7C, 0x08, 0x04, 0x04, 0x78 }, // 110 'n'
    { 0x38, 0x44, 0x44, 0x44, 0x38 }, // 111 'o'
    { 0x7C, 0x14, 0x14, 0x14, 0x08 }, // 112 'p'
    { 0x08, 0x14, 0x14, 0x18, 0x7C }, // 113 'q'
    { 0x7C, 0x08, 0x04, 0x04, 0x08 }, // 114 'r'
    { 0x48, 0x54, 0x54, 0x54, 0x20 }, // 115 's'
    { 0x04, 0x3F, 0x44, 0x40, 0x20 }, // 116 't'
    { 0x3C, 0x40, 0x40, 0x20, 0x7C }, // 117 'u'
    { 0x1C, 0x20, 0x40, 0x20, 0x1C }, // 118 'v'
    { 0x3C, 0x40, 0x30, 0x40, 0x3C }, // 119 'w'
    { 0x44, 0x28, 0x10, 0x28, 0x44 }, // 120 'x'
    { 0x0C, 0x50, 0x50, 0x50, 0x3C }, // 121 'y'
    { 0x44, 0x64, 0x54, 0x4C, 0x44 }, // 122 'z'
    { 0x00, 0x08, 0x36, 0x41, 0x00 }, // 123 '{'
    { 0x00, 0x00, 0x7F, 0x00, 0x00 }, // 124 '|'
    { 0x00, 0x41, 0x36, 0x08, 0x00 }, // 125 '}'
    { 0x08, 0x08, 0x2A, 0x1C, 0x08 }, // 126 '~'
};

void dWait(void) { while(!(SPSR & (1<<SPIF))); }

void SPIinit(void) {
    // SPI mode 3 (CPHA = 1, CPOL = 1)
    // master init
    PRR0 &= ~(1 << PRSPI); //dissable power limit
    DDRB |= (1 << MOSI_PIN) | (1 << SCK_PIN);
    DDRF |= (1 << DC_PIN) | (1 << CS_PIN) | (1 << RST_PIN);

    SPCR = (1 << SPE) | (1 << MSTR) | (1 << CPOL) | (1 << CPHA) | (1 << SPR0); //cfg

    //begin SH1107
    //idle highs
    PORTF |= (1 << RST_PIN); // pull high rst
    PORTF |= (1 << CS_PIN); //pull chip select high
    PORTF &= ~(1 << DC_PIN); //start in command mode
}

void SPItx(char data, uint8_t DC) { // DC: 1 data, 0 cmd
    if (DC) { PORTF |= (1 << DC_PIN); }
    else    { PORTF &= ~(1 << DC_PIN); }
    PORTF &= ~(1 << CS_PIN);
    SPDR = data;
    dWait();
    PORTF |= (1 << CS_PIN);
}

void SPIReset(void) {
    PORTF |= (1 << RST_PIN);
    _delay_us(10);
    PORTF &= ~(1 << RST_PIN);
    _delay_us(10);
    PORTF |= (1 << RST_PIN);  
}

void SH1107_init(void) {
    SPIinit();
    SPIReset();

    SPItx(0x20, 0); //Page Address Mode
    SPItx(0x81, 0); //Contrast control mode
    SPItx(0, 0); //Contrast control value
    SPItx(0xA0, 0); //Normal display direction (seg remap)
    SPItx(0xA8, 0); //multiplex rotation set
    SPItx(127, 0); //multiplex ratio
    SPItx(0xA6, 0); //normal display mode
    SPItx(0xD3, 0); //display offset mode
    SPItx(0x00, 0); //display offset value
    SPItx(0xAD, 0); //DC-DC control mode set
    SPItx(0x81, 0); //DC-DC On/Off mode set 

    //clear internal ram
    // Already cleared on reset?
    //end ram clear

    //set display on
    SPItx(0xAF, 0); //display on
    //end display on
    SH1107_clearScreen();
}

void SH1107_pageTX(uint8_t page, uint8_t column, char data, bool oneShot) { // page = y (0-15), column = x (0-127), data (char 0-7)
    uint8_t higher = 0b00010000;
    uint8_t lower = 0b00000000;

    SPItx(0b10110000 + page, 0); // set page (0 + offset)

    lower = (lower & 0b11110000) | (column & 0b00001111);
    higher = (higher & 0b11110000) | ((column >> 4) & 0b00000111);

    SPItx(higher, 0); // send our higher column address
    SPItx(lower, 0); // send our higher column address

    SPItx(data, 1); // send data in data mode
    PORTF &= ~(1 << DC_PIN); // set back to command mode
}

void SH1107_clearScreen(void) {
    uint8_t higher = 0b00010000;
    uint8_t lower = 0b00000000;

    for (uint8_t y = 0; y < 16; y++) {
        SPItx(0b10110000 + y, 0);
        for (uint8_t x = 0; x < 128; x++) {
            lower = (lower & 0b11110000) | (x & 0b00001111);
            higher = (higher & 0b11110000) | ((x >> 4) & 0b00000111);
            SPItx(higher, 0);
            SPItx(lower, 0);
            SPItx(0b00000000, 1);
            PORTF &= ~(1 << DC_PIN); // set back to command mode
        }
    }
}

void SH1107_clearPage(uint8_t page, uint8_t x0, uint8_t x1) {
    for (uint8_t i = x0; i < (x1 + 1); i++) {
        SH1107_pageTX(page, i, 0x00, true);
    }
}

void SH1107_drawPoint(uint8_t x, uint8_t y) { //char shape, uint8_t radius
    uint8_t higher = 0b00010000;
    uint8_t lower = 0b00000000;
    
    uint8_t page = y >> 3; // x/8
    uint8_t pageData = 0;
    pageData |= (1 << (page % 8));
    SPItx(0b10110000 + page, 0); 

    lower = (lower & 0b11110000) | (x & 0b00001111);
    higher = (higher & 0b11110000) | ((x >> 4) & 0b00000111);
    SPItx(higher, 0);
    SPItx(lower, 0);

    SPItx(pageData, 1);
}

void SH1107_drawLine(uint8_t x0,uint8_t y0,uint8_t x1,uint8_t y1) { //Bresenham's Line Algorithm
    int16_t dx = abs(x1 - x0);
    uint8_t sx = x0 < x1 ? 1 : -1;
    int16_t dy = -abs(y1 - y0);
    uint8_t sy = y0 < y1 ? 1 : -1;
    int16_t err = dx + dy;   // error term

    
    while (!(x0 == x1 && y0 == y1)) {
        // Draw pixel at current (x0, y0)
        uint8_t page = y0 >> 3;
        uint8_t bit = y0 & 7;
        unsigned char data = 1 << bit;
        SH1107_pageTX(page, x0, data, true);
        if (x0 == x1 && y0 == y1) break;
        int16_t e2 = 2 * err;
        if (e2 >= dy) { err += dy; x0 += sx; }
        if (e2 <= dx) { err += dx; y0 += sy; }
    }
}

void SH1107_drawRect(vector2 p1, vector2 p2, bool fill) { // DO NOT USE THIS!! Top left point is p1, bottom right point is p2
    uint8_t dx = (p2.x - p1.x);
    //uint8_t dy = -(p2.y - p1.y);
    uint8_t yCurr = p1.y;

    //draw left side
    uint8_t startingPage = p1.y >> 3;
    uint8_t endingPage = p2.y >> 3; // if statements are slower (1-2 cycles)

    for (uint8_t i = startingPage; i < endingPage + 1; i++) {
        unsigned char a = 0;
        for (uint8_t j = 0; j < (7 + 1); j++) {
            if (yCurr < (p2.y + 1)) {
                a |= (1 << (yCurr % 8));
            }
            yCurr += 1;
        }
        SH1107_pageTX(i, p1.x, a, true);
    }

    // top & bottom
    for (uint8_t i = 1; i < dx; i++) {
        unsigned char a = 0;
        yCurr = 0;
        if (fill) {
            for (uint8_t g = startingPage; g < endingPage + 1; g++) {
                for (uint8_t j = 0; j < (7 + 1); j++) {
                    if (yCurr < (p2.y + 1)) {
                        a |= (1 << (yCurr % 8));
                    }
                    yCurr += 1;
                }
                SH1107_pageTX(g, i, a, true);
            }
        }
        else {
            SH1107_pageTX(startingPage, i, (char)(1 << (p1.y % 8)), true);
            SH1107_pageTX(endingPage, i, (char)(1 << (p2.y % 8)), true);
        }
    }

    yCurr = 0;
    for (uint8_t i = startingPage; i < endingPage + 1; i++) {
        unsigned char a = 0;
        for (uint8_t j = 0; j < (7 + 1); j++) {
            if (yCurr < (p2.y + 1)) {
                a |= (1 << (yCurr % 8));
            }
            yCurr += 1;
        }
        SH1107_pageTX(i, p2.x, a, true);
    }
}

void SH1107_drawCricle();

void SH1107_drawTri();

void SH1107_drawChar(uint8_t x, uint8_t page, char c) {
    const uint8_t *glyph = font5x8[c - 32];
    for (uint8_t i = 0; i < 5; i++) {
        SH1107_pageTX(page, x + i, glyph[i], true);
    }
    SH1107_pageTX(page, x + 5, (char)0, true);
}

void SH1107_drawString(uint8_t x, uint8_t page, int8_t tracking, char str[], uint16_t val) { //tracking = spacing between chars. 1:1 = 3
    uint8_t chars = 0;
    uint8_t x1 = x;
    uint8_t valCharLen = val == 0 ? 1 : (floor(log10(val)) + 1);
    uint16_t valOffset = 1;  

    while (str[chars] != '\0') {
        if (str[chars] == '%' && str[chars + 1] != '\0') {
            if (str[chars + 1] == 'u') {
                valOffset = 1;
                for (uint8_t i = 0; i < valCharLen - 1; i++) {
                    valOffset *= 10;
                }
                for (uint8_t i = 0; i < valCharLen; i++) {
                    SH1107_drawChar(x1, page, (((val % (10 * valOffset)) / valOffset) + '0'));
                    valOffset /= 10;
                    x1 += (tracking + 5);
                }
            }
            chars += 2;
        } else {
            SH1107_drawChar(x1, page, str[chars]);
            x1 += (tracking + 5);
            chars++; 
        }
    }
}
