#include "bsp.h"

//Hardware Initialization
//Parameter:None

void BSP_Init(void)
{
	Bsp_Tim_Init();
	PID_Param_Init();//电机PID初始化 Motor PID initialization
	Delay_Init();
	Set_Buzzer(0);
	RGB_OFF_ALL;
}

//Loop Run Function
//Parameter:None

void BSP_Loop(void)
{
	Ultrasonic_avoidance(20);//设置超声波避障距离为20cm Set the ultrasonic obstacle avoidance distance to 20cm
	// Ultrasonic_follow(30);
}

void BSP_Loop2(void)
{
	Set_Buzzer(1);	// 开启蜂鸣器 turn on the buzzer
	HAL_Delay(200); // 延时200ms
	Set_Buzzer(0);	// 关闭蜂鸣器 turn off the buzzer
	HAL_Delay(200);
}

void BSP_Loop3(void)
{

	Set_RGB(RGB_R, red);   // 开启右边红色RGB探照灯 Turn on the right red RGB searchlight
	HAL_Delay(200);		   // 延时200ms
	RGB_OFF_ALL;		   // 关闭左右两边的所有RGB灯 Turn off all RGB lights on the left and right sides
	HAL_Delay(200);		   // 延时200ms
	Set_RGB(RGB_L, green); // 开启左边绿色RGB探照灯 Turn on the green RGB searchlight on the left
	HAL_Delay(200);
	RGB_OFF_ALL;
	HAL_Delay(200);
	Set_RGB(RGB_Max, purple); // 开启左右两边紫色RGB探照灯 Turn on the purple RGB searchlights on the left and right sides
	HAL_Delay(200);
	RGB_OFF_ALL;
	HAL_Delay(200);
}
