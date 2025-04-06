#ifndef __BSP_FINGER_H
#define __BSP_FINGER_H
#include "bsp.h"

#define PS_Sta   HAL_GPIO_ReadPin(Figher_TCH_GPIO_Port, Figher_TCH_Pin)//读指纹模块状态引脚
#define CharBuffer1 0x01
#define CharBuffer2 0x02

typedef struct
{
	u16 pageID;//Fingerprint ID 指纹ID
	u16 mathscore;//Matching score 匹配得分
}SearchResult;

typedef struct
{
	u16 PS_max;//Maximum fingerprint capacity 指纹最大容量
	u8  PS_level;//security level 安全等级
	u32 PS_addr;
	u8  PS_size;//Communication packet size 通讯数据包大小
	u8  PS_N;//Baud rate base N 波特率基数N
}SysPara;

void PS_StaGPIO_Init(void);//Initialize PA6 read status pin 初始化PA6读状态引脚

u8 PS_GetImage(void); //Input image 录入图像

u8 PS_GenChar(u8 BufferID);//Generate Features 生成特征

u8 PS_Match(void);//Accurately compare the features of two fingerprints 精确比对两枚指纹特征

u8 PS_Search(u8 BufferID,u16 StartPage,u16 PageNum,SearchResult *p);//Search fingerprint 搜索指纹

u8 PS_RegModel(void);//Merge Features (Generate Template) 合并特征（生成模板）

u8 PS_StoreChar(u8 BufferID,u16 PageID);//Storage Template 储存模板

u8 PS_DeletChar(u16 PageID,u16 N);//Delete Template 删除模板

u8 PS_Empty(void);//Clear fingerprint library 清空指纹库

u8 PS_WriteReg(u8 RegNum,u8 DATA);//Write system register 写系统寄存器

u8 PS_ReadSysPara(SysPara *p); //读系统基本参数

u8 PS_SetAddr(u32 addr);  //Read system basic parameters 设置模块地址

u8 PS_WriteNotepad(u8 NotePageNum,u8 *content);//Write a notebook 写记事本

u8 PS_ReadNotepad(u8 NotePageNum,u8 *note);//Reading Chronicles 读记事

u8 PS_HighSpeedSearch(u8 BufferID,u16 StartPage,u16 PageNum,SearchResult *p);//High speed search 高速搜索

u8 PS_ValidTempleteNum(u16 *ValidN);//Number of valid templates read 读有效模板个数

u8 PS_HandShake(u32 *PS_Addr); //Handshake with AS608 module 与AS608模块握手

const char *EnsureMessage(u8 ensure);//Analysis of confirmation code error information 确认码错误信息解析

#endif

