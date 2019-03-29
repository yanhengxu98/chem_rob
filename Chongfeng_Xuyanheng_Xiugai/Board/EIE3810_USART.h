//
// Created by Licheng Mao on 08/03/2018.
//

#ifndef LAB_EIE3810_USART_H
#define LAB_EIE3810_USART_H

#include "stm32f10x.h"
#include "EIE3810_LED.h"
#include "stm32f10x_usart.h"

#define DS1_ON GPIOE->ODR |= 0x00000020;            
#define DS1_OFF GPIOE->ODR &= 0xFFFFFFDF; 


u8 extern Usart1_Buffer[100];      //  接收缓冲
u8 extern USART1_Length;           //  接收长度
u8 extern USART1_RX_FinishFlag;     //  接收完成标志位

u8 extern Usart2_Buffer[100];     //  接收数据缓冲区
u8 extern USART2_Length;        //  接收长度
u8 extern USART2_RX_FinishFlag;    //  接收完成标志位


void EIE3810_USART3_init(u32 pclk1, u32 baudrate);
void EIE3810_USART2_init(u32 pclk1, u32 baudrate);
void EIE3810_USART1_init(u32 pclk1, u32 baudrate);
void USART_print(u8 USARTPort, char *st);




void EIE3810_NVIC_SetPriorityGroup(u8 prigroup);


void EIE3810_USART1_ExtiInit(void);
void USART1_IRQHandler(void);



void EIE3810_USART2_ExtiInit(void);
void USART2_IRQHandler(void);








#endif //LAB_EIE3810_USART_H
