#include "bsp.h"

// Hardware Initialization
// Parameter:None
void BSP_Init(void)
{
	USART1_UART_Init();
	OLED_Init();
	printf("This is an experiment to collect ELE data. \r\n");
	OLED_Draw_Line("oled init success!", 1, true, true);
}

// Loop Run Function
// Parameter:None
void BSP_Loop(void)
{
	EleDataDeal();
	HAL_Delay(100);
}
