#ifndef __APP_X3_RADAR_H_
#define __APP_X3_RADAR_H_

#include "bsp.h"

void App_Print_Data(void);
float App_Data_Avg(uint16_t start,uint16_t end);
float App_Data_Min(uint16_t start,uint16_t end);


void Car_Follow(void);


float my_min(float x);
#endif

