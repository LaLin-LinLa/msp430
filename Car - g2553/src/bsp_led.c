#include "bsp_led.h"

/**
  * @brief  LED��ʼ��
  * @retval None
  */
void bsp_led_init(void)
{
    /*��ʼ��LED����IO��P1.6Ϊ���*/
    P1DIR |= BIT0;  //LED_R
    P1DIR |= BIT6;  //LED_G
    /*��ʼ��LED1����IO��P1.0Ϊ�͵�ƽ��LED1��ʼ״̬Ϊ��*/
    P1OUT &= ~BIT0;
    /*��ʼ��LED2����IO��P1.6Ϊ�͵�ƽ��LED2��ʼ״̬Ϊ��*/
    P1OUT &= ~BIT6;
}

//����LED
void led_set(char ledx)
{
    if(ledx == 1)
        P1OUT |= BIT0;//����LED1
    else if(ledx == 2)
        P1OUT |= BIT6;//����LED2
}

//Ϩ��LED
void led_rest(char ledx)
{
    if(ledx == 1)
        P1OUT &= ~BIT0;//Ϩ��LED1
    else if(ledx == 2)
        P1OUT &= ~BIT6;//Ϩ��LED2
}

//��תLED
void led_toggle(char ledx)
{
    if(ledx == 1)
        P1OUT ^= ~BIT0;//LED1
    else if(ledx == 2)
        P1OUT ^= ~BIT6;//LED2
    else if(ledx == 3){
        P1OUT ^= ~BIT0;P1OUT ^= ~BIT6;
    }
}



