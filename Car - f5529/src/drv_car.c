/**
  ******************************************************************************
  * @file    drv_car.c/h
  * @brief   小车底盘驱动
    P8.1------AN1
    P8.2------AN2
    P1.2------PWMA(TA0_R1)

    P3.5------BN1
    P3.6------BN2
    P1.3------PWMB(TA0_R2)

    P1.4------E1A
    P1.5------E1B

    10KHz
  ******************************************************************************
*/
#include "drv_car.h"

//速度环pid参数
float PID_DRIVER_SPEED[2][5]={0.2f, 0.7f, 0.2f, 50.0f, 40.0f,           //0
                              0.2f, 0.7f, 0.2f, 50.0f, 40.0f,};     //1

void drv_car_init(Car_Control_t* car)
{
    //PWMA(TA0_R1)
    P1SEL|=BIT2; //声明有特殊功能，不做普通 I/O 使用
    P1DIR|=BIT2; //输出
    P1DS |=BIT2; //全力驱动，否则可能无法驱动电机
    P1OUT&=~BIT2; //初始化输出低电平
    //PWMB(TA0_R2)
    P1SEL|=BIT3; //声明有特殊功能，不做普通 I/O 使用
    P1DIR|=BIT3; //输出
    P1DS |=BIT3; //全力驱动，否则可能无法驱动电机
    P1OUT&=~BIT3; //初始化输出低电平

    TA0CTL |=TASSEL_2+MC_3+TACLR; //设置时钟源为SMCLK，增减模式,计时器清零
    TA0EX0|=TAIDEX_4;                 //5分频  5MHz

    TA0CCR0 = 249;  //频率=SMCLK/(TACCR0+1)/2
    TA0CCR1 = 249;  //占空比(TACCR0 - TACCR1) / TACCR0
    TA0CCR2 = 249;

    TA0CCTL0 &= ~CAP;   //设置为比较模式
    TA0CCTL1 &= ~CAP;
    TA0CCTL2 &= ~CAP;
    TA0CCTL1 |= OUTMOD_6;
    TA0CCTL2 |= OUTMOD_6;

    //电机正反转使能引脚
    P8DIR |= BIT1;  //P8.1  AN1
    P8DIR |= BIT2;  //P8.2  AN2
    P3DIR |= BIT5;  //P3.5  BN1
    P3DIR |= BIT6;  //P3.6  BN2

    P8OUT &= ~BIT1;
    P8OUT &= ~BIT2;
    P3OUT &= ~BIT5;
    P3OUT &= ~BIT6;

    //encoder
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

    Init_PID(&car->motor_Speed_pid[0],PID_DRIVER_SPEED[0]);
    Init_PID(&car->motor_Speed_pid[1],PID_DRIVER_SPEED[1]);
    Car_control(car,0,0);

}

void motor_dir(Car_Control_t* car,char motor,char mode){
    switch(mode){
    case 0:
    {
      if(motor==motor_A){
        car->dir_A = 1; //A正转
        P8OUT &= ~BIT1;   //     P8.1 --- AIN1     0
        P8OUT |= BIT2;     //    P8.2 --- AIN2     1
      }else if(motor==motor_B){
        car->dir_B = 2; //B反转
        P3OUT |= BIT5;     //   P3.5 --- BIN1     1
        P3OUT &= ~BIT6;     //    P3.6 --- BIN2     0
      }
    }break;
    case 1:
    {
      if(motor==motor_A){
        car->dir_A = 2; //A反转
        P8OUT |= BIT1;   //     P8.1 --- AIN1     1
        P8OUT &= ~BIT2;     //    P8.2 --- AIN2     0
      }else if(motor==motor_B){
        car->dir_B = 1; //B正转
        P3OUT &= ~BIT5;     //   P3.5 --- BIN1     0
        P3OUT |= BIT6;     //    P3.6 --- BIN2     1
      }
    }break;
    case 2:    //刹车
    {
      if(motor==motor_A){
          car->dir_A = 0;
        P8OUT &= ~BIT1;
        P8OUT &= ~BIT2;
      }else if(motor==motor_B){
          car->dir_B = 0;
        P3OUT &= ~BIT5;
        P3OUT &= ~BIT6;
      }
    }break;
    default:break;
    }
}

//设置pwm占空比
void pwm_set_compare(uint8_t channel, int  cnt){
    switch(channel)
    {
        case 1:
            TA0CCR1 = cnt;
        break;
        case 2:
            TA0CCR2 = cnt;
        break;
        case 3:
            TA0CCR1 = cnt;TA0CCR2 = cnt;
        break;
        default:break;
    }
}

void Car_control_loop(Car_Control_t* car){
  if(car->PWMA_set>100||car->PWMB_set>100)  //判断输入是否合法
  {car->PWMA_set=100;car->PWMB_set=100;}

  car->vel_A[1] = car->vel_A[0];
  car->vel_B[1] = car->vel_B[0];
  //30减速比13线编码器：车轮转一圈每一相输出390个脉冲，测速周期为0.05s
  car->vel_A[0] = car->cnt_A*0.56; //测量cnt数为0~177,换算为占空比(0~100)输入，vel=cnt*0.56
  car->vel_B[0] = car->cnt_B*0.56;
  car->cnt_A=0;car->cnt_B=0;

  UTILS_LP_FAST(car->vel_A[0],car->vel_A[1],0.5f);
  UTILS_LP_FAST(car->vel_B[0],car->vel_B[1],0.5f);


  car->vel_A[3] = car->vel_A[2];
  car->vel_B[3] = car->vel_B[2];
  car->vel_A[2] = PID_Calc(&car->motor_Speed_pid[0], car->vel_A[0], car->PWMA_set, PID_MODE_DEL);
  car->vel_B[2] = PID_Calc(&car->motor_Speed_pid[1], car->vel_B[0], car->PWMB_set, PID_MODE_DEL);

  UTILS_LP_FAST(car->vel_A[2],car->vel_A[3],0.5f);
  UTILS_LP_FAST(car->vel_B[2],car->vel_B[3],0.5f);

  if(car->vel_A[2]>50) car->vel_A[2]=50;
  if(car->vel_B[2]>50) car->vel_B[2]=50;

  pwm_set_compare(1,249-2.5*car->vel_A[2]);
  pwm_set_compare(2,249-2.5*car->vel_B[2]);
}

void PWM_A(Car_Control_t *car,int vel)
{
  if(vel>0){
        motor_dir(car, motor_A,0);
        car->PWMA_set = vel;
    }
    else if(vel<0)
    {
        motor_dir(car, motor_A,1);
        car->PWMA_set = ~vel;
    }
    else
    {
        motor_dir(car, motor_A,2);
        car->PWMA_set = 0;
    }
}
void PWM_B(Car_Control_t *car,int vel)
{
  if(vel>0){
        motor_dir(car, motor_B,1);
        car->PWMB_set = vel;
    }
    else if(vel<0)
    {
        motor_dir(car, motor_B,0);
        car->PWMB_set = ~vel;
    }
    else
    {
        motor_dir(car, motor_B,2);
        car->PWMB_set = 0;
    }
}



//顺时针为角速度w正方向
void Car_control(Car_Control_t *car,int v,int w)
{
    PWM_A(car,(v+w));
    PWM_B(car,(v-w));
}




