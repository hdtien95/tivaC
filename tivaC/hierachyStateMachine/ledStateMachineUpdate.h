/*
 * ledStateMachineUpdate.h
 *
 *  Created on: Jun 3, 2019
 *      Author: hdtie
 */

#ifndef LEDSTATEMACHINEUPDATE_H_
#define LEDSTATEMACHINEUPDATE_H_

#include "switches.h"
#include "led.h"

extern uint32_t ledTimerCount;
extern uint32_t mnt;
void ledStateMachineUpdate(void);



#endif /* LEDSTATEMACHINEUPDATE_H_ */
