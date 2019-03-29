#ifndef __EIE3810_MYOWN_H
#define __EIE3810_MYOWN_H

#include "stm32f10x.h"

// put header here

u8 extern Timer1s_Flag;
u8 extern Game_InitFlag;

u8 extern Role_Server;
u8 extern Role_Catcher;

u8 extern First_StepFlag;
u8 extern Second_StepFlag;
u8 extern Get_RandomFlag;
u8 extern Game_RunFlag;
u8 extern Game_OverFlag;

u8 extern Game_RunningFlag;
u8 extern Game_StoppingFlag;

u8 extern Game_Stop_Restart;
u8 extern Game_Stop_Exit;

u8 extern Need_Random_Flag;
u8 extern Show_Random_Flag;

/****  加入音效   ****/

u8 extern Game_TitleFlag_Beep;
u8 extern Game_InitFlag_Beep_Step2;

/***   实验记录   ****/

u8 extern Game_Round_Record;
u32 extern Game_Time_Using;
u8 extern Game_Time_1s;
u8 extern Game_Time_1mins;


/*****   位置数据   *******/
u16 extern Temp,Cursor_x,Cursor_y;      // 下挡块的 光标点
u8 extern Key_value;                          

u16 extern Cursor_x2,Cursor_y2;           // 上挡块的 光标点 (画矩形程序的形参)
u8 extern Joypad_value;

u16 extern x_speed,y_speed;                 //   弹球的速度 会被随机数更新掉

u16 extern x_move,y_move;               //   弹球的起始位置



void EIE3810_Peripheral_Check(void); // use this subroutine to check each peripheral

void EIE3810_Game_Init(void);
void First_Step(void);
void Need_Random_Value(void);
void Second_Step(void);
void Show_Random_Seed(void);
void Game_Countdown(void);

void EIE3810_Get_Random(void);
void EIE3810_Game_Run(void);
void EIE3810_GameAgain(void);
void EIE3810_Reflection_Judge(void);
void EIE3810_TFTLCD_ShowString_Beep(u16 x,u16 y,u8 *p, u16 color, u16 bgcolor);
#endif
