/*
 * GPIO.h
 *
 *  Created on: 2021Äê7ÔÂ30ÈÕ
 *      Author: hp
 */

#ifndef DRIVER_GPIO_H_
#define DRIVER_GPIO_H_

#include <msp430.h>

void OUTPUT_GPIO_Config(unsigned int x,unsigned int y);
void OUTPUT_GPIO_State(unsigned int x,unsigned int y,unsigned int z);
void INPUT_GPIO_Config(unsigned int x,unsigned int y);



#endif /* DRIVER_GPIO_H_ */
