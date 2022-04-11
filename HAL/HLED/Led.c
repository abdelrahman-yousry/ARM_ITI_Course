/*
 * Led.c
 *
 *  Created on: Apr 11, 2022
 *      Author: Abdelrhman Yousry
 */

#include "Std_types.h"
#include "Gpio.h"
#include "Led.h"
#include "Led_cfg.h"

/*variable which is declared in the led_cfg.c file for user led configuration*/
extern const LedCfg_t Leds_strCfg[];


extern Led_enuErrorStatus_t Led_enuInit(void)
{
	Led_enuErrorStatus_t Loc_enuStatusError= led_enuOk;
	GpioPinCfg_t Loc_strGpioCfg;
	u8 iterator;
	for(iterator=0 ; iterator<LEDS_NUM ; iterator++)
	{
		if(Leds_strCfg[iterator].port==GPIO_A
				||Leds_strCfg[iterator].port==GPIO_B
				||Leds_strCfg[iterator].port==GPIO_C)
		{
			Loc_strGpioCfg.port=Leds_strCfg[iterator].port;
		}
		else
		{
			Loc_enuStatusError = led_enuInvalidPort;
		}
		if(Leds_strCfg[iterator].pin<=GPIO_u8PIN_15)
		{
			Loc_strGpioCfg.pin=GPIO_u8PIN_0;
		}
		else
		{
			Loc_enuStatusError = led_enuInvalidPin;
		}

		if(Leds_strCfg[iterator].otype==LED_OTYPE_PP)
		{
			Loc_strGpioCfg.mode=GPIO_u8MODE_OUTPUT_PP;
		}
		if(Leds_strCfg[iterator].otype==LED_OTYPE_PP)
		{
			Loc_strGpioCfg.mode=GPIO_u8MODE_OUTPUT_OD;
		}
		else
		{
			Loc_enuStatusError=led_enuInvalidOtype;
		}
		Loc_strGpioCfg.speed=GPIO_u8SPEED_HIGH;
	}
	Gpio_enuInit(&Loc_strGpioCfg);

	return Loc_enuStatusError;
}


extern Led_enuErrorStatus_t Led_enuSetState(u16 copy_u16ledNum, u8 copy_u8ledState)
{
	Led_enuErrorStatus_t Loc_enuStatusError = led_enuOk;
	if((Leds_strCfg[copy_u16ledNum].activeState==LED_ACTIVE_STATE_HIGH)||
			(Leds_strCfg[copy_u16ledNum].activeState==LED_ACTIVE_STATE_LOW))
	{
		Gpio_enuSetPinValue(Leds_strCfg[copy_u16ledNum].port,Leds_strCfg[copy_u16ledNum].pin,(copy_u8ledState^Leds_strCfg[copy_u16ledNum].activeState));
	}
	else
	{
		Loc_enuStatusError=led_enuInvalidState;
	}
	return Loc_enuStatusError;
}
