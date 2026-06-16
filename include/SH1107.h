#ifndef SH1107_h
#define SH1107_h

#include "stdbool.h"
#include "stdint.h"

typedef struct {
    uint8_t x;
    uint8_t y;
} vector2;

void SH1107_init(void);
void SH1107_pageTX(uint8_t page, uint8_t column, char data, bool oneShot);
void SH1107_clearScreen(void);
void SH1107_clearPage(uint8_t page, uint8_t x0, uint8_t x1);
void SH1107_drawPoint(uint8_t x, uint8_t y);
void SH1107_drawLine(uint8_t x0,uint8_t y0,uint8_t x1,uint8_t y1);
void SH1107_drawRect(vector2 p1, vector2 p2, bool fill);
void SH1107_drawChar(uint8_t x, uint8_t page, char c);
void SH1107_drawString(uint8_t x, uint8_t page, int8_t tracking, char str[], uint16_t val);

#endif // #ifndef SH1107_h