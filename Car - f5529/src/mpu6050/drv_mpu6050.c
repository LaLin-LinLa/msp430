#include "drv_mpu6050.h"

void MPU_Set_Gyro_Fsr(uint8_t fsr);
void MPU_Set_Accel_Fsr(uint8_t fsr);
void MPU_Set_LPF(uint16_t lpf);
void MPU_Set_Rate(uint16_t rate);

uint8_t res;
uint8_t drv_mpu6050_init()
{
    bsp_iic_init(SlaveAddr);

	iic_write(MPU_PWR_MGMT1_REG,0X80); //复位MPU6050
	__delay_cycles(1000000);
	iic_write(MPU_PWR_MGMT1_REG,0X00); //唤醒MPU6050
    MPU_Set_Gyro_Fsr(3);                    //陀螺仪传感器,±2000dps
    MPU_Set_Accel_Fsr(0);                   //加速度传感器,±2g
    MPU_Set_Rate(50);                       //设置采样率50Hz
    iic_write(MPU_INT_EN_REG,0X00);    //关闭所有中断
    iic_write(MPU_USER_CTRL_REG,0X00); //I2C主模式关闭
    iic_write(MPU_FIFO_EN_REG,0X00);   //关闭FIFO
    iic_write(MPU_INTBP_CFG_REG,0X80); //INT引脚低电平有效
    res=iic_read(MPU_DEVICE_ID_REG);
    if(res==SlaveAddr)//器件ID正确
    {
        iic_write(MPU_PWR_MGMT1_REG,0X01); //设置CLKSEL,PLL X轴为参考
        iic_write(MPU_PWR_MGMT2_REG,0X00); //加速度与陀螺仪都工作
        MPU_Set_Rate(50);                       //设置采样率为50Hz
    }else return 1;
    return 0;
}


//设置MPU6050陀螺仪传感器满量程范围
//fsr:0,±250dps;1,±500dps;2,±1000dps;3,±2000dps
//返回值:0,设置成功
//    其他,设置失败
void MPU_Set_Gyro_Fsr(uint8_t fsr)
{
    iic_write(MPU_GYRO_CFG_REG,fsr<<3);//设置陀螺仪满量程范围
}
//设置MPU6050加速度传感器满量程范围
//fsr:0,±2g;1,±4g;2,±8g;3,±16g
//返回值:0,设置成功
//    其他,设置失败
void MPU_Set_Accel_Fsr(uint8_t fsr)
{
    iic_write(MPU_ACCEL_CFG_REG,fsr<<3);//设置加速度传感器满量程范围
}
//设置MPU6050的数字低通滤波器
//lpf:数字低通滤波频率(Hz)
//返回值:0,设置成功
//    其他,设置失败
void MPU_Set_LPF(uint16_t lpf)
{
    uint8_t data=0;
    if(lpf>=188)data=1;
    else if(lpf>=98)data=2;
    else if(lpf>=42)data=3;
    else if(lpf>=20)data=4;
    else if(lpf>=10)data=5;
    else data=6;
    iic_write(MPU_CFG_REG,data);//设置数字低通滤波器
}
//设置MPU6050的采样率(假定Fs=1KHz)
//rate:4~1000(Hz)
//返回值:0,设置成功
//    其他,设置失败
void MPU_Set_Rate(uint16_t rate)
{
    uint8_t data;
    if(rate>1000)rate=1000;
    if(rate<4)rate=4;
    data=1000/rate-1;
    iic_write(MPU_SAMPLE_RATE_REG,data);  //设置数字低通滤波器
    MPU_Set_LPF(rate/2); //自动设置LPF为采样率的一半
}




int Get16Bit (uint8_t address)
{
    uint8_t ho,lo;
	ho = iic_read(address);
	lo = iic_read(address+1);
	return (ho<<8)+lo;
}

// X/Y/Z-Axis Acceleration
int GetAccelX ()
{
	return Get16Bit(MPU_ACCEL_XOUTH_REG);
}
int GetAccelY ()
{
	return Get16Bit(MPU_ACCEL_YOUTH_REG);
}
int GetAccelZ ()
{
	return Get16Bit(MPU_ACCEL_ZOUTH_REG);
}

// X/Y/Z-Axis Angular velocity
int GetAnguX ()
{
	return Get16Bit(MPU_GYRO_XOUTH_REG);
}
int GetAnguY ()
{
	return Get16Bit(MPU_GYRO_YOUTH_REG);
}
int GetAnguZ ()
{
	return Get16Bit(MPU_GYRO_ZOUTH_REG);
}
