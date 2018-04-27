/********************************************************************************
//File Name:flash.c
//Function :flash��д����
********************************************************************************/
#include "head.h"

u16 SPI_FLASH_TYPE=W25Q64;//Ĭ�Ͼ���25Q64

void FLASH_WriteByte(u32 addr,u16 flashdata1)
{
	
	FLASH_Status FLASHstatus = FLASH_COMPLETE;
	FLASH_Unlock();//����FLASH��̲���������
	FLASH_ClearFlag(FLASH_FLAG_BSY|FLASH_FLAG_EOP|FLASH_FLAG_PGERR|FLASH_FLAG_WRPRTERR); //�����־λ
	FLASHstatus=FLASH_ErasePage(START_ADDR);//����ָ����ַҳ
	if(FLASHstatus == FLASH_COMPLETE)
	{
		FLASHstatus=FLASH_ProgramHalfWord(START_ADDR+addr*2, flashdata1);// ��ָ��ҳ��addr��ַ��ʼд
	}
//	FLASH_ErasePage(START_ADDR);//����ָ����ַҳ
//	FLASH_ProgramHalfWord(START_ADDR+addr*2, flashdata1);// ��ָ��ҳ��addr��ַ��ʼд
	FLASH_Lock();//����FLASH��̲���������
}



uint32_t FlashRead(uint32_t addr, uint8_t *buffer, uint32_t length)  
{  
  memcpy(buffer, (void *)(START_ADDR + addr*2), length);  
  
  return length;  
}  

