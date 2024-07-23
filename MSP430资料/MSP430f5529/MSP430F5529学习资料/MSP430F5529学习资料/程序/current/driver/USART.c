/*
 * USART.c
 *
 *  Created on: 2021年7月30日
 *      Author: hp
 */

#include "USART.h"
#include "DELAY.h"
#include "Define.h"

/*IO口的串口*/
void USART0_Config(void)
{
    //串口初始化
     P3SEL    |=  BIT3+BIT4 ;                        // P3.3,4 = USCI_A1 TXD/RXD
     UCA0CTL1 |=  UCSWRST;                      // **Put state machine in reset**
     UCA0CTL1 |=  UCSSEL_1;                     // ACLK
     UCA0BR0   =  0x03;                         // 32768Hz 9600 波特率为9600
     UCA0BR1   =  0x00;                             // 32768Hz 9600
     UCA0MCTL |=  UCBRS_3 + UCBRF_0;           // Modulation UCBRSx=1, UCBRFx=0
     UCA0CTL1 &= ~UCSWRST;                   // **Initialize USCI state machine**
     UCA0IE   |=  UCRXIE;                       // Enable USCI_A1 RX interrupt 使能中断
}

/*USB串口*/
void USART1_Config(void)
{
    //串口初始化
     P4SEL    |=  BIT4+BIT5 ;                        // P54.4,5 = USCI_A1 TXD/RXD
     UCA1CTL1 |=  UCSWRST;                      // **Put state machine in reset**
     UCA1CTL1 |=  UCSSEL_1;                     // ACLK
     UCA1BR0   =  0x03;                         // 32768Hz 9600 波特率为9600
     UCA1BR1   =  0x00;                             // 32768Hz 9600
     UCA1MCTL |=  UCBRS_3 + UCBRF_0;           // Modulation UCBRSx=1, UCBRFx=0
     UCA1CTL1 &= ~UCSWRST;                   // **Initialize USCI state machine**
     UCA1IE   |=  UCRXIE;                       // Enable USCI_A1 RX interrupt 使能中断
}

void send0_buf(unsigned char *ptr)    //发送字符串
{
    while(*ptr != '\0')
    {
        while(!(UCA0IFG & UCTXIFG));
        UCA0TXBUF = *ptr;
        ptr++;
        delay(10);
    }
}
void send1_buf(unsigned char *ptr)    //发送字符串
{
    while(*ptr != '\0')
    {
        while(!(UCA1IFG & UCTXIFG));
        UCA1TXBUF = *ptr;
        ptr++;
        delay(10);
    }
}

#if USART0_switch
#pragma vector = USCI_A0_VECTOR
__interrupt void USCI_A0_ISR()
{
    switch(_even_in_range(UCA0IV,4))
    {
        case 0:break;                             // Vector 0 - No interrupt
        case 2:                                   // Vector 2 - RXIFG
        UCA0TXBUF = UCA0RXBUF;                // 发送接收到的数据
        break;
        case 4:break;                             // Vector 4 - TXIFG
        default: break;
    }
}
#endif

#if USART1_switch
#pragma vector = USCI_A1_VECTOR
__interrupt void USCI_A1_ISR()
{
    switch(_even_in_range(UCA1IV,4))
    {
        case 0:break;                             // Vector 0 - No interrupt
        case 2:                                   // Vector 2 - RXIFG
        UCA1TXBUF = UCA1RXBUF;                // 发送接收到的数据
        break;
        case 4:break;                             // Vector 4 - TXIFG
        default: break;
    }
}
#endif



