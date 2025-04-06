#include "bsp.h"

extern uint16_t g_car_time;

void BSP_Init(void)
{
	Bsp_Tim_Init();
	PID_Param_Init();//电机PID初始化
	Delay_Init();
	printf("hello \r\n");
}


void BSP_Loop(void)
{

	Irrmote_car();
	if(g_car_time==0)
	{
		wheel_State(MOTION_STOP,0);
	}


}
