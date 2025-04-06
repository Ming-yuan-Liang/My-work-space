#include "bsp.h"

void BSP_Init(void)
{
	Delay_Init();

	USART1_UART_Init();

//	Irremote_GPIO_Init();
}

void BSP_Loop(void)
{
	Print_Irrmote();
}
