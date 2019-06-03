#define LED_RED     GPIO_PIN_1
#define LED_GREEN   GPIO_PIN_3
#define LED_BLUE    GPIO_PIN_2
#define SW1         GPIO_PIN_4
#define SW2         GPIO_PIN_0


/****************************************************************
 * IMPORT
 ****************************************************************/

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_ints.h"
#include "inc/hw_gpio.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"

/******************************************************************************
 * SUB ROUTINE
 *****************************************************************************/
//void ButtonISR(void)
//{
//        static int tick = LED_RED;
//        GPIOIntClear(GPIO_PORTF_BASE, SW1);
//        GPIOPinWrite(GPIO_PORTF_BASE, LED_RED|LED_GREEN|LED_BLUE, tick);
//        tick<<=1;
//        if(tick>GPIO_PIN_3)
//            tick=LED_RED;
//        //Delay 1s
//        SysCtlDelay(SysCtlClockGet()/3);
//}
//
//
///******************************************************************************
// * MAIN
// *****************************************************************************/
//void main (void)
//{
//    // Configure clock 40 MHz
//    SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
//    //PortF Enable
//    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
//    //Config GPIO that connect to LED - PIN 1,2,3
//    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, LED_RED|LED_GREEN|LED_BLUE);
//    //Turn off all LEDs
//    GPIOPinWrite(GPIO_PORTF_BASE,  LED_RED|LED_GREEN|LED_BLUE, 0);
//    //Config Buttons
//    GPIODirModeSet(GPIO_PORTF_BASE,  SW1, GPIO_DIR_MODE_IN);
//    GPIOPadConfigSet(GPIO_PORTF_BASE, SW1, GPIO_STRENGTH_8MA, GPIO_PIN_TYPE_STD_WPU);
//    //Config GPIO Interrupt for SW1
//    GPIOIntTypeSet(GPIO_PORTF_BASE,SW1, GPIO_FALLING_EDGE);
//    GPIOIntRegister(GPIO_PORTF_BASE,&ButtonISR);
//    GPIOIntEnable(GPIO_PORTF_BASE, SW1);
//    IntEnable(INT_GPIOF);
//    IntMasterEnable();
//
//    //Infinite loop
//    while(1)
//    {
//
//    }
//
//}
//int main(void)
//{
//    uint8_t ui8LED = 2;
//    SysCtlClockSet(SYSCTL_SYSDIV_4|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
//    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
//    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
//    while(1)
//    {
//        // Turn on the LED
//        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, ui8LED);
//        // Delay for a bit
//        SysCtlDelay(2000000);
//        // Cycle through Red, Green and Blue LEDs
//        if (ui8LED == 8) {ui8LED = 2;} else {ui8LED = ui8LED*2;}
//    }
//}

//chop tat 1s 1 lan led blue
int main(void)
{
//    uint8_t ui8LED = 2;
    SysCtlClockSet(SYSCTL_SYSDIV_4|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
    while(1)
    {
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, GPIO_PIN_2);
        //Delay 1s
        //SysCtlDelay(count) delay 3*count cycles
        SysCtlDelay(SysCtlClockGet()/3);
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0);
        SysCtlDelay(SysCtlClockGet()/3);
    }
//    while(1)
//    {
//        // Turn on the LED
//        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0);
//        // Delay for 1s
//        SysCtlDelay(SysCtlClockGet()/3);
//        // Cycle through Red, Green and Blue LEDs
//        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2);
//    }
}
/****************************************************************
 * END OF main.c
 ****************************************************************/
