#ifndef __BSP_H_
#define __BSP_H_

#define u8 uint8_t
#define u16 uint16_t
#define u32 uint32_t
#define __IO volatile

#include "main.h"
#include "spi.h"
#include "usart.h"
#include "gpio.h"
#include "bsp_key.h"
#include "stdio.h"
#include "bsp_flash_W25Q64.h"
#include "bsp_usart.h"
#include "string.h"

void BSP_Init(void);
void BSP_Loop(void);

#endif
