#include "bsp.h"

// Hardware Initialization
// Parameter:None

void BSP_Init(void)
{
	Delay_Init();	  // 延迟初始化 Delayed initialization
	Bsp_UART1_Init(); // 串口1初始化 usart1 initialization
	Bsp_TIM7_Init();  // tim7初始化 tim7 initialization
}

// Loop Run Function
// Parameter:None

void BSP_Loop(void)
{
	printf("dis = %.2f cm\r\n", Get_distance()); // 打印超声波的距离 Print ultrasonic distance
	Delay_MS(200);
}
