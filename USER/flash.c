#include "stm32f10x_flash.h"
#include "flash.h"
#include "delay.h"  
#include "spi.h"

u16 SPI_FLASH_TYPE=W25Q64;//默认就是25Q64

void FLASH_WriteByte(u32 addr,u16 flashdata1)
{
	
//	 FLASH_Status FLASHstatus = FLASH_COMPLETE;
	FLASH_Unlock();//解锁FLASH编程擦除控制器
	FLASH_ClearFlag(FLASH_FLAG_BSY|FLASH_FLAG_EOP|FLASH_FLAG_PGERR|FLASH_FLAG_WRPRTERR); //清除标志位
//	 FLASHstatus=FLASH_ErasePage(START_ADDR);//擦除指定地址页
//   FLASHstatus=FLASH_ProgramHalfWord(START_ADDR+addr*2, flashdata1);// 从指定页的addr地址开始写
	FLASH_ErasePage(START_ADDR);//擦除指定地址页
	FLASH_ProgramHalfWord(START_ADDR+addr*2, flashdata1);// 从指定页的addr地址开始写
//	 FLASH_Lock();//解锁FLASH编程擦除控制器
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
// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //复用推挽输出
//	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
// 	GPIO_Init(GPIOB, &GPIO_InitStructure);
// 	GPIO_SetBits(GPIOB,GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14);
//	SPI1_Init();		   //初始化SPI
//	SPI1_SetSpeed(SPI_BaudRatePrescaler_64);	//设置为1M时钟,高速模式
//	SPI_FLASH_TYPE=SPI_Flash_ReadID();//读取FLASH ID.
//}  

////读取芯片ID W25X16的ID:0XEF14
//u16 SPI_Flash_ReadID(void)
//{
//	u16 Temp = 0;	  
//	SPI_FLASH_CS=0;				    
//	SPI1_ReadWriteByte(0x90);//发送读取ID命令	    
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
