/*
 * main.c
 *
 *  Created on: Apr 11, 2022
 *      Author: Abdelrhman Yousry
 */
#include <stdio.h>
#include <stdlib.h>
#include "diag/Trace.h"
#include "Std_types.h"
#include "Rcc.h"
#include "Led.h"


int main(int argc, char* argv[])
{
	(void) argc;
	(void) argv;
	Rcc_enuEnablePeripheralClk(RCC_u8BUS_AHB1,RCC_u32AHB1_GPIOA);
	Led_enuInit();
	Led_enuSetState(LED_STOP,LED_STATE_ON);


  while (1)
    {

    }
}

