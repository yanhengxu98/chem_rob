#ifndef __EIE3810_KEY_H
#define __EIE3810_KEY_H
#include "stm32f10x.h"

#define KEYOFF 0
#define KEYON 1

void EIE3810_KEY_Init(void);
u8 EIE3810_Read_Key2(void);
u8 EIE3810_Read_Key1(void);
u8 EIE3810_Read_Key0(void);
u8 EIE3810_Read_PE1(void);
u8 EIE3810_Read_PE0(void);

u8 EIE3810_Read_KeyUp(void);

u8 EIE3810_KEY_Scan(void);

#endif
