
#include <key/bsp_key.h>

/*重写中断回调处理函数*/
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	switch (GPIO_Pin)
	{
	case GPIO_PIN_3:
		Set_Buzzer(0); // key1按键功能：关闭蜂鸣器和全部LED灯 key1 button function: turn off the buzzer and all LED lights
		Set_led(1, 0);
		Set_led(2, 0);
		break;
	case GPIO_PIN_4:
		Set_led(1, 1); // key2按键功能：打开LED1 key2 key function: turn on LED1

		break;
	case GPIO_PIN_5:
		Set_Buzzer(1); // key3按键功能：打开蜂鸣器并打开LED2 key3 key function: turn on the buzzer and turn on LED2
		Set_led(2, 1);
		break;
	}
}
