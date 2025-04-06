#include "bsp_k210.h"

char buf_msg[20] = {'\0'};
uint8_t g_new_flag = 0;
uint8_t g_index = 0;

// 函数功能:保留k210的信息
// 传入函数:recv_msg:串口发来的信息
// Function function: Preserve information of k210
// Incoming function: recv_ Msg: Information sent from serial port
void Deal_K210(uint8_t recv_msg)
{
	if (recv_msg == '$' && g_new_flag == 0)
	{
		g_new_flag = 1;
		memset(buf_msg, 0, sizeof(buf_msg)); // Clear old data 清除旧数据
		return;
	}
	if(g_new_flag == 1)
	{
		if (recv_msg == '#')
		{
			g_new_flag = 0;
			g_index = 0;
			Change_RGB(); // New data received completed 新数据接收完毕
			memset(buf_msg, 0, sizeof(buf_msg)); // Clear old data 清除旧数据
		}

		else if (g_new_flag == 1 && recv_msg != '$')
		{
			buf_msg[g_index++] = recv_msg;

			if(g_index > 20) //数组溢出 Array overflow
			{
				g_index = 0;
				g_new_flag = 0;
				memset(buf_msg, 0, sizeof(buf_msg)); // Clear old data 清除旧数据
			}
		}
	}
}

// 函数功能:改变板载的RGB状态
// 传入参数:无
// Function function: Change the RGB state of the board
// Incoming parameter: None
void Change_RGB(void)
{
	// After receiving characters from K210, change the RGB light on the board 接收到k210的字符后进行改变板载的RGB灯
	if (strcmp("blue", buf_msg) == 0)
	{
		Set_Color_R(blue);
		Set_Color_L(blue);
	}
	else if (strcmp("red", buf_msg) == 0)
	{
		Set_Color_R(red);
		Set_Color_L(red);
	}
	else if (strcmp("green", buf_msg) == 0)
	{
		Set_Color_R(green);
		Set_Color_L(green);
	}
	else if (strcmp("yellow", buf_msg) == 0)
	{
		Set_Color_R(yellow);
		Set_Color_L(yellow);
	}
	else if (strcmp("purper", buf_msg) == 0)
	{
		Set_Color_R(purper);
		Set_Color_L(purper);
	}
	else if (strcmp("lake", buf_msg) == 0)
	{
		Set_Color_R(lake);
		Set_Color_L(lake);
	}
	else if (strcmp("close", buf_msg) == 0)
	{
		RGB_OFF_ALL;
	}
}



// 函数功能:控制K210上RGB灯的状态
// 传入参数:data_str:协议数据 datasize:数据长度
// Function function: Control the status of RGB lights on K210
// Incoming parameter: Data_ Str: protocol data datasize: data length
void Send_K210(uint8_t *data_str, uint16_t datasize)
{
	USART2_DataString(data_str, datasize);
}
