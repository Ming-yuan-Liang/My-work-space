#include "bsp_usb_serial.h"

extern USBD_HandleTypeDef hUsbDeviceFS;

// 接收数据功能在usbd_cdc_if.c里面的CDC_Receive_FS函数里
// Receive data function on USB_ Cdc_ CDC in if. c_ Receive_ In the FS function

// 接收数据的buf Buf for receiving data
uint8_t recv_buf[recv_len];
uint32_t data_nums = 0;	   // The length of received data 接收到数据的长度
uint8_t get_data_flag = 0; // Flag for receiving data 接收到数据的标志

void USB_Init(void)
{
	USBD_DeInit(&hUsbDeviceFS);

	GPIO_InitTypeDef GPIO_Initure;
	__HAL_RCC_GPIOA_CLK_ENABLE();						   /*Enable PORTA clock 使能PORTA时钟 */
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_RESET); /* PA11 = 0 */
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET); /* PA12 = 0 */

	/* PA11 pin mode setting, push pull output PA11引脚模式设置,推挽输出 */
	GPIO_Initure.Pin = GPIO_PIN_11;
	GPIO_Initure.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_Initure.Pull = GPIO_PULLDOWN;
	GPIO_Initure.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOA, &GPIO_Initure);

	/* PA12 pin mode setting, push pull output PA12引脚模式设置,推挽输出 */
	GPIO_Initure.Pin = GPIO_PIN_12;
	GPIO_Initure.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_Initure.Pull = GPIO_PULLDOWN;
	GPIO_Initure.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOA, &GPIO_Initure);

	HAL_Delay(2);
}

void Deal_Recv(void)
{
	if (get_data_flag == 1)
	{
		usb_printf("Recv_data:%s \r\nRecv_len:%d\r\n", recv_buf, data_nums);
		get_data_flag = 0;
	}
}

// printf 重定义到 usb串口(发送功能)
// Printf redefined to USB serial port (sending function)
void usb_printf(const char *format, ...)
{
	va_list args;
	uint32_t length;
	uint8_t buff[APP_TX_DATA_SIZE];

	va_start(args, format);
	length = vsnprintf((char *)buff, APP_TX_DATA_SIZE, (char *)format, args);
	va_end(args);
	CDC_Transmit_FS(buff, length);
}

// 检测usb连接的情况
// Detecting USB connection
void VCP_Status(void)
{
	static uint8_t old_status = 0;

	if (hUsbDeviceFS.dev_state != old_status)
	{
		if (hUsbDeviceFS.dev_state == USBD_STATE_CONFIGURED)
		{
			OLED_Draw_Line("USB connect", 1, true, true); // Successfully connected 连接成功
			LED1_ON;
		}
		else if (hUsbDeviceFS.dev_state == USBD_STATE_SUSPENDED)
		{
			OLED_Draw_Line("USB disconnect", 2, true, true); // Connection disconnected 连接断开
			LED1_OFF;
		}
		old_status = hUsbDeviceFS.dev_state;
	}
}
