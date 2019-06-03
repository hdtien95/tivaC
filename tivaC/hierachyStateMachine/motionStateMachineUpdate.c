/*
 * motionStateMachineUpdate.c
 *
 *  Created on: Jun 3, 2019
 *      Author: hdtie
 */

#include "motionStateMachineUpdate.h"


typedef enum {S_NOMOTION=0, S_NOMOTION_WAIT, S_MOTION, S_MOTION_WAIT} motionState_t;
static motionState_t     motionState=S_NOMOTION;
uint32_t motionTimerCount=0;

void motionStateMachineUpdate(void)
{
    switch(motionState)
    {
        case S_NOMOTION:
            if (switchState(1) == PRESSED)
            {
                motionState = S_NOMOTION_WAIT;
                motionTimerCount = 50;
            }

        case S_NOMOTION_WAIT:
            if (switchState(1) == RELEASED)
            {
                motionState = S_NOMOTION;
            }
            else if (motionTimerCount == 0) //Timer Timeout
            {
                motionState = S_MOTION;
            }

        case S_MOTION:
            if (switchState(1) == PRESSED)
            {
                motionState = S_MOTION_WAIT;
                motionTimerCount = 50;
            }

        case S_MOTION_WAIT:
            if (switchState(1) == RELEASED)
            {
                motionState = S_MOTION;
            }
            else if (motionTimerCount == 0) //Timer Timeout
            {
                motionState = S_NOMOTION;
            }
    }

    switch (motionState)
    {
        case S_NOMOTION:
        case S_NOMOTION_WAIT:
            mnt = 0;
            break;

        case S_MOTION:
        case S_MOTION_WAIT:
            mnt = 1;
            break;
    }
}


