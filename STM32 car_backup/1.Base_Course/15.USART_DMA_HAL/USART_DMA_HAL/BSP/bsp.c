#include "bsp.h"

// Hardware Initialization
// Parameter:None
void BSP_Init(void)
{
	USART1_UART_Init();
	USART1_DataString("USRT+DMA Class!\r\n", 17);
}

// Loop Run Function
// Parameter:None
void BSP_Loop(void)
{
	HAL_Delay(300);
}
