#include <bsp_tim.h>

/*
 * 打开定时器中断
 *
 * Turn on timer interrupt
 * */
void Bsp_TIM7_Init(void)
{

	HAL_TIM_Base_Start_IT(&htim7);
}

/*
 * 此回调函数可放多个定时器处理
 *
 * This callback function can be used to process multiple timers
 * */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (htim->Instance == TIM7)
	{
		if (ultrasonic_flag) // 开始测距--超声波
		{
			ultrasonic_num++;
		}
	}
}
