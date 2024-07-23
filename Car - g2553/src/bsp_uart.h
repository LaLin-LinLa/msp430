#ifndef BSP_UART_H_
#define BSP_UART_H_
#include <msp430.h>
#include "stdint.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#define UART_RX_LEN 5

extern uint8_t mode;
extern uint8_t rxbuff[UART_RX_LEN];
extern uint8_t iscomend;
void bsp_uart_init(void);
void uart_printf(const char *fmt,...);
void UARTSendString(char *pbuff);
extern void UART_Receive_ISR(void);

#endif
