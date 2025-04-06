/*
 * bsp.c
 *
 *  Created on: 2023年10月8日
 *      Author: YB-101
 */
#include "bsp.h"

int16_t speed;

int Encoder_M3 = 0;
int Encoder_M2 = 0;
int Encoder_M1 = 0;
int Encoder_M4 = 0;

// Hardware Initialization
// Parameter:None
void BSP_Init(void)
{
	Bsp_UART1_Init(); // 初始化串口1 Initialize usarts 1
	Bsp_Tim_Init();	  // 初始化定时器123458 Initialize TIM1.2.3.4.5.8
}

// Loop Run Function
// Parameter:None
void BSP_Loop(void)
{

	Encoder_Update_Count(); // 测编码器的值 Measure the value of the encoder
	HAL_Delay(100);
	Encoder_M3 = Encoder_Get_Count_Now(MOTOR_ID_M3);
	Encoder_M2 = Encoder_Get_Count_Now(MOTOR_ID_M2);
	Encoder_M1 = Encoder_Get_Count_Now(MOTOR_ID_M1);
	Encoder_M4 = Encoder_Get_Count_Now(MOTOR_ID_M4);
	printf("Encoder:%d,%d,%d,%d  \r\n", Encoder_M1, Encoder_M2, Encoder_M3, Encoder_M4); // 打印编码器的值 Print encoder value

	if (Key1_State(1)) // 手动转动并显示编码器的值 Manually turn and display the encoder value
	{
		speed = 0;
		Motor_Set_Pwm(MOTOR_ID_M1, speed);
		Motor_Set_Pwm(MOTOR_ID_M2, speed);
		Motor_Set_Pwm(MOTOR_ID_M3, speed);
		Motor_Set_Pwm(MOTOR_ID_M4, speed);
		Encoder_Update_Count(); // 测编码器的值 Measure the value of the encoder
		HAL_Delay(100);
		Encoder_M3 = Encoder_Get_Count_Now(MOTOR_ID_M3);
		Encoder_M2 = Encoder_Get_Count_Now(MOTOR_ID_M2);
		Encoder_M1 = Encoder_Get_Count_Now(MOTOR_ID_M1);
		Encoder_M4 = Encoder_Get_Count_Now(MOTOR_ID_M4);
		printf("Please rotate the wheel manually. Encoder:%d,%d,%d,%d  \r\n", Encoder_M1, Encoder_M2, Encoder_M3, Encoder_M4);
	}
	if (Key2_State(1)) // 电机正转并打印编码器的值 The motor rotates forward and prints the encoder value
	{
		speed = 1000;
		Motor_Set_Pwm(MOTOR_ID_M1, speed);
		Motor_Set_Pwm(MOTOR_ID_M2, speed);
		Motor_Set_Pwm(MOTOR_ID_M3, speed);
		Motor_Set_Pwm(MOTOR_ID_M4, speed);
		Encoder_Update_Count(); // 测编码器的值 Measure the value of the encoder
		HAL_Delay(100);
		Encoder_M3 = Encoder_Get_Count_Now(MOTOR_ID_M3);
		Encoder_M2 = Encoder_Get_Count_Now(MOTOR_ID_M2);
		Encoder_M1 = Encoder_Get_Count_Now(MOTOR_ID_M1);
		Encoder_M4 = Encoder_Get_Count_Now(MOTOR_ID_M4);
		printf("Motor forward.  Encoder:%d,%d,%d,%d  \r\n", Encoder_M1, Encoder_M2, Encoder_M3, Encoder_M4);
	}
	if (Key3_State(1)) // 电机反转并打印编码器的值 The motor reverses and prints the encoder value
	{
		speed = -1000;
		Motor_Set_Pwm(MOTOR_ID_M1, speed);
		Motor_Set_Pwm(MOTOR_ID_M2, speed);
		Motor_Set_Pwm(MOTOR_ID_M3, speed);
		Motor_Set_Pwm(MOTOR_ID_M4, speed);
		Encoder_Update_Count(); // 测编码器的值 Measure the value of the encoder
		HAL_Delay(100);
		Encoder_M3 = Encoder_Get_Count_Now(MOTOR_ID_M3);
		Encoder_M2 = Encoder_Get_Count_Now(MOTOR_ID_M2);
		Encoder_M1 = Encoder_Get_Count_Now(MOTOR_ID_M1);
		Encoder_M4 = Encoder_Get_Count_Now(MOTOR_ID_M4);
		printf("Motor reverse.  Motor reverse,Encoder:%d,%d,%d,%d  \r\n", Encoder_M1, Encoder_M2, Encoder_M3, Encoder_M4);
	}
}
