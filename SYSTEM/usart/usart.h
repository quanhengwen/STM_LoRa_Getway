#ifndef __USART_H
#define __USART_H

#include "stdio.h"	
#include "sys.h"
#include "stm32f10x_usart.h"

#define USART_RX_LEN 2
#define USART_TX_LEN 2

void USART2_Initialise( u32 bound);

#endif
