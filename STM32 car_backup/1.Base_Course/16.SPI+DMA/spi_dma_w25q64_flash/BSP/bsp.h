/*
 * bsp.h
 *
 *  Created on: 2023年10月10日
 *      Author: YB-101
 */

#ifndef BSP_H_
#define BSP_H_

#include "main.h"
#include "dma.h"
#include "spi.h"
#include "usart.h"
#include "gpio.h"
#include "bsp_key.h"
#include "bsp_usart.h"
#include "bsp_flash_W25Q64.h"
#include "bsp_spi_dma.h"
#include <string.h>


void BSP_Init(void);
void BSP_Loop(void);

#endif /* BSP_H_ */
