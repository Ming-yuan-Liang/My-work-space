/*
 * app_ultrasonic.c
 *
 *  Created on: Oct 26, 2023
 *      Author: YB-101
 */

#include "app_ultrasonic.h"

/*
void Ultrasonic_avoidance(uint16_t distance)
{
	uint16_t dis;
	dis=Get_distance();
	if(distance >2.0 && dis < distance )
		{
   // 侧方停车代码

		    wheel_State(MOTION_STOP, 0);
		    HAL_Delay(500);  // 停止500ms

		// 小车右转
		    Motion_Set_Speed(400, 400, -100, -100);
		    HAL_Delay(800);

		// 小车前进
		    wheel_State(MOTION_RUN, 250);
		    HAL_Delay(1500);

		// 小车左转
			Motion_Set_Speed(-100, -100, 400, 400);
			HAL_Delay(850);

		// 小车前进
			wheel_State(MOTION_RUN, 250);
			HAL_Delay(800);

		// 小车停止
			wheel_State(MOTION_STOP, 0);
			HAL_Delay(10000);


		wheel_State(MOTION_STOP, 0);
	    HAL_Delay(500);

	    Motion_Set_Speed(-400, -400, -100, -100);
	    HAL_Delay(2200);
	    wheel_State(MOTION_BACK, 200);
	    HAL_Delay(500);
		wheel_State(MOTION_STOP, 0);
		HAL_Delay(10000);
		Motion_Set_Speed(-100, -100, 500, 500);
		HAL_Delay(1100);
		wheel_State(MOTION_RUN, 200);
		HAL_Delay(1000);
		wheel_State(MOTION_BACK, 200);
		HAL_Delay(1000);
		Motion_Set_Speed(-100, -100, -500, -500);
		HAL_Delay(1100);
		Motion_Set_Speed(500, 500, -100, -100);
		HAL_Delay(1100);

		Set_Buzzer(1); // 开启蜂鸣器
		// 小车停止
		wheel_State(MOTION_STOP, 0);
		HAL_Delay(100000);


		}
		else
		{
			//小车前进 The car moves forward
			wheel_State(MOTION_RUN,250);
		}
}
*/
/*
void Ultrasonic_avoidance(uint16_t distance)
{
    uint16_t dis;

    while (1) {  // 无限循环，持续监测距离并控制蜂鸣器
        dis = Get_distance(); // 获取当前测距

        // 根据距离设置蜂鸣器的响应速度（延迟时间）
        uint16_t delay_time;

        // 增加多个检测距离，确保蜂鸣器在每个范围内都有反应
        if (dis < 10) {
            delay_time = 10;  // 距离非常近，蜂鸣器频繁响起（最短延迟20ms）
        }
        else if (dis < 20) {
            delay_time = 50;  // 距离非常近，蜂鸣器频繁响起（延迟30ms）
        }
        else if (dis < 50) {
            delay_time = 200;   // 距离较近，蜂鸣器频率较高（延迟60ms）
        }
        else if (dis < 100) {
            delay_time = 500;  // 距离中等，蜂鸣器频率较低（延迟120ms）
        }
        else {
            delay_time = 2000;  // 距离较远，蜂鸣器频率更低（延迟250ms）
        }

        // 启动蜂鸣器并调整延迟时间
        Set_Buzzer(1);  // 开启蜂鸣器
        HAL_Delay(delay_time);  // 延迟以控制频率
        Set_Buzzer(0);  // 关闭蜂鸣器
        HAL_Delay(delay_time);  // 延迟再次控制频率

        if (dis < 5) {

            wheel_State(MOTION_STOP, 0);
            HAL_Delay(200);
            Set_Buzzer(0);
            wheel_State(MOTION_BACK, 300);
            HAL_Delay(500);
            // 小车右转
            Motion_Set_Speed(400, 400, -100, -100);
            HAL_Delay(800);
            // 小车前进
            wheel_State(MOTION_RUN, 250);
            HAL_Delay(1500);
    		// 小车左转
    		Motion_Set_Speed(-100, -100, 400, 400);
    		HAL_Delay(850);

        } else {

            wheel_State(MOTION_RUN, 70);  // 调整速度可以使小车更慢
        }
        }
}
*/
void Ultrasonic_avoidance(uint16_t distance)     // 避障函数
{
    uint16_t dis;
    uint16_t delay_time;
    while (1) {
        dis = Get_distance(); // 获取当前测距
        if (dis < 15) {
            delay_time = 10;
            Set_RGB(RGB_Max, red); } // 红色，距离非常近
        else if (dis < 30) {
            delay_time = 30;
            Set_RGB(RGB_Max, red); } // 红色，距离较近
        else if (dis < 50) {
            delay_time = 150;
            Set_RGB(RGB_Max, blue);} // 紫色，距离中等
        else if (dis < 75) {
            delay_time = 500;
            Set_RGB(RGB_Max, purple);} // 紫色，距离远
        else if (dis < 100) {
                delay_time = 1000;
                Set_RGB(RGB_Max, blue);} // 紫色，距离远
        else {
            delay_time = 1000;
            Set_RGB(RGB_Max, green);} // 绿色，距离最远
        Set_Buzzer(1);  // 开启蜂鸣器
        HAL_Delay(delay_time);  // 延迟以控制蜂鸣器频率
        Set_Buzzer(0);  // 关闭蜂鸣器
        HAL_Delay(delay_time);  // 延迟再次控制频率
        if (dis < 10) {
    	    wheel_State(MOTION_STOP, 0);
    		HAL_Delay(1000);  // 停止500ms
    		wheel_State(MOTION_BACK, 200);
    		HAL_Delay(2000);

    		    Motion_Set_Speed(400, 400, -100, -100);
    		    HAL_Delay(800);
    		    wheel_State(MOTION_RUN, 250);
    		    HAL_Delay(1500);
    			Motion_Set_Speed(-100, -100, 400, 400);
    			HAL_Delay(850);
    			wheel_State(MOTION_STOP, 0);
    			HAL_Delay(1000);
        } else {
            wheel_State(MOTION_RUN, 200);  // 调整速度，小车前进
        }
    }
}


void Ultrasonic_follow(uint16_t target_distance)     // 跟随函数
{
    uint16_t dis;
    uint16_t delay_time;
    uint16_t follow_speed;

    // 理想的目标跟随距离范围
    uint16_t ideal_distance_min = target_distance - 5;
    uint16_t ideal_distance_max = target_distance + 5;

    // 无限循环，持续监测距离并控制小车
    while (1) {
        dis = Get_distance(); // 获取当前测距

        // 判断距离，并调整小车速度
        if (dis < ideal_distance_min) {
            follow_speed = 0;  // 距离太近，减速
            Set_RGB(RGB_Max, red);
            Set_Buzzer(1);  // 开启蜂鸣器
            HAL_Delay(10);  // 延迟以控制蜂鸣器频率
            Set_Buzzer(0);  // 关闭蜂鸣器
            HAL_Delay(10);  // 延迟再次控制频率

        }
        else if (dis > ideal_distance_max) {
            follow_speed = 200;  // 距离较远，加速
            Set_RGB(RGB_Max, blue);
        }
        else {
            follow_speed = 100;  // 距离合适，正常速度
            Set_RGB(RGB_Max, green);
        }

        // 控制小车前进
        wheel_State(MOTION_RUN, follow_speed);

        // 如果距离过近，进行避障处理
        if (dis < 5) {
        	 wheel_State(MOTION_STOP, 0);
        	 HAL_Delay(3000);  // 停止500ms
        	 wheel_State(MOTION_BACK, 100);
        	 HAL_Delay(3000);
        }

        // HAL_Delay(20);  // 控制更新频率，避免过度频繁调整
    }
}






