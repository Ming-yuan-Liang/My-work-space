/*
 * app_ultrasonic.c
 *
 *  Created on: Oct 26, 2023
 *      Author: YB-101
 */


#include "app_ultrasonic.h"

/*
 * 避障函数
 * uint16_t distance： 避障的距离 单位：cm
 *
 *obstacle avoidance function
 *uint16_t distance: obstacle avoidance distance unit: cm
 * */
void Ultrasonic_avoidance(uint16_t distance)
{
	uint16_t dis;
	dis=Get_distance();
	if(distance >2.0 && dis < distance )
		{
			//小车停止 Car stops
			wheel_State(MOTION_STOP,0);
			HAL_Delay(500);

			//小车后退 Car backs up
			wheel_State(MOTION_BACK,500);
			HAL_Delay(1000);

			//小车左转 Car turns left
			Motion_Set_Speed(-100,-100,400,400);
			HAL_Delay(500);
		}
		else
		{
			//小车前进 The car moves forward
			wheel_State(MOTION_RUN,250);
		}


}

/*
 * 跟随函数
 * uint16_t Max_distance：跟随的最大距离。大于这个距离，小车将不再跟随
 * uint16_t Min_distance：跟随的保持的最小距离。小于这个距离，小车会后退。因小车有惯性。建议取这个值的+1和-1.速度越大，这取值范围就需要越大
 *
 * follow function
 * uint16_t Max_distance: The maximum distance to follow. Greater than this distance, the car will no longer follow
 * uint16_t Min_distance: The minimum distance maintained by following. If the distance is less than this distance, the car will move backward.
 * Because the car has inertia. It is recommended to take +1 and -1 of this value. The greater the speed, the larger the value range needs to be.
 * */

void Ultrasonic_follow(uint16_t Max_distance,uint16_t Min_distance)
{
	uint16_t dis;
	dis=Get_distance();
	uint16_t Middle_dis= (Max_distance+Min_distance)/2;

	if(dis <Min_distance)
	{
	wheel_State(MOTION_BACK,250);
	}

	else if(dis >Middle_dis && dis < Max_distance )
	{
	wheel_State(MOTION_RUN,250);
	}
	else
	{
		wheel_State(MOTION_STOP,0);
	}

}
