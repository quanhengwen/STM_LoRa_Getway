#include "stm32f10x_exti.h"
#include "stm32f10x_pwr.h"
#include "stm32f10x_rcc.h"
#include "led.h"



void PVD_Init(void)
{
		EXTI_InitTypeDef EXTI_InitStructure; 
	 NVIC_InitTypeDef NVIC_InitStructure;//嵌套向量中断
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1); 
	NVIC_InitStructure.NVIC_IRQChannel = PVD_IRQn;//  EXTI1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
	
    PWR_PVDLevelConfig(PWR_PVDLevel_2V9); // 设定阀值  
    PWR_PVDCmd(ENABLE); // 使能PVD  
	  EXTI_DeInit();
    EXTI_StructInit(&EXTI_InitStructure);  
    EXTI_InitStructure.EXTI_Line = EXTI_Line16; // PVD连接到中断线16上
   	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt; //使用中断模式
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;//电压低于阀值产生中断
    EXTI_InitStructure.EXTI_LineCmd = ENABLE; // 使能中断线  
    EXTI_Init(&EXTI_InitStructure); // 初始 配置16线产生一个中断
	//		EXTI_InitStructure.EXTI_Trigger= EXTI_Trigger_Rising; 
		
}		
		
/*
		void  PVD_IRQHandler(void)  
    { 
     	
			if(PWR_GetFlagStatus(PWR_FLAG_PVDO))//标志位表明VDD高于还是低于阀值
			{
				LED0 = 0;
			}
			 EXTI_ClearITPendingBit(EXTI_Line16); 
    }
*/