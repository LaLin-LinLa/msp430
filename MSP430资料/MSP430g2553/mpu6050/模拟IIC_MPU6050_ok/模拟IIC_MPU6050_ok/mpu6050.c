/*
 * This file contains some mpu6050 operation.
 * By IC���� (1394024051@qq.com)
 * 2014-4-13 v1.0
 */
#include "mpu6050.h"

unsigned char   mpu6050_buffer[14];     //I2C��ȡ��������

int ACC_OFFSET_X,ACC_OFFSET_Y,ACC_OFFSET_Z;
int GYRO_OFFSET_X,GYRO_OFFSET_Y,GYRO_OFFSET_Z;

unsigned char	GYRO_OFFSET_OK = 1;
unsigned char	ACC_OFFSET_OK = 1;

int MPU6050_ACC_LAST_X,MPU6050_ACC_LAST_Y,MPU6050_ACC_LAST_Z;    //final accelerate speed 
int MPU6050_GYRO_LAST_X,MPU6050_GYRO_LAST_Y,MPU6050_GYRO_LAST_Z; //final  gyro  speed

/**********************************************************/
//�������ƣ�void MPU6050_Dataanl
//��ڲ�������
//���ڲ�������
//�������ܣ�MPU6050���ݶ�ȡ������
/**********************************************************/
void MPU6050_Dataanl(void)
{
#ifndef READALL
  MPU6050_ACC_LAST_X = GetAccelX() - ACC_OFFSET_X;
  MPU6050_ACC_LAST_Y = GetAccelY() - ACC_OFFSET_Y;
  MPU6050_ACC_LAST_Z = GetAccelZ() - ACC_OFFSET_Z;
  
  MPU6050_GYRO_LAST_X = GetAnguX() - GYRO_OFFSET_X;
  MPU6050_GYRO_LAST_Y = GetAnguY() - GYRO_OFFSET_Y;
  MPU6050_GYRO_LAST_Z = GetAnguZ() - GYRO_OFFSET_Z;
  //------------------------------------------------------------------//
  //����ƫ��
  if(!GYRO_OFFSET_OK)
  {
    static long int tempgx=0,tempgy=0,tempgz=0;
    static unsigned char cnt_g=0;

    if(cnt_g==0)
    {
      GYRO_OFFSET_X=0;
      GYRO_OFFSET_Y=0;
      GYRO_OFFSET_Z=0;
      tempgx = 0;
      tempgy = 0;
      tempgz = 0;
      cnt_g = 1;
    }
    tempgx+= MPU6050_GYRO_LAST_X;
    tempgy+= MPU6050_GYRO_LAST_Y;
    tempgz+= MPU6050_GYRO_LAST_Z;
    if(cnt_g==200)
    {
      GYRO_OFFSET_X=tempgx/cnt_g;
      GYRO_OFFSET_Y=tempgy/cnt_g;
      GYRO_OFFSET_Z=tempgz/cnt_g;
      cnt_g = 0;
      GYRO_OFFSET_OK = 1;
      
    }
    cnt_g++;
  }
  if(!ACC_OFFSET_OK)
  {
    static long int tempax=0,tempay=0,tempaz=0;
    static unsigned char cnt_a=0;
    
    if(cnt_a==0)
    {
      ACC_OFFSET_X = 0;
      ACC_OFFSET_Y = 0;
      ACC_OFFSET_Z = 0;
      tempax = 0;
      tempay = 0;
      tempaz = 0;
      cnt_a = 1;
      
    }
    tempax += MPU6050_ACC_LAST_X;//�ۼ�
    tempay += MPU6050_ACC_LAST_Y;
    tempaz += MPU6050_ACC_LAST_Z;
    if(cnt_a==200)
    {
      ACC_OFFSET_X = tempax/cnt_a;
      ACC_OFFSET_Y = tempay/cnt_a;
      ACC_OFFSET_Z = tempaz/cnt_a;
      cnt_a = 0;
      ACC_OFFSET_OK = 1;
      
    }
    cnt_a++;
  }
  //--------------------------------------------//
#else
struct MPU6050Struct *MPU6050WORK;
  MPU6050WORK = ReadMPU6050All();
  MPU6050_ACC_LAST_X = (MPU6050WORK ->MPU6050_ACC_X) - ACC_OFFSET_X;
  MPU6050_ACC_LAST_Y = (MPU6050WORK ->MPU6050_ACC_Y) - ACC_OFFSET_Y;
  MPU6050_ACC_LAST_Z = (MPU6050WORK ->MPU6050_ACC_Z) - ACC_OFFSET_Z;
  
  MPU6050_GYRO_LAST_X = (MPU6050WORK ->MPU6050_GYRO_X) - GYRO_OFFSET_X;
  MPU6050_GYRO_LAST_Y = (MPU6050WORK ->MPU6050_GYRO_Y) - GYRO_OFFSET_Y;
  MPU6050_GYRO_LAST_Z = (MPU6050WORK ->MPU6050_GYRO_Z) - GYRO_OFFSET_Z;

  if(!GYRO_OFFSET_OK)
  {
    static long int tempgx=0,tempgy=0,tempgz=0;
    static unsigned char cnt_g=0;

    if(cnt_g==0)
    {
      GYRO_OFFSET_X=0;
      GYRO_OFFSET_Y=0;
      GYRO_OFFSET_Z=0;
      tempgx = 0;
      tempgy = 0;
      tempgz = 0;
      cnt_g = 1;
    }
    tempgx+= MPU6050_GYRO_LAST_X;
    tempgy+= MPU6050_GYRO_LAST_Y;
    tempgz+= MPU6050_GYRO_LAST_Z;
    if(cnt_g==200)
    {
      GYRO_OFFSET_X=tempgx/cnt_g;
      GYRO_OFFSET_Y=tempgy/cnt_g;
      GYRO_OFFSET_Z=tempgz/cnt_g;
      cnt_g = 0;
      GYRO_OFFSET_OK = 1;
      
    }
    cnt_g++;
  }
  if(!ACC_OFFSET_OK)
  {
    static long int tempax=0,tempay=0,tempaz=0;
    static unsigned char cnt_a=0;
    
    if(cnt_a==0)
    {
      ACC_OFFSET_X = 0;
      ACC_OFFSET_Y = 0;
      ACC_OFFSET_Z = 0;
      tempax = 0;
      tempay = 0;
      tempaz = 0;
      cnt_a = 1;
      
    }
    tempax += MPU6050_ACC_LAST_X;//�ۼ�
    tempay += MPU6050_ACC_LAST_Y;
    tempaz += MPU6050_ACC_LAST_Z;
    if(cnt_a==200)
    {
      ACC_OFFSET_X = tempax/cnt_a;
      ACC_OFFSET_Y = tempay/cnt_a;
      ACC_OFFSET_Z = tempaz/cnt_a;
      cnt_a = 0;
      ACC_OFFSET_OK = 1;
      
    }
    cnt_a++;
  }
#endif
  
}

/**********************************************************/
//�������ƣ�void MPU6050Init
//��ڲ�������
//���ڲ�������
//�������ܣ�MPU6050��ʼ��
/**********************************************************/
void MPU6050_Init()
{
#ifdef IMITATEIIC
  InitImitateIICPort();
#else
  I2C_Init(SlaveAddr);
#endif
  I2C_Write(PWR_MGMT_1,0x00); //resume from sleep.
  I2C_Write(SMPLRT_DIV, 0x07);
  I2C_Write(CONFIG, 0x06);
  I2C_Write(GYRO_CONFIG, 0x18);
  I2C_Write(ACCEL_CONFIG, 0x01);
}
/**********************************************************/
//�������ƣ�int Get16Bit
//��ڲ�����address:��ȡ���ݵĵ�ַ
//���ڲ�������
//�������ܣ���ȡMPU6050��Ӧ��ַ�ϵ�����
/**********************************************************/
int Get16Bit (unsigned char  address)
{
#ifndef MULTIREAD
  unsigned char  ho,lo;
  int temp ;
  ho = I2C_Read(address);
  lo = I2C_Read(address+1);
  temp=ho;
  temp<<=8;
  temp+=lo;
  return temp ;
#else
  return( Double_Read_ADXL345(address));
#endif
}
/**********************************************************/
//�������ƣ�
//��ڲ�������
//���ڲ�������
//�������ܣ���ȡMPU6050��Ӧ���ϵļ��ٶ�����
/**********************************************************/
// X/Y/Z-Axis Acceleration
int GetAccelX ()
{
  return Get16Bit(ACCEL_XOUT_H);
}

int GetAccelY ()
{
  return Get16Bit(ACCEL_YOUT_H);
}

int GetAccelZ ()
{
  return Get16Bit(ACCEL_ZOUT_H);
}
/**********************************************************/
//�������ƣ�
//��ڲ�������
//���ڲ�������
//�������ܣ���ȡMPU6050��Ӧ���ϵĽ��ٶ�����
/**********************************************************/
// X/Y/Z-Axis Angular velocity
int GetAnguX ()
{
  return Get16Bit(GYRO_XOUT_H);
}

int GetAnguY ()
{
  return Get16Bit(GYRO_YOUT_H);
}

int GetAnguZ ()
{
  return Get16Bit(GYRO_ZOUT_H);
}
