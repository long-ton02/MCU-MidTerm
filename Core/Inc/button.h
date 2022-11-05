#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "main.h"

#define NUMBER_OF_BUTTON 3
#define INTERRUPT_TIME 10

#define RELEASED_STATE GPIO_PIN_SET
#define PRESSED_STATE GPIO_PIN_RESET

static GPIO_TypeDef* buttonPort[NUMBER_OF_BUTTON] = {RESET_BUTTON_GPIO_Port, INC_BUTTON_GPIO_Port, DEC_BUTTON_GPIO_Port};
static uint16_t buttonPin[NUMBER_OF_BUTTON] = {RESET_BUTTON_Pin, INC_BUTTON_Pin, DEC_BUTTON_Pin};
static int longPress_duration[NUMBER_OF_BUTTON] = {1000, 3000, 3000};
static int doublePress_duration[NUMBER_OF_BUTTON] = {1, 1, 1};

void initButton();
void readButton();
uint8_t isButtonSinglePressed(uint8_t index);
uint8_t isButtonLongPressed(uint8_t index);
uint8_t isButtonDoublePressed(uint8_t index);
GPIO_PinState getButtonState(uint8_t index);

#endif /* INC_BUTTON_H_ */
