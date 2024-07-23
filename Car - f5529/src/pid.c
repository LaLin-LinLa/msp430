#include "pid.h"

/**
  * @brief  pid��ʼ��
	* @param  pid
 **/
void Init_PID(PidTypeDef_t *pid, const float PID[5])
{	
	if (pid == NULL || PID == NULL)
	{
			return;
	}
	pid->Kp = PID[0];
	pid->Ki = PID[1];
	pid->Kd = PID[2];
	pid->max_out = PID[3]; 
	pid->max_iout = PID[4];
	PID_Clear(pid);
}

/**
  * @brief  ���ֵ����
	* @param  pid
 **/
void PID_Clear(PidTypeDef_t *pid){
	if (pid == NULL)
    {
        return;
    }
    pid->error[0] = pid->error[1] = pid->error[2] = 0.0f;
    pid->Dbuf[0] = pid->Dbuf[1] = 0.0f;
    pid->out = pid->Pout = pid->Iout = pid->Dout = 0.0f;
}


/**
  * @brief  PID����
	* @param  PID
  * @param  ref			����ֵ
	* @param  set  		����ֵ
  * @param  mode  	����ģʽ
  * @param  T  	    ��������
	* @return out			
 **/
float PID_Calc(PidTypeDef_t *pid,float ref,float set, char mode){
	if (pid == NULL)
	{
			return 0.0f;
	}

	pid->error[2] = pid->error[1];
	pid->error[1] = pid->error[0];
	pid->error[0] = set - ref;


  UTILS_LP_FAST(pid->error[0], pid->error[1], 0.05f);

  switch(mode)
  {
    case PID_MODE_DEL:  //����ʽ
    {
      /*����Pout*/
      if(pid->Kp != 0)
        pid->Pout = pid->Kp * (pid->error[0] - pid->error[1]);
      else
        pid->Pout = 0.0f;

      /*����Iout*/
      if(pid->Ki != 0){						
          pid->Iout = pid->Ki * pid->error[0];
        _LimitMax(pid->Iout, pid->max_iout);
      }else
        pid->Iout = 0.0f;

      /*����Dout*/
      if(pid->Kd != 0){
          pid->Dbuf[1] = pid->Dbuf[0];
          pid->Dbuf[0] = (pid->error[0] - 2.0f * pid->error[1] + pid->error[2]);
          UTILS_LP_FAST(pid->Dbuf[0], pid->Dbuf[1], 0.05f);		//����ȫ΢��
          pid->Dout = pid->Kd * pid->Dbuf[0];
      }else
        pid->Dout = 0.0f;

       /*����out*/
       pid->out = pid->Pout + pid->Iout + pid->Dout;
       _LimitMax(pid->out, pid->max_out);
    }break;
    default:break;
  }
  return pid->out;
}

