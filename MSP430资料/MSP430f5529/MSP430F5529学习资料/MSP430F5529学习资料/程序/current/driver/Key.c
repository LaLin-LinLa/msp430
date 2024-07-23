/*
 * Key.c
 *
 *  Created on: 2021年7月30日
 *      Author: hp
 */

#include "Key.h"
#include "DELAY.h"
void KEY0_GPIO_Config(void)
{
    P1DIR &=~ BIT1;
    P1REN |=  BIT1;
    P1OUT |=  BIT1;    //上拉
}
void KEY1_GPIO_Config(void)
{
    P2DIR &=~ BIT1;
    P2REN |=  BIT1;
    P2OUT |=  BIT1;
}
int KEY0_STATE()
{
    if(P1IN & BIT1)
    {
      delay(12); // 延时消抖
      if(P1IN & BIT1)
      {
          return 0;
      }
    }
    return 1;
}

int KEY1_STATE()
{
    if(P2IN & BIT1)
    {
      delay(12);
      if(P2IN & BIT1)
      {
          return 0;
      }
    }
    return 1;
}


