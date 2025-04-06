#include "bsp.h"


void BSP_Init(void)
{
	Bsp_Tim_Init();
	PID_Param_Init();//电机PID初始化 Motor PID initialization
	Delay_Init();
}


void BSP_Loop(void)
{

	Ultrasonic_follow(50,20);//设置跟随最大跟随距离和跟随的保持的最小距离 Set the maximum following distance and the minimum distance for following to maintain
}
