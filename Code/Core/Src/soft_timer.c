#include "soft_timer.h"

int softTimer_counter[NUMBER_OF_SOFTWARE_COUNTER];
int softTimer_flag[NUMBER_OF_SOFTWARE_COUNTER];

void initSoftwareTimer(){
	/*do once on start up*/
	for(int i = 0; i < NUMBER_OF_SOFTWARE_COUNTER; i++){
		softTimer_counter[i] = 0;
		softTimer_flag[i] = 0;
	}
}

void setTimer(int index, int duration){
	if (index < 0 || index >= NUMBER_OF_SOFTWARE_COUNTER) return;
	softTimer_counter[index] = duration/INTERRUPT_TIME;
	softTimer_flag[index] = 0;
}

void runTimer(){
	for(int i = 0; i < NUMBER_OF_SOFTWARE_COUNTER; i++){
		if (softTimer_counter[i] > 0) softTimer_counter[i]--;
		if (softTimer_counter[i] <= 0) softTimer_flag[i] = 1;
	}
}


