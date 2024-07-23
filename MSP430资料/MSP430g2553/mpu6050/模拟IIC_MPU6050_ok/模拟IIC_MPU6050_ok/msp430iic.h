#ifndef msp430iic_h
#define msp430iic_h


#include"msp430g2553.h"
#define I2C_DIR  P1DIR
#define I2C_OUT  P1OUT
#define I2C_IN   P1IN
#define I2C_SCL  0x40     //SCL P1.6
#define I2C_SDA  0x80     //SDA P1.7

#define SDA_HIGH     I2C_OUT |= I2C_SDA         //SDA_HIGH
#define SDA_LOW      I2C_OUT &= ~I2C_SDA       //SDA_LOW

#define SCL_HIGH     I2C_DIR &= ~I2C_SCL                          //SCL_HIGH
#define SCL_LOW      I2C_DIR |= I2C_SCL;I2C_OUT &= ~I2C_SCL       //SCL_LOW

#define SET_SDA_IN   I2C_DIR &= ~I2C_SDA     //I2C_DIR &= ~I2C_SDA        //SET SDA IN
#define SET_SDA_OUT  I2C_DIR |=  I2C_SDA     //I2C_DIR |= I2C_SDA         //SET SDA OUT

#define SDA_IN ( I2C_IN & I2C_SDA)      //READ SDA DATA

#define  SlaveAddress   0xd0
#define Delay5us() __delay_cycles(80)           //5us/(1/16MHZ)=80
struct MPU6050Struct
{
  int MPU6050_ACC_X,MPU6050_ACC_Y,MPU6050_ACC_Z;    
  int MPU6050_GYRO_X,MPU6050_GYRO_Y,MPU6050_GYRO_Z; 
};
static struct MPU6050Struct   MPU6050Data;


void InitImitateIICPort(void);
void Single_Write_ADXL345(unsigned char REG_Address,unsigned char REG_data);
unsigned char  Single_Read_ADXL345(unsigned char  REG_Address);
int  Double_Read_ADXL345(unsigned char  REG_Address);
struct MPU6050Struct *ReadMPU6050All();
#endif