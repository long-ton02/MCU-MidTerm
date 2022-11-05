#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include "soft_timer.h"
#include "button.h"
#include "display_7SEG.h"

enum fsmState {INIT, BASE, HOLD_INC, HOLD_DEC, HOLD_BOTH, COUNTDOWN};

extern enum fsmState currentState;

#endif /* INC_GLOBAL_H_ */
