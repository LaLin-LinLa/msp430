/*
 * This file contains some uSCI_A0 operation.
 * By IC爬虫 (1394024051@qq.com)
 * 2014-4-28 v1.0
 */
//#include "msp430g2553.h"
#include "USCI_A0.h"
//#include "stdio.h"
#include "mpu6050.h"
#include "IMU.h"

#define uchar unsigned char
#define uint unsigned int

//将“int”类型的数据分成两个单字节的数据
#define BYTE0(dwTemp)       (*(char *)(&dwTemp))
#define BYTE1(dwTemp)       (*((char *)(&dwTemp) + 1))
#define BYTE2(dwTemp)       (*((char *)(&dwTemp) + 2))
#define BYTE3(dwTemp)       (*((char *)(&dwTemp) + 3))

/*********************************************************
*名称：USCI_A0_init
*功能：串口初始化
*入口参数：无
*出口参数：无
*说明：设置为P1.1和P1.2为串口通信端口
**********************************************************/
void USCI_A0_init(void)
{
  P1SEL = BIT1 + BIT2 ;   // P1.1 = RXD, P1.2=TXD
  P1SEL2 = BIT1 + BIT2;                      
  UCA0CTL1 |= UCSSEL_2;   // SMCLK
  /*
  UCA0BR0 = 0x45;         // 8MHz 115200
  UCA0BR1 = 0;            // 8MHz 115200
  UCA0MCTL = 0x4a;        // 8MHz 115200  */    
  /*
  UCA0BR0 = 0x68; 
  UCA0BR1 = 0; 
  UCA0MCTL = 0x40;
  */
  UCA0MCTL = UCBRF_0 | UCBRS_4;
    
    /* Baud rate control register 0 */
    UCA0BR0 = 69;
  UCA0CTL1 &= ~UCSWRST;          // **Initialize USCI state machine**
  
  //IE2 |= UCA0RXIE + UCA0TXIE;  // Enable USCI_A0 TX/RX interrupt
  //IE2 |= UCA0RXIE;             // Enable USCI_A0 RX interrupt
  //__bis_SR_register(GIE);      // Enter LPM3 w/ interrupts enabled
}


/*********************************************************
*名称：UartTX_Send_String
*功能：串口发送字符串函数
*入口参数：*data:数据指针        len :数据长度
*出口参数：无
*说明：
**********************************************************/
void UartTX_Send_String(unsigned char *Data,int len)
{
  int j;
  for(j=0;j<len;j++)
  {
    UartTX_Send_char(*Data++);
  }
}

/*********************************************************
*名称：UartTX_Send_char
*功能：串口发送字符函数
*入口参数：c
*出口参数：无
*说明：
**********************************************************/
unsigned char UartTX_Send_char(unsigned char c)
{
    UCA0TXBUF=c;   
    while(!(IFG2&UCA0TXIFG));
    IFG2&=~UCA0TXIFG;
    return c;
}
/*********************************************************
*名称：int putchar
*功能：串口发送字符函数
*入口参数：ch
*出口参数：无
*说明：
**********************************************************/
int putchar(int ch)
{
  UCA0TXBUF=ch;
  while(!(IFG2&UCA0TXIFG));
   //UCA0TXBUF=ch;
  IFG2&=~UCA0TXIFG;
   return ch;
}


void sendChar(unsigned char c)
 {
   while(!(IFG2&UCA0TXIFG));
   UCA0TXBUF=c;
 }

void sendStr(unsigned char *s)
{
  while(*s!='\0')
  {
    sendChar(*s);
    s++;
  }
}

/*********************************************************
*名称：void Uart1_Send_AF
*功能：串口发送姿态数据
*入口参数：无
*出口参数：无
*说明：每一次执行这个函数就算是一帧数据，帧头为0X88，功能字
*      为0XAF
**********************************************************/
void Uart1_Send_AF(void)
{
  unsigned char sum = 0;//累加串口发送的数据的值，做校验用
  unsigned int _temp;   
  sum += UartTX_Send_char(0x88);  //帧头
  sum += UartTX_Send_char(0xAF);  //功能字
  
  sum += UartTX_Send_char(0x1c);
  sum += UartTX_Send_char( BYTE1(MPU6050_ACC_LAST_X) ); //发送加速度X轴数据的高8位
  sum += UartTX_Send_char( BYTE0(MPU6050_ACC_LAST_X) ); //发送加速度X轴数据的低8位
  
  sum += UartTX_Send_char( BYTE1(MPU6050_ACC_LAST_Y) ); //发送加速度Y轴数据的高8位
  sum += UartTX_Send_char( BYTE0(MPU6050_ACC_LAST_Y) ); //发送加速度Y轴数据的低8位
  
  sum += UartTX_Send_char( BYTE1(MPU6050_ACC_LAST_Z) ); //发送加速度Z轴数据的高8位
  sum += UartTX_Send_char( BYTE0(MPU6050_ACC_LAST_Z) ); //发送加速度Z轴数据的低8位
  
  sum += UartTX_Send_char( BYTE1(MPU6050_GYRO_LAST_X) ); //发送陀螺仪X轴数据的高8位
  sum += UartTX_Send_char( BYTE0(MPU6050_GYRO_LAST_X) ); //发送陀螺仪X轴数据的低8位
  
  sum += UartTX_Send_char( BYTE1(MPU6050_GYRO_LAST_Y) ); //发送陀螺仪Y轴数据的高8位
  sum += UartTX_Send_char( BYTE0(MPU6050_GYRO_LAST_Y) ); //发送陀螺仪Y轴数据的低8位
  
  sum += UartTX_Send_char( BYTE1(MPU6050_GYRO_LAST_Z) ); //发送陀螺仪Z轴数据的高8位
  sum += UartTX_Send_char( BYTE0(MPU6050_GYRO_LAST_Z) ); //发送陀螺仪Z轴数据的低8位
  sum += UartTX_Send_char(0);
  sum += UartTX_Send_char(0);
  sum += UartTX_Send_char(0);
  sum += UartTX_Send_char(0);
  sum += UartTX_Send_char(0);
  sum += UartTX_Send_char(0);
	
  _temp = (long int)(Q_ANGLE_X*100);
  sum += UartTX_Send_char( BYTE1(_temp) );
  sum += UartTX_Send_char( BYTE0(_temp) );
  _temp = (long int)(Q_ANGLE_Y*100);
  sum += UartTX_Send_char( BYTE1(_temp) );
  sum += UartTX_Send_char( BYTE0(_temp) );
	
  sum += UartTX_Send_char(0);
  sum += UartTX_Send_char(0);
  sum += UartTX_Send_char(0);
  sum += UartTX_Send_char(0);
  sum += UartTX_Send_char(0);
  sum += UartTX_Send_char(0);
  
  UartTX_Send_char(sum); //串口发送累加值用于校验
}
