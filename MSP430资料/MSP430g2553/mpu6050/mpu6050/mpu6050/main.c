//******************************************************************************
//  ACLK = n/a, MCLK = SMCLK = TACLK = BRCLK = default DCO = ~1.2MHz
//  MSP430 G2553 with LaunchPad
//  P1.7/UCB0SDA
//  P1.6/UCB0SCL
//  Attention : Set RXD&TXD(On LaunchPad) jumpers from SoftUart(SW) to HardUart(HW)
//  By vrqq (vrqq3118@163.com)
//******************************************************************************
#include <msp430g2553.h>
#include "mpu6050.h"

int main(void)
{
	int ax,ay,az,gx,gy,gz;
	WDTCTL = WDTPW + WDTHOLD;                 // Stop Watchdog Timer
	MPU6050Init();

	while(1)
	{
		ax = GetAccelX();
		ay = GetAccelY();
		az = GetAccelZ();
		gx = GetAnguX();
		gy = GetAnguY();
		gz = GetAnguZ();
		__no_operation();  //add a breakpoint and see var here.
	}
}
