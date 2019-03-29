#include "stm32f10x.h"
#include "EIE3810_Joypad.h"

// put your code here


void EIE3810_JOYPAD_Init(void)
{	
 	RCC->APB2ENR|=1<<3;//Add comments 
 	RCC->APB2ENR|=1<<5;//Add comments 
	GPIOB->CRH&=0XFFFF00FF;//Add comments 
	GPIOB->CRH|=0X00003800;//Add comments      
	GPIOB->ODR|=3<<10; //Add comments 
	GPIOD->CRL&=0XFFFF0FFF;	//Add comments 
	GPIOD->CRL|=0X00003000; //Add comments     
	GPIOD->ODR|=1<<3; //Add comments 
	
}

void JOYPAD_Delay(u16 t)
{
	while(t--);
}


u8 EIE3810_JOYPAD_Read(void)
{
	vu8 temp=0;
 	u8 t;
	GPIOB->BSRR |= 1<<11;//Add comments
 	JOYPAD_Delay(80);//Add comments
	GPIOB->BSRR |= 1<<27;//Add comments
	for(t=0;t<8;t++)
	{
		temp>>=1;	 //Add comments
		if((((GPIOB->IDR)>>10)&0x01)==0) temp|=0x80; //Add comments
		GPIOD->BSRR |= (1<<3);	//Add comments
		JOYPAD_Delay(80); //Add comments
		GPIOD->BSRR |= (1<<19);	//Add comments
		JOYPAD_Delay(80); //Add comments
	}
	return temp;
}

