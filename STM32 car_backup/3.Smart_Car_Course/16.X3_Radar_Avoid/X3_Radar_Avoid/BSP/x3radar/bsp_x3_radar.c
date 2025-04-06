#include "bsp_x3_radar.h"

uint8_t g_recvbuf[200] = {'\0'}; // Cache a packet of data 一包数据的缓存

int X3dis[X3CYCLE] = {'\0'}; // Data subscript: represents angle, data is distance 数据下标:代表角度,数据即距离

X3_Msg_t g_x3_msg;
X3_Radar_t x3_new[X3LEN];

// The total amount of effective information in a circle of data 一次数据的有效信息总量
volatile uint16_t g_group_all_num = 0;

void Recv_Radar(uint8_t rxtemp)
{
	static uint8_t step = 0;
	static uint8_t si_lsn = 0;
	static uint8_t si_index = 0;

	switch (step)
	{

	case 0:
		if (rxtemp == 0xAA)
		{
			step = 1;
			g_recvbuf[0] = 0xAA;
		}
		break;

	case 1:
		if (rxtemp == 0x55)
		{
			step = 2;
			g_recvbuf[1] = 0x55;
		}
		else
		{
			step = 0;
		}
		break;

	case 2:
		g_recvbuf[step] = rxtemp;
		step++;
		break; // CT information CT信息
	case 3:
		g_recvbuf[step] = rxtemp;
		step++;
		si_lsn = rxtemp * 2;
		break; // Number of S S的数量

	case 4:
		g_recvbuf[step] = rxtemp;
		step++;
		break; // Starting angle low 8 bits 起始角低8位
	case 5:
		g_recvbuf[step] = rxtemp;
		step++;
		break; // Starting angle high 8 bits 起始角高8位

	case 6:
		g_recvbuf[step] = rxtemp;
		step++;
		break; // End angle low 8 bits 结束角低8位
	case 7:
		g_recvbuf[step] = rxtemp;
		step++;
		break; // End angle height 8 bits 结束角高8位

	case 8:
		g_recvbuf[step] = rxtemp;
		step++;
		break; // Check code low 8 bits 校验码低8位
	case 9:
		g_recvbuf[step] = rxtemp;
		step++;
		break; // Check code high 8 digits 校验码高8位

	case 10:
	{
		g_recvbuf[step + si_index] = rxtemp;
		si_index++;

		if (si_index >= si_lsn)
		{
			Deal_Radar();
			si_index = 0;
			step = 0; // Received a packet of data 接收完一包数据
		}

		break;
	}
	}
}

// Install small end data into large end storage and process it 把小端的数据装成大端的储存方式并处理
void Deal_Radar(void)
{
	X3_Msg_t *x3_msg = &g_x3_msg;
	uint8_t llen = g_recvbuf[3] * 2; // length 长度
	uint8_t si_index = 0;

	x3_msg->PH = g_recvbuf[1] << 8 | g_recvbuf[0];
	x3_msg->CT = g_recvbuf[2];
	x3_msg->LSN = g_recvbuf[3];
	x3_msg->FSA = g_recvbuf[5] << 8 | g_recvbuf[4];
	x3_msg->LSA = g_recvbuf[7] << 8 | g_recvbuf[6];
	x3_msg->CS = g_recvbuf[9] << 8 | g_recvbuf[8];

	for (uint8_t i = 0; i < llen; i += 2)
	{
		x3_msg->SI[si_index++] = g_recvbuf[10 + i + 1] << 8 | g_recvbuf[10 + i];
	}

	// XOR processing 异或处理
	if (ISdoubleBit(x3_msg) != 0) // Verification code error 校验码错误
	{
		memset(g_recvbuf, 0, sizeof(g_recvbuf));
		memset(x3_msg, 0, sizeof(g_x3_msg));
		return;
	}

	// CT-bit0 bit judgment CT-bit0位判断
	//	if((x3_msg->CT & 0x01) == 1)//Starting packet for a round of data 一圈数据的起始包
	//	{
	//	}
	//	else  //Point cloud data package 点云数据包
	//	{
	//
	//
	//	}

	// Data solving function 数据解算函数
	Get_X3_Data(x3_msg);

	//保存数据
	Store_360angle_data();
}

uint8_t ISdoubleBit(X3_Msg_t *msg)
{
	uint16_t result = 0;
	uint16_t second = (msg->LSN << 8) | msg->CT; // Combination of CT and LSN, with LSN leading CT和LSN的合体，LSN在前
	uint8_t len_temp = msg->LSN;
	result = msg->PH ^ second ^ msg->FSA ^ msg->LSA;

	do
	{
		result ^= msg->SI[len_temp - 1]; // Array starts from 0 数组从0开始
		len_temp--;
	} while (len_temp);

	if (result != msg->CS)
	{
		return 1; // Verification code error 校验码错误
	}

	return 0;
}

// 数据解算函数  x3_new使用的是环形队列数据存储方式
// Data solving function x3_ New uses a circular queue data storage method
void Get_X3_Data(X3_Msg_t *msg)
{
	double start_angle, end_angle, abs_angle;
	for (uint8_t len = 0; len < msg->LSN; len++)
	{
		x3_new[len].dis = Get_X3dis(msg->SI[len]); // Obtain distance data 获取距离数据
	}

	// Level 1 solution 1级解算
	start_angle = Get_Level_X3angle(msg->FSA); // Start angle 起始角
	end_angle = Get_Level_X3angle(msg->LSA);   // End angle 结束角

	// Starting angle data storage 起始角数据存储
		x3_new[g_group_all_num].angle = start_angle;

	// End Corner Data Storage 结束角数据存储
		x3_new[msg->LSN - 1].angle = end_angle;

	if (start_angle > end_angle) // 350->10This situation 350->10这种情况
	{
		abs_angle = 360 - start_angle + end_angle;
	}
	else // normal conditions 正常情况
	{
		abs_angle = end_angle - start_angle;
	}

	// Middle angle calculation 中间角解算
	if (abs_angle != 0)
	{
		for (uint8_t len = 1; len < msg->LSN - 1; len++) // 0 is the starting angle; Msg ->LSN-1: Final angle 0是起始角;  msg->LSN-1:最终角
		{
			x3_new[len].angle = Get_Mid_X3angle(abs_angle, len, msg->LSN - 1, start_angle);
		}
	}
	// Level 2 angle calculation, with the function of correcting deviations 角度2级解算，具有纠正偏差作用
	for (uint8_t len = 0; len < msg->LSN; len++)
	{
		// Obtain Level 2 solution angle data 获取2级解算角度数据
		x3_new[len].angle = Get_Leve2_X3angle(x3_new[len].angle, x3_new[len].dis);

	}

	g_group_all_num = msg->LSN; // Accumulate a circle of data 累加一圈数据
}

// Get Distance 获取距离
int Get_X3dis(uint16_t dis_temp)
{
	return (dis_temp >> 8) * 64 + ((dis_temp & 0x00FF) >> 2); // High 8 bits * 64+low 8 bits, remove the last two bits to determine the distance 高8位*64 + 低8位去掉最后两位即为距离
}

// Intermediate angle calculation 中间角度解算
double Get_Mid_X3angle(double abs_angle, uint8_t index, uint8_t data_len, double s_angle)
{
	double angle_temp = abs_angle / data_len * index;

	angle_temp += s_angle;
	return Measure_If_360(angle_temp);
}

// Calculation of starting and ending angles 起始角、结束角解算
double Get_Level_X3angle(uint16_t S_angle)
{
	// Level 1 solution 1级解算
	double angle_temp = (double)((S_angle >> 1) / 64.0);
	return angle_temp;
}

// Angle Level 2 Solution (Correction) 角度2级解算(纠正)
double Get_Leve2_X3angle(double angle, int Ddis)
{
	if (Ddis == 0)
		return angle;

	// Level 2 solution 2级解算
	double angcorrect = 0;
	angcorrect = 21.8 * ((155.3 - Ddis) / (155.3 * Ddis));
	angcorrect = atan(angcorrect) * 180 / 3.1415925;

	angcorrect = angle + angcorrect;

	return Measure_If_360(angcorrect);
}

// Determine if the angle meets the range of 360 ° 判断角是否符合360°的范围
double Measure_If_360(double angle)
{
	if (angle > 360)
	{
		return angle - 360;
	}

	if (angle < 0)
	{
		return 360 + angle;
	}

	return angle;
}

// 保存360度的数据
// Save 360 degree data
void Store_360angle_data(void)
{
	static u16 dis_max = 16383;
	u16 x3dis_index = 0;
	for (u16 len = 0; len < g_group_all_num; len++)
	{
		if (x3_new[len].angle > 360 || x3_new[len].angle < 0) // Illegal angle 角度不合法
			continue;
		x3dis_index = (u16)(x3_new[len].angle);
		X3dis[x3dis_index] = x3_new[len].dis;
		if (X3dis[x3dis_index] > dis_max)
		{
			X3dis[x3dis_index] = dis_max; // Not exceeding the maximum protocol value 不超过协议最大值
		}
	}

	g_group_all_num = 0; //保存完数据清0
}
