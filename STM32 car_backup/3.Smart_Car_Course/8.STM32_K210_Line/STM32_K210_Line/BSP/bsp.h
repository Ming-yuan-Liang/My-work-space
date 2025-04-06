#ifndef __BSP_H_
#define __BSP_H_


#include <stdio.h>
#include <string.h>

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
#include "bsp_usart2.h"
#include "bsp_k210.h"
#include "app_k210.h"
#include "bsp_key.h"

void BSP_Init(void);
void BSP_Loop(void);

#endif
