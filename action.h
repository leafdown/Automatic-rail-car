#ifndef _action_H_
#define _action_H_
#define uchar unsigned char
#define uint unsigned int
	
void end_judge(void);
void time_switch(void);
void act1(uchar n);
void act2(uchar n);
void act3(uchar n);
extern void stepper_motor(int en, int dir, int num);
extern void dc_motor(int a, int b);
extern void delay(uint z);
extern void init(void);
extern uchar index;
#endif
