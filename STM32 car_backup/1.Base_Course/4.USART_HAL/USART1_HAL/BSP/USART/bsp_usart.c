#include "bsp_usart.h"

/**
 * @brief USART1 Initialization Function
 * @param None
 * @retval None
 */
void USART1_UART_Init(void)
{
	LL_USART_EnableIT_RXNE(USART1); // Start receiving interrupt 启动接收中断
}

void USART1_IRQHandler(void)
{
	uint8_t rx1_temp;
	if (LL_USART_IsEnabledIT_RXNE(USART1)) // Determine if there is any interruption information 判断是否有中断信息
	{
		// LL_USART_ClearFlag_RXNE(USART1); //clear interrupt 清除中断
		rx1_temp = LL_USART_ReceiveData8(USART1); // Read information and clear interrupts 读取信息并清除中断
		USART1_DataByte(rx1_temp);				  // send data 发送数据
	}
}

// Send a Byte 发送一个字节
void USART1_DataByte(uint8_t data_byte)
{
	while (!LL_USART_IsActiveFlag_TXE(USART1))
	{
	};
	LL_USART_TransmitData8(USART1, data_byte);
}

// Set to send a string 设置发送一个字符串
void USART1_DataString(uint8_t *data_str, uint16_t datasize)
{
	for (uint8_t len = 0; len < datasize; len++)
	{
		USART1_DataByte(*(data_str + len));
	}
}
