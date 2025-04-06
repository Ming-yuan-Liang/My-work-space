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

void BSP_Init(void);
void BSP_Loop(void);

void Car_Avoid(void);

#endif
