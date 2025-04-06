/*
 * bsp.c
 *
 *  Created on: 2023年10月8日
 *      Author: YB-101
 */
#include "bsp.h"

// Hardware Initialization
// Parameter:None
void BSP_Init(void)
{
  Bsp_UART1_Init();
}

// Loop Run Function
// Parameter:None
void BSP_Loop(void)
{
  printf("X1:%d X2:%d X3:%d X4:%d  \r\n", Read_irtracking(X1), Read_irtracking(X2), Read_irtracking(X3), Read_irtracking(X4));
  HAL_Delay(300);
}
