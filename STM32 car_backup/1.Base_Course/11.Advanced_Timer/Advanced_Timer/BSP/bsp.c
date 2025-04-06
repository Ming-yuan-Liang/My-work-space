#include "bsp.h"


//该实验要用杜邦线进行短接 PE9接到舵机接口S1的黄色接口上
//This experiment requires the use of a DuPont cable for short circuiting PE9 to the yellow S1 interface of the servo interface

// Hardware Initialization
// Parameter:None
void BSP_Init(void)
{
	HAL_Delay(200);
	USART1_UART_Init();
	TIM1_PWM_Init();
	TIM3_PWM_Init();


}

// Loop Run Function
// Parameter:None
void BSP_Loop(void)
{
	printf("IC1Value = %d\r\n",IC1Value);
	printf("IC2Value = %d\r\n",IC2Value);
	printf("DutyCycle = %f \r\n",DutyCycle); //占空比
	printf("Frequency = %f \r\n",Frequency); //频率
	HAL_Delay(500);			// 500ms
}
