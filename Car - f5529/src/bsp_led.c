#include "bsp_led.h"

void bsp_led_init(void)
{
  /*初始化LED所在IO口为输出*/
    P1DIR |= BIT1;  //LED1
    P4DIR |= BIT7;  //LED2
    /*初始化LED所在IO口为低电平，LED2初始状态为灭*/
    P1OUT &= ~BIT1; //LED1
    P4OUT &= ~BIT7; //LED2
}

void LED1(char mode)
{
  switch (mode)
  {
    case 0:
      P1OUT &= ~BIT1;//熄灭LED1
    break;
    case 1:
      P1OUT |= BIT1;//点亮LED1
    break;
    case 2:
      P1OUT ^= BIT1;//翻转LED1
    break;
  default:
    break;
  }
}

void LED2(char mode)
{
  switch (mode)
  {
    case 0:
      P4OUT &= ~BIT7;//熄灭LED2
    break;
    case 1:
      P4OUT |= BIT7;//点亮LED2
    break;
    case 2:
      P4OUT ^= BIT7;//翻转LED2
    break;
  default:
    break;
  }
}
