#ifndef __BSP_K210_H_
#define __BSP_K210_H_

#include "bsp.h"

void data_deal_k210(uint8_t data);
void deal_msg(uint8_t length);
void set_dataid(enum k210_msg id);
uint8_t get_dataid(void);
//倒1库
void Reverse_parking_no1(void);

//倒2库
void Reverse_parking_no2(void);

//出库
void Car_outbound(void);

#endif
