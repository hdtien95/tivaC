/*
 * ledRedStateMachine.h
 *
 *  Created on: Mar 16, 2018
 *      Author: Quoc Bao
 */

#ifndef LEDBLUESTATEMACHINE_H_
#define LEDBLUESTATEMACHINE_H_

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "switches.h"
#include "led.h"
#include "uartstdio.h"
#include "debug.h"
extern uint32_t    ledBTimer;

//void ledBlueStateMachineUpdate(void);

#define TASKLEDBLUEPERIOD 50 //period is 50 ms
#define TASKLEDBLUEINIT 0 //start immediately
extern uint32_t taskblueledcounter;
extern uint32_t taskblueledFlag;
void ledBlueTask(void);

#endif /* LEDBLUESTATEMACHINE_H_ */
