#include "app_MPU6050.h"



float Pitch,Roll,Yaw; 		//欧拉角 //Euler angle
float YAW_app;
float YAW_app_old;

float YAW_car;
float YAW_yaw_e;
float Yaw_old_buckup; //备份停止的角度 //Angle of backup stop
//函数自检函数 Function self checking function
void MPU_Init_Self(void)
{
	while(mpu_dmp_init())
	{
		printf("MPU_Init.....\r\n");
		LED1_OFF;
		delay_ms(200);
		LED1_ON;
		delay_ms(200);

	}
}



void Printf_MPU_Data(void)
{
		if(mpu_dmp_get_data(&Pitch,&Roll,&Yaw)==0)
		{
			return;
		}
		printf("pitch:%.3f\t,roll:%.3f\t,yaw:%.3f\r\n",Pitch,Roll,Yaw);
}

float Convert_to_360(float angle)
{
	if(angle < 0)
		angle +=360;

	if(angle >= 360)
		angle -= 360;

	return angle;
}

