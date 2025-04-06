#ifndef __BSP_ADC_H__
#define __BSP_ADC_H__

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

    extern ADC_HandleTypeDef hadc3;

#define SEEK_ADC_CH ADC_CHANNEL_6

    void SEEK_ADC3_Init(void);
    void user_lightseek_detect();

#ifdef __cplusplus
}
#endif

#endif /* __ADC_H__ */
