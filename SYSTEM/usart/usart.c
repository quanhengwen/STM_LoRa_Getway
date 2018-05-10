/********************************************************************************
//File Name:uart.c
//Function :UART2 初始化配置 中断函数 接收HC8000的时间数据和DAC输出数据
********************************************************************************/
#include "usart.h"	
#include "head.h"

void USART2_Initialise(u32 bound)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    
    /* Enable the USART2 Pins Software Remapping */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE); 
    
    
    /* Configure USART2 Rx (PA.03) as input floating */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    /* Configure USART2 Tx (PA.02) as alternate function push-pull */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    /* Enable the USART2 Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);    
    
    USART_InitStructure.USART_BaudRate = 115200;                
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;     
    USART_InitStructure.USART_Parity = USART_Parity_No;        
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	
    
    USART_Init(USART2, &USART_InitStructure);
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
    //USART_ITConfig(USART2, USART_IT_TXE, ENABLE);
    /* Enable USART2 */
    USART_Cmd(USART2, ENABLE);
}


//=============================================================================
//文件名称：
//功能概要：USART1中断函数
//参数说明：无
//函数返回：无
//============================================================================= 
uint16_t USART2_RX_BUF[USART_RX_LEN];     
int count;
uint32_t date;
void USART2_IRQHandler(void)    
{  
	uint16_t flashdata1;
	uint16_t flashdata2;
	uint16_t flashdata3;
	uint16_t flashdata4;
	float dac;
	
	if(USART_GetFlagStatus(USART2, USART_FLAG_RXNE) == SET)  
	{       
		//USART_SendData(USART2, USART_ReceiveData(USART2));
		USART2_RX_BUF[count++] = USART_ReceiveData(USART2);
		if(count == USART_RX_LEN)
		{
			count = 0;
			if((USART2_RX_BUF[0] & 0xff) == 0x00)
			{
				//SET DATE TO FLASH
				flashdata1 = USART2_RX_BUF[1]; //78
				flashdata2 = USART2_RX_BUF[2]; //1A
				flashdata3 = USART2_RX_BUF[3]; //C8
				flashdata4 = USART2_RX_BUF[4]; //3A
				date = ((((uint32_t)flashdata1) << 24) & 0xff000000) + ((((uint32_t)flashdata2) << 16) & 0xff0000) + ((((uint32_t)flashdata3) << 8) & 0xff00) + (((uint32_t)flashdata4) & 0xff);
				//FLASH_WriteByte(USER_ADDR , date);
			}	
			if((USART2_RX_BUF[0] & 0xff) == 0x01)
			{
				dac = ((USART2_RX_BUF[1] & 0xff) / 256.0) * 3.3;
				//SET DAC OUT
				DAC_OutVoltage(dac);
			}	
		}	
	}     
}

