#include <msp430g2553.h> 
#include"mpu6050.h"
#include "USCI_A0.h"
#include "IMU.h "
/*
 *  ======== BCSplus_graceInit ========
 *  Initialize MSP430 Basic Clock System
 */
void BCSplus_graceInit(void)
{
    /* USER CODE START (section: BCSplus_graceInit_prologue) */
    /* User initialization code */
    /* USER CODE END (section: BCSplus_graceInit_prologue) */

    /* 
     * Basic Clock System Control 2
     * 
     * SELM_0 -- DCOCLK
     * DIVM_0 -- Divide by 1
     * ~SELS -- DCOCLK
     * DIVS_1 -- Divide by 2
     * ~DCOR -- DCO uses internal resistor
     * 
     * Note: ~<BIT> indicates that <BIT> has value zero
     */
    BCSCTL2 = SELM_0 | DIVM_0 | DIVS_1;

    if (CALBC1_16MHZ != 0xFF) {
        /* Adjust this accordingly to your VCC rise time */
        __delay_cycles(100000);

        /* Follow recommended flow. First, clear all DCOx and MODx bits. Then
         * apply new RSELx values. Finally, apply new DCOx and MODx bit values.
         */
        DCOCTL = 0x00;
        BCSCTL1 = CALBC1_16MHZ;     /* Set DCO to 16MHz */
        DCOCTL = CALDCO_16MHZ;
    }

    /* 
     * Basic Clock System Control 1
     * 
     * XT2OFF -- Disable XT2CLK
     * ~XTS -- Low Frequency
     * DIVA_0 -- Divide by 1
     * 
     * Note: ~XTS indicates that XTS has value zero
     */
    BCSCTL1 |= XT2OFF | DIVA_0;

    /* 
     * Basic Clock System Control 3
     * 
     * XT2S_0 -- 0.4 - 1 MHz
     * LFXT1S_0 -- If XTS = 0, XT1 = 32768kHz Crystal ; If XTS = 1, XT1 = 0.4 - 1-MHz crystal or resonator
     * XCAP_1 -- ~6 pF
     */
    BCSCTL3 = XT2S_0 | LFXT1S_0 | XCAP_1;

    /* USER CODE START (section: BCSplus_graceInit_epilogue) */
    /* User code */
    /* USER CODE END (section: BCSplus_graceInit_epilogue) */
}/*
 * main.c
 */
int main(void) 
{
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
    BCSplus_graceInit();        //MCLK = 16M,SMCLK = 8M,ack =32.768k
    WDTCTL = WDTPW | WDTTMSEL | WDTIS0;
    IE1 |= WDTIE;
    USCI_A0_init();             //uart 38400bps  
    P1DIR |= BIT0;              //initialize led control PIN 
    _EINT();
    MPU6050_Init();             //initialize mpu6050
    
    while(1)
    {
      /*
      Get_Attitude();
     //MPU6050_Dataanl();
     // ReadMPU6050All();
     //Prepare_Data();             //耗时6.15ms
     //Uart1_Send_AF();             //耗时8.42ms
     P1OUT ^= BIT0;
     Get_Attitude();
     //ReadMPU6050All();
     //MPU6050_Dataanl();         //未使用多字节读取，耗时6ms,使用多字节读取，耗时3.6ms
     //Prepare_Data();
    // Uart1_Send_AF();
     P1OUT ^= BIT0;
     */
    }
    
}

//watchdog interrupt server program per 1ms
#pragma vector=WDT_VECTOR
__interrupt void WDT_ISR_HOOK(void)
{
    /* USER CODE START (section: WDT_ISR_HOOK) */
    /* replace this comment with your code */
    static unsigned int count=0;
    static unsigned char ms2 = 0,ms5 = 0,ms10 = 0;
    count++;
    ms2++;
    ms5++;
    ms10++;
    
    if(ms2 == 2)
    {
     ms2 = 0;
     Prepare_Data();
     //MPU6050_Dataanl();
    }
    if(ms5 >= 4)
    {
      ms5 = 0;
      Get_Attitude();
    
    }
    if(ms10 >= 10)
    {
      ms10 = 0;
      Uart1_Send_AF();
    }
    if(count== 200)
    {
      count=0;
      P1OUT ^= BIT0;
    }

	/* USER CODE END (section: WDT_ISR_HOOK) */
}