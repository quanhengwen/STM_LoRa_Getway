/********************************************************************************
//File Name:main.c
//Function :主函数入口
********************************************************************************/
#include "head.h"

extern int count;
extern uint16_t USART2_RX_BUF[USART_RX_LEN];  
extern uint32_t date;
/*
 Main application entry point.
*/
int main( void )
{
	uint8_t my_data;
	uint8_t my_stat;
	int i;

	uint8_t buffer[4];
	u8 RFBuffer[12];
	
	/*init program*/
	delay_init();	    
	sx1278GPIO_Ini();    
	PVD_Init();
	Dac1_Init();	
	USART2_Initialise(115200);
	Init_sx1278();
	
	SX1276Read(0x42,&my_data);		// semtech芯片版本，默认0x12
	SX1276Read(0x44,&my_stat);		// 默认值0x2D
	

	FlashRead( USER_ADDR, buffer, 4);

	while(1)
	{
		onslave( RFBuffer);
		for(i = 0; i < 12; i++)
		{
			RFBuffer[i] = 12 - i;
		}
		onmaster(RFBuffer, 12);
		USART_SendData(USART2, 0x11);
		delay_us(100);
		USART_SendData(USART2, 0x11);
		delay_us(100);
		USART_SendData(USART2, 0x11);
		for(i = 0; i < 12; i++)
		{
			delay_us(100);
			USART_SendData(USART2, RFBuffer[i]);
		}		
		count = 0;
		for(i = 0; i < USART_RX_LEN; i++)
		{
			USART2_RX_BUF[i] = 0;
		}
		
	}
}



/*
* printf function
*/
int fputc(int ch, FILE *f)
{
	USART_SendData(USART2, (unsigned char) ch);
	while (!(USART2->SR & USART_FLAG_TXE));
	return (ch);
}

int GetKey(void) 
{
	while (!(USART2->SR & USART_FLAG_RXNE));
	return ((int)(USART2->DR & 0x1FF));
}
