#include "stm32f10x_exti.h"
#include "stm32f10x_pwr.h"
#include "stm32f10x_rcc.h"
#include "led.h"



void PVD_Init(void)
{
		EXTI_InitTypeDef EXTI_InitStructure; 
	 NVIC_InitTypeDef NVIC_InitStructure;//Ƕ�������ж�
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1); 
	NVIC_InitStructure.NVIC_IRQChannel = PVD_IRQn;//  EXTI1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
	
    PWR_PVDLevelConfig(PWR_PVDLevel_2V9); // �趨��ֵ  
    PWR_PVDCmd(ENABLE); // ʹ��PVD  
	  EXTI_DeInit();
    EXTI_StructInit(&EXTI_InitStructure);  
    EXTI_InitStructure.EXTI_Line = EXTI_Line16; // PVD���ӵ��ж���16��
   	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt; //ʹ���ж�ģʽ
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;//��ѹ���ڷ�ֵ�����ж�
    EXTI_InitStructure.EXTI_LineCmd = ENABLE; // ʹ���ж���  
    EXTI_Init(&EXTI_InitStructure); // ��ʼ ����16�߲���һ���ж�
	//		EXTI_InitStructure.EXTI_Trigger= EXTI_Trigger_Rising; 
		
}		
		
/*
		void  PVD_IRQHandler(void)  
    { 
     	
			if(PWR_GetFlagStatus(PWR_FLAG_PVDO))//��־λ����VDD���ڻ��ǵ��ڷ�ֵ
			{
				LED0 = 0;
			}
			 EXTI_ClearITPendingBit(EXTI_Line16); 
    }
*/