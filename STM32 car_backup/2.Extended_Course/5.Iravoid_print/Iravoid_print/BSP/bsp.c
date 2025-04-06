#include "bsp.h"

//Hardware Initialization
//Parameter:None

void BSP_Init(void)
{
	Bsp_UART1_Init();//串口初始化 Serial port initialization

}

//Loop Run Function
//Parameter:None

void BSP_Loop(void)
{
	static uint16_t left_data = 0;
	static uint16_t right_data = 0;
	Get_Iravoid_Data(&left_data,&right_data);//串口打印采集的数据 Serial port printing of collected data
	HAL_Delay(300);
}
