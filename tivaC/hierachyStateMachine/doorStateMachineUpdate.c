/*
 * doorStateMachineUpdate.c
 *
 *  Created on: Jun 3, 2019
 *      Author: hdtie
 */

#include "doorStateMachineUpdate.h"


typedef enum {S_CLOSE=0, S_OPEN, S_OPEN_WAIT} doorState_t;
static doorState_t     doorState=S_CLOSE;
uint32_t doorTimerCount = 0;

void doorStateMachineUpdate(void)
{
    switch (doorState)
    {
        case S_CLOSE:
            if (mnt == 1)
            {
                doorState = S_OPEN;
            }

        case S_OPEN:
            if (mnt == 0)
            {
                doorState = S_OPEN_WAIT;
                doorTimerCount = 10000;
            }

        case S_OPEN_WAIT:
            if (mnt == 1)
            {
                doorState = S_OPEN;
            }
            else if (doorTimerCount == 0)
            {
                doorState = S_CLOSE;
            }
    }

    switch (doorState)
    {
        case S_CLOSE:
            ledControl(LEDRED, OFF);
            break;

        case S_OPEN:
        case S_OPEN_WAIT:
            ledControl(LEDRED, ON);
            break;
    }

}


