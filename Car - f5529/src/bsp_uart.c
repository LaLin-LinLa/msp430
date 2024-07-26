#include "bsp_uart.h"
uint8_t rxbuff0[UART0_RX_LEN] = {0};//命令缓冲区0，用于保存串口命令
uint8_t rxbuff1[UART1_RX_LEN] = {0};//命令缓冲区1，用于保存串口命令
uint8_t iscomend0 = 0;//命令结束？用于判断是否一句完整的命令已经成功接收
uint8_t iscomend1 = 0;

void bsp_uart0_init(void)
{
    //串口0初始化
     P3SEL    |=  BIT3+BIT4 ;                        // P3.3,4 = USCI_A1 TXD/RXD
     UCA0CTL1 |=  UCSWRST;                      // **Put state machine in reset**
     UCA0CTL1 |=  UCSSEL_1;                     // ACLK
     UCA0BR0   =  0x03;                         // 32768Hz 9600 波特率为9600
     UCA0BR1   =  0x00;                             // 32768Hz 9600
     UCA0MCTL |=  UCBRS_3 + UCBRF_0;           // Modulation UCBRSx=1, UCBRFx=0
     UCA0CTL1 &= ~UCSWRST;                   // **Initialize USCI state machine**
     UCA0IE   |=  UCRXIE;                       // Enable USCI_A1 RX interrupt 使能中断
     UCA0IFG  &=~UCRXIFG;//清除中断标志位
}

void bsp_uart1_init(void)
{
    //串口1初始化9600
     P4SEL    |=  BIT4+BIT5 ;
     UCA1CTL1 |=  UCSWRST;
     UCA1CTL1 |=  UCSSEL_1;
     UCA1BR0   =  0x03;
     UCA1BR1   =  0x00;
     UCA1MCTL |=  UCBRS_3 + UCBRF_0;
     UCA1CTL1 &= ~UCSWRST;
     UCA1IE   |=  UCRXIE;
     UCA1IFG  &=~UCRXIFG;//清除中断标志位
}


/**
  * @brief  串口0打印字符串
  * @param  pbuff：需要打印的字符串
  * @retval None
  */
void UART0SendString(char *pbuff)
{
    while (*pbuff)                  //检测字符串结束标志
    {
        while(!(UCA0IFG & UCTXIFG));
        UCA0TXBUF = *pbuff++;
    }
}

/**
  * @brief  串口1打印字符串
  * @param  pbuff：需要打印的字符串
  * @retval None
  */
void UART1SendString(char *pbuff)
{
    while (*pbuff)                  //检测字符串结束标志
    {
        while(!(UCA1IFG & UCTXIFG));
        UCA1TXBUF = *pbuff++;
    }
}


/**
  * @brief  串口0打印函数，功能同printf
  * @retval None
  */
void uart0_printf(const char *fmt,...)
{
    va_list ap;
    char string[40];
    va_start(ap,fmt);
    vsprintf(string,fmt,ap);//此处也可以使用sprintf函数，用法差不多，稍加修改即可，此处略去
    UART0SendString(string);
    va_end(ap);
}

/**
  * @brief  串口1打印函数，功能同printf
  * @retval None
  */
void uart1_printf(const char *fmt,...)
{
    va_list ap;
    char string[40];
    va_start(ap,fmt);
    vsprintf(string,fmt,ap);//此处也可以使用sprintf函数，用法差不多，稍加修改即可，此处略去
    UART1SendString(string);
    va_end(ap);
}


//串口0接收中断服务函数
void UART0_Receive_ISR(void)
{
    static uint8_t cnt = 0;
    UCA0IFG  &=~UCRXIFG;//清除中断标志位
    rxbuff0[cnt++] = UCA0RXBUF;//保存命令
    cnt %= UART0_RX_LEN;//防止cnt大于UART_RX_LEN，导致缓冲区溢出
    if( rxbuff0[cnt - 1] == '\n')//如果检测到命令结束符(以换行作为命令结束)
    {
      cnt = 0;//复位计数器
      iscomend0 = 1;//命令接收完毕
    }
}

//串口1接收中断服务函数
void UART1_Receive_ISR(void)
{
    static uint8_t cnt = 0;
    UCA1IFG  &=~UCRXIFG;//清除中断标志位
    rxbuff1[cnt++] = UCA1RXBUF;//保存命令
    cnt %= UART1_RX_LEN;//防止cnt大于UART_RX_LEN，导致缓冲区溢出
    if( rxbuff1[cnt - 1] == '\n')//如果检测到命令结束符(以换行作为命令结束)
    {
      cnt = 0;//复位计数器
      iscomend1 = 1;//命令接收完毕
    }
}



