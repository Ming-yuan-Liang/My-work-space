#ifndef __APP_FINGER_H_
#define __APP_FINGER_H_

#include "bsp.h"

u8 Finger_Init(void);
void Add_FR(void);	//Fingerprint recording 录指纹
void Del_FR(void);	//Delete fingerprint 删除指纹
void press_FR(void);//Brushing fingerprints 刷指纹

void ShowErrMessage(u8 ensure);//Display confirmation code error message 显示确认码错误信息
void Finger_Loop(void);

#endif
