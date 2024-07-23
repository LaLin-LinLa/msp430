/*
 * This file contains some uSCI_A0 operation.
 * By IC���� (1394024051@qq.com)
 * 2014-4-28 v1.0
 */
//#include "msp430g2553.h"
#include "USCI_A0.h"
//#include "stdio.h"
#include "mpu6050.h"
#include "IMU.h"

#define uchar unsigned char
#define uint unsigned int

//����int�����͵����ݷֳ��������ֽڵ�����
#define BYTE0(dwTemp)       (*(char *)(&dwTemp))
#define BYTE1(dwTemp)       (*((char *)(&dwTemp) + 1))
#define BYTE2(dwTemp)       (*((char *)(&dwTemp) + 2))
#define BYTE3(dwTemp)       (*((char *)(&dwTemp) + 3))

/*********************************************************
*���ƣ�USCI_A0_init
*���ܣ����ڳ�ʼ��
*��ڲ�������
*���ڲ�������
*˵��������ΪP1.1��P1.2Ϊ����ͨ�Ŷ˿�
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
*���ƣ�UartTX_Send_String
*���ܣ����ڷ����ַ�������
*��ڲ�����*data:����ָ��        len :���ݳ���
*���ڲ�������
*˵����
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
*���ƣ�UartTX_Send_char
*���ܣ����ڷ����ַ�����
*��ڲ�����c
*���ڲ�������
*˵����
**********************************************************/
unsigned char UartTX_Send_char(unsigned char c)
{
    UCA0TXBUF=c;   
    while(!(IFG2&UCA0TXIFG));
    IFG2&=~UCA0TXIFG;
    return c;
}
/*********************************************************
*���ƣ�int putchar
*���ܣ����ڷ����ַ�����
*��ڲ�����ch
*���ڲ�������
*˵����
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
*���ƣ�void Uart1_Send_AF
*���ܣ����ڷ�����̬����
*��ڲ�������
*���ڲ�������
*˵����ÿһ��ִ���������������һ֡���ݣ�֡ͷΪ0X88��������
*      Ϊ0XAF
**********************************************************/
void Uart1_Send_AF(void)
{
  unsigned char sum = 0;//�ۼӴ��ڷ��͵����ݵ�ֵ����У����
  unsigned int _temp;   
  sum += UartTX_Send_char(0x88);  //֡ͷ
  sum += UartTX_Send_char(0xAF);  //������
  
  sum += UartTX_Send_char(0x1c);
  sum += UartTX_Send_char( BYTE1(MPU6050_ACC_LAST_X) ); //���ͼ��ٶ�X�����ݵĸ�8λ
  sum += UartTX_Send_char( BYTE0(MPU6050_ACC_LAST_X) ); //���ͼ��ٶ�X�����ݵĵ�8λ
  
  sum += UartTX_Send_char( BYTE1(MPU6050_ACC_LAST_Y) ); //���ͼ��ٶ�Y�����ݵĸ�8λ
  sum += UartTX_Send_char( BYTE0(MPU6050_ACC_LAST_Y) ); //���ͼ��ٶ�Y�����ݵĵ�8λ
  
  sum += UartTX_Send_char( BYTE1(MPU6050_ACC_LAST_Z) ); //���ͼ��ٶ�Z�����ݵĸ�8λ
  sum += UartTX_Send_char( BYTE0(MPU6050_ACC_LAST_Z) ); //���ͼ��ٶ�Z�����ݵĵ�8λ
  
  sum += UartTX_Send_char( BYTE1(MPU6050_GYRO_LAST_X) ); //����������X�����ݵĸ�8λ
  sum += UartTX_Send_char( BYTE0(MPU6050_GYRO_LAST_X) ); //����������X�����ݵĵ�8λ
  
  sum += UartTX_Send_char( BYTE1(MPU6050_GYRO_LAST_Y) ); //����������Y�����ݵĸ�8λ
  sum += UartTX_Send_char( BYTE0(MPU6050_GYRO_LAST_Y) ); //����������Y�����ݵĵ�8λ
  
  sum += UartTX_Send_char( BYTE1(MPU6050_GYRO_LAST_Z) ); //����������Z�����ݵĸ�8λ
  sum += UartTX_Send_char( BYTE0(MPU6050_GYRO_LAST_Z) ); //����������Z�����ݵĵ�8λ
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
  
  UartTX_Send_char(sum); //���ڷ����ۼ�ֵ����У��
}
