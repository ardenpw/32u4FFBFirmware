#include "include.h"
int main() {
    SH1107_init();
    usbInit(); 

    typedef struct {
        int8_t x, y;
    } boing;

    boing a;
    int8_t packets = 0;

    while(1) {
        UENUM = 1;
        while (UEBCLX < sizeof(boing)) {
            while (!(UEINTX & (1 << RWAL)));
            UEDATX = packets++;
            UEDATX = 0;
            UEINTX &= ~(1 << FIFOCON); //push fifo
        }
        
    }; 
    /*
    sei() only enables interrupt servicing; it doesn’t create 
    a separate background task, so main must stay alive while 
    hardware events happen. In leymans terms, there wont be a 
    program to interrupt; thats why we need a while wait.
    */
   return 0;
   
} 
