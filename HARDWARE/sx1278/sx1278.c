/********************************************************************************
//File Name:sx1278.c
//Function :通过模拟SPI对sx1278芯片配置，实现Master or Slave Mode
********************************************************************************/
#include "head.h"
#include "sx1278.h"

const uint8_t PingMsg[] = "PING";
const uint8_t PongMsg[] = "PONG";

uint8_t test=0;
uint8_t prev;
//uint8_t	DIO0=0;
int i;

u8 onslave(u8 *RFBuffer)
{

	SX1276Write(0x01,0x81);  //sleep--LoRa-->standby
	SX1276Write(0x1F,0xfF);			// RX-timeout LSB 2^10
	SX1276Write(0x0C,0x23);			// lnagain
	SX1276Write(0x11,0x0F);			//IRQ
	SX1276Write(0x24,0xFF);			//RegHopPeriod
	SX1276Write(0x40,0x00);			//
//	SX1276Write(0x39,0x34);			//LoRa sync word
	SX1276Write(0x0F,0x00);			//RegFifoRxBaseAddr,默认0x00
	SX1276Write(0x01,0x85);				//Receive continuous
	
	while(1)
	{

		SX1276Read(0x12,&test);		
		if(test==0)
		{
			if(prev==0)
				i++;
			else
				i=0;
			prev=test;
			if(i>0x3ff)
				return 0;
			continue;
		}
		if((test&0x80)==0x80)
		{
			SX1276Write(0x12,0x80);
			return 0;
		}
		else if((test&0x40)==0x40)
		{
			SX1276Write(0x12,0x40);
			SX1276Read(0x1B,&test);

			SX1276Write(0x0D,0x00);			//FifoAddrPtr，Set FifoPtrAddr to FifoRxPtrBase.
			test=0;
			SX1276Read(0x13,&test);
			SX1276ReadBuffer(0x00,RFBuffer,test);
			SX1276Write(0x01,0x81);
			SX1276Write(0x11,0x9F);			//IRQFlagMask
			SX1276Write(0x24,0xFF);			//RegHopPeriod
			return 1;
		}
	}
}

void onmaster(u8 *RFBuffer,u8 length)
{
	SX1276Write(0x01,0x81);			// standby
	SX1276Write(0x24,0x00);			//FreqHoppingPeriod--off
	SX1276Write(0x11,0xF7);			//IRQ
	SX1276Write(0x40,0x40);			//
	SX1276Write(0x22,length);			//payloadLength
	SX1276WriteBuffer(00,RFBuffer,length);// Write PayloadLength bytes to the FIFO (RegFifo)

	SX1276Write(0x01,0x83);
	SX1276Read(0x12,&test);
	if((test&0x08)==0x08)
	{
		SX1276Write(0x12,0x08);
		delay_ms(100);
		SX1276Write(0x01,0x81);
		SX1276Write(0x11,0xF7);			//IRQFlagMask
		SX1276Write(0x01,0x81);
	}
}

void Init_sx1278(void)
{
	u8 test;
	sx1278GPIO_Ini();
	SX1276Read(0x42,&test);
	
	
	SX1276Write(0x01,0x00);			// sleep
	SX1276Write(0x01,0x80);			// Lora
	SX1276Write(0x01,0x81);			// standby
	
	SX1276Write(0x09,0x8F);			//PA:Boost-MAXPower
	SX1276Write(0x4D,0x87);			//PaDac
	
	SX1276Write(0x1D,0x72);			// BW:125kHz CR:4/5
	SX1276Write(0x1E,0x74);			// SF7 CRC:1
	
	SX1276Write(0x26,0x0C);			//LowDataRateOptimize
	SX1276Write(0x0A,0x08);			// 50us PA Ramp-up time
	
	SX1276Write(0x0E,0x80);			//RegFifoTxBaseAddr,默认0x80
	SX1276Write(0x0D,0x80);			//FifoAddrPtr，Set FifoPtrAddr to FifoTxPtrBase.
	
	SX1276Write(0x39,0x34);			//LoRa sync word
	
	SX1276Write(0x41,0x00);			//
}
