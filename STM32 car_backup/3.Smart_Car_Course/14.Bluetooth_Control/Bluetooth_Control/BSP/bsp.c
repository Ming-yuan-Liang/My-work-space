#include "bsp.h"

//app只控制S1路的舵机
//The app only controls the servo of S1 channel

//0: If you don't go in and control the steering gear, it will be interrupted. 1: If you go in and control the steering gear, it can only control the rotation angle, but it won't lock up.
//You can change the angle by turning it manually.
//0:不进去控制舵机中断了 1:进去舵机中断  只能是控制转动的角度，但不锁死，可以用手转动改变角度。
uint8_t g_servo_falg = 0;

//Hardware Initialization
//Parameter:None
void BSP_Init(void)
{
	Delay_Init();
	IR_SWitch(ENABLE);

	Bsp_Tim_Init();
	PID_Param_Init();//电机PID初始化 Motor PID initialization

	OLED_Init();//OLED初始化 OLED initialization
	OLED_Draw_Line("Bluetooth Control.", 1, false, true);

	UART5_Init();//串口5开启中断 Serial port 5 enable interrupt

	Tim_Base_Init();

	PwmServo_Set_Angle_All(90,90,90,90);//舵机归中 Steering gear centering
}

extern int send_time;//引入中断标志 Introducing interrupt flags

//Loop Run Function
//Parameter:None
void BSP_Loop(void)
{
	OLED_SHOW_BAT();//显示电量 Display battery level

	if(g_modeSelect == 0 || g_modeSelect ==1 )
	{
		OLED_SHOW_Car_Speed();

		if(send_time ==0 )
		{
			Send_Msg();//上报数据 10ms发一次 Report data once every 10ms
		}

	}

	USE_Bluetooth_Control();


}
