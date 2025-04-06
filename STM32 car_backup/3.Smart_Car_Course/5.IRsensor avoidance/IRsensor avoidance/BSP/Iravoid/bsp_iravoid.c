#include "bsp_iravoid.h"

/*
 * 采集传感器的电压
 *
 *Collect the voltage of the sensor
 * */

uint16_t Adc_Get_Iravoid(uint32_t ch)
{
  ADC_ChannelConfTypeDef sConfig = {0};
  sConfig.Channel = ch;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_239CYCLES_5;
  if (HAL_ADC_ConfigChannel(&hadc3, &sConfig) != HAL_OK)
  {
	Error_Handler();
  }

	HAL_ADC_Start(&hadc3);
	HAL_ADC_PollForConversion(&hadc3, 500);
	return HAL_ADC_GetValue(&hadc3);
}


/*
 * 串口打印采集的数据
 *
 *Serial port printing of collected data
 * */
void Get_Iravoid_Data(uint16_t *left_data,uint16_t *right_data)
{

	*left_data =  Adc_Get_Iravoid(ADC_CHANNEL_7);
	*right_data = Adc_Get_Iravoid(ADC_CHANNEL_8);

	printf("L1:%d     R1:%d \r\n",*left_data,*right_data);

}
