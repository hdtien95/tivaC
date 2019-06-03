//*****************************************************************************
//
// freertos_demo.c - Simple FreeRTOS example.
//
// Copyright (c) 2012-2017 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
// 
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
// 
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
// 
// This is part of revision 2.1.4.178 of the EK-TM4C123GXL Firmware Package.
//
//*****************************************************************************
#define SW1         GPIO_PIN_4
#define SW2         GPIO_PIN_0

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "drivers/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "led_task.h"
#include "switch_task.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#define TARGET_IS_BLIZZARD_RB1
#include "driverlib/rom.h"
#include "drivers/led.h"
#include "switches.h"



#include "inc/hw_gpio.h"
#include "inc/hw_sysctl.h"

//*****************************************************************************
//
//! \addtogroup example_list
//! <h1>FreeRTOS Example (freertos_demo)</h1>
//!
//! This application demonstrates the use of FreeRTOS on Launchpad.
//!
//! The application blinks the user-selected LED at a user-selected frequency.
//! To select the LED press the left button and to select the frequency press
//! the right button.  The UART outputs the application status at 115,200 baud,
//! 8-n-1 mode.
//!
//! This application utilizes FreeRTOS to perform the tasks in a concurrent
//! fashion.  The following tasks are created:
//!
//! - An LED task, which blinks the user-selected on-board LED at a
//!   user-selected rate (changed via the buttons).
//!
//! - A Switch task, which monitors the buttons pressed and passes the
//!   information to LED task.
//!
//! In addition to the tasks, this application also uses the following FreeRTOS
//! resources:
//!
//! - A Queue to enable information transfer between tasks.
//!
//! - A Semaphore to guard the resource, UART, from access by multiple tasks at
//!   the same time.
//!
//! - A non-blocking FreeRTOS Delay to put the tasks in blocked state when they
//!   have nothing to do.
//!
//! For additional details on FreeRTOS, refer to the FreeRTOS web page at:
//! http://www.freertos.org/
//
//*****************************************************************************


#ifdef DEBUG
void
__error__(char *pcFilename, uint32_t ui32Line)
{
}

#endif

//*****************************************************************************
//
// This hook is called by FreeRTOS when an stack overflow error is detected.
//
//*****************************************************************************
void
vApplicationStackOverflowHook(xTaskHandle *pxTask, char *pcTaskName)
{
    //
    // This function can not return, so loop forever.  Interrupts are disabled
    // on entry to this function, so no processor interrupts will interrupt
    // this loop.
    //
    while(1)
    {
    }
}

//*****************************************************************************
//
// Configure the UART and its pins.  This must be called before UARTprintf().
//
//*****************************************************************************
void
ConfigureUART(void)
{
    //
    // Enable the GPIO Peripheral used by the UART.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    //
    // Enable UART0
    //
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

    //
    // Configure GPIO Pins for UART mode.
    //
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    //
    // Use the internal 16MHz oscillator as the UART clock source.
    //
    UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);

    //
    // Initialize the UART for console I/O.
    //
    UARTStdioConfig(0, 115200, 16000000);
}

//*****************************************************************************
//
// Initialize FreeRTOS and start the initial set of tasks.
//
//*****************************************************************************
typedef     enum {S_LEDON=0,S_WAITLEDOFF, S_LEDOFF, S_WAITLEDON}  ledRState_t;
static ledRState_t State = S_LEDOFF;
static void LEDGreenTask(void *pvParameters);
static void LEDBlueTask(void *pvParameters);
static void LEDRedTask(void *pvParameters);


//*****************************************************************************
//
// Initialize FreeRTOS and start the initial set of tasks.
//
//*****************************************************************************
int main(void)
{
        SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ |
                       SYSCTL_OSC_MAIN);
        ledInit();
//        SwitchTaskInit();
        //unlock the GPIOLOCK register for PF0 using direct register programming
        HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
        HWREG(GPIO_PORTF_BASE + GPIO_O_CR) = 0x01;
        HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = 0;
        GPIODirModeSet(GPIO_PORTF_BASE, SW1|SW2, GPIO_DIR_MODE_IN);
        GPIOPadConfigSet(GPIO_PORTF_BASE, SW1|SW2, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
        xTaskCreate( LEDRedTask,        "LEDTask 1", configMINIMAL_STACK_SIZE, NULL,    1, NULL );
        xTaskCreate( LEDGreenTask,      "LEDTask 2", configMINIMAL_STACK_SIZE, NULL,    1, NULL );
        xTaskCreate( LEDBlueTask,       "LEDTask 3", configMINIMAL_STACK_SIZE, NULL,    1, NULL );

    vTaskStartScheduler();
    while(1)
    {
    }
}
static void LEDRedTask(void *pvParameters)
{
    while (1)
    {
                ledControl(LEDRED,ON);
                vTaskDelay(1000);// sau lenh nay thi task LedRedTask roi vao trang thai block, sau do hdh chay de goi task khac
                ledControl(LEDRED,OFF);
                vTaskDelay(1000);
    }
}


static void LEDGreenTask(void *pvParameters)
{
    while (1)
    {
        if (!GPIOPinRead(GPIO_PORTF_BASE, SW1))
            ledControl(LEDGREEN,ON);
        else
            ledControl(LEDGREEN,OFF);
    }
}

//static void LEDBlueTask(void *pvParameters)
//{
//        while(1)
//        {
//            loop:
//            ledControl(LEDBLUE,OFF);
//
//            while (!GPIOPinRead(GPIO_PORTF_BASE, SW2))
//            {
//                ledControl(LEDBLUE,ON);
//                for (i=0;i<300000;i++);
//                while (GPIOPinRead(GPIO_PORTF_BASE, SW2))
//                {
//                    for (i=0;i<300000;i++);
//                    ledControl(LEDBLUE,ON);
//                    while (!GPIOPinRead(GPIO_PORTF_BASE, SW2))
//                    {
//                        ledControl(LEDBLUE,OFF);
//                        while (GPIOPinRead(GPIO_PORTF_BASE, SW2))
//                        {
//                              goto loop;
//                        }
//                    }
//                }
//            }
//        }
//}

static void LEDBlueTask(void *pvParameters)
{
     while(1)
     {
        switch (State)
        {
            case S_LEDOFF:
                        if (switchState(2) == PRESSED)
                            {
                                State = S_WAITLEDON;
                                //DBG("State = %s\n",stateName[State]);
                            }
                        break;
            case S_WAITLEDON:
                        if (switchState(2) == RELEASED)
                            {
                                State = S_LEDON;
                                //DBG("State = %s\n",stateName[State]);
                            }
                        break;
            case S_LEDON:
                        if (switchState(2) == PRESSED)
                            {
                                State = S_WAITLEDOFF;
                                //DBG("State = %s\n",stateName[State]);
                            }
                        break;
            case S_WAITLEDOFF:
                        if (switchState(2) == RELEASED)
                            {
                                State = S_LEDOFF;
                                //DBG("State = %s\n",stateName[State]);
                            }
                        break;
        }

        switch (State)
        {
        case    S_LEDOFF:
        case    S_WAITLEDOFF:
            ledControl(LEDBLUE,OFF);
            break;
        case    S_LEDON:
        case    S_WAITLEDON:
            ledControl(LEDBLUE,ON);
            break;
        }
   }
}


