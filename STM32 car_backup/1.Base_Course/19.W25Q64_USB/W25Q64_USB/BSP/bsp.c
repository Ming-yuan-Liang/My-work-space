#include "bsp.h"

// 注意：该程序需要在自动生成的usbd_storage_if.c、main.c 添加函数操作
// Note: This program needs to be updated in the automatically generated USB_ Storage_ If.c, main.c add function operation

// Hardware Initialization
// Parameter:None
void BSP_Init(void)
{
	OLED_Init();
	W25Q64_Init();

	if (SPI_FLASH_TYPE != W25Q64)
	{
		while (1)
		{
			OLED_Draw_Line("W25Q64 no find!", 1, false, true);
		}
	}
	else
	{
		OLED_Draw_Line("W25Q64 find!", 1, false, true);
	}
}

// Loop Run Function
// Parameter:None
void BSP_Loop(void)
{
	VCP_Status();
}
