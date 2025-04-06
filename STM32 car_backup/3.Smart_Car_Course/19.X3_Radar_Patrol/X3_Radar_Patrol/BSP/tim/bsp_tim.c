/*
 * bsp_tim.c
 *
 *  Created on: 2023年10月18日
 *      Author: YB-101
 */

#include "bsp_tim.h"
/*
 * 初始化定时器123458 Initialize TIM1.2.3.4.5.8
 * */
void Bsp_Tim_Init(void)

{
	// 启动tim1的pwm输出 Start the pwm output of tim1
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);

	// 启动tim8的pwm输出 Start the pwm output of tim8
	HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_4);

	TIM2->CNT = 0x7fff;
	// 启动tim2的编码器模式 Start the encoder mode of tim2
	HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_1 | TIM_CHANNEL_2);

	TIM3->CNT = 0x7fff;
	// 启动tim3的编码器模式 Start the encoder mode of tim3
	HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_1 | TIM_CHANNEL_2);

	TIM4->CNT = 0x7fff;
	// 启动tim4的编码器模式 Start the encoder mode of tim4
	HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_1 | TIM_CHANNEL_2);

	TIM5->CNT = 0x7fff;
	// 启动tim5的编码器模式 Start the encoder mode of tim5
	HAL_TIM_Encoder_Start(&htim5, TIM_CHANNEL_1 | TIM_CHANNEL_2);


	//启动定时6中断
	HAL_TIM_Base_Start_IT(&htim6);
}






extern uint16_t g_car_time ;//小车走直线的时间 Time for the car to travel in a straight line
extern uint16_t g_car_state;//小车走直线标志 0:不走直线 1:开始走直线 Car walking in a straight line sign 0: Not walking in a straight line 1: Starting to walk in a straight line

float get_data_mid = 0;

uint16_t yaw_time = 200;//yaw角的时间 The time of Yaw angle
//基本定时器中断回调函数 Basic timer interrupt callback function
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (htim->Instance == TIM6)//10ms
	{
		Encoder_Update_Count();//10ms测速
		Motion_Handle();//调用PID控制速度 Calling PID control speed

		get_data_mid = App_Data_Avg(165,195);

		if(mpu_dmp_get_data(&Pitch,&Roll,&Yaw) == 0)
		{
			YAW_app = (int)(Yaw*100) /100.0 ;
			YAW_yaw_e = Convert_to_360(YAW_app);
		}

		if(g_car_state == 1 && get_data_mid > DIS_FOOD && key1_flag == 2)//做直线运动的时间 Time to do linear motion
		{
			if(g_car_time > 0)
			{
				g_car_time -- ;
			}
		}

		if(key1_flag == 0 )//小车不动的时候，mpu的状态稳定判定 When the car is stationary, the stability of the mpu state is determined
		{
			if(yaw_time == 0)
			{
				yaw_time = 200;
				YAW_app_old = YAW_app;
			}
			else
			{
				yaw_time -- ;
			}

		}
		else
		{
			X3_Motion_Car();
		}



	}

}



