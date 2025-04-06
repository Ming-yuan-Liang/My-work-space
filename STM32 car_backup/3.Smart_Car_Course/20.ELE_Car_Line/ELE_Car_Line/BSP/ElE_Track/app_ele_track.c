#include "app_ele_track.h"

extern int ele_seat;
float g_ele_median;
float pid_output_ele = 0;
PID_t pid_ele;

// Incremental PID
#define ELE_PID_KP (25)
#define ELE_PID_KI (0)
#define ELE_PID_KD (20)

#define CAR_SPEED 250 // 巡线的速度

// Initialize K210X axis PID parameters 初始化K210X轴 PID参数
void APP_ELE_Init(void)
{
	pid_ele.target_val = 0.0;
	pid_ele.pwm_output = 0.0;
	pid_ele.err = 0.0;
	pid_ele.err_last = 0.0;
	pid_ele.err_next = 0.0;
	pid_ele.integral = 0.0;

	pid_ele.Kp = ELE_PID_KP;
	pid_ele.Ki = ELE_PID_KI;
	pid_ele.Kd = ELE_PID_KD;
}

// 调用增量式pid计算,返回计算的结果 Call incremental pid calculation and return the result of calculation.
// float actual_value: 当前的误差 Current error
float APP_ELE_PID_Calc(float actual_value)
{
	return PID_Incre_Calc(&pid_ele, actual_value);
}

// 根据传感器的值反馈，使用pid控制小车电机做巡线运动
//  According to the feedback of the sensor, pid is used to control the car motor to patrol the line.
void APP_ELE_Line_PID(void)
{
	g_ele_median = 110 - ele_seat; // ELE的中间值是110 请把每个电磁的值调到相同 The median value of ELE is 110. please set each electromagnetic value to the same.

	pid_output_ele = (int)(APP_ELE_PID_Calc(g_ele_median));

	Motion_Ctrl(CAR_SPEED, 0, pid_output_ele);
}
