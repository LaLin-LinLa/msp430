#include "bsp_key.h"

/**
  * @brief  ������ʼ��
  * @retval None
  */
void bsp_key_init(void)
{
    /*��ʼ����������IO��P1.3Ϊ����*/
    P1DIR &= ~BIT3;
    /*ʹ��P1.3�ڵ���������*/
    P1REN |= BIT3;
    P1OUT |= BIT3;
}

/**
  * @brief  ����ɨ��
  * @param  mode:0,��֧��������;1,֧��������;
  * @retval 1������ 0��û����
  */
char key_scan(char mode)
{
   static char key_up=1;//�������ɿ���־
   if(mode)key_up=1;  //֧������
   if(key_up&&((P1IN & BIT3)==0))
   {
       __delay_cycles(50000);  //ȥ����
       key_up=0;
       if(((P1IN & BIT3)==0))return 1;
   }else if(P1IN & BIT3) key_up = 1;
   return 0;
}
