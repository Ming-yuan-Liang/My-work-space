#include "bsp_flash.h"

FLASH_ProcessTypeDef p_Flash;
u16 STMFLASH_BUF[STM_SECTOR_SIZE / 2]; // Cache array 缓存数组

/**********************************************************************************
 * 函数功能: 读取指定地址的半字(16位数据)
 * 输入参数: faddr：读地址
 * 返 回 值: 对应数据
 * 说    明：
 *Function function: Read half word (16 bit data) of the specified address
 *Input parameter: faddr: Read address
 *Return value: corresponding data
 *Explanation:
 */
u16 STMFLASH_ReadHalfWord(u32 faddr)
{
	return *(vu16 *)faddr;
}

#if STM32_FLASH_WREN // If writing is enabled 如果使能了写
/**********************************************************************************
 * 函数功能:不检查的写入
 * 输入参数: WriteAddr:起始地址、pBuffer:数据指针、NumToWrite:半字(16位)数
 * 返 回 值: 无
 * 说    明：
 */
void STMFLASH_Write_NoCheck(u32 WriteAddr, u16 *pBuffer, u16 NumToWrite)
{
	u16 i;

	for (i = 0; i < NumToWrite; i++)
	{
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, WriteAddr, pBuffer[i]);
		WriteAddr += 2; // Address increase 2 地址增加2.
	}
}
/**********************************************************************************
 * 函数功能:从指定地址开始写入指定长度的数据
 * 输入参数:WriteAddr:起始地址(此地址必须为2的倍数!!)、pBuffer:数据指针、NumToWrite：半字(16位)数(就是要写入的16位数据的个数.)
 * 返 回 值: 无
 * 说    明：
 * Function function: Write data of a specified length starting from the specified address
 *Input parameters: WriteAddr: Start address (this address must be a multiple of 2!!), pBuffer: Data pointer, NumToWrite: Number of half words (16 bits) (which is the number of 16 bit data to write.)
 *Return value: None
 *Explanation:
 */
void STMFLASH_Write(u32 WriteAddr, u16 *pBuffer, u16 NumToWrite)
{
	u32 secpos;	   // sector address 扇区地址
	u16 secoff;	   // Offset address within the sector (16 bit word calculation) 扇区内偏移地址(16位字计算)
	u16 secremain; // Remaining addresses in the sector (16 bit word calculation)扇区内剩余地址(16位字计算)
	u16 i;
	u32 offaddr; // Address after removing 0X08000000 去掉0X08000000后的地址
	FLASH_EraseInitTypeDef STMflash_Eraseop;
	uint32_t erase_addr; /* Erase error, this value is the address of the sector where the error occurred 擦除错误，这个值为发生错误的扇区地址 */

	if (WriteAddr < STM32_FLASH_BASE || (WriteAddr >= (STM32_FLASH_BASE + 1024 * STM32_FLASH_SIZE)))
		return; // illegal address 非法地址

	HAL_FLASH_Unlock();						  // unlock 解锁
	offaddr = WriteAddr - STM32_FLASH_BASE;	  // Actual offset address 实际偏移地址.
	secpos = offaddr / STM_SECTOR_SIZE;		  // sector address 扇区地址
	secoff = (offaddr % STM_SECTOR_SIZE) / 2; // Offset within the sector (2 bytes as the basic unit) 在扇区内的偏移(2个字节为基本单位.)
	secremain = STM_SECTOR_SIZE / 2 - secoff; // Size of remaining space in the sector 扇区剩余空间大小
	if (NumToWrite <= secremain)
		secremain = NumToWrite; // Not greater than the range of this sector 不大于该扇区范围
	while (1)
	{
		STMFLASH_Read(secpos * STM_SECTOR_SIZE + STM32_FLASH_BASE, STMFLASH_BUF, STM_SECTOR_SIZE / 2); // Read the content of the entire sector 读出整个扇区的内容
		for (i = 0; i < secremain; i++)																   // Verification data 校验数据
		{
			if (STMFLASH_BUF[secoff + i] != 0XFFFF)
				break; // Need to erase 需要擦除
		}
		if (i < secremain) // Need to erase 需要擦除
		{
			STMflash_Eraseop.TypeErase = FLASH_TYPEERASE_PAGES; /* Select Page Erase 选择页擦除 */
			STMflash_Eraseop.Banks = FLASH_BANK_1;
			STMflash_Eraseop.NbPages = 1;
			STMflash_Eraseop.PageAddress = secpos * STM_SECTOR_SIZE + STM32_FLASH_BASE; /* Sector to erase 要擦除的扇区 */
			HAL_FLASHEx_Erase(&STMflash_Eraseop, &erase_addr);

			for (i = 0; i < secremain; i++) // copy 复制
			{
				STMFLASH_BUF[i + secoff] = pBuffer[i];
			}
			STMFLASH_Write_NoCheck(secpos * STM_SECTOR_SIZE + STM32_FLASH_BASE, STMFLASH_BUF, STM_SECTOR_SIZE / 2); // Write entire sector 写入整个扇区
		}
		else
		{
			FLASH_WaitForLastOperation(FLASH_WAITETIME);		   // Waiting for the last operation to complete 等待上次操作完成
			STMFLASH_Write_NoCheck(WriteAddr, pBuffer, secremain); // Write what has been erased and directly write to the remaining interval of the sector 写已经擦除了的,直接写入扇区剩余区间.
		}
		if (NumToWrite == secremain)
			break; // Writing completed 写入结束了
		else	   // The writing is not over 写入未结束
		{
			secpos++;					// Increase sector address by 1 扇区地址增1
			secoff = 0;					// Offset position is 0 偏移位置为0
			pBuffer += secremain;		// Pointer offset 指针偏移
			WriteAddr += secremain * 2; // Write address offset (16 bit data address, requires * 2) 写地址偏移(16位数据地址,需要*2)
			NumToWrite -= secremain;	// Byte (16 bit) decrement 字节(16位)数递减
			if (NumToWrite > (STM_SECTOR_SIZE / 2))
				secremain = STM_SECTOR_SIZE / 2; // I can't finish writing the next sector yet 下一个扇区还是写不完
			else
				secremain = NumToWrite; // The next sector can be completed 下一个扇区可以写完了
		}
	};
	HAL_FLASH_Lock(); // lock 上锁
}
#endif
/**********************************************************************************
 * 函数功能:从指定地址开始读出指定长度的数据
 * 输入参数:ReadAddr:起始地址、pBuffer:数据指针、NumToWrite:半字(16位)数
 * 返 回 值: 无
 * 说    明：
 * Function function: Read data of a specified length from the specified address
 *Input parameters: ReadAddr: starting address, pBuffer: data pointer, NumToWrite: number of half words (16 bits)
 *Return value: None
 *Explanation:
 */
void STMFLASH_Read(u32 ReadAddr, u16 *pBuffer, u16 NumToRead)
{
	u16 i;

	for (i = 0; i < NumToRead; i++)
	{
		pBuffer[i] = STMFLASH_ReadHalfWord(ReadAddr); // Read 2 bytes 读取2个字节.
		ReadAddr += 2;								  // Offset by 2 bytes 偏移2个字节.
	}
}
