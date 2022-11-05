#ifndef INC_SOFT_TIMER_H_
#define INC_SOFT_TIMER_H_

#define NUMBER_OF_SOFTWARE_COUNTER 32
#define INTERRUPT_TIME 10

extern int softTimer_counter[NUMBER_OF_SOFTWARE_COUNTER];
extern int softTimer_flag[NUMBER_OF_SOFTWARE_COUNTER];

void initSoftwareTimer();
void setTimer(int index, int duration);
void runTimer();

#endif /* INC_SOFT_TIMER_H_ */
