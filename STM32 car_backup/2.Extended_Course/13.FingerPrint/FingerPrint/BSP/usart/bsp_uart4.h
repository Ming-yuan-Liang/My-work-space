#ifndef __BSP_UART4_H_
#define __BSP_UART4_H_

#include "bsp.h"

#define UART4_MAX_RECV_LEN		400					//Maximum receive cache bytes 最大接收缓存字节数
#define UART4_MAX_SEND_LEN		400					//Maximum Send Cache Bytes 最大发送缓存字节数
#define UART4_RX_EN 			1					//0, do not receive; 1. Receive 0,不接收;1,接收.

extern u8  	UART4_RX_BUF[UART4_MAX_RECV_LEN]; 		//Receive buffer, maximum USART4_ MAX_ RECV_ LEN Bytes 接收缓冲,最大USART4_MAX_RECV_LEN字节
extern u8  	UART4_TX_BUF[UART4_MAX_SEND_LEN]; 		//Send buffer, maximum USART4_ MAX_ SEND_ LEN Bytes 发送缓冲,最大USART4_MAX_SEND_LEN字节
extern vu16 UART4_RX_STA;   						//Received data status 接收数据状态





void UART4_Init(void);
void UART4_DataString(uint8_t * data_str, uint16_t datasize);
void UART4_DataByte(uint8_t data_byte);

#endif


