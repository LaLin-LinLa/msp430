//-----------ʹ��ʵ��-----------//
//------------��ʱ-----------//
/*
delay(int ms);//�����ʱms(���Ľ�)
*/
//------------GPIO-----------//
/*
OUTPUT_GPIO_Config(1��0);//��ʼ��p1.0Ϊ���
INPUT_GPIO_Config(1,1);//��ʼ��p1.1Ϊ����
OUTPUT_GPIO_State(1,0,1);//p1.0����ߵ�ƽ
OUTPUT_GPIO_State(1,0,0);//p1.0����͵�ƽ
if(P1IN & BIT1) //�ж�P1.1�����ƽ�ߵ�״̬
*/
//------------KEY-----------//
/*
KEY0_GPIO_Config();//��ʼ�����ذ���0 p1.1
KEY1_GPIO_Config();//��ʼ�����ذ���1 p2.1
KEY0_STATE();//������·���0 �ɿ�����1
KEY1_STATE();//������·���0 �ɿ�����1
*/
//------------LED-----------//
/*
LED0_GPIO_Config(void);//��ʼ������LED0 p1.0 ��Ҫ����on
LED1_GPIO_Config(void);//��ʼ������LED1 p4.7
LED0_STATE(0);//����led0 ��
LED1_STATE(1);//����led1 ��
LED1_STATE(2);//����led1 ״̬��ת
*/
//---------INTERRUPT--------//
/*
IN_Config(1,1);//���ذ���p2.1���ⲿ�ж� �½��ش���
�жϴ�����ʵ�� ���Black_INTERRUPT.c
*/
//------------PWM-----------//
/*
PWM0_Config(void);//p1.2 ʱ����PWM��ʼ��
PWM1_Config(void);//p1.3 ʱ����PWM��ʼ��
PWM2_Config(void);//p1.4 ʱ����PWM��ʼ��
PWM3_Config(void);//p1.5 ʱ����PWM��ʼ��
PWM0_State(25);//p1.2 PWM�ٷ�֮25ռ�ձ�
PWM1_State(50);//p1.3 PWM�ٷ�֮50ռ�ձ�
PWM2_State(75);//p1.4 PWM�ٷ�֮75ռ�ձ�
PWM3_State(100);//p1.5 PWM�ٷ�֮100ռ�ձ�
*/
//------------USART-----------//
/*
USART0_Config();//����0��ʼ��
USART1_Config();//����1��ʼ�� �˴�����usb��
send0_buf("this is com test"); //���ڷ����ַ���
send1_buf("this is com test"); //���ڷ����ַ���
*/
//------------OLED-----------//
/*
��չʾ�����������������ຯ�����Black_OLED.c
OLED_Init(); //OLED��ʼ�� SCL p6.3 SDA p6.4
OLED_Clear();//OLED����
OLED_ShowString(29,0,��I E LAB��,8); //����x��y��������ʾ�ַ��������һλ�������С
OLED_ShowVI(50-1,3,u32 num,8);//��ʾĳ������ֵ
*/

