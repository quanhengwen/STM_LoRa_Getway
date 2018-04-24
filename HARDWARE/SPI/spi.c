#include "spi.h"

////以下是SPI模块的初始化代码，配置成主机模式，访问SD Card/W25X16/24L01/JF24C							  
////SPI口初始化
////这里针是对SPI2的初始化

//SPI_InitTypeDef  SPI_InitStructure;

//void SPI1_Init(void)
//{
//	GPIO_InitTypeDef GPIO_InitStructure;
//  
//	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB, ENABLE );
//  RCC_APB1PeriphClockCmd( RCC_APB1Periph_SPI2, ENABLE );	
// 
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOB, &GPIO_InitStructure);
//	
//	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;   
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;   
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;//cs
//    GPIO_Init(GPIOB,&GPIO_InitStructure);

// 	GPIO_SetBits(GPIOB,GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);
//  SPI_Cmd(SPI2, DISABLE);
//	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //设置SPI单向或者双向的数据模式:SPI设置为双线双向全双工
//	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		//设置SPI工作模式:设置为主SPI
//	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;		//设置SPI的数据大小:SPI发送接收8位帧结构
//	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;		//选择了串行时钟的稳态:时钟悬空高
//	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;	//数据捕获于第二个时钟沿
//	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		//NSS信号由硬件（NSS管脚）还是软件（使用SSI位）管理:内部NSS信号有SSI位控制
//	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_32;		//定义波特率预分频的值:波特率预分频值为32
//	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	//指定数据传输从MSB位还是LSB位开始:数据传输从MSB位开始
//	SPI_InitStructure.SPI_CRCPolynomial = 7;	//CRC值计算的多项式
//	SPI_Init(SPI2, &SPI_InitStructure);  //根据SPI_InitStruct中指定的参数初始化外设SPIx寄存器
// 
//	SPI_Cmd(SPI2, ENABLE); //使能SPI外设
//	
////	SPI1_ReadWriteByte(0xff);//启动传输		 
//}   
////SPI 速度设置函数
////SpeedSet:
////SPI_BaudRatePrescaler_2   2分频   (SPI 36M@sys 72M)
////SPI_BaudRatePrescaler_8   8分频   (SPI 9M@sys 72M)
////SPI_BaudRatePrescaler_16  16分频  (SPI 4.5M@sys 72M)
////SPI_BaudRatePrescaler_256 256分频 (SPI 281.25K@sys 72M)
//  
//void SPI1_SetSpeed(u8 SpeedSet)
//{
//	SPI_InitStructure.SPI_BaudRatePrescaler = SpeedSet ;
//  	SPI_Init(SPI2, &SPI_InitStructure);
//	SPI_Cmd(SPI2,ENABLE);
//} 

////SPIx 读写一个字节
////TxData:要写入的字节
////返回值:读取到的字节
//u8  SPI2_ReadWriteByte(u8 TxData)
//{		
//	u8 retry=0;				 	
//	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET) //检查指定的SPI标志位设置与否:发送缓存空标志位
//		{
//		retry++;
//		if(retry>200)return 0;
//		}			  
//	SPI_I2S_SendData(SPI2, TxData); //通过外设SPIx发送一个数据
//	retry=0;

//	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET)//检查指定的SPI标志位设置与否:接受缓存非空标志位
//		{
//		retry++;
//		if(retry>200)return 0;
//		}	  						    
//	return SPI_I2S_ReceiveData(SPI2); //返回通过SPIx最近接收的数据					    
//}



//u8 SPI_Write_Byte(u8 data)
//{
//while (!(SPI2->SR & (1 << 1)));
//SPI2->DR = data;
//while (!(SPI2->SR & 1));
//return SPI2->DR;
//}


//u8 SPI_read_byte(void)
//{
//while (!(SPI2->SR & (1 << 1)));
//SPI2->DR = 0x00;
//while (!(SPI2->SR & 1));
//return SPI2->DR;
//}

//#include "stm32f0xx.h"
//#include "sx1278.h"

#define high    1
#define low     0
#define RegNum			44
#define RegNum2594			115
/****************************************************************/
#define  SCL_PIN		GPIO_Pin_13        //LMX_SCK  
#define  WDATA_PIN	GPIO_Pin_15         //LMX_SDI 
#define  CS_PIN			GPIO_Pin_12         //LMX_CSB 	
#define  RDATA_PIN	GPIO_Pin_14         //LMX_RDATA 

#define  HIGH_LOW	  GPIO_Pin_5         //LMX_RDATA 

#define sx1278_Port					GPIOB
#define sx1278_GPIO_CLK   RCC_AHBPeriph_GPIOB

//GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15)

#define  CS_1 	sx1278_Port->BSRR = CS_PIN;	//?1
#define		 CS_0 	sx1278_Port->BRR = CS_PIN;	//?0																					                           


#define	 SCL_1	sx1278_Port->BSRR = SCL_PIN;	//?1
#define		 SCL_0	sx1278_Port->BRR = SCL_PIN;

#define WDATA_1	sx1278_Port->BSRR = WDATA_PIN;
#define		WDATA_0	sx1278_Port->BRR = WDATA_PIN;

//#define RDATA	(sx1278_Port->IDR) & RDATA_PIN;
//#define RESET_1	sx1278_Port->BSRR = RDATA_PIN;
//#define		RESET_0	sx1278_Port->BRR = RDATA_PIN;


void static delay(void)
{
	unsigned int T;
	for (T = 0;T<0x800 ; T++);
}

void SX1276Read(uint8_t Addr,uint8_t *data)
{
	uint8_t ValueBack=0;
	uint8_t	i = 0;
	uint8_t rdata=0;
	delay();
	SCL_0;
	CS_1;
	delay();
	CS_0;

	/*********READ BACK MODE**********/
	 Addr=Addr & 0x7F;
	for(i=0; i<8; i++)
	{
		if(0x80== ( Addr&0x80))
		{
			WDATA_1;	  //Send one to SDO pin
		}
		else
		{
			WDATA_0;	  //Send zero to SDO pin
		}
		delay();
		SCL_1;
		delay();
		Addr <<= 1;	//Rotate data
		SCL_0;
	}
	

	for(i=0;i<8;i++)
	{
		ValueBack<<=1;
		delay();
		SCL_1;
		if(((sx1278_Port->IDR) & RDATA_PIN) == 0x4000)
			rdata=1;
		else
			rdata=0;
		ValueBack+=rdata;
		
		delay();
		SCL_0;
	}
	*data=ValueBack;
	delay();
	CS_1;
}

void SX1276ReadBuffer(uint8_t Addr, uint8_t *buf, uint8_t count)
{
	
	uint8_t ValueBack=0;
	uint8_t	i = 0;
	uint8_t j = 0;
	uint8_t rdata=0;
	delay();
	SCL_0;
	CS_1;
	delay();
	CS_0;

	/*********READ BACK MODE**********/
	 Addr=Addr & 0x7F;
	for(i=0; i<8; i++)
	{
		if(0x80== ( Addr&0x80))
		{
			WDATA_1;	  //Send one to SDO pin
		}
		else
		{
			WDATA_0;	  //Send zero to SDO pin
		}
		delay();
		SCL_1;
		delay();
		Addr <<= 1;	//Rotate data
		SCL_0;
	}
	
	for(j=0;j<count;j++)
 	{
		CS_0;
		for(i=0;i<8;i++)
		{
			ValueBack<<=1;
			delay();
			SCL_1;
			if(((sx1278_Port->IDR) & RDATA_PIN) == 0x4000)
				rdata=1;
			else
				rdata=0;
			ValueBack+=rdata;
			
			delay();
			SCL_0;
		}
		*(buf + j)=ValueBack;
	}
	delay();
	CS_1;
//	delay();
}

void SX1276WriteBuffer(uint8_t Addr,uint8_t *buf,uint8_t count)
{
	uint8_t	ValueToWrite = 0;
  uint8_t	i = 0;
	uint8_t	j = 0;

	delay();
	SCL_0;
	WDATA_0;
	CS_1;
	delay();
	CS_0;
	
	Addr=Addr | 0x80;
	for(j=0; j<8; j++)
	{
		if(0x80 == (Addr & 0x80))
		{
			WDATA_1;	  //Send one to SDO pin
		}
		else
		{
			WDATA_0;	  //Send zero to SDO pin
		}
		delay();
		SCL_1;
		delay();
		Addr <<= 1;	//Rotate data
		SCL_0;
	}
	
	for(i=0;i<count;i++)
 	{
	 	ValueToWrite = *(buf + i );
		for(j=0; j<8; j++)
		{
			if(0x80== (ValueToWrite & 0x80))
			{
				WDATA_1;	  //Send one to SDO pin
			}
			else
			{
				WDATA_0;	  //Send zero to SDO pin
			}
			delay();
			SCL_1;
			delay();
			ValueToWrite <<= 1;	//Rotate data
			SCL_0;
		}
		ValueToWrite=0;
		delay();
	}
	CS_1;
	WDATA_0; 
	delay();
}



void SX1276Write(uint8_t Addr,uint8_t V)
{
	uint8_t	ValueToWrite = V;
	uint8_t	j = 0;
	//SET_DATA_OUT();
	delay();
	SCL_0;
	CS_0;
	delay();
	Addr=Addr | 0x80;
	for(j=0; j<8; j++)
	{
		if(0x80 == (Addr & 0x80))
		{
			WDATA_1;	  //Send one to SDO pin
		}
		else
		{
			WDATA_0;	  //Send zero to SDO pin
		}
		delay();
		SCL_1;
		delay();
		Addr <<= 1;	//Rotate data
		SCL_0;
	}
//	WDATA_0;
	for(j=0; j<8; j++)
	{
		if(0x80 == (ValueToWrite & 0x80))
		{
			WDATA_1;	  //Send one to SDO pin
		}
		else
		{
			WDATA_0;	  //Send zero to SDO pin
		}
		delay();
		SCL_1;
		delay();
		ValueToWrite <<= 1;	//Rotate data
		SCL_0;
	}
	delay();
	CS_1;
//	delay();
}


void sx1278GPIO_Ini(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
//	RCC_AHBPeriphClockCmd(sx1278_GPIO_CLK , ENABLE);
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB, ENABLE );
//  RCC_APB1PeriphClockCmd( RCC_APB1Periph_SPI2, ENABLE );	
	GPIO_InitStructure.GPIO_Pin = SCL_PIN|CS_PIN|WDATA_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;	
	GPIO_Init(sx1278_Port, &GPIO_InitStructure);
	CS_1;  //
	delay();
	SCL_0;
	WDATA_0;
	delay();
	//	RESET_1;
//	delay();
}

void Init_sx1278(void)
{
//	uint8_t i=0;
//	uint8_t tem=0;
	sx1278GPIO_Ini();

//	for(i=0;i<80;i++)
//	{
//		delay();
//		tem=GPIO_ReadInputDataBit(sx1278_Port,HIGH_LOW);
//		delay();
//	}

//	if(tem)
//	{
//		WriteTosx1278(RegNum, InibufHigh);
//	}
//	else
//		WriteTosx1278(RegNum, InibufLow);
}






























