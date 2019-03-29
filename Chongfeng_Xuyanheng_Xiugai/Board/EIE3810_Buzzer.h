#ifndef __EIE3810_BUZZER_H
#define __EIE3810_BUZZER_H
#include "stm32f10x.h"

// put header here

void EIE3810_Buzzer_Init(void);
void EIE3810_BuzzerToggle(void);

void EIE3810_Buzzer_On(void);
void EIE3810_Buzzer_Off(void);

#endif
