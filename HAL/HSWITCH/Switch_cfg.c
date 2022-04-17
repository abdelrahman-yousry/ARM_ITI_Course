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
*/
const SwitchCfg_t Switches_strCfg[SWITCH_NUM]=
{
		[SWITCH_0]={
				.port=GPIO_A,
				.pin=GPIO_u8PIN_0,
				.pupd=SWITCH_PU
		}
};
