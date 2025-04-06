/*
 * bsp.h
 *
 *  Created on: 2023年10月8日
 *      Author: YB-101
 */

#ifndef BSP_H_
#define BSP_H_

#include "pwm_servo.h"
#include "bsp_tim.h"
#include "main.h"

void BSP_Init(void);
void BSP_Loop(void);

#endif /* BSP_H_ */
