#include "include.h"
int main() {
    SH1107_init();
    /*
    uint32_t a = 0;
    while (1) {
        a = (MT6835_burstRead() >> 11);
        a = (uint16_t)(((uint64_t)a * 65535 + 1048576) / 2097151);
        SH1107_drawString(0,1,1,"%u", (uint16_t)a);
    }
    */
   usbInit(); 
   
   while(1) { prepUSBReport(); ep1RDY(); }; 
   /*
    */
    /*
    sei() only enables interrupt servicing; it doesn’t create 
    a separate background task, so main must stay alive while 
    hardware events happen. In leymans terms, there wont be a 
    program to interrupt; thats why we need a while wait.
    */
   return 0;
   
} 
