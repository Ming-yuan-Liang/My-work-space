#include "bsp_ps2.h"

#define DELAY_TIME delay_us(5);

uint16_t Handkey;														  // Read key values and store them at zero. 按键值读取，零时存储。
uint8_t Comd[2] = {0x01, 0x42};											  // Start command. Request Data 开始命令。请求数据
uint8_t Data[9] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}; // Data storage array 数据存储数组
uint16_t MASK[] = {
	PSB_SELECT,
	PSB_L3,
	PSB_R3,
	PSB_START,
	PSB_PAD_UP,
	PSB_PAD_RIGHT,
	PSB_PAD_DOWN,
	PSB_PAD_LEFT,
	PSB_L2,
	PSB_R2,
	PSB_L1,
	PSB_R1,
	PSB_GREEN,
	PSB_RED,
	PSB_BLUE,
	PSB_PINK};

/**************************************************************************
函数功能：向手柄发送命令
入口参数：CMD指令
返回  值：无
Function function: Send commands to the handle
Entry parameter: CMD instruction
Return value: None
**************************************************************************/
void PS2_Cmd(uint8_t CMD)
{
	volatile uint16_t ref = 0x01;
	Data[1] = 0;
	for (ref = 0x01; ref < 0x0100; ref <<= 1)
	{
		if (ref & CMD)
		{
			DO_H; // Output one control bit 输出一位控制位
		}
		else
			DO_L;
		CLK_H; // Clock up 时钟拉高
		DELAY_TIME;
		CLK_L;
		DELAY_TIME;
		CLK_H;
		if (DI) // At high levels 为高电平的时候
			Data[1] = ref | Data[1];
	}
	delay_us(16);
}
/**************************************************************************
函数功能：判断是否为红灯模式,0x41=模拟绿灯，0x73=模拟红灯
入口参数：CMD指令
返回  值：0，红灯模式  其他，其他模式
Function function: Determine whether it is in red light mode, 0x41=simulate green light, 0x73=simulate red light
Entry parameter: CMD instruction
Return value: 0, red light mode Other, other modes
**************************************************************************/
uint8_t PS2_RedLight(void)
{
	CS_L;
	PS2_Cmd(Comd[0]); // start command 开始命令
	PS2_Cmd(Comd[1]); // request data 请求数据
	CS_H;
	if (Data[1] == 0X73)
		return 0;
	else
		return 1;
}
/**************************************************************************
函数功能：读取手柄数据
入口参数：无
返回  值：无
Function function: Read handle data
Entry parameters: None
Return value: None
**************************************************************************/
void PS2_ReadData(void)
{
	volatile uint8_t byte = 0;
	volatile uint16_t ref = 0x01;
	CS_L;
	PS2_Cmd(Comd[0]);				 // start command 开始命令
	PS2_Cmd(Comd[1]);				 // request data 请求数据
	for (byte = 2; byte < 9; byte++) // Start accepting data 开始接受数据
	{
		for (ref = 0x01; ref < 0x100; ref <<= 1)
		{
			CLK_H;
			DELAY_TIME;
			CLK_L;
			DELAY_TIME;
			CLK_H;
			if (DI)
				Data[byte] = ref | Data[byte];
		}
		delay_us(16);
	}
	CS_H;
}
/**************************************************************************
函数功能：对读出来的PS2的数据进行处理,只处理按键部分
入口参数：CMD指令
返回  值：无
//只有一个按键按下时按下为0， 未按下为1
Function function: Process the read data of PS2, only handle the button part
Entry parameter: CMD instruction
Return value: None
//0 when only one button is pressed, 1 when not pressed
**************************************************************************/
uint8_t PS2_DataKey()
{
	uint8_t index;
	PS2_ClearData();
	PS2_ReadData();
	Handkey = (Data[4] << 8) | Data[3]; // These are 16 buttons that are pressed as 0 and not pressed as 1 这是16个按键  按下为0， 未按下为1
	for (index = 0; index < 16; index++)
	{
		if ((Handkey & (1 << (MASK[index] - 1))) == 0)
			return index + 1;
	}
	return 0; // No buttons pressed 没有任何按键按下
}
/**************************************************************************
函数功能：向手柄发送命令
入口参数：得到一个摇杆的模拟量	 范围0~256
返回  值：无
Function function: Send commands to the handle
Entry parameters: Obtain an analog range of 0-256 for a joystick
Return value: None
**************************************************************************/
uint8_t PS2_AnologData(uint8_t button)
{
	return Data[button];
}
// Clear data buffer 清除数据缓冲区
void PS2_ClearData()
{
	uint8_t a;
	for (a = 0; a < 9; a++)
		Data[a] = 0x00;
}
/******************************************************
函数功能: 手柄震动函数，
Calls:		 void PS2_Cmd(uint8_t CMD);
入口参数: motor1:右侧小震动电机 0x00关，其他开
			motor2:左侧大震动电机 0x40~0xFF 电机开，值越大 震动越大
返回  值:无
Function function: Handle vibration function,
Calls: void PS2_ Cmd (uint8_t CMD);
Entrance parameter: motor1: Right small vibration motor 0x00 off, others on
Motor2: Left side large vibration motor 0x40~0xFF, motor on, the greater the value, the greater the vibration
Return value: None
******************************************************/
void PS2_Vibration(uint8_t motor1, uint8_t motor2)
{
	CS_L;
	delay_us(16);
	PS2_Cmd(0x01); // start command 开始命令
	PS2_Cmd(0x42); // request data 请求数据
	PS2_Cmd(0X00);
	PS2_Cmd(motor1);
	PS2_Cmd(motor2);
	PS2_Cmd(0X00);
	PS2_Cmd(0X00);
	PS2_Cmd(0X00);
	PS2_Cmd(0X00);
	CS_H;
	delay_us(16);
}
/**************************************************************************
函数功能：short poll
入口参数：无
返回  值：无
Function function: short poll
Entry parameters: None
Return value: None
**************************************************************************/
void PS2_ShortPoll(void)
{
	CS_L;
	delay_us(16);
	PS2_Cmd(0x01);
	PS2_Cmd(0x42);
	PS2_Cmd(0X00);
	PS2_Cmd(0x00);
	PS2_Cmd(0x00);
	CS_H;
	delay_us(16);
}
/**************************************************************************
函数功能：进入配置
入口参数：无
返回  值：无
Function Function: Enter Configuration
Entry parameters: None
Return value: None
**************************************************************************/
void PS2_EnterConfing(void)
{
	CS_L;
	delay_us(16);
	PS2_Cmd(0x01);
	PS2_Cmd(0x43);
	PS2_Cmd(0X00);
	PS2_Cmd(0x01);
	PS2_Cmd(0x00);
	PS2_Cmd(0X00);
	PS2_Cmd(0X00);
	PS2_Cmd(0X00);
	PS2_Cmd(0X00);
	CS_H;
	delay_us(16);
}
/**************************************************************************
函数功能：发送模式设置
入口参数：无
返回  值：无
Function Function: Sending Mode Settings
Entry parameters: None
Return value: None
**************************************************************************/
void PS2_TurnOnAnalogMode(void)
{
	CS_L;
	PS2_Cmd(0x01);
	PS2_Cmd(0x44);
	PS2_Cmd(0X00);
	PS2_Cmd(0x01); // analog=0x01;digital=0x00  Software settings sending mode 软件设置发送模式
	PS2_Cmd(0x03); // Ox03 latch setting, that is, the mode cannot be set by pressing the "MODE" button. Ox03锁存设置，即不可通过按键“MODE”设置模式。
				   // 0xEE does not lock software settings, and the mode can be set by pressing the "MODE" button. 0xEE不锁存软件设置，可通过按键“MODE”设置模式。
	PS2_Cmd(0X00);
	PS2_Cmd(0X00);
	PS2_Cmd(0X00);
	PS2_Cmd(0X00);
	CS_H;
	delay_us(16);
}
/**************************************************************************
函数功能：振动设置
入口参数：无
返回  值：无
Function Function: Vibration Settings
Entry parameters: None
Return value: None
**************************************************************************/
void PS2_VibrationMode(void)
{
	CS_L;
	delay_us(16);
	PS2_Cmd(0x01);
	PS2_Cmd(0x4D);
	PS2_Cmd(0X00);
	PS2_Cmd(0x00);
	PS2_Cmd(0X01);
	CS_H;
	delay_us(16);
}
/**************************************************************************
函数功能：完成并保存配置
入口参数：无
返回  值：无
Function function: Complete and save configuration
Entry parameters: None
Return value: None
**************************************************************************/
void PS2_ExitConfing(void)
{
	CS_L;
	delay_us(16);
	PS2_Cmd(0x01);
	PS2_Cmd(0x43);
	PS2_Cmd(0X00);
	PS2_Cmd(0x00);
	PS2_Cmd(0x5A);
	PS2_Cmd(0x5A);
	PS2_Cmd(0x5A);
	PS2_Cmd(0x5A);
	PS2_Cmd(0x5A);
	CS_H;
	delay_us(16);
}
/**************************************************************************
函数功能：手柄配置初始化
入口参数：无
返回  值：无
Function Function: Handle Configuration Initialization
Entry parameters: None
Return value: None
**************************************************************************/
void PS2_SetInit(void)
{
	PS2_ShortPoll();
	PS2_ShortPoll();
	PS2_ShortPoll();
	PS2_EnterConfing();		// Entering configuration mode 进入配置模式
	PS2_TurnOnAnalogMode(); // Configure the "Traffic Light" mode and choose whether to save it “红绿灯”配置模式，并选择是否保存
	// PS2_VibrationMode();	//Enable vibration mode 开启震动模式
	PS2_ExitConfing(); // Complete and save the configuration 完成并保存配置
}
