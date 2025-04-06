#ifndef __BSP_BUZZER_H_
#define __BSP_BUZZER_H_

#include "bsp.h"

#define BEEP_ON HAL_GPIO_WritePin(Beep_GPIO_Port, Beep_Pin, GPIO_PIN_SET);
#define BEEP_OFF HAL_GPIO_WritePin(Beep_GPIO_Port, Beep_Pin, GPIO_PIN_RESET);
#define BEEP_Toggle HAL_GPIO_TogglePin(Beep_GPIO_Port, Beep_Pin);

#endif
