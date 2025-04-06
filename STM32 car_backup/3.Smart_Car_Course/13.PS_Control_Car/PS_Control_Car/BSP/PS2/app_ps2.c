#include "app_ps2.h"

int PS2_LX, PS2_LY, PS2_RX, PS2_RY, PS2_KEY;
int16_t g_car_speed = 200;

RGB_Color g_color = red;		   // 设置大灯RGB的颜色 Set the RGB color of the headlights
Color_effect_t g_Se_eff = CUT_RGB; // 特效的切换 Switching of special effects

char buff[20] = {'\0'};

// 函数功能：ps2控制小车
// Function function: PS2 control car
void User_PS2_Control(void)
{
	// 如果不接手柄，即4个255 If the handle is not connected, i.e. 4 255
	PS2_LX = PS2_AnologData(PSS_LX);
	PS2_LY = PS2_AnologData(PSS_LY);
	PS2_RX = PS2_AnologData(PSS_RX);
	PS2_RY = PS2_AnologData(PSS_RY);
	PS2_KEY = PS2_DataKey(); // 出现192

	sprintf(buff, "speed = %d   ", g_car_speed);
	OLED_Draw_Line(buff, 2, false, true);

	// 手柄没通信上 The handle is not communicating
	if ((PS2_LX == 255) && (PS2_LY == 255) && (PS2_RX == 255) && (PS2_RY == 255))
	{
		return;
	}
	else if ((PS2_LX == 0) && (PS2_LY == 0) && (PS2_RX == 0) && (PS2_RY == 0))
	{
		return;
	}
	else if ((PS2_LX == 192) || (PS2_LY == 192) || (PS2_RX == 192) || (PS2_RY == 192)) // 这是误判的值,到时可自己调整 This is a misjudgment value, you can adjust it yourself then
	{
		return;
	}

	// 左边控制前后，右边控制左右 Left controls front and rear, right controls left and right
	if (PS2_LY < 125 && (PS2_RX > 125 && PS2_RX < 150)) // 控制前 Before control
	{
		wheel_State(MOTION_RUN, g_car_speed);
	}
	else if (PS2_LY > 150 && (PS2_RX > 125 && PS2_RX < 150)) // 控制后 After control
	{
		wheel_State(MOTION_BACK, g_car_speed);
	}
	else if (PS2_RX < 125 && (PS2_LY > 125 && PS2_LY < 150)) // 控制左 Control Left
	{
		wheel_State(MOTION_LEFT, g_car_speed);
	}
	else if (PS2_RX > 150 && (PS2_LY > 125 && PS2_LY < 150)) // 控制右 Control Right
	{
		wheel_State(MOTION_RIGHT, g_car_speed);
	}
	else if ((PS2_LY < 125 && PS2_RX < 125) || (PS2_LY > 150 && PS2_RX < 125)) // 左旋 counter-clockwise
	{
		wheel_State(MOTION_SPIN_LEFT, g_car_speed);
	}
	else if ((PS2_LY < 125 && PS2_RX > 150) || (PS2_LY > 150 && PS2_RX > 150)) // 右旋 dextrorotation
	{
		wheel_State(MOTION_SPIN_RIGHT, g_car_speed);
	}

	else
	{
		if (PS2_KEY == 0) // 没按键按下 No buttons pressed
			wheel_State(MOTION_STOP, 0);
	}

	switch (PS2_KEY)
	{
	case PSB_L1:
		g_car_speed += 100;
		if (g_car_speed > 1000)
			g_car_speed = 1000;
		break; // 小加速 Minor acceleration
	case PSB_L2:
		g_car_speed += 250;
		if (g_car_speed > 1000)
			g_car_speed = 1000;
		break; // 大加速  负数的时候，摇杆方向可变反 When the acceleration is negative, the direction of the joystick can be reversed

	case PSB_R1:
		g_car_speed -= 100;
		if (g_car_speed < 100)
			g_car_speed = 100;
		break; // 小减速 Small deceleration
	case PSB_R2:
		g_car_speed -= 250;
		if (g_car_speed < -1000)
			g_car_speed = -1000;
		break; // 大减速 负数的时候，摇杆方向可变反 When the deceleration is negative, the direction of the joystick can be reversed

	case PSB_PAD_UP:
		wheel_State(MOTION_RUN, g_car_speed);
		break;
	case PSB_PAD_RIGHT:
		wheel_State(MOTION_RIGHT, g_car_speed);
		break;
	case PSB_PAD_DOWN:
		wheel_State(MOTION_BACK, g_car_speed);
		break;
	case PSB_PAD_LEFT:
		wheel_State(MOTION_LEFT, g_car_speed);
		break;

	case PSB_GREEN:
		Set_RGB(RGB_Max, (RGB_Color)(g_color % Max_color));
		g_color++;
		if (g_color == Max_color)
			g_color = red;
		break;
	case PSB_BLUE:
		RGB_OFF_ALL;
		if (g_color != red)
			g_color--;
		break; // 关闭所有大灯 Turn off all headlights
	case PSB_PINK:
		g_Se_eff++; // 切换特效 Switch special effects
		if (g_Se_eff >= RGB_EFFCT_MAX)
		{
			g_Se_eff = CUT_RGB;
		}
		wheel_State(MOTION_STOP, 0); // 把车停了，再展示特效 Park the car and display the special effects again
		user_control(g_Se_eff);
		break;
	case PSB_RED:
		g_Se_eff--; // 切换特效 Switch special effects
		if (g_Se_eff < CUT_RGB)
		{
			g_Se_eff = (Color_effect_t)(RGB_EFFCT_MAX - 1);
		}
		wheel_State(MOTION_STOP, 0); // 把车停了，再展示特效 Park the car and display the special effects again
		user_control(g_Se_eff);
		break;

	default:
		break;
		wheel_State(MOTION_STOP, 0);
	}

	HAL_Delay(20); // 保持连接 Stay connected
}
