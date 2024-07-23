/*
 * LED.c
 *
 *  Created on: 2021年7月30日
 *      Author: hp
 */

#include "LED.h"

void LED0_GPIO_Config(void)
{
     P1DIR|=BIT0;             //P1.0-P1.5方向为输出，BITX的定义在msp430.h
     P1OUT&=~BIT0;
}

void LED1_GPIO_Config(void)
{
     P4DIR|=BIT7;             //P1.0-P1.5方向为输出，BITX的定义在msp430.h
     P4OUT&=~BIT7;
}

void LED0_STATE(unsigned int n)
{
    switch(n)
    {
      case 2:P1OUT ^= BIT0;break;      //输出电平翻转
      case 1:P1OUT |= BIT0;break;      //输出高电平
      case 0:P1OUT &=~BIT0;break;      //输出低电平
      default:P1OUT&=~BIT0;break;
    }
}

void LED1_STATE(unsigned int n)
{
    switch(n)
    {
      case 2:P4OUT ^= BIT7;break;
      case 1:P4OUT |= BIT7;break;
      case 0:P4OUT &=~BIT7;break;
      default:P4OUT&=~BIT7;break;
    }
}


