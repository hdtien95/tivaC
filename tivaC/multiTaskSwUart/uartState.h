/*
 * uartState.h
 *
 *  Created on: Apr 8, 2019
 *      Author: BaTien
 */

#ifndef UARTSTATE_H_
#define UARTSTATE_H_

#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "switches.h"
#include "led.h"
#include "uartstdio.h"
#include "debug.h"
#include "inc/hw_types.h"
#include "inc/hw_ints.h"
#include "inc/hw_gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/uart.h"
#include "driverlib/pin_map.h"

#define TASKLEDGREENPERIOD 52 //period is 50 ms
#define TASKLEDGREENINIT 2 //start immediately
extern uint32_t taskgreenledcounter;
extern uint32_t taskUartFlag;
extern uint32_t taskUartFlag2;
extern char buffer0[500];
extern char buffer1[500];

extern void UARTGetBuffer(char *pBuff);
//extern void Config_UART(void);
extern void UARTTask(void);
extern void Reset_Buffer(char *pBuff);
extern void UARTGetBuffer(char *pBuff);

#endif /* UARTSTATE_H_ */
