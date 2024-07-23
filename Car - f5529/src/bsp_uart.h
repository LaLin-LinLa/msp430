#ifndef _BSP_UART_H_
#define _BSP_UART_H_
#include "main.h"


#define UART0_RX_LEN 20
#define UART1_RX_LEN 20


extern uint8_t rxbuff0[UART0_RX_LEN];
extern uint8_t iscomend0;
void bsp_uart0_init(void);
void uart0_printf(const char *fmt,...);
void UART0SendString(char *pbuff);
extern void UART0_Receive_ISR(void);

extern uint8_t rxbuff1[UART1_RX_LEN];
extern uint8_t iscomend1;
void bsp_uart1_init(void);
void uart1_printf(const char *fmt,...);
void UART1SendString(char *pbuff);
extern void UART1_Receive_ISR(void);


#endif /* SRC_BSP_UART_H_ */
