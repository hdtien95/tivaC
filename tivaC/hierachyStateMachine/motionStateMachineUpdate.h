/*
 * motionStateMachineUpdate.h
 *
 *  Created on: Jun 3, 2019
 *      Author: hdtie
 */

#ifndef MOTIONSTATEMACHINEUPDATE_H_
#define MOTIONSTATEMACHINEUPDATE_H_

#include "switches.h"
#include "led.h"

extern uint32_t motionTimerCount;
extern uint32_t mnt;
void motionStateMachineUpdate(void);


#endif /* MOTIONSTATEMACHINEUPDATE_H_ */