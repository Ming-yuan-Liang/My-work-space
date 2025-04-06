#include "app_rgb.h"


//两个RGB灯同时切换7种颜色特效
void RGB_color_ALL(uint32_t times)
{
	for(RGB_Color i = red;i<Max_color;i++)
	{
		Set_RGB(RGB_Max,i);
		Delay_Ms(times);
	}

}

//RGB灯跟随效果
void RGB_color_follow(uint32_t times)
{
	for(RGB_Color i = red;i<=Max_color;i++)
	{
		Set_RGB(RGB_R,(RGB_Color)(i%Max_color));
		Set_RGB(RGB_L,(RGB_Color)((i+1)%Max_color));
		Delay_Ms(times);
	}

}

//RGB灯流水效果
//direction；方向 0从右到左 1从左到右
//times：时间
void RGB_color_water(uint8_t direction,uint32_t times)
{
	if(direction == 0)
	{
		for(RGB_Color i=red;i<Max_color;i++)
		{
			Set_RGB(RGB_L,(RGB_Color)(i%Max_color));
			Delay_Ms(times);
			Set_RGB(RGB_R,(RGB_Color)((i)%Max_color));
			Delay_Ms(times);
		}
	}
	else
	{
		for(RGB_Color i=red;i<Max_color;i++)
		{
			Set_RGB(RGB_R,(RGB_Color)(i%Max_color));
			Delay_Ms(times);
			Set_RGB(RGB_L,(RGB_Color)((i)%Max_color));
			Delay_Ms(times);
		}
	}

}
//单灯轮播效果
void RGB_one_light(uint8_t direction,uint32_t times)
{
	if(direction == 0)
	{
			for(RGB_Color i=red;i<Max_color;i++)
			{
				Set_RGB(RGB_L,(RGB_Color)(i%Max_color));
				RGB_OFF_R;
				Delay_Ms(times);

				RGB_OFF_L;
				Set_RGB(RGB_R,(RGB_Color)((i)%Max_color));
				Delay_Ms(times);
			}
	}
	else
	{
		for(RGB_Color i=red;i<Max_color;i++)
		{
			RGB_OFF_L;
			Set_RGB(RGB_R,(RGB_Color)((i)%Max_color));
			Delay_Ms(times);

			Set_RGB(RGB_L,(RGB_Color)(i%Max_color));
			RGB_OFF_R;
			Delay_Ms(times);
		}
	}

}

void user_control(Color_effect_t effect)
{
	switch((uint8_t)effect)
	{
		case CUT_RGB:			RGB_color_ALL(400); RGB_OFF_ALL;break;
		case FOLLOE_RGB:		RGB_color_follow(350);RGB_OFF_ALL;break;
		case A_WATER:			RGB_color_water(0,500);RGB_OFF_ALL;break;
		case B_WATER:			RGB_color_water(1,500);RGB_OFF_ALL;break;
		case A_ONE_LIHGRT:		RGB_one_light(0,400);RGB_OFF_ALL;break;
		case B_ONE_LIHGRT:		RGB_one_light(1,400);RGB_OFF_ALL;break;
	}
}
