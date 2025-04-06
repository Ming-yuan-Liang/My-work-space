#include "bsp.h"

//Hardware Initialization
//Parameter:None
void BSP_Init(void)
{
	// Ms, us level delay initialization ms、us级延迟初始化
	Delay_Init();

	// 串口初始化
	USART1_UART_Init();

	// Serial port initialization MPU6050-GPIO初始化
	MPU6050_GPIO_Init();

	// MPU self check initialization MPU自检初始化
	MPU6050_Init();
}

//Loop Run Function
//Parameter:None
void BSP_Loop(void)
{
	// Print mpu data 打印mpu数据
	MPU6050_Pose();
	HAL_Delay(300);
}
