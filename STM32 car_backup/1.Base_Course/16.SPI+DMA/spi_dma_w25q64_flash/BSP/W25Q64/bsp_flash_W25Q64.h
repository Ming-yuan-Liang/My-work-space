#ifndef _BSP_FLASH_W25Q64_H_
#define _BSP_FLASH_W25Q64_H_

/**
本程序用于w25q64,其他内存flash通用
有些地方稍做修改即可
w25q64有64MB内存
一页256个字节
4096字节也就是（4KB）为一个扇区
16个扇区为一块（65536字节）
一共128块（8388608字节）
**/

#include <bsp_spi_dma.h>
#include "main.h"
#include "stdint.h"
#include "dma.h"
#include "spi.h"

#define W25Q80 	0XEF13
#define W25Q16 	0XEF14
#define W25Q32 	0XEF15
#define W25Q64 	0XEF16 //ID号

#define u8 uint8_t
#define u16 uint16_t
#define u32 uint32_t

extern u16 SPI_FLASH_TYPE;		//定义我们使用的flash芯片型号
extern u8 SPI_FLASH_BUF[4096];

//0：不使用DMA  1：使用DMA
#define DMA_SPI_USE 1

//W25X64读写
#define FLASH_ID 0XEF16

//指令表
#define W25X_WriteEnable		0x06  //开启写使能
#define W25X_WriteDisable		0x04  //关闭写使能
#define W25X_ReadStatusReg		0x05  //读状态寄存器
#define W25X_WriteStatusReg		0x01
#define W25X_ReadData			0x03  //读命令
#define W25X_FastReadData		0x0B
#define W25X_FastReadDual		0x3B
#define W25X_PageProgram		0x02  //写命令
#define W25X_BlockErase			0xD8  //块擦除64kB
#define W25X_SectorErase		0x20  //扇区擦除4kB
#define W25X_ChipErase			0xC7  //全部擦除
#define W25X_PowerDown			0xB9  //省电模式
#define W25X_ReleasePowerDown	0xAB  //唤醒模式
#define W25X_DeviceID			0xAB
#define W25X_ManufactDeviceID	0x90  //读取厂商id
#define W25X_JedecDeviceID		0x9F


void W25Q64_Init(void);


u16  Spi_Flash_ReadID(void);  	    								//读取FLASH ID
u8	 Spi_Flash_Read_SR(void);        								//读取状态寄存器
void Spi_Flash_Write_SR(u8 sr);  									//写状态寄存器
void Spi_Flash_Write_Enable(void);  								//写使能
void Spi_Flash_Write_Disable(void);									//写保护
void Spi_Flash_Read(u8* pBuffer,u32 ReadAddr,u16 NumByteToRead);    //读取flash
void Spi_Flash_Write(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite); //写入flash
void Spi_Flash_Erase_Chip(void);    	  							//整片擦除
void Spi_Flash_Erase_Sector(u32 Dst_Addr);							//扇区擦除
void Spi_Flash_BlockErase_Sector(u32 Dst_Addr);						//块擦除
void Spi_Flash_Wait_Busy(void);           							//等待空闲
void Spi_Flash_Power_Down(void);           							//进入掉电模式
void Spi_Flash_WAKEUP(void);			  							//唤醒

#endif
