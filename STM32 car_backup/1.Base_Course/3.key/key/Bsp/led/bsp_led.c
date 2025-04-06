/*
 * bsp_led.c
 *
 *  Created on: Oct 9, 2023
 *      Author: YB-101
 */

#include <led/bsp_led.h>

/*
 * 打开或者关闭LED1和LED2 Turn on or off LED1 and LED2
 * id：LED1:1 LED2：2  i：0和1  0：关闭LED灯  1：打开LED灯 id: LED1:1 LED2: 2 i: 0 and 1 0: turn off the LED light 1: turn on the LED light
 * */
void Set_led(uint8_t id, uint8_t i)
{
	if (id == 1)
	{
		if (i == 0)
		{
			HAL_GPIO_WritePin(GPIOG, led1_Pin, GPIO_PIN_RESET);
		}
		else
		{
			HAL_GPIO_WritePin(GPIOG, led1_Pin, GPIO_PIN_SET);
		}
	}
	if (id == 2)
	{
		if (i == 0)
		{
			HAL_GPIO_WritePin(GPIOG, led2_Pin, GPIO_PIN_RESET);
		}
		else
		{
			HAL_GPIO_WritePin(GPIOG, led2_Pin, GPIO_PIN_SET);
		}
	}
}
