#ifndef _MAIN_H_
#define _MAIN_H_
#include <msp430.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#define CPU_F ((double)25000000)
#define __delay_us(x) __delay_cycles((long)(CPU_F*(double)x/1000000.0))//重新定义延时函数
#define __delay_ms(x) __delay_cycles((long)(CPU_F*(double)x/1000.0))

//#define M_PI                    (3.14159265358f)
#define M_2PI                    (6.28318530716f)
#define ONE_BY_SQRT3            (0.57735026919f)
#define TWO_BY_SQRT3            (2.0f * 0.57735026919f)
#define SQRT3_BY_2                (0.86602540378f)

#define u32 unsigned int
#define u16 unsigned short
#define u8 unsigned char

#endif /* SRC_MAIN_H_ */
