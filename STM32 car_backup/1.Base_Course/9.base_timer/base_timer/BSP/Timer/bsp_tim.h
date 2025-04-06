#ifndef __BSP_TIM_H__
#define __BSP_TIM_H__

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "bsp.h"

    // extern TIM_HandleTypeDef htim6;

    void TIM6_Init(void);
    void TIM6_IRQHandler(void);

#ifdef __cplusplus
}
#endif

#endif

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
