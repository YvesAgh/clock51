#include "reg52.h"
#include "show.h"
#include "clock.h"
#include "timer.h"

int main(){

	ClockSegBufInit();
	ClockInit(0,0,1);
	Timer0Init();
	//P0=0xf0;
	//BeepAction();
	while(1){
		SegAction();
		if(IsIntegralPoint()) BeepAction();
	}
}
