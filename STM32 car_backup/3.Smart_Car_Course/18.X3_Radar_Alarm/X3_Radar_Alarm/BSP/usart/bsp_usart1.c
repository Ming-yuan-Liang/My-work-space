#include "bsp_usart1.h"

#define USART_DEBUG huart1

#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif

PUTCHAR_PROTOTYPE
{
  HAL_UART_Transmit(&USART_DEBUG, (uint8_t *)&ch, 1, 0xFFFF); // 阻塞方式打印,串口x
  return ch;
}

// 发送一个字节
// data_str：数据
// datasize：数据长度
// Send a Byte
// Data_ Str: Data
// Datasize: data length
void USART1_Send(uint8_t *data_str, uint16_t datasize)
{
  HAL_UART_Transmit(&huart1, (uint8_t *)data_str, datasize, 0xFFFF);
}
