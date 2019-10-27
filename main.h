#ifndef _main_H_
#define _main_H_
#include "reg51.h"
#define uchar unsigned char
#define uint unsigned int
extern bit motor1_right_flag;
extern bit motor1_left_flag;
sbit LED = P3^3;
/*
  DC MOTOR
*/
sbit IA = P1^0;
sbit IB = P1^1;
/*
	STEPPER MOTOR
*/
sbit CP1 = P1^2;
sbit DIR1= P1^3;
sbit EN1 = P1^4;
sbit CP2 = P1^5;
sbit DIR2 = P1^6;
sbit EN2 = P1^7;

sbit SV = P2^4;
sbit SH = P2^5;
sbit CLY1 = P2^6;
sbit CLY2 = P2^7;
sbit LEFTLIMIT = P2^0;
sbit RIGHTLIMIT = P2^2;
sbit UPLIMIT = P2^1;
sbit UNDERLIMIT = P2^3;
sbit SW1 = P3^4;
sbit SW2 = P3^5;
sbit SW3 = P3^6;
sbit SW4 = P3^7;
void timer_init();
extern bit time_flag;//时间倒计时标志
extern bit start_flag;//启动标志
extern bit test_run;//测试运行标志
extern bit end_flag;//
extern bit end_flag1;//
extern void end_judge(void);
extern float hour,hour1,hour2,hour3,hour4;
extern void time_switch(void);
#endif
