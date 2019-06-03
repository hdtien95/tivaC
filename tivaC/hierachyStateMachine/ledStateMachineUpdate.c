/*
 * ledStateMachineUpdate.c
 *
 *  Created on: Jun 3, 2019
 *      Author: hdtie
 */



#include "ledStateMachineUpdate.h"


typedef enum {S_LEDOFF=0, S_LEDON} ledState_t;
static ledState_t     ledState=S_LEDOFF;
uint32_t ledTimerCount = 0;

void ledStateMachineUpdate(void)
{
    switch (ledState)
    {
        case S_LEDOFF:
            if (mnt == 1 & ledTimerCount == 0)
            {
                ledState = S_LEDON;
                ledTimerCount = 500; //0.5s
            }

        case S_LEDON:
            if (ledTimerCount == 0)
            {
                ledState = S_LEDOFF;
            }
    }

    switch (ledState)
    {
        case S_LEDOFF:
            ledControl(LEDBLUE,OFF);
            break;
        case S_LEDON:
            ledControl(LEDBLUE,ON);
            break;
    }
}