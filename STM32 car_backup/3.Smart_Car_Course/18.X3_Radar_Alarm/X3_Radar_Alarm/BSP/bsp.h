#ifndef __BSP_H_
#define __BSP_H_


#define bool _Bool
#define true 1
#define false 0

#define u8 uint8_t
#define u16 uint16_t
#define u32 uint32_t
#define __IO volatile

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <Time.h>

#include "main.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

#include "bsp_encoder.h"
#include "bsp_motor.h"
#include "bsp_tim.h"
#include "bsp_PID_motor.h"
#include "app_motor.h"

#include "bsp_usart1.h"
#include "bsp_usart3.h"

#include "bsp_x3_radar.h"
#include "app_x3_radar.h"

#include "bsp_key.h"
#include "bsp_oled.h"

void BSP_Init(void);
void BSP_Loop(void);

void Car_Alarm(void);


#define BEEP_ON HAL_GPIO_WritePin(BEEP_GPIO_Port, BEEP_Pin, GPIO_PIN_SET);
#define LED1_ON HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
#define LED2_ON HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET);


#define BEEP_OFF HAL_GPIO_WritePin(BEEP_GPIO_Port, BEEP_Pin, GPIO_PIN_RESET);
#define LED1_OFF HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);
#define LED2_OFF HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET);


#endif
