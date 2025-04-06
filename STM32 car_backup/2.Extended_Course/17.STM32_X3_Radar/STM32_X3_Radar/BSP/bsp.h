#ifndef __BSP_H_
#define __BSP_H_

#include <math.h>
#include <string.h>
#include "main.h"
#include "usart.h"
#include "gpio.h"
#include "bsp_usart1.h"
#include "bsp_usart3.h"
#include "bsp_x3_radar.h"
#include "bsp_buzzer.h"

typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8;

void BSP_Init(void);
void BSP_Loop(void);

#endif
