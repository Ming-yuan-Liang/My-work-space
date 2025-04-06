#include "bsp_tim.h"

//该实验使用的是通用定时器产生中断，使用计算器模拟pwm输出,实现呼吸灯效果
//This experiment uses a General timer to generate interrupts,
//and uses a calculator to simulate PWM output to achieve a breathing light effect


/* TIM3 init function */
// 定时器3初始化
void TIM3_Init(void)
{
	HAL_TIM_Base_Start_IT(&htim3);
}


extern uint16_t pwm_val;
extern uint16_t pwm_set;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	pwm_val++;
	if(pwm_val<pwm_set)
	{
		RRGB_SET(reset,reset,reset);
		LRGB_SET(reset,reset,reset);
	}

	if(pwm_val>pwm_set)
	{
		RRGB_SET(set,reset,set);
		LRGB_SET(set,reset,set);
	}

	if(pwm_val == PWM_MAX) pwm_val = 0;

}


