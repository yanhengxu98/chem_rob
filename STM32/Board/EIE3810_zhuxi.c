#include "stm32f10x.h"
#include "EIE3810_zhuxi.h"
#include "EIE3810_USART.h"
#include "EIE3810_LED.h"
#include "EIE3810_Timer.h"
#include "EIE3810_Key.h"
#include "EIE3810_zhuxidebug.h"

// put your procedure and code here


u8 Yuxiao_Start[]={0x23,0x23,0x23};          // 告知 宇 啸 门已经打开了    
u8 Yuxiao_Over[]={0x24,0x24,0x24};           // 告知 宇 啸 实验结束了，门 已经打开了

u8 Yunkai[]={0x26,0x26,0x26};                // 告知 云开 实验进样完成了 可以开始 加热实验了

u8 Open_Door_Relay_Flag;                     //  开门          继电器
u8 Close_Door_Relay_Flag;                    //  关门          继电器

u8 Motor_RunOpen_Flag;                       //  开门电机运转 标志  
u8 Motor_RunClose_Flag;                      //  关门电机运转 标志

u8 Step_Run_Flag;                            //  进样步进电机运转标志  
u8 Stepmotor1_Reset_Flag;                    //  进样步进电机复位标志

u8 Pump_1_start_Flag;														// four triggers for four pumps
u8 Pump_2_start_Flag;
u8 Pump_3_start_Flag;
u8 Pump_4_start_Flag;

u16 static Pump_1_starter;                  // record the start time of each pump
u16 static Pump_2_starter; 
u16 static Pump_3_starter; 
u16 static Pump_4_starter;

u16 static Pump_1_timer;
u16 static Pump_2_timer; 
u16 static Pump_3_timer; 
u16 static Pump_4_timer; // operate these 4 variables to measure time

u8 Pump_Jinyang_Flag;                        //  蠕动泵进样标志
u8 System_Heat_Flag;                         //  系统加热标志  

u8 UV_Lamp_Open_Flag;                        //  紫外灯加
u8 Stir_Heat_Flag;                           //  磁力搅拌 加热

u8 Over_Open_Door_Relay_Flag;                //  
u8 Over_Motor_RunOpen_Flag;                  // 

u8 Experiment_Over_Flag;                     //  实验结束的标志

u8 Tenth_bit;
u8 One_bit;
u8 Point_bit;

u8 Start_Tenth_bit;
u8 Start_One_bit;
u8 Start_Point_bit;

u8 Liquid_Number0;                           // 1 号液体
u8 Liquid_Number1;                           // 2 号液体
u8 Liquid_Number2;                           // 3 号液体
u8 Liquid_Number3;                           // 4 号液体

u8 Solid_Number0;                            // 1 号固体
u8 Solid_Number1;                            // 2 号固体
u8 Solid_Number2;                            // 3 号固体
u8 Solid_Number3;                            // 4 号固体

u8 Step1;                                    // 第一步数值  保存第一步 进样 的样品编号
u8 Step2;
u8 Step3;


void Delay(u32 count) 
{
    u32 i;
    for (i = 0; i < count; i++);
}

void Send_YuXiao_Start(void)                // 发送 开门完成 命令 给 宇啸
{
	u8 i;
  for(i=0;i<sizeof(Yuxiao_Start);i++)
  {
			USART1->DR = Yuxiao_Start[i];
			while (!((USART1->SR >> 7) & 0x1));
	}
}	

void Send_YuXiao_Over(void)
{
	u8 i;
  for(i=0;i<sizeof(Yuxiao_Over);i++)
  {
			USART1->DR = Yuxiao_Over[i];
			while (!((USART1->SR >> 7) & 0x1));
	}
}	


void Send_YunKai(void)                // 发送 进样完成命令给 云开
{
	u8 i;
  for(i=0;i<sizeof(Yunkai);i++)
  {
			USART1->DR = Yunkai[i];
			while (!((USART1->SR >> 7) & 0x1));
	}
}	


void Send_Experiment_Over(void)
{
	u8 i;
  for(i=0;i<sizeof(Yunkai);i++)
  {
			USART1->DR = Yunkai[i];
			while (!((USART1->SR >> 7) & 0x1));
	}
}	




void Receive_Process(void)
{
#if 0
	
		if(USART1_RX_FinishFlag)	           //   串口1 接收 数据  串口 2 发送出来  
		{
			int j;
			for(j=0;j<USART1_Length;j++)
			{
			USART2->DR = Usart1_Buffer[j];
			while (!((USART2->SR >> 7) & 0x1))
				;
				EIE3810_LED0_On();   
			}
			USART1_RX_FinishFlag=0;
			USART1_Length=0;
			
			EIE3810_LED0_Off();		
		}
#endif		
		
		#if 1
		
		if(USART1_RX_FinishFlag)	                               //   串口1 接收 数据  串口 1 发送出来  
		{
			int j;
			if(USART1_Length<=3)
	    {
					if(Usart1_Buffer[0]=='#' && Usart1_Buffer[1]=='$')     // 接收到 #$  启动开门程序
					{
//						Open_Door_Relay_Flag=1;                              // 开门启动标志位，先将继电器上电	
						Step_Run_Flag=1;
									for(j=0;j<USART1_Length;j++)
									{
									USART1->DR = Usart1_Buffer[j];
									while (!((USART1->SR >> 7) & 0x1))
										;
										EIE3810_LED0_On();   
									}
						
					}
					
					if(Usart1_Buffer[0]=='$' && Usart1_Buffer[1]=='$')     
					{			
						;
					}			
					
					if(Usart1_Buffer[0]=='y' && Usart1_Buffer[1]=='x')     //  接收到宇啸 机械臂完成进样的命令
					{
						Close_Door_Relay_Flag=1;                             //  可以开始关门了  
					}		
					

					
					if(Usart1_Buffer[0]=='s' && Usart1_Buffer[1]=='t')
					{
						Step_Run_Flag=1;
					}
					
// here, we need to add 4 conponent to control 4 pumps
			    if(Usart1_Buffer[0]=='p' && Usart1_Buffer[1]=='1')
					{
						Pump_1_start_Flag=1;
						Pump_1_starter = 0;
						Pump_1_timer = 9999;
					}	
					
					if(Usart1_Buffer[0]=='p' && Usart1_Buffer[1]=='2')
					{
						Pump_2_start_Flag=1;
						Pump_2_starter = 0;
						Pump_2_timer = 9999;
					}	
					
					if(Usart1_Buffer[0]=='p' && Usart1_Buffer[1]=='3')
					{
						Pump_3_start_Flag=1;
						Pump_3_starter = 0;
						Pump_3_timer = 9999;
					}	
					
					if(Usart1_Buffer[0]=='p' && Usart1_Buffer[1]=='4')
					{
						Pump_4_start_Flag=1;
						Pump_4_starter = 0;
						Pump_4_timer = 9999;
					}
					
					if(Usart1_Buffer[0]=='s' && Usart1_Buffer[1]=='1')
					{
						Pump_1_start_Flag=2;
						Pump_1_timer = 9999;

					}
					if(Usart1_Buffer[0]=='s' && Usart1_Buffer[1]=='2')
					{
						Pump_2_start_Flag=2;
						Pump_2_timer = 9999;

					}
					if(Usart1_Buffer[0]=='s' && Usart1_Buffer[1]=='3')
					{
						Pump_3_start_Flag=2;
						Pump_3_timer = 9999;
					}
					if(Usart1_Buffer[0]=='s' && Usart1_Buffer[1]=='4')
					{
						Pump_4_start_Flag=2;
						Pump_4_timer = 9999;
					}
					
					if(Usart1_Buffer[0]=='u' && Usart1_Buffer[1]=='v')      
					{
						UV_Lamp_Open_Flag=1;
					}

					
					if(Usart1_Buffer[0]=='v' && Usart1_Buffer[1]=='u')
					{
						UV_Lamp_Open_Flag=0;
					}
			}		
			
			/************* Send something like: p1300, means to let p1 run for 30 seconds.  ***********/					
					if(USART1_Length==9)
					{
						if (Usart1_Buffer[0] == '#')
						{
							switch(Usart1_Buffer[3])
							{
								case '0': Start_Tenth_bit=0; break;
								case '1': Start_Tenth_bit=1; break;
								case '2': Start_Tenth_bit=2; break;
								case '3': Start_Tenth_bit=3; break;
								case '4': Start_Tenth_bit=4; break;
								case '5': Start_Tenth_bit=5; break;
								case '6': Start_Tenth_bit=6; break;
								case '7': Start_Tenth_bit=7; break;
								case '8': Start_Tenth_bit=8; break;
								case '9': Start_Tenth_bit=9; break;
							  default: Start_Tenth_bit=0; break;
						  }
							
							switch(Usart1_Buffer[4])
							{
								case '0': Start_One_bit=0; break;
								case '1': Start_One_bit=1; break;
								case '2': Start_One_bit=2; break;
								case '3': Start_One_bit=3; break;
								case '4': Start_One_bit=4; break;
								case '5': Start_One_bit=5; break;
								case '6': Start_One_bit=6; break;
								case '7': Start_One_bit=7; break;
								case '8': Start_One_bit=8; break;
								case '9': Start_One_bit=9; break;
							  default: Start_One_bit=0; break;
						  }
							
							switch(Usart1_Buffer[5])
							{
								case '0': Start_Point_bit=0; break;
								case '1': Start_Point_bit=1; break;
								case '2': Start_Point_bit=2; break;
								case '3': Start_Point_bit=3; break;
								case '4': Start_Point_bit=4; break;
								case '5': Start_Point_bit=5; break;
								case '6': Start_Point_bit=6; break;
								case '7': Start_Point_bit=7; break;
								case '8': Start_Point_bit=8; break;
								case '9': Start_Point_bit=9; break;
							  default: Start_Point_bit=0; break;
						  }	
							switch(Usart1_Buffer[6])
							{
								case '0': Tenth_bit=0; break;
								case '1': Tenth_bit=1; break;
								case '2': Tenth_bit=2; break;
								case '3': Tenth_bit=3; break;
								case '4': Tenth_bit=4; break;
								case '5': Tenth_bit=5; break;
								case '6': Tenth_bit=6; break;
								case '7': Tenth_bit=7; break;
								case '8': Tenth_bit=8; break;
								case '9': Tenth_bit=9; break;
							  default: Tenth_bit=0; break;
						  }
							
							switch(Usart1_Buffer[7])
							{
								case '0': One_bit=0; break;
								case '1': One_bit=1; break;
								case '2': One_bit=2; break;
								case '3': One_bit=3; break;
								case '4': One_bit=4; break;
								case '5': One_bit=5; break;
								case '6': One_bit=6; break;
								case '7': One_bit=7; break;
								case '8': One_bit=8; break;
								case '9': One_bit=9; break;
							  default: One_bit=0; break;
						  }
							
							switch(Usart1_Buffer[8])
							{
								case '0': Point_bit=0; break;
								case '1': Point_bit=1; break;
								case '2': Point_bit=2; break;
								case '3': Point_bit=3; break;
								case '4': Point_bit=4; break;
								case '5': Point_bit=5; break;
								case '6': Point_bit=6; break;
								case '7': Point_bit=7; break;
								case '8': Point_bit=8; break;
								case '9': Point_bit=9; break;
							  default: Point_bit=0; break;
						  }	

							if(Usart1_Buffer[1]=='p' && Usart1_Buffer[2]=='1')
							{
								Pump_1_start_Flag=1;
								Pump_1_starter = 1000 * Start_Tenth_bit + 100 * Start_One_bit + 10 * Start_Point_bit;
								Pump_1_timer = 1000 * Tenth_bit + 100 * One_bit + 10 * Point_bit;
							}	
					
							if(Usart1_Buffer[1]=='p' && Usart1_Buffer[2]=='2')
							{
								Pump_2_start_Flag=1;
								Pump_2_starter = 1000 * Start_Tenth_bit + 100 * Start_One_bit + 10 * Start_Point_bit;
								Pump_2_timer = 1000 * Tenth_bit + 100 * One_bit + 10 * Point_bit;
							}	
					
							if(Usart1_Buffer[1]=='p' && Usart1_Buffer[2]=='3')
							{
								Pump_3_start_Flag=1;
								Pump_3_starter = 1000 * Start_Tenth_bit + 100 * Start_One_bit + 10 * Start_Point_bit;
								Pump_3_timer = 1000 * Tenth_bit + 100 * One_bit + 10 * Point_bit;

							}
							
							if(Usart1_Buffer[1]=='p' && Usart1_Buffer[2]=='4')
							{
								Pump_4_start_Flag=1;
								Pump_4_starter = 1000 * Start_Tenth_bit + 100 * Start_One_bit + 10 * Start_Point_bit;
								Pump_4_timer = 1000 * Tenth_bit + 100 * One_bit + 10 * Point_bit;
							}									
						}	
					}		
			
			USART1_RX_FinishFlag=0;
			USART1_Length=0;
			
	}
		
	#endif
	

}
/*******  控制BLDC3650 

需要一个IO控制继电器    上电控制  PF14
需要一个IO控制方向      方向控制  PF13

*******/

void Open_Door_Relay(void)      
{
		if(Open_Door_Relay_Flag)    //   开门命令，电机默认是关门的，
		{
			  GPIO_SetBits(GPIOE, GPIO_Pin_5);   // 设置方向 电机升起 方向
			  Delay(10000000);
			
			  Open_Door_Relay_Flag=0;
			  Motor_RunOpen_Flag=1;
			
		}		
}	


void Open_Motor1_Run(void)            //  开门  通过设定PWM波 来 开门电机 BLDC3650 的 速度
{
	u16 static Open_Run_Count;
	if(Motor_RunOpen_Flag)
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
					Motor_RunOpen_Flag=0;
				   
				  Send_YuXiao_Start();                             //  发送命令给 宇啸  表示 门 已经  打开了 
			}	
			
			Timer10ms_Flag=0;
		}	
	}	
}	




void Close_Door_Relay(void)      
{
		if(Close_Door_Relay_Flag)               //   开门命令， 默认状态是关门的
		{
			  GPIO_ResetBits(GPIOE, GPIO_Pin_5);   //  复位命令   电机回到默认方向
			  Delay(10000);

			  Close_Door_Relay_Flag=0;
			  Motor_RunClose_Flag=1;
		}		
}	



void Close_Motor1_Run(void)                        //   关门 功能， 控制电机 运行  关门
{
	u16 static Close_Run_Count;
	if(Motor_RunClose_Flag)
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
					Motor_RunClose_Flag=0;
				
				  Step_Run_Flag=1;
					break;
			
			}
			if (EIE3810_Read_Key0() == KEYON) // TEST
			{
					GPIO_ResetBits(GPIOF, GPIO_Pin_5);     // 控制电机 断电
				
					Delay(10000);
				  
					BLDC_Motor_Config(0,0);
				
					Close_Run_Count=0;
					Motor_RunClose_Flag=0;
				
				  Step_Run_Flag=1;
			}
			Timer10ms_Flag=0;
			
		}	
	}	
}	


// 3.25 modification:


void StepMotor1_Run(void)                                 // 电机关门 完毕  可以开始 进样
{
	u16 static Stepmotor1_Run_Count;
	if(Step_Run_Flag)                                      // 如果接收到 st 命令 标志位会被置为 1       
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
				  Step_Run_Flag=0;
				  
				  Stepmotor1_Reset_Flag=1;
				  GPIOB->BSRR|=(1<<5);                            // 步进电机 Direction 置高, 方向翻转 与 LED0 公用一路 IO
				break;
			}
			if (EIE3810_Read_PE0() == KEYON)				// TEST
			{
				SteppingMotor_Config_1(0,0);
				Delay(10000000);
				Stepmotor1_Run_Count=0;
				Step_Run_Flag=0;
				  
				Stepmotor1_Reset_Flag=1;
				GPIOB->BSRR|=(1<<5);                            // 步进电机 Direction 置高, 方向翻转 与 LED0 公用一路 IO
			}	
				Timer10ms_Flag=0;
		}	
	}	
}	




void StepMotor_Reset(void)                            //   步进电机 进样完成之后  退回原来的位置
{
	u16 static Stepmotor_Reset_Count;
	if(Stepmotor1_Reset_Flag)
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
					Stepmotor1_Reset_Flag=0;
				  Stepmotor_Reset_Count=0;
				  
				  Pump_Jinyang_Flag=1;
				  GPIOB->BRR|=(1<<5);                           // 运行结束  复位 PB5
				break;
			
			}	
			if (EIE3810_Read_PE1() == KEYON)
			{
				SteppingMotor_Config_1(0,0);
				Delay(10000000);
				Stepmotor1_Reset_Flag=0;
				Stepmotor_Reset_Count=0;				  
				// Pump_Jinyang_Flag=1;
				GPIOB->BRR|=(1<<5);                           // 运行结束  复位 PB5
			}
				
			Timer10ms_Flag=0;
		}	

	}	

}	



void Pump_Jinyang(void)               //  这里 最多需要完成 4 通道
{
  u16 static Pump_Jinyang_Count;    
	if(Pump_Jinyang_Flag)
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
          GPIO_ResetBits(GPIOF, GPIO_Pin_3);                             //   断开继电器				PF3 置  低电平
					Pump_Jinyang_Count=0;
				  Pump_Jinyang_Flag=0;

				  Send_YunKai();             //    发送命令  给 云开  可以开始   进行加热 程序
          System_Heat_Flag=1;			
				break;
			
			}	
			Timer10ms_Flag=0;
			
		}
	}	
}

void Pump_1_pumping(void)               
{
	u16 static Pump_Jinyang_Count_1; 
	if(Pump_1_start_Flag == 1)
	{
	                    
		if(Timer10ms_Flag)								//  开始蠕动泵1通道的进样
		{
			Pump_Jinyang_Count_1++;
			if (Pump_Jinyang_Count_1 == Pump_1_starter + 1)     GPIO_SetBits(GPIOF, GPIO_Pin_0);
			else if (Pump_Jinyang_Count_1 == Pump_1_starter + 10) GPIO_ResetBits(GPIOF, GPIO_Pin_0);
			else if (Pump_Jinyang_Count_1 == Pump_1_starter + 20) 	GPIO_SetBits(GPIOF, GPIO_Pin_0);
			else if (Pump_Jinyang_Count_1 >= Pump_1_starter + Pump_1_timer)
			{
				  GPIO_ResetBits(GPIOF, GPIO_Pin_0);              
					Pump_Jinyang_Count_1=0;
				  Pump_1_start_Flag=0;
					Pump_1_timer = 9999;
			}
			Timer10ms_Flag=0;
		}
	}	else if (Pump_1_start_Flag == 2)
		{
			GPIO_ResetBits(GPIOF, GPIO_Pin_0);
			Pump_Jinyang_Count_1=0;
			Pump_1_start_Flag=0;
			Pump_1_timer = 9999;
			Pump_1_starter = 0;
			Timer10ms_Flag=0;
		}
}

void Pump_2_pumping(void)               
{
	u16 static Pump_Jinyang_Count_2; 
	if(Pump_2_start_Flag == 1)
	{
	                    
		if(Timer10ms_Flag_2)								//  开始蠕动泵1通道的进样
		{
			Pump_Jinyang_Count_2++;
			if (Pump_Jinyang_Count_2 == Pump_2_starter + 1)     GPIO_SetBits(GPIOF, GPIO_Pin_1);
			else if (Pump_Jinyang_Count_2 == Pump_2_starter + 10) GPIO_ResetBits(GPIOF, GPIO_Pin_1);
			else if (Pump_Jinyang_Count_2 == Pump_2_starter + 20) 	GPIO_SetBits(GPIOF, GPIO_Pin_1);
			else if (Pump_Jinyang_Count_2 >= Pump_2_starter + Pump_2_timer)
			{
				  GPIO_ResetBits(GPIOF, GPIO_Pin_1);              
					Pump_Jinyang_Count_2=0;
				  Pump_2_start_Flag=0;
					Pump_2_timer = 9999;
			}
			Timer10ms_Flag_2=0;
		} 
	} 
	else if (Pump_2_start_Flag == 2)
	{
			GPIO_ResetBits(GPIOF, GPIO_Pin_1);
			Pump_Jinyang_Count_2=0;
			Pump_2_start_Flag=0;
			Pump_2_timer = 9999;
		  Pump_2_starter = 0;
			Timer10ms_Flag_2=0;
	}	
}

void Pump_3_pumping(void)               //  这里 最多需要完成 4 通道
{
	u16 static Pump_Jinyang_Count_3; 
	if(Pump_3_start_Flag)
	{
	                    
		if(Timer10ms_Flag_3 == 1)								
		{
			Pump_Jinyang_Count_3++;
			if (Pump_Jinyang_Count_3 == Pump_3_starter + 1)     GPIO_SetBits(GPIOF, GPIO_Pin_3);
			else if (Pump_Jinyang_Count_3 == Pump_3_starter + 10) GPIO_ResetBits(GPIOF, GPIO_Pin_3);
			else if (Pump_Jinyang_Count_3 == Pump_3_starter + 20) 	GPIO_SetBits(GPIOF, GPIO_Pin_3);
			else if (Pump_Jinyang_Count_3 >= Pump_3_starter + Pump_3_timer)
			{
				  GPIO_ResetBits(GPIOF, GPIO_Pin_3);              
					Pump_Jinyang_Count_3=0;
				  Pump_3_start_Flag=0;
					Pump_3_timer = 9999;
			}
			Timer10ms_Flag_3=0;
			
		} else if (Pump_3_start_Flag == 2)
		{
			GPIO_ResetBits(GPIOF, GPIO_Pin_3);
			Pump_Jinyang_Count_3=0;
			Pump_3_start_Flag=0;
			Pump_3_timer = 9999;
			Pump_3_starter = 0;
			Timer10ms_Flag_3=0;
		}
	}	
}


void Pump_4_pumping(void)               //  这里 最多需要完成 4 通道
{
	u16 static Pump_Jinyang_Count_4; 
	if(Pump_4_start_Flag)
	{
	                    
		if(Timer10ms_Flag_4 == 1)								
		{
			Pump_Jinyang_Count_4++;
			if (Pump_Jinyang_Count_4 == Pump_4_starter + 1)     GPIO_SetBits(GPIOF, GPIO_Pin_2);
			else if (Pump_Jinyang_Count_4 == Pump_4_starter + 10) GPIO_ResetBits(GPIOF, GPIO_Pin_2);
			else if (Pump_Jinyang_Count_4 == Pump_4_starter + 20) 	GPIO_SetBits(GPIOF, GPIO_Pin_2);
			else if (Pump_Jinyang_Count_4 >= Pump_4_starter + Pump_4_timer)
			{
				  GPIO_ResetBits(GPIOF, GPIO_Pin_2);              
					Pump_Jinyang_Count_4=0;
				  Pump_4_start_Flag=0;
					Pump_4_timer = 9999;
			}
			Timer10ms_Flag_4=0;
			
		} else if (Pump_4_start_Flag == 2)
		{
			GPIO_ResetBits(GPIOF, GPIO_Pin_2);
			Pump_Jinyang_Count_4=0;
			Pump_4_start_Flag=0;
			Pump_4_timer = 9999;
			Pump_4_starter = 0;
			Timer10ms_Flag_4=0;
		}
	}	
}



void System_Heat_Run(void)             //  如果进入了 系统加热状态 处理云开那边 过来的数据  串口 接收  处理程序
{
	u16 static System_Heat_Count;
	if(System_Heat_Flag)
	{   
		  if(Timer10ms_Flag)
      {
				System_Heat_Count++;
				switch(System_Heat_Count)
				{
					case 1:
						GPIO_SetBits(GPIOA, GPIO_Pin_7);              // 模拟紫外灯控制
					break;
					
					case 200:
						GPIO_ResetBits(GPIOA, GPIO_Pin_7);           //  模拟紫外灯控制
					break;
				
					case 300:
						System_Heat_Count=0;
					  System_Heat_Flag=0;
					
					  
						Over_Open_Door_Relay_Flag=1;              
					break;
				
				}	
			
				Timer10ms_Flag=0;	
				
			}
	}	
}	


/*********  2018-6-5  增加  演示的程序  

	模拟进样完成之后， 实验 进行结束  开门 发送命令  给 宇啸，  同时可以 接收 宇啸 结束的  关门程序   *******/

void Over_Open_Door_Relay(void)      
{
		if(Over_Open_Door_Relay_Flag)    //   开门命令，电机默认是关门的，
		{
			  GPIO_SetBits(GPIOE, GPIO_Pin_5);   // 设置方向 电机升起 方向
			  Delay(10000000);
			
			  Over_Open_Door_Relay_Flag=0;
			  Over_Motor_RunOpen_Flag=1;
			
		}		
}	


void Over_Open_Motor1_Run(void)            //  开门  通过设定PWM波 来 开门电机 BLDC3650 的 速度
{
	u16 static Over_Open_Run_Count;
	if(Over_Motor_RunOpen_Flag)
	{
		
		if(Timer10ms_Flag)
		{
			Over_Open_Run_Count++;               // 每 10ms 进来  加 1
			switch(Over_Open_Run_Count)
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
				
					Over_Open_Run_Count=0;
					Over_Motor_RunOpen_Flag=0;
				  
				  Send_YuXiao_Over();                             //  发送命令给 宇啸  表示 门 已经  打开了 
					break;
			}
			if (EIE3810_Read_Key2() == KEYON) // TEST
			{
					GPIO_ResetBits(GPIOF, GPIO_Pin_5);     // 控制电机 断电
					Delay(10000000);
				  GPIO_ResetBits(GPIOE, GPIO_Pin_5);     // 设置方向 复位  回到默认方向状态
					Delay(10000000);
					BLDC_Motor_Config(0,0);	               // 关闭脉冲
				  
					Over_Open_Run_Count=0;
					Over_Motor_RunOpen_Flag=0;
				   
				  Send_YuXiao_Over();                             //  发送命令给 宇啸  表示 门 已经  打开了 
			}	
			
			Timer10ms_Flag=0;
		}	
	}	
}	



void Experiment_Over(void)
{
	u8 static Over_Flag_Count;
  if(Experiment_Over_Flag)
  {
	   if(Timer10ms_Flag)
		 {
			 Over_Flag_Count++;
			switch(Over_Flag_Count)
			{
				case 1:
					;
				break;
				
				case 2:
					;
				break;
			
			
			}

		 Timer10ms_Flag=0;
			
		 } 
	}		
}	








void Temp_Upload(void)
{
	
		if(Timer10ms_Flag)								//  开始蠕动泵1 通道的进样
		{
     ;
			Timer10ms_Flag=0;	 	
		}
   

}










