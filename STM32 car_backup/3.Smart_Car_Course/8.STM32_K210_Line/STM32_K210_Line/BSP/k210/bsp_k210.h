#ifndef __BSP_K210_H_
#define __BSP_K210_H_

#include "bsp.h"


typedef struct K210_Data
{
	uint16_t k210_X ; //识别框x轴的中心点 Identify the center point of the x-axis of the box
	uint16_t k210_Y ; //识别框y轴的中心点 Identify the center point of the y-axis of the box
}K210_Data_t;

void Deal_K210(uint8_t recv_msg);
void Get_K210_Data(void);

extern K210_Data_t K210_data;

#endif
