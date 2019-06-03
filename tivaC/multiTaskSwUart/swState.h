/*
 * sw.h
 *
 *  Created on: Apr 8, 2019
 *      Author: BaTien
 */


#ifndef SWSTATE_H_
#define SWSTATE_H_


#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "switches.h"
#include "led.h"
#include "uartstdio.h"
#include "debug.h"


#define TASKLEDREDPERIOD 51 //period is 50 ms
#define TASKLEDREDINIT 1 //start immediately

extern uint32_t taskredledFlag;
extern uint32_t taskredledcounter;
extern void ledRedTask(void);



#endif /* SWSTATE_H_ */