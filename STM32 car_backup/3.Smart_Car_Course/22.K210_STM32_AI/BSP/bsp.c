#include "bsp.h"

#define speed_go 300 //出停止线速度 Stop line speed
#define de_time  200  //出停止线延迟时间 Exit stop line delay time

uint8_t stop_flag = 0;
uint32_t n_stime = 0;   //恢复正常巡线的时间 Time to resume normal line patrol
uint16_t wait_k210 = 700;//等待k210启动的时间 Waiting time for k210 to start
uint8_t id_num = MAX_id;
uint8_t id_num_back = MAX_id;

void BSP_Init(void)
{

	Bsp_Tim_Init();
	PID_Param_Init();//电机PID初始化 Motor PID initialization
	// 这个库初始化完成会有0xff的数据
	// After the initialization of this library is completed, there will be 0xff data sent
	USART2_UART_Init();


		//设置一个等待k210正常开启的时间 Set a time to wait for k210 to turn on normally
		while(wait_k210);

}


void BSP_Loop(void)
{


		id_num = get_dataid();//获取最新的id Get the latest id

		if(id_num != id_num_back)//状态发生改变 status changes
		{
				id_num_back = id_num;

				//以下的标志都逃离黑线 The following signs are all escaping from the black line
				switch(id_num)
				{
					case green_light:
					case school:
					case walk:
					case right:
					case left:
					case freeSpeed:
					case limitSpeed:
					case horn :
						Leave_Stop();
						Motion_Set_Pwm(200,100,200,100);//处理出黑线检查不到线的状态 Handle the situation where the black line cannot be checked and the line cannot be checked
						break;


					case one:
							Reverse_parking_no1();//倒1库 Back up into parking garage 1
					break;

					case two:
							Reverse_parking_no2();//倒2库 Back up into parking garage 2
					break;


					case chuku_track_line: break; //不做任何操作 Do nothing

					default:Motion_Set_Pwm(200,100,200,100);//处理出黑线检查不到线的状态 Handle the situation where the black line cannot be checked and the line cannot be checked
				}

		}

		switch(id_num_back)
		{
			case red_light:
				Motion_Set_Speed(0,0,0,0);//小车停止 Car stops
				set_dataid(MAX_id);//回到正常巡线 Return to normal line patrol
			break;

			case green_light:
				set_dataid(MAX_id);//回到正常巡线 Return to normal line patrol
			break;

			case school:
			case walk:
				set_dataid(MAX_id);//回到正常巡线 Return to normal line patrol
				break;

			case right:
				Road_sign_right();//右转优先巡线 Right turn priority line patrol
			break;

			case left:
				Road_sign_left();//左转优先巡线 Left turn priority line patrol
				break;

			case freeSpeed:
				set_dataid(MAX_id);//回到正常巡线 Return to normal line patrol
				break;

			case limitSpeed:
				Road_sign_speedlimit();//低速巡线 Low speed line patrol
			break;

			case chuku_track_line://出库后的巡线 Line patrol after exiting the garage
					car_outbound_track();
					break;
			case horn:
					beep();
					break;

			//不做任何处理 No processing
			case one:
			case two:


			default: Track_line();//调用正常巡线函数 Call the normal line following function
		}



}

//出停止线 exit stop line

void Leave_Stop(void)
{
	Motion_Set_Pwm(speed_go,speed_go,speed_go,speed_go);
	HAL_Delay(de_time);
}
