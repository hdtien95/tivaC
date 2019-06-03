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

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
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
#include "driver/led.h"
#include "driver/switches.h"
#include "driverlib/interrupt.h"
#include "inc/hw_nvic.h"
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
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    //
    // Enable UART0
    //
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

    //
    // Configure GPIO Pins for UART mode.
    //
    ROM_GPIOPinConfigure(GPIO_PA0_U0RX);
    ROM_GPIOPinConfigure(GPIO_PA1_U0TX);
    ROM_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    //
    // Use the internal 16MHz oscillator as the UART clock source.
    //
    UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);

    //
    // Initialize the UART for console I/O.
    //
    UARTStdioConfig(0, 115200, 16000000);
}


xQueueHandle xQueue;

static  void vReceiverTask( void *pvParameters );
/* Define the structure type that will be passed on the queue. */
typedef struct
{
    unsigned int buttonStatus;
} Data_t;

//*****************************************************************************
//
// Initialize FreeRTOS and start the initial set of tasks.
//
//*****************************************************************************

static void LEDGreenTask(void *pvParameters);
//static void LEDBlueTask(void *pvParameters);
static void LEDRedTask(void *pvParameters);



int main(void)
{

    SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ |
                       SYSCTL_OSC_MAIN);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
    ConfigureUART();
    IntMasterDisable();
    switchInit();
    swIntEnable();

    xQueue = xQueueCreate( 3, sizeof( Data_t ) );

    xTaskCreate( vReceiverTask, "ReceiverTask", 240, NULL, 1, NULL );
    xTaskCreate( LEDGreenTask,  "LEDTask 2", configMINIMAL_STACK_SIZE, NULL, 1, NULL );
    vTaskStartScheduler();
    for( ;; );
}

void GPIOPortFIntHandler()
{
        Data_t  data;
        unsigned long status;

        portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
        status = GPIOIntStatus(BUTTONS_GPIO_BASE,ALL_BUTTONS);
        GPIOIntClear(BUTTONS_GPIO_BASE,ALL_BUTTONS);
        data.buttonStatus = status;
        UARTprintf("GPIOPortFIntHandler-send button status to queue\n");
        xQueueSendFromISR( xQueue, &data, &xHigherPriorityTaskWoken );
        portEND_SWITCHING_ISR( xHigherPriorityTaskWoken );
}

static void vReceiverTask( void *pvParameters )
{
    Data_t   data;
    portBASE_TYPE xStatus;
    /* This task is also defined within an infinite loop. */
    for( ;; )
    {
        UARTprintf( "ReceiverTask-trying to read queue\n" );
        xQueueReceive( xQueue, &data, portMAX_DELAY );
        if (data.buttonStatus & LEFT_BUTTON)
        {
            UARTprintf( "ReceiverTask-Left Button Pressed\n\n" );
//			LEDRedTask();
            xTaskCreate( LEDRedTask, "LEDTask 1", configMINIMAL_STACK_SIZE, NULL, 0, NULL );
        }
//        if (data.buttonStatus & RIGHT_BUTTON)   UARTprintf( "ReceiverTask-Right Button Pressed\n\n" );
    }
}

static void LEDRedTask(void *pvParameters)
{
    int i = 0;
    while ( i < 5)
    {
                ledControl(LEDRED,ON);
          //     for (i=0;i<1000000;i++);
                vTaskDelay(1000);
                ledControl(LEDRED,OFF);
          //      for (i=0;i<1000000;i++);
                vTaskDelay(1000);
                i++;
    }
}

static void LEDGreenTask(void *pvParameters)
{
   // int     i;
    while (1)
    {
                ledControl(LEDGREEN,ON);
            //    for (i=0;i<1500000;i++);
                vTaskDelay(1000);
                ledControl(LEDGREEN,OFF);
            //    for (i=0;i<1500000;i++);
                vTaskDelay(1000);
    }
}