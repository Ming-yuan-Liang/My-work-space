#include "app_x3_radar.h"


char car_buff[20] = {'\0'};

//函数功能:串打印雷达每个点的数
//传入参数:无
//Function function: Print the number of radar points in series
//Incoming parameter: None
void App_Print_Data(void)
{
	for(uint16_t i=0;i<360;i++)
	{
		if(X3dis[i]!=0)
		printf("%d\t%d\r\n",i,X3dis[i]);
	}
	printf("######################\r\n");
}


//根据雷达的一定的区域,取平均值
//传入参数：start：起始的角度  end:结束的角度
//Take the average value based on a certain area of the radar
//Incoming parameter: start: starting angle end: ending angle
float App_Data_Avg(uint16_t start,uint16_t end)
{
	uint16_t sum = 0;
	uint16_t new_sum = 0;
	float average = 0;
	if(start > 360 || end > 360)//角度不合法 Illegal angle
	{
		return -1;
	}

	if(start-end > 0)
	{
		sum = 360 - start + end;
	}
	else
	{
		sum = end - start;
	}

	new_sum = sum;

	for(uint16_t i=0;i<sum;i++)
	{
		if(X3dis[(start+i)%360]==0)
		{
			new_sum -- ;
		}
		else
		{
			average +=X3dis[(start+i)%360]; //刚好满足数组的下标0-359 Exactly satisfies the index 0-359 of the array
		}

	}

	if(new_sum == 0)
	{
		return -1;//没接收到对应范围内角度的距离 Not receiving the distance of the corresponding angle within the range
	}

	return average/sum;
}


//根据雷达的一定的区域,取最小值
//传入参数：start：起始的角度  end:结束的角度
//Take the minimum value based on a certain area of the radar
//Incoming parameter: start: starting angle end: ending angle
float App_Data_Min(uint16_t start,uint16_t end)
{
	uint16_t sum = 0;
	int min = 20000;//该值大于雷达协议检测的最大值 This value is greater than the maximum value detected by the radar protocol
	if(start >360 || end > 360)//角度不合法 Illegal angle
	{
		return -1;
	}

	if(start-end > 0)
	{
		sum = 360 - start + end;
	}
	else
	{
		sum = end - start;
	}

	for(uint16_t i=0;i<sum;i++)
	{
		if(X3dis[(start+i)%360]!=0)//抛弃为0的数 Discard numbers with 0
		{
			if(min > X3dis[(start+i)%360])
			{
				min = X3dis[(start+i)%360];
			}
		}
	}

	return min;
}

float my_abs(float x)
{
	if(x<0)
		x = -x;
	return x;
}



uint16_t g_car_time = Car_Go_Time;//小车走直线的时间 Time for the car to travel in a straight line
uint16_t g_car_state = 1;//小车走直线标志 0:不走直线 1:开始走直线 2:碰到障碍物 Car walking in a straight line sign 0: Not walking in a straight line 1: Starting to walk in a straight line 2: Encountering obstacles
uint8_t  g_car_stop_flag = 2;//0:转弯是被障碍物中断 1:直线时被障碍物中断 Turning interrupted by an obstacle 1: Straight line interrupted by an obstacle
//重置 resetting
void APP_Reset(void)
{
	g_car_time = Car_Go_Time;//小车走直线的时间 Time for the car to travel in a straight line
	g_car_state = 1;//小车走直线标志 0:不走直线 1:开始走直线

	YAW_car = YAW_yaw_e;//直线运动的角度 Angle of linear motion
	Yaw_old_buckup = YAW_car;

}

void APP_X3_MPU_Patrol(void)
{
	if(g_car_time == 0 && g_car_state == 1) //直线运动结束 End of linear motion
	{
		if(my_abs(YAW_car - YAW_yaw_e) > 3)
		{
			return;
		}
		wheel_State_YAW(MOTION_STOP,0,0);//停车 stop

		g_car_state = 0;
		g_car_time = Car_Go_Time;

		YAW_car = Convert_to_360(YAW_yaw_e + Turn_Angle); //设置目标角度 转弯角度 Set target angle turning angle
		Yaw_old_buckup = YAW_car;

		wheel_State_YAW(MOTION_RUN,200,1); //用这速度转弯 ,只运行1次 Turn at this speed and only run once

	}


	if(g_car_state == 2 && g_car_stop_flag == 0)//停止后,恢复转弯运动 After stopping, resume turning motion
	{
		g_car_state = 0;
		YAW_car = Yaw_old_buckup;
		wheel_State_YAW(MOTION_RUN,200,1); //用这速度转弯 ,只运行1次
	}
	else if(g_car_state == 2 && g_car_stop_flag == 1)//恢复直线运动 Restore linear motion
	{
		g_car_state = 1;
		YAW_car = Yaw_old_buckup;
		wheel_State_YAW(MOTION_RUN,200,1);//用这速度走直线 ,只执行1次即可
	}


	if(g_car_state == 0)//转弯
	{
		Car_Turn();
	}

}


//函数功能:运动的判断
//Function function: judgment of motion
void Car_Turn(void)
{
	if(my_abs(YAW_car - YAW_yaw_e) <= 4)//误差
	{
		wheel_State_YAW(MOTION_STOP,0,0);//小车停止,并关闭偏航角调整

		YAW_car = Yaw_old_buckup;
		wheel_State_YAW(MOTION_RUN,200,1);//用这速度走直线 ,只执行1次即可
		g_car_state = 1; //恢复直走

		run_num ++;
		if(run_num >= (360/Turn_Angle)*Patrol_Count) //只巡逻2次  8
		{
			key1_flag = 0;
			wheel_State_YAW(MOTION_STOP,0,0);//停车
			run_num = 0;
		}
	}

}

//函数功能:直线运动
//Function function: linear motion
void Car_straight(void)
{
	wheel_State_YAW(MOTION_RUN,200,1);
}



//函数功能:x3雷达前面检测到障碍物 如何运动函数
//Function function: How does the x3 radar detect obstacles in front of it? Function
void X3_Motion_Car(void)
{
	if(get_data_mid < DIS_FOOD)
	{
		BEEP_ON;
		//小车停止 Car stop
		wheel_State_YAW(MOTION_STOP,0,0);

		if(g_car_state == 0)//小车转弯运动
		{
			g_car_stop_flag = 0;
		}
		else if(g_car_state == 1) //小车直线运动
		{
			g_car_stop_flag = 1;
		}

		g_car_state = 2;//表示出现障碍物 Indicates the presence of obstacles
		return ;
	}
	BEEP_OFF;

	APP_X3_MPU_Patrol(); //没障碍物开始巡逻 No obstacles, start patrolling

}

