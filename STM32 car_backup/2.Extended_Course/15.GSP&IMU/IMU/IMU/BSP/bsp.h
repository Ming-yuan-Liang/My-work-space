/*
 * bsp.h
 *
 *  Created on: Oct 18, 2023
 *      Author: YB-101
 */

#ifndef BSP_H_
#define BSP_H_


#include "main.h"
#include "usart.h"
#include "gpio.h"

#include "bsp_usart1.h"
#include "bsp_usrt4.h"
#include "wit_c_sdk.h"
#include "REG.h"
#include "stdio.h"




void BSP_Init(void);
void BSP_Loop(void);




#endif /* BSP_H_ */

