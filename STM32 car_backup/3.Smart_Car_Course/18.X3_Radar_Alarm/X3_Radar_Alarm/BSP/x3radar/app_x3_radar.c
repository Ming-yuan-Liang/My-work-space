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
		x =9999; //这款雷达的最小测距距离 The minimum ranging distance of this radar
	return x;

}


/*************结合小车做动作 Combined with the small car for action*****************/
#define LEN_MUN 9
#define Alarm_Dis 420
#define BEEP_Alarm_Dis 200
float get_data[LEN_MUN];
float data_min = 0;
int data_min_index = 4;

void Get_DIS_Group(void)
{
	data_min = 9999;//每次重新赋值
	data_min_index = 4; //中间
	for(uint8_t i = 0;i<LEN_MUN;i++) //存数据
	{
		get_data[i] = App_Data_Min(((i*30)+45),((i*30)+75));  //去掉330-30这个范围的数值 //Remove values from the range of 330 to 30
		if(i == 4)
		{
			get_data[i] = App_Data_Min(170,190);
		}

		if(data_min > get_data[i])
		{
			data_min = get_data[i];//保存最小的数据
			data_min_index = i;
		}

		printf("%d = %.2f\r\n",i,get_data[i]);
	}

	printf("min:%d = %.2f\r\n",data_min_index,data_min);


}

//函数功能:小车结合雷达警卫
//Function function: Car combined with radar guard
void Car_Alarm(void)
{

	Get_DIS_Group();

	if( data_min <= BEEP_Alarm_Dis)
	{
		BEEP_ON;
		LED2_ON;
		OLED_Draw_Line("     Alarming...    ",3,false,true);
		LED1_ON;
	}
	else if( data_min <= Alarm_Dis)
	{
		LED1_ON;
		LED2_OFF;
		BEEP_OFF;
		OLED_Draw_Line("    Car Wakeup!      ",3,false,true);
	}
	else //都不在范围
	{
		LED1_OFF;
		LED2_OFF;
		BEEP_OFF;
		OLED_Draw_Line("    Normal!      ",3,false,true);
		wheel_State(MOTION_STOP, 0);//小车停止
	}

	//控制小车
	if(data_min_index<4) //4就是中间值 170-190
	{
		wheel_State(MOTION_SPIN_LEFT, 450); //小车左旋
	}
	else if(data_min_index>4)
	{
		wheel_State(MOTION_SPIN_RIGHT, 450);//小车右旋
	}
	else
	{
		wheel_State(MOTION_STOP, 0);
	}



}


