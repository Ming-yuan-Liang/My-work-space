#ifndef __BSP_RGB_H_
#define __BSP_RGB_H_

#include "bsp.h"

typedef enum _car_rgb
{
	RGB_R = 1,
	RGB_L,
	RGB_Max
} car_RGB_t;

typedef enum _rgb_color
{
	red = 0,
	green,
	blue,
	yellow,
	purper,
	lake,
	write,
	Max_color
} RGB_Color_t;

#define RRGB_R PEout(2)
#define RRGB_G PEout(3)
#define RRGB_B PEout(4)

#define LRGB_R PGout(1)
#define LRGB_G PEout(7)
#define LRGB_B PGout(2)

// Rgb function rgb功能
#define RRGB_SET(R, G, B) \
	RRGB_R = R;           \
	RRGB_G = G;           \
	RRGB_B = B;
#define LRGB_SET(R, G, B) \
	LRGB_R = R;           \
	LRGB_G = G;           \
	LRGB_B = B;

#define RGB_OFF_R RRGB_SET(0, 0, 0);
#define RGB_OFF_L LRGB_SET(0, 0, 0);

#define RGB_OFF_ALL \
	RGB_OFF_R;      \
	RGB_OFF_L;

void RGB_Init(void);
void Set_Color_R(RGB_Color_t color);
void Set_Color_L(RGB_Color_t color);

#endif
