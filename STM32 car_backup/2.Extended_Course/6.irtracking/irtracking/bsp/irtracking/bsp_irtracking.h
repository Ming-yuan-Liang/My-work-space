/*
 * bsp_irtracking.h
 *
 *  Created on: Oct 11, 2023
 *      Author: YB-101
 */

#ifndef BSP_IRTRACKING_H_
#define BSP_IRTRACKING_H_

#include "main.h"

typedef enum irtracking_pin
{
	X1 = 1, // 右边RGB探照灯 Right RGB searchlight
	X2,		// 左边RGB探照灯 Left RGB searchlight
	X3,
	X4
} Irtracking_Pin;

uint8_t Read_irtracking(Irtracking_Pin irtracking);

#endif /* BSP_IRTRACKING_H_ */
