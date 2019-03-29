#ifndef __EIE3810_LED_H
#define __EIE3810_LED_H
#include "stm32f10x.h"

// put header here

void EIE3810_LED_Init(void);
void EIE3810_LED0_On(void);
void EIE3810_LED0_Off(void);	
void EIE3810_LED1_Toggle(void);

void EIE3810_LED1_On(void);

void EIE3810_LED1_Off(void);


void GPIO_Config_Relay(void);                                //  用语控制继电器的 IO Inition 


#endif
