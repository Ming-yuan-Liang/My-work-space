#include "bsp.h"

// Hardware Initialization
// Parameter:None
void BSP_Init(void)
{
	USART3_Init();
}

int avag= 0;

// Loop Run Function
// Parameter:None
void BSP_Loop(void)
{

	for (u16 i = 0; i < 360; i++) // Subscripts start from 0 下标从0开始
	{
		if (X3dis[i] != 0)
		{
			printf("angle : %d\t  dis: %d \r\n",i+1,X3dis[i]);
		}
	}


	printf("#########################\r\n");
	HAL_Delay(500);
}
