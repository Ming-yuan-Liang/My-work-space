#ifndef __BSP_USRT4_H__
#define __BSP_USRT4_H__

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "bsp.h"

    void UART4_Init(void);
    void USRT4_DataByte(uint8_t data_byte);
    void USRT4_DataString(uint8_t *data_str, uint16_t datasize);
    void Uart4_Send(uint8_t *data_str, uint16_t datasize);

#ifdef __cplusplus
}
#endif

#endif /* __USART_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
