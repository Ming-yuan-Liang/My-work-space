#ifndef __BSP_H_
#define __BSP_H_

#define bool _Bool
#define true 1
#define false 0

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <Time.h>

#include "main.h"
#include "usart.h"
#include "gpio.h"
#include "delay.h"
#include "bsp_usart.h"
#include "bsp.h"

#include "bsp_MPU6050.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
#include "dmpKey.h"
#include "dmpmap.h"
#include "mpu6050.h"

void BSP_Init(void);
void BSP_Loop(void);

#endif
