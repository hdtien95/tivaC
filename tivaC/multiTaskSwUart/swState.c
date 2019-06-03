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

uint32_t taskredledcounter = TASKLEDREDINIT;
uint32_t taskredledFlag = 0;

void ledRedTask(void)
{
          if (!GPIOPinRead(GPIO_PORTF_BASE, SW1))
          {
              GPIOPinWrite(GPIO_PORTF_BASE, LED_RED, 2);
          }
          else
          {
              GPIOPinWrite(GPIO_PORTF_BASE, LED_RED, 0);
          }
}

