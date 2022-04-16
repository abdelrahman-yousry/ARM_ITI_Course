/*
 * Led_cfg.c
 *
 *  Created on: Apr 11, 2022
 *      Author: Abdelrhman Yousry
 */
#include "Std_types.h"
#include "Gpio.h"
#include "Led.h"
#include "Led_cfg.h"



const LedCfg_t Leds_strCfg[LEDS_NUM]=
{
		[LED_STOP]={
				.port=GPIO_A,
				.pin=GPIO_u8PIN_3,
				.activeState=LED_ACTIVE_STATE_HIGH,
				.otype=LED_OTYPE_PP
		}
};
