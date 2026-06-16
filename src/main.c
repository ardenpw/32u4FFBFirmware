#include "include.h"
int main() {
    SH1107_init();
    while (1) {
        SH1107_drawString(0,1,1,"%u", (uint16_t)MT6835_burst());
    }
    /*
    usbInit(); 
    
    while(1) { prepUSBReport(); ep1RDY(); }; 
    */
    /*
    sei() only enables interrupt servicing; it doesn’t create 
    a separate background task, so main must stay alive while 
    hardware events happen. In leymans terms, there wont be a 
    program to interrupt; thats why we need a while wait.
    */
   return 0;
   
} 
