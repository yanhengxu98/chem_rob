#include "stm32f10x.h"
#include "EIE3810_ADC.h"




void EIE3810_ADC_Init(void)
{    
	
 	RCC->APB2ENR|=1<<2;                  // Enable portA clock
	GPIOA->CRL&=0XFFFFFF0F;              // PA1 
	RCC->APB2ENR|=1<<9;                  // Enable ADC1 clock
	RCC->APB2RSTR|=1<<9;                 // ADC1 reset
	RCC->APB2RSTR&=~(1<<9);              // reset finished
	RCC->CFGR&=~(3<<14);                 // 
	//SYSCLK/DIV2=12M   set adc clock to 12M, the maximum is 14M
	//?????ADC?????! 
	RCC->CFGR|=2<<14;                     //  	 
	ADC1->CR1&=0XF0FFFF;                  //??????
	ADC1->CR1|=0<<16;                     //??????  
	ADC1->CR1&=~(1<<8);                   //?????	  
	ADC1->CR2&=~(1<<1);                   //??????
	ADC1->CR2&=~(7<<17);	   
	ADC1->CR2|=7<<17;	                    //??????  
	ADC1->CR2|=1<<20;                     //???????(SWSTART)!!!	???????????
	ADC1->CR2&=~(1<<11);                  //???	 
	ADC1->SQR1&=~(0XF<<20);
	ADC1->SQR1|=0<<20;                    //1????????? ??????????1 			   
	//????1?????
	ADC1->SMPR2&=~(3*1);                  //??1??????	  
 	ADC1->SMPR2|=7<<(3*1);                //??1  239.5??,?????????????	 
	ADC1->CR2|=1<<0;	                    //??AD???	 
	ADC1->CR2|=1<<3;                      //??????  
	while(ADC1->CR2&1<<3);                //?????? 			 
                                        //???????????????????????????????? 		 
	ADC1->CR2|=1<<2;                      //	   
	while(ADC1->CR2&1<<2);                //??????
	                                      //????????????,????????????  
}	






u16 EIE3810_Get_ADC(u8 ch)   
{
  		 
	ADC1->SQR3&=0XFFFFFFE0;//????1 ??ch
	ADC1->SQR3|=ch;		  			    
	ADC1->CR2|=1<<22;       //???????? 
	while(!(ADC1->SR&1<<1));//??????	 	   
	return ADC1->DR;		//??adc?	
}



