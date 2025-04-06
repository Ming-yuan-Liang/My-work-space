#include "bsp.h"

//Hardware Initialization
//Parameter:None

void BSP_Init(void)
{
	Bsp_Tim_Init();
	PID_Param_Init();//电机PID初始化 Motor PID initialization
	UART4_Init();
}

uint16_t state=100;
uint16_t voice_car_speed = 250;

//Hardware Initialization
//Parameter:None

void BSP_Loop(void)
{
    if(state!=Get_Massage())//判断是否更新了语音指令 Determine whether the voice command has been updated
    {
	Change_RGB((Control_RGB_t)Get_Massage());
	Control_Car((Control_MOTOR_t)Get_Massage());
	Control_speed((Control_Speed_t)Get_Massage());
	state=Get_Massage();
    }
}

/*
 * 语音控制RGB灯
 * Control_RGB_t rgb_flag ：对应语音模块发送给主机后两位id
 *
 * Voice control RGB light
 * Control_RGB_t rgb_flag: The last two digits of the id sent by the corresponding voice module to the host
 * */

void Change_RGB(Control_RGB_t rgb_flag)
{
	switch (rgb_flag)
	{
	case close_light:
		RGB_OFF_ALL;
		break;
	case red_light:
		Set_color_R(red);
		Set_color_L(red);
		break;
	case green_light:
		Set_color_R(green);
		Set_color_L(green);
		break;
	case blue_light:
		Set_color_R(blue);
		Set_color_L(blue);
		break;
	case yellow_light:
		Set_color_R(yellow);
		Set_color_L(yellow);
		break;
	}

	Send_Massage((uint16_t)rgb_flag);

}

/*
 * 语音控制小车行动
 * Control_MOTOR_t car_state：对应语音模块发送给主机后两位id
 *
 * Voice control car action
 * Control_RGB_t rgb_flag: The last two digits of the id sent by the corresponding voice module to the host
 * */

void Control_Car(Control_MOTOR_t car_state )
{
	switch(car_state)
	{
	case car_stop:
		wheel_State(MOTION_STOP,0);
		break;
	case stop:
		wheel_State(MOTION_STOP, 0);
	    HAL_Delay(500);
	    Motion_Set_Speed(-400, -400, -100, -100);
	    HAL_Delay(2300);
	    wheel_State(MOTION_BACK, 200);
	    HAL_Delay(3000);
		wheel_State(MOTION_STOP, 0);
		HAL_Delay(10000);
		Motion_Set_Speed(-100, -100, 500, 500);
		HAL_Delay(1100);
		wheel_State(MOTION_RUN, 200);
		HAL_Delay(3000);
		wheel_State(MOTION_STOP, 0);
		HAL_Delay(3000);
		wheel_State(MOTION_BACK, 200);
		HAL_Delay(3000);

		Motion_Set_Speed(-100, -100, -500, -500);
		HAL_Delay(1600);
		wheel_State(MOTION_BACK, 200);
		HAL_Delay(3000);
		wheel_State(MOTION_RUN, 200);
		HAL_Delay(3000);
		Motion_Set_Speed(500, 500, -100, -100);
		HAL_Delay(1000);
		wheel_State(MOTION_RUN, 200);
		HAL_Delay(5000);

		wheel_State(MOTION_STOP, 0);
	    HAL_Delay(30000);
		break;

	case sleep:
		break;
	case car_forward:
		wheel_State(MOTION_RUN,voice_car_speed);
		break;
	case car_back:
		wheel_State(MOTION_BACK,voice_car_speed);
		break;
	case car_left:
		Motion_Set_Speed(-voice_car_speed/4,-voice_car_speed/4,voice_car_speed,voice_car_speed);
		break;
	case car_right:
		Motion_Set_Speed(voice_car_speed,voice_car_speed,-voice_car_speed/4,-voice_car_speed/4);
		break;
	case left_spin:
		wheel_State(MOTION_SPIN_LEFT,voice_car_speed);
		break;
	case right_spipn:
		wheel_State(MOTION_SPIN_RIGHT,voice_car_speed);
		break;
	case parking1:
		wheel_State(MOTION_STOP, 0);
	    HAL_Delay(500);
	    Motion_Set_Speed(-400, -400, -100, -100);
	    HAL_Delay(2300);
	    wheel_State(MOTION_BACK, 200);
	    HAL_Delay(3000);
		wheel_State(MOTION_STOP, 0);
		HAL_Delay(10000);
		Motion_Set_Speed(-100, -100, 500, 500);
		HAL_Delay(1100);
		wheel_State(MOTION_RUN, 200);
		HAL_Delay(3000);
		wheel_State(MOTION_STOP, 0);
		HAL_Delay(3000);
		wheel_State(MOTION_BACK, 200);
		HAL_Delay(3000);

		Motion_Set_Speed(-100, -100, -500, -500);
		HAL_Delay(1600);
		wheel_State(MOTION_BACK, 200);
		HAL_Delay(3000);
		wheel_State(MOTION_RUN, 200);
		HAL_Delay(3000);
		Motion_Set_Speed(500, 500, -100, -100);
		HAL_Delay(1000);
		wheel_State(MOTION_RUN, 200);
		HAL_Delay(5000);

		wheel_State(MOTION_STOP, 0);
	    HAL_Delay(30000);
		break;
	case parking2:

		break;

	}
	Send_Massage((uint16_t)car_state);

}

/*
 * 语音控制加、减速
 * Control_Speed_t ctrl_speed：对应语音模块的语音模块发送给主机后两位id
 *
 * Voice control acceleration and deceleration
 * Control_RGB_t rgb_flag: The last two digits of the id sent by the corresponding voice module to the host
 * */

void Control_speed( Control_Speed_t ctrl_speed)
{
	if(ctrl_speed== up )
	{
		voice_car_speed=voice_car_speed+100;
		if(voice_car_speed>1000)
		{
			voice_car_speed=1000;
		}

	}
	if(ctrl_speed== down )
	{
		voice_car_speed=voice_car_speed-100;
		if(voice_car_speed<100)
		{
			voice_car_speed=100;
		}
	}
	Send_Massage(ctrl_speed);
}
