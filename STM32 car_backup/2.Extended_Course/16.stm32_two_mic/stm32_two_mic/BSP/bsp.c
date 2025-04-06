#include "bsp.h"

// Hardware Initialization
// Parameter:None
void BSP_Init(void)
{
	// Serial port 4 is connected to the serial port of the voice module 串口4接语音模块的串口
	UART4_Init();
}

// Loop Run Function
// Parameter:None
void BSP_Loop(void)
{
	Change_RGB((Control_RGB_t)Get_Massage());
}

// 函数功能:控制板载RGB
// 传入函数:Control_RGB_t
// Function function: Control onboard RGB
// Incoming function: Control_RGB_t
void Change_RGB(Control_RGB_t rgb_flag)
{
	switch (rgb_flag)
	{
	case close_light:
		RGB_OFF_ALL;
		break;
	case red_light:
		Set_Color_R(red);
		Set_Color_L(red);
		break;
	case green_light:
		Set_Color_R(green);
		Set_Color_L(green);
		break;
	case blue_light:
		Set_Color_R(blue);
		Set_Color_L(blue);
		break;
	case yellow_light:
		Set_Color_R(yellow);
		Set_Color_L(yellow);
		break;
	}

	Send_Massage((uint16_t)rgb_flag);
}
