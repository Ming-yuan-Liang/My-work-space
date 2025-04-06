#include "bsp_ccd.h"

uint16_t ADV[128] = {0};
uint8_t CCD_median, CCD_threshold;

// Function: The AD sampling
// Input   : The ADC channels
// Output  : AD conversion results
// 函数功能：AD采样
// 入口参数：ADC的通道
// 返回  值：AD转换结果
uint16_t Get_Adc_CCD(uint8_t ch)
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

// 函数功能:延迟
// 入口参数:无
// 返回值：无
// Function Function: Delay
// Entry parameters: None
// Return value: None
void Dly_us(void)
{
	int ii;
	for (ii = 0; ii < 10; ii++)
		;
}

// 函数功能：CCD数据采集
// 入口参数：无
// 返回  值：无
// Function function: CCD data collection
// Entry parameters: None
// Return value: None
void RD_TSL(void)
{
	uint8_t i = 0, tslp = 0;
	TSL_CLK = 1;
	TSL_SI = 0;
	Dly_us();

	TSL_SI = 1;
	TSL_CLK = 0;
	Dly_us();

	TSL_CLK = 1;
	TSL_SI = 0;
	Dly_us();
	for (i = 0; i < 128; i++) // Read 128 pixel voltage values 读取128个像素点电压值
	{
		TSL_CLK = 0;
		Dly_us(); // Adjusting exposure time 调节曝光时间
		Dly_us();

		ADV[tslp] = (Get_Adc_CCD(CCD_ADC_CH)) >> 4;
		++tslp;
		TSL_CLK = 1;
		Dly_us();
	}
}

// Start CCD collection and processing of output data 开始CCD采集并处理输出数据
void Deal_Data_CCD(void)
{
	RD_TSL();
	Find_CCD_Median();
}

void Find_CCD_Median(void)
{

	static uint16_t i, j, Left, Right;
	static uint16_t value1_max, value1_min;

	value1_max = ADV[0];	  // Dynamic threshold algorithm, reading maximum and minimum values 动态阈值算法，读取最大和最小值
	for (i = 5; i < 123; i++) // Remove 5 points on each side 两边各去掉5个点
	{
		if (value1_max <= ADV[i])
			value1_max = ADV[i];
	}
	value1_min = ADV[0]; // MIN 最小值
	for (i = 5; i < 123; i++)
	{
		if (value1_min >= ADV[i])
			value1_min = ADV[i];
	}
	CCD_threshold = (value1_max + value1_min) / 2; // Calculate the threshold for this centerline extraction 计算出本次中线提取的阈值
	for (i = 5; i < 118; i++)					   // Find the left jump edge 寻找左边跳变沿
	{
		if (ADV[i] > CCD_threshold && ADV[i + 1] > CCD_threshold && ADV[i + 2] > CCD_threshold && ADV[i + 3] < CCD_threshold && ADV[i + 4] < CCD_threshold && ADV[i + 5] < CCD_threshold)
		{
			Left = i;
			break;
		}
	}
	for (j = 118; j > 5; j--) // Find the right jump edge 寻找右边跳变沿
	{
		if (ADV[j] < CCD_threshold && ADV[j + 1] < CCD_threshold && ADV[j + 2] < CCD_threshold && ADV[j + 3] > CCD_threshold && ADV[j + 4] > CCD_threshold && ADV[j + 5] > CCD_threshold)
		{
			Right = j;
			break;
		}
	}
	CCD_median = (Right + Left) / 2; // Calculate centerline position 计算中线位置
}

// Printing CCD data 打印CCD的数据
void Print_CCD_data(void)
{
	static uint8_t key_cnt = 0;
	if (Key1_State(1))
	{
		key_cnt = !key_cnt;
		if (key_cnt)
		{
			printf("Print Median and Threshold\r\n");
			printf("********************************\r\n");
		}
		else
		{
			printf("Print raw data\r\n");
			printf("#################################\r\n");
		}
	}
	if (key_cnt) // 为1时
	{
		printf("\r\n");
		Deal_Data_CCD();
		printf("The median of this data is:%d\r\n", CCD_median);
		printf("The light intensity threshold for this data is:%d\r\n", CCD_threshold);
		printf("\r\n");
		OLED_Show_CCD_Image(CCD_Get_ADC_128X32()); // OLED display of CCD data OLED 显示 CCD数据
	}
	// Print raw data 打印原始数据
	else
	{
		printf("**********************************\r\n");
		RD_TSL();
		for (uint8_t i = 0; i < 128; i++)
		{
			if (i % 8 == 0)
			{
				printf("\r\n"); // Replace 8 data lines 8个数据换一行
			}
			printf("ADV[%d]:%d \t", i, ADV[i]);
		}
	}
}

uint8_t ADC_128X32[128] = {0};
// Return the ADV acquisition voltage values of 128 pixels and compress the amplitude into 128 * 32.  返回128个像素点的ADV采集电压值，并将幅值压缩成128*32。
uint8_t *CCD_Get_ADC_128X32(void)
{
	//		RD_TSL(); //Obtained during serial output 串口输出的时候已经获取
	// Convert 8-bit AD values to 5-bit AD values 将8位AD值转化成5位AD值
	for (int i = 0; i < 128; i++)
	{
		ADC_128X32[i] = ADV[i] >> 3;
	}
	return ADC_128X32;
}

void OLED_Show_CCD_Image(uint8_t *p_img)
{
	OLED_Clear();
	for (int i = 0; i < 128; i++)
	{
		if (p_img[i] < 32)
		{
			SSD1306_DrawPixel(i, p_img[i], SSD1306_COLOR_WHITE);
		}
	}
	OLED_Refresh();
}
