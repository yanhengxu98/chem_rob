#include "stm32f10x.h"
#include "EIE3810_zhuxidebug.h"
#include "EIE3810_USART.h"
#include "EIE3810_LED.h"
#include "EIE3810_Timer.h"
#include "EIE3810_Key.h"
#include "EIE3810_zhuxi.h"

// put your procedure and code here

u8 Step1_Start_Flag;
u8 Step2_Start_Flag;
u8 Step3_Start_Flag;
u8 Step4_Start_Flag;

u8 Step1_Done_Flag;
u8 Step2_Done_Flag;
u8 Step3_Done_Flag;


u8 Open_Door_Relay_Flag_Nolink;
u8 Motor_RunOpen_Flag_Nolink;
u8 Close_Door_Relay_Flag_Nolink;
u8 Motor_RunClose_Flag_Nolink;

u8 Step_Run_Flag_Nolink;
u8 Stepmotor1_Reset_Flag_Nolink;

u8 Pump_Jinyang_Flag_Nolink;






void Step1_Process(void)
{
	if(Step1_Start_Flag)
	{
		switch(Step1)
		{
			case 0:
				;                                  // 液体1 标志位   现在蠕动泵没有接                 
			break;
		  
			case 1:
					;                                // 液体2 标志位   现在蠕动泵没有接
				break;
			case 2:
				Pump_Jinyang_Flag_Nolink=1;        // 液体3 标志位   现在蠕动泵  只接了 这一路
				break;
			case 3:
				;                                  // 液体4 标志位    现在蠕动泵没有接
			break;
			
			
			case 4:                              // 固体1 标志位   现在步进电机默认是这一路
				Step_Run_Flag_Nolink=1;
			break;
			case 5:
				;                                  // 固体2 标志位
			break;
			
			case 6:
				;                                  // 固体3 标志位
			break; 
			case 7:
				;                                  // 固体4 标志位
			break;
		
		  default:
				break;
		}	
			
		
	 Step1_Start_Flag=0;		
	 Step2_Start_Flag=1;	
	}	
	
}	


void Step2_Process(void)
{
	if(Step2_Start_Flag)
	{		
		switch(Step2)
		{
			case 0:
				;                                 // 液体1 标志位   现在蠕动泵没有接                 
			break;
			case 1:
				;                                 // 液体2 标志位   现在蠕动泵没有接
			break;
			case 2:
				Pump_Jinyang_Flag_Nolink=1;        // 液体3 标志位   现在蠕动泵  只接了 这一路
			break;
			case 3:
				;                                  // 液体4 标志位    现在蠕动泵没有接
			break;
			
			
			case 4:                              // 固体1 标志位   现在步进电机默认是这一路
				Step_Run_Flag_Nolink=1;
			break;
			case 5:
				;                                  // 固体2 标志位
			break;
			case 6:
				;                                  // 固体3 标志位
			break; 
			case 7:
				;                                  // 固体4 标志位
			break;
		
		  default:
				break;
		}


		
			
	 Step2_Start_Flag=0;		

	 Step3_Start_Flag=1;
			
	}

}
void Step3_Process(void)
{
	if(Step3_Start_Flag)
	{
		switch(Step3)
		{
			case 0:
				;                                  // 液体1 标志位   现在蠕动泵没有接                 
			break;
		  
			case 1:
					;                                // 液体2 标志位   现在蠕动泵没有接
				break;
			case 2:
				Pump_Jinyang_Flag_Nolink=1;        // 液体3 标志位   现在蠕动泵  只接了 这一路
				break;
			case 3:
				;                                  // 液体4 标志位    现在蠕动泵没有接
			break;
			
			
			case 4:                              // 固体1 标志位   现在步进电机默认是这一路
				Step_Run_Flag_Nolink=1;
			break;
			case 5:
				;                                  // 固体2 标志位
			break;
			
			case 6:
				;                                  // 固体3 标志位
			break; 
			case 7:
				;                                  // 固体4 标志位
			break;
		
		  default:
				break;
		}	
			
	 Step3_Start_Flag=0;		
	}		
}

	



void Multi_Jinyang_Process(void)
{
//   u16 static Multi_Count;
//	if(Timer10ms_Flag)
//	{	
//		Multi_Count++;
//		switch(Multi_Count)
//		{
//			case 1:
//			
//			break;
//			
//			case 1400:                   // 第一个需要 14秒
//				
//			break;
//		}	
//	
//	
//	}
	
	
	
 	Step1_Process();

	
	Step2_Process();

	
	Step3_Process();

	
	StepMotor1_Run_Nolink();                      // 
	Pump_Jinyang_Nolink();
	StepMotor_Reset_Nolink();
	
	
}	




void Open_Door_Relay_Nolink(void)      
{
		if(Open_Door_Relay_Flag_Nolink)    //   开门命令，电机默认是关门的，
		{
			  GPIO_SetBits(GPIOE, GPIO_Pin_5);   // 设置方向 电机升起 方向
			  Delay(10000000);
			
			  Open_Door_Relay_Flag_Nolink=0;

		}		
}	


void Open_Motor1_Run_Nolink(void)            //  开门  通过设定PWM波 来 开门电机 BLDC3650 的 速度
{
	u16 static Open_Run_Count;
	if(Motor_RunOpen_Flag_Nolink)
	{
		
		if(Timer10ms_Flag)
		{
			Open_Run_Count++;               // 每 10ms 进来  加 1
			switch(Open_Run_Count)
			{
				case 1:
					BLDC_Motor_Config(359,9);       //  72 000000/ 3600 =  20K  频率 一定上 20K   ---- 50k
					break;
				
				case 2:
					GPIO_SetBits(GPIOF, GPIO_Pin_5);   // 控制电机 上电
					break;
				
				case 1250:                     // 15000ms 之后 15 秒

					GPIO_ResetBits(GPIOF, GPIO_Pin_5);     // 控制电机 断电
					Delay(10000000);
				  GPIO_ResetBits(GPIOE, GPIO_Pin_5);     // 设置方向 复位  回到默认方向状态
					Delay(10000000);
					BLDC_Motor_Config(0,0);	               // 关闭脉冲
				
					Open_Run_Count=0;
					Motor_RunOpen_Flag=0;
				  
				  Send_YuXiao_Start();                             //  发送命令给 宇啸  表示 门 已经  打开了 
					break;
			}
			if (EIE3810_Read_Key2() == KEYON) // TEST
			{
					GPIO_ResetBits(GPIOF, GPIO_Pin_5);     // 控制电机 断电
					Delay(10000000);
				  GPIO_ResetBits(GPIOE, GPIO_Pin_5);     // 设置方向 复位  回到默认方向状态
					Delay(10000000);
					BLDC_Motor_Config(0,0);	               // 关闭脉冲
				
					Open_Run_Count=0;
					Motor_RunOpen_Flag_Nolink=0;
				   
//				  Send_YuXiao_Start();                             //  发送命令给 宇啸  表示 门 已经  打开了 
			}	
			
			Timer10ms_Flag=0;
		}	
	}	
}	




void Close_Door_Relay_Nolink(void)      
{
		if(Close_Door_Relay_Flag_Nolink)               //   开门命令， 默认状态是关门的
		{
			  GPIO_ResetBits(GPIOE, GPIO_Pin_5);   //  复位命令   电机回到默认方向
			  Delay(10000);

			  Close_Door_Relay_Flag_Nolink=0;
//			  Motor_RunClose_Flag=1;            // because this is no-link mode in this .c file
		}		
}	



void Close_Motor1_Run_Nolink(void)                        //   关门 功能， 控制电机 运行  关门
{
	u16 static Close_Run_Count;
	if(Motor_RunClose_Flag_Nolink)
	{
		if(Timer10ms_Flag)
		{
			Close_Run_Count++;
			switch(Close_Run_Count)
			{
				case 1:				
					BLDC_Motor_Config(359,9);
					break;
				
				case 2:
					GPIO_SetBits(GPIOF, GPIO_Pin_5);       // 控制电机 上电
					break;
				
				case 670:
					GPIO_ResetBits(GPIOF, GPIO_Pin_5);     // 控制电机 断电
				
					Delay(10000);
				  
					BLDC_Motor_Config(0,0);
				
					Close_Run_Count=0;
					Motor_RunClose_Flag_Nolink=0;
				
//				  Step_Run_Flag=1;                      // because this is no-link mode in this .c file
					break;
			
			}
			if (EIE3810_Read_Key0() == KEYON) // TEST
			{
					GPIO_ResetBits(GPIOF, GPIO_Pin_5);     // 控制电机 断电
				
					Delay(10000);
				  
					BLDC_Motor_Config(0,0);
				
					Close_Run_Count=0;
					Motor_RunClose_Flag_Nolink=0;          
				
//				  Step_Run_Flag=1;                      // because this is no-link mode in this .c file
			}
			Timer10ms_Flag=0;
			
		}	
	}	
}	





void StepMotor1_Run_Nolink(void)                                 // 电机关门 完毕  可以开始 进样
{
	u16 static Stepmotor1_Run_Count;
	if(Step_Run_Flag_Nolink)                                      // 如果接收到 st 命令 标志位会被置为 1       
	{
		if(Timer10ms_Flag)
		{
			Stepmotor1_Run_Count++;
			switch(Stepmotor1_Run_Count)
			{
				case 1:

					SteppingMotor_Config_1(1439,99);               // 72 000 000 / 720 00 =1000 HZ  发送PWM 		
				
				break;
			  
				case 600:
					SteppingMotor_Config_1(0,0);                  // 2000ms， 经过测试一共可以跑  8个 
				break;
			
				case 800:                                    
					Stepmotor1_Run_Count=0;
				  Step_Run_Flag_Nolink=0;
				  
//				  Stepmotor1_Reset_Flag=1;                   // because this is the no-link mode
				  GPIOB->BSRR|=(1<<5);                            // 步进电机 Direction 置高, 方向翻转 与 LED0 公用一路 IO
				break;
			}
			if (EIE3810_Read_PE0() == KEYON)				// TEST
			{
				SteppingMotor_Config_1(0,0);
				Delay(10000000);
				Stepmotor1_Run_Count=0;
				Step_Run_Flag_Nolink=0;
				  
				Stepmotor1_Reset_Flag_Nolink=1;
				GPIOB->BSRR|=(1<<5);                            // 步进电机 Direction 置高, 方向翻转 与 LED0 公用一路 IO
			}	
				Timer10ms_Flag=0;
		}	
	}	
}	



void StepMotor_Reset_Nolink(void)                            //   步进电机 进样完成之后  退回原来的位置
{
	u16 static Stepmotor_Reset_Count;
	if(Stepmotor1_Reset_Flag_Nolink)
	{
		if(Timer10ms_Flag)
		{
			Stepmotor_Reset_Count++;
			switch(Stepmotor_Reset_Count)
			{
				case 1:
//					SteppingMotor_Config_1(719,99);
					SteppingMotor_Config_1(1439,99);               // 72 000 000 / 720 00 =1000 HZ  发送PWM 				
				break;
			
				case 600:
					SteppingMotor_Config_1(0,0);
				
				break;
			  case 800:
					Stepmotor1_Reset_Flag_Nolink=0;
				  Stepmotor_Reset_Count=0;
				  
//				  Pump_Jinyang_Flag=1;
				  GPIOB->BRR|=(1<<5);                           // 运行结束  复位 PB5
				break;
			
			}	
			if (EIE3810_Read_PE1() == KEYON)
			{
				SteppingMotor_Config_1(0,0);
				Delay(10000000);
				Stepmotor1_Reset_Flag_Nolink=0;
				Stepmotor_Reset_Count=0;				  
//				Pump_Jinyang_Flag=1;
				GPIOB->BRR|=(1<<5);                           // 运行结束  复位 PB5
			}
				
			Timer10ms_Flag=0;
		}	

	}	

}	



void Pump_Jinyang_Nolink(void)               //  这里 最多需要完成 4 通道
{
  u16 static Pump_Jinyang_Count;    
	if(Pump_Jinyang_Flag_Nolink)
	{
	                    
		if(Timer10ms_Flag)								//  开始蠕动泵1 通道的进样
		{
			Pump_Jinyang_Count++;
			switch(Pump_Jinyang_Count)
			{
				case 1:
          GPIO_SetBits(GPIOF, GPIO_Pin_3);				// 
					break;
				
				case 100:
					GPIO_ResetBits(GPIOF, GPIO_Pin_3); //  闭合继电器   蠕动泵开始 进样  PF3 置 高电平
					break;
				
				case 200:
					GPIO_SetBits(GPIOF, GPIO_Pin_3); //  闭合继电器   蠕动泵开始 进样  PF3 置 高电平
					break;
				
				case 1100:                    //   30秒 = 30 000 = 3000 个 10ms
          GPIO_ResetBits(GPIOF, GPIO_Pin_3);                             //   断开继电器				PF5 置  低电平
					Pump_Jinyang_Count=0;
				  Pump_Jinyang_Flag_Nolink=0;

//				  Send_YunKai();             //    发送命令  给 云开  可以开始   进行加热 程序
          System_Heat_Flag=1;			
				break;
			
			}	
			Timer10ms_Flag=0;
			
		}
	}	
}
