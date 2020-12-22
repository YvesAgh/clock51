
#ifndef __CLOCK_H__
#define __CLOCK_H__
typedef struct CLOCK{
	int hour;
	int min;
	int sec;
}Clock;

void ClockInit(int hour,int min,int sec);

Clock* GetClock();
void ClockAdd();
void ClockUpdate();
int IsIntegralPoint();
void Timer0Init();
void ChangeMode();

#endif
