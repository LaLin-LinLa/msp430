/*
 * main.c
 *
 *  Created on: 2021��7��30��
 *      Author: hp
 */

#include "All.h"
#include "motor.h"



void main(void)
{
     Init();
    //IN_Config(1,1);  //�ж�
    //IN_Config(2,1);  //�ж�
    LED0_STATE(0);//����led0 ��
    LED1_STATE(0);//����led1 ��
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
//�����ж�ʾ��
#pragma vector = PORT1_VECTOR
__interrupt void P1_ISR()
{
    if(P1IFG & BIT1)
    {
        while((P1IN & BIT1)==0);
        led1_flag++;
        if(led1_flag > 4)
            led1_flag = 4;
        send1_buf("����1����\r\n");
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
        send1_buf("����2����\r\n");
    }
    P2IFG &=~ BIT1;
}
*/
#if TIME_A1
/*��ʱ��1���жϺ����ص�*/
#pragma vector=TIMER1_A0_VECTOR
__interrupt void TIMER1_A0_ISR(void)
{
    LED0_STATE(2);
    LED1_STATE(2);
}
#endif
#if TIME_A2
/*��ʱ��2���жϺ����ص�*/
#pragma vector=TIMER2_A0_VECTOR
__interrupt void TIMER2_A0_ISR(void)
{
    LED0_STATE(2);
    LED1_STATE(2);
    send1_buf("������Ϣ\r\n");
}
#endif

