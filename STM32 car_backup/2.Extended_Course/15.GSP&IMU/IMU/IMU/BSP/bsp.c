/*
 * bsp.c
 *
 *  Created on: Oct 18, 2023
 *      Author: YB-101
 */

#include "bsp.h"



#define ACC_UPDATE		0x01
#define GYRO_UPDATE		0x02
#define ANGLE_UPDATE	0x04
#define MAG_UPDATE		0x08
#define READ_UPDATE		0x80
static volatile char s_cDataUpdate = 0, s_cCmd = 0xff;
const uint32_t c_uiBaud[10] = {0, 4800, 9600, 19200, 38400, 57600, 115200, 230400, 460800, 921600};


static void AutoScanSensor(void);
static void SensorUartSend(uint8_t *p_data, uint32_t uiSize);
static void SensorDataUpdata(uint32_t uiReg, uint32_t uiRegNum);
static void Delayms(uint16_t ucMs);

//Hardware Initialization
//Parameter:None

uint8_t i;
float fAcc[3], fGyro[3], fAngle[3];
float fAngle_tmp = 0;

void BSP_Init(void)
{
	UART4_Init();

	WitInit(WIT_PROTOCOL_NORMAL, 0x50);
	WitSerialWriteRegister(SensorUartSend);
	WitRegisterCallBack(SensorDataUpdata);
	WitDelayMsRegister(Delayms);
	printf("\r\n********************** wit-motion normal example  ************************\r\n");
	AutoScanSensor();

}


//Loop Run Function
//Parameter:None
void BSP_Loop(void)
{

	if(s_cDataUpdate)
	{
		for(i = 0; i < 3; i++)
		{
			fAcc[i] = sReg[AX+i] / 32768.0f * 16.0f;
			fGyro[i] = sReg[GX+i] / 32768.0f * 2000.0f;
		}
		if((sReg[TEMP] - sReg[Roll] > 10) |( sReg[Roll] - sReg[TEMP] > 10))
		{
			fAngle[0] = sReg[Roll] / 32768.0f * 180.0f;
			fAngle_tmp = fAngle[0];
		}
		else   fAngle[0] = fAngle_tmp;

		for(i = 1; i<3;i++)
		{
			fAngle[i] = sReg[Roll+i] / 32768.0f * 180.0f;
		}

		if(s_cDataUpdate & ACC_UPDATE)
		{
			printf("acc:%.3f %.3f %.3f\r\n", fAcc[0], fAcc[1], fAcc[2]);//打印acc的数据 Print acc data
			HAL_Delay(300);
			s_cDataUpdate &= ~ACC_UPDATE;
		}
		if(s_cDataUpdate & GYRO_UPDATE)
		{
			printf("gyro:%.3f %.3f %.3f\r\n", fGyro[0], fGyro[1], fGyro[2]);//打印gyro的数据 打印gyro的数据
			HAL_Delay(300);
			s_cDataUpdate &= ~GYRO_UPDATE;
		}
		if(s_cDataUpdate & ANGLE_UPDATE)
		{
			printf("angle:%.3f %.3f %.3f\r\n", fAngle[0], fAngle[1], fAngle[2]);//打印angle的数据 Print the data of angle
			HAL_Delay(300);
			s_cDataUpdate &= ~ANGLE_UPDATE;
     	}
		if(s_cDataUpdate & MAG_UPDATE)
		{
			printf("mag:%d %d %d\r\n", sReg[HX], sReg[HY], sReg[HZ]);//打印mag的数据 Print mag data
			HAL_Delay(300);
			s_cDataUpdate &= ~MAG_UPDATE;
		}
	}
}

/*
 * 通过串口4发送imu数据
 *
 * Send imu data through serial port 4
 * */

static void SensorUartSend(uint8_t *p_data, uint32_t uiSize)
{
	Uart4_Send(p_data, uiSize);
}

static void Delayms(uint16_t ucMs)
{
	HAL_Delay(ucMs);
}

/*
 * 更新imu数据
 *
 * Update imu data
 * */

static void SensorDataUpdata(uint32_t uiReg, uint32_t uiRegNum)
{
	int i;
    for(i = 0; i < uiRegNum; i++)
    {
        switch(uiReg)
        {
//            case AX:
//            case AY:
            case AZ:
				s_cDataUpdate |= ACC_UPDATE;
            break;
//            case GX:
//            case GY:
            case GZ:
				s_cDataUpdate |= GYRO_UPDATE;
            break;
//            case HX:
//            case HY:
            case HZ:
				s_cDataUpdate |= MAG_UPDATE;
            break;
//            case Roll:
//            case Pitch:
            case Yaw:
				s_cDataUpdate |= ANGLE_UPDATE;
            break;
            default:
				s_cDataUpdate |= READ_UPDATE;
			break;
        }
		uiReg++;
    }
}

/*
 * 检查imu是否连接
 * Check if imu is connected
 *
 * */
static void AutoScanSensor(void)
{
	int iRetry;
		iRetry = 2;
		do
		{
			s_cDataUpdate = 0;
			WitReadReg(AX, 3);
			HAL_Delay(100);
			if(s_cDataUpdate != 0)
			{
				return ;
			}
			iRetry--;
		}while(iRetry);

	printf("can not find sensor\r\n");
	printf("please check your connection\r\n");
}

