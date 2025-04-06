#include "bsp_RGB.h"

// Set the RGB light color on the right 设置右边的RGB灯颜色
void Set_Color_R(RGB_Color_t color)
{
	switch (color)
	{
	case red:
		RRGB_SET(1, 0, 0);
		break; // RED 红色
	case green:
		RRGB_SET(0, 1, 0);
		break; // Green 绿色
	case blue:
		RRGB_SET(0, 0, 1);
		break; // Bule 蓝色
	case yellow:
		RRGB_SET(1, 1, 0);
		break; // Yellow 黄色
	case purper:
		RRGB_SET(1, 0, 1);
		break; // Purper 紫色
	case lake:
		RRGB_SET(0, 1, 1);
		break; // lake 青色
	case write:
		RRGB_SET(1, 1, 1);
		break; // Full open 全开
	default:
		RGB_OFF_R;
	}
}

// Set the RGB light color on the left 设置左边的RGB灯颜色
void Set_Color_L(RGB_Color_t color)
{
	switch (color)
	{
	case red:
		LRGB_SET(1, 0, 0);
		break; // RED 红色
	case green:
		LRGB_SET(0, 1, 0);
		break; // Green 绿色
	case blue:
		LRGB_SET(0, 0, 1);
		break; // Bule 蓝色
	case yellow:
		LRGB_SET(1, 1, 0);
		break; // Yellow 黄色
	case purper:
		LRGB_SET(1, 0, 1);
		break; // Purper 紫色
	case lake:
		LRGB_SET(0, 1, 1);
		break; // lake 青色
	case write:
		LRGB_SET(1, 1, 1);
		break; // Full open 全开
	default:
		RGB_OFF_L;
	}
}
