#ifndef BSP_USART_H_
#define BSP_USART_H_

#include "stdio.h"
#include "string.h"
#include "usart.h"
#include "bsp.h"

#define RXBUFFERSIZE 200

#define false 0
#define true 1
// 定义数组长度 Define array length
#define GPS_Buffer_Length 80
#define UTCTime_Length 11
#define latitude_Length 11
#define N_S_Length 2
#define longitude_Length 12
#define E_W_Length 2

typedef struct SaveData
{
	char GPS_Buffer[GPS_Buffer_Length];
	char isGetData;					  // 是否获取到GPS数据 Whether to obtain GPS data
	char isParseData;				  // 是否解析完成 Is parsing completed?
	char UTCTime[UTCTime_Length];	  // UTC时间 UTC time
	char latitude[latitude_Length];	  // 纬度 latitude
	char N_S[N_S_Length];			  // N/S
	char longitude[longitude_Length]; // 经度 longitude
	char E_W[E_W_Length];			  // E/W
	char isUsefull;					  // 定位信息是否有效 Is the positioning information valid?
} _SaveData;

extern uint16_t point1;
extern _SaveData Save_Data;

void CLR_Buf(void);
uint8_t Hand(char *a);
void clrStruct(void);

void Bsp_UART1_Init(void);

#endif /* BSP_USART_H_ */
