#include "bsp_uart.h"

uint8_t rxbuff[UART_RX_LEN] = {0};//命令缓冲区，用于保存串口命令
uint8_t iscomend = 0;//命令结束？用于判断是否一句完整的命令已经成功接收

/**
  * @brief  串口初始化（默认波特率9600）
  * @retval None
  */
void bsp_uart_init(void)
{
    /*复位USCI_Ax*/
    UCA0CTL1 |= UCSWRST;
    /*选择USCI_Ax为UART模式*/
    UCA0CTL0 &= ~UCSYNC;
    /*配置UART时钟源为SMCLK*/
    UCA0CTL1 |= UCSSEL1;
    /*配置波特率为9600@16/8MHz*/
    UCA0BR0 = 0xCC;
    UCA0BR1 = 0x00;
    UCA0MCTL = 1 << 1;
    /*使能端口复用*/
    P1SEL |= BIT1 + BIT2;   //P1.1 RX
    P1SEL2 |= BIT1 + BIT2;  //P1.2 TX
    /*清除复位位，使能UART*/
    UCA0CTL1 &= ~UCSWRST;


    //接收中断启用
    IE2 |= UCA0RXIE;
    //清空接收中断标志
    IFG2 &= ~UCA0RXIFG;

}

/**
  * @brief  串口打印字符串
  * @param  pbuff：需要打印的字符串
  * @retval None
  */
void UARTSendString(char *pbuff)
{
    while (*pbuff)                  //检测字符串结束标志
    {
        while(UCA0STAT & UCBUSY);
        UCA0TXBUF = *pbuff++;
    }
}

/**
  * @brief  串口打印函数，功能同printf
  * @retval None
  */
void uart_printf(const char *fmt,...)
{
    va_list ap;
    char string[20];
    va_start(ap,fmt);
    vsprintf(string,fmt,ap);//此处也可以使用sprintf函数，用法差不多，稍加修改即可，此处略去
    UARTSendString(string);
    va_end(ap);
}

uint8_t mode;

//串口接收中断服务函数
void UART_Receive_ISR(void)
{
    if(IFG2 & UCA0RXIFG)//检测是否是USCI_A0的接收中断，USCI_A0和USIC_B0的接收中断共享同一向量
    {
        IFG2 &= ~UCA0RXIFG;//清除标志位
        static uint8_t cnt = 0;
//        if(!iscomend){
//        rxbuff[cnt++] = UCA0RXBUF;//保存命令
//        cnt %= UART_RX_LEN;//防止cnt大于UART_RX_LEN，导致缓冲区溢出
//        if( rxbuff[cnt - 1] == '\n')//如果检测到命令结束符(以换行作为命令结束)
//        {
//            cnt = 0;//复位计数器
//            iscomend = 1;//命令接收完毕
//        }
//      }
        rxbuff[cnt++] = UCA0RXBUF;//保存命令
        cnt %= UART_RX_LEN;//防止cnt大于UART_RX_LEN，导致缓冲区溢出
        if( rxbuff[cnt - 1] == '\n')//如果检测到命令结束符(以换行作为命令结束)
        {
           cnt = 0;//复位计数器
           mode = rxbuff[0]-48;
           iscomend = 1;//命令接收完毕
        }

    }
}

