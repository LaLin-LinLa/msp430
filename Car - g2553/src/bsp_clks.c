#include "bsp_clks.h"

/**
  * @brief  内部数控振荡器(DCO)初始化
  * @param  配置的主时钟频率1/8/12/16
  * @retval None
  */
void bsp_clks_init(void)
{
    /*系统上电默认MCLK的时钟源为DCO，注意G2553不支持外部高速晶振艹*/
    /*设置MCLK频率*/
    DCOCTL = CALDCO_16MHZ;
    BCSCTL1 = CALBC1_16MHZ;
    /*配置SMCLK的时钟源为DCO(系统一般上电默认选择DCO)*/
    BCSCTL2 &= ~SELS;
    /*SMCLK的分频系数置为8*/
    BCSCTL2 |= (DIVS0 | DIVS1);


}



