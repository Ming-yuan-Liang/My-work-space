#ifndef __BSP_USART_H_
#define __BSP_USART_H_

#define DMA_USART 1

#include "main.h"

void USART1_UART_Init(void);
void DMA_Init(void);

void USART1_DataByte(uint8_t data_byte);
void USART1_DataString(uint8_t *data_str, uint16_t datasize);

#endif
