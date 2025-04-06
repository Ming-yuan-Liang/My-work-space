#include "bsp.h"

//Hardware Initialization
//Parameter:None
void BSP_Init(void)
{
	Delay_Init();

	PID_Param_Init();//电机PID初始化 Motor PID initialization
	Bsp_Tim_Init();//电机相关定时器初始化 Motor related timer initialization

	OLED_Init();
	OLED_Draw_Line("PS2 control Car!",1,false,true);

	PS2_SetInit();//强制进入红绿模式 Forced entry into red green mode

	Motion_Set_Speed(0,0,0,0);//小车停止 Car stop

}

//Loop Run Function
//Parameter:None
void BSP_Loop(void)
{
	User_PS2_Control();
}
