#include "bsp_usart3.h"

void USART3_Init(void)
{
	// 该串口只使用接受端进行雷达的接收，因此把发送端配置成普通io模式,设置雷达的转速
	// 串口默认配置也是全速输出，因此下面可不加
	// This serial port only uses the receiving end for radar reception, so configure the sending end to a normal IO mode and set the radar speed
	// The default configuration of the serial port is also full speed output, so there is no need to add
	//	LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
	//	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOD);
	//	GPIO_InitStruct.Pin = LL_GPIO_PIN_8;
	//	GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
	//	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
	//	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	//	LL_GPIO_Init(GPIOD, &GPIO_InitStruct);

	// SET: Radar rotates at full speed RESET: Radar rotates at low speed
	// SET:雷达全速转动 RESET:雷达低速转动
	//	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, SET);

	LL_USART_EnableIT_RXNE(USART3); // Start receiving interrupt 启动接收中断
}

void USART3_IRQHandler(void)
{
	uint8_t rx3_temp;
	if (LL_USART_IsActiveFlag_RXNE(USART3) == SET) // Determine if there is a receiving flag and continue the message 判断是否有接收标志就续信息
	{
		LL_USART_ClearFlag_RXNE(USART3);		  // clear interrupt 清除中断
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
