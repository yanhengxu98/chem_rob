#include "stm32f10x.h"
#include "EIE3810_KEY.h"

// put your procedure and code here


void EIE3810_KEY_Init(void)
{
	RCC->APB2ENR |= 0x00000044;  // Enable GPIOA and GPIOE

	GPIOA->CRL &= 0xFFFFFFF0;    // Key_up (PA0)
	GPIOA->CRL |= 0x00000008;
	GPIOA->BSRR=(1<<16);         // Reset ODR bit0 for pull down 
	 
	GPIOE->CRL &= 0xFFF00000;    // Key2 PE2, Key1 PE3 PE4: Key0 PE0, PE1
	GPIOE->CRL |= 0x00088888;
	GPIOE->BSRR=(1<<0)|(1<<1)|(1<<2)|(1<<3)|(1<<4)|(1<<6);   // Set ODR bit2 and bit 3 for pull up   add bit 4
}


u8 EIE3810_Read_Key2(void)
{
	u32 temp;
	temp=GPIOE->IDR;
	if (((temp>>2)&0x0001)==1)
	{
		return KEYOFF;
	}
	else
	{
		return KEYON;
	}	
}


u8 EIE3810_Read_Key1(void)
{
	u32 temp;
	temp=GPIOE->IDR;
	if (((temp>>3)&0x0001)==1)         //not pressed
	{
		return KEYOFF;
	}
	else
	{
		return KEYON;
	}	
}

u8 EIE3810_Read_Key0(void)
{
	u32 temp;
	temp=GPIOE->IDR;
	if (((temp>>4)&0x0001)==1)         //not pressed
	{
		return KEYOFF;
	}
	else
	{
		return KEYON;
	}	

}	

u8 EIE3810_Read_PE0(void) //  READ PE0
{
	u32 temp;
	temp=GPIOE->IDR;
	if (((temp>>0)&0x0001)==1)         //not pressed
	{
		return KEYOFF;
	}
	else
	{
		return KEYON;
	}	

}	

u8 EIE3810_Read_PE1(void)  // READ PE1
{
	u32 temp;
	temp=GPIOE->IDR;
	if (((temp>>1)&0x0001)==1)         //not pressed
	{
		return KEYOFF;
	}
	else
	{
		return KEYON;
	}	

}	

u8 EIE3810_Read_KeyUp(void)
{
	u32 temp;
	temp=GPIOA->IDR;
	if ((temp&0x0001)==1)          // pressed
	{
		return KEYON; 
	}
	else
	{
		return KEYOFF;
	}	
}



u8 EIE3810_KEY_Scan(void)
{	 
  u32 tempA,tempE;
	tempA=GPIOA->IDR;
	tempE=GPIOE->IDR;
	if (((tempE>>2)&0x0001)==0)   //  key2
	{
		return 3;
	}
	if (((tempE>>3)&0x0001)==0) 
	{
		return 2;
	}	
	if (((tempE>>4)&0x0001)==0) 
	{
		return 1;
	}	
	if ((tempA&0x0001)==1) 
	{
		return 4;
	}	
 	return 0;// 无按键按下
}
