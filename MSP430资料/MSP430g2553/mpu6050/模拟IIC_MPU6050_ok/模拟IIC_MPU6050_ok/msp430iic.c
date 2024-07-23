#include"msp430iic.h"  

struct MPU6050Struct    MPU6050Data;
void InitImitateIICPort(void)
{ 
  SET_SDA_OUT;          //set  SDA PIN is out mode 
  SDA_HIGH;             // set SDA PIN out is high 
  SCL_HIGH;             //set SCL PIN is input mode ,pull up register to SCL PIN high 
}

/**************************************
起始信号
**************************************/
void ADXL345_Start(void)
{
    SET_SDA_OUT;
    SDA_HIGH;                    //拉高数据线
    SCL_HIGH;                    //拉高时钟线
    Delay5us();                 //延时
    SDA_LOW;                    //产生下降沿
    Delay5us();                 //延时
    SCL_LOW;                    //拉低时钟线
}

/**************************************
停止信号
**************************************/
void ADXL345_Stop(void)
{
    SET_SDA_OUT;
    SDA_LOW;                    //拉低数据线
    SCL_HIGH;                    //拉高时钟线
    Delay5us();                 //延时
    SDA_HIGH;                    //产生上升沿
    Delay5us();                 //延时
}

/**************************************
发送应答信号
入口参数:ack (0:ACK 1:NAK)
**************************************/
void ADXL345_SendACK(unsigned char ack)
{
    SET_SDA_OUT;
    if(ack)
      SDA_HIGH;                //写NACK应答信号
    else
      SDA_LOW;                 //写ACK应答信号
    SCL_HIGH;                    //拉高时钟线
    Delay5us();                 //延时
    SCL_LOW;                    //拉低时钟线
    Delay5us();                 //延时
}

/**************************************
接收应答信号
**************************************/
unsigned char ADXL345_RecvACK(void)
{
    unsigned char ack;
    //------------------//
    //一下两句切不可调换顺序，否则会导致时序错误
    SET_SDA_IN;
    SCL_HIGH;                    //拉高时钟线  
    //-----------------//
    Delay5us();                 //延时
    ack = SDA_IN;                   //读应答信号
    SCL_LOW;                    //拉低时钟线
    Delay5us();                 //延时
    return ack;
}

/**************************************
向IIC总线发送一个字节数据
**************************************/
void ADXL345_Senduchar(unsigned char dat)
{
    unsigned char i,m;
    SET_SDA_OUT;
    for (i=8; i!=0; i--)         //8位计数器
    {
        m=dat & 0x80;           //移出数据的最高位
        if(m == 0x80)
            SDA_HIGH;
        else
            SDA_LOW;
        SCL_HIGH;                //拉高时钟线
        Delay5us();             //延时
        SCL_LOW;                //拉低时钟线
        dat=dat<<1;
        Delay5us();             //延时
    }
    ADXL345_RecvACK();
}

/**************************************
从IIC总线接收一个字节数据
**************************************/
unsigned char  ADXL345_Recvuchar(void)
{
    unsigned char  i;
    unsigned char dat = 0;
    unsigned char m;
    SDA_HIGH;                    //使能内部上拉,准备读取数据,
    SET_SDA_IN;
    for (i=8; i!=0; i--)         //8位计数器
    {
        dat <<= 1;
        SCL_HIGH;                //拉高时钟线
        SET_SDA_IN;
        m = SDA_IN;
        if(m == I2C_SDA)
            dat = dat|0x01;
        Delay5us();             //延时
        SCL_LOW;                //拉低时钟线
        Delay5us();             //延时
    }
    return dat;
}

//******单字节写入*******************************************

void Single_Write_ADXL345(unsigned char REG_Address,unsigned char REG_data)
{
    ADXL345_Start();                  //起始信号
    ADXL345_Senduchar(SlaveAddress);   //发送设备地址+写信号
    ADXL345_Senduchar(REG_Address);    //内部寄存器地址，请参考中文pdf22页
    ADXL345_Senduchar(REG_data);       //内部寄存器数据，请参考中文pdf22页
    ADXL345_Stop();                   //发送停止信号
}

//********单字节读取*****************************************
unsigned char  Single_Read_ADXL345(unsigned char  REG_Address)
{  unsigned char REG_data=0;
    ADXL345_Start();                          //起始信号
    ADXL345_Senduchar(SlaveAddress);           //发送设备地址+写信号 
    ADXL345_Senduchar(REG_Address);                   //发送存储单元地址，从0开始
    ADXL345_Start();                          //起始信号
    ADXL345_Senduchar(SlaveAddress+1);         //发送设备地址+读信号
    REG_data=ADXL345_Recvuchar();              //读出寄存器数据
    ADXL345_SendACK(1);                     //NACK
    ADXL345_Stop();                           //停止信号
    return REG_data;
}
//********多字节读取*****************************************
int  Double_Read_ADXL345(unsigned char  REG_Address)
{
    unsigned char ValueL=0;
    int Value=0;
    ADXL345_Start();                            //起始信号
    ADXL345_Senduchar(SlaveAddress);            //发送设备地址+写信号 
    ADXL345_Senduchar(REG_Address);             //发送存储单元地址，从0开始
    ADXL345_Start();                            //起始信号
    ADXL345_Senduchar(SlaveAddress+1);          //发送设备地址+读信号
    
    Value=ADXL345_Recvuchar();                  //读出寄存器数据
    ADXL345_SendACK(0);                         //ACK
    
    ValueL=ADXL345_Recvuchar();                 //读出寄存器数据
    ADXL345_SendACK(1);                         //NACK
    
    ADXL345_Stop();                             //停止信号
    Value=(Value<<8)+ValueL;
    return Value;
}

struct MPU6050Struct *ReadMPU6050All()
{
  unsigned char TempAcc1=0,TempAcc2=0,TempAcc3=0,TempAcc4=0,TempAcc5=0,TempAcc6=0;
  unsigned char TempGyro1=0,TempGyro2=0,TempGyro3=0,TempGyro4=0,TempGyro5=0,TempGyro6=0;

    ADXL345_Start();                            //起始信号
    ADXL345_Senduchar(SlaveAddress);            //发送设备地址+写信号 
    ADXL345_Senduchar(0x3B);                    //发送存储单元地址，从0x3b开始
    ADXL345_Start();                            //起始信号
    ADXL345_Senduchar(SlaveAddress+1);          //发送设备地址+读信号
    
    TempAcc2=ADXL345_Recvuchar();                  //读出寄存器数据
    ADXL345_SendACK(0);                         //ACK
    
    TempAcc1=ADXL345_Recvuchar();                 //读出寄存器数据
    ADXL345_SendACK(0);                         //ACK
    
    TempAcc4=ADXL345_Recvuchar();                  //读出寄存器数据
    ADXL345_SendACK(0);                         //ACK
    
    TempAcc3=ADXL345_Recvuchar();                 //读出寄存器数据
    ADXL345_SendACK(0);                         //ACK
    
    TempAcc6=ADXL345_Recvuchar();                  //读出寄存器数据
    ADXL345_SendACK(0);                         //ACK
    
    TempAcc5=ADXL345_Recvuchar();                 //读出寄存器数据
    ADXL345_SendACK(0);                         //ACK
    
    ADXL345_Recvuchar();                         //丢弃不连续地址的数据
    ADXL345_SendACK(0);                         //ACK
    
    ADXL345_Recvuchar();                         //丢弃不连续地址的数据
    ADXL345_SendACK(0); 
    
    TempGyro2=ADXL345_Recvuchar();                  //读出寄存器数据
    ADXL345_SendACK(0);                         //ACK
    
    TempGyro1=ADXL345_Recvuchar();                 //读出寄存器数据
    ADXL345_SendACK(0); 
    
    TempGyro4=ADXL345_Recvuchar();                  //读出寄存器数据
    ADXL345_SendACK(0);                         //ACK
    
    TempGyro3=ADXL345_Recvuchar();                 //读出寄存器数据
    ADXL345_SendACK(0); 
    
    TempGyro6=ADXL345_Recvuchar();                  //读出寄存器数据
    ADXL345_SendACK(0);                         //ACK
    
    TempGyro5=ADXL345_Recvuchar();                 //读出寄存器数据
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