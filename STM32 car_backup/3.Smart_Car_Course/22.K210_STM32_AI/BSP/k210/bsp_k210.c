
#include "bsp_k210.h"
#include "bsp.h"

uint8_t data_step = 0;
uint8_t k210_data[2] = {'\0'};
uint8_t len = 0;
static uint8_t data_id = MAX_id;//id的数据 id data

uint8_t bound_num = two;//默认是2库 The default is parking garage 2

void data_deal_k210(uint8_t data)//处理k210的串口 Processing the serial port of k210
{
	switch(data_step)
	{
		case 0: if(data == '$') data_step ++; else data_step = 0; break;
		case 1:if(data == '0') data_step ++; else data_step = 0;break;
		case 2:if(data == '9') data_step ++; else data_step = 0;break;
		//接收id信息 Receive id information
		case 3:
			if(data != ',')
			{
				k210_data[len] = data;
				len ++;
			}
			else
			{
				if(len > 2)//长度已经超出 length has exceeded
				{
					data_step = 0;
					len = 0;
					memset(k210_data,0,2);//清空buff Clear buff
				}
				else
				{
					data_step ++;
				}
			}
			break;

		case 4:
				if (data == '#')
				{
					deal_msg(len);
				}
				len = 0;
				data_step = 0;
		break;

	}
}

void deal_msg(uint8_t length)//应该不超过2位 Should not exceed 2 digits
{

	if(length == 1)
	{
		data_id = k210_data[0]-'0';
	}
	else if(length == 2)
	{
		uint8_t data_H;
		uint8_t data_L;
		data_H = k210_data[0]- '0';
		data_L = k210_data[1]- '0';
		data_id = data_H*10 +data_L;
	}
//	USART1_Send_uint8_t(data_id);
	if(data_id!=MAX_id)
	{
		stop_flag = 0;//获取正确的信息，不处理串口接收 Get the correct information without processing serial port reception
	}
}

void set_dataid(enum k210_msg id) //设置id 用于清除 Set id  for clearing
{
	data_id = id;
}

uint8_t get_dataid(void)//获取id Get id
{
	return data_id;
}


/*******************************倒库部分****************************************/
/*******************************Backing into the parking garage section****************************************/
//倒1库 Back to garage No. 1
void Reverse_parking_no1(void)
{
	bound_num = one;
	//倒右转一下 Back up and turn right
	Motion_Set_Pwm(-1600,-1600,1600,1600);
	HAL_Delay(240); //330 时间要调，满电的状态需要减少 The time needs to be adjusted. When fully charged, the time needs to be reduced.
	Motion_Set_Pwm(0,0,0,0);
	HAL_Delay(100);

	//后退 Back
	Motion_Set_Pwm(-400,-400,-400,-400);
	HAL_Delay(500);

	//调用出库 Call the exit garage function
	Car_outbound();
}

//倒2库 Back to garage No. 2
void Reverse_parking_no2(void)
{
	bound_num = two;
	//后退
	Motion_Set_Pwm(-300,-300,-300,-300);
	HAL_Delay(500);

	Motion_Set_Pwm(0,0,0,0);
	HAL_Delay(500);

	//倒右转一下 Back up and turn right
	Motion_Set_Pwm(-1500,-1500,500,500);
	HAL_Delay(600);

	Motion_Set_Pwm(0,0,0,0);
	HAL_Delay(100);

	//后退 Back
	Motion_Set_Pwm(-300,-300,-300,-300);
	HAL_Delay(200);

	//调用出库 Call the exit garage function
	Car_outbound();

}

//出库函数 Car exit function
void Car_outbound()
{
	//停车 parking
	Motion_Set_Pwm(0,0,0,0);

	HAL_Delay(2000);


	//前进 go ahead
	Motion_Set_Pwm(300,300,300,300);
	HAL_Delay(750);

	Motion_Set_Pwm(0,0,0,0);
	HAL_Delay(500);

	//前进右转 Go forward and turn right
	Motion_Set_Pwm(1500,1500,-1500,-1500);

	HAL_Delay(370); //430电池没啥电的情况 When fully charged, the time needs to be reduced.

	Motion_Set_Pwm(300,300,300,300);
	HAL_Delay(750);

	//调用出库函数 Call the exit garage function
	set_dataid(chuku_track_line);

}

