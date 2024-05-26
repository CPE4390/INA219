
#include <xc.h>
#include "LCD.h"
#include "INA219.h"

//RD5 = SDA
//RD6 = SCL
//pull-ups on board
//Connect ground of PIC board to ground of measured power source.

void main(void) {
    OSCTUNEbits.PLLEN = 1;
    LCDInit();
    lprintf(0, "INA219");
    __delay_ms(2000);
    INA219_Init();
    INA219_SetCalibration();
    while (1) {
        double current = INA219_ReadCurrent();
        double voltage = INA219_ReadVoltage();
        double power = INA219_ReadPower();
        lprintf(1, "%.3lfA %.2lfV", current, voltage);
        lprintf(0, "%.2lfW", power);
        __delay_ms(200);
    }
}


 