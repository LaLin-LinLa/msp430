#ifndef _PID_H_
#define _PID_H_
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

//快速低通滤波
#define UTILS_LP_FAST(value, sample, filter_constant)    (value -= (filter_constant) * ((value) - (sample)))
//限幅
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
  PID_MODE_DEL, //增量式PID

} PID_MODE_e;

typedef struct PidTypeDef_s
{
  float error[3]; //误差项 0现在 1过去 2以前
  float Dbuf[2];  //微分项 0现在 1过去

  float Kp;
  float Ki;
  float Kd;

  float Pout;
  float Iout;
  float Dout;
  float out;

  float max_out;  //输出限幅
  float max_iout; //积分输出限幅

} PidTypeDef_t;

void Init_PID(PidTypeDef_t *pid, const float PID[5]);
void PID_Clear(PidTypeDef_t *pid);
float PID_Calc(PidTypeDef_t *pid,float ref,float set, char mode);

#endif
