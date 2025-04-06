#include "bsp_wwdg.h"

// 函数功能:窗口看门狗回调函数
// 传入参数：窗口看门狗初始化结构体
// Function function: Window watchdog callback function
// Incoming parameter: Window watchdog initialization structure
void HAL_WWDG_EarlyWakeupCallback(WWDG_HandleTypeDef *hwwdg)
{
	HAL_WWDG_Refresh(hwwdg);					  /* Update Window Watchdog Values 更新窗口看门狗值 */
	HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin); /* LED1 flashing LED1闪烁 */
}
