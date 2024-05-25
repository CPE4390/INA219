
#include <xc.h>
#include "LCD.h"
#include "INA219.h"

//RD5 = SDA
//RD6 = SCL
//pull-ups on board

void main(void) {
    OSCTUNEbits.PLLEN = 1;
    LCDInit();
    lprintf(0, "INA219");
    INA219_Init();
    INA219_SetCalibration();
    while (1) {
        double current = INA219_ReadCurrent();
        double voltage = INA219_ReadVoltage();
        lprintf(1, "%.2lfA %.2lfV", current, voltage);
        __delay_ms(100);
    }
}


 