#ifndef _BSP_OLED_H
#define _BSP_OLED_H

#include "bsp.h"
#include "oled_fonts.h"

#define OLED_ADDRESS (0x3c << 1)
#define OLED_I2C I2C1

#define SSD1306_WIDTH 128
#define SSD1306_HEIGHT 32

typedef enum
{
	SSD1306_COLOR_BLACK = 0x00, /*!< Black color, no pixel */
	SSD1306_COLOR_WHITE = 0x01	/*!< Pixel is set. Color depends on LCD */
} SSD1306_COLOR_t;

void OLED_Init(void);

void SSD1306_UpdateScreen(void);
void SSD1306_ToggleInvert(void);
void SSD1306_Fill(SSD1306_COLOR_t Color);
void SSD1306_DrawPixel(uint16_t x, uint16_t y, SSD1306_COLOR_t color);
void SSD1306_GotoXY(uint16_t x, uint16_t y);
char SSD1306_Putc(char ch, FontDef_t *Font, SSD1306_COLOR_t color);
char SSD1306_Puts(char *str, FontDef_t *Font, SSD1306_COLOR_t color);
void SSD1306_DrawLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, SSD1306_COLOR_t c);
void SSD1306_DrawRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, SSD1306_COLOR_t c);
void SSD1306_DrawFilledRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, SSD1306_COLOR_t c);
void SSD1306_DrawTriangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, SSD1306_COLOR_t color);
void SSD1306_DrawCircle(int16_t x0, int16_t y0, int16_t r, SSD1306_COLOR_t c);
void SSD1306_DrawFilledCircle(int16_t x0, int16_t y0, int16_t r, SSD1306_COLOR_t c);

void ssd1306_I2C_Init(void);
void ssd1306_I2C_Write(uint8_t address, uint8_t reg, uint8_t data);
void ssd1306_I2C_WriteMulti(uint8_t address, uint8_t reg, uint8_t *data, uint16_t count);

void OLED_Clear(void);
void OLED_Refresh(void);
void OLED_Draw_String(char *data, uint8_t x, uint8_t y, bool clear, bool refresh);
void OLED_Draw_Line(char *data, uint8_t line, bool clear, bool refresh);

#endif
