#ifndef __BSP_H_
#define __BSP_H_

#include "main.h"
#include "delay.h"
#include "dma.h"
#include "tim.h"
#include "gpio.h"
#include "bsp_ws281x.h"
#include "bsp_key.h"

void BSP_Init(void);
void BSP_Loop(void);

#endif
