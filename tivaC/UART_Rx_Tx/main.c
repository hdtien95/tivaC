#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
//#include "utils/ringbuf.h"

void StrToHoa(char *str);

char buffer1[1000];
char buffer2[1000];
int index=0;
int remain=5;

void UARTGetBuffer(char *pBuff)
{
    while(UARTCharsAvail(UART0_BASE))
    {
        *pBuff = UARTCharGet(UART0_BASE);
        pBuff++;
    }
}

//void StrToHoa(char *str)
//{
//    while(*str != 0)
//    {
//        if (*str > 96 && *str < 123)
//        {
//            buffer2[remain] = *str - 32;
//        }
//        else
//        {
//            buffer2[remain] = *str;
//        }
//        str++;
//        remain--;
//    }
//
////    index = 0;
////    remain = 5;//strlen(str);
//    UARTIntEnable(UART0_BASE, UART_INT_TX);
//
//    UARTCharPut(UART0_BASE, buffer2[index]);
//}

void UARTIntHandler(void)
{
    uint32_t ui32Status = UARTIntStatus(UART0_BASE, true); //get interrupt status
    UARTGetBuffer(&buffer1[0]);
//    StrToHoa(&buffer1[0]);
    if ((ui32Status & UART_INT_TX) != 0)
    {
        UARTIntClear(UART0_BASE, ui32Status); //clear the asserted(khang dinh) interrupts

        if (remain > 0)
        {
            index++;
            remain --;
            UARTCharPutNonBlocking(UART0_BASE, buffer2[index]);
        }
        else
        {
            UARTIntDisable(UART0_BASE, UART_INT_TX);
        }
    }
    else
        UARTIntClear(UART0_BASE, ui32Status);
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
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_2); //enable pin for LED PF2

    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200,
        (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));

//    UARTFIFODisable(UART0_BASE);

    IntMasterEnable(); //enable processor interrupts
    IntEnable(INT_UART0); //enable the UART interrupt
    UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT); //only enable RX and TX interrupts


    while (1) //let interrupt handler do the UART echo function
    {

    }
}




