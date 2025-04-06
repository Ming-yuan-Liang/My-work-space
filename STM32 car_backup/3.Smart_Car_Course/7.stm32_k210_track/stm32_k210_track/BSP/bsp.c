/*
 * bsp.c
 *
 *  Created on: 2023年10月8日
 *      Author: YB-101
 */

#include "bsp.h"

// Hardware Initialization
// Parameter:None
void BSP_Init(void)
{
	Bsp_TIM7_Init();
	PwmServo_Set_Angle_All(90,90,90,90);//舵机角度初始化归中

	APP_K210X_Y_Init();//k210PID初始化

	USART2_UART_Init();

}

uint8_t g_key_flag =0; //1：云台开始追踪 0：云台停止追踪
// Loop Run Function
// Parameter:None
void BSP_Loop(void)
{
	if(Key1_State(1))
	{
		g_key_flag = !g_key_flag;
		LED2_ON;
	}

	if(g_key_flag == 0)
	{
		LED2_OFF;
		APP_K210X_Y_Init();//K210-PID重置

	}
	else
	{
		APP_K210X_Y_Line_PID();
	}
}
