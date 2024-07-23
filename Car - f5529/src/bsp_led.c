#include "bsp_led.h"

void bsp_led_init(void)
{
  /*��ʼ��LED����IO��Ϊ���*/
    P1DIR |= BIT1;  //LED1
    P4DIR |= BIT7;  //LED2
    /*��ʼ��LED����IO��Ϊ�͵�ƽ��LED2��ʼ״̬Ϊ��*/
    P1OUT &= ~BIT1; //LED1
    P4OUT &= ~BIT7; //LED2
}

void LED1(char mode)
{
  switch (mode)
  {
    case 0:
      P1OUT &= ~BIT1;//Ϩ��LED1
    break;
    case 1:
      P1OUT |= BIT1;//����LED1
    break;
    case 2:
      P1OUT ^= BIT1;//��תLED1
    break;
  default:
    break;
  }
}

void LED2(char mode)
{
  switch (mode)
  {
    case 0:
      P4OUT &= ~BIT7;//Ϩ��LED2
    break;
    case 1:
      P4OUT |= BIT7;//����LED2
    break;
    case 2:
      P4OUT ^= BIT7;//��תLED2
    break;
  default:
    break;
  }
}
