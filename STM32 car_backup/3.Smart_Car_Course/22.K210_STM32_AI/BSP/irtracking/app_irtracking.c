/*
 * app_irtracking.c
 *
 *  Created on: Oct 25, 2023
 *      Author: YB-101
 */

#include "app_irtracking.h"


extern uint8_t stop_flag;
extern uint8_t bound_num;
/*
 * 简单的4路巡线
 *
 * Simple 4-way line patrol
 * */
void car_irtrack(void)
{

	if((IN_X1 == 0 && IN_X3 == 0) && IN_X2 == 1 && IN_X4 == 1) //直走 go straight
	{
		Motion_Set_Speed(500,500,500,500);
	}


	if(IN_X1 == 0 && IN_X3 == 1 && IN_X4 == 1 && IN_X2 == 1)//小幅度调整 small adjustment
	{
		Motion_Set_Speed(0,0,500,500);
	}
	else	if(IN_X1 == 1 && IN_X3 == 0 && IN_X4 == 1 && IN_X2 == 1)
	{
		Motion_Set_Speed(500,500,0,0);
	}


	if(IN_X2 == 0 && IN_X3 == 1 ) //大幅度左右转 Turn left and right sharply
	{
		Motion_Set_Speed(-500,-500,500,500);
	}
	else if(IN_X4 == 0 && IN_X1 == 1 )
	{
		Motion_Set_Speed(500,500,-500,-500);
	}

	//其它情况保持不变 Other things remain unchanged
}

void Track_line(void) //红外循迹处理，检测黑线就是亮灯 Infrared tracking processing, detecting black line module indicator light is on
{

	if(stop_flag)//碰到停止线但超了一点，但没接收到k210信息，保持停止 It hit the stop line but exceeded it a little, but did not receive the k210 message and kept stopping.
	{
		wheel_State(MOTION_BRAKE,0);
		return ;
	}

	if((IN_X1 == 0 && IN_X3 == 0) && IN_X2 == 1 && IN_X4 == 1) //直走 go straight
	{
				Motion_Set_Pwm(600,100,600,100);
	}

	//小幅度调整
	if(IN_X1 == 0 && IN_X3 == 1 && IN_X4 == 1 && IN_X2 == 1)//左转 Turn left
	{
		Motion_Set_Pwm(-400,-400,1200,1200);

	}
	else	if(IN_X1 == 1 && IN_X3 == 0 && IN_X4 == 1 && IN_X2 == 1)//右转 Turn right
	{
		Motion_Set_Pwm(1200,1200,-400,-400);

	}

	//大幅度左右转 Turn left and right sharply
	if(IN_X2 == 0 && IN_X3 == 1 )
	{

		Motion_Set_Pwm(-400,-400,1350,1350);//左转 Turn left

	}
		else if(IN_X4 == 0 && IN_X1 == 1 )
	{
			Motion_Set_Pwm(1400,1400,-400,-400);//右转 Turn right

	}


	if((IN_X1 == 0 && IN_X2 == 0) && (IN_X3 == 0 && IN_X4 == 0))//都是黑线 All are black lines
	{

		Motion_Set_Pwm(0,0,0,0);//停止 stop
		HAL_Delay(300);//不要停止前的误判数据 Discard the misjudged data before stopping
		stop_flag = 1;//开始接收k210信息,中断处理 Start receiving k210 information and interrupt processing
	}



}
uint8_t right_left_flag = 0;
uint8_t right_left_num = 0;

/*右转优先巡线
 *
 * Right turn priority line patrol
 * */
void Road_sign_right(void)
{
	if((IN_X1 == 0 || IN_X3 == 0) && IN_X2 == 1 && IN_X4 == 1) //直走
	{
		Motion_Set_Pwm(300,300,300,300);

		if(right_left_flag == 1)
		{
			right_left_num++;
			right_left_flag = 0;
		}
	}

	if(IN_X2 == 0 && IN_X3 == 1 )
	{
		Motion_Set_Pwm(-500,-500,1400,1400);

		if(right_left_flag == 1)
		{
			right_left_num++;
			right_left_flag = 0;
		}
	}

		if(IN_X4 == 0 && IN_X1 == 1 )
	{
			Motion_Set_Pwm(1400,1400,-500,-500);

		if(right_left_flag == 1)
		{
			right_left_num++;
			right_left_flag = 0;
		}
	}

	if(IN_X1 == 0  && IN_X3 == 0 && IN_X4 == 0)//134都是黑线右转  或者是134   2可以忽略 134 is a black line and turn right, or 134 2 can be ignored.
	{
		right_left_flag = 1;
		Motion_Set_Pwm(1400,1400,-500,-500);

		HAL_Delay(400);  //加大时间 increase time
	}

	if(right_left_num == 2)
	{
		//回到正常巡线 Return to normal line patrol
		set_dataid(MAX_id);
		right_left_flag = 0 ;
		right_left_num = 0;
	}

}

/*
 * 左转优先巡线
 * Left turn priority line patrol
 * */
void Road_sign_left(void)
{
	if((IN_X1 == 0 || IN_X3 == 0) && IN_X2 == 1 && IN_X4 == 1) //直走
		{
		Motion_Set_Pwm(300,300,300,300);

			if(right_left_flag == 1)
			{
				right_left_num++;
				right_left_flag = 0;
			}
		}

		if(IN_X2 == 0 && IN_X3 == 1 )//左转 Turn left
		{
			Motion_Set_Pwm(-500,-500,1400,1400);

			if(right_left_flag == 1)
			{
				right_left_num++;
				right_left_flag = 0;
			}
		}

			if(IN_X4 == 0 && IN_X1 == 1 )//右转 Turn right
		{
				Motion_Set_Pwm(1400,1400,-500,-500);

			if(right_left_flag == 1)
			{
				right_left_num++;
				right_left_flag = 0;
			}
		}

		if(IN_X1 == 0 && IN_X2 == 0 && IN_X3 == 0 )//123都是黑线左转  4可以忽略 123 is a black line and turn left. 4 can be ignored.
		{
			right_left_flag = 1;
			Motion_Set_Pwm(-500,-500,1400,1400);

			HAL_Delay(400);  //加大时间 increase time
		}

		if(right_left_num == 2)
		{
			//回到正常巡线 Return to normal line patrol
			set_dataid(MAX_id);
			right_left_flag = 0 ;
			right_left_num = 0;
		}

}

/*
 * 低速巡线
 * Low speed line patrol
 * */
void Road_sign_speedlimit(void)
{
	if(stop_flag)//碰到停止线但超了一点，但没接收到k210信息，保持停止 It hit the stop line but exceeded it a little, but did not receive the k210 message and kept stopping.
	{
			Motion_Set_Pwm(0,0,0,0);//停止 stop
			return ;
	}

	if((IN_X1 == 0 && IN_X3 == 0) && IN_X2 == 1 && IN_X4 == 1) //直走 go straight
	{
		Motion_Set_Pwm(300,300,300,300);
	}

	//小幅度调整 small adjustment
	if(IN_X1 == 0 && IN_X3 == 1 && IN_X4 == 1 && IN_X2 == 1)
	{
		Motion_Set_Pwm(-400,-400,1200,1200);

	}
	else	if(IN_X1 == 1 && IN_X3 == 0 && IN_X4 == 1 && IN_X2 == 1)
	{
		Motion_Set_Pwm(1200,1200,-400,-400);

	}

	//大幅度左右转 Turn left and right sharply
	if(IN_X2 == 0 && IN_X3 == 1 )
	{

		Motion_Set_Pwm(-400,-400,1400,1400);//左转 Turn left

	}
		else if(IN_X4 == 0 && IN_X1 == 1 )
	{
			Motion_Set_Pwm(1400,1400,-400,-400);//右转 Turn right

	}


	if((IN_X1 == 0 && IN_X2 == 0) && (IN_X3 == 0 && IN_X4 == 0))//都是黑线 All are black lines
	{

		Motion_Set_Pwm(0,0,0,0);//停止 stop
		HAL_Delay(300);//不要停止前的误判数据 Discard the misjudged data before stopping
		stop_flag = 1;//开始接收k210信息,中断处理 Start receiving k210 information and interrupt processing
	}

}
uint8_t outbound_flag = 0; /*1:表示刚出库碰到停止线 2：表示过了停止线可以切换正常模式 0:其它情况
 1: Indicates that the stop line is encountered just after leaving the warehouse
 2: Indicates that the normal mode can be switched after passing the stop line 0: Other situations
*/
/*
 * 出库巡线
 * Outbound inspection line
 * */
void car_outbound_track(void)
{
	if((IN_X1 == 0 || IN_X3 == 0) && IN_X2 == 1 && IN_X4 == 1) //直走
		{
		Motion_Set_Pwm(600,100,600,100);

			if(outbound_flag == 1)
			{
				outbound_flag =2;
			}
		}

		if(IN_X2 == 0 && IN_X3 == 1 )
		{
			Motion_Set_Pwm(-500,-500,1400,1400);

			if(outbound_flag == 1)
			{
				outbound_flag =2;
			}

		}

			if(IN_X4 == 0 && IN_X1 == 1 )
		{
				Motion_Set_Pwm(1400,1400,-500,-500);

			if(outbound_flag == 1)
			{
				outbound_flag =2;
			}
		}

		if(IN_X1 == 0 && IN_X2 == 0 && IN_X3 == 0 && IN_X4 == 0)//都是黑线直走 The black line goes straight
		{
			if(bound_num == two)
			{
				outbound_flag = 1;
				Motion_Set_Pwm(500,500,500,500);
				HAL_Delay(200);//逃离黑线 Escape from the black line
			}

			else if(bound_num == one)
			{
				outbound_flag = 2;
			}

		}

		if(outbound_flag == 2)
		{
			//回到正常巡线 Return to normal line patrol
			set_dataid(MAX_id);
			outbound_flag = 0;

		}
}

/*
 * 鸣笛
 * whistle
 * */
void beep(void)
{
	Set_Buzzer(1);
	HAL_Delay(150);
	Set_Buzzer(0);
	HAL_Delay(100);
	Set_Buzzer(1);
	HAL_Delay(300);
	Set_Buzzer(0);
	HAL_Delay(100);

}
