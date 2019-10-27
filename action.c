#include "action.h"
//#include "motor.h"
#include "main.h"
#include "reg51.h"


bit motor1_right_flag=0;
bit motor1_left_flag=0;
bit motor2_right_flag=0;
bit motor2_left_flag=0;
bit SV_flag=0;//垂直光电开关标志位
bit SV_flag1=0;//垂直光电开关标志位
bit SH_flag=0;
bit SH_flag1=0;
bit time_flag=1;//时间倒计时标志
bit start_flag=0;//启动标志
bit test_run=0;//测试运行标志
bit end_flag=0;
bit end_flag1=0;
bit continue_flag=0;
bit continue_flag1=0;
float hour,hour1,hour2,hour3,hour4;

void init(void)
{
  time_flag=1;//时间倒计时标志
  start_flag=0;//启动标志
  test_run=0;//测试运行标志
	motor1_right_flag=0;
	motor1_left_flag=0;
	motor2_right_flag=0;
	motor2_left_flag=0;
	SV_flag=0;//垂直光电开关标志位
	SV_flag1=0;//垂直光电开关标志位
	SH_flag=0;
	SH_flag1=0;
	end_flag=0;
	end_flag1=0;
}

void act1(uchar n)
{
	n=index;
	if(n==0)
	{
		CLY1 = 0;
		if(LEFTLIMIT==0&&RIGHTLIMIT==1)//右转
			motor1_right_flag=1;	
		if(LEFTLIMIT==1&&RIGHTLIMIT==0)//左转
			motor1_left_flag=1;	
			do{
				if(motor1_right_flag==1)
				{
					stepper_motor(1, 1, 0);//forward
				}
				if(motor1_left_flag==1)
				{
					stepper_motor(1, 0, 0);//reserve
				}			
				if(SH_flag1==0)
				{
					if(SH==0)//
					{	
						SH_flag=0;	//
						SH_flag1=1;
					}
					else    
						SH_flag=1;				
				}
				if(SH==1)
					SH_flag1=0;
				
				if(end_flag==1)
				{
					if(LEFTLIMIT==0||RIGHTLIMIT==0)
					{					
						end_flag1=1;
						continue_flag1=1;
						break;
					}	
				}		
			}while(SH_flag==1);
			stepper_motor(0, 0, 0);//MOTOR STOP			
			SH_flag=1;
			index=1;
			if(continue_flag==1)
			{	
				if(continue_flag1==1)
				{
					end_flag=0;
					index=0;
					continue_flag1=0;
				}
			}
	}	
}

void act2(uchar n)
{
	n=index;
	if(n==1)
	{
		if(UPLIMIT==0)//
		{
			motor2_left_flag = 1;
		}
		while(UNDERLIMIT==1)
		{		
			do{
				if(motor2_left_flag == 1)
				{
					CLY2=0;
					stepper_motor(1, 1, 1);
					dc_motor(1,0);
				}
				
				if(SV_flag1==0)
				{
					if(SV==0)//
					{	
						SV_flag=0;	//DC MOTOR STOP
						SV_flag1=1;
					}
					else    
						SV_flag=1;				
				}
				if(SV==1)
					SV_flag1=0;			
					
				if(UNDERLIMIT==0)
					break;
			}while(SV_flag==1);
			if(UNDERLIMIT==0)
					break;
			stepper_motor(0, 1, 1);		
			dc_motor(0,0);
			delay(5000);		
			SV_flag=1;
		}
		motor2_right_flag = 1;
		motor2_left_flag = 0;	
		index=2;
	}

}

void act3(uchar n)
{
	n=index;
	if(n==2)
	{
		do{
			if(motor2_right_flag==1)//上升标志
			{									
				stepper_motor(1, 0, 1);//步进电机上升
				dc_motor(0,1);//直流电机上升
			}		
		}while(UPLIMIT==1);//碰到上限位跳出
		stepper_motor(0, 0, 1);//
		dc_motor(0,0);//
		CLY2=1;//上下继电器释放
		delay(2000);
		end_flag=1;
		test_run=0;
		index=0;
	}

}


void time_switch(void)
{
	if(SW1==0)hour1=0.5 ;	else hour1=0;
	if(SW2==0)hour2=1 ;		else hour2=0;
	if(SW3==0)hour3=2 ;		else hour3=0;
	if(SW4==0)hour4=4 ;		else hour4=0;
	if((SW1==1)&&(SW2==1)&&(SW3==1)&&(SW4==1))
	{
		time_flag=0;
		start_flag=1;
		continue_flag=1;
	}
	hour=hour1+hour2+hour3+hour4;
}
