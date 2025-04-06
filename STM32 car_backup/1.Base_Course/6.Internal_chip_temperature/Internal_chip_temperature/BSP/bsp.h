#ifndef __BSP_H_
#define __BSP_H_

#include "main.h"
#include "adc.h"
#include "usart.h"
#include "gpio.h"
#include "stdio.h"

extern uint16_t g_ADC_Value;
extern double Inter_Temperature;
extern double Current_Voltage;

void BSP_Init(void);
void BSP_Loop(void);

#endif
