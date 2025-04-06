#include "bsp.h"

// Hardware Initialization
// Parameter:None
void BSP_Init(void)
{
	char senf_buff[10] = {'\0'};

	// 这个库初始化完成会有0xff的数据
	// After the initialization of this library is completed, there will be 0xff data sent
	USART2_UART_Init();

	HAL_Delay(10);
	strcpy(senf_buff, "$close#");
	USART2_DataString((uint8_t *)senf_buff, sizeof(senf_buff)); // 关闭k210-RGB灯
}

char senf_buf[10] = {'\0'};
// Loop Run Function
// Parameter:None
void BSP_Loop(void)
{
	static uint8_t send_key1 = 0;
	static uint8_t send_key2 = 0;
	// 使用按键，按一下改变k210的RGB颜色
	// Using the button, press once to change the RGB color of k210
	if (Key1_State(1))
	{
		switch (send_key1)
		{
		case 0:
			strcpy(senf_buf, "$blue#");
			break;
		case 1:
			strcpy(senf_buf, "$red#");
			break;
		case 2:
			strcpy(senf_buf, "$green#");
			break;
		default:
			send_key1 = 0;
		}
		send_key1 = (send_key1 + 1) % 3;
		Send_K210((uint8_t *)senf_buf,sizeof(senf_buf));
	}

	// 使用按键，按一下改变k210的RGB颜色
	// Using the button, press once to change the RGB color of k210
	if (Key2_State(1))
	{
		switch (send_key2)
		{
		case 0:
			strcpy(senf_buf, "$yellow#");
			break;
		case 1:
			strcpy(senf_buf, "$purper#");
			break;
		case 2:
			strcpy(senf_buf, "$lake#");
			break;
		default:
			send_key2 = 0;
		}
		send_key2 = (send_key2 + 1) % 3;
		Send_K210((uint8_t *)senf_buf,sizeof(senf_buf));
	}
	if (Key3_State(1))
	{
		strcpy(senf_buf, "$close#");
		Send_K210((uint8_t *)senf_buf,sizeof(senf_buf));
	}
}
