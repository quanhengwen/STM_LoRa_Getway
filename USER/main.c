/********************************************************************************
//File Name:main.c
//Function :主函数入口
********************************************************************************/
#include "head.h"


/*
 Main application entry point.
*/
int main( void )
{
	uint8_t my_data;
	uint8_t my_stat;
	
	delay_init();	    
	sx1278GPIO_Ini();    
	PVD_Init();
	Dac1_Init();	
	USART2_Initialise(115200);
	
	SX1276Read(0x42,&my_data);		// semtech芯片版本，默认0x12
	SX1276Read(0x44,&my_stat);		// 默认值0x2D
	

	while(1)
	{
		OnSlave();
		delay_us(10000);
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
