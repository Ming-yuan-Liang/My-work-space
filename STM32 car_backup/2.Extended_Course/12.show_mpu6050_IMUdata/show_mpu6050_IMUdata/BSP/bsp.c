#include "bsp.h"

//Hardware Initialization
//Parameter:None
void BSP_Init(void)
{
	// Ms, us level delay initialization ms、us级延迟初始化
	Delay_Init();

	// 串口初始化
	USART1_UART_Init();
	MPU_Init_Self();//自检


}

//Loop Run Function
//Parameter:None
void BSP_Loop(void)
{
	Printf_MPU_Data();
//	HAL_Delay(100);
}
