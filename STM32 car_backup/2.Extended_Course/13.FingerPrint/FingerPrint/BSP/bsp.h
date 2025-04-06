#ifndef __BSP_H_
#define __BSP_H_

#include <stdio.h>
#include <string.h>

#include "main.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

#include "bsp_uart4.h"
#include "bsp_time.h"
#include "bsp_key.h"
#include "malloc.h"

#include "bsp_Finger.h"
#include "app_Finger.h"
extern u32 AS608Addr;//指纹模块地址

#define delay_ms(x) HAL_Delay(x)

void BSP_Init(void);
void BSP_Loop(void);

#endif

