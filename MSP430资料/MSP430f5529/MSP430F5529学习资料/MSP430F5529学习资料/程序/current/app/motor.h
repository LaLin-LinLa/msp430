/*
 * motor.h
 *
 *  Created on: 2021Äê8ÔÂ3ÈÕ
 *      Author: hp
 */

#ifndef APP_MOTOR_H_
#define APP_MOTOR_H_

void motor_init(void);
#define right_motor_head P6OUT |= BIT3;P3OUT &=~ BIT2;
#define right_motor_back P6OUT |= BIT4;P3OUT &=~ BIT1;
#define right_motor_stop P6OUT &=~ BIT6;P3OUT &=~ BIT2;

#define left_motor_head  P3OUT |= BIT5;P3OUT &=~ BIT6;
#define left_motor_back  P3OUT |= BIT6;P3OUT &=~ BIT5;
#define left_motor_stop  P3OUT &=~ BIT5;P3OUT &=~ BIT6;
#define head()  right_motor_head;left_motor_head;
#define right() right_motor_back;left_motor_head;
#define left()  right_motor_head;left_motor_back;
#define back()  right_motor_back;left_motor_back;
#define stop()  right_motor_stop;left_motor_stop;

#endif /* APP_MOTOR_H_ */
