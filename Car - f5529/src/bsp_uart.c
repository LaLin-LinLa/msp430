#include "bsp_uart.h"
uint8_t rxbuff0[UART0_RX_LEN] = {0};//�������0�����ڱ��洮������
uint8_t rxbuff1[UART1_RX_LEN] = {0};//�������1�����ڱ��洮������
uint8_t iscomend0 = 0;//��������������ж��Ƿ�һ�������������Ѿ��ɹ�����
uint8_t iscomend1 = 0;

void bsp_uart0_init(void)
{
    //����0��ʼ��
     P3SEL    |=  BIT3+BIT4 ;                        // P3.3,4 = USCI_A1 TXD/RXD
     UCA0CTL1 |=  UCSWRST;                      // **Put state machine in reset**
     UCA0CTL1 |=  UCSSEL_1;                     // ACLK
     UCA0BR0   =  0x03;                         // 32768Hz 9600 ������Ϊ9600
     UCA0BR1   =  0x00;                             // 32768Hz 9600
     UCA0MCTL |=  UCBRS_3 + UCBRF_0;           // Modulation UCBRSx=1, UCBRFx=0
     UCA0CTL1 &= ~UCSWRST;                   // **Initialize USCI state machine**
     UCA0IE   |=  UCRXIE;                       // Enable USCI_A1 RX interrupt ʹ���ж�
     UCA0IFG  &=~UCRXIFG;//����жϱ�־λ
}

void bsp_uart1_init(void)
{
    //����1��ʼ��9600
     P4SEL    |=  BIT4+BIT5 ;
     UCA1CTL1 |=  UCSWRST;
     UCA1CTL1 |=  UCSSEL_1;
     UCA1BR0   =  0x03;
     UCA1BR1   =  0x00;
     UCA1MCTL |=  UCBRS_3 + UCBRF_0;
     UCA1CTL1 &= ~UCSWRST;
     UCA1IE   |=  UCRXIE;
     UCA1IFG  &=~UCRXIFG;//����жϱ�־λ
}


/**
  * @brief  ����0��ӡ�ַ���
  * @param  pbuff����Ҫ��ӡ���ַ���
  * @retval None
  */
void UART0SendString(char *pbuff)
{
    while (*pbuff)                  //����ַ���������־
    {
        while(!(UCA0IFG & UCTXIFG));
        UCA0TXBUF = *pbuff++;
    }
}

/**
  * @brief  ����1��ӡ�ַ���
  * @param  pbuff����Ҫ��ӡ���ַ���
  * @retval None
  */
void UART1SendString(char *pbuff)
{
    while (*pbuff)                  //����ַ���������־
    {
        while(!(UCA1IFG & UCTXIFG));
        UCA1TXBUF = *pbuff++;
    }
}


/**
  * @brief  ����0��ӡ����������ͬprintf
  * @retval None
  */
void uart0_printf(const char *fmt,...)
{
    va_list ap;
    char string[40];
    va_start(ap,fmt);
    vsprintf(string,fmt,ap);//�˴�Ҳ����ʹ��sprintf�������÷���࣬�Լ��޸ļ��ɣ��˴���ȥ
    UART0SendString(string);
    va_end(ap);
}

/**
  * @brief  ����1��ӡ����������ͬprintf
  * @retval None
  */
void uart1_printf(const char *fmt,...)
{
    va_list ap;
    char string[40];
    va_start(ap,fmt);
    vsprintf(string,fmt,ap);//�˴�Ҳ����ʹ��sprintf�������÷���࣬�Լ��޸ļ��ɣ��˴���ȥ
    UART1SendString(string);
    va_end(ap);
}


//����0�����жϷ�����
void UART0_Receive_ISR(void)
{
    static uint8_t cnt = 0;
    UCA0IFG  &=~UCRXIFG;//����жϱ�־λ
    rxbuff0[cnt++] = UCA0RXBUF;//��������
    cnt %= UART0_RX_LEN;//��ֹcnt����UART_RX_LEN�����»��������
    if( rxbuff0[cnt - 1] == '\n')//�����⵽���������(�Ի�����Ϊ�������)
    {
      cnt = 0;//��λ������
      iscomend0 = 1;//����������
    }
}

//����1�����жϷ�����
void UART1_Receive_ISR(void)
{
    static uint8_t cnt = 0;
    UCA1IFG  &=~UCRXIFG;//����жϱ�־λ
    rxbuff1[cnt++] = UCA1RXBUF;//��������
    cnt %= UART1_RX_LEN;//��ֹcnt����UART_RX_LEN�����»��������
    if( rxbuff1[cnt - 1] == '\n')//�����⵽���������(�Ի�����Ϊ�������)
    {
      cnt = 0;//��λ������
      iscomend1 = 1;//����������
    }
}



