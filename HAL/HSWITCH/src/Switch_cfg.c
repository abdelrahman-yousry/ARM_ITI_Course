/*
 * Led_cfg.c
 *
 *  Created on: Apr 11, 2022
 *      Author: Abdelrhman Yousry
 */
#include "Std_types.h"
#include "Gpio.h"
#include "Switch.h"
#include "Switch_cfg.h"


/*Here you should configure your LED according to the number of leds
 * you listed in the LED_CFG.h file
 * and it is a constant variable for two reasons
 * 1- not to be reserved in RAM and FLASH
 * 2- not to be configured in the runtime
 * */
const SwitchCfg_t Switches_strCfg[SWITCH_NUM]=
{
		[SWITCH_0]={
				.port=GPIO_A,
				.pin=GPIO_u8PIN_0,
				.pupd=SWITCH_PU
		}
};
