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

static char Buff[100];

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
//        c=UARTCharGet(UART0_BASE);
//        *(pBuff+i)=c;
//        i++;

            c = UARTCharGet(UART0_BASE);
            if (c > 96 && c < 123)
            {
                *(pBuff+i) = c - 32;
            }
            else
            {
                *(pBuff+i)=c;
            }
            i++;
    }

    if(c==13)
        i=0;
}

//void UARTGetBuffer(char *pBuff)
//{
//    while(UARTCharsAvail(UART0_BASE))
//    {
//        *pBuff = UARTCharGet(UART0_BASE);
//        pBuff++;
//    }
//}

void UARTIntHandler(void)
{
    UARTIntClear(UART0_BASE,UARTIntStatus(UART0_BASE,true));
    UARTGetBuffer(&Buff[0]);
}

void UARTPutBuffer(void)
{
    uint16_t i=0;
    while(Buff[i]!= 13)
    {
        UARTCharPut(UART0_BASE,Buff[i]);
        i++;
    }
}

void ButtonISR(void)
{
    GPIOIntClear(GPIO_PORTF_BASE, GPIO_PIN_4);
    UARTPutBuffer();
}

int main(void)
{
    // Configure clock 40 MHz
    SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
    //PortF Enable and PortA, UART0
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    //Config GPIO that connect to LED - PIN 1,2,3
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, LED_RED|LED_GREEN|LED_BLUE);

    //Turn off all LEDs
    GPIOPinWrite(GPIO_PORTF_BASE,  LED_RED|LED_GREEN|LED_BLUE, 0);

    //Config UART that connect
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    //Config Buttons
    GPIODirModeSet(GPIO_PORTF_BASE,  SW1, GPIO_DIR_MODE_IN);
    GPIOPadConfigSet(GPIO_PORTF_BASE, SW1, GPIO_STRENGTH_8MA, GPIO_PIN_TYPE_STD_WPU);
    //Config GPIO Interrupt for SW1
    GPIOIntTypeSet(GPIO_PORTF_BASE, SW1, GPIO_FALLING_EDGE);
    GPIOIntRegister(GPIO_PORTF_BASE,&ButtonISR);
    GPIOIntEnable(GPIO_PORTF_BASE, SW1);
    IntEnable(INT_GPIOF);
    IntMasterEnable();

    //config Uart interrupt
    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200,
        (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));

    IntMasterEnable(); //enable processor interrupts
    IntEnable(INT_UART0); //enable the UART interrupt
    UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT); //only enable RX and TX interrupts


    while (1) //let interrupt handler do the UART echo function
    {

    }
}
