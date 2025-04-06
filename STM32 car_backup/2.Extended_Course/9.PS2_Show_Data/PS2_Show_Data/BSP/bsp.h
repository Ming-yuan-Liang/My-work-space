#ifndef __BSP_H_
#define __BSP_H_

#include <stdio.h>

#include "main.h"
#include "usart.h"
#include "gpio.h"
#include "delay.h"
#include "bsp_ps2.h"
#include "bsp_usart.h"

void BSP_Init(void);
void BSP_Loop(void);

void PS2_Data_Show(void);

#endif
