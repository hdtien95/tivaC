/*
 * doorStateMachineUpdate.h
 *
 *  Created on: Jun 3, 2019
 *      Author: hdtie
 */

#ifndef DOORSTATEMACHINEUPDATE_H_
#define DOORSTATEMACHINEUPDATE_H_

#include "switches.h"
#include "led.h"

extern uint32_t doorTimerCount;
extern uint32_t mnt;
void doorStateMachineUpdate(void);



#endif /* DOORSTATEMACHINEUPDATE_H_ */
