#ifndef _DRV_CAR_H_
#define _DRV_CAR_H_
#include "main.h"
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
  char     dir_A;        //A方向标识：0停止，1正转，2反转
  char     dir_B;        //B方向标识：0停止，1正转，2反转
} Car_Control_t;

void drv_car_init(Car_Control_t* car);
void motor_dir(Car_Control_t* car,char motor,char mode);
void pwm_set_compare(uint8_t channel, int  cnt);
void PWM_A(Car_Control_t *car,int vel);
void PWM_B(Car_Control_t *car,int vel);
void Car_control(Car_Control_t *car,int v,int w);
void Car_control_loop(Car_Control_t* car);

#endif /* SRC_DRV_CAR_H_ */
