/********************************************************************************
//File Name:sx1278.c
//Function :通过模拟SPI对sx1278芯片配置，实现Master or Slave Mode
********************************************************************************/
#include "head.h"
#include "sx1278.h"

uint8_t SX1278Regs[0x06]={0x64,0x48,0x80,0x00,0x00,0};
uint8_t test=0;

//	RadioDriverInit();
//	SX1276Read(0x42,&my_data);		// semtech芯片版本，默认0x12
//	SX1276Read(0x44,&my_stat);		// 默认值0x2D

//#define BUFFER_SIZE  30                     // Define the payload size here
//static uint16_t BufferSize = BUFFER_SIZE;	  // RF buffer size
//static uint8_t Buffer[BUFFER_SIZE];					// RF buffer

//static uint8_t EnableMaster = true; 				// Master/Slave selection
//static uint8_t EnableMaster = false; 				// Master/Slave selection
//tRadioDriver *Radio = NULL;

const uint8_t PingMsg[] = "PING";
const uint8_t PongMsg[] = "PONG";

const uint8_t MY_TEST_Msg[] = "SX1278_TEST";
static uint8_t RFBuffer[11];

uint8_t SX1276Regs_test[0x70]={0};
uint8_t	DIO0=0;
static uint8_t count;

/*
 * Manages the master operation
 */
void OnMaster( void )
{
	uint8_t i=0;
	RFBuffer[0]='p';
	RFBuffer[1]='i';
	RFBuffer[2]='n';
	RFBuffer[3]='g';
	RFBuffer[4] = count ++;
	for(i=5;i<11;i++)
	{
		RFBuffer[i]=i-5;
	}
	// lora-init
	SX1276Write(0x01,0x00);			// sleep
	SX1276Write(0x01,0x80);			// Lora
	SX1276Write(0x01,0x81);			// standby
	
//	SX1276Write(0x40,0x00);
//	SX1276Write(0x41,0x00);
	SX1276Write(0x4D,0x87);			//PaDac
	SX1276Write(0x09,0x8F);			//PA:Boost-MAXPower
	
	SX1276Write(0x1D,0x72);			// BW:125kHz CR:4/5
	SX1276Write(0x1E,0x74);			// SF7 CRC:1
	
	SX1276Write(0x26,0x0C);			//LowDataRateOptimize
	
	SX1276Write(0x0A,0x08);			// 50us PA Ramp-up time
	
	SX1276Write(0x39,0x34);			//LoRa sync word

	SX1276Write(0x24,0x00);			//FreqHoppingPeriod--off
	SX1276Write(0x11,0xF7);			//IRQ
	SX1276Write(0x22,11);			  //payloadLength
	SX1276Write(0x0E,0x80);			//RegFifoTxBaseAddr,??0x80
	SX1276Write(0x0D,0x80);			//FifoAddrPtr,Set FifoPtrAddr to FifoTxPtrBase.
	SX1276WriteBuffer(00,RFBuffer,11);// Write PayloadLength bytes to the FIFO (RegFifo)
	
	SX1276Write(0x40,0x40);			//
	SX1276Write(0x41,0x00);			//
	
	SX1276Write(0x01,0x83);

	SX1276ReadBuffer(0x01,SX1276Regs_test+1,0x70-1);

	while(1)
	{
		SX1276Read(0x12,&test);
//		DIO0=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_9);
//		if(1==DIO0)
		if((test&0x08)==0x08)
		{
			SX1276Write(0x12,0x08);
			delay_ms(100);
			SX1276Write(0x01,0x81);
			SX1276Write(0x11,0xF7);			//IRQFlagMask
			SX1276Write(0x24,0x00);			//RegHopPeriod
			SX1276Write(0x0D,0x80);			//FifoAddrPtr,Set FifoPtrAddr to FifoTxPtrBase.
			SX1276WriteBuffer(00,RFBuffer,11);
			RFBuffer[4] = count++;
			SX1276Write(0x40,0x00);			//
			SX1276Write(0x41,0x00);			//
			SX1276Write(0x01,0x83);
		}
	}
}


/*
 * Manages the slave operation
 */

uint16_t i=0;
uint8_t prev=0;
void OnSlave( void )
{
	SX1276Write(0x01,0x00);
	SX1276Write(0x01,0x80);
	SX1276Write(0x01,0x81);     //sleep--LoRa-->standby
	/*
	SX1276Write(0x0D,0x00);			//FifoAddrPtr,Set FifoPtrAddr to FifoRxPtrBase.
	SX1276Write(0x0F,0x00);			//RegFifoRxBaseAddr,??0x00
	
	SX1276Write(0x40,0x00);			//
	SX1276Write(0x41,0x00);			//
	SX1276Write(0x4D,0x87);			//PaDac
	SX1276Write(0x09,0x8F);			//PA:Boost-MAXPower
	SX1276Write(0x0C,0x23);			// lnagain
	
	SX1276Write(0x1D,0x72);			// BW:125kHz CR:4/5
	SX1276Write(0x1E,0x74);			// SF7 CRC:1
	
	SX1276Write(0x26,0x0C);			//LowDataRateOptimize
	SX1276Write(0x24,0x00);			//RegHopPeriod
	
	SX1276Write(0x1F,0x9F);			// RX-timeout LSB 2^10
	SX1276Write(0x21,0x0C);			//payloadLength
	SX1276Write(0x23,0x40);			//payloadLength
	
	SX1276Write(0x33,0x67);
	SX1276Write(0x39,0x34);			//LoRa sync word
	SX1276Write(0x3B,0x19);
	
	SX1276Write(0x11,0x0F);			//IRQFlagMask
	SX1276Write(0x40,0x00);			//
	SX1276Write(0x41,0x00);			//
*/
	
	SX1276Write(0x1D,0x72);			// BW:125kHz CR:4/5
	SX1276Write(0x1E,0x77);			// SF7 CRC:1
	SX1276Write(0x1F,0xfF);			// RX-timeout LSB 2^10
	
	SX1276Write(0x22,11);			  //payloadLength
	SX1276Write(0x26,0x0C);			//LowDataRateOptimize
	SX1276Write(0x09,0x8F);			//PA:Boost-MAXPower
	SX1276Write(0x4D,0x87);			//PaDac
//	SX1276Write(0x0C,0x23);			// lnagain

	SX1276Write(0x11,0x0F);			//IRQ
	SX1276Write(0x24,0xFF);			//RegHopPeriod
	
	SX1276Write(0x40,0x00);			//
	SX1276Write(0x41,0x00);			//
	SX1276Write(0x39,0x34);			//LoRa sync word
	SX1276Write(0x0F,0x00);			//RegFifoRxBaseAddr,??0x00
	
	SX1276Write(0x01,0x86);			//Receive continuous
	while(1)
	{
//		SX1276Write(0x01,0x8E);				//Receive continuous
		SX1276Read(0x12,&test);
//		
//		SX1276Write(0x01,0x86);				//Receive continuous
		
		if(test==0)
		{
			if(prev==0)
				i++;
			else
				i=0;
			prev=test;
			if(i>0x3ff)
				break;
			continue;
		}
		
		prev=test;
		if((test&0x80)==0x80)
		{
			SX1276Write(0x12,0x80);
			break;
		}
		else if((test&0x40)==0x40)
		{
			SX1276Write(0x12,0x40);
			SX1276Read(0x1B,&test);

			SX1276Write(0x0D,0x00);			//FifoAddrPtr,Set FifoPtrAddr to FifoRxPtrBase.
			test=0;
			SX1276Read(0x13,&test);
			SX1276ReadBuffer(0x00,RFBuffer,test);
			for(i = 0; i < 11; i++)
			{
				USART_SendData(USART2, RFBuffer[i]);
			}		
			SX1276Write(0x01,0x81);
			SX1276Write(0x11,0x9F);			//IRQFlagMask
			SX1276Write(0x24,0xFF);			//RegHopPeriod
			SX1276Write(0x40,0x00);			//
			SX1276Write(0x41,0x00);			//
			
			SX1276Write(0x01,0x86);
		}
		SX1276ReadBuffer(0x01,SX1276Regs_test+1,0x70-1);
//		else
//		{SX1276Write(0x12,0xBF);}
	}
}

void CADdetect( void )
{
	SX1276Write(0x01,0x00);
	SX1276Write(0x01,0x80);
	SX1276Write(0x01,0x81);     //sleep--LoRa-->standby
	
	SX1276Write(0x1D,0x72);			// BW:125kHz CR:4/5
	SX1276Write(0x1E,0x77);			// SF7 CRC:1
	SX1276Write(0x1F,0xfF);			// RX-timeout LSB 2^10
	
	SX1276Write(0x22,11);		    //payloadLength
	SX1276Write(0x26,0x0C);			//LowDataRateOptimize
	SX1276Write(0x09,0x8F);			//PA:Boost-MAXPower
	SX1276Write(0x4D,0x87);			//PaDac
	
	SX1276Write(0x11,0xFA);			//IRQ

	// DIO0: CadDone		DIO1: CadDetected
	SX1276Write(0x40,0xA0);			
	SX1276Write(0x41,0x00);			
	
	// DIO3: CadDone		DIO4: CadDetected
	SX1276Write(0x40,0x00);			
	SX1276Write(0x41,0x00);			
	
	SX1276Write(0x39,0x34);			//LoRa sync word
	SX1276Write(0x01,0x87);  		//OpMode:CAD
	while(1)
	{
		SX1276Read(0x12,&test);
		if((test&0x04)==0x04)
		{
			SX1276Write(0x12,0x04);
			if((test&0x01)==0x01)
			{
				SX1276Write(0x12,0x01);
				OnSlave();
				SX1276Write(0x01,0x87);//OpMode:CAD
			}
		}
		SX1276ReadBuffer(0x01,SX1276Regs_test+1,0x70-1);
	}
}

