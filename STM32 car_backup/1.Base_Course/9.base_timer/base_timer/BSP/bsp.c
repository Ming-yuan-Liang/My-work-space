#include "bsp.h"

// Hardware Initialization
// Parameter:None
void BSP_Init(void)
{
	// 基本定时器开启中断
	// Basic timer start interrupt
	TIM6_Init();
}

// Loop Run Function
// Parameter:None
void BSP_Loop(void)
{
	// 本实验效果处理LED1 1s闪一次   LED2 500ms闪1次
	// 处理在bsp_tim.c文件里面
	// The effect of this experiment is to handle LED1 flashing once every 1s and LED2 flashing once every 500ms
	// Processing in BSP_tim.c file
}
