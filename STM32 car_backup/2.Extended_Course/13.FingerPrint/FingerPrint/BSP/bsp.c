#include "bsp.h"


//Hardware Initialization
//Parameter:None
void BSP_Init(void)
{
	//串口4的波特率是57600，也是指纹模块默认的波特率,图形化配置的时候要注意
	//The baud rate of serial port 4 is 57600, which is also the default baud rate for the fingerprint module.
	//When configuring graphically, it is important to pay attention to this
	UART4_Init();

	if(Finger_Init()==1)
	{
		while(1)
		{
			printf("Finger fail!\r\n");
			HAL_Delay(200);
		}
	}

}

//Loop Run Function
//Parameter:None
void BSP_Loop(void)
{
	Finger_Loop();
}
