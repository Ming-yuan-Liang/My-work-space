#ifndef __BSP_K210_H_
#define __BSP_K210_H_

#include "bsp.h"

void Change_RGB(void);
void Send_K210(uint8_t *data_str, uint16_t datasize);
void Deal_K210(uint8_t recv_msg);

#endif
