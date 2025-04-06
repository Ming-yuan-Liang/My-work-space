#ifndef __BSP_H_
#define __BSP_H_

#include "main.h"
#include "adc.h"
#include "usart.h"
#include "gpio.h"
#include "bsp_usart.h"
#include "bsp_vol.h"

void BSP_init(void);
void BSP_Loop(void);

#endif
