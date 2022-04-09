
#include <stdio.h>
#include <stdlib.h>
#include "diag/Trace.h"
#include "Std_types.h"
#include "Gpio.h"
#include "Rcc.h"
// ----------------------------------------------------------------------------



int main(int argc, char* argv[])
{

	Rcc_enuEnablePeripheralClk(RCC_u8BUS_AHB1,RCC_u32AHB1_GPIOA);
	GpioPinCfg_t pinCfg;
	u8 value=0;
	pinCfg.pin  = GPIO_u8PIN_0;
	pinCfg.port = GPIO_A;
	pinCfg.mode = GPIO_u8MODE_OUTPUT_PP_PU;
	pinCfg.speed= GPIO_u8SPEED_MEDIUM;
	Gpio_enuInit(&pinCfg);
	Gpio_enuSetPinValue(GPIO_A,GPIO_u8PIN_0,GPIO_u8PIN_HIGH);
	Gpio_enuSetPinValue(GPIO_A,GPIO_u8PIN_1,GPIO_u8PIN_LOW);
	Gpio_enuSetPinValue(GPIO_A,GPIO_u8PIN_2,GPIO_u8PIN_HIGH);
	Gpio_enuGetPinValue(GPIO_A,GPIO_u8PIN_0,&value);
	while(1)
	{

	}
}

// ----------------------------------------------------------------------------
