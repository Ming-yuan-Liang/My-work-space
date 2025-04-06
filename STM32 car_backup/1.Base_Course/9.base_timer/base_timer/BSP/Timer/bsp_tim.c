#include "bsp_tim.h"

// 使用hal库的中断回调函数 1：使用 0：不使用
// Use HAL library's interrupt callback function 1: Use 0: Do not use
#define USE_HAL_IRQ 1

uint8_t g_time = 1; // timer counter 定时计数

// 定时器6初始化 传入参数：无
// Timer 6 initialization Incoming parameter: None
void TIM6_Init(void)
{
	// 打开定时器中断
	// Turn on timer interrupt
	HAL_TIM_Base_Start_IT(&htim6);
}

void TIM6_IRQHandler(void)
{
#if USE_HAL_IRQ
	HAL_TIM_IRQHandler(&htim6);

#else
	if (__HAL_TIM_GET_FLAG(&htim6, TIM_FLAG_UPDATE) != RESET) // Check if TIM update interrupt occurs 检查TIM更新中断发生与否
	{
		if (__HAL_TIM_GET_IT_SOURCE(&htim6, TIM_IT_UPDATE) != RESET) // Check if TIM6 interrupt is enabled 检查TIM6的中断是否启用
		{
			__HAL_TIM_CLEAR_IT(&htim6, TIM_IT_UPDATE); // clear interrupt 清除中断

			g_time++;
			if (g_time % 100 == 0) // 1s = 100*10ms
			{
				g_time = 1;
				HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
			}
			else if (g_time % 50 == 0) // 500ms = 50*10ms
			{
				HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);
			}
		}
	}

#endif
}

// 此回调函数可放多个定时器处理
// 传入参数：定时器结构体
// This callback function can handle multiple timers
// Incoming parameter: Timer structure
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (htim->Instance == TIM6)
	{
		g_time++;
	}

	if (g_time % 100 == 0) // 1s = 100*10ms
	{
		g_time = 1;
		HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
	}
	if (g_time % 50 == 0) // 500ms = 50*10ms
	{
		HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);
	}
}
