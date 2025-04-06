
#include "bsp_k210.h"

char buf_msg[20] = {'\0'};
uint8_t g_new_flag = 0;
uint8_t g_index = 0;
uint8_t g_new_data = 0; //1:数据接收完成

// 函数功能:保留k210的信息
// 传入函数:recv_msg:串口发来的信息
// Function function: Preserve information of k210
// Incoming function: recv_ Msg: Information sent from serial port
void Deal_K210(uint8_t recv_msg)
{
	if (recv_msg == '$'&& g_new_flag == 0)
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
			g_new_data = 1;
		}

		if (g_new_flag == 1 && recv_msg != '$')
		{
			buf_msg[g_index++] = recv_msg;

			if(g_index > 20) //数组溢出 Array overflow
			{
				g_index = 0;
				g_new_flag = 0;
				g_new_data = 0;
				memset(buf_msg, 0, sizeof(buf_msg)); // Clear old data 清除旧数据
			}

		}
	}
}

/*
 * 函数功能：根据k210发来的不同指令进行不同的动作
 *
 *Function: perform different actions according to different instructions sent by k210
 * */

void Change_state(void)
{
	if(g_new_data == 1)
	{
		if (strcmp("1", buf_msg) == 0 )
		  {
			Motion_Set_Speed(250,250,250,250);//小车前进两秒后停止
			HAL_Delay(2000);
			wheel_State(MOTION_STOP,0);
		  }
		else if (strcmp("2", buf_msg) == 0 )
		  {
			Motion_Set_Speed(500,500,0,0);
			HAL_Delay(1000);
			Motion_Set_Speed(250,250,250,250);//小车右转一秒然后前进一秒后停止
			HAL_Delay(1000);
			wheel_State(MOTION_STOP,0);

		  }
		else if (strcmp("3", buf_msg) == 0)
		  {
			Motion_Set_Speed(0,0,500,500);
			HAL_Delay(1000);
			Motion_Set_Speed(250,250,250,250);//小车左转一秒然后前进一秒后停止
			HAL_Delay(1000);
			wheel_State(MOTION_STOP,0);
		  }
		g_new_data = 0;
	}




}

