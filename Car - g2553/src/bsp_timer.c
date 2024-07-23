#include "bsp_timer.h"

volatile uint32_t timer_cnt = 0;

void bsp_timer_init(void)
{
  /*=======================Timer_Config_Start=======================*/
  /*设置时钟源为SMCLK*/
    TA0CTL |= TASSEL1;
    /*设置工作模式为Up Mode*/
    TA0CTL |= MC_1;//Up Mode模式下，16bit(65536) Timer计数器 TAR会从0递增到TACCR0，然后回到0，重复这个过程
    /*设置定时间隔*/
    TA0CCR0 = 49999;//16/8MHz 计 50000个数，1/2MHz * 50000 40Hz 0.025s           
    /*开启TAIFG中断*/
    TA0CTL |= TAIE;
  /*=======================Timer_Config_END=======================*/ 

}

/**
	* @brief  更新定时器时间
	* @not    将此函数加入定时器中断服务函数中
	* @param  None
	* @retval None
	*/
void Update_Tick(void)
{
    timer_cnt++;
}

/**
    * @brief  获取定时器时间
    * @param  None
    * @retval 实时时间
    */
uint32_t Get_Tick(void)
{
    return TAR + timer_cnt * 0x1388;
}


