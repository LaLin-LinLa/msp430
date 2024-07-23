/*
 * Black_Init.c
 *
 *  Created on: 2020��10��8��
 *      Author: PC
 */

#include "Black_All.h"


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
    /* �����˿ڳ�ʼ�� */
    KEY0_GPIO_Config();
    #endif
    #if KEY1_Switch
    /* �����˿ڳ�ʼ�� */
    KEY1_GPIO_Config();
    #endif
    #if USART0_switch
    /* ���� 1 ��ʼ�� */
    USART0_Config();
    #endif
    #if USART1_switch
    /* ���� 2 ��ʼ�� */
    USART1_Config();
    #endif
    #if PWM0_switch
    /* ��� PWM ��ʼ�� */
    PWM0_Config();
    #endif
    #if PWM1_switch
    /* ��� PWM ��ʼ�� */
    PWM1_Config();
    #endif
    #if PWM2_switch
    /* ��� PWM ��ʼ�� */
    PWM2_Config();
    #endif
    #if PWM3_switch
    /* ��� PWM ��ʼ�� */
    PWM3_Config();
    #endif
    #if OLED_switch
    /* ��� PWM ��ʼ�� */
    OLED_Init();
    #endif
}
