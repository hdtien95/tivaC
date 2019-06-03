/*
 * main.c
 */




#define LED_RED		GPIO_PIN_1
#define LED_BLUE	GPIO_PIN_2
#define LED_GREEN	GPIO_PIN_3
#define SW1			GPIO_PIN_4
#define SW2 		GPIO_PIN_0



#include <stdbool.h>
#include <stdint.h>

#include "inc/hw_gpio.h"

#include "inc/hw_sysctl.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"


int main(void)
{
    int read;
	// Configure clock 40 MHz
	SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
	//PortF Enable
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	//Config GPIO that connect to LED - PIN 1,2,3
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, LED_RED|LED_GREEN|LED_BLUE);
	//Turn off all LEDs
	GPIOPinWrite(GPIO_PORTF_BASE, LED_RED|LED_GREEN|LED_BLUE, 0);
	//Config Buttons
	//unlock the GPIOLOCK register for PF0 using direct register programming
	HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
	HWREG(GPIO_PORTF_BASE + GPIO_O_CR) = 0x01;
	HWREG(GPIO_PORTF_BASE + GPIO_O_CR) = 0;
	GPIODirModeSet(GPIO_PORTF_BASE, SW1|SW2, GPIO_DIR_MODE_IN);
	GPIOPadConfigSet(GPIO_PORTF_BASE, SW1|SW2, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
	
	//Infinite loop
	while(1)
	{
		read=GPIOPinRead(GPIO_PORTF_BASE, SW1|SW2);
		if((read&(SW1|SW2))==0)
		GPIOPinWrite(GPIO_PORTF_BASE, LED_RED|LED_GREEN|LED_BLUE, LED_BLUE);
		else if((read&SW1 )==0)
		GPIOPinWrite(GPIO_PORTF_BASE, LED_RED|LED_GREEN|LED_BLUE, LED_RED);
		else if((read&SW2)==0)
		GPIOPinWrite(GPIO_PORTF_BASE, LED_RED|LED_GREEN|LED_BLUE, LED_GREEN);
		else
		GPIOPinWrite(GPIO_PORTF_BASE, LED_RED|LED_GREEN|LED_BLUE, 0);
	}
//    while(1)
//    {
//        if (!GPIOPinRead(GPIO_PORTF_BASE, SW2))
//            GPIOPinWrite(GPIO_PORTF_BASE, LED_RED|LED_GREEN|LED_BLUE, LED_BLUE);
//        else
//            GPIOPinWrite(GPIO_PORTF_BASE, LED_RED|LED_GREEN|LED_BLUE, 0);
//    }
//	return 0;
}
