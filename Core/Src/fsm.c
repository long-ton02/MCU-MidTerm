#include "fsm.h"
/*------STEP 1------*/
void runFSM1(){
	switch(currentState){
	case INIT:
		buffer_7SEG[0] = 0;
		currentState = BASE;
		break;
	case BASE:
		if(isButtonSinglePressed(0) == 1){
			//RESET
			buffer_7SEG[0] = 0;
		}
		if(isButtonSinglePressed(1) == 1){
			//INC
			buffer_7SEG[0] = (10 + buffer_7SEG[0] + 1) % 10;
		}
		if(isButtonSinglePressed(2) == 1){
			//DEC
			buffer_7SEG[0] = (10 + buffer_7SEG[0] - 1) % 10;
		}
		break;
	default:
		break;
	}
}


/*------STEP 2------*/
static inline void resetBuffer(){
	buffer_7SEG[0] = 0;
}

static inline void increaseBuffer(){
	buffer_7SEG[0] = (10 + buffer_7SEG[0] + 1) % 10;
}

static inline void decreaseBuffer(){
	buffer_7SEG[0] = (10 + buffer_7SEG[0] - 1) % 10;
}

void runFSM2(){
	switch(currentState){
	case INIT:
		buffer_7SEG[0] = 0;
		currentState = BASE;
		break;
	case BASE:
		if(isButtonSinglePressed(0) == 1){
			resetBuffer();
		}
		if(isButtonSinglePressed(1) == 1){
			increaseBuffer();
		}
		if(isButtonSinglePressed(2) == 1){
			decreaseBuffer();
		}

		if(isButtonLongPressed(1) == 1){
			increaseBuffer();
			setTimer(0, 1000);
			currentState = HOLD_INC;
		}
		if(isButtonLongPressed(2) == 1){
			decreaseBuffer();
			setTimer(1, 1000);
			currentState = HOLD_DEC;
		}
		break;
	case HOLD_INC:
		if(getButtonState(1) == RELEASED_STATE){
			currentState = BASE;
		}

		if(isButtonSinglePressed(0) == 1){
			resetBuffer();
		}
		if(isButtonSinglePressed(2) == 1){
			decreaseBuffer();
		}

		if(isButtonLongPressed(2) == 1){
			decreaseBuffer();
			setTimer(1, 1000);
			currentState = HOLD_BOTH;
		}

		if(softTimer_flag[0] == 1){
			softTimer_flag[0] = 0;
			setTimer(0, 1000);

			increaseBuffer();
		}
		break;
	case HOLD_DEC:
		if(getButtonState(2) == RELEASED_STATE){
			currentState = BASE;
		}

		if(isButtonSinglePressed(0) == 1){
			resetBuffer();
		}
		if(isButtonSinglePressed(1) == 1){
			increaseBuffer();
		}

		if(isButtonLongPressed(1) == 1){
			increaseBuffer();
			setTimer(0, 1000);
			currentState = HOLD_BOTH;
		}

		if(softTimer_flag[1] == 1){
			softTimer_flag[1] = 0;
			setTimer(1, 1000);

			decreaseBuffer();
		}
	case HOLD_BOTH:
		if(getButtonState(1) == RELEASED_STATE){
			currentState = HOLD_DEC;
		}
		if(getButtonState(2) == RELEASED_STATE){
			currentState = HOLD_INC;
		}

		if(isButtonSinglePressed(0) == 1){
			resetBuffer();
		}

		if(softTimer_flag[0] == 1){
			softTimer_flag[0] = 0;
			setTimer(0, 1000);

			increaseBuffer();
		}
		if(softTimer_flag[1] == 1){
			softTimer_flag[1] = 0;
			setTimer(1, 1000);

			decreaseBuffer();
		}
		break;
	default:
		break;
	}
}


/*------STEP 3------*/
static inline void _resetBuffer(){
	setTimer(2, 10000);			//reset countdown timer
	buffer_7SEG[0] = 0;
}

static inline void _increaseBuffer(){
	setTimer(2, 10000);			//reset countdown timer
	buffer_7SEG[0] = (10 + buffer_7SEG[0] + 1) % 10;
}

static inline void _decreaseBuffer(){
	setTimer(2, 10000);			//reset countdown timer
	buffer_7SEG[0] = (10 + buffer_7SEG[0] - 1) % 10;
}

static inline void resetButtonEvent(){
	if(isButtonSinglePressed(0) == 1){
		_resetBuffer();
	}
}

static inline void incButtonEvent(){
	if(isButtonSinglePressed(1) == 1){
		_increaseBuffer();
	}
}

static inline void decButtonEvent(){
	if(isButtonSinglePressed(2) == 1){
		_decreaseBuffer();
	}
}

void increment_1s(){
	if(softTimer_flag[0] == 1){
		softTimer_flag[0] = 0;
		setTimer(0, 1000);

		_increaseBuffer();
	}
}

void decrement_1s(){
	if(softTimer_flag[1] == 1){
		softTimer_flag[1] = 0;
		setTimer(1, 1000);

		_decreaseBuffer();
	}
}

void countdown(){
	if(buffer_7SEG[0] > 0) buffer_7SEG[0]--;
}

void runFSM3(){
	switch(currentState){
	case INIT:
		buffer_7SEG[0] = 0;
		setTimer(2, 10000);			//for COUNTDOWN
		currentState = BASE;
		break;
	case BASE:
		resetButtonEvent();
		incButtonEvent();
		decButtonEvent();

		if(isButtonLongPressed(1) == 1){
			_increaseBuffer();
			setTimer(0, 1000);		//for increment_1s
			currentState = HOLD_INC;
		}
		if(isButtonLongPressed(2) == 1){
			_decreaseBuffer();
			setTimer(1, 1000);		//for decrement_1s
			currentState = HOLD_DEC;
		}
		if(softTimer_flag[2] == 1){
			softTimer_flag[2] = 0;

			countdown();

			setTimer(3, 500);		//for countdown
			currentState = COUNTDOWN;
		}
		break;
	case HOLD_INC:
		if(getButtonState(1) == RELEASED_STATE){
			currentState = BASE;
		}

		resetButtonEvent();
		decButtonEvent();

		increment_1s();

		if(isButtonLongPressed(2) == 1){
			_decreaseBuffer();
			setTimer(1, 1000);		//for decrement_1s
			currentState = HOLD_BOTH;
		}
		break;
	case HOLD_DEC:
		if(getButtonState(2) == RELEASED_STATE){
			currentState = BASE;
		}

		resetButtonEvent();
		incButtonEvent();

		decrement_1s();

		if(isButtonLongPressed(1) == 1){
			_increaseBuffer();
			setTimer(0, 1000);		//for increment_1s
			currentState = HOLD_BOTH;
		}
		break;
	case HOLD_BOTH:
		if(getButtonState(1) == RELEASED_STATE){
			currentState = HOLD_DEC;
		}
		if(getButtonState(2) == RELEASED_STATE){
			currentState = HOLD_INC;
		}

		resetButtonEvent();

		increment_1s();
		decrement_1s();
		break;
	case COUNTDOWN:
		if(softTimer_flag[3] == 1){
			softTimer_flag[3] = 0;
			setTimer(3, 500);

			countdown();
		}

		if(getButtonState(0) == PRESSED_STATE || getButtonState(1) == PRESSED_STATE ||
				getButtonState(2) == PRESSED_STATE){
			setTimer(2, 10000);
			currentState = BASE;
		}
		break;
	default:
		break;
	}
}
