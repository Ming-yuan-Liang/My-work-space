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
void TIM7_IRQHandler(void)
{
	if (__HAL_TIM_GET_FLAG(&htim7, TIM_FLAG_UPDATE) != RESET) // Check if TIM update interrupt occurs 检查TIM更新中断发生与否
	{
		if (__HAL_TIM_GET_IT_SOURCE(&htim7, TIM_IT_UPDATE) != RESET) // Check if TIM6 interrupt is enabled 检查TIM6的中断是否启用
		{
			__HAL_TIM_CLEAR_IT(&htim7, TIM_IT_UPDATE); // clear interrupt 清除中断
			if (ultrasonic_flag)					   // 开始测距--超声波 Start ranging--ultrasound
			{
				ultrasonic_num++;
			}
			PwmServo_Handle();
		}
	}
}
