/*
 * app_irtracking.h
 *
 *  Created on: Oct 25, 2023
 *      Author: YB-101
 */

#ifndef IRTRACKING_APP_IRTRACKING_H_
#define IRTRACKING_APP_IRTRACKING_H_

#include "bsp.h"
#include "bsp_k210.h"

void car_irtrack(void);
void Track_line(void);//正常巡线

void Road_sign_right(void); //右转优先巡线

void Road_sign_left(void); //左转优先巡线

void Road_sign_speedlimit(void); //低速巡线

void car_outbound_track(void); //出库巡线
void beep(void);

#endif /* IRTRACKING_APP_IRTRACKING_H_ */
