#ifndef USCI_A0_h
#define USCI_A0_h
#define uchar unsigned char
#define uint unsigned int

void USCI_A0_init(void);
void UartTX_Send_String(unsigned char *Data,int len);
unsigned char UartTX_Send_char(unsigned char c);

int putchar(int ch);
void sendChar(unsigned char c);
void sendStr(unsigned char *s);

void Uart1_Send_AF(void);
#endif /* #ifndef USCI_A0_h */