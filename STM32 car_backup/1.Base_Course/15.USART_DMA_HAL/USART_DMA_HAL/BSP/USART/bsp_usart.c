#include "bsp_usart.h"

#define LEN 200

uint8_t buf[LEN];

/**
 * @brief USART1 Initialization Function
 * @param None
 * @retval None
 */
void USART1_UART_Init(void)
{
	// Receive Configuration 接收配置
	LL_DMA_SetMemoryAddress(DMA1, LL_DMA_CHANNEL_5, (uint32_t)buf);			// Set Memory Address 设置内存地址
	LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_5, sizeof(buf));				// Set maximum length 设置最大长度
	LL_DMA_SetPeriphAddress(DMA1, LL_DMA_CHANNEL_5, (uint32_t)&USART1->DR); // Set the peripheral address, which is to set the data register of the serial port 设置外设地址，也就是设置串口的数据寄存器
	LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_5);

	// Send Configuration 发送配置
	LL_DMA_SetPeriphAddress(DMA1, LL_DMA_CHANNEL_4, (uint32_t)&USART1->DR);
	LL_DMA_SetMemoryAddress(DMA1, LL_DMA_CHANNEL_4, (uint32_t)buf); // Set Memory Address 设置内存地址
	LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_4, 0);

	LL_USART_EnableIT_IDLE(USART1);
	LL_USART_EnableDMAReq_RX(USART1); // Enable DMA serial port reception 使能DMA串口接收
	LL_USART_EnableDMAReq_TX(USART1); // Enable DMA serial port transmission 使能DMA串口发送
}

void USART1_IRQHandler(void) // Serial port interrupt handling 串口中断处理
{
#if DMA_USART
	uint32_t len;
	/* Determine idle interrupt flag bit 判断空闲中断标志位 */
	if (LL_USART_IsActiveFlag_IDLE(USART1) && LL_USART_IsEnabledIT_IDLE(USART1))
	{
		LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_5);
		len = LEN - LL_DMA_GetDataLength(DMA1, LL_DMA_CHANNEL_5);

		// Send back what you received 把收到的，再发回去
		USART1_DataString(buf, len);

		/* Reset the data length and turn on DMA to receive from scratch 重新设置数据长度并打开DMA，使DMA从头开始接收 */
		LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_5, LEN);
		LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_5);

		// Clear idle interrupt flag bit 清除空闲中断标志位
		LL_USART_ClearFlag_IDLE(USART1);
	}

#else
	uint8_t rx1_temp;
	if (LL_USART_IsEnabledIT_RXNE(USART1)) // Determine if there is any interruption information 判断是否有中断信息
	{
		// LL_USART_ClearFlag_RXNE(USART1); //clear interrupt 清除中断
		rx1_temp = LL_USART_ReceiveData8(USART1); // Read information and clear interrupts 读取信息并清除中断
		USART1_DataByte(rx1_temp);				  // send data 发送数据
	}
#endif
}

// Send a Byte 发送一个字节
void USART1_DataByte(uint8_t data_byte)
{
#if DMA_USART
	while (LL_USART_IsActiveFlag_TC(USART1) == 0)
		;
	LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_4);						   // Turn off transmission 关闭传输
	LL_DMA_SetMemoryAddress(DMA1, LL_DMA_CHANNEL_4, (uint32_t)&data_byte); // Set Memory Address 设置内存地址
	LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_4, 1);
	LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_4); // Start transfer 启动传输
#else
	while (!LL_USART_IsActiveFlag_TXE(USART1))
	{
	};
	LL_USART_TransmitData8(USART1, data_byte);
#endif
}

// Set to send a string 设置发送一个字符串
void USART1_DataString(uint8_t *data_str, uint16_t datasize)
{
#if DMA_USART
	while (LL_USART_IsActiveFlag_TC(USART1) == 0)
		;
	LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_4);						 // Turn off transmission 关闭传输
	LL_DMA_SetMemoryAddress(DMA1, LL_DMA_CHANNEL_4, (uint32_t)data_str); // Set Memory Address 设置内存地址
	LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_4, datasize);				 // set length 设置长度
	LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_4);						 // Start transfer 启动传输

#else
	for (uint8_t len = 0; len < datasize; len++)
	{
		USART1_DataByte(*(data_str + len));
	}
#endif
}
