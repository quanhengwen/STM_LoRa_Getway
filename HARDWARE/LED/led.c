#include "led.h"
#include "stm32f10x_gpio.h"

	   

//初始化PB5和PE5为输出口.并使能这两个口的时钟		    
//LED IO初始化
void LED_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //使能AFIO,GPIOB端口时钟
	 
 GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE); //开启SWD，失能JTAG
 DBGMCU->CR &= 0xFFFFFFDF;
 
 	

	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;				 //LED0-->PA.8 端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化GPIOA.8
 GPIO_SetBits(GPIOB,GPIO_Pin_3);						 //PA.8 输出高

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;	    		 //LED1-->PD.2 端口配置, 推挽输出
	GPIO_Init(GPIOB, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
	GPIO_SetBits(GPIOB,GPIO_Pin_4); 						 //PD.2 输出高 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;	    		 //LED1-->PD.2 端口配置, 推挽输出
 GPIO_Init(GPIOB, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
 GPIO_SetBits(GPIOB,GPIO_Pin_5); 						 //PD.2 输出高 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;	    		 //LED1-->PD.2 端口配置, 推挽输出
 GPIO_Init(GPIOB, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
 GPIO_SetBits(GPIOB,GPIO_Pin_6); 						 //PD.2 输出高 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;	    		 //LED1-->PD.2 端口配置, 推挽输出
 GPIO_Init(GPIOB, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
 GPIO_SetBits(GPIOB,GPIO_Pin_11|GPIO_Pin_7); 						 //PD.2 输出高 

 
}
 
