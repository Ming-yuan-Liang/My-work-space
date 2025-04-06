#include "app_k210.h"

float g_K210y_median;
float pid_output_k210y = 0;
PID_t pid_k210_y;

float g_K210x_median;
float pid_output_k210x = 0;
PID_t pid_k210_x;

//Incremental PID - X 增量PID--X
#define K210X_PID_KP       (17)//15
#define K210X_PID_KI       (0.0001)
#define K210X_PID_KD       (5)

//Incremental PID - Y 增量PID--Y
#define K210Y_PID_KP       (3.5)
#define K210Y_PID_KI       (0)
#define K210Y_PID_KD       (0.5)

// Initialize K210X axis PID parameters 初始化K210X轴 PID参数
void APP_K210X_Y_Init(void)
{
	//x方向的 X-direction
	pid_k210_x.target_val = 0.0;
	pid_k210_x.pwm_output = 0.0;
	pid_k210_x.err = 0.0;
	pid_k210_x.err_last = 0.0;
	pid_k210_x.err_next = 0.0;
	pid_k210_x.integral = 0.0;

	pid_k210_x.Kp = K210X_PID_KP;
	pid_k210_x.Ki = K210X_PID_KI;
	pid_k210_x.Kd = K210X_PID_KD;

	//y方向的 Y-direction
	pid_k210_y.target_val = 0.0;
	pid_k210_y.pwm_output = 0.0;
	pid_k210_y.err = 0.0;
	pid_k210_y.err_last = 0.0;
	pid_k210_y.err_next = 0.0;
	pid_k210_y.integral = 0.0;

	pid_k210_y.Kp = K210Y_PID_KP;
	pid_k210_y.Ki = K210Y_PID_KI;
	pid_k210_y.Kd = K210Y_PID_KD;

	K210_data.k210_X = 160;
	K210_data.k210_Y = 120;
}



float APP_K210X_PID_Calc(float actual_value)
{
    return PID_Incre_Calc(&pid_k210_x, actual_value);
}


float APP_K210Y_PID_Calc(float actual_value)
{
    return PID_Incre_Calc(&pid_k210_y, actual_value);
}


//函数功能:结合k210做颜色跟随
//Function function: Combining with K210 for color following
void APP_K210X_Y_Line_PID(void)
{
	g_K210x_median = 160 - K210_data.k210_X ; //k210屏幕的x轴是320 所以中间值为160 The x-axis of the K210 screen is 320, so the median value is 160
	g_K210y_median = K210_data.k210_Y - 120; //k210屏幕的y轴是240 所以中间值为120 The x-axis of the K210 screen is 240, so the median value is 120



	if((my_abs(g_K210y_median )<= 30) && (my_abs(g_K210x_median )<= 30) )//后面改成一个不动区
	{
		Motion_Set_Speed(0,0,0,0);
		return;
	}

	pid_output_k210x = (int)(APP_K210X_PID_Calc(g_K210x_median));
	pid_output_k210y = (int)(APP_K210Y_PID_Calc(g_K210y_median));


	Motion_Ctrl(pid_output_k210y, 0, pid_output_k210x);
}

float my_abs(float num)
{
	if(num < 0)
		num = -num;
	return num;
}


