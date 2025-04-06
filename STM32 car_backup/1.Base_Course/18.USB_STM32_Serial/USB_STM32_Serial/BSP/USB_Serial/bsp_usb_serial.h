#ifndef __BSP_USB_SERIAL_H_
#define __BSP_USB_SERIAL_H_

#include "bsp.h"
#include <stdarg.h>
#include "usbd_cdc_if.h"

#define recv_len 200

void USB_Init(void);
void USBD_Port_Config(uint8_t state);
void usb_printf(const char *format, ...);
void Deal_Recv(void);

extern uint8_t recv_buf[recv_len];
extern uint32_t data_nums;    // 接收到数据的长度 The length of received data
extern uint8_t get_data_flag; // 接收到数据的标志 Flag for receiving data

#endif
