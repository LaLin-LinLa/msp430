#include "bsp_clks.h"

/**
  * @brief  �ڲ���������(DCO)��ʼ��
  * @param  ���õ���ʱ��Ƶ��1/8/12/16
  * @retval None
  */
void bsp_clks_init(void)
{
    /*ϵͳ�ϵ�Ĭ��MCLK��ʱ��ԴΪDCO��ע��G2553��֧���ⲿ���پ���ܳ*/
    /*����MCLKƵ��*/
    DCOCTL = CALDCO_16MHZ;
    BCSCTL1 = CALBC1_16MHZ;
    /*����SMCLK��ʱ��ԴΪDCO(ϵͳһ���ϵ�Ĭ��ѡ��DCO)*/
    BCSCTL2 &= ~SELS;
    /*SMCLK�ķ�Ƶϵ����Ϊ8*/
    BCSCTL2 |= (DIVS0 | DIVS1);


}



