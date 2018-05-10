#ifndef __SX1278_H
#define __SX1278_H
#include "head.h"

void Init_sx1278(void);
void onmaster(u8 *RFBuffer, u8 length);
u8 onslave(u8 *RFBuffer);
#endif

