/*
 * bsp.h
 *
 *  Created on: 2023年10月8日
 *      Author: YB-101
 */

#ifndef BSP_H_
#define BSP_H_

#include <stdio.h>
#include <string.h>

#include "main.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "pwm_servo.h"
#include "bsp_tim.h"

#include "bsp_k210.h"
#include "app_k210.h"
#include "bsp_key.h"
#include "bsp_PID_servo.h"
#include "bsp_usart1.h"
#include "bsp_usart2.h"


#define LED2_ON   HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET)
#define LED2_OFF  HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET)


void BSP_Init(void);
void BSP_Loop(void);

#endif /* BSP_H_ */
