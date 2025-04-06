#ifndef __BSP_TASK_H_
#define __BSP_TASK_H_

#include "main.h"
#include "gpio.h"
#include "freertos.h"
#include "bsp_rgb.h"
#include "bsp_key.h"
#include "bsp_buzzer.h"

extern unsigned int Beep_Switch;
extern unsigned int LED1_Switch;
extern unsigned int LED2_Switch;

void Task_Entity_RGB(void);
void Task_Entity_LED(void);
void Task_Entity_BEEP(void);
void Task_Entity_KEY(void);

#endif
