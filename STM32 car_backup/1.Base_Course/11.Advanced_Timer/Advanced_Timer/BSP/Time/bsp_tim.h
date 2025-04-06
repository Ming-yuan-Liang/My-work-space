#ifndef __BSP_TIM_H__
#define __BSP_TIM_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "bsp.h"


void TIM1_PWM_Init(void);
void TIM3_PWM_Init(void);


//计算占空比时的全局表变量
extern __IO uint16_t IC2Value;
extern __IO uint16_t IC1Value;
extern __IO float DutyCycle;
extern __IO float Frequency;


#ifdef __cplusplus
}
#endif

#endif /* __TIM_H__ */
