/*
 * app_Iravoid.c
 *
 *  Created on: Oct 27, 2023
 *      Author: YB-101
 */

#include "app_iravoid.h"

/*
 * 超声波结合红外做避障
 * uint16_t distance 避障的距离 单位：cm
 *
 * Ultrasound combined with infrared for obstacle avoidance
 * uint16_t distance obstacle avoidance distance unit: cm
 * */
/*
void Ir_Ultrasonic_avoid(uint16_t distance)
{
	uint16_t left_data = 0;
	uint16_t right_data = 0;
	uint16_t dis;
	dis=Get_distance();
	Get_Iravoid_Data(&left_data,&right_data);//串口打印采集的数据 Serial port printing of collected data
	if((distance >2.0 && dis < distance )||(left_data <500||right_data<500))
		{
			//小车停止 Car stops
			wheel_State(MOTION_STOP,0);
			HAL_Delay(500);

			//小车后退 Car backs up
			wheel_State(MOTION_BACK,250);
			HAL_Delay(1000);

			Get_Iravoid_Data(&left_data,&right_data);

			if(left_data>=right_data)
			{
				//小车左旋 Car turns left
				wheel_State(MOTION_SPIN_LEFT,400);
				HAL_Delay(500);
			}
			else
			{
				//小车右旋 Car rotates right
				wheel_State(MOTION_SPIN_RIGHT,400);
				HAL_Delay(500);
			}
		}
		else
		{
			//小车前进 The car moves forward
			wheel_State(MOTION_RUN,250);
		}
}
*/
void Ir_Ultrasonic_avoid(uint16_t distance)
{
    uint16_t left_data = 0;
    uint16_t right_data = 0;
    uint16_t dis;
    dis = Get_distance();  // 获取正前方的距离
    Get_Iravoid_Data(&left_data, &right_data); // 获取左前和右前的距离

    // 如果前方有障碍物
    if (dis < distance || left_data<150 || right_data<150)
    {
        wheel_State(MOTION_STOP, 0);  // 停止前进
        HAL_Delay(500);  // 暂停一会儿，避免碰撞

        // 再次获取左侧和右侧的数据
        Get_Iravoid_Data(&left_data, &right_data);

        // 判断转向策略
        if (left_data > right_data)  // 如果左侧更远或者右侧有障碍物
        {
            // 小车右转，保持较小的转角
            wheel_State(MOTION_SPIN_LEFT, 400);  // 小幅度左转
            HAL_Delay(200);  // 等待转向完成
        }
        else if (right_data > left_data)  // 如果右侧更远
        {
            // 小车左转，保持较小的转角
            wheel_State(MOTION_SPIN_RIGHT, 400);  // 小幅度右转
            HAL_Delay(200);  // 等待转向完成
        }
        else  // 如果左右距离相等
        {
            wheel_State(MOTION_STOP, 0);  // 小车停止
            HAL_Delay(500);
        }
    }
    else
    {
        // 没有障碍物，可以继续前进
        wheel_State(MOTION_RUN, 500);
    }
}



