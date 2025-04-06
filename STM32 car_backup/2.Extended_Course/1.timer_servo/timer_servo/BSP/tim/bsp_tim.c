/*
 * bsp_tim.c
 *
 *  Created on: Oct 18, 2023
 *      Author: YB-101
 */

#include "bsp_tim.h"

/*
 * 初始化tim7
 * Initialize tim7
 * */
void Bsp_TIM7_Init(void)
{
  HAL_TIM_Base_Start_IT(&htim7);
}
