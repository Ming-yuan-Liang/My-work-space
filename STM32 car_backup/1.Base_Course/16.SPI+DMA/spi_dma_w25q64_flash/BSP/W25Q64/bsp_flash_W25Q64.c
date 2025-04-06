#include "bsp_flash_W25Q64.h"

u16 SPI_FLASH_TYPE = W25Q64; // 默认就是25Q64

/*
 * flash初始化
 *
 * flash initialization
 * */
void W25Q64_Init(void)
{


	SPI_FLASH_TYPE = Spi_Flash_ReadID();// 读取FLASH ID. Read FLASH ID.
}

/**********************
spi协议发送1个字节函数
uint8_t BYTE ：你需要发送的字节数据
spi protocol sends 1 byte function
uint8_t BYTE: the byte data you need to send
*********************/
uint8_t SPI_Read_Write_Byte(uint8_t BYTE)
{
	uint8_t SNED_BYTE = BYTE;
	uint8_t READ_BYTE = 0;

#if DMA_SPI_USE
	SPI_DMA_Stop2();
	HAL_SPI_TransmitReceive_DMA(&hspi2, &SNED_BYTE, &READ_BYTE, 1);
	SPI_DMA_Stop2();
#else
	HAL_SPI_TransmitReceive(&hspi2, &SNED_BYTE, &READ_BYTE, 1, 1000);
#endif

	return READ_BYTE;
}




// 读取SPI_FLASH的状态寄存器
// BIT7  6   5   4   3   2   1   0
// SPR   RV  TB BP2 BP1 BP0 WEL BUSY
// SPR:默认0,状态寄存器保护位,配合WP使用
// TB,BP2,BP1,BP0:FLASH区域写保护设置
// WEL:写使能锁定
// BUSY:忙标记位(1,忙;0,空闲)
// 默认:0x00
//Read the status register of SPI_FLASH
// BIT7 6 5 4 3 2 1 0
// SPR RV TB BP2 BP1 BP0 WEL BUSY
// SPR: Default 0, status register protection bit, used with WP
// TB, BP2, BP1, BP0: FLASH area write protection settings
// WEL: Write enable lock
// BUSY: busy flag bit (1, busy; 0, idle)
//Default:0x00
u8 Spi_Flash_Read_SR(void)
{
	u8 byte = 0;
	CS_LOW;									 // 使能器件 enable device
	SPI_Read_Write_Byte(W25X_ReadStatusReg); // 发送读取状态寄存器命令 Send read status register command
	byte = SPI_Read_Write_Byte(0Xff);		 // 读取一个字节 Read a byte
	CS_HIGH;								 // 取消片选 Cancel movie selection
	return byte;
}
// 写SPI_FLASH状态寄存器
// 只有SPR,TB,BP2,BP1,BP0(bit 7,5,4,3,2)可以写!!!
//Write SPI_FLASH status register
// Only SPR, TB, BP2, BP1, BP0 (bit 7,5,4,3,2) can be written!!!
void Spi_Flash_Write_SR(u8 sr)
{
	CS_LOW;									  // 使能器件 enable device
	SPI_Read_Write_Byte(W25X_WriteStatusReg); // 发送写取状态寄存器命令 Send write status register command
	SPI_Read_Write_Byte(sr);				  // 写入一个字节 write a byte
	CS_HIGH;								  // 取消片选 Cancel movie selection
}
// SPI_FLASH写使能
// 将WEL置位
// SPI_FLASH write enable
//Set WEL
void Spi_Flash_Write_Enable(void)
{
	CS_LOW;								   // 使能器件 enable device
	SPI_Read_Write_Byte(W25X_WriteEnable); // 发送写使能 Send write enable
	CS_HIGH;							   // 取消片选 Cancel movie selection
}
// SPI_FLASH写禁止
// 将WEL清零
// SPI_FLASH write disabled
// Clear WEL to zero
void Spi_Flash_Write_Disable(void)
{
	CS_LOW;									// 使能器件 enable device
	SPI_Read_Write_Byte(W25X_WriteDisable); // 发送写禁止指令 Send write inhibit command
	CS_HIGH;								// 取消片选 Cancel movie selection
}
// 读取芯片ID W25X16的ID:0XEF16
//Read chip ID W25X16 ID: 0XEF16
u16 Spi_Flash_ReadID(void)
{
	u16 Temp = 0;
	CS_LOW;
	SPI_Read_Write_Byte(0x90); // 发送读取ID命令 Send read ID command
	SPI_Read_Write_Byte(0x00);
	SPI_Read_Write_Byte(0x00);
	SPI_Read_Write_Byte(0x00);
	Temp |= SPI_Read_Write_Byte(0xFF) << 8;
	Temp |= SPI_Read_Write_Byte(0xFF);
	CS_HIGH;
	return Temp;
}
// 读取SPI FLASH
// 在指定地址开始读取指定长度的数据
// pBuffer:数据存储区
// ReadAddr:开始读取的地址(24bit)
// NumByteToRead:要读取的字节数(最大65535)
//Read SPI FLASH
//Start reading data of the specified length at the specified address
// pBuffer: data storage area
// ReadAddr: address to start reading (24bit)
// NumByteToRead: Number of bytes to read (maximum 65535)
void Spi_Flash_Read(u8 *pBuffer, u32 ReadAddr, u16 NumByteToRead)
{
	u16 i;
	CS_LOW;										 // 使能器件 enable device
	SPI_Read_Write_Byte(W25X_ReadData);			 // 发送读取命令  Send read command
	SPI_Read_Write_Byte((u8)((ReadAddr) >> 16)); // 发送24bit地址 Send 24bit address
	SPI_Read_Write_Byte((u8)((ReadAddr) >> 8));
	SPI_Read_Write_Byte((u8)ReadAddr);
	for (i = 0; i < NumByteToRead; i++)
	{
		pBuffer[i] = SPI_Read_Write_Byte(0XFF); // 循环读数 Cycle reading
	}
	CS_HIGH; // 取消片选 Cancel movie selection
}
// SPI在一页(0~65535)内写入少于256个字节的数据
// 在指定地址开始写入最大256字节的数据
// pBuffer:数据存储区
// WriteAddr:开始写入的地址(24bit)
// NumByteToWrite:要写入的字节数(最大256),该数不应该超过该页的剩余字节数!!!
// SPI writes less than 256 bytes of data in one page (0~65535)
//Start writing data up to 256 bytes at the specified address
// pBuffer: data storage area
// WriteAddr: address to start writing (24bit)
// NumByteToWrite: The number of bytes to be written (maximum 256), this number should not exceed the remaining bytes of the page!!!
void Spi_Flash_Write_Page(u8 *pBuffer, u32 WriteAddr, u16 NumByteToWrite)
{
	Spi_Flash_Write_Enable();					  // SET WEL
	CS_LOW;										  // 使能器件 enable device
	SPI_Read_Write_Byte(W25X_PageProgram);		  // 发送写页命令 Send page write command
	SPI_Read_Write_Byte((u8)((WriteAddr) >> 16)); // 发送24bit地址 Send 24bit address
	SPI_Read_Write_Byte((u8)((WriteAddr) >> 8));
	SPI_Read_Write_Byte((u8)WriteAddr);
#if	DMA_SPI_USE== 1
	SPI_Write_DMA(pBuffer,NumByteToWrite);
	SPI_DMA_Stop();
	CS_HIGH;
#else
	for (u16 i = 0; i < NumByteToWrite; i++)
		SPI_Read_Write_Byte(pBuffer[i]); // 循环写数 Loop write number
	CS_HIGH;							 // 取消片选 Cancel movie selection
#endif
	Spi_Flash_Wait_Busy();				 // 等待写入结束 Wait for writing to complete
}
// 无检验写SPI FLASH
// 必须确保所写的地址范围内的数据全部为0XFF,否则在非0XFF处写入的数据将失败!
// 具有自动换页功能
// 在指定地址开始写入指定长度的数据,但是要确保地址不越界!
// pBuffer:数据存储区
// WriteAddr:开始写入的地址(24bit)
// NumByteToWrite:要写入的字节数(最大65535)
// CHECK OK
//Write SPI FLASH without verification
// It must be ensured that all data within the written address range are 0XFF, otherwise data written at non-0XFF locations will fail!
//Has automatic page changing function
// Start writing data of the specified length at the specified address, but make sure the address does not cross the boundary!
// pBuffer: data storage area
// WriteAddr: address to start writing (24bit)
// NumByteToWrite: Number of bytes to be written (maximum 65535)
// CHECK OK
void Spi_Flash_Write_NoCheck(u8 *pBuffer, u32 WriteAddr, u16 NumByteToWrite)
{
	u16 pageremain;
	pageremain = 256 - WriteAddr % 256; // 单页剩余的字节数 Number of bytes remaining in a single page
	if (NumByteToWrite <= pageremain)
		pageremain = NumByteToWrite; // 不大于256个字节 No more than 256 bytes
	while (1)
	{
		Spi_Flash_Write_Page(pBuffer, WriteAddr, pageremain);
		// 写入结束了 Writing is over
		if (NumByteToWrite == pageremain)
			break;
		else // NumByteToWrite>pageremain
		{
			pBuffer += pageremain;
			WriteAddr += pageremain;

			NumByteToWrite -= pageremain; // 减去已经写入了的字节数 Subtract the number of bytes that have been written
			if (NumByteToWrite > 256)
				pageremain = 256; // 一次可以写入256个字节 Can write 256 bytes at a time
			else
				pageremain = NumByteToWrite; // 不够256个字节了 Not enough 256 bytes
		}
	};
}
// 写SPI FLASH
// 在指定地址开始写入指定长度的数据
// 该函数带擦除操作!
// pBuffer:数据存储区
// WriteAddr:开始写入的地址(24bit)
// NumByteToWrite:要写入的字节数(最大65535)
//Write SPI FLASH
//Start writing data of the specified length at the specified address
// This function has an erase operation!
// pBuffer: data storage area
// WriteAddr: address to start writing (24bit)
// NumByteToWrite: Number of bytes to be written (maximum 65535)
u8 SPI_FLASH_BUF[4096];
void Spi_Flash_Write(u8 *pBuffer, u32 WriteAddr, u16 NumByteToWrite)
{
	u32 secpos;
	u16 secoff;
	u16 secremain;
	u16 i;

	secpos = WriteAddr / 4096; // 扇区地址 0~511 for w25x16 Sector address 0~511 for w25x16
	secoff = WriteAddr % 4096; // 在扇区内的偏移 Offset within sector
	secremain = 4096 - secoff; // 扇区剩余空间大小 Sector remaining space size

	// 不大于4096个字节 No larger than 4096 bytes
	if (NumByteToWrite <= secremain)
		secremain = NumByteToWrite;
	while (1)
	{
		// 读出整个扇区的内容 Read the contents of the entire sector
		Spi_Flash_Read(SPI_FLASH_BUF, secpos * 4096, 4096);
		for (i = 0; i < secremain; i++) // 校验数据 Check data
		{
			// 需要擦除 Need to erase
			if (SPI_FLASH_BUF[secoff + i] != 0XFF)
				break;
		}
		if (i < secremain) // 需要擦除 Need to erase
		{
			Spi_Flash_Erase_Sector(secpos); // 擦除这个扇区 Erase this sector
			for (i = 0; i < secremain; i++) // 复制 copy
			{
				SPI_FLASH_BUF[i + secoff] = pBuffer[i];
			}
			// 写入整个扇区 Write entire sector
			Spi_Flash_Write_NoCheck(SPI_FLASH_BUF, secpos * 4096, 4096);
		}
		else // 写已经擦除了的,直接写入扇区剩余区间. To write what has been erased, write directly to the remaining area of the sector.
			Spi_Flash_Write_NoCheck(pBuffer, WriteAddr, secremain);
		if (NumByteToWrite == secremain)
			break; // 写入结束了 Writing is over
		else	   // 写入未结束 Writing is not completed
		{
			secpos++;	// 扇区地址增1 Increase sector address by 1
			secoff = 0; // 偏移位置为0 Offset position is 0

			pBuffer += secremain;		 // 指针偏移 pointer offset
			WriteAddr += secremain;		 // 写地址偏移 write address offset
			NumByteToWrite -= secremain; // 字节数递减 Decrementing the number of bytes
			if (NumByteToWrite > 4096)
				secremain = 4096; // 下一个扇区还是写不完 The next sector still cannot be written.
			else
				secremain = NumByteToWrite; // 下一个扇区可以写完了 The next sector can be written
		}
	};
}

// 擦除整个芯片
// 整片擦除时间:
// W25X16:25s
// W25X32:40s
// W25X64:40s
// 等待时间超长...
// Erase the entire chip
//Full chip erase time:
// W25X16:25s
// W25X32:40s
// W25X64:40s
// The waiting time is too long...
void Spi_Flash_Erase_Chip(void)
{
	Spi_Flash_Write_Enable(); // SET WEL
	Spi_Flash_Wait_Busy();
	CS_LOW;								 // 使能器件 enable device
	SPI_Read_Write_Byte(W25X_ChipErase); // 发送片擦除命令 Send chip erase command
	CS_HIGH;							 // 取消片选 Cancel movie selection
	Spi_Flash_Wait_Busy();				 // 等待芯片擦除结束 Wait for chip erase to complete
}
// 擦除一个扇区
// Dst_Addr:扇区地址 0~511(0-2047) for w25x16
// 擦除一个山区的最少时间:150ms
// Erase a sector
// Dst_Addr: sector address 0~511(0-2047) for w25x16
// Minimum time to erase a mountainous area: 150ms
void Spi_Flash_Erase_Sector(u32 Dst_Addr)
{
	Dst_Addr *= 4096;
	Spi_Flash_Write_Enable(); // SET WEL
	Spi_Flash_Wait_Busy();
	CS_LOW;										 // 使能器件 enable device
	SPI_Read_Write_Byte(W25X_SectorErase);		 // 发送扇区擦除指令 Send sector erase command
	SPI_Read_Write_Byte((u8)((Dst_Addr) >> 16)); // 发送24bit地址 Send 24bit address
	SPI_Read_Write_Byte((u8)((Dst_Addr) >> 8));
	SPI_Read_Write_Byte((u8)Dst_Addr);
	CS_HIGH;			   // 取消片选 Cancel movie selection
	Spi_Flash_Wait_Busy(); // 等待擦除完成 Wait for erasure to complete
}

// 擦除一个块
// Dst_Addr:块地址 0~128
// 擦除一个山区的最少时间:150ms
// Erase a block
// Dst_Addr: block address 0~128
// Minimum time to erase a mountainous area: 150ms
void Spi_Flash_BlockErase_Sector(u32 Dst_Addr)
{
	Dst_Addr *= 65536;
	Spi_Flash_Write_Enable(); // SET WEL
	Spi_Flash_Wait_Busy();
	CS_LOW;										 // 使能器件 enable device
	SPI_Read_Write_Byte(W25X_BlockErase);		 // 发送块擦除指令 Send block erase command
	SPI_Read_Write_Byte((u8)((Dst_Addr) >> 16)); // 发送24bit地址 Send 24bit address
	SPI_Read_Write_Byte((u8)((Dst_Addr) >> 8));
	SPI_Read_Write_Byte((u8)Dst_Addr);
	CS_HIGH;			   // 取消片选 Cancel movie selection
	Spi_Flash_Wait_Busy(); // 等待擦除完成 Wait for erasure to complete
}

// 等待空闲
//wait for idle
void Spi_Flash_Wait_Busy(void)
{
	while ((Spi_Flash_Read_SR() & 0x01) == 0x01)
		; // 等待BUSY位清空 Wait for the BUSY bit to clear
}
// 进入掉电模式
//Enter power-down mode
void Spi_Flash_Power_Down(void)
{
	CS_LOW;								 // 使能器件 enable device
	SPI_Read_Write_Byte(W25X_PowerDown); // 发送掉电命令 Send power down command
	CS_HIGH;							 // 取消片选 Cancel movie selection
	HAL_Delay(1);
}
// 唤醒
// wake up
void Spi_Flash_WAKEUP(void)
{
	CS_LOW;										// 使能器件 enable device
	SPI_Read_Write_Byte(W25X_ReleasePowerDown); // send W25X_PowerDown command 0xAB
	CS_HIGH;									// 取消片选 Cancel movie selection
	HAL_Delay(1);
}
