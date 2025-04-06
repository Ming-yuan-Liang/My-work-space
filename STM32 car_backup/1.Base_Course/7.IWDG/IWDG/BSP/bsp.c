#include "bsp.h"

// Hardware Initialization
// Parameter:None

void BSP_Init(void)
{

	Bsp_UART1_Init();
	printf("\n\r***** IWDG Test Start *****\n\r");
}

// Loop Run Function
// Parameter:None

void BSP_Loop(void)
{

	if (Key1_State(0))
	{
		HAL_IWDG_Refresh(&hiwdg); // 喂狗 feed the dog
		printf("\n\r Refreshes the IWDG !!!\n\r");
	}
	else
	{
		printf("\n\r IWDG no no no reload !!!\n\r"); // 重启单片机 Restart the microcontroller
	}

	HAL_Delay(800);
}
