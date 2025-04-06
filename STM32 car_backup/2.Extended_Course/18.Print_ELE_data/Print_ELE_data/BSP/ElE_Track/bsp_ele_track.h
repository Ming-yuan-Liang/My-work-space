#ifndef _BSP_ELE_TRACK_H_
#define _BSP_ELE_TRACK_H_

#include "bsp.h"

#define ELE_R1_CH 		ADC_CHANNEL_10  //PC0
#define ELE_R2_CH 		ADC_CHANNEL_11  //PC1
#define ELE_R3_CH 		ADC_CHANNEL_12  //PC2

#define ELE_M1_CH 		ADC_CHANNEL_13  //PC3

#define ELE_L1_CH 		ADC_CHANNEL_2  //PA2
#define ELE_L2_CH 		ADC_CHANNEL_3  //PA3
#define ELE_L3_CH 		ADC_CHANNEL_14  //PC4


uint16_t Get_Adc_ele(uint8_t ch);
void  ele_Init(void);
void EleDataDeal(void);
void getEleData(void);
int guiyi_way(void);




#endif

