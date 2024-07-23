#include "bsp_timer.h"

volatile uint32_t timer_cnt = 0;

void bsp_timer_init(void)
{
  /*=======================Timer_Config_Start=======================*/
  /*����ʱ��ԴΪSMCLK*/
    TA0CTL |= TASSEL1;
    /*���ù���ģʽΪUp Mode*/
    TA0CTL |= MC_1;//Up Modeģʽ�£�16bit(65536) Timer������ TAR���0������TACCR0��Ȼ��ص�0���ظ��������
    /*���ö�ʱ���*/
    TA0CCR0 = 49999;//16/8MHz �� 50000������1/2MHz * 50000 40Hz 0.025s           
    /*����TAIFG�ж�*/
    TA0CTL |= TAIE;
  /*=======================Timer_Config_END=======================*/ 

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
    * @brief  ��ȡ��ʱ��ʱ��
    * @param  None
    * @retval ʵʱʱ��
    */
uint32_t Get_Tick(void)
{
    return TAR + timer_cnt * 0x1388;
}


