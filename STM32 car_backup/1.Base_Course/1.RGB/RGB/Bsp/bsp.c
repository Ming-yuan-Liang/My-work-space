/*
 * bsp.c
 *
 *  Created on: 2023年10月9日
 *      Author: YB-101
 */

#include "bsp.h"
#include "bsp_rgb.h"

void BSP_Init(void)
{
	RGB_OFF_ALL; // 关闭左右两边的所有RGB灯 Turn off all RGB lights on the left and right sides
}

void BSP_Loop(void)
{

	Set_RGB(RGB_R, red);   // 开启右边红色RGB探照灯 Turn on the right red RGB searchlight
	HAL_Delay(200);		   // 延时200ms
	RGB_OFF_ALL;		   // 关闭左右两边的所有RGB灯 Turn off all RGB lights on the left and right sides
	HAL_Delay(200);		   // 延时200ms
	Set_RGB(RGB_L, green); // 开启左边绿色RGB探照灯 Turn on the green RGB searchlight on the left
	HAL_Delay(200);
	RGB_OFF_ALL;
	HAL_Delay(200);
	Set_RGB(RGB_Max, purple); // 开启左右两边紫色RGB探照灯 Turn on the purple RGB searchlights on the left and right sides
	HAL_Delay(200);
	RGB_OFF_ALL;
	HAL_Delay(200);
}
