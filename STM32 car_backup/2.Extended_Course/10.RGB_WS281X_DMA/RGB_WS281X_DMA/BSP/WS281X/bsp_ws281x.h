#ifndef __BSP_WS281X_H
#define __BSP_WS281X_H

#include "bsp.h"
#include <math.h>

#define WS281x_GPIOx GPIOB
#define WS281x_GPIO_PIN GPIO_PIN_8

#define WS281x_TIMx TIM4
#define WS281x_TIM_CHANNEL TIM_CHANNEL_3

#define WS281x_DMA_PERIPH_ADDR (uint32_t) & (TIM4->CCR3)
#define WS281x_DMAx_CHANNELx DMA1_Channel5
#define WS281x_DMA_FLAG DMA_FLAG_TC5

#define ONE_PULSE (59)							  // 1 码计数个数 1 code count
#define ZERO_PULSE (29)							  // 0 码计数个数 0 code count
#define RESET_PULSE (48)						  // 80 复位电平个数（不能低于40） 80 Number of reset levels (cannot be less than 40)
#define LED_NUMS (14)							  // led 个数 number of leds
#define LED_DATA_LEN (24)						  // led 长度，单个需要24个字节 ed length, each requires 24 bytes
#define WS2812_DATA_LEN (LED_NUMS * LED_DATA_LEN) // ws2812灯条需要的数组长度 Array length required by ws2812 light strip

#define WS_HIGH 61 // 45
#define WS_LOW 29  // 30

//    颜色 color     	RGB
#define C_Green 0x00FF00
#define C_Red 0xFF0000
#define C_Blue 0x0000FF
#define C_Yellow 0xFFFF00
#define C_Purple 0xFF00FF
#define C_Orange 0xFF7D00
#define C_indigo 0x00FFFF
#define C_white 0xFFFFFF

typedef enum Color_WQ281x
{
	Red_WQ281X,
	Green_WQ281X,
	Blue_WQ281X,
	Yellow_WQ281X,
	Purple_WQ281X,
	Orange_WQ281X,
	Indigo_WQ281X,
	White_WQ281X,
	Max_WQ281X,
} color_WQ281x;

typedef struct RGB_Color
{
	unsigned char R;
	unsigned char G;
	unsigned char B;
	unsigned char l;
} RGB_Color;

typedef struct HSV_Color
{
	float H;
	float S;
	float V;
} HSV_Color;

void WS281x_Init(void);
void Set_Pixel_RGB(uint16_t n, uint8_t color);
void WS2812_AllOpen(uint32_t RGBcolor);
void WS2812_AllOpen_Two(uint8_t R, uint8_t G, uint8_t B);
void WS281x_Init(void);
void WS281x_CloseAll(void);
void WS281x_RainbowCycle(uint8_t wait);
void WS281x_SetPixelColor(uint16_t n, uint32_t RGBcolor);
void WS281x_Show(void);

void WS281x_ColorWipe(uint32_t color, uint8_t wait);
void WS281x_Rainbow(uint8_t wait);
void Set_WQ281x_AllOpen(uint8_t color);
void SSwitch_AllOpen_Color(uint16_t time);
void WS2812_All_LED_ONE_Color_Breath(uint16_t wait, uint32_t RGB_color);

/*
 * 数学函数
 *
 * Math functions
 * */
void __brightnessAdjust(float percent, RGB_Color RGB);

#endif /* __BSP_WS281X_H */
