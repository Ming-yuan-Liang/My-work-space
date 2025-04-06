#include "bsp.h"

//Hardware Initialization
//Parameter:None
void BSP_Init(void)
{
	//电机部分
	//Motor part
	Bsp_Tim_Init();
	PID_Param_Init();//Motor PID initialization 电机PID初始化
	APP_K210X_Y_Apriltag_Init();//K210_ PID initialization K210_PID初始化

	USART2_UART_Init();


}

uint8_t g_key_flag =0; //1：小车开始跟随  0：小车停止跟随 1: Car starts following 0: Car stops following
//Loop Run Function
//Parameter:None
void BSP_Loop(void)
{
	if(Key1_State(1))
	{
		g_key_flag = !g_key_flag;
		LED1_ON;
	}

	if(g_key_flag == 0)
	{
		LED1_OFF;
		Motion_Set_Speed(0,0,0,0);
		APP_K210X_Y_Apriltag_Init();//K210-PID重置  K210-PID reset

	}
	else
	{
		APP_K210X_Y_Line_PID();
	}

}
