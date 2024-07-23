#include "bsp_clks.h"
#include "bsp_led.h"
#include "bsp_key.h"
#include "bsp_uart.h"
#include "drv_car.h"
#include "bsp_timer.h"
#include "drv_mpu6050.h"

//char flag=0;
//char mode = 0;
//int vel = 0;

Car_Control_t   car_control = {0};

//uint32_t dt,dt_last=0;
//int gz=0;
//int angle_gz=0;
//#define PI  3.141592653


int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	bsp_clks_init();
	bsp_led_init();
	bsp_key_init();
	bsp_uart_init();
	bsp_timer_init();
    drv_car_init(&car_control);

	__bis_SR_register(GIE);    //�������ж�
	//while(drv_mpu6050_init());

	while(1)
	{
//          if(key_scan(0)){
//              mode++;
//              if(mode>3)mode=0;
//              switch(mode)
//              {
//                  case 0:
//                      vel=0;
//                  break;
//                  case 1:
//                      vel=5;
//                  break;
//                  case 2:
//                      vel=10;
//                  break;
//                  case 3:
//                      vel=15;
//                  break;
//                  default:break;
//              }

// //              if(!flag)
// //              {
// //                  vel++;
// //                  if(vel>=100){
// //                      vel=100;
// //                      flag=1;
// //                  }
// //              }else{
// //                  vel--;
// //                  if(vel<=0){
// //                      vel=0;
// //                      flag=0;
// //                  }
// //              }
//              PWM_A(&car_control,vel);
//              PWM_B(&car_control,vel);
//          }
	    if(iscomend){
            switch(mode){
                case 0: //ֹͣ
                {
                    PWM_set(&car_control,0,0);
                }break;
                case 1: //��ת��
                {
                    PWM_set(&car_control,30,-30);
                }break;
                case 2: //��ת��
                {
                     PWM_set(&car_control,30,-10);
                }break;
                case 3://��תС
                {
                     PWM_set(&car_control,30,-5);
                }break;
                case 4://ֱ��
                {
                     PWM_set(&car_control,30,0);
                }break;
                case 5://��תС
                {
                     PWM_set(&car_control,30,5);
                }break;
                case 6://��ת��
                {
                     PWM_set(&car_control,30,10);
                }break;
                case 7://��ת��
                {
                     PWM_set(&car_control,30,30);
                }break;
                default:{
                                PWM_set(&car_control,0,0);
                }break;
            }
        iscomend = 0;
	  }


//          dt_last = dt;
//          dt = Get_Tick();
//          if((dt-dt_last)>=20000)  //0.01s��ȡһ��
//          {
//            gz = GetAnguZ();
//            angle_gz += gz*0.01;
//            if(angle_gz > PI) angle_gz -= 2*PI;
//            if(angle_gz < -PI) angle_gz += 2*PI;
//            uart_printf("%d,%d\n", gz,angle_gz);
//          }

          //uart_printf("%d,%d,%d,%d,%d\n",car_control.vel_A[0], car_control.vel_B[0],car_control.vel_A[2],car_control.vel_B[2],vel);

	}
}

//�ⲿ�ж�1������
#pragma vector = PORT1_VECTOR
__interrupt void Port1_ISR(void)
{

    if(P1IFG & BIT4)//�ж��Ƿ���P1.4�����ж�
    {
        P1IFG &= ~BIT4;//�����־λ
        __bis_SR_register(GIE);//�����ж�Ƕ��
        car_control.cnt_A++;
    }
    if(P1IFG & BIT5)//�ж��Ƿ���P1.5�����ж�
    {
        P1IFG &= ~BIT5;//�����־λ
        __bis_SR_register(GIE);//�����ж�Ƕ��
        car_control.cnt_B++;
    }
}

//��ʱ��A�жϷ�����
#pragma vector = TIMER0_A1_VECTOR
__interrupt void TIMA0_ISR(void)
{
    switch(TA0IV)   //��TA0IV���ж��������Զ����
    {
//        case 0x02:  //��׽/�Ƚ�1�ж�
//            break;
//        case 0x04:  //��׽/�Ƚ�2�ж�
//            break;
        case 0x0A:  //��ʱ������ж�
        {
            Update_Tick();
            Car_control_loop(&car_control);
        }
            break;
        default:
        break;
    }
}


//����ͨѶ�ڷ����жϷ�����
#pragma vector = USCIAB0TX_VECTOR
__interrupt void USCIAB0TX_ISR(void)
{
    IIC_TX_ISR();

}

//����ͨѶ�ڽ����жϷ�����
#pragma vector = USCIAB0RX_VECTOR
__interrupt void USCIAB0RX_ISR(void)
{
    UART_Receive_ISR();

}

