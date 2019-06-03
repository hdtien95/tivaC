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


#define TASKLEDREDPERIOD 1000 //period is 1s
#define TASKLEDREDINIT 0 //start immediately

#define TASKLEDBLUEPERIOD 2000 //period is 2s
#define TASKLEDBLUEINIT 1000 //start immediately

#define TASKLEDGREENPERIOD 3000 //period is 3s
#define TASKLEDGREENINIT 3000 //start immediately


extern void ledRedTask(void);
extern void ledGreenTask(void);
extern void ledBlueTask(void);

extern uint32_t taskredledcounter, taskgreenledcounter, taskblueledcounter;
extern uint32_t taskredledFlag, taskgreenledFlag, taskblueledFlag;


#endif /* SWSTATE_H_ */
