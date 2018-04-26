/********************************************************************************
//File Name:spi.c
//Author   :fluency
//Mail     :1005068694@qq.com
//Function :GPIO模拟的spi功能函数，用于LoRa模块sx1278的信息交互
********************************************************************************/
#include "spi.h"


#define high    1
#define low     0
#define RegNum			44
#define RegNum2594			115
/****************************************************************/
#define  SCL_PIN		GPIO_Pin_13         //SCK  
#define  WDATA_PIN	GPIO_Pin_15         //SDI 
#define  CS_PIN			GPIO_Pin_12         //CSB 	
#define  RDATA_PIN	GPIO_Pin_14         //RDATA 

#define  HIGH_LOW	  GPIO_Pin_5          //RDATA 

#define sx1278_Port					GPIOB
#define sx1278_GPIO_CLK   RCC_AHBPeriph_GPIOB
#define CS_1   	sx1278_Port->BSRR = CS_PIN;	    //CS管脚拉高
#define	CS_0 	  sx1278_Port->BRR = CS_PIN;	    //CS管脚拉低																		                           
#define	SCL_1	  sx1278_Port->BSRR = SCL_PIN;	  //CLK管脚拉高
#define	SCL_0	  sx1278_Port->BRR = SCL_PIN;     //CLK管脚拉低
#define WDATA_1	sx1278_Port->BSRR = WDATA_PIN;  //DATA管脚拉高
#define	WDATA_0	sx1278_Port->BRR = WDATA_PIN;   //DATA管脚拉低

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
	CS_1;  
	delay();
	SCL_0;
	WDATA_0;
	delay();
}



