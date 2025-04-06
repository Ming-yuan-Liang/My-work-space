#ifndef __BSP_USART3_H_
#define __BSP_USART3_H_

#include "bsp.h"

void USART3_Init(void);
void USART3_IRQHandler(void);
void USART3_DataByte(uint8_t data_byte);
void USART3_DataString(uint8_t *data_str, uint16_t datasize);

#endif
