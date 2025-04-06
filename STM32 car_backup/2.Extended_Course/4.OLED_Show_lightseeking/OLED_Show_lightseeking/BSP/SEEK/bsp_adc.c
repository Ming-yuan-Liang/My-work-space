#include "bsp_adc.h"

/*
 * 采集光敏电压
 *
 *Collect photosensitive voltage
 * */

static uint16_t Adc_Get_seek(uint32_t ch)
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
	HAL_ADC_PollForConversion(&hadc3, 1000);
	return HAL_ADC_GetValue(&hadc3);
}
/*
 * 根据光敏电压换算成电阻
 *
 * Convert to resistance based on photosensitive voltage
 * */

uint32_t Adc_Get_seek_finally(void) // 使用的是5528的光敏电阻
{
	uint16_t adcx;
	uint32_t temp;
	adcx = Adc_Get_seek(SEEK_ADC_CH);
	temp = (uint32_t)(10240000 / (1.1 * adcx) - 2500); // 电阻的阻值
	return temp;
}

/*
 * OLED显示光敏的阻值
 *
 * OLED display photosensitive resistance
 * */

void user_lightseek_detect(void)
{
	uint32_t seek_number = 0;
	seek_number = Adc_Get_seek_finally();
	char seek[15];
	sprintf(seek, "Seek:%d", (int)seek_number);
	OLED_Draw_Line(seek, 3, true, true);
}
