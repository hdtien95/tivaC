/*
 * uartState.c
 *
 *  Created on: Apr 8, 2019
 *      Author: BaTien
 */

#include "uartState.h"

char buffer0[500];
char buffer1[500];
uint32_t taskUartFlag = 0;
uint32_t taskUartFlag2 = 0;
uint32_t taskgreenledcounter = TASKLEDGREENINIT;

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

    if(c==13)
    {
        i=0;
    }
}


//const char string3[]= {'G', 'O', 'N' };
//const char string4[]= "GOFF";

void UARTTask(void)
{
    if (strcmp(buffer0, "ON") == 0)
    {
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_PIN_3);
    }

    else if (strcmp(buffer0, "OFF") == 0)
    {
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0);
    }

    else
    {
       UARTprintf("Xin moi nhap lai chuoi ki tu dung");
    }

}


