
#ifndef INA219_H
#define	INA219_H

void INA219_Init(void);
void INA219_SetCalibration(void);
double INA219_ReadCurrent(void);
double INA219_ReadVoltage(void);
double INA219_ReadPower(void);

enum {INA219_CONFIGURATION = 0, INA219_SHUNT_VOLTAGE = 1, INA219_BUS_VOLTAGE = 2,
INA219_POWER = 3, INA219_CURRENT = 4, INA219_CALIBRATION = 5};  

#define DEVICE_ADDRESS  0b01000000

#endif	/* INA219_H */

