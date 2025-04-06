#ifndef __APP_X3_RADAR_H_
#define __APP_X3_RADAR_H_

#include "bsp.h"

#define Patrol_Count 2 //巡逻的次数  如果次数太多,就会偏离轨道 If the number of patrols is too high, it will deviate from the track
#define Turn_Angle   90 //转弯角度 Turning angle

#define DIS_FOOD   	 250 //障碍物距离 Obstacle distance
#define Car_Go_Time  350 //小车直线的时间 Car_Go_Time*10 = s


void APP_X3_Init(void);
void App_Print_Data(void);
float App_Data_Avg(uint16_t start,uint16_t end);
float App_Data_Min(uint16_t start,uint16_t end);

void APP_X3_MPU_Patrol(void);
void X3_Motion_Car(void);

void Car_Turn(void);
void Car_straight(void);

float get_way_L(void);
void APP_Reset(void);

int my_math(float x);
float my_abs(float x);
#endif

