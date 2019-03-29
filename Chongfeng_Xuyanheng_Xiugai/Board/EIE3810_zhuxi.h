#ifndef __EIE3810_ZHUXI_H
#define __EIE3810_ZHUXI_H

#include "stm32f10x.h"

// put header here

#define LED0_PWM_VAL  TIM3->CCR2



extern u8 Open_Door_Relay_Flag;                     //  ¿ªÃÅ          ¼ÌµçÆ÷
extern u8 Close_Door_Relay_Flag;                    //  ¹ØÃÅ          ¼ÌµçÆ÷

extern u8 Motor_RunOpen_Flag;                       //  ¿ªÃÅµç»úÔË×ª ±êÖ¾  
extern u8 Motor_RunClose_Flag;                      //  ¹ØÃÅµç»úÔË×ª ±êÖ¾

extern u8 Step_Run_Flag;                            //  ½øÑù²½½øµç»úÔË×ª±êÖ¾  
extern u8 Stepmotor1_Reset_Flag;                    //  ½øÑù²½½øµç»ú¸´Î»±êÖ

extern u8 Pump_1_start_Flag;														// four triggers for four pumps
extern u8 Pump_2_start_Flag;
extern u8 Pump_3_start_Flag;
extern u8 Pump_4_start_Flag;

extern u8 Tenth_bit;
extern u8 One_bit;
extern u8 Point_bit;

extern u8 Pump_Jinyang_Flag;                        //  Èä¶¯±Ã½øÑù±êÖ¾
extern u8 System_Heat_Flag;                         //  ÏµÍ³¼ÓÈÈ±êÖ¾  

extern u8 UV_Lamp_Open_Flag;                        //  ×ÏÍâµÆ
extern u8 Heat_Flag;   
extern u8 Stir_Heat_Flag;                           //  ´ÅÁ¦½Á°è ¼ÓÈÈ

extern u8 Over_Open_Door_Relay_Flag;
extern u8 Over_Motor_RunOpen_Flag;
extern u8 Experiment_Over_Flag;                     //  ÊµÑé½áÊøµÄ±êÖ¾


extern u8 Liquid_Number0;                           // 1 ºÅÒºÌå
extern u8 Liquid_Number1;                           // 2 ºÅÒºÌå
extern u8 Liquid_Number2;                           // 3 ºÅÒºÌå
extern u8 Liquid_Number3;                           // 4 ºÅÒºÌå

extern u8 Solid_Number0;                            // 1 ºÅ¹ÌÌå
extern u8 Solid_Number1;                            // 2 ºÅ¹ÌÌå
extern u8 Solid_Number2;                            // 3 ºÅ¹ÌÌå
extern u8 Solid_Number3;                            // 4 ºÅ¹ÌÌå

extern u8 Step1;
extern u8 Step2;
extern u8 Step3;




void Delay(u32 count) ;


void Send_YuXiao_Start(void);
void Send_YuXiao_Over(void);

void Send_YunKai(void);

void Receive_Process(void);


void Open_Door_Relay(void); 

void Open_Motor1_Run(void);


void Close_Door_Relay(void);

void Close_Motor1_Run(void); 

void StepMotor1_Run(void); 
	
void StepMotor_Reset(void);

void Pump_Jinyang(void);

void Pump_1_pumping(void);
void Pump_2_pumping(void);
void Pump_3_pumping(void);
void Pump_4_pumping(void);

void System_Heat_Run(void); 

void Over_Open_Door_Relay(void);
void Over_Open_Motor1_Run(void);
void Experiment_Over(void);


#endif
