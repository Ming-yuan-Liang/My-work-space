#ifndef __BSP_H_
#define __BSP_H_

#define bool _Bool
#define true 1
#define false 0

#include "stdio.h"
#include "main.h"
#include "tim.h"
#include "gpio.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <Time.h>
#include "stm32f1xx_hal.h"

#include "bsp_encoder.h"
#include "bsp_motor.h"
#include "bsp_tim.h"
#include "bsp_PID_motor.h"
#include "app_motor.h"
#include "delay.h"
#include "bsp_ultrasonic.h"
#include "app_ultrasonic.h"
#include "bsp_usart.h"
#include "bsp_buzzer.h"
#include "bsp_rgb.h"

extern uint32_t ultrasonic_num;
extern uint8_t ultrasonic_flag;
extern uint8_t g_servo_falg;

void BSP_Init(void);
void BSP_Loop(void);
void BSP_Loop2(void);
void BSP_Loop3(void);

#endif
