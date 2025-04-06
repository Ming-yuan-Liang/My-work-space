#include "app_k210.h"

float g_K210y_median;
float pid_output_k210y = 0;
PID_t pid_k210_y;

float g_K210x_median;
float pid_output_k210x = 0;
PID_t pid_k210_x;

//Incremental PID - X 增量PID--X
#define K210X_PID_KP       (16)
#define K210X_PID_KI       (0.001)//0.005
#define K210X_PID_KD       (5)//10.5

//Incremental PID - Y 增量PID--Y
#define K210Y_PID_KP       (3.0)//3
#define K210Y_PID_KI       (0.000001)//
#define K210Y_PID_KD       (1.2)//1.2

// Initialize K210X axis PID parameters 初始化K210X轴 PID参数
void APP_K210X_Y_Apriltag_Init(void)
{
	//X-direction x方向的
	pid_k210_x.target_val = 0.0;
	pid_k210_x.pwm_output = 0.0;
	pid_k210_x.err = 0.0;
	pid_k210_x.err_last = 0.0;
	pid_k210_x.err_next = 0.0;
	pid_k210_x.integral = 0.0;

	pid_k210_x.Kp = K210X_PID_KP;
	pid_k210_x.Ki = K210X_PID_KI;
	pid_k210_x.Kd = K210X_PID_KD;

	//Y-direction y方向的
	pid_k210_y.target_val = 0.0;
	pid_k210_y.pwm_output = 0.0;
	pid_k210_y.err = 0.0;
	pid_k210_y.err_last = 0.0;
	pid_k210_y.err_next = 0.0;
	pid_k210_y.integral = 0.0;

	pid_k210_y.Kp = K210Y_PID_KP;
	pid_k210_y.Ki = K210Y_PID_KI;
	pid_k210_y.Kd = K210Y_PID_KD;

	K210_data.k210_X = 80;
	K210_data.k210_Y = 60;
}



float APP_K210X_PID_Calc(float actual_value)
{
    return PID_Incre_Calc(&pid_k210_x, actual_value);
}


float APP_K210Y_PID_Calc(float actual_value)
{
    return PID_Incre_Calc(&pid_k210_y, actual_value);
}

//函数功能:小车结合k210数据做机器码跟随
//Function function: combine the car with K210 data to follow the machine code
void APP_K210X_Y_Line_PID(void)
{
	g_K210x_median = 80 - K210_data.k210_X ; //案例的x轴是160 所以中间值为80 The x-axis of the case is 160, so the median value is 80
	g_K210y_median = K210_data.k210_Y - 60 ; //案例的y轴是120 所以中间值为60 The x-axis of the case is 120, so the median value is 60



	if((my_abs(g_K210y_median )<= 23) && (my_abs(g_K210x_median )<= 25) )//A fixed area 一个不动区
	{
		Motion_Set_Speed(0,0,0,0);
		return;
	}

	pid_output_k210x = (int)(APP_K210X_PID_Calc(g_K210x_median));
	pid_output_k210y = (int)(APP_K210Y_PID_Calc(g_K210y_median));

	printf("%.2f\t , %.2f\r\n",pid_output_k210y, pid_output_k210x);

	Motion_Ctrl(pid_output_k210y, 0, pid_output_k210x);
}

float my_abs(float num)
{
	if(num < 0)
		num = -num;
	return num;
}


