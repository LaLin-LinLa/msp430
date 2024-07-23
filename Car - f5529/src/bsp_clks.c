#include "bsp_clks.h"
#include "HAL_PMM.h"

void bsp_clks_init(void)
{
//  P1SEL |= BIT0;
//  P1DIR |= BIT0;//����ACLK��  32.768KHz
//  P2SEL |= BIT2;
//  P2DIR |= BIT2;//����SMCLK�� 25MHz
//  P7SEL |= BIT7;
//  P7DIR |= BIT7;//����MCLK��  25MHz

  P5SEL |= BIT4|BIT5; //��IO����ΪXT1����
  UCSCTL6 |= XCAP_3;  //���õ���Ϊ12pF
  UCSCTL6 &= ~XT1OFF; //ʹ��XT1

  SetVCore(3);              //��� Vcore ��ѹ����߼��������㱶Ƶ����ú���λ��HAL_PMM.H ��
  __bis_SR_register(SCG0);  //���﷨Ϊ�̶���ʽ����Ϊ�������ڵı�����λ��SCG0��ϵͳ����ģʽ�йأ���ʱ MCLK ��ͣ����
  UCSCTL0 = 0;              //�����㣬FLL ����ʱ���üĴ���ϵͳ���Զ����ã����ù�
  UCSCTL1 = DCORSEL_6;
  UCSCTL2 = FLLD_1 | 380;   //FLLD=1,FLLN=380,��Ƶ��Ϊ2*��380+1��*32.768=24.969MHZ
  __bic_SR_register(SCG0);
  __delay_cycles(782000);   //ϵͳ�Դ��ľ�ȷ��ʱ����λ us


  while (SFRIFG1 & OFIFG){
     UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + DCOFFG);         // �������ʱ�ӱ�־λ��������Ҫ������ֱ�־λ����Ϊ�κ�һ�ֱ�־λ���ὫOFIFG��λ
     SFRIFG1 &= ~OFIFG;                                  // ���ʱ�Ӵ����־λ
  }
  UCSCTL4 = UCSCTL4&(~(SELS_7|SELM_7))|SELS_3|SELM_3;     //��SMCLK��MCLKʱ��Դ����ΪDCO
  //UCSCTL5 = UCSCTL5&(~DIVS_7)|DIVS_4;   //SMCLK16��Ƶ 1.57MHz
}

