/*
 * bsp.h
 *
 *  Created on: 2023年10月9日
 *      Author: YB-101
 */

#ifndef BSP_H_
#define BSP_H_

#define PWM_MAX 2000

#include "main.h"
#include "tim.h"
#include "gpio.h"

#include "bsp_tim.h"
#include "bsp_rgb.h"

void BSP_Init(void);
void BSP_Loop(void);

#endif /* BSP_H_ */
