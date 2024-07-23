#ifndef _PID_H_
#define _PID_H_
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

//���ٵ�ͨ�˲�
#define UTILS_LP_FAST(value, sample, filter_constant)    (value -= (filter_constant) * ((value) - (sample)))
//�޷�
#define _LimitMax(input, max)   \
    {                          \
        if (input > max)       \
        {                      \
            input = max;       \
        }                      \
        else if (input < -max) \
        {                      \
            input = -max;      \
        }                      \
    }

enum
{
  PID_MODE_DEL, //����ʽPID

} PID_MODE_e;

typedef struct PidTypeDef_s
{
  float error[3]; //����� 0���� 1��ȥ 2��ǰ
  float Dbuf[2];  //΢���� 0���� 1��ȥ

  float Kp;
  float Ki;
  float Kd;

  float Pout;
  float Iout;
  float Dout;
  float out;

  float max_out;  //����޷�
  float max_iout; //��������޷�

} PidTypeDef_t;

void Init_PID(PidTypeDef_t *pid, const float PID[5]);
void PID_Clear(PidTypeDef_t *pid);
float PID_Calc(PidTypeDef_t *pid,float ref,float set, char mode);

#endif
