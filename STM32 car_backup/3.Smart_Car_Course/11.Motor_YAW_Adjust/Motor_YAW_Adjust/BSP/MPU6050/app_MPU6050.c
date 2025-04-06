#include "app_MPU6050.h"



float Pitch,Roll,Yaw; 		//欧拉角
float YAW_app;
float Yaw_old;

//函数自检函数
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
