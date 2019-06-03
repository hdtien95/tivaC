/*
 * ledBlueStateMachine.h
 *
 *  Created on: Apr 10, 2019
 *      Author: BaTien
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

#define GENON 1;
#define GENOFF 0;

#define LEDON   GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 1<<2) //led blue
#define LEDOFF   GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0) //led blue

//function prototype

void ledBlueTask(void *myobject);

#endif /* LEDBLUESTATEMACHINE_H_ */
