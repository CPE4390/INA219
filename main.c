
#include <xc.h>
#include "LCD.h"

//RD5 = SDA
//RD6 = SCL
//pull-ups on board

void main(void) {
    OSCTUNEbits.PLLEN = 1;
    LCDInit();
    lprintf(0, "AHT25");
    
    while (1) {
    
    }
}


 