#include "motor.h"
#include <reg51.h>
#include "main.h"

void stepper_motor(int en, int dir, int num)
{
	/*
		horizontal motor
	*/
	if(num==0)
	{
		EN1  = en;
		DIR1 = dir;
	
	}
	/*
		vertical motor
	*/
	if(num==1)
	{
		EN2  = en;
		DIR2 = dir;		

	}	
}

void dc_motor(int a, int b)
{
	IA=a;
	IB=b;
}

void timer3() interrupt 3 using 3
{	
	//uchar i;
	TH1=(65535-100)/256;
	TL1=(65535-100)%256;
	
	if(EN1==1)
		CP1=!CP1;
	else
		CP1=0;
	if(EN2==1)
		CP2=!CP2;
	else
		CP2=0;
}
