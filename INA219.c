#include "INA219.h"
#include "pic18_i2c.h"

void INA219_Init(void) {
    pic18_i2c_enable();
    uint8_t val[] = {0x39, 0x9f};  //default values - modify as needed
    pic18_i2c_write(DEVICE_ADDRESS, INA219_CONFIGURATION, val, 2);
}

void INA219_SetCalibration(void) {
    //Shunt resistor = 0.1 ohm
    // Use Current LSB of 100uA
    // Calibration value = 4096 = 0x1000
    uint8_t val[] = {0x10, 0x00};
    pic18_i2c_write(DEVICE_ADDRESS, INA219_CALIBRATION, val, 2);
}

double INA219_ReadCurrent(void) {
    return 0.0;
}

double INA219_ReadVoltage(void) {
    uint8_t reg[2];
    pic18_i2c_read(DEVICE_ADDRESS, INA219_BUS_VOLTAGE, (uint8_t *)&reg, 2);
    uint16_t reg_le;
    reg_le = reg[0];
    reg_le <<= 8;
    reg_le |= reg[1];
    reg_le >>= 3;  //discard lower 3 bits
    double voltage = reg_le * 0.004;
    return voltage;
}

double INA219_ReadPower(void) {
    return 0.0;
}
