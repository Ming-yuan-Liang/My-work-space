/*
 * bsp.c
 *
 *  Created on: 2023年10月8日
 *      Author: YB-101
 */

#include "bsp.h"

// Hardware Initialization
// Parameter:None
void BSP_Init(void)
{
	Bsp_TIM7_Init();
}

// Loop Run Function
// Parameter:None
void BSP_Loop(void)
{
	PwmServo_Set_Angle(0, 0); // S1舵机转到0度 S1 servo turns to 0 degrees
	HAL_Delay(500);
	PwmServo_Set_Angle(0, 45);
	HAL_Delay(500);
	PwmServo_Set_Angle(0, 90);
	HAL_Delay(500);
	PwmServo_Set_Angle(0, 135);
	HAL_Delay(500);
	PwmServo_Set_Angle(0, 180);
	HAL_Delay(500);
	PwmServo_Set_Angle(0, 135);
	HAL_Delay(500);
	PwmServo_Set_Angle(0, 90);
	HAL_Delay(500);
	PwmServo_Set_Angle(0, 45);
	HAL_Delay(500);
}
