#include "INA219.h"
#include "pic18_i2c.h"

void INA219_Init(void) {
    pic18_i2c_enable();
    //default config value is 0x399f - modify as needed
    uint8_t val[] = {0x39, 0x9f};
    pic18_i2c_write(DEVICE_ADDRESS, INA219_CONFIGURATION, val, 2);
}

void INA219_SetCalibration(void) {
    // Shunt resistor = 0.1 ohm
    // Use Current LSB of 100uA
    // Calibration value = 4096 = 0x1000
    uint8_t val[] = {0x10, 0x00}; //put in big endian order
    pic18_i2c_write(DEVICE_ADDRESS, INA219_CALIBRATION, val, 2);
}

double INA219_ReadCurrent(void) {
    uint16_t reg;
    pic18_i2c_read(DEVICE_ADDRESS, INA219_CURRENT, (uint8_t *)&reg, 2);
    reg = (reg >> 8) | (reg << 8);  //convert to little endian
    return (int16_t)reg * 100e-6;
}

double INA219_ReadVoltage(void) {
    uint16_t reg;
    pic18_i2c_read(DEVICE_ADDRESS, INA219_BUS_VOLTAGE, (uint8_t *)&reg, 2);
    reg = (reg >> 8) | (reg << 8);  //convert to little endian
    reg >>= 3;  //discard lower 3 bits
    return reg * 0.004;
}

double INA219_ReadPower(void) {
    uint16_t reg;
    pic18_i2c_read(DEVICE_ADDRESS, INA219_POWER, (uint8_t *)&reg, 2);
    reg = (reg >> 8) | (reg << 8);  //convert to little endian
    return (int16_t)reg * (20 * 100e-6);
}
