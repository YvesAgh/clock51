#include "reg52.h"
#include "clock.h"
#include "show.h"
#include "timer.h"
typedef unsigned int u16;	  //���������ͽ�����������
typedef unsigned char u8;
void Timer0Init()
{
	TMOD|=0X01;//ѡ��Ϊ��ʱ��0ģʽ��������ʽ1������TR0��������

	TH0=0XFC;	//����ʱ������ֵ����ʱ1ms
	TL0=0X18;	
	ET0=1;//�򿪶�ʱ��0�ж�����
	EA=1;//�����ж�
	TR0=1;//�򿪶�ʱ��			
}

void Timer0() interrupt 1
{
	static u16 i;
	TH0=0XFC;	//����ʱ������ֵ����ʱ1ms
	TL0=0X18;
	i++;
	if(i==1000)//1sִ��һ��
	{
		ClockAdd();
		ClockUpdate();
		ChangeIntoSegBuf(GetClock());
		i=0;
		//LedAction();
	}	
}

