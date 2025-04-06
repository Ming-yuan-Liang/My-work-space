/*
 * pwm_servo.h
 *
 *  Created on: Sep 22, 2023
 *      Author: YB-101
 */

#ifndef PWM_SERVO_H_
#define PWM_SERVO_H_

#include "main.h"

#define MAX_PWM_SERVO 4

#define USE_SERVO_J1
#define USE_SERVO_J2
#define USE_SERVO_J3
#define USE_SERVO_J4

#define SERVO_1_HIGH() HAL_GPIO_WritePin(GPIOB, S1_Pin, GPIO_PIN_SET)
#define SERVO_1_LOW() HAL_GPIO_WritePin(GPIOB, S1_Pin, GPIO_PIN_RESET)

#define SERVO_2_HIGH() HAL_GPIO_WritePin(GPIOB, S2_Pin, GPIO_PIN_SET)
#define SERVO_2_LOW() HAL_GPIO_WritePin(GPIOB, S2_Pin, GPIO_PIN_RESET)

#define SERVO_3_HIGH() HAL_GPIO_WritePin(GPIOD, S3_Pin, GPIO_PIN_SET)
#define SERVO_3_LOW() HAL_GPIO_WritePin(GPIOD, S3_Pin, GPIO_PIN_RESET)

#define SERVO_4_HIGH() HAL_GPIO_WritePin(GPIOD, S4_Pin, GPIO_PIN_SET)
#define SERVO_4_LOW() HAL_GPIO_WritePin(GPIOD, S4_Pin, GPIO_PIN_RESET)

void PwmServo_Init(void);
void PwmServo_Set_Angle(uint8_t index, uint8_t angle);
void PwmServo_Set_Angle_All(uint8_t angle_s1, uint8_t angle_s2, uint8_t angle_s3, uint8_t angle_s4);
void PwmServo_Handle(void);

#endif /* PWM_SERVO_H_ */
