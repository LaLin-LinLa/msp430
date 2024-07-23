/*
 * PWM.h
 *
 *  Created on: 2021年7月30日
 *      Author: hp
 */

#ifndef DRIVER_PWM_H_
#define DRIVER_PWM_H_

#include <msp430.h>

#define PWMPeriod  100   //PWM周期
void PWM0_Config(void);
void PWM1_Config(void);
void PWM2_Config(void);
void PWM3_Config(void);
int PWM0_State(unsigned int n);
int PWM1_State(unsigned int n);
int PWM2_State(unsigned int n);
int PWM3_State(unsigned int n);
void time0_Config(void);


#endif /* DRIVER_PWM_H_ */
