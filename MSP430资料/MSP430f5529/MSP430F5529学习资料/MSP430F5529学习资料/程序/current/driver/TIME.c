#include "TIME.h"




void TimeA1_Config()
{
    WDTCTL = WDTPW + WDTHOLD;           //�رտ��Ź�
    TA1CCR0 = 65000;
    TA1CCTL0 = CCIE;                    // CCR0�ж�����
    TA1CTL= TASSEL_2+TAIE+TACLR+MC_1;   //ʹ��SMCLKʱ�ӣ������жϲ����㣬����ģʽ;
    _EINT();    //�������ж�
}

void TimeA2_Config()
{
    WDTCTL = WDTPW + WDTHOLD;           //�رտ��Ź�
    TA2CCR0 = 65000;
    TA2CCTL0 = CCIE;                    // CCR0�ж�����
    TA2CTL= TASSEL_2+TAIE+TACLR+MC_1;   //ʹ��SMCLKʱ�ӣ������жϲ����㣬����ģʽ;
    _EINT();    //�������ж�
}





