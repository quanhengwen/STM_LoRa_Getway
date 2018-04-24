#include "stm32f10x_flash.h"
#include "flash.h"
#include "delay.h"  
#include "spi.h"

u16 SPI_FLASH_TYPE=W25Q64;//Ĭ�Ͼ���25Q64

void FLASH_WriteByte(u32 addr,u16 flashdata1)
{
	
//	 FLASH_Status FLASHstatus = FLASH_COMPLETE;
	FLASH_Unlock();//����FLASH��̲���������
	FLASH_ClearFlag(FLASH_FLAG_BSY|FLASH_FLAG_EOP|FLASH_FLAG_PGERR|FLASH_FLAG_WRPRTERR); //�����־λ
//	 FLASHstatus=FLASH_ErasePage(START_ADDR);//����ָ����ַҳ
//   FLASHstatus=FLASH_ProgramHalfWord(START_ADDR+addr*2, flashdata1);// ��ָ��ҳ��addr��ַ��ʼд
	FLASH_ErasePage(START_ADDR);//����ָ����ַҳ
	FLASH_ProgramHalfWord(START_ADDR+addr*2, flashdata1);// ��ָ��ҳ��addr��ַ��ʼд
//	 FLASH_Lock();//����FLASH��̲���������
}


//void FLASH_RriteByte(u32 addr,u16 rdata)
//{
////	u16 rdata;
//	rdata = *(u16*) (START_ADDR + addr*2);
//	return rdata;
//}

//void SPI_Flash_Init(void)
//{

//	GPIO_InitTypeDef GPIO_InitStructure;

//  RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB, ENABLE );

//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14;  //SPI CS
// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //�����������
//	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
// 	GPIO_Init(GPIOB, &GPIO_InitStructure);
// 	GPIO_SetBits(GPIOB,GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14);
//	SPI1_Init();		   //��ʼ��SPI
//	SPI1_SetSpeed(SPI_BaudRatePrescaler_64);	//����Ϊ1Mʱ��,����ģʽ
//	SPI_FLASH_TYPE=SPI_Flash_ReadID();//��ȡFLASH ID.
//}  

////��ȡоƬID W25X16��ID:0XEF14
//u16 SPI_Flash_ReadID(void)
//{
//	u16 Temp = 0;	  
//	SPI_FLASH_CS=0;				    
//	SPI1_ReadWriteByte(0x90);//���Ͷ�ȡID����	    
//	SPI1_ReadWriteByte(0x00); 	    
//	SPI1_ReadWriteByte(0x00); 	    
//	SPI1_ReadWriteByte(0x00); 	 			   
//	Temp|=SPI1_ReadWriteByte(0xFF)<<8;  
//	Temp|=SPI1_ReadWriteByte(0xFF);	 
//	SPI_FLASH_CS=1;				    
//	return Temp;
//}   		   

int ReadFlashNBtye(u32 ReadAddress) 
{
		u16 rdata=0;
		rdata = *(u16*) (START_ADDR + ReadAddress*2);
	return rdata;
}
