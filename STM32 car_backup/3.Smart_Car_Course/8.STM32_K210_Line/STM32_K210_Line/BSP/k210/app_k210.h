#ifndef __APP_K210_H_
#define __APP_K210_H_

#include "bsp.h"

void APP_K210X_Init(void);
float APP_K210X_PID_Calc(float actual_value);
void APP_K210X_Line_PID(void);


#endif


