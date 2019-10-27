#include<reg51.h>
#include<intrins.h>
#include "main.h"
#include "motor.h"
//#include "delay.h"
#include "action.h"


uchar i=0;//
uchar s=0;//
uchar m=0;//
uchar index=0;


void main(void)
{
	timer_init();//timer initialization
	stepper_motor(0,0,0);
	init();	
	while(1)
	{		
		index=0;	
		motor1_left_flag=0;
		motor1_right_flag=0;
		while(start_flag==1)
		{								
			act1(index); 	
			if(end_flag1==1)
				break;			
			act2(index);
			act3(index);				
		}
		CLY1=1;
	}
}

void timer_init()
{
	TMOD|=0X11;
	TH0=(65535-50000)/256;
	TL0=(65535-50000)%256;
	TH1=(65535-100)/256;
	TL1=(65535-100)%256;
	EA=1;
	ET0=1;TR0=1;
	ET1=1;TR1=1;
	IT0=1;
	EX0=1;
}

void int0() interrupt 0 using 0
{
	start_flag=1;
	time_flag=0;
	test_run=1;
	end_flag1=0;
	end_flag=0;
}	

void timer1() interrupt 1 using 1      //0.0358 3800
{		
	float hour1=0;
  i++; //0.0358 5400	
	time_switch();
	hour1=hour;
		if(time_flag==1) 
		{		
			if(i>=20) // 
			{					
				i=0;
				s++;
				if(s>=46) 
				{
					m++;				
					s=0;          
				}//一分钟
				if(m>=30) 
				{
					m=0;
					hour1=hour1-0.5;
				}//30分钟			
			}	
		}
		if(hour1<=0) //
		{
			start_flag=1;//小车启动	
			time_flag=0;//倒计时停止		
			end_flag1=0;			
		}
		
	if(end_flag1==1)
	{	
		if(hour>0)
		{
			start_flag=0;
			time_flag=1;
		}		
	}
	
	if(time_flag==1)
		LED = 0;
	else 
		LED = 1;
	
	if(test_run==1)
		LED=1;		
}

