#include "bsp.h"

uint16_t g_count = 0;
uint16_t g_datatempdd = 0xFFFF;

void BSP_Init(void)
{
	USART1_UART_Init();

	//  STMFLASH_Write(FLASH_SAVE_ADDR,&count,1);
	HAL_Delay(50);
	STMFLASH_Read(FLASH_SAVE_ADDR, &g_datatempdd, 1);
	if (g_datatempdd == 0xFFFF)
	{
		printf("count is 0,frist time running!!! \r\n");
	}
	else
	{
		printf("count is reading :%d \r\n", g_datatempdd);
		g_count = g_datatempdd;
	}
}

void BSP_Loop(void)
{
	if (Key1_State(1))
	{
		g_count++;
		if (g_count >= 0xff) // No more than 255, the maximum number of 16 bits is 65535 不超过255，16位的数最大是65535
		{
			g_count = 0;
		}

		STMFLASH_Write(FLASH_SAVE_ADDR, &g_count, 1); // Write in flash 写进flash
		printf("count is Add! count now : %d \r\n", g_count);
		printf("please press down key3 reading! \r\n");
	}

	if (Key2_State(1)) // zero clearing 清零
	{
		g_count = 0;
		STMFLASH_Write(FLASH_SAVE_ADDR, &g_count, 1); // zero clearing 写进flash
		printf("count is clear! count now : %d \r\n", g_count);
		printf("please press down key3 reading! \r\n");
	}

	if (Key3_State(1)) // read out 读出来
	{
		STMFLASH_Read(FLASH_SAVE_ADDR, &g_datatempdd, 1);
		printf("Read count is : %d \r\n", g_datatempdd);
		if (g_datatempdd == g_count)
		{
			printf("The flash variables are consistent with the program variables!\r\n");
		}
	}
}
