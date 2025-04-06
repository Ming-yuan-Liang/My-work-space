#ifndef __APP_CCD_H_
#define __APP_CCD_H_

#include "bsp.h"

void APP_ELE_Init(void);
float APP_ELE_PID_Calc(float actual_value);
void APP_ELE_Line_PID(void);

#endif
