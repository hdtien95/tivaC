

/**
 * main.c
 */
#include "include.h"

void main(void)
{
    SysCtlClockSet(SYSCTL_SYSDIV_2_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ); //80Mhz

    Config_UART();
    ledInit();
    IntMasterEnable();

    while(1)
    {

    }
}
