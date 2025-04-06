#ifndef __DELAY_H_
#define __DELAY_H_

#include "main.h"

void Delay_Init(void);
void Delay_us(uint32_t nus); // 定时us
void Delay_ms(uint16_t nms);

#endif
