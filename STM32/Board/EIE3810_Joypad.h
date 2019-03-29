#ifndef __EIE3810_JOYPAD_H
#define __EIE3810_JOYPAD_H

#include "stm32f10x.h"

// put header here

void EIE3810_JOYPAD_Init(void);
void JOYPAD_Delay(u16 t);

u8 EIE3810_JOYPAD_Read(void);



#endif
