#ifndef __BSP_H_
#define __BSP_H_

//从1开始
enum k210_msg
{
	red_light = 1,
	green_light,
	school,
	walk,
	one,
	right,
	two,
	freeSpeed,
	left,
	limitSpeed,
	horn,
	chuku_track_line,
	MAX_id
};

#include "stdio.h"
#include "string.h"
#include "main.h"
#include "tim.h"
#include "gpio.h"
#include "usart.h"
#include "stdint.h"

extern uint8_t stop_flag;
extern uint32_t n_stime ;
extern uint16_t wait_k210;
extern uint8_t bound_num;



#include "bsp_encoder.h"
#include "bsp_motor.h"
#include "bsp_tim.h"
#include "bsp_PID_motor.h"
#include "app_motor.h"
#include "bsp_k210.h"
#include "bsp_usart2.h"
#include "app_irtracking.h"
#include "bsp_irtracking.h"
#include "bsp_buzzer.h"


void BSP_Init(void);
void BSP_Loop(void);
void Leave_Stop(void);

#endif
