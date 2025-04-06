#include "app_x3_radar.h"


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

	return my_min(min);
}

float my_min(float x)
{
	if(x>=20000)
		x =120; //这款雷达的最小测距距离 The minimum ranging distance of this radar
	return x;

}


/*************结合小车做动作 Combined with the small car for action*****************/


//函数功能:小车结合雷达跟随
//Function function: Car combined with radar following
void Car_Follow(void)
{
	float get_data_mid = my_min(App_Data_Min(170,190));

	float get_data_LL = my_min(App_Data_Min(70, 150));

	float get_data_RR = my_min(App_Data_Min(210, 290));

	float get_data_LL2 = my_min(App_Data_Min(140, 160));

	float get_data_RR2 = my_min(App_Data_Min(200, 220));

	printf("data = %.2f\t %.2f\t %.2f\t %.2f\t %.2f\r\n",get_data_mid,get_data_LL,get_data_LL2,get_data_RR,get_data_RR2);

	// positive direction 正方向
	if(get_data_mid < 200)
	{
		wheel_State(MOTION_BACK,250);
	}
	else if (get_data_mid > 300 && get_data_mid < 500)
	{
		//小车前进 The car moves forward
		wheel_State(MOTION_RUN,250);
	}


	// Left direction 左方向
	else if (get_data_LL < 350 )//|| get_data_LL2 < 320
	{
		// Left rotation of the car 小车左旋
		wheel_State(MOTION_SPIN_LEFT,450);

	}


	// Right direction 右方向
	else if (get_data_RR < 350 )//|| get_data_RR2 < 320
	{
		//小车右旋
		wheel_State(MOTION_SPIN_RIGHT,450);
	}

	else//Not following 不跟随
	{
		wheel_State(MOTION_STOP,0);
	}

}



