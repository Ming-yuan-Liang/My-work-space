#include "app_MPU6050.h"



float pitch,roll,yaw; 		//欧拉角


//函数自检函数
void MPU_Init_Self(void)
{
	while(mpu_dmp_init())
	{
		printf("MPU_Init.....\r\n");
		delay_ms(20);
	}
}



void Printf_MPU_Data(void)
{
		if(mpu_dmp_get_data(&pitch,&roll,&yaw)==0)
		{
			return;
		}
		printf("pitch:%.3f\t,roll:%.3f\t,yaw:%.3f\r\n",pitch,roll,yaw);
}
