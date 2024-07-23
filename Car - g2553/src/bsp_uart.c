#include "bsp_uart.h"

uint8_t rxbuff[UART_RX_LEN] = {0};//������������ڱ��洮������
uint8_t iscomend = 0;//��������������ж��Ƿ�һ�������������Ѿ��ɹ�����

/**
  * @brief  ���ڳ�ʼ����Ĭ�ϲ�����9600��
  * @retval None
  */
void bsp_uart_init(void)
{
    /*��λUSCI_Ax*/
    UCA0CTL1 |= UCSWRST;
    /*ѡ��USCI_AxΪUARTģʽ*/
    UCA0CTL0 &= ~UCSYNC;
    /*����UARTʱ��ԴΪSMCLK*/
    UCA0CTL1 |= UCSSEL1;
    /*���ò�����Ϊ9600@16/8MHz*/
    UCA0BR0 = 0xCC;
    UCA0BR1 = 0x00;
    UCA0MCTL = 1 << 1;
    /*ʹ�ܶ˿ڸ���*/
    P1SEL |= BIT1 + BIT2;   //P1.1 RX
    P1SEL2 |= BIT1 + BIT2;  //P1.2 TX
    /*�����λλ��ʹ��UART*/
    UCA0CTL1 &= ~UCSWRST;


    //�����ж�����
    IE2 |= UCA0RXIE;
    //��ս����жϱ�־
    IFG2 &= ~UCA0RXIFG;

}

/**
  * @brief  ���ڴ�ӡ�ַ���
  * @param  pbuff����Ҫ��ӡ���ַ���
  * @retval None
  */
void UARTSendString(char *pbuff)
{
    while (*pbuff)                  //����ַ���������־
    {
        while(UCA0STAT & UCBUSY);
        UCA0TXBUF = *pbuff++;
    }
}

/**
  * @brief  ���ڴ�ӡ����������ͬprintf
  * @retval None
  */
void uart_printf(const char *fmt,...)
{
    va_list ap;
    char string[20];
    va_start(ap,fmt);
    vsprintf(string,fmt,ap);//�˴�Ҳ����ʹ��sprintf�������÷���࣬�Լ��޸ļ��ɣ��˴���ȥ
    UARTSendString(string);
    va_end(ap);
}

uint8_t mode;

//���ڽ����жϷ�����
void UART_Receive_ISR(void)
{
    if(IFG2 & UCA0RXIFG)//����Ƿ���USCI_A0�Ľ����жϣ�USCI_A0��USIC_B0�Ľ����жϹ���ͬһ����
    {
        IFG2 &= ~UCA0RXIFG;//�����־λ
        static uint8_t cnt = 0;
//        if(!iscomend){
//        rxbuff[cnt++] = UCA0RXBUF;//��������
//        cnt %= UART_RX_LEN;//��ֹcnt����UART_RX_LEN�����»��������
//        if( rxbuff[cnt - 1] == '\n')//�����⵽���������(�Ի�����Ϊ�������)
//        {
//            cnt = 0;//��λ������
//            iscomend = 1;//����������
//        }
//      }
        rxbuff[cnt++] = UCA0RXBUF;//��������
        cnt %= UART_RX_LEN;//��ֹcnt����UART_RX_LEN�����»��������
        if( rxbuff[cnt - 1] == '\n')//�����⵽���������(�Ի�����Ϊ�������)
        {
           cnt = 0;//��λ������
           mode = rxbuff[0]-48;
           iscomend = 1;//����������
        }

    }
}

