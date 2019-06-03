/*
 * uart_0_util.c
 *
 *  Created on: Feb 27, 2019
 *      Author: BaTien
 */

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "uart_0_util.h"

void Putstr(char *str)
{
	int i=0;
    while((*(str+i)))
    {
    	UARTCharPut(UART0_BASE, *(str+i));
    	i++;
    }
}
