#ifndef __BSP_H_
#define __BSP_H_

#include <stdio.h>
#include <string.h>

#include "main.h"
#include "gpio.h"
#include "bsp_key.h"
#include "bsp_rgb.h"
#include "freertos.h"
#include "bsp_task.h"
#include "bsp_buzzer.h"

void BSP_Init(void);
void BSP_Loop(void);

#endif
