#ifndef __MPUIIC_H
#define __MPUIIC_H
#include "main.h"
 	   		   
//IO��������
#define MPU_SDA_IN()  { P2DIR &= ~BIT4;}
#define MPU_SDA_OUT() { P2DIR |= BIT4;}

//IO��������	 
#define MPU_IIC_SCL(a)    {if(a)P2OUT |= BIT5;else P2OUT &= ~BIT5;} 		//SCL
#define MPU_IIC_SDA(a)    {if(a)P2OUT |= BIT4;else P2OUT &= ~BIT4;}		    //SDA
#define MPU_READ_SDA    P2DIR &= BIT4 		//����SDA

//IIC���в�������
void MPU_IIC_Delay(void);				//MPU IIC��ʱ����
void MPU_IIC_Init(void);                //��ʼ��IIC��IO��				 
void MPU_IIC_Start(void);				//����IIC��ʼ�ź�
void MPU_IIC_Stop(void);	  			//����IICֹͣ�ź�
void MPU_IIC_Send_Byte(u8 txd);			//IIC����һ���ֽ�
u8 MPU_IIC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
u8 MPU_IIC_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void MPU_IIC_Ack(void);					//IIC����ACK�ź�
void MPU_IIC_NAck(void);				//IIC������ACK�ź�

u8 MPU_Write_Len(u8 addr,u8 reg,u8 len,u8 *buf);//IIC����д
u8 MPU_Read_Len(u8 addr,u8 reg,u8 len,u8 *buf); //IIC������

void IMPU_IC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8 MPU_IIC_Read_One_Byte(u8 daddr,u8 addr);	  
#endif
















