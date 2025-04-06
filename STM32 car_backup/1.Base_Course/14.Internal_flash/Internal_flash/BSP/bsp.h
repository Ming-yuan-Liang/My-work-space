#ifndef __BSP_H
#define __BSP_H

#include "main.h"
#include <stdio.h>
#include "usart.h"
#include "gpio.h"
#include "bsp_key.h"
#include "bsp_flash.h"
#include "bsp_usart.h"

void BSP_Init(void);
void BSP_Loop(void);

#endif
