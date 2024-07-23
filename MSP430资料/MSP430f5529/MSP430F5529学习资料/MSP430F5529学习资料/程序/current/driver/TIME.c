#include "TIME.h"




void TimeA1_Config()
{
    WDTCTL = WDTPW + WDTHOLD;           //关闭看门狗
    TA1CCR0 = 65000;
    TA1CCTL0 = CCIE;                    // CCR0中断允许
    TA1CTL= TASSEL_2+TAIE+TACLR+MC_1;   //使用SMCLK时钟，开启中断并清零，递增模式;
    _EINT();    //开启总中断
}

void TimeA2_Config()
{
    WDTCTL = WDTPW + WDTHOLD;           //关闭看门狗
    TA2CCR0 = 65000;
    TA2CCTL0 = CCIE;                    // CCR0中断允许
    TA2CTL= TASSEL_2+TAIE+TACLR+MC_1;   //使用SMCLK时钟，开启中断并清零，递增模式;
    _EINT();    //开启总中断
}





