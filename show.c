#include "reg52.h"
#include "show.h"
#include "clock.h"

ClockSegBuf clockseg_buf;

#define LED P0
#define SEG P0
#define POS P2

typedef unsigned int u16;	  //���������ͽ�����������
typedef unsigned char u8;

sbit DULA=P2^6;
sbit WELA=P2^7;
sbit BEEP=P3^6;
sbit LED0=P0^0;

void delay(unsigned int i){//��i=1ʱ����ʱ1us
	while(i--);
}

void delayms(unsigned char i){//��i=1ʱ����ʱ1ms
	while(i--)
		delay(1000);
}

u8 code smgduan[17]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
					0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};//��ʾ0~F��ֵ

void ChangeIntoSegBuf(Clock* clock)
{
	char num[6];
	num[0]=clock->sec%10;
	num[1]=clock->sec/10;
	num[2]=clock->min%10;
	num[3]=clock->min/10;
	num[4]=clock->hour%10;
	num[5]=clock->hour/10;

	clockseg_buf.seg[0]=smgduan[num[0]];
	clockseg_buf.seg[1]=smgduan[num[1]];
	clockseg_buf.seg[2]=smgduan[num[2]];
	clockseg_buf.seg[3]=smgduan[num[3]];
	clockseg_buf.seg[4]=smgduan[num[4]];
	clockseg_buf.seg[5]=smgduan[num[5]];
}
void ClockSegBufInit(){
	DULA=0;
	WELA=1;
	clockseg_buf.seg[0]=smgduan[0];
	clockseg_buf.seg[1]=smgduan[0];
	clockseg_buf.seg[2]=smgduan[0];
	clockseg_buf.seg[3]=smgduan[0];
	clockseg_buf.seg[4]=smgduan[0];
	clockseg_buf.seg[5]=smgduan[0];
}
void BeepAction(){
	BEEP=1;
	delayms(1000);
	BEEP=0;
	delayms(1000);
	BEEP=1;
	delayms(1000);
	BEEP=0;
	delayms(1000);
	BEEP=1;
	delayms(1000);
	BEEP=0;
	delayms(1000);
}
void LedAction(){
	LED0=~LED0;
}

void SegAction(){
	u8 i;
	u8 temp;
	for(i=0;i<6;i++)
	{
		//POS = 0xFF;
		switch(i)	 //λѡ��ѡ�����������ܣ�
		{
			case(0):
				POS=0xFE; break;//��ʾ��0λ
			case(1):
				POS=0xFD; break;//��ʾ��1λ
			case(2):
				POS=0xFB; break;//��ʾ��2λ
			case(3):
				POS=0xF7; break;//��ʾ��3λ
			case(4):
				POS=0xEF; break;//��ʾ��4λ
			case(5):
				POS=0xDF; break;//��ʾ��5λ
		}
		if(i==2||i==4) clockseg_buf.seg[i]|=0x80;
		SEG=clockseg_buf.seg[i];
		DULA =1;
		DULA=0;
		delay(2500); //���һ��ʱ��ɨ��	
	}
}
