#include "bsp_key.h"

/**
  * @brief  按键初始化
  * @retval None
  */
void bsp_key_init(void)
{
    /*初始化按键所在IO口为输入*/
    P1DIR &= ~BIT1; //S2
    P2DIR &= ~BIT1; //S1
    /*使能P1.1口的上拉电阻*/
    P1REN |= BIT1;
    P1OUT |= BIT1;
    /*使能P2.1口的上拉电阻*/
    P2REN |= BIT1;
    P2OUT |= BIT1;

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
   if(key_up&&((P1IN & BIT1)==0||(P2IN & BIT1)==0))
   {
       __delay_us(50);  //去抖动
       key_up=0;
       if(((P2IN & BIT1)==0))return 1;
       else if(((P1IN & BIT1)==0))return 2;
   }else if((P2IN & BIT1)&&(P1IN & BIT1)) key_up = 1;
   return 0;
}
