#include "dac.h"

//DACͨ��1�����ʼ��
void Dac1_Init(void)
{
  
	GPIO_InitTypeDef GPIO_InitStructure;
	DAC_InitTypeDef DAC_InitType;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE );	  //ʹ��PORTAͨ��ʱ��
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE );	  //ʹ��DACͨ��ʱ�� 

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;				 // �˿�����
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; 		 //ģ������
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_SetBits(GPIOA,GPIO_Pin_4)	;//PA.4 �����
					
	DAC_InitType.DAC_Trigger=DAC_Trigger_Software;	//�������DAת��
	DAC_InitType.DAC_WaveGeneration=DAC_WaveGeneration_None;//��ʹ�ò��η���
	DAC_InitType.DAC_LFSRUnmask_TriangleAmplitude=DAC_LFSRUnmask_Bit0;//���Ρ���ֵ����
	//DAC_InitType.DAC_OutputBuffer=DAC_OutputBuffer_Disable ;	//DAC1�������ر� BOFF1=1
	DAC_InitType.DAC_OutputBuffer=DAC_OutputBuffer_Enable ;
  DAC_Init(DAC_Channel_1,&DAC_InitType);	 //��ʼ��DACͨ��1

	DAC_Cmd(DAC_Channel_1, ENABLE);  //ʹ��DAC1
  
  DAC_SetChannel1Data(DAC_Align_12b_R, 0);  //12λ�Ҷ������ݸ�ʽ����DACֵ

}

//����ͨ��1�����ѹ
//����0~3.3V
void Dac1_Set_Vol(uint16_t vol)
{
	uint16_t temp;
	
	temp = (uint16_t) ((vol/3.3) * 4096);
	DAC_SetChannel1Data(DAC_Align_12b_R,temp);//12λ�Ҷ������ݸ�ʽ����DACֵ
	DAC_SoftwareTriggerCmd(DAC_Channel_1,ENABLE);
}

void DAC_OutVoltage(float valtage)
{
	uint16_t data;
	data = (uint16_t)((valtage/3.3) *4096);
	DAC_SetChannel1Data(DAC_Align_12b_R,data);//12λ�Ҷ������ݸ�ʽ����DACֵ
	DAC_SoftwareTriggerCmd(DAC_Channel_1,ENABLE);
}



