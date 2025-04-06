#include "bsp.h"

// Hardware Initialization
// Parameter:None

void BSP_Init(void)
{
	Delay_Init();
	Bsp_Tim_Init();
	PID_Param_Init(); // 电机PID初始化 Motor PID initialization
}

// Loop Run Function
// Parameter:None

void BSP_Loop(void)
{

	Ultrasonic_servo_avoidance(20); // 设置超声波避障距离为20cm Set the ultrasonic obstacle avoidance distance to 20cm
}
