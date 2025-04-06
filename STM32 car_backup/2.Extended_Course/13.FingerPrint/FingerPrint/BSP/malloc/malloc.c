#include "malloc.h"	    

//Memory pool (4-byte aligned) 内存池(4字节对齐)
__ALIGNED(4) u8 membase[MEM_MAX_SIZE];			//SRAM memory pool SRAM内存池
//Memory Management Table 内存管理表
u16 memmapbase[MEM_ALLOC_TABLE_SIZE];			//SRAM Memory Pool MAP SRAM内存池MAP
//Memory management parameters 内存管理参数
const u32 memtblsize=MEM_ALLOC_TABLE_SIZE;		//Memory Table Size 内存表大小
const u32 memblksize=MEM_BLOCK_SIZE;			//Memory Chunking Size 内存分块大小
const u32 memsize=MEM_MAX_SIZE;					//Total Memory Size 内存总大小

//Memory Management Controller 内存管理控制器
struct _m_mallco_dev mallco_dev=
{
	mem_init,			//Memory initialization 内存初始化
	mem_perused,		//Memory usage rate s内存使用率
	membase,			//Memory Pool 内存池
	memmapbase,			//Memory Management Status Table 内存管理状态表
	0,  				//Memory management not ready 内存管理未就绪
};

//复制内存
//*des:目的地址
//*src:源地址
//n:需要复制的内存长度(字节为单位)
//Copy Memory
//*Des: Destination address
//*Src: Source Address
//n: The length of memory to be copied (in bytes)
void mymemcpy(void *des,void *src,u32 n)  
{  
    u8 *xdes=des;
	u8 *xsrc=src; 
    while(n--)*xdes++=*xsrc++;  
}  

//设置内存
//*s:内存首地址
//c :要设置的值
//count:需要设置的内存大小(字节为单位)
//Set Memory
//*s: Memory First Address
//C: Value to be set
//Count: The memory size to be set (in bytes)
void mymemset(void *s,u8 c,u32 count)  
{  
    u8 *xs = s;  
    while(count--)*xs++=c;  
}	   
//Memory management initialization 内存管理初始化
void mem_init(void)  
{  
    mymemset(mallco_dev.memmap, 0,memtblsize*2);//Memory status table data reset 内存状态表数据清零
	mymemset(mallco_dev.membase, 0,memsize);	//Clear all data in the memory pool 内存池所有数据清零
	mallco_dev.memrdy=1;						//Memory management initialization OK 内存管理初始化OK
}  
//获取内存使用率
//返回值:使用率(0~100)
//Get Memory Usage
//Return value: Usage rate (0-100)
u8 mem_perused(void)  
{  
    u32 used=0;  
    u32 i;  
    for(i=0;i<memtblsize;i++)  
    {  
        if(mallco_dev.memmap[i])used++; 
    } 
    return (used*100)/(memtblsize);  
}  
//内存分配(内部调用)
//memx:所属内存块
//size:要分配的内存大小(字节)
//返回值:0XFFFFFFFF,代表错误;其他,内存偏移地址
//Memory allocation (internal calls)
//Memx: memory block to which it belongs
//Size: Size of memory to allocate (in bytes)
//Return value: 0XFFFFFFFF, representing an error; Other, memory offset address
u32 mem_malloc(u32 size)  
{  
    signed long offset=0;  
    u16 nmemb;	//Number of memory blocks required 需要的内存块数
	u16 cmemb=0;//Number of contiguous empty memory blocks 连续空内存块数
    u32 i;  
    if(!mallco_dev.memrdy)mallco_dev.init();	//Not initialized, execute initialization first 未初始化,先执行初始化
    if(size==0)return 0XFFFFFFFF;				//No allocation required 不需要分配
    nmemb=size/memblksize;  					//Obtain the number of contiguous memory blocks that need to be allocated 获取需要分配的连续内存块数
    if(size%memblksize)nmemb++;  
    for(offset=memtblsize-1;offset>=0;offset--)	//Search the entire memory control area 搜索整个内存控制区
    {     
		if(!mallco_dev.memmap[offset])cmemb++;	//Continuously increasing the number of empty memory blocks 连续空内存块数增加
		else cmemb=0;							//Zeroing Continuous Memory Blocks 连续内存块清零
		if(cmemb==nmemb)						//Found consecutive nmemb empty memory blocks 找到了连续nmemb个空内存块
		{
            for(i=0;i<nmemb;i++)  				//Mark memory block is not empty 标注内存块非空
            {  
                mallco_dev.memmap[offset+i]=nmemb;  
            }  
            return (offset*memblksize);			//Return offset address 返回偏移地址
		}
    }  
    return 0XFFFFFFFF;//No memory blocks found that meet the allocation criteria 未找到符合分配条件的内存块
}  
//释放内存(内部调用)
//offset:内存地址偏移
//返回值:0,释放成功;1,释放失败;
//Release memory (internal call)
//Offset: Memory address offset
//Return value: 0, successfully released; 1. Release failed;
u8 mem_free(u32 offset)  
{  
    int i;  
    if(!mallco_dev.memrdy)//Not initialized, execute initialization first 未初始化,先执行初始化
	{
		mallco_dev.init();    
        return 1;//not initialized 未初始化
    }  
    if(offset<memsize)//Offset within the memory pool 偏移在内存池内.
    {  
        int index=offset/memblksize;		//Offset memory block number 偏移所在内存块号码
        int nmemb=mallco_dev.memmap[index];	//Number of memory blocks 内存块数量
        for(i=0;i<nmemb;i++)  				//Memory Block Zeroing 内存块清零
        {  
            mallco_dev.memmap[index+i]=0;  
        }
        return 0;  
    }else return 2;//The offset is out of range 偏移超区了.
}  
//释放内存(外部调用)
//ptr:内存首地址
//Release memory (external call)
//Ptr: memory first address
void myfree(void *ptr)  
{  
	u32 offset;  
    if(ptr==NULL)return;//The address is 0 地址为0.
 	offset=(u32)ptr-(u32)mallco_dev.membase;  
    mem_free(offset);	//free memory 释放内存
}  
//分配内存(外部调用)
//size:内存大小(字节)
//返回值:分配到的内存首地址.
//Allocate memory (external calls)
//Size: Memory size (in bytes)
//Return value: The first address of the allocated memory
void *mymalloc(u32 size)  
{  
    u32 offset;  									      
	offset=mem_malloc(size);  	   				   
    if(offset==0XFFFFFFFF)return NULL;  
    else return (void*)((u32)mallco_dev.membase+offset);  
}  
//重新分配内存(外部调用)
//*ptr:旧内存首地址
//size:要分配的内存大小(字节)
//返回值:新分配到的内存首地址.
//Reassign memory (external call)
//*Ptr: Old Memory First Address
//Size: Size of memory to allocate (in bytes)
//Return value: The first address of the newly allocated memory
void *myrealloc(void *ptr,u32 size)  
{  
    u32 offset;  
    offset=mem_malloc(size);  
    if(offset==0XFFFFFFFF)return NULL;     
    else  
    {  									   
	    mymemcpy((void*)((u32)mallco_dev.membase+offset),ptr,size);	//Copy old memory content to new memory 拷贝旧内存内容到新内存
        myfree(ptr);  											  	//Release old memory 释放旧内存
        return (void*)((u32)mallco_dev.membase+offset);  			//Return the first address of the new memory 返回新内存首地址
    }  
}












