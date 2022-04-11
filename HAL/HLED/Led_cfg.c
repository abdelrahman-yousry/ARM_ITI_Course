/*
 * Led_cfg.c
 *
 *  Created on: Apr 11, 2022
 *      Author: Abdelrhman Yousry
 */

#include "Led_cfg.h"
#include "Led.h"
#include "Gpio.h"

/*Here you should configure your LED according to the number of leds
 * you listed in the LED_CFG.h file
 * and it is a constant variable for two reasons
 * 1- not to be reserved in RAM and FLASH
 * 2- not to be configured in the runtime
 * */
const LedCfg_t Leds_strCfg[LEDS_NUM]=
{
		[LED_STOP]={
				.port=GPIO_A,
				.pin=GPIO_u8PIN_0,
				.activeState=LED_ACTIVE_STATE_HIGH,
				.otype=LED_OTYPE_PP
		}
};
