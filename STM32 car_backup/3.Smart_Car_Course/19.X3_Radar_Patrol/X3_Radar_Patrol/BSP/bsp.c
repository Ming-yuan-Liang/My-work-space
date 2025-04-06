#include "bsp.h"

//Hardware Initialization
//Parameter:None
void BSP_Init(void)
{
	Delay_Init();
	OLED_Init();
	MPU_Init_Self();//MPU初始化 MPU initialization
	LED1_OFF;//mpu正常的情况下，led1灭 Under normal mpu conditions, LED 1 goes out

	Bsp_Tim_Init();
	PID_Param_Init();//电机PID初始化 Motor PID initialization

	USART3_Init();
}


uint8_t key1_flag = 0;
uint8_t run_num = 0;
uint8_t mpu_flag = 0;

char buff[20];
//Loop Run Function
//Parameter:None
void BSP_Loop(void)
{
	if(Key1_State(1))
	{
		key1_flag ++;
		if(key1_flag >2)
		{
			key1_flag = 0;
		}
	}

	if(key1_flag == 0)
	{
		wheel_State_YAW(MOTION_STOP,0,0);//停车 stop
		APP_Reset();
		LED2_OFF;
		BEEP_OFF;

		if(my_abs(YAW_app - YAW_app_old) > 0.1) //值还没稳定  The value is not stable yet
		{
			OLED_Draw_Line("Wait for MPU6050",1,false,true);
		}
		else
		{
			OLED_Draw_Line("                        ",1,false,true);
		}
		if(mpu_flag ==1)
		{
			MPU_Init_Self();//再次自检  Self check again
			mpu_flag = 0;
		}

	}
	else if(key1_flag == 1) //按下按键
	{
		key1_flag ++;
		YAW_car = YAW_yaw_e;
		Car_straight();
		LED2_ON;
		run_num = 0;
		mpu_flag = 1;
	}
	else
	{
		OLED_Draw_Line("                        ",1,false,true);
	}
	sprintf(buff,"Yaw = %.2f     ",YAW_yaw_e);//要等待mpu6050校正完才能开始巡逻  We need to wait for the MPU6050 to be corrected before we can start patrolling
	OLED_Draw_Line(buff,2,false,true);

	sprintf(buff,"dis = %.2f     ",get_data_mid);
	OLED_Draw_Line(buff,3,false,true);

}
