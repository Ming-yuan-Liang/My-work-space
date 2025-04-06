#include "bsp_irremote.h"


uint8_t g_hwjs_DATA = CLR_CLR;
uint8_t g_hwjs_DATA_old = CLR_CLR;
uint8_t g_data_deal;
uint16_t  g_ircar_speed=200;
uint16_t g_car_time;

uint8_t beep_state=0;
uint8_t led1_state=0;
uint8_t led2_state=0;

RGB_Color g_color_RGB = red;

// 计算低电平的持续时间 Calculate the duration of the low level
uint16_t InfraredRecvLowTime(void)
{
    uint16_t time = 0;
    while (HAL_GPIO_ReadPin(Irremote_GPIO_Port, Irremote_Pin) == 0)
    {
        if (time >= 500)
            break;
        time += 1;
        Delay_US(17);
    }
    return time;
}
// 计算高电平的持续时间 Calculate the duration of the high level
uint16_t InfraredRecvHighTime(void)
{
    uint16_t time = 0;
    while (HAL_GPIO_ReadPin(Irremote_GPIO_Port, Irremote_Pin) == 1)
    {
        if (time >= 250)
            break;
        time += 1;
        Delay_US(17);
    }
    return time;
}

uint8_t InfraredDataRecv(void) // 获取红外遥控数据 Acquisition of infrared remote control data
{
    uint16_t time;
    uint8_t i, j;
    uint8_t data[4] = {0};
    // 获取引导码 Get boot code
    time = InfraredRecvLowTime();
    if (time < 400 || time >= 500)
        return Irremote_error;
    time = InfraredRecvHighTime();
    if (time < 150 || time > 250)
        return Irremote_error;
    // 获取数据 Get data
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 8; j++)
        {
            time = InfraredRecvLowTime();
            if (time < 20 || time > 35)
                return Irremote_error;
            time = InfraredRecvHighTime(); // 通过高电平的时间长短来判断数据0,1 The data 0p1 is judged by the duration of the high level.
            if (time < 35)                 // 数据0 Data 0
            {
                data[i] <<= 1;
                data[i] |= 0x0;
            }
            else
            {
                data[i] <<= 1;
                data[i] |= 0x1;
            }
        }
    }
    return data[2];
}

// 中断回调函数 -只要按了按键会进来 Interrupt callback function-as long as the button is pressed, it will come in
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    UNUSED(GPIO_Pin);
    uint8_t data;
    data = InfraredDataRecv();

    if (data != Irremote_error)
    {
    	g_hwjs_DATA  = data;
    }

    //这是能触发长按的写法，但要确保中断是正常触发的 This is a way to trigger a long press, but make sure the interrupt is triggered normally
//    g_hwjs_DATA  = data;
//    if (g_hwjs_DATA != Irremote_error)
//       {
//
//           g_hwjs_DATA_old = g_hwjs_DATA;
//       }

    __HAL_GPIO_EXTI_CLEAR_IT(GPIO_Pin);//清掉中断 Clear the interrupt

}

/*
 * 打印红外按键值 Print infrared button valu
 *
 * Print infrared key value
 * */
void Print_Irrmote(void)
{
	if (g_hwjs_DATA != 0xFF)
	{
//		g_hwjs_DATA = g_hwjs_DATA_old; //这是能触发长按的写法，但要确保中断是正常触发的 This is a way to trigger a long press, but make sure the interrupt is triggered normally
		printf("irrmote key is :%X \r\n", g_hwjs_DATA);
		g_hwjs_DATA = 0xFF;
	}

}

/*
 * 红外遥控小车
 *
 * Infrared remote control car
 *
 * */

void Irrmote_car(void)
{
	if (g_hwjs_DATA != CLR_CLR)
		{
		g_data_deal=g_hwjs_DATA;
		g_hwjs_DATA=CLR_CLR;
		}
	switch(g_data_deal)
	{
	case IR_ADD:g_ircar_speed +=100;if(g_ircar_speed>1000)g_ircar_speed =1000;g_data_deal=g_hwjs_DATA_old;break;//加速 accelerate
	case IR_SUB:g_ircar_speed -=100;if(g_ircar_speed<100)g_ircar_speed =100;g_data_deal=g_hwjs_DATA_old;break;//减速 Deceleration
	case IR_UP:g_car_time=300;wheel_State(MOTION_RUN,g_ircar_speed);g_data_deal=g_hwjs_DATA_old; break;//前进3秒 Forward for 3 seconds
	case IR_DOWN: g_car_time=300;wheel_State(MOTION_BACK,g_ircar_speed);g_data_deal=g_hwjs_DATA_old;break;//后退3秒 Back up 3 seconds.
	case IR_LEFT:g_car_time=300; wheel_State(MOTION_LEFT,g_ircar_speed);;g_data_deal=g_hwjs_DATA_old;break;//左转3秒 Turn left for 3 seconds
	case IR_RIGHT: g_car_time=300;wheel_State(MOTION_RIGHT,g_ircar_speed);;g_data_deal=g_hwjs_DATA_old;break;//右转3秒 Turn right for 3 seconds
	case IR_LEFT_SPIN: g_car_time=300; wheel_State(MOTION_SPIN_LEFT,g_ircar_speed);g_data_deal=g_hwjs_DATA_old;break;//左旋3秒 spin left 3 seconds
	case IR_RIHGT_SPIN: g_car_time=300;wheel_State(MOTION_SPIN_RIGHT,g_ircar_speed);g_data_deal=g_hwjs_DATA_old; break;//右旋3秒 spin right 3 seconds
	case IR_BEEP: beep_state=!beep_state;Set_Buzzer(beep_state);g_data_deal=g_hwjs_DATA_old;break;//打开蜂鸣器 Turn on the buzzer.
	case IR_POWER: Set_Buzzer(0);RGB_OFF_ALL;wheel_State(MOTION_STOP,0);Set_led(1, 0);Set_led(2, 0);g_data_deal=g_hwjs_DATA_old;break;//关闭所有功能 Turn off all features
	case IR_0:wheel_State(MOTION_STOP,0);g_data_deal=g_hwjs_DATA_old;break;  //停车 Stop the car.
	case IR_1:led1_state=!led1_state;Set_led(1, led1_state);g_data_deal=g_hwjs_DATA_old;break;//打开led1 Open led1
	case IR_2:led2_state=!led2_state;Set_led(2, led2_state);g_data_deal=g_hwjs_DATA_old;break;//打开led2 Open led2
	case IR_LIGHT: //打开RGB灯
		if(g_color_RGB == red)
			g_color_RGB = Max_color;
		else g_color_RGB = red;
		Set_RGB(RGB_Max, g_color_RGB);
		g_data_deal=g_hwjs_DATA_old;
		break;
	}
}






