/*
 * Interrupt.c
 *
 *  Created on: 2021年7月30日
 *      Author: hp
 */

#include "Interrupt.h"

void IN_Config(unsigned int x,unsigned int y)
{
    if(x == 1)
    {
        if(y == 1)
        {
            P2IE  |= BIT1;
            P2IES |= BIT1; //下降沿
            P2IFG &= ~ BIT1;
            P2REN |= BIT1;
            P2OUT |= BIT1;
            _EINT();
        }
        else
        {
            P2IE  |= BIT1;
            P2IES &= ~ BIT1;//上降沿
            P2IFG &= ~ BIT1;
            P2REN |= BIT1;
            P2OUT |= BIT1;
            _EINT();
        }
    }
    else
    {
        if(y == 1)
        {
            P1IE |= BIT1;
            P1IES |= BIT1;
            P1IFG &= ~ BIT1;
            P1REN |= BIT1;
            P1OUT |= BIT1;
            _EINT();
        }
        else
        {
            P1IE  |= BIT1;
            P1IES &= ~ BIT1;
            P1IFG &= ~ BIT1;
            P1REN |= BIT1;
            P1OUT |= BIT1;
            _EINT();
        }
    }
}

/*
//串口中断函数示例
#pragma vector = USCI_A1_VECTOR
__interrupt void USCI_ISR()
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

 //中断配置函数示例
#pragma vector = PORT2_VECTOR
__interrupt void P2_ISR()
{
    if(P2IFG & BIT1)
    {
        //程序
    }
    else
    {

    }
    P2IFG &=~ BIT1;
}

*/


