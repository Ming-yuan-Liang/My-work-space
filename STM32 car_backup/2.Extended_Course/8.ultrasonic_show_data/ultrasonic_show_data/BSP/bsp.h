#ifndef __BSP_H_
#define __BSP_H_

#include "main.h"
#include "tim.h"
#include "delay.h"
#include "bsp_ultrasonic.h"
#include "bsp_tim.h"
#include "bsp_usart.h"

extern uint32_t ultrasonic_num;
extern uint8_t ultrasonic_flag;
void BSP_Init(void);
void BSP_Loop(void);

#endif
