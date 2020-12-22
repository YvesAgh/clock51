#include "reg52.h"
#include "clock.h"
#include "show.h"
#include "timer.h"
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

