#include <stm32f10x.h>
#include "EIE3810_Clock.h"
#include "EIE3810_USART.h"
#include "EIE3810_LED.h" 
#include "EIE3810_Buzzer.h"
#include "EIE3810_Key.h"
#include "EIE3810_Timer.h"
#include "EIE3810_TFTLCD.h"
#include "EIE3810_Myown.h"
#include "EIE3810_Joypad.h"
#include "EIE3810_zhuxi.h"
#include "EIE3810_zhuxidebug.h"

// put your code here
// this is all the code designed for Professor Zhuxi and programming by Yanheng and Chongfeng based on STM32 Developing Board


/*****   测试串口打开磁力搅拌器  OK    *****/


/*****   2018-5-22   开始测试直流无刷电机  开关门    ******/


/***** 2018-6-5 在彦恒 基础上  增加功能程序:  多种样品 进样

固体 液体 编号为：

        液体1     液体2     液体3（蠕动泵3，已接）    液体4    固体1（步进电机）   固体2   固体3    固体4
编号：    0         1         2                         3        4                   5       6        7 


依据协议： 如收到数据： 23     03            02      05    05      04      0A      05      02    05    05   24
对应：                  头   种类数         样品1  1用量  1速度   样品2  2用量   2速度   样品3 3用量  3速度  尾
即：                      （有3种试剂要进） 液体3                 固体1                  液体3

那么动作顺序为：   蠕动泵3  进样  之后，  步进电机进样 固体  之后，   蠕动泵3 再  进样

目前 暂时没有对试剂 的进样量  和  进样速度  进行 处理

********/

int main(void) 
{
		EIE3810_LED_Init();
	  GPIO_Config_Relay();
	  EIE3810_Buzzer_Init();
		EIE3810_KEY_Init();
    EIE3810_clock_tree_init();
	  EIE3810_NVIC_SetPriorityGroup(5);     // interrupt group     
	
	  EIE3810_USART1_ExtiInit();
	  EIE3810_USART2_ExtiInit();
	  
    EIE3810_USART1_init(72, 9600);
    EIE3810_USART2_init(36, 9600);
	
	  EIE3810_TIM4_Init(7199,99);           //  99 equals to 10ms  timer

    
		while(1)  
	  {
/*****   磁力搅拌器的  测试数据   FE B2 03 E8 00 9D     ****/			
			#if 1			
				Receive_Process();
			#endif
			
			
			#if 1			                         //   如果改成 0  则 不执行 后面的程序
//			Open_Door_Relay();
//			Open_Motor1_Run();                 //   开门
//			Close_Door_Relay();
//			Close_Motor1_Run();
//			
//			StepMotor1_Run();
//			StepMotor_Reset();
			
			// Pump_Jinyang();
			Pump_1_pumping();
			Pump_2_pumping();
			Pump_4_pumping();
			Pump_3_pumping();
//			System_Heat_Run(); 
//			Over_Open_Door_Relay();
//			Over_Open_Motor1_Run();
//			Experiment_Over();
			#endif
			                                  // 温度 上传指令  
			#if 0
			
			 Multi_Jinyang_Process();
			
			#endif
      						
		}  	
}






