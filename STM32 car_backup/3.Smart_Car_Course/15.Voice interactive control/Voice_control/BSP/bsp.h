#ifndef __BSP_H_
#define __BSP_H_


#include "stdio.h"
#include "main.h"
#include "tim.h"
#include "gpio.h"
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "bsp_encoder.h"
#include "bsp_motor.h"
#include "bsp_tim.h"
#include "bsp_PID_motor.h"
#include "app_motor.h"
#include "bsp_rgb.h"
#include "bsp_two_wheat.h"
#include "bsp_usrt4.h"



typedef enum _control_rgb
{
	close_light = 10,
	red_light,
	green_light,
	blue_light,
	yellow_light

} Control_RGB_t;

typedef enum _control_motor
{
	car_stop = 1,
	stop,
	sleep,
	car_forward,
	car_back,
	car_left,
	car_right,
	left_spin,
	right_spipn,
	parking1,
	parking2

} Control_MOTOR_t;
typedef enum _control_speed
{
	up = 95,
	down

} Control_Speed_t;

void BSP_Init(void);
void BSP_Loop(void);
void Change_RGB(Control_RGB_t rgb_flag);
void Control_Car(Control_MOTOR_t car_state );
void Control_speed( Control_Speed_t ctrl_speed);
#endif
