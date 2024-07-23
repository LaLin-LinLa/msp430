/*
 * USART.h
 *
 *  Created on: 2021年7月30日
 *      Author: hp
 */

#ifndef DRIVER_USART_H_
#define DRIVER_USART_H_

#include <msp430.h>

void USART0_Config(void);
void USART1_Config(void);
void send0_buf(unsigned char *ptr);    //发送字符串
void send1_buf(unsigned char *ptr);    //发送字符串



#endif /* DRIVER_USART_H_ */
