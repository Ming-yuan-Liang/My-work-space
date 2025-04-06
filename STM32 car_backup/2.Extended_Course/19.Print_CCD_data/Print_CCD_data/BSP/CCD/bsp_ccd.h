#ifndef __BSP_CCD_H_
#define __BSP_CCD_H_

#include "bsp.h"

// IO Port Operation Macro Definition IO口操作宏定义
#define BITBAND(addr, bitnum) ((addr & 0xF0000000) + 0x2000000 + ((addr & 0xFFFFF) << 5) + (bitnum << 2))
#define MEM_ADDR(addr) *((volatile unsigned long *)(addr))
#define BIT_ADDR(addr, bitnum) MEM_ADDR(BITBAND(addr, bitnum))

#define GPIOF_ODR_Addr (GPIOF_BASE + 12) // 0x40011A0C
#define GPIOF_IDR_Addr (GPIOF_BASE + 8)

#define PFout(n) BIT_ADDR(GPIOF_ODR_Addr, n) // output 输出
#define PFin(n) BIT_ADDR(GPIOF_IDR_Addr, n)  // input 输入

#define TSL_SI PFout(4)  // SI
#define TSL_CLK PFout(5) // CLK

#define CCD_ADC_CH ADC_CHANNEL_4

void Deal_Data_CCD(void);
void Find_CCD_Median(void);
void Print_CCD_data(void);

// OLED screen display section OLED屏显示部分
uint8_t *CCD_Get_ADC_128X32(void);
void OLED_Show_CCD_Image(uint8_t *p_img);

#endif
