#include "bsp.h"


void BSP_Init(void)
{

	Bsp_Tim_Init();
	PID_Param_Init();//电机PID初始化 Motor PID initialization
	// 这个库初始化完成会有0xff的数据
	// After the initialization of this library is completed, there will be 0xff data sent
	USART2_UART_Init();
}


void BSP_Loop(void)
{
	Change_state();//根据k210发来的不同指令进行不同的动作 perform different actions according to different instructions sent by k210




}
