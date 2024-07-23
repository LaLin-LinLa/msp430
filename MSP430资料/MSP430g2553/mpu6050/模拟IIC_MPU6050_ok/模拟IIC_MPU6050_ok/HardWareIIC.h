/*
 * This file contains some I2C operation.
 * By IC≈¿≥Ê (1394024051@qq.com)
 * 2014-4-13 v1.0
 */
#ifndef HARDWAREIIC_H_
#define HARDWAREIIC_H_

#include <msp430g2553.h>

#define uchar unsigned char
void I2C_Init(unsigned char SlaveAddr);
void I2C_WriteInit();
void I2C_ReadInit();
void I2C_Write(uchar,uchar);
uchar I2C_Read(uchar);


#endif /* I2C_H_ */

