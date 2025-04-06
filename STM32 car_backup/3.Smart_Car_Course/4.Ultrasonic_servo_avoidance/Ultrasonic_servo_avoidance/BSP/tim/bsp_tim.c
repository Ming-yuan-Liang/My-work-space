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

	// 启动定时6中断 Start timer 6 interrupt
	//	HAL_TIM_Base_Start_IT(&htim6);
	// 启动定时7中断 Start timer 7 interrupt
	HAL_TIM_Base_Start_IT(&htim7);
}

uint16_t motor_count = 1000;

void TIM6_IRQHandler(void)
{
	if (__HAL_TIM_GET_FLAG(&htim6, TIM_FLAG_UPDATE) != RESET) // Check if TIM update interrupt occurs 检查TIM更新中断发生与否
	{
		if (__HAL_TIM_GET_IT_SOURCE(&htim6, TIM_IT_UPDATE) != RESET) // Check if TIM6 interrupt is enabled 检查TIM6的中断是否启用
		{
			__HAL_TIM_CLEAR_IT(&htim6, TIM_IT_UPDATE); // clear interrupt 清除中断
		}
	}
}

/**
 * @brief This function handles TIM7 global interrupt.
 */
void TIM7_IRQHandler(void)
{
	if (__HAL_TIM_GET_FLAG(&htim6, TIM_FLAG_UPDATE) != RESET) // Check if TIM update interrupt occurs 检查TIM更新中断发生与否
	{
		if (__HAL_TIM_GET_IT_SOURCE(&htim7, TIM_IT_UPDATE) != RESET) // Check if TIM6 interrupt is enabled 检查TIM6的中断是否启用
		{
			__HAL_TIM_CLEAR_IT(&htim7, TIM_IT_UPDATE); // clear interrupt 清除中断
			if (ultrasonic_flag)					   // 开始测距--超声波 Start ranging--ultrasound
			{
				ultrasonic_num++;
			}
			if (motor_count > 0)
			{
				motor_count--;
			}
			else
			{
				Encoder_Update_Count(); // 10ms测速 10ms speed test
				Motion_Handle();		// 调用PID控制速度 Call PID to control speed
				motor_count = 1000;
			}

			PwmServo_Handle();
		}
	}
}
