/*
 * USART.h
 *
 *  Created on: 2021��7��30��
 *      Author: hp
 */

#ifndef DRIVER_USART_H_
#define DRIVER_USART_H_

#include <msp430.h>

void USART0_Config(void);
void USART1_Config(void);
void send0_buf(unsigned char *ptr);    //�����ַ���
void send1_buf(unsigned char *ptr);    //�����ַ���



#endif /* DRIVER_USART_H_ */
