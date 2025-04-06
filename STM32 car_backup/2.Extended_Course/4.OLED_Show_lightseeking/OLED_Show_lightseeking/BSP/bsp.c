#include "bsp.h"

// Hardware Initialization
// Parameter:None

void BSP_Init(void)
{

	OLED_Init();
	OLED_Draw_Line("oled init success!", 1, true, true);
}

// Loop Run Function
// Parameter:None

void BSP_Loop(void)
{
	user_lightseek_detect();
}
