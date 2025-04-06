#ifndef __APP_MPU6050_H_
#define __APP_MPU6050_H_


#include "bsp.h"

void MPU_Init_Self(void);
void Printf_MPU_Data(void);
float Convert_to_360(float angle);

extern float Pitch,Roll,Yaw; 		//欧拉角
extern float YAW_app;
extern float YAW_car;
extern float YAW_yaw_e; //把-180~180转成0-360的范围 Convert -180~180 to a range of 0~360
extern float Yaw_old_buckup;
extern float YAW_app_old;

#endif
