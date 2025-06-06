#include "bsp_usart.h"

UART_HandleTypeDef huart1;
uint8_t RxTemp = 0;
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

/**
 * @brief USART1 Initialization Function
 * @param None
 * @retval None
 */
void USART1_UART_Init(void)
{
  // Start receiving interrupt 启动接收中断
  HAL_UART_Receive_IT(&huart1, (uint8_t *)&RxTemp, 1);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{

  UNUSED(huart);

  HAL_UART_Receive_IT(&huart1, (uint8_t *)&RxTemp, 1);

  HAL_UART_Transmit(&huart1, (uint8_t *)&RxTemp, 1, 0xFFFF);
}
