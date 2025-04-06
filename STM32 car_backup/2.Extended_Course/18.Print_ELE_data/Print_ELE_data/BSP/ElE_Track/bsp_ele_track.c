#include "bsp_ele_track.h"

int Sensor_Left_1, Sensor_Left_2, Sensor_Left_3;
int Sensor_Right_1, Sensor_Right_2, Sensor_Right_3;
int Sensor_Middle;
int ele_seat = 0;

/**************************************************************************
函数功能：AD采样
入口参数：ADC1 的通道
返回  值：AD转换结果
Function function: AD sampling
Entry parameter: ADC1 channel
Return value: AD conversion result
**************************************************************************/
uint16_t Get_Adc_ele(uint8_t ch)
{
	// Set the specified ADC's rule group channel, a sequence, and sampling time 设置指定ADC的规则组通道，一个序列，采样时间
	ADC_ChannelConfTypeDef sConfig = {0};
	sConfig.Channel = ch;
	sConfig.Rank = ADC_REGULAR_RANK_1;
	sConfig.SamplingTime = ADC_SAMPLETIME_239CYCLES_5;
	if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
	{
		Error_Handler();
	}

	HAL_ADC_Start(&hadc1);
	HAL_ADC_PollForConversion(&hadc1, 500);
	return HAL_ADC_GetValue(&hadc1);
}

// 函数功能：将得到的数据做处理
// Function function: Process the obtained data
int guiyi_way(void)
{
	int sum, Sensor;
	int Sensor_Left, Sensor_Right;

	//	sum=(Sensor_Right_1*1+Sensor_Right_2*100+Sensor_Right_3*200)
	//			+ Sensor_Middle *300
	//			+(Sensor_Left_1*400+Sensor_Left_2*500+Sensor_Left_3*599);  //Normalization processing 归一化处理

	// Remove vertical inductance 去掉垂直的电感
	sum = (Sensor_Right_1 * 1 + Sensor_Right_3 * 100) + Sensor_Middle * 200 + (Sensor_Left_1 * 300 + Sensor_Left_3 * 400); // Normalization processing 归一化处理

	Sensor_Left = Sensor_Left_1 + Sensor_Left_3;	//+Sensor_Left_2
	Sensor_Right = Sensor_Right_1 + Sensor_Right_3; //+Sensor_Right_2

	Sensor = sum / (Sensor_Left + Sensor_Middle + Sensor_Right); // Find deviation 求偏差
	return Sensor;												 // Return to the current position in the magnetic field 返回目前的在磁场的位置
}

// Obtain sensor data 获取传感器数据
void getEleData(void)
{
	// 小车屁股对着自己，从左到右数
	//	The car's butt is facing itself, counting from left to right
	Sensor_Right_1 = Get_Adc_ele(ELE_R1_CH); // Collect data on the inductance on the right side 采集右边电感的数据
	Sensor_Right_2 = Get_Adc_ele(ELE_R2_CH); // Collect data on the inductance on the right side 采集右边电感的数据
	Sensor_Right_3 = Get_Adc_ele(ELE_R3_CH); // Collect data on the inductance on the right side 采集右边电感的数据

	Sensor_Middle = Get_Adc_ele(ELE_M1_CH); // Collect data on intermediate inductance 采集中间电感的数据

	Sensor_Left_1 = Get_Adc_ele(ELE_L1_CH); // Collect data on the left inductance 采集左边电感的数据
	Sensor_Left_2 = Get_Adc_ele(ELE_L2_CH); // Collect data on the left inductance 采集左边电感的数据
	Sensor_Left_3 = Get_Adc_ele(ELE_L3_CH); // Collect data on the left inductance 采集左边电感的数据
}

// Data displayed on screen 数据显示在屏幕上
void EleDataDeal(void)
{

	char ele_data[30] = {'\0'};
	getEleData();
	ele_seat = guiyi_way();

	// Algorithm processing for printing to serial port assistant 算法处理的打印到串口助手
	printf("ele_seat:%d   \r\n", ele_seat);
	// Print the middle value to the serial assistant 中间的值打印到串口助手
	printf("MID:%d   \r\n", Sensor_Middle);
	printf("**************\r\n");

	sprintf(ele_data, "L1:%d  L2:%d        ", Sensor_Left_1, Sensor_Left_2);
	OLED_Draw_Line(ele_data, 1, false, true);

	sprintf(ele_data, "L3:%d  R1:%d        ", Sensor_Left_3, Sensor_Right_1);
	OLED_Draw_Line(ele_data, 2, false, true);

	sprintf(ele_data, "R2:%d  R3:%d        ", Sensor_Right_2, Sensor_Right_3);
	OLED_Draw_Line(ele_data, 3, false, true);
}
