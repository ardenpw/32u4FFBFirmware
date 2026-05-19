#include "include.h"
int main() {
    SH1107_init();

    //uint8_t a = 0x12;

    //char b[] = { (a + '0'), '\0' };
    

    //SH1107_drawString(0, 0, 1, b);

    usbInit(); 
    while(1); 
    /*
    sei() only enables interrupt servicing; it doesn’t create 
    a separate background task, so main must stay alive while 
    hardware events happen. Thats why we need a while wait
    */
    //
   return 0;
   
} 
