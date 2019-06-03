#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "uart_0_util.h"
#include "utils/uartstdio.h"

void ConfigureUART(void)
{
    //
    // Enable the GPIO Peripheral used by the UART.
    //
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

	//
	// Enable UART0
	//
	SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

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

    /*
    //cau hinh thong so uart
	//UART_CONFIG_WLEN_8 => che do 8 bit
	//SysCtlClockGet() = 50tr Hz
    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200, (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
     */
}

int main(void)
{
    //
    // Set the clocking to run directly from the crystal.
    //
    SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);

    //
    // Initialize the UART.
    //
    ConfigureUART();
    //char  msg[] = "Enter Text 2: ";

    while (1)
    {
		//UARTCharsAvail tra ve value chung
        if (UARTCharsAvail(UART0_BASE))
        {
            //
            // put string uart: "Enter Text: "
            //
            UARTprintf("Enter Text 1: ");
        	//Putstr(msg);// str=msg <=> str= &msg[0]
        	Putstr("Enter Text 2: ");
        	UARTCharPut(UART0_BASE, UARTCharGet(UART0_BASE));

        	UARTprintf("\n");
        }
    }

}

