#ifndef __APP_CCD_H_
#define __APP_CCD_H_

#include "bsp.h"


void APP_CCD_Init(void);
float APP_CCD_PID_Calc(float actual_value);
void APP_CCD_Line_PID(void);
float my_abs(float num);

#endif



