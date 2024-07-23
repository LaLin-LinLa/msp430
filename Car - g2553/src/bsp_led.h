#ifndef BSP_LED_H_
#define BSP_LED_H_
#include <msp430.h>

void bsp_led_init(void);
void led_set(char ledx);
void led_rest(char ledx);
void led_toggle(char ledx);

#endif /* BSP_BSP_LED_H_ */
