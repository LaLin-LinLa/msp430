#include "bsp_led.h"

/**
  * @brief  LED初始化
  * @retval None
  */
void bsp_led_init(void)
{
    /*初始化LED所在IO口P1.6为输出*/
    P1DIR |= BIT0;  //LED_R
    P1DIR |= BIT6;  //LED_G
    /*初始化LED1所在IO口P1.0为低电平，LED1初始状态为灭*/
    P1OUT &= ~BIT0;
    /*初始化LED2所在IO口P1.6为低电平，LED2初始状态为灭*/
    P1OUT &= ~BIT6;
}

//点亮LED
void led_set(char ledx)
{
    if(ledx == 1)
        P1OUT |= BIT0;//点亮LED1
    else if(ledx == 2)
        P1OUT |= BIT6;//点亮LED2
}

//熄灭LED
void led_rest(char ledx)
{
    if(ledx == 1)
        P1OUT &= ~BIT0;//熄灭LED1
    else if(ledx == 2)
        P1OUT &= ~BIT6;//熄灭LED2
}

//翻转LED
void led_toggle(char ledx)
{
    if(ledx == 1)
        P1OUT ^= ~BIT0;//LED1
    else if(ledx == 2)
        P1OUT ^= ~BIT6;//LED2
    else if(ledx == 3){
        P1OUT ^= ~BIT0;P1OUT ^= ~BIT6;
    }
}



