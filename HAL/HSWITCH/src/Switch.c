/*
 * Hswitch.c
 *
 *  Created on: Apr 11, 2022
 *      Author: U3
 */


/*
 * Led.c
 *
 *  Created on: Apr 11, 2022
 *      Author: Abdelrhman Yousry
 */

#include "Std_types.h"
#include "Gpio.h"
#include "Switch.h"
#include "Switch_cfg.h"

/*variable which is declared in the led_cfg.c file for user led configuration*/
extern const SwitchCfg_t Switches_strCfg[];


extern Switch_enuErrorStatus_t Switch_enuInit(void)
{
	Switch_enuErrorStatus_t Loc_enuStatusError= Switch_enuOk;
	GpioPinCfg_t Loc_strGpioCfg;
	u8 iterator;
	for(iterator=0 ; iterator<SWITCH_NUM ; iterator++)
	{
		if(Switches_strCfg[iterator].port==GPIO_A
				||Switches_strCfg[iterator].port==GPIO_B
				||Switches_strCfg[iterator].port==GPIO_C)
		{
			Loc_strGpioCfg.port=Switches_strCfg[iterator].port;
		}
		else
		{
			Loc_enuStatusError = Switch_enuInvalidPort;
		}
		if(Switches_strCfg[iterator].pin<=GPIO_u8PIN_15)
		{
			Loc_strGpioCfg.pin=GPIO_u8PIN_0;
		}
		else
		{
			Loc_enuStatusError = Switch_enuInvalidPin;
		}

		if(Switches_strCfg[iterator].pupd==SWITCH_PU)
		{
			Loc_strGpioCfg.mode=GPIO_u8MODE_INPUT_PU;
		}
		else if(Switches_strCfg[iterator].pupd==SWITCH_PD)
		{
			Loc_strGpioCfg.mode=GPIO_u8MODE_INPUT_PD;
		}
		else if(Switches_strCfg[iterator].pupd==SWITCH_FLOAT)
		{
			Loc_strGpioCfg.mode=GPIO_u8MODE_INPUT;
		}
		else
		{
			Loc_enuStatusError=Switch_enuInvalidPupdConfig;
		}
		Loc_strGpioCfg.speed=GPIO_u8SPEED_HIGH;
	}
	Gpio_enuInit(&Loc_strGpioCfg);

	return Loc_enuStatusError;
}


extern Switch_enuErrorStatus_t Switch_enuGetState(u16 copy_u16SwitchNum,pu8 copy_pu8Result)

{
	Switch_enuErrorStatus_t Loc_enuStatusError = Switch_enuOk;
	Gpio_enuGetPinValue(Switches_strCfg[copy_u16SwitchNum].port,Switches_strCfg[copy_u16SwitchNum].pin,copy_pu8Result);
	return Loc_enuStatusError;
}




