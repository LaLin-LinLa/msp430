/*
 * LED.h
 *
 *  Created on: 2021Äê7ÔÂ30ÈÕ
 *      Author: hp
 */

#ifndef DRIVER_LED_H_
#define DRIVER_LED_H_

#include <msp430.h>

void LED0_GPIO_Config(void);
void LED1_GPIO_Config(void);
void LED0_STATE(unsigned int n);
void LED1_STATE(unsigned int n);



#endif /* DRIVER_LED_H_ */
