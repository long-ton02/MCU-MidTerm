#include "button.h"

static GPIO_PinState buttonBuffer[NUMBER_OF_BUTTON];
static GPIO_PinState keyReg1[NUMBER_OF_BUTTON];
static GPIO_PinState keyReg2[NUMBER_OF_BUTTON];
static GPIO_PinState keyReg3[NUMBER_OF_BUTTON];

static int longPress_counter[NUMBER_OF_BUTTON];

static int doublePress_counter[NUMBER_OF_BUTTON];
static int doublePress_received[NUMBER_OF_BUTTON];

static int singlePress_flag[NUMBER_OF_BUTTON];
static int longPress_flag[NUMBER_OF_BUTTON];
static int doublePress_flag[NUMBER_OF_BUTTON];

void initButton(){
	for(int i = 0; i < NUMBER_OF_BUTTON; i++){
		buttonBuffer[i] = RELEASED_STATE;
		keyReg1[i] = RELEASED_STATE;
		keyReg2[i] = RELEASED_STATE;
		keyReg3[i] = RELEASED_STATE;

		longPress_counter[i] = -1;

		doublePress_counter[i] = -1;
		doublePress_received[i] = 0;

		singlePress_flag[i] = 0;
		longPress_flag[i] = 0;
		doublePress_flag[i] = 0;
	}
}

void readButton(){
	for(int i = 0; i < NUMBER_OF_BUTTON; i++){
		keyReg3[i] = keyReg2[i];
		keyReg2[i] = keyReg1[i];
		keyReg1[i] = HAL_GPIO_ReadPin(buttonPort[i], buttonPin[i]);

		if(doublePress_counter[i] > 0){
			doublePress_counter[i]--;
		}

		if(doublePress_counter[i] == 0){
			doublePress_received[i] = 0;
		}

		if((keyReg3[i] == keyReg2[i]) && (keyReg2[i] == keyReg1[i])){
			if(buttonBuffer[i] != keyReg1[i]){
				buttonBuffer[i] = keyReg1[i];

				if(keyReg1[i] == PRESSED_STATE){
					singlePress_flag[i] = 1;

					longPress_counter[i] = longPress_duration[i]/INTERRUPT_TIME;

					if(doublePress_received[i] == 0){
						doublePress_received[i] = 1;
						doublePress_counter[i] = doublePress_duration[i]/INTERRUPT_TIME;
					} else if (doublePress_received[i] == 1) {
						doublePress_flag[i] = 1;

						doublePress_received[i] = 0;
						doublePress_counter[i] = -1;
					}
				} else {
					/*singlePress_flag[i] = 0;

					longPress_flag[i] = 0;*/
					longPress_counter[i] = -1;
				}
			}
			else {
				if(keyReg1[i] == PRESSED_STATE){
					longPress_counter[i]--;
					if(longPress_counter[i] == 0){
						longPress_counter[i] = longPress_duration[i]/INTERRUPT_TIME;
						longPress_flag[i] = 1;
					}
				}
			}
		}
	}
}

uint8_t isButtonSinglePressed(uint8_t index){
	if (singlePress_flag[index] == 1){
		singlePress_flag[index] = 0;
		return 1;
	} else return 0;
}

uint8_t isButtonLongPressed(uint8_t index){
	if (longPress_flag[index] == 1){
		longPress_flag[index] = 0;
		return 1;
	} else return 0;
}

uint8_t isButtonDoublePressed(uint8_t index){
	if (doublePress_flag[index] == 1){
		doublePress_flag[index] = 0;
		return 1;
	} else return 0;
}

GPIO_PinState getButtonState(uint8_t index){
	return buttonBuffer[index];
}
