/*
 * bsp.c
 *
 *  Created on: Oct 9, 2023
 *      Author: YB-101
 */

#include "bsp.h"

void BSP_Init(void)
{
	Set_Buzzer(0); // 关闭蜂鸣器 turn off the buzzer
}

void BSP_Loop(void)
{
	Set_Buzzer(1);	// 开启蜂鸣器 turn on the buzzer
	HAL_Delay(200); // 延时200ms
	Set_Buzzer(0);	// 关闭蜂鸣器 turn off the buzzer
	HAL_Delay(200);
}
