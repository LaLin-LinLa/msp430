#include"msp430iic.h"  

struct MPU6050Struct    MPU6050Data;
void InitImitateIICPort(void)
{ 
  SET_SDA_OUT;          //set  SDA PIN is out mode 
  SDA_HIGH;             // set SDA PIN out is high 
  SCL_HIGH;             //set SCL PIN is input mode ,pull up register to SCL PIN high 
}

/**************************************
��ʼ�ź�
**************************************/
void ADXL345_Start(void)
{
    SET_SDA_OUT;
    SDA_HIGH;                    //����������
    SCL_HIGH;                    //����ʱ����
    Delay5us();                 //��ʱ
    SDA_LOW;                    //�����½���
    Delay5us();                 //��ʱ
    SCL_LOW;                    //����ʱ����
}

/**************************************
ֹͣ�ź�
**************************************/
void ADXL345_Stop(void)
{
    SET_SDA_OUT;
    SDA_LOW;                    //����������
    SCL_HIGH;                    //����ʱ����
    Delay5us();                 //��ʱ
    SDA_HIGH;                    //����������
    Delay5us();                 //��ʱ
}

/**************************************
����Ӧ���ź�
��ڲ���:ack (0:ACK 1:NAK)
**************************************/
void ADXL345_SendACK(unsigned char ack)
{
    SET_SDA_OUT;
    if(ack)
      SDA_HIGH;                //дNACKӦ���ź�
    else
      SDA_LOW;                 //дACKӦ���ź�
    SCL_HIGH;                    //����ʱ����
    Delay5us();                 //��ʱ
    SCL_LOW;                    //����ʱ����
    Delay5us();                 //��ʱ
}

/**************************************
����Ӧ���ź�
**************************************/
unsigned char ADXL345_RecvACK(void)
{
    unsigned char ack;
    //------------------//
    //һ�������в��ɵ���˳�򣬷���ᵼ��ʱ�����
    SET_SDA_IN;
    SCL_HIGH;                    //����ʱ����  
    //-----------------//
    Delay5us();                 //��ʱ
    ack = SDA_IN;                   //��Ӧ���ź�
    SCL_LOW;                    //����ʱ����
    Delay5us();                 //��ʱ
    return ack;
}

/**************************************
��IIC���߷���һ���ֽ�����
**************************************/
void ADXL345_Senduchar(unsigned char dat)
{
    unsigned char i,m;
    SET_SDA_OUT;
    for (i=8; i!=0; i--)         //8λ������
    {
        m=dat & 0x80;           //�Ƴ����ݵ����λ
        if(m == 0x80)
            SDA_HIGH;
        else
            SDA_LOW;
        SCL_HIGH;                //����ʱ����
        Delay5us();             //��ʱ
        SCL_LOW;                //����ʱ����
        dat=dat<<1;
        Delay5us();             //��ʱ
    }
    ADXL345_RecvACK();
}

/**************************************
��IIC���߽���һ���ֽ�����
**************************************/
unsigned char  ADXL345_Recvuchar(void)
{
    unsigned char  i;
    unsigned char dat = 0;
    unsigned char m;
    SDA_HIGH;                    //ʹ���ڲ�����,׼����ȡ����,
    SET_SDA_IN;
    for (i=8; i!=0; i--)         //8λ������
    {
        dat <<= 1;
        SCL_HIGH;                //����ʱ����
        SET_SDA_IN;
        m = SDA_IN;
        if(m == I2C_SDA)
            dat = dat|0x01;
        Delay5us();             //��ʱ
        SCL_LOW;                //����ʱ����
        Delay5us();             //��ʱ
    }
    return dat;
}

//******���ֽ�д��*******************************************

void Single_Write_ADXL345(unsigned char REG_Address,unsigned char REG_data)
{
    ADXL345_Start();                  //��ʼ�ź�
    ADXL345_Senduchar(SlaveAddress);   //�����豸��ַ+д�ź�
    ADXL345_Senduchar(REG_Address);    //�ڲ��Ĵ�����ַ����ο�����pdf22ҳ
    ADXL345_Senduchar(REG_data);       //�ڲ��Ĵ������ݣ���ο�����pdf22ҳ
    ADXL345_Stop();                   //����ֹͣ�ź�
}

//********���ֽڶ�ȡ*****************************************
unsigned char  Single_Read_ADXL345(unsigned char  REG_Address)
{  unsigned char REG_data=0;
    ADXL345_Start();                          //��ʼ�ź�
    ADXL345_Senduchar(SlaveAddress);           //�����豸��ַ+д�ź� 
    ADXL345_Senduchar(REG_Address);                   //���ʹ洢��Ԫ��ַ����0��ʼ
    ADXL345_Start();                          //��ʼ�ź�
    ADXL345_Senduchar(SlaveAddress+1);         //�����豸��ַ+���ź�
    REG_data=ADXL345_Recvuchar();              //�����Ĵ�������
    ADXL345_SendACK(1);                     //NACK
    ADXL345_Stop();                           //ֹͣ�ź�
    return REG_data;
}
//********���ֽڶ�ȡ*****************************************
int  Double_Read_ADXL345(unsigned char  REG_Address)
{
    unsigned char ValueL=0;
    int Value=0;
    ADXL345_Start();                            //��ʼ�ź�
    ADXL345_Senduchar(SlaveAddress);            //�����豸��ַ+д�ź� 
    ADXL345_Senduchar(REG_Address);             //���ʹ洢��Ԫ��ַ����0��ʼ
    ADXL345_Start();                            //��ʼ�ź�
    ADXL345_Senduchar(SlaveAddress+1);          //�����豸��ַ+���ź�
    
    Value=ADXL345_Recvuchar();                  //�����Ĵ�������
    ADXL345_SendACK(0);                         //ACK
    
    ValueL=ADXL345_Recvuchar();                 //�����Ĵ�������
    ADXL345_SendACK(1);                         //NACK
    
    ADXL345_Stop();                             //ֹͣ�ź�
    Value=(Value<<8)+ValueL;
    return Value;
}

struct MPU6050Struct *ReadMPU6050All()
{
  unsigned char TempAcc1=0,TempAcc2=0,TempAcc3=0,TempAcc4=0,TempAcc5=0,TempAcc6=0;
  unsigned char TempGyro1=0,TempGyro2=0,TempGyro3=0,TempGyro4=0,TempGyro5=0,TempGyro6=0;

    ADXL345_Start();                            //��ʼ�ź�
    ADXL345_Senduchar(SlaveAddress);            //�����豸��ַ+д�ź� 
    ADXL345_Senduchar(0x3B);                    //���ʹ洢��Ԫ��ַ����0x3b��ʼ
    ADXL345_Start();                            //��ʼ�ź�
    ADXL345_Senduchar(SlaveAddress+1);          //�����豸��ַ+���ź�
    
    TempAcc2=ADXL345_Recvuchar();                  //�����Ĵ�������
    ADXL345_SendACK(0);                         //ACK
    
    TempAcc1=ADXL345_Recvuchar();                 //�����Ĵ�������
    ADXL345_SendACK(0);                         //ACK
    
    TempAcc4=ADXL345_Recvuchar();                  //�����Ĵ�������
    ADXL345_SendACK(0);                         //ACK
    
    TempAcc3=ADXL345_Recvuchar();                 //�����Ĵ�������
    ADXL345_SendACK(0);                         //ACK
    
    TempAcc6=ADXL345_Recvuchar();                  //�����Ĵ�������
    ADXL345_SendACK(0);                         //ACK
    
    TempAcc5=ADXL345_Recvuchar();                 //�����Ĵ�������
    ADXL345_SendACK(0);                         //ACK
    
    ADXL345_Recvuchar();                         //������������ַ������
    ADXL345_SendACK(0);                         //ACK
    
    ADXL345_Recvuchar();                         //������������ַ������
    ADXL345_SendACK(0); 
    
    TempGyro2=ADXL345_Recvuchar();                  //�����Ĵ�������
    ADXL345_SendACK(0);                         //ACK
    
    TempGyro1=ADXL345_Recvuchar();                 //�����Ĵ�������
    ADXL345_SendACK(0); 
    
    TempGyro4=ADXL345_Recvuchar();                  //�����Ĵ�������
    ADXL345_SendACK(0);                         //ACK
    
    TempGyro3=ADXL345_Recvuchar();                 //�����Ĵ�������
    ADXL345_SendACK(0); 
    
    TempGyro6=ADXL345_Recvuchar();                  //�����Ĵ�������
    ADXL345_SendACK(0);                         //ACK
    
    TempGyro5=ADXL345_Recvuchar();                 //�����Ĵ�������
    ADXL345_SendACK(1);                         //NACK
    
    ADXL345_Stop();

    MPU6050Data.MPU6050_ACC_X=(TempAcc2<<8) + TempAcc1;
    MPU6050Data.MPU6050_ACC_Y=(TempAcc4<<8) + TempAcc3;
    MPU6050Data.MPU6050_ACC_Z=(TempAcc6<<8) + TempAcc5;
    
    MPU6050Data.MPU6050_GYRO_X=(TempGyro2<<8) + TempGyro1;
    MPU6050Data.MPU6050_GYRO_Y=(TempGyro4<<8) + TempGyro3;
    MPU6050Data.MPU6050_GYRO_Z=(TempGyro6<<8) + TempGyro5;
    return (&MPU6050Data);
}