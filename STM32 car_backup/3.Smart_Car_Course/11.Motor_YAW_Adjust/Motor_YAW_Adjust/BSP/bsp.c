//该案例注意事项要等mpu6050的值稳定后（值在一定幅度上变动，而不是单一递增或递减）  这是一个校正状态，可观察oled
//才能按下按键1,让小车前进，不然是有问题的

#include "bsp.h"

float my_abs(float x)
{
	if(x<0)
		x=-x;
	return x;
}


//Hardware Initialization
//Parameter:None
void BSP_Init(void)
{
	Delay_Init();

	OLED_Init();//oled初始化
//	OLED_Draw_Line("oled init success!",1,true,true);

	MPU_Init_Self();
	LED1_OFF;//mpu正常的情况下，led1灭

	Bsp_Tim_Init();
	PID_Param_Init();//电机PID初始化


}

uint8_t key1_flag = 0; //0:停止运动 1:开始运动


char buff [20] ={'\0'};
//Loop Run Function
//Parameter:None
void BSP_Loop(void)
{
	if(mpu_dmp_get_data(&Pitch,&Roll,&Yaw)==0)
	{
		return; //目标稳定时
	}
	YAW_app = (int)(Yaw*100) /100.0; //保留1位小数，过虑漂移的数据


	sprintf(buff,"Yaw = %.2f     ",YAW_app);
	OLED_Draw_Line(buff,2,false,true);

	if(Key1_State(1))
	{
		key1_flag ++;
		if(key1_flag > 2)
			key1_flag = 0;
	}

	if(key1_flag == 0)
	{
		LED2_OFF;
		wheel_State_YAW(MOTION_STOP,0,DISABLE);
		if(my_abs(Yaw_old - YAW_app) > 0.2)
		{
			OLED_Draw_Line("please wait!",1,false,true);
			key1_flag = 0;
		}
		else
		{
			OLED_Draw_Line("                    ",1,false,true);
		}
	}
	else if(key1_flag == 1)
	{
		LED2_ON;
		wheel_State_YAW(MOTION_RUN,200,ENABLE);
		key1_flag ++;
		OLED_Draw_Line("                    ",1,false,true);
	}

}
