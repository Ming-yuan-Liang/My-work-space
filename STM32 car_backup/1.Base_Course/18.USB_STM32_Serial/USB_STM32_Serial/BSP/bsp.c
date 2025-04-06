#include "bsp.h"

// Hardware Initialization
// Parameter:None
void BSP_Init(void)
{
	OLED_Init();
	OLED_Draw_Line("OLED init success!", 1, false, true);

	USB_Init();			  // 防止下载完程序后需要再次插拔的情况 Prevent situations where you need to plug and unplug the program again after downloading it
	MX_USB_DEVICE_Init(); // 再重新初始化 Reinitialize again
}

// Loop Run Function
// Parameter:None
void BSP_Loop(void)
{
	VCP_Status(); // 检测usb连接状态 Detecting USB connection status
	Deal_Recv();  // 处理接收的数据 Processing Received Data
	HAL_Delay(10);
}
