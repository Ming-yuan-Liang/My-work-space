#include "bsp_usart3.h"

void USART3_Init(void)
{

	LL_USART_EnableIT_RXNE(USART3); // Start receiving interrupt 启动接收中断
}

void USART3_IRQHandler(void)
{
	uint8_t rx3_temp;
	if (LL_USART_IsActiveFlag_RXNE(USART3) == SET) // Determine if there is a receiving flag and continue the message 判断是否有接收标志就续信息
	{
//		LL_USART_ClearFlag_RXNE(USART3);		  // clear interrupt 清除中断
		rx3_temp = LL_USART_ReceiveData8(USART3); // Read information and clear interrupts 读取信息并清除中断
		Recv_Radar(rx3_temp);
	}
}

// Send a Byte 发送一个字节
void USART3_DataByte(uint8_t data_byte)
{
	while (!LL_USART_IsActiveFlag_TXE(USART3))
	{
	};
	LL_USART_TransmitData8(USART3, data_byte);
}

// Set to send a string 设置发送一个字符串
void USART3_DataString(uint8_t *data_str, uint16_t datasize)
{
	for (uint8_t len = 0; len < datasize; len++)
	{
		USART3_DataByte(*(data_str + len));
	}
}
