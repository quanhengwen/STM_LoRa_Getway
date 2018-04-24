//#include "stm32f0xx.h"
//#include "sx1278.h"

#define high    1
#define low     0
#define RegNum			44
#define RegNum2594			115
/****************************************************************/
#define  SCL_PIN		GPIO_Pin_4        //LMX_SCK  
#define  WDATA_PIN	GPIO_Pin_3         //LMX_SDI 
#define  CS_PIN			GPIO_Pin_2         //LMX_CSB 	
#define  RDATA_PIN	GPIO_Pin_1         //LMX_RDATA 

#define  HIGH_LOW	  GPIO_Pin_5         //LMX_RDATA 

#define sx1278_Port					GPIOA
#define sx1278_GPIO_CLK   RCC_AHBPeriph_GPIOA 



#define  CS_1 	sx1278_Port->BSRR = CS_PIN;	//?1
#define		 CS_0 	sx1278_Port->BRR = CS_PIN;	//?0																					                           


#define	 SCL_1	sx1278_Port->BSRR = SCL_PIN;	//?1
#define		 SCL_0	sx1278_Port->BRR = SCL_PIN;

#define WDATA_1	sx1278_Port->BSRR = WDATA_PIN;
#define		WDATA_0	sx1278_Port->BRR = WDATA_PIN;

#define RDATA	((sx1278_Port->IDR) & RDATA_PIN);
//#define RESET_1	sx1278_Port->BSRR = RDATA_PIN;
//#define		RESET_0	sx1278_Port->BRR = RDATA_PIN;


void static delay(void)				 	
{
   unsigned int T;
   for (T = 0;T<0x800 ; T++);
}
unsigned char ReadFromsx1278(unsigned short Addr )
{
	unsigned	char ValueBack=0;
    unsigned	char	i = 0;




	delay();
	SCL_0;
	CS_1;
	WDATA_0;
	delay();
	/******READ BACK MODE****/
	
	CS_0;
	
	WDATA_1;
	SCL_1;
	delay();
	SCL_0;

	WDATA_0;
	delay();
	SCL_1;
	delay();
	SCL_0;
	delay();
	SCL_1;
	delay();
	SCL_0;
	/*********READ BACK MODE**********/
	 
		for(i=0; i<13; i++)
		{
			if(0x1000 == ( Addr&0x1000))
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
			delay();
			SCL_1;
			//ValueBack+=RDATA;
			delay();
			SCL_0;	
			ValueBack<<=1;
		
		}
		
		

	delay();
	CS_1;
	delay();
		
		return ValueBack;

}
void WriteTosx1278(unsigned char count, unsigned int *buf)
{
	unsigned	long	ValueToWrite = 0;
    unsigned	char	i = 0;
	unsigned	char	j = 0;

	//SET_DATA_OUT();

	delay();
	SCL_0;
	WDATA_0;
	CS_1;
	delay();
	

	for(i=0;i<count;i++)
 	{
			CS_0;
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
		CS_1;
		delay();
	}
	WDATA_0;
	delay();
	
	delay();
}

void WriteTosx1278Register( unsigned long V)
{
	unsigned	long	ValueToWrite = V;
	unsigned	char	j = 0;
	//SET_DATA_OUT();
	delay();
	SCL_0;
	CS_0;
	delay();

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
	WDATA_0;
	delay();
	CS_1;

	delay();
}

void sx1278GPIO_Ini(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHBPeriphClockCmd(sx1278_GPIO_CLK , ENABLE);
    GPIO_InitStructure.GPIO_Pin = SCL_PIN|CS_PIN|WDATA_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;	
    GPIO_Init(sx1278_Port, &GPIO_InitStructure);
	CS_1;  // ????????CS
	delay();
	SCL_0;
	WDATA_0;
	
	delay();
//	RESET_1;
	
	delay();
}




void Init_sx1278(void)
{
	unsigned char i=0;
	unsigned char tem=0;
	
	
		sx1278GPIO_Ini();

//WriteTosx1278(RegNum2594, Inibuf2594);
	
	for(i=0;i<80;i++)
	{
		delay();
		tem=GPIO_ReadInputDataBit(sx1278_Port,HIGH_LOW);
		delay();
	}
	
	if(tem)
	{
	WriteTosx1278(RegNum, InibufHigh);
	
	}
	else WriteTosx1278(RegNum, InibufLow);
	

		




}



