#include "app_k210.h"

float g_K210x_median;
float pid_output_k210x = 0;
PID_t pid_k210_x;

//增量PID Incremental PID
#define K210X_PID_KP       (5)
#define K210X_PID_KI       (100)
#define K210X_PID_KD       (5)

#define K210X_SPEED 		200

// 初始化K210X轴 PID参数 Initialize the K210X axis PID parameter
void APP_K210X_Init(void)
{
	pid_k210_x.target_val = 0.0;
	pid_k210_x.pwm_output = 0.0;
	pid_k210_x.err = 0.0;
	pid_k210_x.err_last = 0.0;
	pid_k210_x.err_next = 0.0;
	pid_k210_x.integral = 0.0;

	pid_k210_x.Kp = K210X_PID_KP;
	pid_k210_x.Ki = K210X_PID_KI;
	pid_k210_x.Kd = K210X_PID_KD;

	//初始化 Initialization
	K210_data.k210_X = 160;
	K210_data.k210_Y = 120;
}

// 调用增量式pid计算,返回计算的结果 Call incremental pid calculation and return the result of calculation.
// float actual_value: 当前的误差 Current error
float APP_K210X_PID_Calc(float actual_value)
{
    return PID_Incre_Calc(&pid_k210_x, actual_value);
}

// 根据传感器的值反馈，使用pid控制小车电机做巡线运动
//  According to the feedback of the sensor, pid is used to control the car motor to patrol the line.
void APP_K210X_Line_PID(void)
{

	g_K210x_median=160-K210_data.k210_X; //k210屏幕的x轴是320 所以中间值为160 The x-axis of the k210 screen is 320, so the median value is 160.

	pid_output_k210x = (int)(APP_K210X_PID_Calc(g_K210x_median));

	printf("%.4f\r\n",pid_output_k210x);
	Motion_Ctrl(K210X_SPEED, 0, pid_output_k210x);

}
