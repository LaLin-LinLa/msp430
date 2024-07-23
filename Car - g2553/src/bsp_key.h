#ifndef BSP_KEY_H_
#define BSP_KEY_H_
#include <msp430.h>
#include "stdint.h"

void bsp_key_init(void);
char key_scan(char mode);

#endif
