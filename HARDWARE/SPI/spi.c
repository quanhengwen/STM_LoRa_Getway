#include "spi.h"

////������SPIģ��ĳ�ʼ�����룬���ó�����ģʽ������SD Card/W25X16/24L01/JF24C							  
////SPI�ڳ�ʼ��
////�������Ƕ�SPI2�ĳ�ʼ��

//SPI_InitTypeDef  SPI_InitStructure;

//void SPI1_Init(void)
//{
//	GPIO_InitTypeDef GPIO_InitStructure;
//  
//	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB, ENABLE );
//  RCC_APB1PeriphClockCmd( RCC_APB1Periph_SPI2, ENABLE );	
// 
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOB, &GPIO_InitStructure);
//	
//	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;   
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;   
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;//cs
//    GPIO_Init(GPIOB,&GPIO_InitStructure);

// 	GPIO_SetBits(GPIOB,GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);
//  SPI_Cmd(SPI2, DISABLE);
//	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //����SPI�������˫�������ģʽ:SPI����Ϊ˫��˫��ȫ˫��
//	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		//����SPI����ģʽ:����Ϊ��SPI
//	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;		//����SPI�����ݴ�С:SPI���ͽ���8λ֡�ṹ
//	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;		//ѡ���˴���ʱ�ӵ���̬:ʱ�����ո�
//	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;	//���ݲ����ڵڶ���ʱ����
//	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		//NSS�ź���Ӳ����NSS�ܽţ����������ʹ��SSIλ������:�ڲ�NSS�ź���SSIλ����
//	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_32;		//���岨����Ԥ��Ƶ��ֵ:������Ԥ��ƵֵΪ32
//	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	//ָ�����ݴ����MSBλ����LSBλ��ʼ:���ݴ����MSBλ��ʼ
//	SPI_InitStructure.SPI_CRCPolynomial = 7;	//CRCֵ����Ķ���ʽ
//	SPI_Init(SPI2, &SPI_InitStructure);  //����SPI_InitStruct��ָ���Ĳ�����ʼ������SPIx�Ĵ���
// 
//	SPI_Cmd(SPI2, ENABLE); //ʹ��SPI����
//	
////	SPI1_ReadWriteByte(0xff);//��������		 
//}   
////SPI �ٶ����ú���
////SpeedSet:
////SPI_BaudRatePrescaler_2   2��Ƶ   (SPI 36M@sys 72M)
////SPI_BaudRatePrescaler_8   8��Ƶ   (SPI 9M@sys 72M)
////SPI_BaudRatePrescaler_16  16��Ƶ  (SPI 4.5M@sys 72M)
////SPI_BaudRatePrescaler_256 256��Ƶ (SPI 281.25K@sys 72M)
//  
//void SPI1_SetSpeed(u8 SpeedSet)
//{
//	SPI_InitStructure.SPI_BaudRatePrescaler = SpeedSet ;
//  	SPI_Init(SPI2, &SPI_InitStructure);
//	SPI_Cmd(SPI2,ENABLE);
//} 

////SPIx ��дһ���ֽ�
////TxData:Ҫд����ֽ�
////����ֵ:��ȡ�����ֽ�
//u8  SPI2_ReadWriteByte(u8 TxData)
//{		
//	u8 retry=0;				 	
//	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET) //���ָ����SPI��־λ�������:���ͻ���ձ�־λ
//		{
//		retry++;
//		if(retry>200)return 0;
//		}			  
//	SPI_I2S_SendData(SPI2, TxData); //ͨ������SPIx����һ������
//	retry=0;

//	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET)//���ָ����SPI��־λ�������:���ܻ���ǿձ�־λ
//		{
//		retry++;
//		if(retry>200)return 0;
//		}	  						    
//	return SPI_I2S_ReceiveData(SPI2); //����ͨ��SPIx������յ�����					    
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






























