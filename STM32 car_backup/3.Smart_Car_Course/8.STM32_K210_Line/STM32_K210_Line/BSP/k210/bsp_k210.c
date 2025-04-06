#include "bsp_k210.h"

uint8_t buf_msg[20] = {'\0'};
uint8_t g_new_flag = 0;
uint8_t g_index = 0;


K210_Data_t K210_data;

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
			Get_K210_Data(); // New data received completed 新数据接收完毕
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

//函数功能:获取识别图像的中心点X\Y坐标
//传入参数:无
//Function function: Obtain the X  Y coordinates of the center point of the recognition image
//Incoming parameter: None
void Get_K210_Data(void)
{
	K210_data.k210_X = (buf_msg[0] -'0') *100 + (buf_msg[1] -'0') *10 + (buf_msg[2] -'0');

	K210_data.k210_Y = (buf_msg[3] -'0') *100 + (buf_msg[4] -'0') *10 + (buf_msg[5] -'0');
}




