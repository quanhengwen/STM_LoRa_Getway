#ifndef __SPI_H
#define __SPI_H
#include "sys.h"

// 				  	    													  
//void SPI1_Init(void);			 //��ʼ��SPI��
//void SPI1_SetSpeed(u8 SpeedSet); //����SPI�ٶ�   
//u8 SPI1_ReadWriteByte(u8 TxData);//SPI���߶�дһ���ֽ�
//u8 SPI_Write_Byte(u8 data);
void static delay(void);

void SX1276Read(uint8_t Addr,uint8_t *data);
void SX1276ReadBuffer(uint8_t Addr, uint8_t *buf, uint8_t count);
void SX1276WriteBuffer(uint8_t Addr,uint8_t *buf,uint8_t count);
void SX1276Write(uint8_t Addr,uint8_t V);
void sx1278GPIO_Ini(void);
void Init_sx1278(void);
#endif

