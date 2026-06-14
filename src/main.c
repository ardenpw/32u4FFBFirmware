#include "include.h"
int main() {
    SH1107_init();
    usbInit(); 
    
    while(1) { prepUSBReport(); ep1RDY(); }; 
    /*
    sei() only enables interrupt servicing; it doesn’t create 
    a separate background task, so main must stay alive while 
    hardware events happen. In leymans terms, there wont be a 
    program to interrupt; thats why we need a while wait.
    */
   return 0;
   
} 
