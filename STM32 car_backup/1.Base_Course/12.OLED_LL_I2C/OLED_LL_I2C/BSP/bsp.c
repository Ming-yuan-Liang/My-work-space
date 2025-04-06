#include "bsp.h"

// Hardware Initialization
// Parameter:None
void BSP_Init(void)
{
	OLED_Init();

	OLED_Draw_Line("oled init success!", 1, true, true);
	OLED_Draw_Line("oled + I2c class!", 2, false, true);
	OLED_Draw_Line("oled show success!", 3, false, true);
}

// Loop Run Function
// Parameter:None
void BSP_Loop(void)
{
}
