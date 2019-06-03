#define LED_RED     GPIO_PIN_1
#define LED_BLUE    GPIO_PIN_2
#define LED_GREEN   GPIO_PIN_3
#define SW1         GPIO_PIN_4
#define SW2         GPIO_PIN_0



#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.c"


char buffer[5];

char string1[]= "RON";
char string2[]= "ROFF";
char string3[]= "GON";
char string4[]= "GOFF";
char string5[]= "BON";
char string6[]= "BOFF";

void Reset_Buffer(char *pBuff)
{
    while(*pBuff!=0x0A)
    {
        *pBuff=0;
        pBuff++;
    }
}
void UARTGetBuffer(char *pBuff)
{
    static uint16_t i=0;
    char c;

    if(i==0)
        Reset_Buffer(pBuff);

    while(UARTCharsAvail(UART0_BASE))
    {
        c=UARTCharGet(UART0_BASE);
        *(pBuff+i)=c;
        i++;
    }

    if(c==13)
        i=0;
}

void UARTIntHandler(void)
{

    uint32_t ui32Status;

    ui32Status = UARTIntStatus(UART0_BASE, true); //get interrupt status

    UARTIntClear(UART0_BASE, ui32Status); //clear the asserted interrupts
    UARTGetBuffer(&buffer[0]);
}

int main(void)
{
    SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF); //enable GPIO port for LED
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3); //enable pin for LED PF2

    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200,
        (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
//    UARTFIFODisable(UART0_BASE)
    IntMasterEnable(); //enable processor interrupts
    IntEnable(INT_UART0); //enable the UART interrupt
    UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT); //only enable RX and TX interrupts

    while (1) //let interrupt handler do the UART echo function
    {
        UARTprintf("Xin moi ");
        if (buffer[3] == 13)
        {
            int test1 = strcmp(buffer, string1);
            int test3 = strcmp(buffer, string3);
            int test5 = strcmp(buffer, string5);

            if (test1 > 0)
            {
               GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1,GPIO_PIN_1);
            }

            else if (test3 > 0)
            {
               GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3,GPIO_PIN_3);
            }

            else if (test5 > 0)
            {
               GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2,GPIO_PIN_2);
            }

            else
            {
               UARTprintf("Xin moi nhap lai chuoi ki tu dung");
            }
        }

        else if (buffer[4] == 13)
        {
            int test2 = strcmp(buffer, string2);
            int test4 = strcmp(buffer, string4);
            int test6 = strcmp(buffer, string6);

            if (test2 > 0)
            {
                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0);
            }

            else if (test4 > 0)
            {
                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0);
            }

            else if (test6 > 0)
            {
                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0);
            }
            else
            {
               UARTprintf("Xin moi nhap lai chuoi ki tu dung");
            }
        }

        else
        {
            UARTprintf("Xin moi nhap lai chuoi ki tu dung");
        }
    }
}




