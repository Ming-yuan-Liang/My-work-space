#ifndef __APP_MPU6050_H_
#define __APP_MPU6050_H_


#include "bsp.h"

void MPU_Init_Self(void);
void Printf_MPU_Data(void);


extern float Pitch,Roll,Yaw; 		//欧拉角
extern float YAW_app;
extern float Yaw_old;

#endif
