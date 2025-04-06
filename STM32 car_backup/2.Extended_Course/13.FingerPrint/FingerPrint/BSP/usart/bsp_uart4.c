#include "bsp_uart4.h"

// Serial port receive buffer 串口接收缓存区
u8 UART4_RX_BUF[UART4_MAX_RECV_LEN]; 				//Receive buffer, maximum USART2_MAX_RECV_LEN bytes 接收缓冲,最大USART2_MAX_RECV_LEN个字节.
u8 UART4_TX_BUF[UART4_MAX_SEND_LEN]; 			   //Send buffer,maximum USART2_MAX_SEND_LEN bytes 发送缓冲,最大USART2_MAX_SEND_LEN字节

//通过判断接收连续2个字符之间的时间差不大于10ms来决定是不是一次连续的数据.
//如果2个字符接收间隔超过10ms,则认为不是1次连续数据.也就是超过10ms没有接收到
//任何数据,则表示此次接收完毕.
//接收到的数据状态
//[15]:0,没有接收到数据;1,接收到了一批数据.
//[14:0]:接收到的数据长度
//Determine whether a continuous data is received by determining that the time difference between two consecutive characters is not greater than 10ms
//If the interval between receiving two characters exceeds 10ms, it is considered that there is not one consecutive data. That is, if the interval exceeds 10ms, no data is received
//Any data indicates that the reception has been completed
//Received data status
//[15] : 0, no data received; 1. Received a batch of data
//[14:0]: Received data length
vu16 UART4_RX_STA=0;

//需要把stm32f1xx_it.c的同名函数注释掉.
//串口4中断函数
//Need to convert stm32f1xx_ Comment out the function with the same name in it. c
//Serial port 4 interrupt function
void UART4_IRQHandler(void)
{
	uint8_t rx4_temp;
	if(LL_USART_IsActiveFlag_RXNE(UART4) == SET) //Determine if there is a receiving flag and continue the message 判断是否有接收标志就续信息
	{
		rx4_temp = LL_USART_ReceiveData8(UART4);//Read information and clear interrupts 读取信息并清除中断
//		UART4_DataByte(rx4_temp);//Baudrate:57600

		if(UART4_RX_STA<UART4_MAX_RECV_LEN)	    //Can also receive data 还可以接收数据
		{
				TIM6_Clear_CNT();			   //Counter clear 计数器清空

				if(UART4_RX_STA==0) 			//Enable timer 6 interrupt 使能定时器6的中断
				{
					__HAL_TIM_CLEAR_IT(&htim6, TIM_IT_UPDATE);//Clearing the interrupt without adding this sentence will immediately enter the interrupt 清除中断 不加这句会立刻进入中断
					TIM6_Open();			   //Enable Timer 6 使能定时器6
				}
				//Record received values 记录接收到的值
				UART4_RX_BUF[UART4_RX_STA++]=rx4_temp;
		}else
		{
			UART4_RX_STA|=1<<15;				//Force mark receipt completion 强制标记接收完成
		}

	}
}

//Serial port initialization 串口初始化
void UART4_Init(void)
{
	LL_USART_EnableIT_RXNE(UART4);//Start receiving interrupt 启动接收中断
}

//Send a Byte 发送一个字节
void UART4_DataByte(uint8_t data_byte)
{
	 while(!LL_USART_IsActiveFlag_TXE(UART4)){};
	  LL_USART_TransmitData8(UART4,data_byte);
}


//Set to send a string 设置发送一个字符串
void UART4_DataString(uint8_t * data_str, uint16_t datasize)
{
    for (uint8_t len = 0; len < datasize; len++)
    {
        UART4_DataByte(*(data_str + len));
    }
}

