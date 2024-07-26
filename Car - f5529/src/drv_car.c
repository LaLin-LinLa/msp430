/**
  ******************************************************************************
  * @file    drv_car.c/h
  * @brief   С����������
    P8.1------AN1
    P8.2------AN2
    P1.2------PWMA(TA0_R1)

    P3.5------BN1
    P3.6------BN2
    P1.3------PWMB(TA0_R2)

    P1.4------E1A
    P3.7------E1B

    P1.5------E2A
    P2.3------E2B

    10KHz
  ******************************************************************************
*/
#include "drv_car.h"

//�ٶȻ�pid����
float PID_DRIVER_SPEED[2][5]={0.2f, 0.7f, 0.2f, 50.0f, 40.0f,           //0
                              0.2f, 0.7f, 0.2f, 50.0f, 40.0f,};     //1

void drv_car_init(Car_Control_t* car)
{
    //PWMA(TA0_R1)
    P1SEL|=BIT2; //���������⹦�ܣ�������ͨ I/O ʹ��
    P1DIR|=BIT2; //���
    P1DS |=BIT2; //ȫ����������������޷��������
    P1OUT&=~BIT2; //��ʼ������͵�ƽ
    //PWMB(TA0_R2)
    P1SEL|=BIT3; //���������⹦�ܣ�������ͨ I/O ʹ��
    P1DIR|=BIT3; //���
    P1DS |=BIT3; //ȫ����������������޷��������
    P1OUT&=~BIT3; //��ʼ������͵�ƽ

    TA0CTL |=TASSEL_2+MC_3+TACLR; //����ʱ��ԴΪSMCLK������ģʽ,��ʱ������
    TA0EX0|=TAIDEX_4;                 //5��Ƶ  5MHz

    TA0CCR0 = ARR;  //Ƶ��=SMCLK/(TACCR0+1)/2
    TA0CCR1 = ARR;  //ռ�ձ�(TACCR0 - TACCR1) / TACCR0
    TA0CCR2 = ARR;

    TA0CCTL0 &= ~CAP;   //����Ϊ�Ƚ�ģʽ
    TA0CCTL1 &= ~CAP;
    TA0CCTL2 &= ~CAP;
    TA0CCTL1 |= OUTMOD_6;
    TA0CCTL2 |= OUTMOD_6;

    //�������תʹ������
    P8DIR |= BIT1;  //P8.1  AN1
    P8DIR |= BIT2;  //P8.2  AN2
    P3DIR |= BIT5;  //P3.5  BN1
    P3DIR |= BIT6;  //P3.6  BN2

    P8OUT &= ~BIT1;
    P8OUT &= ~BIT2;
    P3OUT &= ~BIT5;
    P3OUT &= ~BIT6;

    //encoder
    /*��ʼ��IO��P1.4Ϊ����*/
    P1DIR &= ~BIT4;
    /*��ʼ��IO��P1.5Ϊ����*/
    P1DIR &= ~BIT5;

    P3DIR &= ~BIT7;
    P2DIR &= ~BIT3;

    /*ʹ��P1.4�ڵ���������*/
    P1REN |= BIT4;
    P1OUT |= BIT4;
    /*ʹ��P1.5�ڵ���������*/
    P1REN |= BIT5;
    P1OUT |= BIT5;
    /*��P1.4���ж�*/
    P1IE |= BIT4;
    /*�趨Ϊ�����ش���*/
    P1IES &= ~BIT4;
    /*��P1.5���ж�*/
    P1IE |= BIT5;
    /*�趨Ϊ�����ش���*/
    P1IES &= ~BIT5;
    /*����жϱ�־λ*/
    P1IFG &= ~BIT4;P1IFG &= ~BIT5;

    Init_PID(&car->motor_Speed_pid[0],PID_DRIVER_SPEED[0]);
    Init_PID(&car->motor_Speed_pid[1],PID_DRIVER_SPEED[1]);
    Car_control(car,0,0);

}

void motor_dir(char motor,char mode){
    switch(mode){
    case 0:
    {
      if(motor==motor_A){
        P8OUT &= ~BIT1;   //     P8.1 --- AIN1     0
        P8OUT |= BIT2;     //    P8.2 --- AIN2     1
      }else if(motor==motor_B){
        P3OUT |= BIT5;     //   P3.5 --- BIN1     1
        P3OUT &= ~BIT6;     //    P3.6 --- BIN2     0
      }
    }break;
    case 1:
    {
      if(motor==motor_A){
        P8OUT |= BIT1;   //     P8.1 --- AIN1     1
        P8OUT &= ~BIT2;     //    P8.2 --- AIN2     0
      }else if(motor==motor_B){
        P3OUT &= ~BIT5;     //   P3.5 --- BIN1     0
        P3OUT |= BIT6;     //    P3.6 --- BIN2     1
      }
    }break;
    case 2:    //ɲ��
    {
      if(motor==motor_A){
        P8OUT &= ~BIT1;
        P8OUT &= ~BIT2;
      }else if(motor==motor_B){
        P3OUT &= ~BIT5;
        P3OUT &= ~BIT6;
      }
    }break;
    default:break;
    }
}

//����pwmռ�ձ�
void pwm_set_compare(uint8_t channel, int  cnt){
    if(cnt>=100)cnt=100;
     if(cnt<=-100)cnt=-100;
    switch(channel)
    {
        case 1: //A
        {
          if(cnt>0)
          {
            motor_dir(motor_A,0);
            TA0CCR1 = 249-2.49*cnt;
          }else if(cnt<0)
          {
            motor_dir(motor_A,1);
            TA0CCR1 = 2.49*cnt+249;
          }else
          {
            TA0CCR1 = 249;
            motor_dir(motor_A,2);
          }

        }
        break;
        case 2:   //B
        {
          if(cnt>0)
          {
            motor_dir(motor_B,1);
            TA0CCR2 = 249-2.49*cnt;
          }else if(cnt<0)
          {
            motor_dir(motor_B,0);
            TA0CCR2 = 2.49*cnt+249;
          }else
          {
            TA0CCR2 = 249;
            motor_dir(motor_B,2);

          }
        }
        break;
        case 3:
        {
          if(cnt>0)
          {
            motor_dir(motor_A,0);
            motor_dir(motor_B,1);
            TA0CCR2 = TA0CCR1 = 249-2.49*cnt;
          }else if(cnt<0)
          {
            motor_dir(motor_A,1);
            motor_dir(motor_B,0);
            TA0CCR2 = TA0CCR1 = 2.49*cnt+249;
          }else
          {
            TA0CCR1=TA0CCR2 = 249;
            motor_dir(motor_A,2);
            motor_dir(motor_B,2);
          }
        }
        break;
        default:break;
    }
}

void Car_control_loop(Car_Control_t* car){
   if(car->PWMA_set>=100)
       car->PWMA_set = 100;
   else if(car->PWMA_set<=-100)
       car->PWMA_set = -100;

   if(car->PWMB_set>=100)
       car->PWMB_set = 100;
   else if(car->PWMB_set<=-100)
       car->PWMB_set = -100;


   car->vel_A[1] = car->vel_A[0];
   car->vel_B[1] = car->vel_B[0];
  //30���ٱ�13�߱�����������תһȦÿһ�����390�����壬��������Ϊ0.05s
  car->vel_A[0] = car->cnt_A*0.5882; //����cnt��Ϊ0~170,����Ϊռ�ձ�(0~100)���룬vel=cnt*0.5882
  car->vel_B[0] = car->cnt_B*0.5882;
  car->cnt_A=0;car->cnt_B=0;

  UTILS_LP_FAST(car->vel_A[0],car->vel_A[1],0.2f);
  UTILS_LP_FAST(car->vel_B[0],car->vel_B[1],0.2f);

  car->vel_A[3] = car->vel_A[2];
  car->vel_B[3] = car->vel_B[2];

  car->vel_A[2] = PID_Calc(&car->motor_Speed_pid[0], car->vel_A[0], car->PWMA_set, PID_MODE_DEL);
  car->vel_B[2] = PID_Calc(&car->motor_Speed_pid[1], car->vel_B[0], car->PWMB_set, PID_MODE_DEL);

  UTILS_LP_FAST(car->vel_A[2],car->vel_A[3],0.2f);
  UTILS_LP_FAST(car->vel_B[2],car->vel_B[3],0.2f);

 pwm_set_compare(1,car->vel_A[2]);
 pwm_set_compare(2,car->vel_B[2]);
}

void update_encoder_cnt(Car_Control_t *car)
{
   if(P1IFG & BIT4)//A�ж�
   {
       P1IFG &= ~BIT4;//�����־λ
       __bis_SR_register(GIE);//�����ж�Ƕ��
       if(P3IN & BIT7)
           car->cnt_A--;
       else
           car->cnt_A++;
   }
   if(P1IFG & BIT5)//B�ж�
   {
       P1IFG &= ~BIT5;//�����־λ
       __bis_SR_register(GIE);//�����ж�Ƕ��
       if(P2IN & BIT3)
           car->cnt_B++;
       else
           car->cnt_B--;
}
}


//˳ʱ��Ϊ���ٶ�w������
void Car_control(Car_Control_t *car,int v,int w)
{
    car->PWMA_set = (v+w);
    car->PWMB_set = (v-w);

}




