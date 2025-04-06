/*
 * app_ultrasonic.c
 *
 *  Created on: Oct 26, 2023
 *      Author: YB-101
 */

#include "app_ultrasonic.h"

void Ultrasonic_servo_avoidance(uint16_t distance)
{
	float dis;
	float letf_dis;
	float right_dis;

	dis = Get_distance();
	if (distance > 2.0 && dis < distance)
	{
		// 小车停止 Car stops
		wheel_State(MOTION_STOP, 0);

		PwmServo_Set_Angle(0, 0);
		HAL_Delay(500);
		right_dis = Get_distance();

		PwmServo_Set_Angle(0, 180);
		HAL_Delay(500);
		letf_dis = Get_distance();

		printf("l:%.3f\t,R:%.3f\r\n", letf_dis, right_dis);

		PwmServo_Set_Angle(0, 90);

		if ((letf_dis < 20) && (right_dis < 20)) // 小车原地掉头 The car turned around in place.
		{
			wheel_State(MOTION_SPIN_RIGHT, 800);
			HAL_Delay(1000);
		}
		else
		{
			if (letf_dis >= right_dis)
			{
				wheel_State(MOTION_SPIN_LEFT, 500); // 小车左转 Car turns left
				HAL_Delay(1000);
			}
			else if (letf_dis < right_dis) // 小车右转 Car turns right
			{
				wheel_State(MOTION_SPIN_RIGHT, 500);
				HAL_Delay(1000);
			}
		}
	}
	else
	{
		// 小车前进 The car moves forward
		wheel_State(MOTION_RUN, 250);
	}
}
