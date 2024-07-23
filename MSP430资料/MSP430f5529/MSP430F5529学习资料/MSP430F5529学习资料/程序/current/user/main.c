/*
 * main.c
 *
 *  Created on: 2021年7月30日
 *      Author: hp
 */

#include "All.h"
#include "motor.h"



void main(void)
{
     Init();
    //IN_Config(1,1);  //中断
    //IN_Config(2,1);  //中断
    LED0_STATE(0);//操作led0 灭
    LED1_STATE(0);//操作led1 灭
    //OLED_Clear();
    motor_init();
    PWM1_State(40);
        while(1)
        {
            delay(100);
            left_motor_head;
            //OLED_ShowString(39,0,"I E LAB",8);

        }
}



/*
//按键中断示例
#pragma vector = PORT1_VECTOR
__interrupt void P1_ISR()
{
    if(P1IFG & BIT1)
    {
        while((P1IN & BIT1)==0);
        led1_flag++;
        if(led1_flag > 4)
            led1_flag = 4;
        send1_buf("按键1按下\r\n");
    }
    P1IFG &=~ BIT1;
}
#pragma vector = PORT2_VECTOR
__interrupt void P2_ISR()
{
    if(P2IFG & BIT1)
    {
        while((P2IN & BIT1)==0);
        led1_flag--;
        if(led1_flag < 0)
            led1_flag = 0;
        send1_buf("按键2按下\r\n");
    }
    P2IFG &=~ BIT1;
}
*/
#if TIME_A1
/*定时器1的中断函数回调*/
#pragma vector=TIMER1_A0_VECTOR
__interrupt void TIMER1_A0_ISR(void)
{
    LED0_STATE(2);
    LED1_STATE(2);
}
#endif
#if TIME_A2
/*定时器2的中断函数回调*/
#pragma vector=TIMER2_A0_VECTOR
__interrupt void TIMER2_A0_ISR(void)
{
    LED0_STATE(2);
    LED1_STATE(2);
    send1_buf("发送消息\r\n");
}
#endif

