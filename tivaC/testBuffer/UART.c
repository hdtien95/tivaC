/*
 * UART.c
 *
 *  Created on: Apr 5, 2019
 *      Author: BaTien
 */

#include "include.h"
#include "UART.h"

static char Buff[100];

/* funcion ky tu => UART => buffer*/
//void UARTGetBuffer(char *pBuff)
//{
//    while(UARTCharsAvail(UART0_BASE))
//    {
//        *pBuff=UARTCharGet(UART0_BASE);
//        pBuff++;
//    }
//
//}

/* funciong cong don buffer */
void UARTGetBuffer(char *pBuff)
{
    static uint16_t i=0; // bien i luu vi tri trong buffer de lan sau nghi vao tiep
    while(UARTCharsAvail(UART0_BASE))
    {
        *(pBuff+i)=UARTCharGet(UART0_BASE);
        i++;
    }

}

/* funciong reset buffer sau moi lan send data */

//void Reset_Buffer(char *pBuff)
//{
//    while(*pBuff != 0x0A)
//    {
//        *pBuff=0;
//        pBuff++;
//    }
//}
//void UARTGetBuffer(char *pBuff)
//{
//    static uint16_t i=0; // bien i luu vi tri trong buffer de lan sau nghi vao tiep
//    char c;
//
//    while(UARTCharsAvail(UART0_BASE))
//    {
//        c=UARTCharGet(UART0_BASE);
//        *(pBuff+i) = c;
//        i++;
//    }
//
//    if (c==0x0A)
//    {
//        i=0;
//        Reset_Buffer(pBuff);
//    }
//}

void UART_ISR(void)
{
    uint32_t ui32Status = UARTIntStatus(UART0_BASE, true); //get interrupt status
    UARTIntClear(UART0_BASE, ui32Status);

    UARTGetBuffer(&Buff[0]);
}

void Config_UART(void)
{
    //Enable PortA and UART0
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    //Config UART that connect
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    //config Uart interrupt
    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200,
        (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));

    IntMasterEnable(); //enable processor interrupts
    IntEnable(INT_UART0); //enable the UART interrupt
    UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT); //only enable RX and TX interrupts
}


