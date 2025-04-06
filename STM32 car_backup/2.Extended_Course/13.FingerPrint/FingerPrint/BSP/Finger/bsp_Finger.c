#include "bsp_Finger.h"

u32 AS608Addr = 0XFFFFFFFF; //default addr 默认地址

// Sending a Byte through a Serial Port 串口发送一个字节
static void MYUSART_SendData(u8 data)
{
	UART4_DataByte(data);
}
// Send header 发送包头
static void SendHead(void)
{
	MYUSART_SendData(0xEF);
	MYUSART_SendData(0x01);
}
// Sending Address 发送地址
static void SendAddr(void)
{
	MYUSART_SendData(AS608Addr >> 24);
	MYUSART_SendData(AS608Addr >> 16);
	MYUSART_SendData(AS608Addr >> 8);
	MYUSART_SendData(AS608Addr);
}
// Send package identification, 发送包标识,
static void SendFlag(u8 flag)
{
	MYUSART_SendData(flag);
}
// Send packet length 发送包长度
static void SendLength(int length)
{
	MYUSART_SendData(length >> 8);
	MYUSART_SendData(length);
}
// Send command code 发送指令码
static void Sendcmd(u8 cmd)
{
	MYUSART_SendData(cmd);
}
// Send checksum 发送校验和
static void SendCheck(u16 check)
{
	MYUSART_SendData(check >> 8);
	MYUSART_SendData(check);
}

// 判断中断接收的数组有没有应答包
// waittime为等待中断接收数据的时间（单位1ms）
// 返回值：数据包首地址
//Determine if the array received by the interrupt has a response packet
//Waittime is the time spent waiting for an interrupt to receive data (in 1ms)
//Return value: packet first address
static u8 *JudgeStr(u16 waittime)
{
	char *data;
	u8 str[8];
	str[0] = 0xef;
	str[1] = 0x01;
	str[2] = AS608Addr >> 24;
	str[3] = AS608Addr >> 16;
	str[4] = AS608Addr >> 8;
	str[5] = AS608Addr;
	str[6] = 0x07;
	str[7] = '\0';
	UART4_RX_STA = 0;
	while (--waittime)
	{
		delay_ms(1);
		if (UART4_RX_STA & 0X8000) // Received data once 接收到一次数据
		{
			UART4_RX_STA = 0;
			data = strstr((const char *)UART4_RX_BUF, (const char *)str);
			if (data)
				return (u8 *)data;
		}
	}
	return 0;
}

// 录入图像 PS_GetImage
// 功能:探测手指，探测到后录入指纹图像存于ImageBuffer。
// 模块返回确认字
//Input image PS_ GetImage
//Function: Detect fingers, input fingerprint images after detection, and store them in ImageBuffer.
//Module return confirmation word
u8 PS_GetImage(void)
{
	u16 temp;
	u8 ensure;
	u8 *data;
	SendHead();
	SendAddr();
	SendFlag(0x01); // Command package identification 命令包标识
	SendLength(0x03);
	Sendcmd(0x01);
	temp = 0x01 + 0x03 + 0x01;
	SendCheck(temp);
	data = JudgeStr(2000);
	if (data)
		ensure = data[9];
	else
		ensure = 0xff;
	return ensure;
}

// 生成特征 PS_GenChar
// 功能:将ImageBuffer中的原始图像生成指纹特征文件存于CharBuffer1或CharBuffer2
// 参数:BufferID --> charBuffer1:0x01	charBuffer1:0x02
// 模块返回确认字
//Generate feature PS_ GenChar
//Function: Generate fingerprint feature files from the original images in ImageBuffer and store them in CharBuffer1 or CharBuffer2
//Parameter: BufferID -->charBuffer1: 0x01 charBuffer1: 0x02
//Module return confirmation word
u8 PS_GenChar(u8 BufferID)
{
	u16 temp;
	u8 ensure;
	u8 *data;
	SendHead();
	SendAddr();
	SendFlag(0x01); // Command package identification 命令包标识
	SendLength(0x04);
	Sendcmd(0x02);
	MYUSART_SendData(BufferID);
	temp = 0x01 + 0x04 + 0x02 + BufferID;
	SendCheck(temp);
	data = JudgeStr(2000);
	if (data)
		ensure = data[9];
	else
		ensure = 0xff;
	return ensure;
}

// 精确比对两枚指纹特征 PS_Match
// 功能:精确比对CharBuffer1 与CharBuffer2 中的特征文件
// 模块返回确认字
//Accurately compare two fingerprint features PS_ Match
//Function: Accurately compare feature files in CharBuffer1 and CharBuffer2
//Module return confirmation word
u8 PS_Match(void)
{
	u16 temp;
	u8 ensure;
	u8 *data;
	SendHead();
	SendAddr();
	SendFlag(0x01); // Command package identification 命令包标识
	SendLength(0x03);
	Sendcmd(0x03);
	temp = 0x01 + 0x03 + 0x03;
	SendCheck(temp);
	data = JudgeStr(2000);
	if (data)
		ensure = data[9];
	else
		ensure = 0xff;
	return ensure;
}

// 搜索指纹 PS_Search
// 功能:以CharBuffer1或CharBuffer2中的特征文件搜索整个或部分指纹库.若搜索到，则返回页码。
// 参数:  BufferID @ref CharBuffer1	CharBuffer2
// 说明:  模块返回确认字，页码（相配指纹模板）
//Search fingerprint PS_ Search
//Function: Search the entire or partial fingerprint library based on the feature files in CharBuffer1 or CharBuffer2. If found, return the page number.
//Parameter: BufferID @ ref CharBuffer1 CharBuffer2
//Description: Module returns confirmation word, page number (matching fingerprint template)
u8 PS_Search(u8 BufferID, u16 StartPage, u16 PageNum, SearchResult *p)
{
	u16 temp;
	u8 ensure;
	u8 *data;
	SendHead();
	SendAddr();
	SendFlag(0x01); //Command package identification 命令包标识
	SendLength(0x08);
	Sendcmd(0x04);
	MYUSART_SendData(BufferID);
	MYUSART_SendData(StartPage >> 8);
	MYUSART_SendData(StartPage);
	MYUSART_SendData(PageNum >> 8);
	MYUSART_SendData(PageNum);
	temp = 0x01 + 0x08 + 0x04 + BufferID + (StartPage >> 8) + (u8)StartPage + (PageNum >> 8) + (u8)PageNum;
	SendCheck(temp);
	data = JudgeStr(2000);
	if (data)
	{
		ensure = data[9];
		p->pageID = (data[10] << 8) + data[11];
		p->mathscore = (data[12] << 8) + data[13];
	}
	else
		ensure = 0xff;
	return ensure;
}

// 合并特征（生成模板）PS_RegModel
// 功能:将CharBuffer1与CharBuffer2中的特征文件合并生成 模板,结果存于CharBuffer1与CharBuffer2
// 说明:  模块返回确认字
//Merge Features (Generate Template) PS_ RegModel
//Function: Merge feature files from CharBuffer1 and CharBuffer2 to generate a template, and store the results in CharBuffer1 and CharBuffer2
//Description: Module returns confirmation word
u8 PS_RegModel(void)
{
	u16 temp;
	u8 ensure;
	u8 *data;
	SendHead();
	SendAddr();
	SendFlag(0x01);
	SendLength(0x03);
	Sendcmd(0x05);
	temp = 0x01 + 0x03 + 0x05;
	SendCheck(temp);
	data = JudgeStr(2000);
	if (data)
		ensure = data[9];
	else
		ensure = 0xff;
	return ensure;
}

// 储存模板 PS_StoreChar
// 功能:将 CharBuffer1 或 CharBuffer2 中的模板文件存到 PageID 号flash数据库位置。
// 参数:  BufferID @ref charBuffer1:0x01	charBuffer1:0x02
//        PageID（指纹库位置号）
// 说明:  模块返回确认字
//Storage template PS_ StoreChar
//Function: Save the template files in CharBuffer1 or CharBuffer2 to the PageID number flash database location.
//Parameter: BufferID @ ref charBuffer1: 0x01 charBuffer1: 0x02
//PageID (fingerprint library location number)
//Description: Module returns confirmation word
u8 PS_StoreChar(u8 BufferID, u16 PageID)
{
	u16 temp;
	u8 ensure;
	u8 *data;
	SendHead();
	SendAddr();
	SendFlag(0x01);
	SendLength(0x06);
	Sendcmd(0x06);
	MYUSART_SendData(BufferID);
	MYUSART_SendData(PageID >> 8);
	MYUSART_SendData(PageID);
	temp = 0x01 + 0x06 + 0x06 + BufferID + (PageID >> 8) + (u8)PageID;
	SendCheck(temp);
	data = JudgeStr(2000);
	if (data)
		ensure = data[9];
	else
		ensure = 0xff;
	return ensure;
}

// 删除模板 PS_DeletChar
// 功能:  删除flash数据库中指定ID号开始的N个指纹模板
// 参数:  PageID(指纹库模板号)，N删除的模板个数。
// 说明:  模块返回确认字
//Delete Template PS_ DeletChar
//Function: Delete N fingerprint templates starting from the specified ID number in the flash database
//Parameters: PageID (fingerprint library template number), N Number of templates deleted.
//Description: Module returns confirmation word
u8 PS_DeletChar(u16 PageID, u16 N)
{
	u16 temp;
	u8 ensure;
	u8 *data;
	SendHead();
	SendAddr();
	SendFlag(0x01);
	SendLength(0x07);
	Sendcmd(0x0C);
	MYUSART_SendData(PageID >> 8);
	MYUSART_SendData(PageID);
	MYUSART_SendData(N >> 8);
	MYUSART_SendData(N);
	temp = 0x01 + 0x07 + 0x0C + (PageID >> 8) + (u8)PageID + (N >> 8) + (u8)N;
	SendCheck(temp);
	data = JudgeStr(2000);
	if (data)
		ensure = data[9];
	else
		ensure = 0xff;
	return ensure;
}

// 清空指纹库 PS_Empty
// 功能:  删除flash数据库中所有指纹模板
// 参数:  无
// 说明:  模块返回确认字
//Clear fingerprint library PS_ Empty
//Function: Delete all fingerprint templates in the flash database
//Parameter: None
//Description: Module returns confirmation word
u8 PS_Empty(void)
{
	u16 temp;
	u8 ensure;
	u8 *data;
	SendHead();
	SendAddr();
	SendFlag(0x01);
	SendLength(0x03);
	Sendcmd(0x0D);
	temp = 0x01 + 0x03 + 0x0D;
	SendCheck(temp);
	data = JudgeStr(2000);
	if (data)
		ensure = data[9];
	else
		ensure = 0xff;
	return ensure;
}

// 写系统寄存器 PS_WriteReg
// 功能:  写模块寄存器
// 参数:  寄存器序号RegNum:4\5\6
// 说明:  模块返回确认字
//Write system register PS_ WriteReg
//Function: Write module registers
//Parameter: Register sequence number RegNum: 4  5  6
//Description: Module returns confirmation word
u8 PS_WriteReg(u8 RegNum, u8 DATA)
{
	u16 temp;
	u8 ensure;
	u8 *data;
	SendHead();
	SendAddr();
	SendFlag(0x01);
	SendLength(0x05);
	Sendcmd(0x0E);
	MYUSART_SendData(RegNum);
	MYUSART_SendData(DATA);
	temp = RegNum + DATA + 0x01 + 0x05 + 0x0E;
	SendCheck(temp);
	data = JudgeStr(2000);
	if (data)
		ensure = data[9];
	else
		ensure = 0xff;
	if (ensure == 0)
		printf("\r\nSuccessfully set parameters!");
	else
		printf("\r\n%s", EnsureMessage(ensure));
	return ensure;
}

// 读系统基本参数 PS_ReadSysPara
// 功能:  读取模块的基本参数（波特率，包大小等)
// 参数:  无
// 说明:  模块返回确认字 + 基本参数（16bytes）
//Read system basic parameters PS_ ReadSysPara
//Function: Read the basic parameters of the module (baud rate, packet size, etc.)
//Parameter: None
//Description: Module returns confirmation word+basic parameters (16bytes)
u8 PS_ReadSysPara(SysPara *p)
{
	u16 temp;
	u8 ensure;
	u8 *data;
	SendHead();
	SendAddr();
	SendFlag(0x01);
	SendLength(0x03);
	Sendcmd(0x0F);
	temp = 0x01 + 0x03 + 0x0F;
	SendCheck(temp);
	data = JudgeStr(1000);
	if (data)
	{
		ensure = data[9];
		p->PS_max = (data[14] << 8) + data[15];
		p->PS_level = data[17];
		p->PS_addr = (data[18] << 24) + (data[19] << 16) + (data[20] << 8) + data[21];
		p->PS_size = data[23];
		p->PS_N = data[25];
	}
	else
		ensure = 0xff;
	if (ensure == 0x00)
	{
		printf("\r\nMaximum total number of fingerprints=%d", p->PS_max);
		printf("\r\nComparison level=%d", p->PS_level);
		printf("\r\naddr=%lx", p->PS_addr);
		printf("\r\nbaudrate=%d", p->PS_N * 9600);
	}
	else
		printf("\r\n%s", EnsureMessage(ensure));
	return ensure;
}

// 设置模块地址 PS_SetAddr
// 功能:  设置模块地址
// 参数:  PS_addr
// 说明:  模块返回确认字
//Set module address PS_ SetAddr
//Function: Set module address
//Parameter: PS_ Addr
//Description: Module returns confirmation word
u8 PS_SetAddr(u32 PS_addr)
{
	u16 temp;
	u8 ensure;
	u8 *data;
	SendHead();
	SendAddr();
	SendFlag(0x01); //Command package identification 命令包标识
	SendLength(0x07);
	Sendcmd(0x15);
	MYUSART_SendData(PS_addr >> 24);
	MYUSART_SendData(PS_addr >> 16);
	MYUSART_SendData(PS_addr >> 8);
	MYUSART_SendData(PS_addr);
	temp = 0x01 + 0x07 + 0x15 + (u8)(PS_addr >> 24) + (u8)(PS_addr >> 16) + (u8)(PS_addr >> 8) + (u8)PS_addr;
	SendCheck(temp);
	AS608Addr = PS_addr; //After sending the command, change the address 发送完指令，更换地址
	data = JudgeStr(2000);
	if (data)
		ensure = data[9];
	else
	{
		ensure = 0xff;
	}
	AS608Addr = PS_addr;
	if (ensure == 0x00)
		printf("\r\nSuccessfully set address!");
	else
		printf("\r\n%s", EnsureMessage(ensure));
	return ensure;
}

// 功能： 模块内部为用户开辟了256bytes的FLASH空间用于存用户记事本,
//	该记事本逻辑上被分成 16 个页。
// 参数:  NotePageNum(0~15),Byte32(要写入内容，32个字节)
// 说明:  模块返回确认字
//Function: The module internally opens up 256bytes of FLASH space for users to store their notebooks,
//The notebook is logically divided into 16 pages.
//Parameters: NotePageNum (0-15), Byte32 (32 bytes to write content)
//Description: Module returns confirmation word
u8 PS_WriteNotepad(u8 NotePageNum, u8 *Byte32)
{
	u16 temp;
	u8 ensure, i;
	u8 *data;
	SendHead();
	SendAddr();
	SendFlag(0x01);
	SendLength(36);
	Sendcmd(0x18);
	MYUSART_SendData(NotePageNum);
	for (i = 0; i < 32; i++)
	{
		MYUSART_SendData(Byte32[i]);
		temp += Byte32[i];
	}
	temp = 0x01 + 36 + 0x18 + NotePageNum + temp;
	SendCheck(temp);
	data = JudgeStr(2000);
	if (data)
		ensure = data[9];
	else
		ensure = 0xff;
	return ensure;
}

// 读记事PS_ReadNotepad
// 功能：  读取FLASH用户区的128bytes数据
// 参数:  NotePageNum(0~15)
// 说明:  模块返回确认字+用户信息
//Reading Notes PS_ ReadNotepad
//Function: Read 128bytes of data from FLASH user area
//Parameter: NotePageNum (0-15)
//Description: Module returns confirmation word+user information
u8 PS_ReadNotepad(u8 NotePageNum, u8 *Byte32)
{
	u16 temp;
	u8 ensure, i;
	u8 *data;
	SendHead();
	SendAddr();
	SendFlag(0x01);
	SendLength(0x04);
	Sendcmd(0x19);
	MYUSART_SendData(NotePageNum);
	temp = 0x01 + 0x04 + 0x19 + NotePageNum;
	SendCheck(temp);
	data = JudgeStr(2000);
	if (data)
	{
		ensure = data[9];
		for (i = 0; i < 32; i++)
		{
			Byte32[i] = data[10 + i];
		}
	}
	else
		ensure = 0xff;
	return ensure;
}

// 高速搜索PS_HighSpeedSearch
// 功能：以 CharBuffer1或CharBuffer2中的特征文件高速搜索整个或部分指纹库。
//		  若搜索到，则返回页码,该指令对于的确存在于指纹库中 ，且登录时质量
//		  很好的指纹，会很快给出搜索结果。
// 参数:  BufferID， StartPage(起始页)，PageNum（页数）
// 说明:  模块返回确认字+页码（相配指纹模板）
//High speed search PS_ HighSpeedSearch
//Function: High speed search of the entire or partial fingerprint library using feature files from CharBuffer1 or CharBuffer2.
//If it is found, the page number will be returned. This instruction is valid if it is stored in the fingerprint database and the quality at login
//A good fingerprint will quickly provide search results.
//Parameters: BufferID, StartPage, PageNum
//Description: Module returns confirmation word+page number (matching fingerprint template)
u8 PS_HighSpeedSearch(u8 BufferID, u16 StartPage, u16 PageNum, SearchResult *p)
{
	u16 temp;
	u8 ensure;
	u8 *data;
	SendHead();
	SendAddr();
	SendFlag(0x01);
	SendLength(0x08);
	Sendcmd(0x1b);
	MYUSART_SendData(BufferID);
	MYUSART_SendData(StartPage >> 8);
	MYUSART_SendData(StartPage);
	MYUSART_SendData(PageNum >> 8);
	MYUSART_SendData(PageNum);
	temp = 0x01 + 0x08 + 0x1b + BufferID + (StartPage >> 8) + (u8)StartPage + (PageNum >> 8) + (u8)PageNum;
	SendCheck(temp);
	data = JudgeStr(2000);
	if (data)
	{
		ensure = data[9];
		p->pageID = (data[10] << 8) + data[11];
		p->mathscore = (data[12] << 8) + data[13];
	}
	else
		ensure = 0xff;
	return ensure;
}

// 读有效模板个数 PS_ValidTempleteNum
// 功能：读有效模板个数
// 参数: 无
// 说明: 模块返回确认字+有效模板个数ValidN
//Read the number of valid templates PS_ ValidTempleteNum
//Function: Read the number of valid templates
//Parameter: None
//Description: Module returns confirmation word+number of valid templates ValidN
u8 PS_ValidTempleteNum(u16 *ValidN)
{
	u16 temp;
	u8 ensure;
	u8 *data;
	SendHead();
	SendAddr();
	SendFlag(0x01);
	SendLength(0x03);
	Sendcmd(0x1d);
	temp = 0x01 + 0x03 + 0x1d;
	SendCheck(temp);
	data = JudgeStr(2000);
	if (data)
	{
		ensure = data[9];
		*ValidN = (data[10] << 8) + data[11];
	}
	else
		ensure = 0xff;

	if (ensure == 0x00)
	{
		printf("\r\nTotal number of valid fingerprints=%d\r\n", (data[10] << 8) + data[11]);
	}
	else
		printf("\r\n%s", EnsureMessage(ensure));
	return ensure;
}

// 与AS608握手 PS_HandShake
// 参数: PS_Addr地址指针
// 说明: 模块返新地址（正确地址）
//Shake Hands with AS608 PS_ HandShake
//Parameter: PS_ Addr address pointer
//Description: Module return address (correct address)
u8 PS_HandShake(u32 *PS_Addr)
{
	SendHead();
	SendAddr();
	MYUSART_SendData(0X01);
	MYUSART_SendData(0X00);
	MYUSART_SendData(0X00);
	delay_ms(200);
	if (UART4_RX_STA & 0X8000) // Received data 接收到数据
	{
		if ( // Determine if it is a response packet returned by the module 判断是不是模块返回的应答包
			UART4_RX_BUF[0] == 0XEF && UART4_RX_BUF[1] == 0X01 && UART4_RX_BUF[6] == 0X07)
		{
			*PS_Addr = (UART4_RX_BUF[2] << 24) + (UART4_RX_BUF[3] << 16) + (UART4_RX_BUF[4] << 8) + (UART4_RX_BUF[5]);
			UART4_RX_STA = 0;
			return 0;
		}
		UART4_RX_STA = 0;
	}
	return 1;
}

// 模块应答包确认码信息解析
// 功能：解析确认码错误信息返回信息
// 参数: ensure
//Analysis of module response package confirmation code information
//Function: Parse confirmation code error information and return information
//Parameter: ensure
const char *EnsureMessage(u8 ensure)
{
	const char *p;
	switch (ensure)
	{
	case 0x00:
		p = "OK\r\n";
		break;
	case 0x01:
		p = "Packet reception error!\r\n";
		break;
	case 0x02:
		p = "There are no fingers on the sensor!\r\n";
		break;
	case 0x03:
		p = "Failed to input fingerprint image\r\n";
		break;
	case 0x04:
		p = "Failed to input fingerprint image.\r\n";
		break;
	case 0x05:
		p = "Error:The fingerprint image is too wet and sticky.\r\n";
		break;
	case 0x06:
		p = "Error:Fingerprint image too messy\r\n";
		break;
	case 0x07:
		p = "Error:Fingerprint feature points are too few (or too small in area)\r\n";
		break;
	case 0x08:
		p = "Fingerprint mismatch\r\n";
		break;
	case 0x09:
		p = "No fingerprints found\r\n";
		break;
	case 0x0a:
		p = "Feature merge failed\r\n";
		break;
	case 0x0b:
		p = "Exceeding the valid range of fingerprint database\r\n";
	case 0x10:
		p = "Failed to delete template\r\n";
		break;
	case 0x11:
		p = "Failed to clear fingerprint library\r\n";
		break;
	case 0x15:
		p = "Error:There is no valid original image in the buffer zone\r\n";
		break;
	case 0x18:
		p = "Error reading and writing FLASH\r\n";
		break;
	case 0x19:
		p = "Undefined error\r\n";
		break;
	case 0x1a:
		p = "Invalid register number\r\n";
		break;
	case 0x1b:
		p = "Register setting content error\r\n";
		break;
	case 0x1c:
		p = "Notepad page number specified incorrectly\r\n";
		break;
	case 0x1f:
		p = "Fingerprint library full\r\n";
		break;
	case 0x20:
		p = "Address Error\r\n";
		break;
	default:
		p = "Module returned confirmation code error\r\n";
		break;
	}
	return p;
}
