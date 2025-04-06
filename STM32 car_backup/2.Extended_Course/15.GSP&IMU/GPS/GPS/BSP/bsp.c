/*
 * bsp.c
 *
 *  Created on: Oct 25, 2023
 *      Author: YB-101
 */

#include "bsp.h"

// Hardware Initialization
// Parameter:None

void Bsp_Init(void)
{

	Bsp_UART1_Init(); // 串口初始化 Serial port initialization
	clrStruct();	  // 初始化gps结构体 Initialize the gps structure
	printf("Welcome to use!\r\n");
}

// Hardware Initialization
// Parameter:None

void Bsp_Loop(void)
{
	parseGpsBuffer(); // 解析gps数据 parse gps data
	printGpsBuffer(); // 打印gps数据 print gps data
}
