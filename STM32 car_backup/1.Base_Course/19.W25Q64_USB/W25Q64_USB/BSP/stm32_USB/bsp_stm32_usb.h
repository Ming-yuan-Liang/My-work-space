#ifndef __BSP_STM32_USB_H_
#define __BSP_STM32_USB_H_

#include "bsp.h"
#include <stdarg.h>
#include "usbd_storage_if.h"

void USB_Init(void);
void USBD_Port_Config(uint8_t state);
void usb_printf(const char *format, ...);
void Deal_Recv(void);
void VCP_Status(void);

#endif
