#ifndef BSP_TIMER_H_
#define BSP_TIMER_H_
#include "main.h"

void bsp_timer_init(void);
uint32_t Get_Tick(void);
extern void Update_Tick(void);

#endif /* SRC_BSP_TIMER_H_ */
