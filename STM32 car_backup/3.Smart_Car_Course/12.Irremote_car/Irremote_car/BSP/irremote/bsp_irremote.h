#ifndef __BSP_IRREMOTE_H__
#define __BSP_IRREMOTE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "bsp.h"


#define Irremote_error   	0x01
#define IR_POWER			0x00   //此按键不要使用-一旦使用就会有问题 使用外部中断无法避免。按键切换就会
#define IR_UP				0x80
#define IR_LIGHT			0x40
#define IR_LEFT				0x20
#define IR_BEEP				0xA0
#define IR_RIGHT			0x60
#define IR_LEFT_SPIN	 	0x10
#define IR_DOWN		   		0x90
#define IR_RIHGT_SPIN		0x50
#define IR_ADD				0x30
#define IR_0				0xB0
#define IR_SUB				0x70
#define IR_1				0x08
#define IR_2				0x88
#define IR_3				0x48
#define IR_4				0x28
#define IR_5				0xA8
#define IR_6				0x68
#define IR_7				0x18
#define IR_8				0x98
#define IR_9				0x58
#define CLR_CLR       		0xFF

void Print_Irrmote(void);
void Irrmote_car(void);

#ifdef __cplusplus
}
#endif

#endif

