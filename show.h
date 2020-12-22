#ifndef __SHOW_H__
#define __SHOW_H__
#include "clock.h"


typedef  struct CLOCKSEGBUF{
	char seg[6];
}ClockSegBuf;

void ClockSegBufInit();

void ChangeIntoSegBuf(Clock* clock);

void BeepAction();
void LedAction();
void SegAction();

#endif