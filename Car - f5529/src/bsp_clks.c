#include "bsp_clks.h"
#include "HAL_PMM.h"

void bsp_clks_init(void)
{
//  P1SEL |= BIT0;
//  P1DIR |= BIT0;//测量ACLK用  32.768KHz
//  P2SEL |= BIT2;
//  P2DIR |= BIT2;//测量SMCLK用 25MHz
//  P7SEL |= BIT7;
//  P7DIR |= BIT7;//测量MCLK用  25MHz

  P5SEL |= BIT4|BIT5; //将IO配置为XT1功能
  UCSCTL6 |= XCAP_3;  //配置电容为12pF
  UCSCTL6 &= ~XT1OFF; //使能XT1

  SetVCore(3);              //提高 Vcore 电压到最高级，以满足倍频需求该函数位于HAL_PMM.H 中
  __bis_SR_register(SCG0);  //该语法为固定格式，意为将括号内的变量置位，SCG0与系统工作模式有关，此时 MCLK 暂停工作
  UCSCTL0 = 0;              //先清零，FLL 运行时，该寄存器系统会自动配置，不用管
  UCSCTL1 = DCORSEL_6;
  UCSCTL2 = FLLD_1 | 380;   //FLLD=1,FLLN=380,则频率为2*（380+1）*32.768=24.969MHZ
  __bic_SR_register(SCG0);
  __delay_cycles(782000);   //系统自带的精确延时，单位 us


  while (SFRIFG1 & OFIFG){
     UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + DCOFFG);         // 清除三类时钟标志位，这里需要清除三种标志位，因为任何一种标志位都会将OFIFG置位
     SFRIFG1 &= ~OFIFG;                                  // 清除时钟错误标志位
  }
  UCSCTL4 = UCSCTL4&(~(SELS_7|SELM_7))|SELS_3|SELM_3;     //将SMCLK和MCLK时钟源配置为DCO
  //UCSCTL5 = UCSCTL5&(~DIVS_7)|DIVS_4;   //SMCLK16分频 1.57MHz
}

