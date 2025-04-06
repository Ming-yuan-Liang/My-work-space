/*
 * bsp_usart.c
 *
 *  Created on: 2023年10月11日
 *      Author: YB-101
 */

#include "bsp_usart1.h"

char RxBuffer1[RXBUFFERSIZE]; // 接收数据 Receive data

_SaveData Save_Data;

uint8_t Uart1_Rx_Cnt = 0; // 接收缓冲计数 Receive buffer count

uint8_t RxTemp1 = 0;

#define USART_DEBUG1 huart1

#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif

PUTCHAR_PROTOTYPE
{
	HAL_UART_Transmit(&USART_DEBUG1, (uint8_t *)&ch, 1, 0xFFFF); // 阻塞方式打印,串口x
	return ch;
}

void Bsp_UART1_Init(void)
{
	HAL_UART_Receive_IT(&huart1, (uint8_t *)&RxTemp1, 1);
	CLR_Buf();
}

void CLR_Buf(void) // 串口缓存清理 Serial port cache cleaning
{
	memset(RxBuffer1, 0x00, sizeof(RxBuffer1)); // 清空 Clear
	Uart1_Rx_Cnt = 0;
}

void clrStruct()
{
	Save_Data.isGetData = false;
	Save_Data.isParseData = false;
	Save_Data.isUsefull = false;
	memset(Save_Data.GPS_Buffer, 0, GPS_Buffer_Length); // 清空 清空
	memset(Save_Data.UTCTime, 0, UTCTime_Length);
	memset(Save_Data.latitude, 0, latitude_Length);
	memset(Save_Data.N_S, 0, N_S_Length);
	memset(Save_Data.longitude, 0, longitude_Length);
	memset(Save_Data.E_W, 0, E_W_Length);
}

uint8_t Hand(char *a) // 串口命令识别函数 Serial port command identification function
{
	if (strstr(RxBuffer1, a) != NULL)
		return 1;
	else
		return 0;
}

/*重写接收回调函数 Override the receive callback function*/
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{

	UNUSED(huart);

	if (huart->Instance == USART1)
	{

		if (RxTemp1 == '$')
		{
			Uart1_Rx_Cnt = 0;
		}
		RxBuffer1[Uart1_Rx_Cnt++] = RxTemp1;
		if (RxBuffer1[0] == '$' && RxBuffer1[4] == 'M' && RxBuffer1[5] == 'C') // 确定是否收到"GPRMC/GNRMC"这一帧数据 Determine whether the "GPRMC/GNRMC" frame data is received
		{
			if (RxTemp1 == '\n')
			{
				memset(Save_Data.GPS_Buffer, 0, GPS_Buffer_Length);	   // 清空 Clear
				memcpy(Save_Data.GPS_Buffer, RxBuffer1, Uart1_Rx_Cnt); // 保存数据 save data
				Save_Data.isGetData = true;
				Uart1_Rx_Cnt = 0;
				memset(RxBuffer1, 0, RXBUFFERSIZE); // 清空 Clear
			}
		}
		if (Uart1_Rx_Cnt >= RXBUFFERSIZE)
		{
			Uart1_Rx_Cnt = RXBUFFERSIZE;
		}
	}

	HAL_UART_Receive_IT(&huart1, (uint8_t *)&RxTemp1, 1); // 再开启接收中断 Turn on receive interrupt again
}
