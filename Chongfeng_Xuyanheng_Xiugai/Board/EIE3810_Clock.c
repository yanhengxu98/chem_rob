//
// Created by Licheng Mao on 08/03/2018.
//

#include "EIE3810_Clock.h"

void EIE3810_clock_tree_init(void)
{
    u8 PLL = 7;
    u8 temp = 0;
    RCC->CR |= 0x00010000; // HSE set to ON
    while (!((RCC->CR >> 17) & 0x1));// block until HSE RDY
    RCC->CFGR &= 0xFFFDFFFF; // PLLXTPRE to 0, HSE not divided
    RCC->CFGR |= 1 << 16; // PLLSRC to 1, HSE as PLL input
    RCC->CFGR |= PLL << 18; // PLLMUL to 9, input clk 9x
    RCC->CR |= 0x01000000; // PLLON to 1, enable PLL
    while (!(RCC->CR >> 25)); // block until PLL RDY
    RCC->CFGR &= 0xFFFFFFFE; // SW[0] to 0
    RCC->CFGR |= 0x00000002; // SW[1] to 1, combine together: SW = 10, PLL as system clock
    while (temp != 0x02) // block until temp = 0x02 (PLL as system clock ready)
    {
        temp = RCC->CFGR >> 2; // combine with next command
        temp &= 0x03; // let temp = SWS
    }
    RCC->CFGR &= 0xFFFFFC0F; // HPRE[3:0] = 0000; PPRE1[2:0] = X00  SYSCLK not divided
    RCC->CFGR |= 0x00000400; // PRPE1[2:0] = 100; PCLK1 = HCLK divided by 2

    RCC->CFGR &= 0xFFFFDFFF; // E2: PRPE2[2:0] = 0XX; PCLK2 = HCLK not divided

    FLASH->ACR = 0x32; // Set FLASH with 2 wait states
    RCC->APB1ENR |= 1 << 17; // USART2 enable

    RCC->APB2ENR |= 1 << 14; // E2: USART1 enable (page 112 RM0008)  
		
}

