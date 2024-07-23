/*
 * Init.c
 *
 *  Created on: 2021年7月30日
 *      Author: hp
 */

#include <All.h>

void Init(void)
{
    WDTCTL = WDTPW + WDTHOLD;
    #if LED0_Switch
    LED0_GPIO_Config();
    #endif
    #if LED1_Switch
    LED1_GPIO_Config();
    #endif
    #if KEY0_Switch
    /* 按键端口初始化 */
    KEY0_GPIO_Config();
    #endif
    #if KEY1_Switch
    /* 按键端口初始化 */
    KEY1_GPIO_Config();
    #endif
    #if TIME_A1
    /* 定时器A1初始化 */
    TimeA1_Config();
    #endif
    #if TIME_A2
    /* 定时器A1初始化 */
    TimeA2_Config();
    #endif
    #if USART0_switch
    /* 串口 1 初始化 */
    USART0_Config();
    #endif
    #if USART1_switch
    /* 串口 2 初始化 */
    USART1_Config();
    #endif
    #if PWM0_switch
    /* 电机 PWM 初始化 */
    PWM0_Config();
    #endif
    #if PWM1_switch
    /* 电机 PWM 初始化 */
    PWM1_Config();
    #endif
    #if PWM2_switch
    /* 电机 PWM 初始化 */
    PWM2_Config();
    #endif
    #if PWM3_switch
    /* 电机 PWM 初始化 */
    PWM3_Config();
    #endif
    #if OLED_switch
    /* 电机 PWM 初始化 */
    OLED_Init();
    #endif
}


