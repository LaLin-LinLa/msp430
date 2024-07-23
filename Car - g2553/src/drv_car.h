#ifndef DRV_CAR_H_
#define DRV_CAR_H_
#include <msp430.h>
#include "pid.h"

#define H_half       1 //底盘宽度7.5cm
#define motor_A 0
#define motor_B 1

typedef struct Car_Control_s
{
  PidTypeDef_t  motor_Speed_pid[2];
  int cnt_A;        //脉冲数A
  int cnt_B;        //脉冲数B
  int vel_A[4];     //vel_A[0]：测量速度A vel_A[2]：输出速度A
  int vel_B[4];     //vel_B[0]：测量速度B vel_B[2]：输出速度B
  int PWMA_set;     //PWM_A设定值
  int PWMB_set;     //PWM_B设定值
} Car_Control_t;

void drv_car_init(Car_Control_t* car);
void motor_dir(char motor,char mode);
void PWM_A(Car_Control_t *car,int vel);
void PWM_B(Car_Control_t *car,int vel);
void PWM_set(Car_Control_t *car,int v,int w);
void Car_control_loop(Car_Control_t* car);
void Car_move_straight(Car_Control_t *car,int vel);

#endif
