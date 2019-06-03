/*
 * sw.c
 *
 *  Created on: Apr 8, 2019
 *      Author: BaTien
 */

#define LED_RED     GPIO_PIN_1
#define LED_BLUE    GPIO_PIN_2
#define LED_GREEN   GPIO_PIN_3
#define SW1         GPIO_PIN_4
#define SW2         GPIO_PIN_0

#include "swState.h"

uint32_t taskredledcounter = TASKLEDREDINIT, taskgreenledcounter = TASKLEDGREENINIT, taskblueledcounter = TASKLEDBLUEINIT;
uint32_t taskredledFlag = 0, taskgreenledFlag = 0, taskblueledFlag = 0;


void ledRedTask(void)
{
    GPIOPinWrite(GPIO_PORTF_BASE, LED_RED, 2);
    SysCtlDelay(SysCtlClockGet()/6);
    GPIOPinWrite(GPIO_PORTF_BASE, LED_RED, 0);
    SysCtlDelay(SysCtlClockGet()/6);
}

void ledBlueTask(void)
{
    GPIOPinWrite(GPIO_PORTF_BASE, LED_BLUE, 4);
    SysCtlDelay(SysCtlClockGet()/3);
    GPIOPinWrite(GPIO_PORTF_BASE, LED_BLUE, 0);
    SysCtlDelay(SysCtlClockGet()/3);
}

void ledGreenTask(void)
{
    GPIOPinWrite(GPIO_PORTF_BASE, LED_GREEN, 8);
    SysCtlDelay(SysCtlClockGet()/2);
    GPIOPinWrite(GPIO_PORTF_BASE, LED_GREEN, 0);
    SysCtlDelay(SysCtlClockGet()/2);
}


