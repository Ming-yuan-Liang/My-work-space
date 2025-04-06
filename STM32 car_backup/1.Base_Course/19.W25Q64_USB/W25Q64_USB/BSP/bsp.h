#ifndef __BSP_H_
#define __BSP_H_

#define bool _Bool
#define true 1
#define false 0

#define u8 uint8_t
#define u16 uint16_t
#define u32 uint32_t
#define __IO volatile

#include <string.h>
#include "main.h"
#include "i2c.h"
#include "spi.h"
#include "usb_device.h"
#include "gpio.h"

#include "bsp_stm32_usb.h"
#include "bsp_flash_W25Q64.h"
#include "bsp_oled.h"

void BSP_Init(void);
void BSP_Loop(void);

#define CS_LOW HAL_GPIO_WritePin(FLASH_SPI_CS_GPIO_Port, FLASH_SPI_CS_Pin, GPIO_PIN_RESET);
#define CS_HIGH HAL_GPIO_WritePin(FLASH_SPI_CS_GPIO_Port, FLASH_SPI_CS_Pin, GPIO_PIN_SET);

#endif
