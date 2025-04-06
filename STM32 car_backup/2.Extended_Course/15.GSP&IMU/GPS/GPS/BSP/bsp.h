/*
 * bsp.h
 *
 *  Created on: Oct 25, 2023
 *      Author: YB-101
 */

#ifndef BSP_H_
#define BSP_H_

#include "bsp_usart1.h"
#include "gps.h"
#include "main.h"

void Bsp_Init(void);
void Bsp_Loop(void);

#endif /* BSP_H_ */
