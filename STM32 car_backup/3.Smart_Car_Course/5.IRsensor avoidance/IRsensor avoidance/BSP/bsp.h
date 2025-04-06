#ifndef __BSP_H_
#define __BSP_H_


#include "stdio.h"
#include "main.h"
#include "tim.h"
#include "gpio.h"
#include "adc.h"

#include "bsp_encoder.h"
#include "bsp_motor.h"
#include "bsp_tim.h"
#include "bsp_PID_motor.h"
#include "app_motor.h"
#include "delay.h"
#include "bsp_ultrasonic.h"
#include "app_ultrasonic.h"
#include "bsp_usart.h"
#include "bsp_iravoid.h"
#include "app_iravoid.h"



extern uint32_t ultrasonic_num;
extern uint8_t ultrasonic_flag;

void BSP_Init(void);
void BSP_Loop(void);

#endif
