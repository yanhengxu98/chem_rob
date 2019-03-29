#include "stm32f10x.h"
#include "EIE3810_Buzzer.h"

// put your procedure and code here

void EIE3810_Buzzer_Init(void)
{
	RCC->APB2ENR|=0x00000008; //Enable GPIOB for buzzer
	GPIOB->CRH &= 0xFFFFFFF0; //Buzzer PB8
	GPIOB->CRH |= 0x00000003;
	GPIOB->ODR &= 0xFFFFFEFF;//Set to turn off buzzer; you can also use GPIOB->BSRR |= 1<<24
}


void EIE3810_BuzzerToggle(void)
{
	GPIOB->ODR ^= 1<<8; 
}

void EIE3810_Buzzer_On(void)
{
   GPIOB->BSRR |= 1<<8;
}	

void EIE3810_Buzzer_Off(void)
{
	GPIOB->BSRR |= 1<<24;
}	
