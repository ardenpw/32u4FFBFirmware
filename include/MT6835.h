#ifndef MT6835_h
#define MT6835_h

#include <stdint.h>

void MT6835_burstBegin(void);
void MT6835_burstEnd(void);
uint32_t MT6835_burstRead(void);
uint32_t MT6835_sequentialRead(void);

#endif // #ifndef MT6835_h