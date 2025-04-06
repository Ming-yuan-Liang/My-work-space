#include "bsp.h"


void BSP_Init(void)
{
	Bsp_Tim_Init();
	PID_Param_Init();//电机PID初始化 Motor PID initialization
}


void BSP_Loop(void)
{

	Ir_Ultrasonic_avoid(20);//设置避障距离为20cm Set the obstacle avoidance distance to 20cm

}
