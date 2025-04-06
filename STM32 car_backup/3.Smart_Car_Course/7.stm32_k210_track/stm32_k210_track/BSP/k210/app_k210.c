#include "app_k210.h"

float g_K210y_median;
float pid_output_k210y = 0;
PID_t pid_k210_y;

float g_K210x_median;
float pid_output_k210x = 0;
PID_t pid_k210_x;

//增量PID--X  //Incremental PID - X
#define K210X_PID_KP       (0.02)  //0.02
#define K210X_PID_KI       (0.002) //0.002
#define K210X_PID_KD       (0.005)//0.005

//增量PID--Y  //Incremental PID - Y
#define K210Y_PID_KP       (0.03)
#define K210Y_PID_KI       (0.003)
#define K210Y_PID_KD       (0.006)

// 初始化K210X\y轴 PID参数
//Initialize K210X  y-axis PID parameters
void APP_K210X_Y_Init(void)
{
	//x方向的
	//X-direction
	pid_k210_x.target_val = 0.0;
	pid_k210_x.pwm_output = 0.0;
	pid_k210_x.err = 0.0;
	pid_k210_x.err_last = 0.0;
	pid_k210_x.err_next = 0.0;
	pid_k210_x.integral = 0.0;

	pid_k210_x.Kp = K210X_PID_KP;
	pid_k210_x.Ki = K210X_PID_KI;
	pid_k210_x.Kd = K210X_PID_KD;

	//y方向的
	//y-direction
	pid_k210_y.target_val = 0.0;
	pid_k210_y.pwm_output = 0.0;
	pid_k210_y.err = 0.0;
	pid_k210_y.err_last = 0.0;
	pid_k210_y.err_next = 0.0;
	pid_k210_y.integral = 0.0;

	pid_k210_y.Kp = K210Y_PID_KP;
	pid_k210_y.Ki = K210Y_PID_KI;
	pid_k210_y.Kd = K210Y_PID_KD;

	//initialization 初始化
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


void APP_K210X_Y_Line_PID(void)
{
	g_K210x_median = K210_data.k210_X - 160; //k210屏幕的x轴是320 所以中间值为160 The x-axis of the K210 screen is 320, so the median value is 160
	g_K210y_median = 120 - K210_data.k210_Y ; //k210屏幕的y轴是240 所以中间值为120 The y-axis of the K210 screen is 240, so the middle value is 120

//	printf("%f\t  %f\r\n",g_K210x_median,g_K210y_median);

	if((my_abs(g_K210y_median )<= 30) && (my_abs(g_K210x_median )<= 40) )//不进行pid运算区域 Area without pid operation
	{
		return;
	}

	pid_output_k210x = (int)(APP_K210X_PID_Calc(g_K210x_median));
	pid_output_k210y = (int)(APP_K210Y_PID_Calc(g_K210y_median));


	printf("%f\t  %f\r\n",pid_output_k210x,pid_output_k210y);

	//控制左右(X轴方向)舵机---S1舵机
	//Control the left and right (X-axis direction) steering gear - S1 steering gear
	PwmServo_Set_Angle(0,90+pid_output_k210x);

	//控制上下(Y轴方向)舵机---S2舵机
	//Control the up and down (Y-axis direction) steering gear - S2 steering gear
	PwmServo_Set_Angle(1,90+pid_output_k210y);

}

float my_abs(float num)
{
	if(num < 0)
		num = -num;
	return num;
}


