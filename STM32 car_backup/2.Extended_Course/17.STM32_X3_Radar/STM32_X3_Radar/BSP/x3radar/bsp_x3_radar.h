#ifndef __BSP_X3_RADAR_H_
#define __BSP_X3_RADAR_H_

#include "bsp.h"

#define SILEN 45	// SI length of a packet protocol 一包协议的SI长度
#define X3LEN 200	// Effective data storage 有效数据储存
#define X3CYCLE 360 // The number of rotatable degrees of a radar circle 雷达的一圈可转度数

// The final information structure of radar 雷达的最终信息结构体
typedef struct _x3_radar
{
	int dis;	  // distance 距离
	double angle; // angle 角度
} X3_Radar_t;

// Protocol Structure 协议结构体
typedef struct _x3_msg_
{
	uint16_t PH;		// header 包头
	uint8_t CT;			// CT information CT信息
	uint8_t LSN;		// Length of SI SI的长度
	uint16_t FSA;		// Start angle 起始角
	uint16_t LSA;		// End Corner 结束角
	uint16_t CS;		// Check Code 校验码
	uint16_t SI[SILEN]; // Data Valid Array 数据有效数组
} X3_Msg_t;

void Recv_Radar(uint8_t rxtemp);
void Deal_Radar(void);
uint8_t ISdoubleBit(X3_Msg_t *msg);
double Get_Level_X3angle(uint16_t S_angle);
int Get_X3dis(uint16_t dis_temp);
double Get_Mid_X3angle(double abs_angle, uint8_t lenght, uint8_t data_len, double s_angle);
double Measure_If_360(double angle);
double Get_Leve2_X3angle(double angle, int Ddis);
void Get_X3_Data(X3_Msg_t *msg);
void Store_360angle_data(void);

extern X3_Radar_t x3_new[X3LEN];
extern int X3dis[X3CYCLE];
#endif
