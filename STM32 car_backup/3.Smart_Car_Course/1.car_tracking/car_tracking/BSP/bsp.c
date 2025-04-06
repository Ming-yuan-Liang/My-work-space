#include "bsp.h"


void BSP_Init(void)
{
	Bsp_Tim_Init();
	PID_Param_Init();//电机PID初始化 Motor PID initialization

}


void BSP_Loop(void)
{

	car_irtrack();//小车巡线 Car line patrol


}
