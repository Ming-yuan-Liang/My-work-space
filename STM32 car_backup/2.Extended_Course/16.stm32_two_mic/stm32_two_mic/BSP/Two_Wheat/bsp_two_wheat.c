#include "bsp_two_wheat.h"

uint8_t g_recv_buf[20] = {'\0'};
uint8_t g_recv_send_flag = 0; // Received and sent completed 1: Received but not sent 接收并发送完成 1：接收但没发送

// 函数功能:接收2麦的信息
// 传入函数:recv:串口接收到的信息
// Function function: Receive information from 2 microphones
// Incoming function: recv: Information received by serial port
void Deal_Two_Massage(uint8_t recv)
{

	static uint8_t recv_flag = 0;  // Flag for the start of reception 接收开始的标志
	static uint8_t recv_index = 0; // Index Flag 索引的标志

	if (recv == '$')
	{
		recv_flag = 1;
		memset(g_recv_buf, 0, sizeof(g_recv_buf));
	}

	if (recv == '#')
	{
		// Enter data processing 进入数据处理
		if (recv_flag == 1)
		{
			Massage_Deal(); // Incoming function 传入函数
			g_recv_send_flag = 1;
		}
		recv_flag = 0;
		recv_index = 0;
		memset(g_recv_buf, 0, sizeof(g_recv_buf));
		return;
	}

	if (recv_flag == 1)
	{
		if ((recv != '#') && (recv != '$')) // Remove$# 去$#
		{
			// Save valid data 有效数据存起来
			g_recv_buf[recv_index++] = recv;
		}
	}
}

uint16_t g_massage = 0;

// 函数功能:2麦信息处理
// 传入函数:无
// Function function: 2-microphone information processing
// Incoming function: None
void Massage_Deal(void) // Because the data is $B001#  因为数据是"$B001#"
{
	if (g_recv_buf[0] != 'B')
		return;

	uint8_t recv_buff[20] = {'\0'};
	my_strcmp(recv_buff, &g_recv_buf[1]);

	g_massage = atoi((char *)recv_buff);
}

// 函数功能:获取2麦信息的最新指令信息
// 传入函数:无
uint16_t Get_Massage(void)
{
	return g_massage;
}

// 函数功能:设置获取2麦信息的最新指令信息-一般不使用
// 传入函数:无
// Function function: Set the latest instruction information for obtaining 2-bit information - generally not used
// Incoming function: None
void Set_Massage(uint16_t num)
{
	g_massage = num;
}

// Send data to voice for broadcast feedback 发送数据给语音进行播报反馈
char send_buf[20] = {'\0'};

// 函数功能:发送数据给2麦，使其进行语音播报
// 传入函数:msg:信息
// Function function: Send data to 2 microphones for voice broadcasting
// Incoming function: msg: Information
void Send_Massage(uint16_t msg)
{
	if (g_recv_send_flag == 0)
		return;
	// The data transmitted is not the latest data 传过来的数据不是最新数据
	if (msg != g_massage)
		return;
	// If it is 0, no data will be returned 是0就不回传数据了
	if (msg == 0)
	{
		g_recv_send_flag = 0;
		return;
	}

	// The data type is $A010# 数据类型是$A010# \ $A101#
	if (msg < 100)
	{
		sprintf(send_buf, "$A0%d#", msg);
		if (msg < 10)
			sprintf(send_buf, "$A00%d#", msg);
	}
	else
	{
		sprintf(send_buf, "$A%d#", msg);
	}

	HAL_Delay(500); // We need to add a delay to the 2-wire reaction 要加延迟给2麦反应
	USRT4_DataString((uint8_t *)send_buf, strlen(send_buf));
	memset(send_buf, 0, sizeof(send_buf));
	g_recv_send_flag = 0;
}

// 函数功能:复制函数
// 传入函数:*str1：保存数据的地址  *str2：要复制数据的地址
void my_strcmp(uint8_t *str1, uint8_t *str2)
{
	while (*str2 != '\0')
	{
		*str1 = *str2;
		str2++;
		str1++;
	}
	*str1 = '\0';
}
