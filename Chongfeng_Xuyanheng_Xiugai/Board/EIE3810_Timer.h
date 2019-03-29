#ifndef __EIE3810_TIMER_H
#define __EIE3810_TIMER_H
#include "stm32f10x.h"

// put header here

u8 extern Timer10ms_Flag;
u8 extern Timer10ms_Flag_2;
u8 extern Timer10ms_Flag_3;
u8 extern Timer10ms_Flag_4;
u8 extern Timer20ms_Flag;
u8 extern Timer100ms_Flag;


u8 extern Usart1_CountDown;
u8 extern Usart2_CountDown;


void EIE3810_TIM3_Init(u16 arr, u16 psc);
void TIM4_IRQHandler(void);

void TIM3_PWM_Init(u16 arr,u16 psc);
void TIM2_ETR_Init(u16 arr,u16 psc);
void EIE3810_TIM4_Init(u16 arr, u16 psc);
void TIM4_IRQHandler(void);



void SteppingMotor_Config_1(u16 arr1,u16 psc1);
void SteppingMotor_Config_2(u16 arr2,u16 psc2);
void BLDC_Motor_Config(u16 arr3,u16 psc3);

#endif
