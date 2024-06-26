#include <xc.h>
#include "pic18_i2c.h"

void pic18_i2c_enable(void) {
    TRISD |= 0b01100000; //MMSP2 uses RD5 as SDA, RD6 as SCL, both set as inputs
    SSP2ADD = 19; //400kHz
    SSP2CON1bits.SSPM = 0b1000; //I2C Master mode
    SSP2CON1bits.SSPEN = 1; //Enable MSSP
}

void pic18_i2c_disable(void) {
    SSP2CON1bits.SSPEN = 0; //Disable MSSP
}

int8_t pic18_i2c_write(uint8_t slave_addr, uint8_t reg_addr, uint8_t *data, uint16_t length) {
    SSP2CON2bits.SEN = 1;
    while (SSP2CON2bits.SEN == 1);
    SSP2BUF = (uint8_t)(slave_addr << 1);
    while (SSP2STATbits.BF || SSP2STATbits.R_W);
    if (SSP2CON2bits.ACKSTAT == 1) {
        SSP2CON2bits.PEN = 1;
        while (SSP2CON2bits.PEN == 1);
        return -1;
    }
    SSP2BUF = reg_addr;
    while (SSP2STATbits.BF || SSP2STATbits.R_W);
    while (length > 0) {
        SSP2BUF = *data;
        while (SSP2STATbits.BF || SSP2STATbits.R_W);
        --length;
        ++data;
    }
    SSP2CON2bits.PEN = 1;
    while (SSP2CON2bits.PEN == 1);
    return 0;
}

int8_t pic18_i2c_read(uint8_t slave_addr, uint8_t reg_addr, uint8_t *data, uint16_t length) {
    SSP2CON2bits.SEN = 1;
    while (SSP2CON2bits.SEN == 1);
    SSP2BUF = (uint8_t)(slave_addr << 1);
    while (SSP2STATbits.BF || SSP2STATbits.R_W);
    if (SSP2CON2bits.ACKSTAT == 1) {
        SSP2CON2bits.PEN = 1;
        while (SSP2CON2bits.PEN == 1);
        return -1;
    }
    SSP2BUF = reg_addr;
    while (SSP2STATbits.BF || SSP2STATbits.R_W);
    SSP2CON2bits.RSEN = 1;
    while (SSP2CON2bits.RSEN == 1);
    SSP2BUF = (uint8_t)((slave_addr << 1) + 1); //address with R/W set for read
    while (SSP2STATbits.BF || SSP2STATbits.R_W);
    while (length > 0) {
        SSP2CON2bits.RCEN = 1;
        while (!SSP2STATbits.BF);
        *data = SSP2BUF;
        if (length > 1) {
            SSP2CON2bits.ACKDT = 0;
        } else {
            SSP2CON2bits.ACKDT = 1;
        }
        SSP2CON2bits.ACKEN = 1;
        while (SSP2CON2bits.ACKEN != 0);
        --length;
        ++data;
    }
    SSP2CON2bits.PEN = 1;
    while (SSP2CON2bits.PEN == 1);
    return 0;
}

