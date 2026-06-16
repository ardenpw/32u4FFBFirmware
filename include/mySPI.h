#ifndef mySPI_h
#define mySPI_h

void dWait(void);
void SPIinit(void);
uint8_t SPItx(char data, uint8_t DC, volatile uint8_t *port, uint8_t cs_pin);
void SPIReset(void);

#endif // #ifndef mySPI_h