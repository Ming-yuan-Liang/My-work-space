/*
 * gps.c
 *
 *  Created on: Oct 25, 2023
 *      Author: YB-101
 */

#include "gps.h"

/*
 * 打印错误记录
 * num：错误序号
 *
 * Print error log
 * num: error number
 * */

void errorLog(int num)
{

	while (1)
	{
		printf("ERROR%d\r\n", num);
	}
}

/*
 * 解析数据
 *
 * Analytical GPS data
 * */

void parseGpsBuffer()
{
	char *subString;
	char *subStringNext;
	char i = 0;
	if (Save_Data.isGetData)
	{
		Save_Data.isGetData = false;
		printf("**************\r\n");
		printf(Save_Data.GPS_Buffer);

		for (i = 0; i <= 6; i++)
		{
			if (i == 0)
			{
				if ((subString = strstr(Save_Data.GPS_Buffer, ",")) == NULL)
					errorLog(1); // 解析错误 Parse error
			}
			else
			{
				subString++;
				if ((subStringNext = strstr(subString, ",")) != NULL)
				{
					char usefullBuffer[2];
					switch (i)
					{
					case 1:
						memcpy(Save_Data.UTCTime, subString, subStringNext - subString);
						break; // 获取UTC时间 Get UTC time
					case 2:
						memcpy(usefullBuffer, subString, subStringNext - subString);
						break; // 获取UTC时间 Get UTC time
					case 3:
						memcpy(Save_Data.latitude, subString, subStringNext - subString);
						break; // 获取纬度信息 Get latitude information
					case 4:
						memcpy(Save_Data.N_S, subString, subStringNext - subString);
						break; // 获取N/S Get N/S
					case 5:
						memcpy(Save_Data.longitude, subString, subStringNext - subString);
						break; // 获取经度信息 Get longitude information
					case 6:
						memcpy(Save_Data.E_W, subString, subStringNext - subString);
						break; // 获取E/W Get E/W

					default:
						break;
					}

					subString = subStringNext;
					Save_Data.isParseData = true;
					if (usefullBuffer[0] == 'A')
						Save_Data.isUsefull = true;
					else if (usefullBuffer[0] == 'V')
						Save_Data.isUsefull = false;
				}
				else
				{
					errorLog(2); // 解析错误 Parse error
				}
			}
		}
	}
}

/*
 * 打印gps数据
 *
 * print gps data
 * */

void printGpsBuffer()
{
	if (Save_Data.isParseData)
	{
		Save_Data.isParseData = false;

		printf("Save_Data.UTCTime = ");
		printf(Save_Data.UTCTime);
		printf("\r\n");

		if (Save_Data.isUsefull)
		{
			Save_Data.isUsefull = false;
			printf("Save_Data.latitude = ");
			printf(Save_Data.latitude);
			printf("\r\n");

			printf("Save_Data.N_S = ");
			printf(Save_Data.N_S);
			printf("\r\n");

			printf("Save_Data.longitude = ");
			printf(Save_Data.longitude);
			printf("\r\n");

			printf("Save_Data.E_W = ");
			printf(Save_Data.E_W);
			printf("\r\n");
		}
		else
		{
			printf("GPS DATA is not usefull!\r\n");
		}
	}
}
