/*
 * LED.c
 *
 *  Created on: 2021��7��30��
 *      Author: hp
 */

#include "LED.h"

void LED0_GPIO_Config(void)
{
     P1DIR|=BIT0;             //P1.0-P1.5����Ϊ�����BITX�Ķ�����msp430.h
     P1OUT&=~BIT0;
}

void LED1_GPIO_Config(void)
{
     P4DIR|=BIT7;             //P1.0-P1.5����Ϊ�����BITX�Ķ�����msp430.h
     P4OUT&=~BIT7;
}

void LED0_STATE(unsigned int n)
{
    switch(n)
    {
      case 2:P1OUT ^= BIT0;break;      //�����ƽ��ת
      case 1:P1OUT |= BIT0;break;      //����ߵ�ƽ
      case 0:P1OUT &=~BIT0;break;      //����͵�ƽ
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


