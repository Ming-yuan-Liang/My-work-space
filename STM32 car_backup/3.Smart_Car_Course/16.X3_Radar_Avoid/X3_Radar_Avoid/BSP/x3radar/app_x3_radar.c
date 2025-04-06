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

	return min;
}


/*************结合小车做动作*****************/


//函数功能:小车结合雷达避障
//Function function: Car combined with radar obstacle avoidance
void Car_Avoid(void)
{
	float get_data_mid = App_Data_Avg(170,190);

	float get_data_LL = App_Data_Avg(140,170);
	float get_data_RR = App_Data_Avg(190,210);

	float get_data_Lmid=0, get_data_Rmid=0;

	printf("data = %.2f\t %.2f\t %.2f\r\n",get_data_mid,get_data_LL,get_data_RR);

		if(get_data_mid <250 || get_data_LL <250 || get_data_RR <250)//避障 Avoiding obstacles
		{
			//小车停止 Car stop
			wheel_State(MOTION_STOP,0);
			HAL_Delay(300);


			//小车后退 Trolley backward
			wheel_State(MOTION_BACK,250);
			HAL_Delay(1000);

			//获取左右的数据 Get data on both sides
			get_data_Lmid = App_Data_Avg(70,110);//Left 左边
			get_data_Rmid = App_Data_Avg(250,290);//Right 右边
			printf("data_L = %.2f\r\n",get_data_Lmid);
			printf("data_R = %.2f\r\n",get_data_Rmid);


			//小车判断左右两边障碍做运动 The car detects obstacles on both sides and moves
			if(get_data_Lmid >= get_data_Rmid )
			{
				wheel_State(MOTION_SPIN_LEFT,550);//左边 left
				HAL_Delay(1000);
			}
			else
			{
				wheel_State(MOTION_SPIN_RIGHT,550);//右边 right
				HAL_Delay(1000);
			}

		}


		//小车前进 The car moves forward
		wheel_State(MOTION_RUN,250);



}







