#include "bsp.h"

uint16_t g_ADC_Value = 0;
double Current_Voltage = 0;
double Inter_Temperature = 0;
char g_buff[1024] = {0};

// Hardware Initialization
// Parameter:None
void BSP_Init(void)
{
	HAL_ADCEx_Calibration_Start(&hadc1);
}

// Loop Run Function
// Parameter:None
void BSP_Loop(void)
{
	HAL_ADC_Start(&hadc1);
	HAL_ADC_PollForConversion(&hadc1,10);
	g_ADC_Value = HAL_ADC_GetValue(&hadc1);
	Current_Voltage = g_ADC_Value / 4096.0 * 3.3;
	Inter_Temperature = (1.43 - Current_Voltage) / 0.0043 + 25.0;
	printf("The Current ADC_Value is %d\n",g_ADC_Value);
	printf("The Current Voltage is %.3f\n",Current_Voltage);
	printf("The Interal Temperature is %.2f\n",Inter_Temperature);
	HAL_Delay(500);
}

