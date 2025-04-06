#ifndef __BSP_USART_H_
#define __BSP_USART_H_

#include "bsp.h"
#include "stdio.h"

void USART1_DataByte(uint8_t data_byte);
void USART1_DataString(uint8_t *data_str, uint16_t datasize);

#endif
