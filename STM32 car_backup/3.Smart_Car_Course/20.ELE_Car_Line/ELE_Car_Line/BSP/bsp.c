#include "bsp.h"

// Hardware Initialization
// Parameter:None
void BSP_Init(void)
{
	Init_ElE_GPIO();

	Bsp_Tim_Init();
	PID_Param_Init(); // 电机PID初始化

	APP_ELE_Init();
	HAL_ADCEx_Calibration_Start(&hadc1);
	OLED_Init();
}

// Loop Run Function
// Parameter:None
void BSP_Loop(void)
{
	static uint8_t key_flag = 0;

	EleDataDeal();

	if (Key1_State(1))
	{
		LED2_ON;
		key_flag++;
		if (key_flag > 2)
		{
			key_flag = 0;
		}
	}

	if (key_flag == 0)
	{
		APP_ELE_Init();				 // 重置PID
		wheel_State(MOTION_STOP, 0); // 小车停止
		LED2_OFF;
		key_flag++;
	}

	if (key_flag == 2)
	{
		APP_ELE_Line_PID();
	}
}
