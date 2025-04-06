#include "bsp_time.h"

extern vu16 UART4_RX_STA;//从外部引入变量

void TIM6_Clear_CNT(void)
{
	//清掉cnt的值为0
	//Clear CNT with a value of 0
	__HAL_TIM_SET_COUNTER(&htim6,0);
}

void TIM6_Open(void)//10ms
{
  //Turn on timer interrupt 打开定时器中断
  HAL_TIM_Base_Start_IT(&htim6);
}

void TIM6_Close(void)
{
  //Turn off timer interrupt 关闭定时器中断
  HAL_TIM_Base_Stop_IT(&htim6);
}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	 if(htim->Instance==TIM6)
	  {
		 UART4_RX_STA |=1<<15;
		 __HAL_TIM_SET_COUNTER(&htim6,0);
		 TIM6_Close();
	  }

}
