/*
 * bsp.c
 *
 *  Created on: 2023年10月9日
 *      Author: YB-101
 */

#include "bsp.h"

//Hardware Initialization
//Parameter:None
void BSP_Init(void)
{
	TIM3_Init();
}



uint16_t pwm_val;
uint16_t pwm_set;

//Loop Run Function
//Parameter:None
void BSP_Loop(void)
{
	static uint8_t dir = 1;

	if(dir)
	{
		HAL_Delay(1);
		pwm_set++;
		if(pwm_set == PWM_MAX) dir = 0;
	}
	if(!dir)
	{
		HAL_Delay(1);
		pwm_set--;
		if(pwm_set == 0) dir = 1;
	}

}
