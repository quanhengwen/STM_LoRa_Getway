#include "head.h"



float dac; 
uint32_t addr;
uint16_t date;

/*
 Main application entry point.
*/
int main( void )
{
	delay_init();	    
	Init_sx1278();    
	PVD_Init();
	Dac1_Init();	
	USART2_Initialise(115200);
	
	
	
	while(1)
	{
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
