/*
 * PWM.c
 *
 *  Created on: 2021年7月30日
 *      Author: hp
 */

#include "PWM.h"

void PWM0_Config(void)
{
    WDTCTL = WDTPW + WDTHOLD;  // 关闭看门狗
    P1DIR |=BIT2;              // 设置 P1.2为输出
    P1SEL |=BIT2;              // 设置 P1.2为TA0.2输出,外设功能模式
    P1DS |=BIT2;               //全力驱动，否则可能无法驱动电机
    TA0CCR0 = PWMPeriod;       // 设置PWM 周期
    TA0CCTL1 = OUTMOD_7;       // 设置PWM 输出模式为：7 - PWM复位/置位模式，即输出电平在TAR的值等于CCR2时复位为0，当TAR的值等于CCR0时置位为1，改变CCR2，从而产生PWM。其实模式2也可以
    TA0CTL= TASSEL_2 +MC_1;    // 设置TIMERA的时钟源为SMCLK, 计数模式为up,到CCR0再自动从0开始计数
    TA0CCR1=0;
}
int PWM0_State(unsigned int n)
{
    unsigned int v = 0;
    v = (n*PWMPeriod)/100;
    TA0CCR1=v;
    return 0;
}
void PWM1_Config(void)
{
    WDTCTL = WDTPW + WDTHOLD;  // 关闭看门狗
    P1DIR |=BIT3;              // 设置 P1.3为输出
    P1SEL |=BIT3;              // 设置 P1.3为TA0.2输出
    P1DS |=BIT3;               //全力驱动，否则可能无法驱动电机
    TA0CCR0 = PWMPeriod;       // 设置PWM 周期
    TA0CCTL2 = OUTMOD_7;       // 设置PWM 输出模式为：7 - PWM复位/置位模式，即输出电平在TAR的值等于CCR2时复位为0，当TAR的值等于CCR0时置位为1，改变CCR2，从而产生PWM。其实模式2也可以
    TA0CTL= TASSEL_2 +MC_1;    // 设置TIMERA的时钟源为SMCLK, 计数模式为up,到CCR0再自动从0开始计数
    TA0CCR2=0;
}
int PWM1_State(unsigned int n)
{
    unsigned int v;
    v = (n*PWMPeriod)/100;
    TA0CCR2=v;
    return 0;
}
void PWM2_Config(void)
{
    WDTCTL = WDTPW + WDTHOLD;  // 关闭看门狗
    P1DIR |=BIT4;              // 设置 P1.4为输出
    P1SEL |=BIT4;              // 设置 P1.4为TA0.2输出
    P1DS |=BIT4;               //全力驱动，否则可能无法驱动电机
    TA0CCR0 = PWMPeriod;       // 设置PWM 周期
    TA0CCTL3 = OUTMOD_7;       // 设置PWM 输出模式为：7 - PWM复位/置位模式，即输出电平在TAR的值等于CCR2时复位为0，当TAR的值等于CCR0时置位为1，改变CCR2，从而产生PWM。其实模式2也可以
    TA0CTL= TASSEL_2 +MC_1;    // 设置TIMERA的时钟源为SMCLK, 计数模式为up,到CCR0再自动从0开始计数
    TA0CCR3=0;
}
int PWM2_State(unsigned int n)
{
    unsigned int v = 0;
    v = (n*PWMPeriod)/100;
    TA0CCR3=v;
    return 0;
}
void PWM3_Config(void)
{
    WDTCTL = WDTPW + WDTHOLD;  // 关闭看门狗
    P1DIR |=BIT5;              // 设置 P1.5为输出
    P1SEL |=BIT5;              // 设置 P1.5为TA0.2输出
    P1DS |=BIT5;               //全力驱动，否则可能无法驱动电机
    TA0CCR0 = PWMPeriod;       // 设置PWM 周期
    TA0CCTL4 = OUTMOD_7;       // 设置PWM 输出模式为：7 - PWM复位/置位模式，即输出电平在TAR的值等于CCR2时复位为0，当TAR的值等于CCR0时置位为1，改变CCR2，从而产生PWM。其实模式2也可以
    TA0CTL= TASSEL_2 +MC_1;    // 设置TIMERA的时钟源为SMCLK, 计数模式为up,到CCR0再自动从0开始计数
    TA0CCR4=0;
}
int PWM3_State(unsigned int n)
{
    unsigned int v = 0;
    v = (n*PWMPeriod)/100;
    TA0CCR4=v;
    return 0;
}




