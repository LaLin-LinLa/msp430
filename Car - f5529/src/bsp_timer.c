#include "bsp_timer.h"
volatile uint32_t timer_cnt = 0;
//MSP430F5529共有两类共4个定时器，分别是 Timer_A 定时器3个和
//Timer_B 定时器1个，按照每个寄存器配备的捕获/比较器的个数分别命名为 Timer0_A
//（内有5个捕获比较器）、Timer1_A（3个）、Timer2_A（3个）、Timer0_B（7个）

//设定中断频率为40Hz，即状态机控制周期为0.025s
void bsp_timer_init(void)
{
    TA1CTL|=TASSEL_2+MC_1+TAIE+TACLR;   //选择SMCLK为时钟源，递增模式(TA0R会从0递增到TA0CCR0，然后回到0，重复这个过程)
    TA1CTL|=ID_2;                       //4分频
    TA1EX0|=TAIDEX_4;                   //5分频
                                        //共20分频，分频后为1.25MHz
    TA1CCR0 = 62500;                    //最大0xFFFF(65536)   设定20Hz，0.05s 即TA0CCR0 = 0.05*1.25M = 62500


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
    * @brief  获取定时器时间(s)
    * @param  None
    * @retval 实时时间
    */
uint32_t Get_Tick(void)
{
    uint16_t cnt_now = TA1R;
    cnt_now /= 62500;
    return ((cnt_now + timer_cnt)*0.05);
}

