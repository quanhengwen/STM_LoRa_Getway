#ifndef __USART_H
#define __USART_H	
#include "sys.h"

#define USART_RX_LEN 5

void USART2_Initialise( u32 bound);
void USART2_IRQHandler(void);
#endif
