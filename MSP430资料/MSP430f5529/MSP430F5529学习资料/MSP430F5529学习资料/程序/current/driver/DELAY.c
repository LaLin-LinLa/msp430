/*
 * DELAY.c
 *
 *  Created on: 2021��7��30��
 *      Author: hp
 */

#include "DELAY.h"

void delay(int ms)        //��ʱ����
{
    int i,j;
    for(i=0;i<ms;i++)
    for(j=0;j<240;j++);
}


