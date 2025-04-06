#include "bsp.h"

// Hardware Initialization
// Parameter:None
void BSP_Init(void)
{
	// 程序现象
	// 喂了狗就LED2会灭，LED1会闪
	// 不喂狗就LED1会灭，LED2会闪 说明硬件看门狗有异常
	// Procedural phenomenon
	// After feeding the dog, LED2 will extinguish and LED1 will flash
	// If the dog is not fed, LED1 will go out, and LED2 will flash, indicating that the hardware watchdog is abnormal

	HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET);
	HAL_Delay(300);
}

// Loop Run Function
// Parameter:None
void BSP_Loop(void)
{
	HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET); // turn off the light 灭灯
}
