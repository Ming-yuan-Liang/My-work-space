#include "bsp_usrt4.h"

void UART4_Init(void)
{

	LL_USART_EnableIT_RXNE(UART4); // Start receiving interrupt 启动接收中断
}

/**
 * @brief This function handles UART4 global interrupt.
 */
void UART4_IRQHandler(void)
{
	uint8_t rx4_temp;
	if (LL_USART_IsEnabledIT_RXNE(UART4)) // Determine if there is any interruption information 判断是否有中断信息
	{
		// LL_USART_ClearFlag_RXNE(UART4); //clear interrupt 清除中断
		rx4_temp = LL_USART_ReceiveData8(UART4); // Read information and clear interrupts 读取信息并清除中断
		WitSerialDataIn(rx4_temp);
		// USRT4_DataByte(rx4_temp);//send data 发送数据
	}
}

// Send a Byte 发送一个字节
void USRT4_DataByte(uint8_t data_byte)
{
	while (!LL_USART_IsActiveFlag_TXE(UART4))
	{
	};
	LL_USART_TransmitData8(UART4, data_byte);
}

// Set to send a string 设置发送一个字符串
void USRT4_DataString(uint8_t *data_str, uint16_t datasize)
{
	for (uint8_t len = 0; len < datasize; len++)
	{
		USRT4_DataByte(*(data_str + len));
	}
}

void Uart4_Send(uint8_t *data_str, uint16_t datasize)
{
	for (uint8_t len = 0; len < datasize; len++)
		{
			USRT4_DataByte(*(data_str + len));
		}
}
