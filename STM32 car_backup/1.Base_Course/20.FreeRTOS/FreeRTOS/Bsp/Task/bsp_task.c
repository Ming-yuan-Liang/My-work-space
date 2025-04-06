#include "bsp_task.h"

unsigned int Beep_Switch = 0;	//0：关闭 其它：开启
unsigned int LED1_Switch = 0;	//0：关闭 其它：开启
unsigned int LED2_Switch = 0;	//0：关闭 其它：开启

void Task_Entity_RGB(void)//RGB任务实体函数 RGB task entity function
{
	while(1)
	{
		osDelay(500);
		Set_RGB(RGB_Max, red);
		osDelay(500);
		Set_RGB(RGB_Max, green);
		osDelay(500);
		Set_RGB(RGB_Max, blue);
		osDelay(500);
		Set_RGB(RGB_Max, yellow);
		osDelay(500);
		Set_RGB(RGB_Max, purple);
		osDelay(500);
		Set_RGB(RGB_Max, lake);
		osDelay(500);
		Set_RGB(RGB_Max, white);
		osDelay(500);
	}
}

void Task_Entity_BEEP(void)//蜂鸣器任务实体函数 Buzzer task entity functions
{
	while(1)
	{
		if(Beep_Switch)
		{
			Set_Buzzer(1);
			osDelay(100);
			Set_Buzzer(0);
			osDelay(1000);
		}
		else
		{
			Set_Buzzer(0);
		}
	}
}

void Task_Entity_LED(void)//LED任务实体函数 LED task entity functions
{
	while(1)
	{
		if(LED1_Switch)
		{
			HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
		}
		if(LED2_Switch)
		{
			HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);
		}
		else
		{
			HAL_GPIO_WritePin(GPIOG, LED1_Pin|LED2_Pin, GPIO_PIN_RESET);
		}
	}
}

void Task_Entity_KEY(void)//按键实体函数 Button entity function
{
	while(1)
	{
		if(Key1_State(1) == KEY_PRESS)
		{
			Beep_Switch = !Beep_Switch;
		}
		if(Key2_State(1) == KEY_PRESS)
		{
			LED1_Switch = !LED1_Switch;
		}
		if(Key3_State(1) == KEY_PRESS)
		{
			LED2_Switch = !LED2_Switch;
		}
		osDelay(10);
	}
}
