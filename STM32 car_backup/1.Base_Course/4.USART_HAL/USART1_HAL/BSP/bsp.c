#include "bsp.h"

// Hardware Initialization
// Parameter:None
void BSP_Init(void)
{
	USART1_UART_Init();
}

// Loop Run Function
// Parameter:None
void BSP_Loop(void)
{
	HAL_Delay(200); // ms
}
