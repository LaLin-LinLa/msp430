#include "bsp_key.h"

/**
  * @brief  按键初始化
  * @retval None
  */
void bsp_key_init(void)
{
    /*初始化按键所在IO口P1.3为输入*/
    P1DIR &= ~BIT3;
    /*使能P1.3口的上拉电阻*/
    P1REN |= BIT3;
    P1OUT |= BIT3;
}

/**
  * @brief  按键扫描
  * @param  mode:0,不支持连续按;1,支持连续按;
  * @retval 1：按下 0：没按下
  */
char key_scan(char mode)
{
   static char key_up=1;//按键按松开标志
   if(mode)key_up=1;  //支持连按
   if(key_up&&((P1IN & BIT3)==0))
   {
       __delay_cycles(50000);  //去抖动
       key_up=0;
       if(((P1IN & BIT3)==0))return 1;
   }else if(P1IN & BIT3) key_up = 1;
   return 0;
}
