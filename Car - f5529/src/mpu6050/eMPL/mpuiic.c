#include "mpuiic.h"

  //MPU IIC ��ʱ����
void MPU_IIC_Delay(void)
{
	__delay_us(2);
}

//��ʼ��IIC
void MPU_IIC_Init(void)
{					     
    P2DIR |= BIT4;  //SDA
    P2DIR |= BIT5;  //SCL
    P2OUT |= BIT4;
    P2OUT |= BIT5;
 
}
//����IIC��ʼ�ź�
void MPU_IIC_Start(void)
{
	MPU_SDA_OUT();     //sda�����
	MPU_IIC_SDA(1);
	MPU_IIC_SCL(1);
	MPU_IIC_Delay();
 	MPU_IIC_SDA(0);//START:when CLK is high,DATA change form high to low
	MPU_IIC_Delay();
	MPU_IIC_SCL(0);//ǯסI2C���ߣ�׼�����ͻ��������
}	  
//����IICֹͣ�ź�
void MPU_IIC_Stop(void)
{
	MPU_SDA_OUT();//sda�����
	MPU_IIC_SCL(0);
	MPU_IIC_SDA(0);//STOP:when CLK is high DATA change form low to high
 	MPU_IIC_Delay();
	MPU_IIC_SCL(1);
	MPU_IIC_SDA(1);//����I2C���߽����ź�
	MPU_IIC_Delay();							   	
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
u8 MPU_IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	MPU_SDA_IN();      //SDA����Ϊ����  
	MPU_IIC_SDA(1);MPU_IIC_Delay();
	MPU_IIC_SCL(1);MPU_IIC_Delay();
	while(MPU_READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			MPU_IIC_Stop();
			return 1;
		}
	}
	MPU_IIC_SCL(0);//ʱ�����0
	return 0;  
} 
//����ACKӦ��
void MPU_IIC_Ack(void)
{
	MPU_IIC_SCL(0);
	MPU_SDA_OUT();
	MPU_IIC_SDA(0);
	MPU_IIC_Delay();
	MPU_IIC_SCL(1);
	MPU_IIC_Delay();
	MPU_IIC_SCL(0);
}
//������ACKӦ��		    
void MPU_IIC_NAck(void)
{
	MPU_IIC_SCL(0);
	MPU_SDA_OUT();
	MPU_IIC_SDA(1);
	MPU_IIC_Delay();
	MPU_IIC_SCL(1);
	MPU_IIC_Delay();
	MPU_IIC_SCL(0);
}					 				     
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			  
void MPU_IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
	MPU_SDA_OUT(); 	    
    MPU_IIC_SCL(0);//����ʱ�ӿ�ʼ���ݴ���
    for(t=0;t<8;t++)
    {              
        MPU_IIC_SDA((txd&0x80)>>7);
        txd<<=1; 	  
		    MPU_IIC_SCL(1);
		    MPU_IIC_Delay(); 
		    MPU_IIC_SCL(0);
		    MPU_IIC_Delay();
    }	 
} 	    
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
u8 MPU_IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	MPU_SDA_IN();//SDA����Ϊ����
    for(i=0;i<8;i++ )
	{
        MPU_IIC_SCL(0);
        MPU_IIC_Delay();
		MPU_IIC_SCL(1);
        receive<<=1;
        if(MPU_READ_SDA)receive++;
		MPU_IIC_Delay(); 
    }					 
    if (!ack)
        MPU_IIC_NAck();//����nACK
    else
        MPU_IIC_Ack(); //����ACK   
    return receive;
}

//IIC����д
//addr:������ַ
//reg:�Ĵ�����ַ
//len:д�볤��
//buf:������
//����ֵ:0,����
//    ����,�������
u8 MPU_Write_Len(u8 addr,u8 reg,u8 len,u8 *buf)
{
    u8 i;
    MPU_IIC_Start();
    MPU_IIC_Send_Byte((addr<<1)|0);//����������ַ+д����
    if(MPU_IIC_Wait_Ack())  //�ȴ�Ӧ��
    {
        MPU_IIC_Stop();
        return 1;
    }
    MPU_IIC_Send_Byte(reg); //д�Ĵ�����ַ
    MPU_IIC_Wait_Ack();     //�ȴ�Ӧ��
    for(i=0;i<len;i++)
    {
        MPU_IIC_Send_Byte(buf[i]);  //��������
        if(MPU_IIC_Wait_Ack())      //�ȴ�ACK
        {
            MPU_IIC_Stop();
            return 1;
        }
    }
    MPU_IIC_Stop();
    return 0;
}
//IIC������
//addr:������ַ
//reg:Ҫ��ȡ�ļĴ�����ַ
//len:Ҫ��ȡ�ĳ���
//buf:��ȡ�������ݴ洢��
//����ֵ:0,����
//    ����,�������
u8 MPU_Read_Len(u8 addr,u8 reg,u8 len,u8 *buf)
{
    MPU_IIC_Start();
    MPU_IIC_Send_Byte((addr<<1)|0);//����������ַ+д����
    if(MPU_IIC_Wait_Ack())  //�ȴ�Ӧ��
    {
        MPU_IIC_Stop();
        return 1;
    }
    MPU_IIC_Send_Byte(reg); //д�Ĵ�����ַ
    MPU_IIC_Wait_Ack();     //�ȴ�Ӧ��
    MPU_IIC_Start();
    MPU_IIC_Send_Byte((addr<<1)|1);//����������ַ+������
    MPU_IIC_Wait_Ack();     //�ȴ�Ӧ��
    while(len)
    {
        if(len==1)*buf=MPU_IIC_Read_Byte(0);//������,����nACK
        else *buf=MPU_IIC_Read_Byte(1);     //������,����ACK
        len--;
        buf++;
    }
    MPU_IIC_Stop(); //����һ��ֹͣ����
    return 0;
}






















