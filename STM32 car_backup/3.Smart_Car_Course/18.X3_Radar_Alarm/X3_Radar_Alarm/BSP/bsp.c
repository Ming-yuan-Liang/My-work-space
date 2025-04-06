#include "bsp.h"

//Hardware Initialization
//Parameter:None
void BSP_Init(void)
{
	Bsp_Tim_Init();
	PID_Param_Init();//电机PID初始化 Motor PID initialization

	USART3_Init();
	OLED_Init();//OLED初始化 OLED initialization

	OLED_Draw_Line("X3 Alarm class!",1,false,true);

	HAL_Delay(1000);//等待获取雷达的信息稳定
}


//Loop Run Function
//Parameter:None
void BSP_Loop(void)
{

	Car_Alarm();
//	HAL_Delay(20);

}

