#include "bsp_clks.h"
#include "bsp_led.h"
#include "bsp_key.h"
#include "bsp_timer.h"
#include "bsp_iic.h"
#include "bsp_uart.h"
#include "drv_oled.h"
#include "drv_car.h"
//#include "inv_mpu.h"
//#include "inv_mpu_dmp_motion_driver.h"

 #include "drv_mpu6050.h"

Car_Control_t   car_control = {0};

char flag=0;
int vel = 0;
uint8_t mode;
uint32_t time;


int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    bsp_clks_init();
    bsp_led_init();
    bsp_key_init();
    bsp_timer_init();
    bsp_uart0_init();
    bsp_uart1_init();
    drv_car_init(&car_control);

//    OLED_Init();
//    OLED_Clear();
//    OLED_ShowString(30,1, "2024NUEDC",16);
//    OLED_ShowString(35,4, "Welcome",16);

//   while(mpu_dmp_init())
//   {
//       __delay_ms(20);
//   }

    __bis_SR_register(GIE);    //�������ж�
     while(drv_mpu6050_init());



//    OLED_Clear();
//    OLED_ShowString(20,0, "MOTOR_TEST",16);
//    OLED_ShowString(20,2, "VEL_A",16);
//    OLED_ShowString(20,4, "VEL_B",16);

//    OLED_Clear();
//    OLED_ShowString(20,0, "RED_POINT",16);
//    OLED_ShowString(20,2, "VEL_A",16);
//    OLED_ShowString(20,4, "VEL_B",16);

//    OLED_Clear();
//    OLED_ShowString(20,0, "HC05_TEST",16);

//    OLED_Clear();
//    OLED_ShowString(20,0, "MPU_TEST",16);

    while(1){
        LED1(2);
        __delay_ms(100);
        //motor_test
//        time = Get_Tick();
//           if(key_scan(1)==1){
//              if(!flag)
//              {
//                  vel++;
//                  if(vel==60){
//                      vel=60;
//                      flag=1;
//                  }
//              }else{
//                  vel--;
//                  if(vel==0){
//                      vel=0;
//                      flag=0;
//                  }
//              }
//              Car_control(&car_control,vel,0);
//         }
//        OLED_ShowNum(70,2,car_control.vel_A[0],2,16);
//        OLED_ShowNum(70,4,car_control.vel_B[0],2,16);
//        uart1_printf("%d,%d,%d,%d,%d\n",car_control.vel_A[0],car_control.vel_B[0],car_control.vel_A[2],car_control.vel_B[2],vel);


//        OLED_ShowString(20,2, rxbuff1,8);   //�����2077
        //OLED_ShowNum(100,7,time,4,8);

//        mpu_dmp_get_data(&pitch,&roll,&yaw);
//        uart1_printf("%f,%f,%f\n",pitch,roll,yaw);





            //red_point
//                 if(iscomend0){
//                     mode = rxbuff0[0]-48;
//                     switch(mode){
//                         case 0: //ֹͣ
//                         {
//                             Car_control(&car_control,0,0);
//                         }break;
//                         case 1: //��ת
//                         {
//                             Car_control(&car_control,20,5);
//                         }break;
//                         case 2: //ֱ��
//                         {
//                              Car_control(&car_control,20,0);
//                         }break;
//                         case 3://��ת
//                         {
//                              Car_control(&car_control,20,-5);
//                         }break;
//                         default:break;
//                     }
//                     iscomend0 = 0;
//               }
//             OLED_ShowNum(70,2,car_control.vel_A[0],2,16);
//             OLED_ShowNum(70,4,car_control.vel_B[0],2,16);
           //uart1_printf("%d,%d,%d,%d\n",car_control.vel_A[0],car_control.vel_B[0],car_control.vel_A[2],car_control.vel_B[2]);



    }
}



/*TIMER0_A0_VECTOR �Ǽ�ʱ��0�� CCR0���жϼĴ�����TIMER0_A1_VECTOR �Ǽ�ʱ��0�� CCR1-CCR4��TA �ļĴ���*/
/*ͬ��ʱ�� TA1Ҳ�Ƿ�Ϊ���� TIMER1_A0_VECTOR ��TIMER1_A1_VECTOR*/
#pragma vector = TIMER1_A1_VECTOR
__interrupt void TIMA1_A1_ISR(void)
{
    switch(__even_in_range(TA1IV,14))/* ��仰����˼�ǣ�ֻ���� TA1IV ��ֵ����0--14�ڵ�ż��ʱ�Ż�ִ�� switch �����ڵ��������������� switch ����Ч��*/
    {
        case 0x0E:  //��ʱ������ж�,��ͨ���ж����������ȼ�
        {
            Update_Tick();
            LED2(2);
            Car_control_loop(&car_control);
        }
        break;
        default:
        break;
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

#pragma vector = USCI_A0_VECTOR
__interrupt void USCI_A0_ISR()
{
    switch(_even_in_range(UCA0IV,4))
    {
        case 0:break;                             // Vector 0 - No interrupt
        case 2:                                   // Vector 2 - RXIFG
        {
            UART0_Receive_ISR();
        }
        break;
        case 4:break;                             // Vector 4 - TXIFG
        default: break;
    }
}


#pragma vector = USCI_A1_VECTOR
__interrupt void USCI_A1_ISR()
{
    switch(_even_in_range(UCA1IV,4))
    {
        case 0:break;                             // Vector 0 - No interrupt
        case 2:                                   // Vector 2 - RXIFG
        {
            UART1_Receive_ISR();
        }
        break;
        case 4:break;                             // Vector 4 - TXIFG
        default: break;
    }
}

// USCI_B0 State ISR
#pragma vector = USCI_B0_VECTOR
__interrupt void USCI_B0_ISR(void)
{
  switch(__even_in_range(UCB0IV,12))
  {
  case  0: break;                           // Vector  0: No interrupts
  case  2: break;                           // Vector  2: ALIFG
  case  4: break;                           // Vector  4: NACKIFG
  case  6:                                  // Vector  6: STTIFG
     break;
  case  8:                                  // Vector  8: STPIFG
    break;
  case 10:                            // Vector 10: RXIFG
  {
      IIC_RX_ISR();
  }
      break;
  case 12:                                  // Vector 12: TXIFG
  {
      IIC_TX_ISR();
  }
    break;
  default: break;
  }
}



