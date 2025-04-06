#include "bsp.h"

// Hardware Initialization
// Parameter:None
void BSP_init(void)
{
}

float g_batty_vol = 0;

// Loop Run Function
// Parameter:None
void BSP_Loop(void)
{
	g_batty_vol = Adc_Get_Battery_Volotage();
	printf("VOL = %.2f\r\n", g_batty_vol);
	HAL_Delay(50);
}
