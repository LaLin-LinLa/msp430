#ifndef _DRV_CAR_H_
#define _DRV_CAR_H_
#include "main.h"
#include "pid.h"

#define H_half       1 //���̿��7.5cm
#define motor_A 0
#define motor_B 1

typedef struct Car_Control_s
{
  PidTypeDef_t  motor_Speed_pid[2];
  int cnt_A;        //������A
  int cnt_B;        //������B
  int vel_A[4];     //vel_A[0]�������ٶ�A vel_A[2]������ٶ�A
  int vel_B[4];     //vel_B[0]�������ٶ�B vel_B[2]������ٶ�B
  int PWMA_set;     //PWM_A�趨ֵ
  int PWMB_set;     //PWM_B�趨ֵ
  char     dir_A;        //A�����ʶ��0ֹͣ��1��ת��2��ת
  char     dir_B;        //B�����ʶ��0ֹͣ��1��ת��2��ת
} Car_Control_t;

void drv_car_init(Car_Control_t* car);
void motor_dir(Car_Control_t* car,char motor,char mode);
void pwm_set_compare(uint8_t channel, int  cnt);
void PWM_A(Car_Control_t *car,int vel);
void PWM_B(Car_Control_t *car,int vel);
void Car_control(Car_Control_t *car,int v,int w);
void Car_control_loop(Car_Control_t* car);

#endif /* SRC_DRV_CAR_H_ */
