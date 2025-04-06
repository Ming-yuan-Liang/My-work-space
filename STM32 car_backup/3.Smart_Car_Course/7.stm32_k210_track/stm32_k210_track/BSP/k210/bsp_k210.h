#ifndef __BSP_K210_H_
#define __BSP_K210_H_

#include "bsp.h"


typedef struct K210_Data
{
	uint16_t k210_X ; //Identify the center point of the x-axis of the box 识别框x轴的中心点
	uint16_t k210_Y ; //Identify the center point of the y-axis of the box 识别框y轴的中心点
}K210_Data_t;

void Deal_K210(uint8_t recv_msg);
void Get_K210_Data(void);
float APP_K210Y_PID_Calc(float actual_value);

extern K210_Data_t K210_data;

#endif
