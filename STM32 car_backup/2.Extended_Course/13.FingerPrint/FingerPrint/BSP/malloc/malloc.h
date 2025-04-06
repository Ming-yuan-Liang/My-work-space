#ifndef __MALLOC_H
#define __MALLOC_H
#include "main.h"




#ifndef NULL
#define NULL 0
#endif

//Memory parameter settings内存参数设定.
#define MEM_BLOCK_SIZE			7  	  							//Memory block size is 32 bytes 内存块大小为32字节
#define MEM_MAX_SIZE			8*1024  						//Maximum management memory 35K 最大管理内存 35K
#define MEM_ALLOC_TABLE_SIZE	MEM_MAX_SIZE/MEM_BLOCK_SIZE 	//Memory Table Size 内存表大小
 
		 
//Memory Management Controller 内存管理控制器
struct _m_mallco_dev
{
	void (*init)(void);				//initialization 初始化
	u8 (*perused)(void);		  	//Memory usage rate 内存使用率
	u8 	*membase;					//Memory Pool 内存池
	u16 *memmap; 					//Memory Management Status Table 内存管理状态表
	u8  memrdy; 					//Is memory management ready 内存管理是否就绪
};
extern struct _m_mallco_dev mallco_dev;	//mallco.c

void mymemset(void *s,u8 c,u32 count);	//Set Memory 设置内存
void mymemcpy(void *des,void *src,u32 n);//Copy Memory 复制内存
void mem_init(void);					 //Memory management initialization function (external/internal calls) 内存管理初始化函数(外/内部调用)
u32 mem_malloc(u32 size);		 		//Memory allocation (internal calls) 内存分配(内部调用)
u8 mem_free(u32 offset);		 		//Memory Release (Internal Call) 内存释放(内部调用)
u8 mem_perused(void);					//Memory usage rate (external/internal calls) 得内存使用率(外/内部调用)
////////////////////////////////////////////////////////////////////////////////
//User Call Function 用户调用函数
void myfree(void *ptr);  				//Memory Release (External Call) 内存释放(外部调用)
void *mymalloc(u32 size);				//Memory allocation (external calls) 内存分配(外部调用)
void *myrealloc(void *ptr,u32 size);	//Reassign memory (external call) 重新分配内存(外部调用)
#endif












