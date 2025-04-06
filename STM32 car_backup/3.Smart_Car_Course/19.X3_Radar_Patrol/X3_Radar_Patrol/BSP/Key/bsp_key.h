#ifndef _BSP_KEY_H_
#define _BSP_KEY_H_

#include "bsp.h"

// The button state is opposite to the actual level.
// 按键状态，与实际电平相反。
#define KEY_PRESS 1
#define KEY_RELEASE 0

#define KEY_MODE_ONE_TIME 1
#define KEY_MODE_ALWAYS 0

uint8_t Key_Scan(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

void Key_Init_GPIO(void);

uint8_t Key1_State(uint8_t mode);
uint8_t Key1_Long_Press(uint16_t timeout);

uint8_t Key2_State(uint8_t mode);
uint8_t Key2_Long_Press(uint16_t timeout);

uint8_t Key3_State(uint8_t mode);
uint8_t Key3_Long_Press(uint16_t timeout);

#endif
