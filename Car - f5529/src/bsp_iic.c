#include "bsp_iic.h"
#define MAX_BUFFER_SIZE     20

uint8_t I2CSendBuffer[MAX_BUFFER_SIZE],I2CRecvBuffer;
int I2CSendPtr=0;

void bsp_iic_init (uint8_t SlaveAddr)
{
    P2SEL |= BIT5;                       // Assign I2C pins to USCI_B0 SCL P2.5
    P2SEL |= BIT4;                       //Assign I2C pins to USCI_B0 SDA P2.4
    /*使能P2.5口的上拉电阻*/
    P2REN |= BIT5;
    P2OUT |= BIT5;
    /*使能2.4口的上拉电阻*/
    P2REN |= BIT4;
    P2OUT |= BIT4;
    UCB0CTL1 |= UCSWRST;                      // Enable SW reset
    UCB0CTL0 = UCMST+UCMODE_3+UCSYNC;         // I2C Master, synchronous mode
    UCB0CTL1 = UCSSEL_1+UCSWRST;              // Use ACLK, keep SW reset
    UCB0BR0 = 250;                             // fSCL = SMCLK/250 = ~100kHz
    UCB0BR1 = 0;
    UCB0I2COA = 0x01A5;
    UCB0I2CSA = SlaveAddr;                    // Set slave address
    UCB0CTL1 &= ~UCSWRST;                     // Clear SW reset, resume operation
    UCB0IE |= UCRXIE + UCTXIE;                         // Enable RX/TX interrupt

}

void iic_write_init()
{
    UCB0CTL1 |= UCTR;               // UCTR=1 => Transmit Mode (R/W bit = 0)
    UCB0IFG &= ~UCTXIFG;            // Clear Transmit Interrupt Flag
    UCB0IE &= ~UCRXIE;               // disable Receive ready interrupt
    UCB0IE |= UCTXIE;               // enable Transmit ready interrupt
}
void iic_read_init()
{
    UCB0CTL1 |= ~UCTR;               // UCTR=1 => Transmit Mode (R/W bit = 0)
    UCB0IFG &= ~UCRXIFG;            // Clear Transmit Interrupt Flag
    UCB0IE &= ~UCTXIE;               // disable Transmit ready interrupt
    UCB0IE |= UCRXIE;               // enable Receive ready interrupt

}

void iic_write(uint8_t address,uint8_t data)
{
    I2CSendPtr = 1;
    I2CSendBuffer[1] = address;
    I2CSendBuffer[0] = data;

    while (UCB0STAT & UCBUSY);          // wait until I2C module has finished all operations.
    iic_write_init();
    //_disable_interrupt();
    UCB0CTL1 |= UCTXSTT;
    //__bis_SR_register(GIE);    // Waiting for Sending.
    UCB0CTL1 |= UCTXSTP;                // I2C stop condition
    while (UCB0CTL1 & UCTXSTP);         // Ensure stop condition got sent
}

uint8_t iic_read(uint8_t address)
{
    while (UCB0STAT & UCBUSY);          // wait until I2C module has finished all operations
    //Change to Write Mode.
    I2CSendBuffer[0] = address;
    I2CSendPtr = 0;
    iic_write_init();
    //_disable_interrupt();
    UCB0CTL1 |= UCTXSTT;                 // start condition generation
                                         // => I2C communication is started
    //__bis_SR_register(GIE);     // Enter LPM0 w/ interrupts

    //Change to Read Mode.
    iic_read_init();

    //while (UCB0CTL1 & UCTXSTP);             // Ensure stop condition got sent
   UCB0CTL1 |= UCTXSTT;                    // I2C start condition
   while(UCB0CTL1 & UCTXSTT);              // Start condition sent?
   UCB0CTL1 |= UCTXSTP;                    // I2C stop condition

    //__bis_SR_register(LPM0_bits + GIE);     // Enter LPM0 w/ interrupts
    while (UCB0CTL1 & UCTXSTP);             // Ensure stop condition got sent
    return I2CRecvBuffer;
}

int iic_write_len(uint8_t addr, uint8_t reg, uint8_t len, uint8_t *buf)
{
    int i;
    UCB0I2CSA = addr;
    I2CSendPtr = len-1;
    I2CSendBuffer[len-1] = reg;
    for(i=(len-2);i>=0;i--){
        // I2CSendBuffer[i] = buf[len-2-i];
         I2CSendBuffer[i] = *buf;
         buf++;
    }

    while (UCB0STAT & UCBUSY);          // wait until I2C module has finished all operations.
    iic_write_init();
    //_disable_interrupt();
    UCB0CTL1 |= UCTXSTT;
    //__bis_SR_register(CPUOFF + GIE);    // Waiting for Sending.
    UCB0CTL1 |= UCTXSTP;                // I2C stop condition
    while (UCB0CTL1 & UCTXSTP);         // Ensure stop condition got sent

    return 0;
}

int iic_read_len(uint8_t addr, uint8_t reg, uint8_t len, uint8_t *buf)
{
    UCB0I2CSA = addr;
    while(len){
        *buf=iic_read(reg);
        buf++;
        len--;
    }
    return 0;
}

// USCI_B0 Data ISR
// Notice : UCSIAB0RX_ISR should be handle with UCSIAB0TX_ISR
void IIC_TX_ISR(void)
{
    UCB0TXBUF = I2CSendBuffer[I2CSendPtr];      // Load TX buffer
    I2CSendPtr--;                               // Decrement TX byte counter
    if (I2CSendPtr < 0) {
        while (!(UCB0IFG & UCTXIFG));            // wait for tx complete
        UCB0IE &= ~UCTXIE;               // disable Transmit ready interrupt
        UCB0IFG &= ~UCTXIFG;                     // Clear USCI_B0 TX int flag
        //__bic_SR_register_on_exit(LPM0_bits);   // Exit LPM0
    }
}

void IIC_RX_ISR(void)
{
    UCB0IFG &= ~UCRXIFG;
    I2CRecvBuffer = UCB0RXBUF;
}


