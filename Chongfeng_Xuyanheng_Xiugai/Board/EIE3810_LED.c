#include "stm32f10x.h"
#include "EIE3810_LED.h"

// put your code here

void EIE3810_LED_Init(void)
{
	RCC->APB2ENR|=0x00000048; // LED0 PB5, LED1 PE5
	GPIOB->CRL &= 0xFF0FFFFF; //Configure PB5 to output 50MHz
	GPIOB->CRL |= 0x00300000;
	GPIOE->CRL &= 0xFF0FFFFF; //Configure PE5 to output 50MHz
	GPIOE->CRL |= 0x00300000;	
//	GPIOB->BSRR|=(1<<5);//Set to turn off LED0
//	GPIOE->BSRR|=(1<<5);//Set to turn off LED1
	 GPIOB->BRR|=(1<<5);      // 设置 PB5 初始化 低电平
	 GPIOE->BRR|=(1<<5);      // 设置 PE5 初始化 低电平
}


void GPIO_Config_Relay(void)                                //  用语控制继电器的 IO Inition 
{
    GPIO_InitTypeDef GPIO_InitStructure;                 

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF|RCC_APB2Periph_GPIOA, ENABLE);  

  
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_4|GPIO_Pin_3|GPIO_Pin_2|GPIO_Pin_1|GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;        
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;        
    GPIO_Init(GPIOF, &GPIO_InitStructure);  
	  GPIO_ResetBits(GPIOF, GPIO_Pin_5|GPIO_Pin_4|GPIO_Pin_3|GPIO_Pin_2|GPIO_Pin_1|GPIO_Pin_0);    	//   初始化 置 0	
	
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;        
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;        
    GPIO_Init(GPIOA, &GPIO_InitStructure);  

		GPIO_ResetBits(GPIOA, GPIO_Pin_7);                        //   初始化 置 0  
	  
}



void EIE3810_LED0_On(void)
{
	GPIOB->BSRR = 1<<21;
}
	
void EIE3810_LED0_Off(void)
{
	GPIOB->BSRR = 1<<5;
}

void EIE3810_LED1_On(void)
{
	GPIOE->BSRR = 1<<21;
}
	
void EIE3810_LED1_Off(void)
{
	GPIOE->BSRR = 1<<5;
}


void EIE3810_LED1_Toggle(void)
{
	GPIOE->ODR ^= 1<<5;
}
