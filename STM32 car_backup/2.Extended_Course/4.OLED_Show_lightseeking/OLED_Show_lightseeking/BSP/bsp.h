#ifndef __BSP_H_
#define __BSP_H_

#include "main.h"

void BSP_Init(void);
void BSP_Loop(void);

#define ABS(x) (((x) >= 0) ? (x) : -(x))
#define bool _Bool
#define true 1
#define false 0

#include "oled_fonts.h"
#include "bsp_oled_i2c.h"
#include "bsp_oled.h"
#include "bsp_adc.h"

#endif
