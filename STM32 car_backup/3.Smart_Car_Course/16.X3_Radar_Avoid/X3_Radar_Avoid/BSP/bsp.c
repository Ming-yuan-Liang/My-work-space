#include "bsp.h"

//Hardware Initialization
//Parameter:None
void BSP_Init(void)
{
	Bsp_Tim_Init();
	PID_Param_Init();//电机PID初始化

	USART3_Init();
	HAL_Delay(1000);
}


//Loop Run Function
//Parameter:None
void BSP_Loop(void)
{
	Car_Avoid();
	HAL_Delay(20);

}

