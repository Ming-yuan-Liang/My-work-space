#include "bsp.h"

//Hardware Initialization
//Parameter:None
void BSP_Init(void)
{

	Bsp_Tim_Init();//电机相关部分初始化 Initialization of motor related parts
	PID_Param_Init();//电机PID初始化 Motor PID initialization



	USART2_UART_Init();


}

uint8_t g_key_flag =0; //1：小车开始巡线运动 0：小车停止巡线运动 1: the car starts patrolling. 0: the car stops patrolling.
//Loop Run Function
//Parameter:None
void BSP_Loop(void)
{
	if(Key1_State(1))
	{
		g_key_flag = !g_key_flag;
	}

	if(g_key_flag == 0)
	{
		Motion_Set_Speed(0,0,0,0);
		APP_K210X_Init();//电机PID重置 Motor PID reset

	}
	else
	{
		APP_K210X_Line_PID();
	}

}
