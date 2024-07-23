/*
 * This file contains some I2C operation.
 * By IC���� (1394024051@qq.com)
 * 2014-4-13 v1.0
 */
#include "HardWareIIC.h"

uchar I2CSendBuffer[2],I2CRecvBuffer; //I2C���ͻ���ͽ��ջ���

int I2CSendPtr=0;

/**********************************************************/
//�������ƣ�void I2C_Init
//��ڲ�����SlaveAddr:�ӻ����豸��ַ
//���ڲ�������
//�������ܣ�I2C��ʼ����P1.6->SCL ,P1.7->SDA
/**********************************************************/
void I2C_Init (unsigned char SlaveAddr)
{
  P1SEL |= BIT6+BIT7;               // Assign I2C pins to USCI_B0
  P1SEL2|= BIT6+BIT7;               // Assign I2C pins to USCI_B0
  UCB0CTL1 |= UCSWRST;              // Enable SW reset
  
  UCB0CTL0 = UCMST+UCMODE_3+UCSYNC; // I2C Master, synchronous mode
  UCB0CTL0 &= ~(UCSLA10+UCA10);			//7 bit add of slave and master 
  
  UCB0CTL1 = UCSSEL_2+UCSWRST;      // Use SMCLK, keep SW reset
  
  UCB0BR0 = 80;                     // fSCL = SMCLK/12 = ~100kHz
  UCB0BR1 = 0;
  
  UCB0I2COA = 0x01A5;								//set own address 
  UCB0I2CSA = SlaveAddr;            // Set slave address
  
  IE2 &= ~(UCB0RXIE+UCB0TXIE);         // disenable  TX&RX interrupt
  UCB0CTL1 &= ~UCSWRST;             // Clear SW reset, resume operation
  
}
/**********************************************************/
//�������ƣ�void I2C_WriteInit
//��ڲ�������
//���ڲ�������
//�������ܣ�I2Cд���ݳ�ʼ��������ģʽ�������жϹرգ������жϹر�
/**********************************************************/
void I2C_WriteInit()
{
  UCB0CTL1 |= UCTR;    	// UCTR=1 => Transmit Mode (R/W bit = 0)
  IFG2 &= ~UCB0TXIFG;		//clean TX interrupt sign 
  IE2 &= ~UCB0RXIE;   	// disable Receive ready interrupt
  IE2 &= ~UCB0TXIE;     // disable Transmit ready interrupt
}
/**********************************************************/
//�������ƣ�void I2C_ReadInit
//��ڲ�������
//���ڲ�������
//�������ܣ�I2C�����ݳ�ʼ��������ģʽ�������жϹرգ������жϹر�
/**********************************************************/
void I2C_ReadInit()
{
  UCB0CTL1 &= ~UCTR;   // UCTR=0 => Receive Mode (R/W bit = 1)
  IFG2 &= ~UCB0RXIFG;
  IE2 &= ~UCB0TXIE;    // disable Transmit ready interrupt
  IE2 &= ~UCB0RXIE;     // disable Receive ready interrupt
}
/**********************************************************/
//�������ƣ�I2C_Write
//��ڲ�����address:��Ҫд�����ݵ��豸�ĵ�ַ
//          data�����͵�����
//���ڲ�������
//�������ܣ�I2C��������
/**********************************************************/
void I2C_Write(uchar address,uchar data)
{

  I2C_WriteInit();
  UCB0CTL1 |= UCTXSTT;          //generate start condition
  //while(UCB0CTL1 & UCTXSTT);	//generate start condition ,and transmit slave address and write bit
  while(!(IFG2 & UCB0TXIFG));   //wait start condition and equipment address transmitted 
  IFG2 &= ~UCB0TXIFG;           //clean UCB0TXIFG 
  while(UCB0CTL1 & UCTXSTT);    //wait slave acknowledge 
  
  UCB0TXBUF=address;		//send address code 
  while(!(IFG2 & UCB0TXIFG ));	//wait sending over 
  IFG2 &= ~UCB0TXIFG;            // Clear USCI_B0 TX int flag
    
  UCB0TXBUF=data;		//send  data 
  while(!(IFG2 & UCB0TXIFG ));		//wait sending over 
  IFG2 &= ~UCB0TXIFG;            // Clear USCI_B0 TX int flag
  
  UCB0CTL1 |= UCTXSTP;            // I2C stop condition
  while (UCB0CTL1 & UCTXSTP);     // Ensure stop condition got sent
}
/**********************************************************/
//�������ƣ�uchar I2C_Read
//��ڲ�����address:��Ҫ�����ݵ��豸�ĵ�ַ
//���ڲ�������
//�������ܣ�I2C��������
/**********************************************************/
uchar I2C_Read(uchar address)
{
  unsigned char data;
  while (UCB0STAT & UCBUSY); // wait until I2C module has finished all operations
  I2C_WriteInit();
  UCB0CTL1 |= UCTXSTT;       // start condition generation
  while(UCB0CTL1 & UCTXSTT);
  
  
  UCB0TXBUF=address;							//send address code 
  while(!(IFG2 & UCB0TXIFG ));		//wait sending over 
  IFG2 &= ~UCB0TXIFG;            // Clear USCI_B0 TX int flag
  
 // __disable_interrupt();
 I2C_ReadInit();
  while(UCB0RXIFG & IFG2);
  IFG2 &= ~UCB0RXIFG;
  data  = UCB0RXBUF;
  
  UCB0CTL1 |= UCTXSTP;            // I2C stop condition
  while (UCB0CTL1 & UCTXSTP);     // Ensure stop condition got sent
  return data;
}

/*----------------------------------------------------------------------------*/
// Description:
//   Acknowledge Polling. The EEPROM will not acknowledge if a write cycle is
//   in progress. It can be used to determine when a write cycle is completed.
/*----------------------------------------------------------------------------*/
void I2C_AckPolling(void)
{
  while (UCB0STAT & UCBUSY) 
  {     
    ;// wait until I2C module has
  }  // finished all operations

  do 
  {
    UCB0STAT = 0x00;              // clear I2C interrupt flags
    UCB0CTL1 |= UCTR;             // I2CTRX=1 => Transmit Mode (R/W bit = 0)
    UCB0CTL1 &= ~UCTXSTT;
    UCB0CTL1 |= UCTXSTT;          // start condition is generated
    while (UCB0CTL1 & UCTXSTT)    // wait till I2CSTT bit was cleared
    {    
      if (!(UCNACKIFG & UCB0STAT)) 
      {  
        break;// Break out if ACK received
      }
    }
    UCB0CTL1 |= UCTXSTP;          // stop condition is generated after
                                  // slave address was sent => I2C communication is started
    while (UCB0CTL1 & UCTXSTP)
    {    
      ;// wait till stop bit is reset
    }
    __delay_cycles(500);          // Software delay
    
  } while (UCNACKIFG & UCB0STAT);
}


// USCI_B0 Data ISR
// Notice : UCSIAB0RX_ISR should be handle with UCSIAB0TX_ISR
#pragma vector = USCIAB0TX_VECTOR
__interrupt void USCIAB0TX_ISR(void)
{
  if (UCB0TXIFG & IFG2)      // TX
  {
    UCB0TXBUF = I2CSendBuffer[I2CSendPtr]; // Load TX buffer
    I2CSendPtr--;                          // Decrement TX byte counter
    if (I2CSendPtr < 0) 
    {		
      while (!(IFG2 & UCB0TXIFG));         // wait for tx complete
      IE2 &= ~UCB0TXIE;                    // disable interrupts.
      IFG2 &= ~UCB0TXIFG;                  // Clear USCI_B0 TX int flag
      __bic_SR_register_on_exit(LPM0_bits);// Exit LPM0
    }
  }
  else if (UCB0RXIFG & IFG2) // RX
  {
    I2CRecvBuffer = UCB0RXBUF;             // store received data in buffer
    __bic_SR_register_on_exit(LPM0_bits);  // Exit LPM0
  }
}
