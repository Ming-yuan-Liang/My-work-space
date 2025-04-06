#ifndef __APP_K210_H_
#define __APP_K210_H_

#include "bsp.h"

void APP_K210X_Y_Init(void);
float APP_K210X_PID_Calc(float actual_value);
float APP_K210Y_PID_Calc(float actual_value);
void APP_K210X_Y_Line_PID(void);

float my_abs(float num);

#endif


