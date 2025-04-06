#include "bsp.h"

uint16_t ID;
uint8_t buff_wirte[] = {"yahboom spi+dma experiment"};
uint8_t buff_read[50];
uint8_t g_count = 0;

void Flash_Test(void)
{
	// 先擦后写
	Spi_Flash_Erase_Sector(0);							// 擦除删去，只有擦除才能写进去数据
	Spi_Flash_Write(buff_wirte, 0, sizeof(buff_wirte)); // 写入数据，0扇区，字节大小

	Spi_Flash_Read(buff_read, 0, sizeof(buff_read)); // 读第0扇区

	if (strncmp((char *)buff_read, (char *)buff_wirte, sizeof(buff_wirte)) == 0)
	{
		printf("buff : %s\r\n", buff_read);
		printf("The W25q64 variable is consistent with the program variable\r\n");
	}
}

void BSP_Init(void)
{

	Bsp_UART1_Init();
	W25Q64_Init();

	if (SPI_FLASH_TYPE != W25Q64)
	{
		while (1)
		{
			printf("W25Q64 no find! maybe it bad! please reset!!!");
		}
	}
	else
	{
		printf("W25Q64 find!\r\n");
		Flash_Test();
	}
}

void BSP_Loop(void)
{

	if (Key1_State(1)) // 写操作
	{
		Spi_Flash_Erase_Sector(5);
		memset(buff_wirte, 0, sizeof(buff_wirte));
		sprintf((char *)buff_wirte, "flash conut : %d", g_count);
		Spi_Flash_Write(buff_wirte, 5 * 4096, sizeof(buff_wirte)); // 写第5扇区
		printf("write Done!\r\n Data is %s\r\n", buff_wirte);
		g_count++;
	}
	if (Key2_State(1)) // 读操作
	{
		memset(buff_read, 0, sizeof(buff_read));
		Spi_Flash_Read(buff_read, 5 * 4096, sizeof(buff_read)); // 读第5扇区
		if (strncmp((char *)buff_read, (char *)buff_wirte, sizeof(buff_wirte)) == 0)
		{
			printf(" read data is %s \r\n", buff_read);
			printf("The W25q64 variable is consistent with the program variable.\r\n");
		}
		else
		{
			printf("****W25q64 variable and program variable are different.****\r\n");
		}
	}
	if (Key3_State(1)) // 擦除操作
	{
		// 4096为一扇区
		Spi_Flash_Erase_Sector(5);
		printf("Erase Done!\r\n ");
	}
}
