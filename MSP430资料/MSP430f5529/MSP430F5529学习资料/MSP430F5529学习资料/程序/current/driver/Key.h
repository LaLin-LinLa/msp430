/*
 * Key.h
 *
 *  Created on: 2021Äê7ÔÂ30ÈÕ
 *      Author: hp
 */

#ifndef DRIVER_KEY_H_
#define DRIVER_KEY_H_

#include <msp430.h>

void KEY0_GPIO_Config(void);
void KEY1_GPIO_Config(void);
int KEY0_STATE();
int KEY1_STATE();



#endif /* DRIVER_KEY_H_ */
