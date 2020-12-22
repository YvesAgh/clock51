#include "reg52.h"
#include "clock.h"
#include "show.h"
Clock clock;
void ClockInit(int hour,int min,int sec){
	clock.hour=hour;
	clock.min=min;
	clock.sec=sec;
}
Clock* GetClock(){
	return &clock;
}

void ClockAdd(){
	clock.sec++;
}

void ClockUpdate(){
	if(clock.sec>=60){
		clock.sec=0;
		clock.min++;
	}
	if(clock.min>=60){
		clock.min=0;
		clock.hour++;
	}
	if(clock.hour>=24){
		clock.hour=0;
	}
}
int IsIntegralPoint()
{
	if(clock.min==0&&clock.sec==0)
		return 1;
	else return 0;
}

typedef unsigned int u16;	  //对数据类型进行声明定义
typedef unsigned char u8;
void Timer0Init()
{
	TMOD|=0X01;//选择为定时器0模式，工作方式1，仅用TR0打开启动。

	TH0=0XFC;	//给定时器赋初值，定时1ms
	TL0=0X18;	
	ET0=1;//打开定时器0中断允许
	EA=1;//打开总中断
	TR0=1;//打开定时器			
}

void Timer0() interrupt 1
{
	static u16 i;
	TH0=0XFC;	//给定时器赋初值，定时1ms
	TL0=0X18;
	i++;
	if(i==1000)//1s执行一次
	{
		ClockAdd();
		ClockUpdate();
		ChangeIntoSegBuf(GetClock());
		i=0;
		//LedAction();
	}	
}


