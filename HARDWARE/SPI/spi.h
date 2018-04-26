#ifndef __SPI_H
#define __SPI_H
#include "sys.h"

void static delay(void);
void SX1276Read(uint8_t Addr,uint8_t *data);
void SX1276ReadBuffer(uint8_t Addr, uint8_t *buf, uint8_t count);
void SX1276WriteBuffer(uint8_t Addr,uint8_t *buf,uint8_t count);
void SX1276Write(uint8_t Addr,uint8_t V);
void sx1278GPIO_Ini(void);

#endif

