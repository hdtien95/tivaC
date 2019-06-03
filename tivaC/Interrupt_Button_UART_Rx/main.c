#define LED_RED     GPIO_PIN_1
#define LED_BLUE    GPIO_PIN_2
#define LED_GREEN   GPIO_PIN_3
#define SW1         GPIO_PIN_4
#define SW2         GPIO_PIN_0


/****************************************************************
 * IMPORT
 ****************************************************************/

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_ints.h"
#include "inc/hw_gpio.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/uart.h"
#include "driverlib/pin_map.h"
#include "utils/uartstdio.h"

/******************************************************************************
 * SUB ROUTINE
 *****************************************************************************/
void ButtonISR(void)
{
        GPIOIntClear(GPIO_PORTF_BASE, SW1);
        loop:
                GPIOPinWrite(GPIO_PORTF_BASE, LED_RED, 0);
                while (!GPIOPinRead(GPIO_PORTF_BASE, SW1))
                {
                    GPIOPinWrite(GPIO_PORTF_BASE, LED_RED, 2);
                    while (GPIOPinRead(GPIO_PORTF_BASE, SW1))
                    {
                        GPIOPinWrite(GPIO_PORTF_BASE, LED_RED, 2);
                        while (!GPIOPinRead(GPIO_PORTF_BASE, SW1))
                        {
                            GPIOPinWrite(GPIO_PORTF_BASE, LED_RED, 0);
                            while (GPIOPinRead(GPIO_PORTF_BASE, SW1))
                            {
                                  goto loop;
                            }
                        }
                    }
                }
}

//void UARTIntHandler(void)
//{
//    uint32_t ui32Status;
//
//    ui32Status = UARTIntStatus(UART0_BASE, true); //get interrupt status
//
//    UARTIntClear(UART0_BASE, ui32Status); //clear the asserted interrupts
//
//    while(UARTCharsAvail(UART0_BASE)) //loop while there are chars
//    {
//        char x = UARTCharGetNonBlocking(UART0_BASE);
//
//        if (x == 'o')
//        {
//            GPIOPinWrite(GPIO_PORTF_BASE, LED_RED, LED_RED);
//        }
//        else if (x == 'f')
//        {
//            GPIOPinWrite(GPIO_PORTF_BASE, LED_RED, 0);
//        }
//    }
//}



uint32_t taskUartFlag = 0;
char buffer0[10];
char buffer1[10];
//char buffer2[10];



//void PutStrInt(char *str)
//{
//    static int remain=0;
//    while(*str != 0)
//    {
//        buffer1[remain] = *str;
//        str++;
//        remain++;
//    }
//}

void Reset_Buffer(char *pBuff)
{
    while(*pBuff!=13)
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
    {
        Reset_Buffer(pBuff);
        Reset_Buffer(buffer0);
    }

    while(UARTCharsAvail(UART0_BASE))
    {
        c=UARTCharGet(UART0_BASE);
        *(pBuff+i)=c;
        i++;
    }

//    int s=strlen(pBuff);
//    strncpy(buffer1, pBuff, s);

    if(c==13)
    {
        i=0;
    }
}

void UARTIntHandler(void)
{
    UARTGetBuffer(buffer1);

    int z=strlen(buffer1)-1;
    if (buffer1[z] == 13)
    {
        taskUartFlag = 1;
    }

    strncpy(buffer0, buffer1, z);
}

const char string3[]= {'G', 'O', 'N' };
const char string4[]= "GOFF";

void UARTTask(void)
{
    if (strcmp(buffer1, "ON\x0D\0xA") == 0)
//    {
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_PIN_3);
//    }

    else if (strcmp(buffer1, "OFF\x0D\0xA") == 0)
    {
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0);
    }
//    else
//    {
//       UARTprintf("Xin moi nhap lai chuoi ki tu dung");
//    }

}





/******************************************************************************
 * MAIN
 *****************************************************************************/
void main (void)
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
    GPIOIntTypeSet(GPIO_PORTF_BASE,SW1, GPIO_FALLING_EDGE);
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

    //Infinite loop
    while(1)
    {
        if (taskUartFlag)
        {
            taskUartFlag = 0;
            UARTTask();
        }
    }

}

/****************************************************************
 * END OF main.c
 ****************************************************************/
