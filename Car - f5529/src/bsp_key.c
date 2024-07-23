#include "bsp_key.h"

/**
  * @brief  ������ʼ��
  * @retval None
  */
void bsp_key_init(void)
{
    /*��ʼ����������IO��Ϊ����*/
    P1DIR &= ~BIT1; //S2
    P2DIR &= ~BIT1; //S1
    /*ʹ��P1.1�ڵ���������*/
    P1REN |= BIT1;
    P1OUT |= BIT1;
    /*ʹ��P2.1�ڵ���������*/
    P2REN |= BIT1;
    P2OUT |= BIT1;

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
   if(key_up&&((P1IN & BIT1)==0||(P2IN & BIT1)==0))
   {
       __delay_us(50);  //ȥ����
       key_up=0;
       if(((P2IN & BIT1)==0))return 1;
       else if(((P1IN & BIT1)==0))return 2;
   }else if((P2IN & BIT1)&&(P1IN & BIT1)) key_up = 1;
   return 0;
}
