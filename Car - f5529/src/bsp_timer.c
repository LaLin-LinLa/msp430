#include "bsp_timer.h"
volatile uint32_t timer_cnt = 0;
//MSP430F5529�������๲4����ʱ�����ֱ��� Timer_A ��ʱ��3����
//Timer_B ��ʱ��1��������ÿ���Ĵ����䱸�Ĳ���/�Ƚ����ĸ����ֱ�����Ϊ Timer0_A
//������5������Ƚ�������Timer1_A��3������Timer2_A��3������Timer0_B��7����

//�趨�ж�Ƶ��Ϊ40Hz����״̬����������Ϊ0.025s
void bsp_timer_init(void)
{
    TA1CTL|=TASSEL_2+MC_1+TAIE+TACLR;   //ѡ��SMCLKΪʱ��Դ������ģʽ(TA0R���0������TA0CCR0��Ȼ��ص�0���ظ��������)
    TA1CTL|=ID_2;                       //4��Ƶ
    TA1EX0|=TAIDEX_4;                   //5��Ƶ
                                        //��20��Ƶ����Ƶ��Ϊ1.25MHz
    TA1CCR0 = 62500;                    //���0xFFFF(65536)   �趨20Hz��0.05s ��TA0CCR0 = 0.05*1.25M = 62500


}

/**
    * @brief  ���¶�ʱ��ʱ��
    * @not    ���˺������붨ʱ���жϷ�������
    * @param  None
    * @retval None
    */
void Update_Tick(void)
{
    timer_cnt++;
}

/**
    * @brief  ��ȡ��ʱ��ʱ��(s)
    * @param  None
    * @retval ʵʱʱ��
    */
uint32_t Get_Tick(void)
{
    uint16_t cnt_now = TA1R;
    cnt_now /= 62500;
    return ((cnt_now + timer_cnt)*0.05);
}

