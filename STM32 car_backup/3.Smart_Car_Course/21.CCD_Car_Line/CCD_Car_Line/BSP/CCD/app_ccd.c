#include "app_ccd.h"

extern uint8_t CCD_median;//引入CCD的变量
float g_ccd_median;
float pid_output_ccd = 0;
PID_t pid_ccd;

//Incremental PID
#define CCD_PID_KP       (85) //85
#define CCD_PID_KI       (5)  //5
#define CCD_PID_KD       (8)  //8

#define CAR_SPEED  375 //巡线的速度

// Initialize K210X axis PID parameters 初始化K210X轴 PID参数
void APP_CCD_Init(void)
{
	pid_ccd.target_val = 0.0;
	pid_ccd.pwm_output = 0.0;
	pid_ccd.err = 0.0;
	pid_ccd.err_last = 0.0;
	pid_ccd.err_next = 0.0;
	pid_ccd.integral = 0.0;

	pid_ccd.Kp = CCD_PID_KP;
	pid_ccd.Ki = CCD_PID_KI;
	pid_ccd.Kd = CCD_PID_KD;
}



float APP_CCD_PID_Calc(float actual_value)
{
    return PID_Incre_Calc(&pid_ccd, actual_value);
}


void APP_CCD_Line_PID(void)
{
	g_ccd_median = 64 - CCD_median; //CCD的中间值是64

	pid_output_ccd = (int)(APP_CCD_PID_Calc(g_ccd_median));

	Motion_Ctrl(CAR_SPEED, 0, pid_output_ccd);
}


float my_abs(float num)
{
	if(num < 0)
		num = -num;
	return num;
}
