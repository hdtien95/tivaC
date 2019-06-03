/*
 * ledRedStateMachine.c
 *
 *  Created on: Mar 16, 2018
 *      Author: Quoc Bao
 */
#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "ledRedStateMachine.h"
#include "driverlib/gpio.h"
#include "switches.h"
#include "led.h"
#include "uartstdio.h"
#include "debug.h"

#ifdef DEBUG
const char *stateName[4]=
{
 "LED_RED_ON",
 "WAIT_LED_RED_OFF",
 "LED_RED_OFF",
 "WAIT_LED_RED_ON"
};
#endif

  typedef     enum
  {
      S_LEDON = 0,
      S_WAITLEDOFF,
      S_LEDOFF,
      S_WAITLEDON,
      NUM_STATES
  } StateType;

  StateType SmState = S_LEDOFF;

  typedef     struct
  {
      StateType State;
      void (*func)(void);
  } StateMachineType;

  void Sm_State_LEDON(void)
  {
      if (switchState(1) == PRESSED)
      {
          SmState = S_WAITLEDOFF;
          DBG("State = %s\n",stateName[SmState]);
      }
  }

  void Sm_State_WAITLEDOFF(void)
  {
//      ledControl(LEDRED, OFF);
      if (switchState(1) == RELEASED)
      {
          SmState = S_LEDOFF;
          DBG("State = %s\n",stateName[SmState]);
      }
  }

  void Sm_State_LEDOFF(void)
  {
      if (switchState(1) == PRESSED)
      {
          SmState = S_WAITLEDON;
          DBG("State = %s\n",stateName[SmState]);
      }
  }

  void Sm_State_WAITLEDON(void)
  {
//      ledControl(LEDRED, ON);
      if (switchState(1) == RELEASED)
      {
          SmState = S_LEDON;
          DBG("State = %s\n",stateName[SmState]);
      }
  }

  StateMachineType StateMachine[] =
  {
   {  S_LEDON       , Sm_State_LEDON  },
   {  S_WAITLEDOFF  , Sm_State_WAITLEDOFF  },
   {  S_LEDOFF      , Sm_State_LEDOFF  },
   {  S_WAITLEDON   , Sm_State_WAITLEDON  }
  };

  void Sm_Run(void)
  {
      if (SmState < NUM_STATES)
      {
          (*StateMachine[SmState].func)();
      }
      else
      {
          DBG("BUG!");
      }

      switch (SmState)
      {
      case    S_WAITLEDOFF:
          ledControl(LEDRED,OFF);
          break;
      case    S_WAITLEDON:
          ledControl(LEDRED,ON);
      }
  }
