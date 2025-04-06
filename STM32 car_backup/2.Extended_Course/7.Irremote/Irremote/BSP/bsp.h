#ifndef __BSP_H_
#define __BSP_H_

#include <stdio.h>

#include "main.h"
#include "usart.h"
#include "gpio.h"
#include "delay.h"
#include "bsp_usart.h"
#include "bsp_irremote.h"


void BSP_Init(void);
void BSP_Loop(void);

#endif
