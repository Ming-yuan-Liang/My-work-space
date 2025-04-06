#include "bsp_PID_servo.h"

// Set PID parameters 设置PID参数
void PID_Set_Parm(PID_t *pid, float p, float i, float d)
{
    pid->Kp = p; // Set Scale Factor 设置比例系数 P
    pid->Ki = i; // Set integration coefficient 设置积分系数 I
    pid->Kd = d; // Set differential coefficient 设置微分系数 D
}

// Set the target value of PID 设置PID的目标值
void PID_Set_Target(PID_t *pid, float temp_val)
{
    pid->target_val = temp_val; // Set the current target value 设置当前的目标值
}

// Obtain PID target value 获取PID目标值
float PID_Get_Target(PID_t *pid)
{
    return pid->target_val; // Set the current target value 设置当前的目标值
}

// Incremental PID calculation formula 增量式PID计算公式
float PID_Incre_Calc(PID_t *pid, float actual_val)
{
    /*计算目标值与实际值的误差*/
	//Calculate the error between the target value and the actual value
    pid->err = pid->target_val - actual_val;
    /*PID算法实现*/
    //PID algorithm implementation
    pid->pwm_output += pid->Kp * (pid->err - pid->err_next) + pid->Ki * pid->err + pid->Kd * (pid->err - 2 * pid->err_next + pid->err_last);
    /*传递误差*/
    //transmission error
    pid->err_last = pid->err_next;
    pid->err_next = pid->err;

    //角度只有-90~0~90
    if(pid->pwm_output <= -90)
    	pid->pwm_output = -90;
    if(pid->pwm_output >= 90)
    	pid->pwm_output = 90;

    return pid->pwm_output;
}

// 位置式PID计算方式
//Position PID calculation method
float PID_Location_Calc(PID_t *pid, float actual_val)
{
    /*计算目标值与实际值的误差*/
	/*Calculate the error between the target value and the actual value*/
    pid->err = pid->target_val - actual_val;

    /* 限定闭环死区 */
    /*Limited closed-loop dead zone*/
    if ((pid->err >= -40) && (pid->err <= 40))
    {
        pid->err = 0;
        pid->integral = 0;
    }

    /* 积分分离，偏差较大时去掉积分作用 */
    /*Integral separation, removing the integral effect when the deviation is large*/
    if (pid->err > -1500 && pid->err < 1500)
    {
        pid->integral += pid->err; // error accumulation 误差累积

        /* Limit the integration range to prevent integration saturation 限定积分范围，防止积分饱和 */
        if (pid->integral > 4000)
            pid->integral = 4000;
        else if (pid->integral < -4000)
            pid->integral = -4000;
    }

    /*PID算法实现*/ /*PID algorithm implementation*/
    pid->output_val = pid->Kp * pid->err +
                      pid->Ki * pid->integral +
                      pid->Kd * (pid->err - pid->err_last);

    /*误差传递*/ /*Error transmission*/
    pid->err_last = pid->err;

    /*返回当前实际值*/ /*Returns the current actual value*/
    return pid->output_val;
}
