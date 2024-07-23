/**
  ******************************************************************************
  * @file    drv_car.c/h
  * @brief   小车底盘驱动
    P2.0------AN1
    P2.1------AN2
    P2.2------PWMA

    P2.3------BN1
    P2.4------BN2
    P2.5------PWMB
      
    P1.4------E1A
    P1.5------E1B
  ******************************************************************************
*/
#include "drv_car.h"
//0.2 0.7
//速度环pid参数
float PID_DRIVER_SPEED[2][5]={0.2f, 0.7f, 0.0f, 30.0f, 35.0f,			//0
                              0.2f, 0.7f, 0.0f, 30.0f, 35.0f,};		//1

void drv_car_init(Car_Control_t* car){
  /*=======================PWM_Config_Start=======================*/
    /*设置时钟源为SMCLK*/
    TA1CTL |= TASSEL_2;
    /*设置工作模式为Up&Down*/
    TA1CTL |= MC0|MC1;
    /*设置TA1CCR0为0x00FF计数值极大值*/
    TA1CCR0 = 99;  //10Khz
    /*设置TA1CCR1为0x00FF*/
    TA1CCR1 = 99;//占空比(TACCR0 - TACCR1) / TACCR0,频率=SMCLK/(TACCR0+1)/2
    /*设置TA1CCR2为0x00FF*/
    TA1CCR2 = 99;//占空比(TACCR0 - TACCR2) / TACCR0,频率=SMCLK/(TACCR0+1)/2

    TA1CCTL0 &= ~CAP;   //设置为比较模式
    TA1CCTL1 &= ~CAP;
    TA1CCTL2 &= ~CAP;
    TA1CCTL1 |= OUTMOD_6;
    TA1CCTL2 |= OUTMOD_6;
    //PWM引脚
    P2SEL |= BIT5;  //P2.5
    P2DIR |= BIT5;
    P2SEL |= BIT2;  //P2.2
    P2DIR |= BIT2;
    //电机正反转使能引脚
    P2DIR |= BIT0;  //P2.0  AN1
    P2DIR |= BIT1;  //P2.1  AN2
    P2DIR |= BIT3;  //P2.3  BN1
    P2DIR |= BIT4;  //P2.4  BN2

    P2OUT &= ~BIT0;
    P2OUT &= ~BIT1;
    P2OUT &= ~BIT3;
    P2OUT &= ~BIT4;
  /*=======================PWM_Config_END=======================*/  

  /*=======================Encoder_Config_Start=======================*/
    /*初始化IO口P1.4为输入*/
    P1DIR &= ~BIT4;
    /*初始化IO口P1.5为输入*/
    P1DIR &= ~BIT5;
    /*使能P1.4口的上拉电阻*/
    P1REN |= BIT4;
    P1OUT |= BIT4;
    /*使能P1.5口的上拉电阻*/
    P1REN |= BIT5;
    P1OUT |= BIT5;
    /*打开P1.4口中断*/
    P1IE |= BIT4;
    /*设定为上升沿触发*/
    P1IES &= ~BIT4;
    /*打开P1.5口中断*/
    P1IE |= BIT5;
    /*设定为上升沿触发*/
    P1IES &= ~BIT5;
    /*清除中断标志位*/
    P1IFG &= ~BIT4;P1IFG &= ~BIT5;
    /*=======================Encoder_Config_END=======================*/
  Init_PID(&car->motor_Speed_pid[0],PID_DRIVER_SPEED[0]);
  Init_PID(&car->motor_Speed_pid[1],PID_DRIVER_SPEED[1]);
  motor_dir(motor_A, 3);motor_dir(motor_B, 3);

}

void motor_dir(char motor,char mode){
    switch(mode){
    case 0:   //正传
    {
      if(motor==motor_A){
        P2OUT &= ~BIT0;   //     P2.0 --- AIN1     0
        P2OUT |= BIT1;     //    P2.1 --- AIN2     1
      }else if(motor==motor_B){
        P2OUT |= BIT4;     //   P2.3 --- BIN1     1
        P2OUT &= ~BIT3;     //    P2.4 --- BIN2     0
      }
    }break;
    case 1:    //反转
    {
      if(motor==motor_A){
        P2OUT |= BIT0;   //     P2.0 --- AIN1     1
        P2OUT &= ~BIT1;     //    P2.1 --- AIN2     0
      }else if(motor==motor_B){
        P2OUT &= ~BIT4;     //   P2.3 --- BIN1     0
        P2OUT |= BIT3;     //    P2.4 --- BIN2     1
      }
    }break;
    case 3:    //刹车
    {
      if(motor==motor_A){
        P2OUT &= ~BIT0;
        P2OUT &= ~BIT1;
      }else if(motor==motor_B){
        P2OUT &= ~BIT3;
        P2OUT &= ~BIT4;
      }
    }break;
    default:break;
    }
}
//设置pwm占空比
void pwm_set_compare(uint8_t channel, uint16_t  cnt){
    switch(channel)
    {
        case 1:
            TA1CCR1 = cnt;
        break;
        case 2:
            TA1CCR2 = cnt;
        break;
        case 3:
            TA1CCR1 = cnt;TA1CCR2 = cnt;
        break;
        default:break;
    }
}


void Car_control_loop(Car_Control_t* car){
  //30减速比13线编码器：车轮转一圈每一相输出390个脉冲
  //测速周期为0.025s   转速=cnt/0.025/390
  car->vel_A[1] = car->vel_A[0];
  car->vel_B[1] = car->vel_B[0];
  car->vel_A[0] = car->cnt_A;
  car->vel_B[0] = car->cnt_B;
  car->cnt_A=0;car->cnt_B=0;

  UTILS_LP_FAST(car->vel_A[0],car->vel_A[1],0.05f);
  UTILS_LP_FAST(car->vel_B[0],car->vel_B[1],0.05f);
  car->vel_A[3] = car->vel_A[2];
  car->vel_B[3] = car->vel_B[2];

  car->vel_A[2] = PID_Calc(&car->motor_Speed_pid[0], car->vel_A[0], car->PWMA_set, PID_MODE_DEL);
  car->vel_B[2] = PID_Calc(&car->motor_Speed_pid[1], car->vel_B[0], car->PWMB_set, PID_MODE_DEL);

  UTILS_LP_FAST(car->vel_A[2],car->vel_A[3],0.05f);
  UTILS_LP_FAST(car->vel_B[2],car->vel_B[3],0.05f);

  pwm_set_compare(1,(99 - car->vel_A[2]));
  pwm_set_compare(2,(99 - car->vel_B[2]));
}


void PWM_A(Car_Control_t *car,int vel)
{
  if(vel>0){
        motor_dir(motor_A,1);
        car->PWMA_set = vel;
    }
    else if(vel<0)
    {
        motor_dir(motor_A,0);
        car->PWMA_set = ~vel;
    }
    else
    {
        motor_dir(motor_A,3);
        car->PWMA_set = 0;
    }
}
void PWM_B(Car_Control_t *car,int vel)
{
  if(vel>0){
        motor_dir(motor_B,1);
        car->PWMB_set = vel;
    }
    else if(vel<0)
    {
        motor_dir(motor_B,0);
        car->PWMB_set = ~vel;
    }
    else
    {
        motor_dir(motor_B,3);
        car->PWMB_set = 0;
    }
}



//顺时针为角速度w正方向
void PWM_set(Car_Control_t *car,int v,int w)
{
    PWM_A(car,(v+w));
    PWM_B(car,(v-w));
}




