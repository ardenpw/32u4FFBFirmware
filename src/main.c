#include "include.h"
int main() {
    SH1107_init();
    usbInit();

    DDRD &= ~(1 << PORTD3);
    PORTD |= (1 << PORTD3);

    EICRA &= ~(1 << ISC30);
    EICRA &= ~(1 << ISC31);

    EIMSK |= (1 << INT3);

    sei();
    
    while(1) { 
        prepUSBReport(); 
        ep1RDY();
        ep2Dump();
        
    }; 
    /*
    sei() only enables interrupt servicing; it doesn’t create 
    a separate background task, so main must stay alive while 
    hardware events happen. In leymans terms, there wont be a 
    program to interrupt; thats why we need a while wait.
    */
    return 0;
   
} 
