/*
 * motor.c
 *
 *  Created on: 2021年8月3日
 *      Author: hp
 */
#include "GPIO.h"
#include "PWM.h"


void motor_init(void)
{
    OUTPUT_GPIO_Config(6, 1);   //A2
    OUTPUT_GPIO_Config(6, 2);   //A1
    OUTPUT_GPIO_Config(3, 5);   //B1
    OUTPUT_GPIO_Config(3, 6);   //B2
    OUTPUT_GPIO_Config(3, 7);   //STBY
    OUTPUT_GPIO_State(3, 7, 1); //STBY高电平
    PWM0_Config();              //PWA
    PWM1_Config();              //PWB
}


void motor_PWM(int x, int y)   //x是右轮PWM值，y是左轮PWM值
{
    PWM0_State(x);             //A,右轮PWM
    PWM1_State(y);             //B,左轮PWM
}




