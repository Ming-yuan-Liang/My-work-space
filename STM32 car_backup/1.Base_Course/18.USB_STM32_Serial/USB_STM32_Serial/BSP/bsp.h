#ifndef __BSP_H_
#define __BSP_H_

#define bool _Bool
#define true 1
#define false 0

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <Time.h>

#include "main.h"
#include "i2c.h"
#include "usb_device.h"
#include "gpio.h"

#include "bsp_oled.h"
#include "bsp_usb_serial.h"

void BSP_Init(void);
void BSP_Loop(void);
void VCP_Status(void);

#define LED1_ON HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET)
#define LED1_OFF HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET)

#define LED2_ON HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET)
#define LED2_OFF HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET)

#endif
