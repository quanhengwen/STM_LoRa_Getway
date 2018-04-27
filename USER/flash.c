/********************************************************************************
//File Name:flash.c
//Function :flash读写函数
********************************************************************************/
#include "head.h"

u16 SPI_FLASH_TYPE=W25Q64;//默认就是25Q64

void FLASH_WriteByte(u32 addr,u16 flashdata1)
{
	
	FLASH_Status FLASHstatus = FLASH_COMPLETE;
	FLASH_Unlock();//解锁FLASH编程擦除控制器
	FLASH_ClearFlag(FLASH_FLAG_BSY|FLASH_FLAG_EOP|FLASH_FLAG_PGERR|FLASH_FLAG_WRPRTERR); //清除标志位
	FLASHstatus=FLASH_ErasePage(START_ADDR);//擦除指定地址页
	if(FLASHstatus == FLASH_COMPLETE)
	{
		FLASHstatus=FLASH_ProgramHalfWord(START_ADDR+addr*2, flashdata1);// 从指定页的addr地址开始写
	}
//	FLASH_ErasePage(START_ADDR);//擦除指定地址页
//	FLASH_ProgramHalfWord(START_ADDR+addr*2, flashdata1);// 从指定页的addr地址开始写
	FLASH_Lock();//解锁FLASH编程擦除控制器
}



uint32_t FlashRead(uint32_t addr, uint8_t *buffer, uint32_t length)  
{  
  memcpy(buffer, (void *)(START_ADDR + addr*2), length);  
  
  return length;  
}  

