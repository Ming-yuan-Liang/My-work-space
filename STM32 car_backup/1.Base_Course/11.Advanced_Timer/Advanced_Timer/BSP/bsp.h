#ifndef __BSP_H_
#define __BSP_H_

#include <stdio.h>
#include "main.h"
#include "tim.h"
#include "gpio.h"
#include "bsp_tim.h"
#include "bsp_usart.h"

void BSP_Init(void);
void BSP_Loop(void);

#endif

