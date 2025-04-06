#include "bsp.h"

// Hardware Initialization
// Parameter:None
void BSP_Init(void)
{
	USART1_UART_Init();
	OLED_Init();
	OLED_Draw_Line("oled init success!", 1, true, true);
}

// Loop Run Function
// Parameter:None
void BSP_Loop(void)
{
	Print_CCD_data(); // Serial port printing CCD data 串口打印CCD数据

	HAL_Delay(100);
}
