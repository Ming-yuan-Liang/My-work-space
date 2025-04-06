#include "bsp_ws281x.h"

uint16_t static RGB_buffur[RESET_PULSE + WS2812_DATA_LEN] = {0};

RGB_Color rgb_color;
HSV_Color hsv_color;

/**
 * @brief  initialize WS281x LED
 * @param  None
 * @retval None
 */

void WS281x_Init(void)
{
  /*关闭所有灯珠 Turn off all lamp beads*/
  WS281x_CloseAll();
  Delay_MS(100);
}

void WS281x_Show(void)
{
  HAL_TIM_PWM_Start_DMA(&htim4, WS281x_TIM_CHANNEL, (uint32_t *)RGB_buffur, (uint16_t)(RESET_PULSE + WS2812_DATA_LEN));
}

void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
  HAL_TIM_PWM_Stop_DMA(&htim4, WS281x_TIM_CHANNEL);
}

static void WS281X_SET_RGB(uint8_t R, uint8_t G, uint8_t B, uint16_t num)
{
  // 指针偏移:需要跳过复位信号的N个0 Pointer offset: N zeros that need to be skipped in the reset signal
  uint16_t *p = (RGB_buffur + RESET_PULSE) + (num * LED_DATA_LEN);

  for (uint16_t i = 0; i < 8; i++)
  {
    // 填充数组
    p[i] = (G << i) & (0x80) ? ONE_PULSE : ZERO_PULSE;
    p[i + 8] = (R << i) & (0x80) ? ONE_PULSE : ZERO_PULSE;
    p[i + 16] = (B << i) & (0x80) ? ONE_PULSE : ZERO_PULSE;
  }
}

/**
 * @brief  将RGB颜色组合到一个32位数据中存储 Combine RGB colors into one 32-bit data for storage
 * @param  red：  0-255
 *         green：0-255
 *         blue： 0-255
 * @retval None
 */

static uint32_t WS281x_Color(uint8_t red, uint8_t green, uint8_t blue)
{
  return green << 16 | red << 8 | blue;
}

/**
  * @brief  给特定LED灯设定颜色-但不显示 Set a color for a specific LED - but not display it
  * @param  ｎ：LED灯号  LED light signal
　*          GRBClor: 32位的颜色值 32-bit color values
  * @retval None
  */

void WS281x_SetPixelColor(uint16_t n, uint32_t RGBcolor)
{
  uint8_t R = (RGBcolor & 0xFF0000) >> 16;
  uint8_t G = (RGBcolor & 0x00FF00) >> 8;
  uint8_t B = (RGBcolor & 0x0000FF);
  WS281X_SET_RGB(R, G, B, n);
}

/*
 * 关闭所有灯
 *
 * turn off all lights
 * */

void WS281x_CloseAll(void)
{
  for (uint8_t i = 0; i < LED_NUMS; i++)
  {
    WS281X_SET_RGB(0x00, 0x00, 0x00, i);
  }
  WS281x_Show();
}

/*
 * 打开所有灯 -方式1
 *
 * Turn on all lights - Way 1
 * */

void WS2812_AllOpen(uint32_t RGBcolor)
{
  uint8_t R = (RGBcolor & 0xFF0000) >> 16;
  uint8_t G = (RGBcolor & 0x00FF00) >> 8;
  uint8_t B = (RGBcolor & 0x0000FF);

  for (uint8_t i = 0; i < LED_NUMS; i++)
  {
    WS281X_SET_RGB(R, G, B, i);
  }
  WS281x_Show();
}

/*
 * 打开所有灯 -方式2
 *
 * Turn on all lights - Way 2
 * */

void WS2812_AllOpen_Two(uint8_t R, uint8_t G, uint8_t B)
{
  for (uint8_t i = 0; i < LED_NUMS; i++)
  {
    WS281X_SET_RGB(R, G, B, i);
  }
  WS281x_Show();
}

uint32_t WS281x_Wheel(uint8_t wheelPos)
{
  wheelPos = 255 - wheelPos;
  if (wheelPos < 85)
  {
    return WS281x_Color(255 - wheelPos * 3, 0, wheelPos * 3);
  }
  if (wheelPos < 170)
  {
    wheelPos -= 85;
    return WS281x_Color(0, wheelPos * 3, 255 - wheelPos * 3);
  }
  wheelPos -= 170;
  return WS281x_Color(wheelPos * 3, 255 - wheelPos * 3, 0);
}

/*
 * 流水灯特效
 * color:什么颜色点亮
 * wait:间隔的时间（ms）0-255
 *
 * Water light special effects
 * color: what color lights up
 * wait: interval time (ms) 0-255
 * */

void WS281x_ColorWipe(uint32_t color, uint8_t wait)
{
  for (uint16_t i = 0; i < LED_NUMS; i++)
  {
    WS281x_SetPixelColor(i, color);
    WS281x_Show();
    HAL_Delay(wait);
  }
}

/*
 * 颜色转换
 * wait:间隔的时间（ms）0-255
 *
 * color conversion
 * wait: interval time (ms) 0-255
 * */

void WS281x_Rainbow(uint8_t wait)
{
  uint16_t i, j;

  for (j = 0; j < 256; j++)
  {
    for (i = 0; i < LED_NUMS; i++)
    {
      WS281x_SetPixelColor(i, WS281x_Wheel((i + j) & 255));
    }
    WS281x_Show();
    HAL_Delay(wait);
  }
}

/*
 * 彩虹特效跑马灯
 * wait:间隔的时间（ms）0-255
 *
 * Rainbow special effect marquee
 * wait: interval time (ms) 0-255
 * */

void WS281x_RainbowCycle(uint8_t wait)
{
  uint16_t i, j;

  for (j = 0; j < 256 * 5; j++)
  { // 5 cycles of all colors on wheel
    for (i = 0; i < LED_NUMS; i++)
    {
      WS281x_SetPixelColor(i, WS281x_Wheel(((i * 256 / LED_NUMS) + j) & 255));
    }
    WS281x_Show();
    HAL_Delay(wait);
  }
}

/**
 * @Description  	WS2812 设置灯珠颜色（固定的） WS2812 Set lamp bead color (fixed)
 * @Param       		 n:第几个灯珠   color:哪种颜色（0-7） n: Which lamp bead color: Which color (0-7)
 * @Return
 */
void Set_Pixel_RGB(uint16_t n, uint8_t color) // n从0开始 n starts from 0
{
  switch (color)
  {
  case Red_WQ281X:
    WS281X_SET_RGB(255, 0, 0, n);
    break;
  case Green_WQ281X:
    WS281X_SET_RGB(0, 255, 0, n);
    break;
  case Blue_WQ281X:
    WS281X_SET_RGB(0, 0, 255, n);
    break;
  case Yellow_WQ281X:
    WS281X_SET_RGB(255, 255, 0, n);
    break;
  case Purple_WQ281X:
    WS281X_SET_RGB(255, 0, 255, n);
    break;
  case Orange_WQ281X:
    WS281X_SET_RGB(255, 125, 0, n);
    break;
  case Indigo_WQ281X:
    WS281X_SET_RGB(0, 255, 255, n);
    break;
  case White_WQ281X:
    WS281X_SET_RGB(255, 255, 255, n);
    break;
  }

  WS281x_Show();
  HAL_Delay(300);
}

/**
 * @Description 设置所有灯的颜色(同一种) Set the color of all lights (same)
 *
 *@Param     	 NONE
 *@Return    	NONE
 */
void Set_WQ281x_AllOpen(uint8_t color)
{
  switch (color)
  {
  case Red_WQ281X:
    WS2812_AllOpen_Two(255, 0, 0);
    break;
  case Green_WQ281X:
    WS2812_AllOpen_Two(0, 255, 0);
    break;
  case Blue_WQ281X:
    WS2812_AllOpen_Two(0, 0, 255);
    break;
  case Yellow_WQ281X:
    WS2812_AllOpen_Two(255, 255, 0);
    break;
  case Purple_WQ281X:
    WS2812_AllOpen_Two(255, 0, 255);
    break;
  case Orange_WQ281X:
    WS2812_AllOpen_Two(255, 125, 0);
    break;
  case Indigo_WQ281X:
    WS2812_AllOpen_Two(0, 255, 255);
    break;
  case White_WQ281X:
    WS2812_AllOpen_Two(255, 255, 255);
    break;
  }

  WS281x_Show();
}

/**
 * @Description 设置所有灯的颜色在一定时间切换 Set the color of all lights to switch at a certain time
 *
 *@Param time    	间隔时间 Intervals
 *@Return    		NONE
 */
void SSwitch_AllOpen_Color(uint16_t time) // ms为单位 ms is the unit
{
  for (color_WQ281x i = Red_WQ281X; i < Max_WQ281X; i++)
  {
    Set_WQ281x_AllOpen(i);
    Delay_MS(time);
  }
}

// 单色呼吸灯 暗->亮->暗 Monochrome breathing light dark->bright->dark
void WS2812_All_LED_ONE_Color_Breath(uint16_t wait, uint32_t RGB_color)
{
  uint8_t i = 0;
  uint16_t j = 0;
  rgb_color.G = RGB_color >> 8;
  rgb_color.R = RGB_color >> 16;
  rgb_color.B = RGB_color;
  for (i = 1; i <= 100; i++)
  {
    __brightnessAdjust(i / 100.0f, rgb_color);
    for (j = 0; j < LED_NUMS; j++)
    {
      WS281x_SetPixelColor(j, ((rgb_color.R << 16) | (rgb_color.G << 8) | (rgb_color.B)));
    }
    WS281x_Show();
    HAL_Delay(wait);
  }

  for (i = 100; i >= 1; i--)
  {
    __brightnessAdjust(i / 100.0f, rgb_color);
    for (j = 0; j < LED_NUMS; j++)
    {
      WS281x_SetPixelColor(j, ((rgb_color.R << 16) | (rgb_color.G << 8) | (rgb_color.B)));
    }
    WS281x_Show();
    HAL_Delay(wait);
  }
}

/**
 * @Description  	获得两数最大值 Get the maximum of two numbers
 * @Param     	  {float a,float b}
 * @Return    	  {float}
 */
float __getMaxValue(float a, float b)
{
  return a >= b ? a : b;
}

/**
 * @Description  	获得两数最小值 Get the minimum of two numbers
 * @Param     	  {void}
 * @Return    	  {void}
 */
float __getMinValue(float a, float b)
{
  return a <= b ? a : b;
}

/**
 * @Description  	RGB 转为 HSV RGB to HSV
 * @Param     	  {RGB_Color RGB, HSV_Color *HSV}
 * @Return    	  {void}
 */
void __RGB_2_HSV(RGB_Color RGB, HSV_Color *HSV)
{
  float r, g, b, minRGB, maxRGB, deltaRGB;

  r = RGB.R / 255.0f;
  g = RGB.G / 255.0f;
  b = RGB.B / 255.0f;
  maxRGB = __getMaxValue(r, __getMaxValue(g, b));
  minRGB = __getMinValue(r, __getMinValue(g, b));
  deltaRGB = maxRGB - minRGB;

  HSV->V = deltaRGB;
  if (maxRGB != 0.0f)
  {
    HSV->S = deltaRGB / maxRGB;
  }
  else
  {
    HSV->S = 0.0f;
  }
  if (HSV->S <= 0.0f)
  {
    HSV->H = 0.0f;
  }
  else
  {
    if (r == maxRGB)
    {
      HSV->H = (g - b) / deltaRGB;
    }
    else
    {
      if (g == maxRGB)
      {
        HSV->H = 2.0f + (b - r) / deltaRGB;
      }
      else
      {
        if (b == maxRGB)
        {
          HSV->H = 4.0f + (r - g) / deltaRGB;
        }
      }
    }
    HSV->H = HSV->H * 60.0f;
    if (HSV->H < 0.0f)
    {
      HSV->H += 360;
    }
    HSV->H /= 360;
  }
}

/**
 * @Description  	HSV 转为 RGB HSV to RGB
 * @Param     	  {void}
 * @Return    	  {void}
 */
void __HSV_2_RGB(HSV_Color HSV, RGB_Color *RGB)
{
  float R, G, B, aa, bb, cc, f;
  int k;
  if (HSV.S <= 0.0f)
    R = G = B = HSV.V;
  else
  {
    if (HSV.H == 1.0f)
    {
      HSV.H = 0.0f;
    }
    HSV.H *= 6.0f;
    k = (int)floor(HSV.H);
    f = HSV.H - k;
    aa = HSV.V * (1.0f - HSV.S);
    bb = HSV.V * (1.0f - HSV.S * f);
    cc = HSV.V * (1.0f - (HSV.S * (1.0f - f)));
    switch (k)
    {
    case 0:
      R = HSV.V;
      G = cc;
      B = aa;
      break;
    case 1:
      R = bb;
      G = HSV.V;
      B = aa;
      break;
    case 2:
      R = aa;
      G = HSV.V;
      B = cc;
      break;
    case 3:
      R = aa;
      G = bb;
      B = HSV.V;
      break;
    case 4:
      R = cc;
      G = aa;
      B = HSV.V;
      break;
    case 5:
      R = HSV.V;
      G = aa;
      B = bb;
      break;
    }
  }
  RGB->R = (unsigned char)(R * 255);
  RGB->G = (unsigned char)(G * 255);
  RGB->B = (unsigned char)(B * 255);
}

/**
 * @Description  	亮度调节 Dimming
 * @Param     	  {void}
 * @Return    	  {void}
 */
void __brightnessAdjust(float percent, RGB_Color RGB)
{
  if (percent < 0.01f)
  {
    percent = 0.01f;
  }
  if (percent > 1.0f)
  {
    percent = 1.0f;
  }
  __RGB_2_HSV(RGB, &hsv_color);
  hsv_color.V = percent;
  __HSV_2_RGB(hsv_color, &rgb_color);
}
