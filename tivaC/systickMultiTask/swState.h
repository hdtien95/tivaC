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
#include "driverlib/sysctl.h"


#define TASKLEDREDPERIOD 20000 //period is 20s
#define TASKLEDREDINIT 0 //start immediately

#define TASKLEDBLUEPERIOD 40000 //period is 40s
#define TASKLEDBLUEINIT 1000 //start immediately

#define TASKLEDGREENPERIOD 100000 //period is 100s
#define TASKLEDGREENINIT 2000 //start immediately


extern void ledRedTask(void);
extern void ledGreenTask(void);
extern void ledBlueTask(void);

extern uint32_t taskredledcounter, taskgreenledcounter, taskblueledcounter;
extern uint32_t taskredledFlag, taskgreenledFlag, taskblueledFlag;


#endif /* SWSTATE_H_ */
