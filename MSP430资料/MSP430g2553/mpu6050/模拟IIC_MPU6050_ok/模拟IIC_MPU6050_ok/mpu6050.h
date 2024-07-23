/*
 * This file contains some mpu6050 operation.
 * By IC爬虫 (1394024051@qq.com)
 * 2014-4-13 v1.0
 */
#ifndef MPU6050_H_
#define MPU6050_H_

//***********************************************************
#define IMITATEIIC
#define MULTIREAD               //一次性读取多个字节
#define READALL                 //使用一次start 信号，14个寄存器的数据,屏蔽，则根据MULTIREAD读取，或一次一个，或一次两个。 
//mpu6050模块与iic模块结构定义
#ifdef IMITATEIIC
  #include"msp430iic.h"
  #define I2C_Write     Single_Write_ADXL345
  #define I2C_Read      Single_Read_ADXL345
#else
  #include "HardWareIIC.h"
  #define I2C_Write     I2C_Write
  #define I2C_Read      I2C_Read
#endif
//***********************************************************

//****************************************
// 定义MPU6050内部地址
//****************************************
#define	SMPLRT_DIV	0x19	//陀螺仪采样率，典型值：0x07(125Hz)
#define	CONFIG		0x1A	//低通滤波频率，典型值：0x06(5Hz)
#define	GYRO_CONFIG	0x1B	//陀螺仪自检及测量范围，典型值：0x18(不自检，2000deg/s)
#define	ACCEL_CONFIG	0x1C	//加速计自检、测量范围及高通滤波频率，典型值：0x01(不自检，2G，5Hz)
#define	ACCEL_XOUT_H	0x3B    //加速度
#define	ACCEL_XOUT_L	0x3C
#define	ACCEL_YOUT_H	0x3D
#define	ACCEL_YOUT_L	0x3E
#define	ACCEL_ZOUT_H	0x3F
#define	ACCEL_ZOUT_L	0x40
#define	TEMP_OUT_H	0x41
#define	TEMP_OUT_L	0x42
#define	GYRO_XOUT_H	0x43    //角速度
#define	GYRO_XOUT_L	0x44
#define	GYRO_YOUT_H	0x45
#define	GYRO_YOUT_L	0x46
#define	GYRO_ZOUT_H	0x47
#define	GYRO_ZOUT_L	0x48
#define	PWR_MGMT_1	0x6B	//电源管理，典型值：0x00(正常启用)

#define SlaveAddr	0x68    //MPU6050 address when AD0==0.


extern int MPU6050_ACC_LAST_X,MPU6050_ACC_LAST_Y,MPU6050_ACC_LAST_Z;
extern int MPU6050_GYRO_LAST_X,MPU6050_GYRO_LAST_Y,MPU6050_GYRO_LAST_Z;

extern unsigned char GYRO_OFFSET_OK;
extern unsigned char ACC_OFFSET_OK;

void MPU6050_Init();  //MPU6050初始化
int Get16Bit (unsigned char  address);  //读数据

// X/Y/Z-Axis Acceleration
int GetAccelX ();  //读取x轴的加速度
int GetAccelY ();  //读取y轴的加速度
int GetAccelZ ();  //读取z轴的加速度

// X/Y/Z-Axis Angular velocity
int GetAnguX ();  //读取x轴的角速度
int GetAnguY ();  //读取y轴的角速度
int GetAnguZ ();  //读取z轴的角速度

void MPU6050_Dataanl(void);
#endif /* MPU6050_H_ */
