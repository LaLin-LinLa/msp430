/*
 * DELAY.c
 *
 *  Created on: 2021年7月30日
 *      Author: hp
 */

#include "DELAY.h"

void delay(int ms)        //延时函数
{
    int i,j;
    for(i=0;i<ms;i++)
    for(j=0;j<240;j++);
}


