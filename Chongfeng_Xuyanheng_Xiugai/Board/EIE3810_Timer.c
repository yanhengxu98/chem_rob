#include "stm32f10x.h"
#include "EIE3810_Timer.h"
#include "EIE3810_USART.h"
// put your code here

u8 Timer10ms_Flag;
u8 Timer10ms_Flag_2;
u8 Timer10ms_Flag_3;
u8 Timer10ms_Flag_4;

u8 Timer20ms_Flag;
u8 Timer100ms_Flag;


u8 Usart1_CountDown;       // 用来给定时间，一旦串口收到数据就设置1， 如果检测到 为 0
u8 Usart2_CountDown;


void EIE3810_TIM3_Init(u16 arr, u16 psc)
{
	RCC->APB1ENR |=1<<1;    //  TIM3  enable
	TIM3->ARR=arr;
	TIM3->PSC=psc;
	TIM3->DIER |=1<<0;
	TIM3->CR1 |=0X01;  
	NVIC->IP[29] = 0X45;
	NVIC->ISER[0] |= (1<<29);    // specify interrupt number  29
	
}	


void TIM3_IRQHandler(void)
{
	if(TIM3->SR & 1<<0)
		  TIM3->SR &= ~(1<<0);
}


//TIM3 PWM 初始化
//arr  重装载值
//psc  分频系数

void TIM3_PWM_Init(u16 arr,u16 psc)
{
    GPIO_InitTypeDef     GPIO_InitStrue;
    TIM_OCInitTypeDef     TIM_OCInitStrue;
    TIM_TimeBaseInitTypeDef     TIM_TimeBaseInitStrue;
    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);        // enable TIM3 and GPIO
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);        
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
   
		GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3,ENABLE);        // 部分重映射  TIM3-CH2   映射到  PB5  
  
    GPIO_InitStrue.GPIO_Pin=GPIO_Pin_5;     
    GPIO_InitStrue.GPIO_Mode=GPIO_Mode_AF_PP;    
    GPIO_InitStrue.GPIO_Speed=GPIO_Speed_50MHz;    
    GPIO_Init(GPIOB,&GPIO_InitStrue);                
    

    TIM_TimeBaseInitStrue.TIM_Period=arr;    
    TIM_TimeBaseInitStrue.TIM_Prescaler=psc;        
    TIM_TimeBaseInitStrue.TIM_CounterMode=TIM_CounterMode_Up;    
    TIM_TimeBaseInitStrue.TIM_ClockDivision=TIM_CKD_DIV1;       
    TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStrue);        
    
    TIM_OCInitStrue.TIM_OCMode=TIM_OCMode_PWM2;                
    TIM_OCInitStrue.TIM_OCPolarity=TIM_OCPolarity_High;        
    TIM_OCInitStrue.TIM_OutputState=TIM_OutputState_Enable;    
    TIM_OC2Init(TIM3,&TIM_OCInitStrue);                       

    TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable);           
    
    TIM_Cmd(TIM3,ENABLE);                                     
    
}
	



void EIE3810_TIM4_Init(u16 arr, u16 psc)
{
	RCC->APB1ENR |=1<<2;    //     TIM4 enable
	TIM4->ARR=arr;
	TIM4->PSC=psc;
	TIM4->DIER |=1<<0;
	TIM4->CR1 |=0X01;
	NVIC->IP[30] = 0X45;
	NVIC->ISER[0] |= (1<<30);   //  specify interrupt number  29
	
	Usart1_CountDown=0;
	Usart2_CountDown=0;
	
}	


void TIM4_IRQHandler(void)
{
	if(TIM4->SR & 1<<0)
  {
		int static i,j;	
		
		Timer10ms_Flag=1;
		Timer10ms_Flag_2=1;
		Timer10ms_Flag_3=1;
		Timer10ms_Flag_4=1;
		/*i++;
		j++;
		if(i>1)
		{
			Timer20ms_Flag=1;
			i=0;
		}	
		if(j>10)
		{
			j=0;
			Timer100ms_Flag=1;
		}	*/
		
		if(Usart1_CountDown)
		{ 
			if(--Usart1_CountDown==0)
			{	
				USART1_RX_FinishFlag=1;
			}
		}	
		/*
		if(Usart2_CountDown)
		{ 
			if(--Usart2_CountDown==0)
			{	
				USART2_RX_FinishFlag=1;
			}
		}		*/

  TIM4->SR &= ~(1<<0);
	}	

}


//****************步进电机1控制********************//
void SteppingMotor_Config_1(u16 arr1,u16 psc1)                      //  TIM3    CH3   PB0
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;
    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); 
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;                 
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&GPIO_InitStructure);
////PA1用来控制步进电机1的方向
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;    
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//    GPIO_Init(GPIOA,&GPIO_InitStructure);
//	
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);     //开启重映射时钟
//	  GPIO_PinRemapConfig(GPIO_PartialRemap2_TIM2,ENABLE);     //设置TIM2的部分映射
	
    //定时器初始化，向上计数
    TIM_TimeBaseStructure.TIM_Prescaler =arr1;                  
    TIM_TimeBaseStructure.TIM_Period =psc1;                  
    TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);          
                                                                      
    //输出比较初始化
    TIM_OCStructInit(& TIM_OCInitStructure);

    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_Pulse =50;                      //设置50%的占空比
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;    
    TIM_OC3Init(TIM3, &TIM_OCInitStructure);
    TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);
    TIM_ARRPreloadConfig(TIM3,ENABLE);
    TIM_Cmd(TIM3, ENABLE);
    TIM_CtrlPWMOutputs(TIM3, ENABLE); 
}


//void SteppingMotorControl_1(u8 dir)                     //正反转控制
//{

//    if(0==dir)
//    {
//        GPIO_ResetBits(GPIOA,GPIO_Pin_1);     //逆时针旋转
//    }
//    else
//    {
//        GPIO_SetBits(GPIOA,GPIO_Pin_1);         //顺时针旋转
//    }
//}



//*********     步进电机2控制   ********//
void SteppingMotor_Config_2(u16 arr2,u16 psc2)      //   PB1    TIM3 -  CH4
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;
    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); 
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;                 
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&GPIO_InitStructure);
////PA2用来控制步进电机1的方向
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3; 
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//    GPIO_Init(GPIOA,&GPIO_InitStructure);
//	
//	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);     //开启重映射时钟
//	  GPIO_PinRemapConfig(GPIO_PartialRemap2_TIM2,ENABLE);     //设置TIM2的部分映射

    //定时器初始化，向上计数
    TIM_TimeBaseStructure.TIM_Prescaler =arr2;                  
    TIM_TimeBaseStructure.TIM_Period =psc2;                  
    TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);          
                                                                      
    //输出比较初始化
    TIM_OCStructInit(& TIM_OCInitStructure);

    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_Pulse =50;                      //设置50%的占空比
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;    
    TIM_OC4Init(TIM3, &TIM_OCInitStructure);
    TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);
    TIM_ARRPreloadConfig(TIM3,ENABLE);
    TIM_Cmd(TIM3, ENABLE);
     
}


//************** 开关门电机控制     *******************//
void BLDC_Motor_Config(u16 arr1,u16 psc1)         //      TIM2   CH2  PA1
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;
    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); 
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;                 
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);
////PA1用来控制步进电机1的方向
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;    
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//    GPIO_Init(GPIOA,&GPIO_InitStructure);
//	
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);     //开启重映射时钟
//	  GPIO_PinRemapConfig(GPIO_PartialRemap2_TIM2,ENABLE);     //设置TIM2的部分映射
	
    //定时器初始化，向上计数
    TIM_TimeBaseStructure.TIM_Prescaler =arr1;                  
    TIM_TimeBaseStructure.TIM_Period =psc1;                  
    TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);          
                                                                      
    //输出比较初始化
    TIM_OCStructInit(& TIM_OCInitStructure);

    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_Pulse =5;                      //设置3%的占空比
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;    
    TIM_OC2Init(TIM2, &TIM_OCInitStructure);
    TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);
    TIM_ARRPreloadConfig(TIM2,ENABLE);
    TIM_Cmd(TIM2, ENABLE);
    TIM_CtrlPWMOutputs(TIM2, ENABLE); 
}






//TIM2_CH2 PWM 部分初始化
//PWM输出初始化
//arr:自动装载值
//psc: 预分频系数
void TIM2_ETR_Init(u16 arr,u16 psc)
{ 
//????????IO???
RCC->APB1ENR|=1<<0; //TIM2???? 
RCC->APB2ENR|=1<<2; //??PORTA?? 

GPIOA->CRL &= 0XFFFFFF0F; //
GPIOA->CRL |= 0X00000080; //PA1???? 
GPIOA->ODR |= 0<<1; 

TIM2->ARR=arr; //?????????? 
TIM2->PSC=psc; //???????

TIM2->CCMR1|=1<<8; //CC2S=01 ????? IC1???TI2?
TIM2->CCMR1|=0<<12; //IC2F=0000 ??????? ?Fck_int??
TIM2->CCMR1|=0<<10; //IC2PS=00 ??????,???

TIM2->CCER |=0<<5; //CC2P=0 ?????
TIM2->SMCR |=0X07<<0; //SMS =111 
TIM2->SMCR |=0X06<<4; //TS =110 

TIM2->CR1 |= 0x01; //?????1 
}

