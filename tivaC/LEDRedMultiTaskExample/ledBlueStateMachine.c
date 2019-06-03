/*
 * ledRedStateMachine.c
 *
 *  Created on: Mar 16, 2018
 *      Author: Quoc Bao //moore
 */
#include <ledBlueStateMachine.h>


typedef     enum {S_LEDON = 0, S_LEDON_WAIT, S_LEDOFF, S_LEDOFF_WAIT}  ledBState_t;
uint32_t    ledBTimer = 0;

static ledBState_t State = S_LEDOFF;
uint32_t taskblueledcounter = TASKLEDBLUEINIT;
uint32_t taskblueledFlag = 0;

#ifdef  DEBUG
  static const  char *stateName[4]={
                                      "S_LEDON",
                                      "S_LEDON_WAIT",
                                      "S_LEDOFF",
                                      "S_LEDOFF_WAIT",
                                   };

#endif

void ledBlueTask(void)
{
        switch (State)
        {
            case S_LEDOFF:
                if (switchState(2) == PRESSED)
                    {
                        State = S_LEDOFF_WAIT;
                        ledBTimer = 20000;       //set timer to 20 sec
                        DBG("State = %s\n",stateName[State]);
                    }
                break;

            case S_LEDOFF_WAIT:
                        if (switchState(2) == RELEASED) //if switch is release before timer counting down to 0
                            {
                                State = S_LEDOFF;       //come back to OFF state
                                DBG("State = %s\n",stateName[State]);
                            }
                        else if (ledBTimer==0)
                        {
                            State = S_LEDON;
                            DBG("State = %s\n",stateName[State]);
                        }
                        break;

            case S_LEDON:
                        if (switchState(2) == RELEASED)
                            {
                                State = S_LEDON_WAIT;
                                ledBTimer = 20000;       //set timer to 20 sec
                                DBG("State = %s\n",stateName[State]);
                            }
                        break;
            case S_LEDON_WAIT:
                         if (switchState(2) == PRESSED) //if switch is release before timer counting down to 0
                             {
                                 State = S_LEDON;       //come back to OFF state
                                 DBG("State = %s\n",stateName[State]);
                             }
                         else if (ledBTimer==0)
                         {
                             State = S_LEDOFF;
                             DBG("State = %s\n",stateName[State]);
                         }
                         break;
        }

        switch (State)
        {
        case    S_LEDOFF:
        case    S_LEDOFF_WAIT:
            ledControl(LEDBLUE,OFF);
            break;

        case S_LEDON:
        case    S_LEDON_WAIT:
            ledControl(LEDBLUE,ON);
            break;
        }
}
