#ifndef __BSP_IRAVOID_H_
#define __BSP_IRAVOID_H_

#include "main.h"
#include "adc.h"


uint16_t Adc_Get_Iravoid(uint32_t ch);
void Get_Iravoid_Data(uint16_t *left_data,uint16_t *right_data);

#endif
