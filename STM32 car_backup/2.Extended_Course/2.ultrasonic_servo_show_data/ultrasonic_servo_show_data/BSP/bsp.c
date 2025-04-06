#include "bsp.h"

// Hardware Initialization
// Parameter:None

void BSP_Init(void)
{
	Delay_Init();	  // 延迟初始化 Delayed initialization
	Bsp_UART1_Init(); // 串口1初始化 usart1 initialization
	Bsp_TIM7_Init();  // tim7初始化 tim7 initialization
}

// Loop Run Function
// Parameter:None
float dis;
void BSP_Loop(void)
{

	PwmServo_Set_Angle(0, 90); // 超声波朝正前方角度。如果不是朝正前方，需要调节角度 The ultrasound is straight ahead.If it's not straight ahead, you need to adjust the angle.
	HAL_Delay(1000);
	dis = Get_distance();
	if (dis == -1)
	{
		printf("Front_distance Beyond the maximum measuring range of 5m.\r\n");
	}
	else
	{
		printf("Front_distance = %.2f cm\r\n", dis); // 打印前方超声波的距离 Print ultrasonic distance
	}

	PwmServo_Set_Angle(0, 180); // 超声波朝左边角度。如果不是朝左边，需要调节角度 The ultrasound is pointing to the left.If it's not to the left, you need to adjust the angle.
	HAL_Delay(1000);
	dis = Get_distance();
	if (dis == -1)
	{
		printf("Left_distance Beyond the maximum measuring range of 5m.\r\n");
	}
	else

	{
		printf("Left_distance = %.2f cm\r\n", dis);
	}

	PwmServo_Set_Angle(0, 0); // 超声波朝右边角度。如果不是朝右边，需要调节角度  The ultrasound is pointing to the right.If it's not to the right, you need to adjust the angle.
	HAL_Delay(1000);
	dis = Get_distance();
	if (dis == -1)
	{
		printf("right_distance Beyond the maximum measuring range of 5m.\r\n");
	}
	else
	{
		printf("right_distance = %.2f cm\r\n", dis);
	}
}
