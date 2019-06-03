/*
 * ledBlueStateMachine.c
 *
 *  Created on: Apr 10, 2019
 *      Author: BaTien
 */

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "ledBlueStateMachine.h"
#include "driverlib/gpio.h"
#include "switches.h"
#include "led.h"
#include "uartstdio.h"
#include "debug.h"


//void ledBlueTask(void *myobject)
//{
//      ledBlueStateUpdate();
//}
//void ledBlueStateUpdate(void )
//{
//    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, GPIO_PIN_2);
//    //Delay 1s
//    //SysCtlDelay(count) delay 3*count cycles
//    SysCtlDelay(SysCtlClockGet()/3);
//    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0);
//    SysCtlDelay(SysCtlClockGet()/3);
//}
typedef enum {S_LEDON, S_LEDOFF}                                 ledBState_t;
static ledBState_t State = S_LEDOFF;
uint32_t    ledBTimer = 0;


#ifdef  DEBUG
static const  char *stateName[2]={
                              "S_LEDON",
                              "S_LEDOFF",
                                 };

#endif

void ledBlueTask(void *myobject)
{
    ledBlueStateMachineUpdate();
}

void ledBlueStateMachineUpdate(void *myobject)
{
    switch (State)
    {
        case S_LEDON:
            if (ledBTimer == 0)
            {
                State = S_LEDOFF;
                ledBTimer = 1000;
                DBG("State = %s\n",stateName[State]);
            }
            break;

        case S_LEDOFF:
            if (ledBTimer == 0)
            {
                State = S_LEDON;
                ledBTimer = 1000;
                DBG("State = %s\n",stateName[State]);
            }
            break;
    }

    switch (State)
    {
        case S_LEDON:
            ledControl(LEDBLUE,ON);
            break;
        case S_LEDOFF:
            ledControl(LEDBLUE,OFF);
            break;
    }
}











