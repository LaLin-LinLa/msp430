/*
 * This file contains some mpu6050 operation.
 * By IC���� (1394024051@qq.com)
 * 2014-4-13 v1.0
 */
#ifndef MPU6050_H_
#define MPU6050_H_

//***********************************************************
#define IMITATEIIC
#define MULTIREAD               //һ���Զ�ȡ����ֽ�
#define READALL                 //ʹ��һ��start �źţ�14���Ĵ���������,���Σ������MULTIREAD��ȡ����һ��һ������һ�������� 
//mpu6050ģ����iicģ��ṹ����
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
// ����MPU6050�ڲ���ַ
//****************************************
#define	SMPLRT_DIV	0x19	//�����ǲ����ʣ�����ֵ��0x07(125Hz)
#define	CONFIG		0x1A	//��ͨ�˲�Ƶ�ʣ�����ֵ��0x06(5Hz)
#define	GYRO_CONFIG	0x1B	//�������Լ켰������Χ������ֵ��0x18(���Լ죬2000deg/s)
#define	ACCEL_CONFIG	0x1C	//���ټ��Լ졢������Χ����ͨ�˲�Ƶ�ʣ�����ֵ��0x01(���Լ죬2G��5Hz)
#define	ACCEL_XOUT_H	0x3B    //���ٶ�
#define	ACCEL_XOUT_L	0x3C
#define	ACCEL_YOUT_H	0x3D
#define	ACCEL_YOUT_L	0x3E
#define	ACCEL_ZOUT_H	0x3F
#define	ACCEL_ZOUT_L	0x40
#define	TEMP_OUT_H	0x41
#define	TEMP_OUT_L	0x42
#define	GYRO_XOUT_H	0x43    //���ٶ�
#define	GYRO_XOUT_L	0x44
#define	GYRO_YOUT_H	0x45
#define	GYRO_YOUT_L	0x46
#define	GYRO_ZOUT_H	0x47
#define	GYRO_ZOUT_L	0x48
#define	PWR_MGMT_1	0x6B	//��Դ��������ֵ��0x00(��������)

#define SlaveAddr	0x68    //MPU6050 address when AD0==0.


extern int MPU6050_ACC_LAST_X,MPU6050_ACC_LAST_Y,MPU6050_ACC_LAST_Z;
extern int MPU6050_GYRO_LAST_X,MPU6050_GYRO_LAST_Y,MPU6050_GYRO_LAST_Z;

extern unsigned char GYRO_OFFSET_OK;
extern unsigned char ACC_OFFSET_OK;

void MPU6050_Init();  //MPU6050��ʼ��
int Get16Bit (unsigned char  address);  //������

// X/Y/Z-Axis Acceleration
int GetAccelX ();  //��ȡx��ļ��ٶ�
int GetAccelY ();  //��ȡy��ļ��ٶ�
int GetAccelZ ();  //��ȡz��ļ��ٶ�

// X/Y/Z-Axis Angular velocity
int GetAnguX ();  //��ȡx��Ľ��ٶ�
int GetAnguY ();  //��ȡy��Ľ��ٶ�
int GetAnguZ ();  //��ȡz��Ľ��ٶ�

void MPU6050_Dataanl(void);
#endif /* MPU6050_H_ */
