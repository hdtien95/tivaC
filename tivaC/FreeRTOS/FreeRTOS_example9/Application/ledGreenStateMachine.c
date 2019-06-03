/*
 * ledRedStateMachine.c
 *
 *  Created on: Mar 16, 2018
 *      Author: Quoc Bao
 */
#include <ledGreenStateMachine.h>
#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driver/switches.h"
#include "driver/led.h"
#include "uartstdio.h"
#include "debug.h"

typedef     enum {S_LEDON=0,S_WAITLEDOFF, S_LEDOFF, S_WAITLEDON}  ledGState_t;

static ledGState_t State = S_LEDOFF;


void ledGreenStateMachineUpdate(void)
{
    switch (State)
    {
        case S_LEDOFF:
            if (switchState(1) == PRESSED)
                {
                    State = S_WAITLEDON;
                }
            break;
        case S_WAITLEDON:
                    if (switchState(1) == RELEASED)
                        {
                            State = S_LEDON;
                        }
                    break;
        case S_LEDON:
            if (switchState(1) == PRESSED)
                {
                    State = S_WAITLEDOFF;
                }
            break;
        case S_WAITLEDOFF:
                    if (switchState(1) == RELEASED)
                        {
                            State = S_LEDOFF;
                        }
                    break;
    }
    switch (State)
    {
    case S_LEDOFF:
    case    S_WAITLEDOFF:
        ledControl(LEDGREEN,OFF);
        break;
    case S_LEDON:
    case    S_WAITLEDON:
        ledControl(LEDGREEN,ON);
        break;
    }
}
