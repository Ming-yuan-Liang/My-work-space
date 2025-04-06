#include "bsp.h"

// Hardware Initialization
// Parameter:None
void BSP_Init(void)
{
	Delay_Init();
	WS281x_Init();

	WS2812_AllOpen(C_Purple); // 亮紫色 bright purple
}

// Loop Run Function
// Parameter:None
void BSP_Loop(void)
{
	if (Key1_State(0))
	{
		SSwitch_AllOpen_Color(300); // 设置所有灯的颜色在300ms切换 Set the color of all lights to switch in 300ms
		WS281x_CloseAll();			// 关闭所有灯 turn off all lights
	}
	if (Key2_State(0))
	{
		WS281x_Rainbow(50); // 在50ms内转换颜色 Convert colors in 50ms
		WS281x_CloseAll();
	}
	if (Key3_State(0))
	{
		WS2812_All_LED_ONE_Color_Breath(30, C_Green); // 绿色呼吸灯 green breathing light
		WS281x_CloseAll();
	}
}
