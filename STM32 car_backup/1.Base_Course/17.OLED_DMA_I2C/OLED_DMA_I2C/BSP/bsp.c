#include "bsp.h"

// Hardware Initialization
// Parameter:None
void BSP_Init(void)
{
	OLED_Init();
	OLED_Draw_Line("OLED init success!", 1, false, true);
	OLED_Draw_Line("yahboom !", 2, false, true);
	OLED_Draw_Line("This is a DMA+I2c!", 3, false, true);
}

// Loop Run Function
// Parameter:None
void BSP_Loop(void)
{
}
