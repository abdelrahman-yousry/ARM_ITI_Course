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
static u8 SwitchStatus[SWITCH_NUM];

extern Switch_enuErrorStatus_t Switch_enuInit(void)
{
	/*Define GPIO error enum*/
	Switch_enuErrorStatus_t Loc_enuStatusError= Switch_enuOk;
	/*Declare GPIO cfg struct */
	GpioPinCfg_t Loc_strGpioCfg;
	// Decalre iterator var
	u8 iterator;
	for(iterator=0 ; iterator<SWITCH_NUM ; iterator++)
	{
		/*Validate on the input*/
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
		/*Validate on the input*/
		if(Switches_strCfg[iterator].pin<=GPIO_u8PIN_15)
		{
			Loc_strGpioCfg.pin=GPIO_u8PIN_0;
		}
		else
		{
			Loc_enuStatusError = Switch_enuInvalidPin;
		}
		/*Check if the Input  pin is Input PU or PD or Floating*/
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
		/*Configure the pin speed to be HIGH*/
		Loc_strGpioCfg.speed=GPIO_u8SPEED_HIGH;
	}
	/*Sending the configuration to the GPIO_Init Func*/
	Gpio_enuInit(&Loc_strGpioCfg);

	return Loc_enuStatusError;
}


extern Switch_enuErrorStatus_t Switch_enuGetState(u16 copy_u16SwitchNum,pu8 copy_pu8Result)

{
	Switch_enuErrorStatus_t Loc_enuStatusError = Switch_enuOk;
	if(copy_pu8Result == NULL)
	{
		Loc_enuStatusError= Switch_enuNullPointer;
	}
	else
	{
		*copy_pu8Result = SwitchStatus[copy_u16SwitchNum];
	}

	return Loc_enuStatusError;
}



extern void Switch_Task(void)
{
	/*Declare GPIO Cfg struct*/
	GpioPinCfg_t Loc_strCfg;
	/*Declare VAR iterator to store the cfg for every pin*/
	u16 Loc_u16Iterator = 0;
	/*Declare var to store the current status of the button*/
	u32 Loc_u32CurSwitchStatus	= 0;
	/*create STATIC var to store the prev_status of the button*/
	static u8  Loc_u8PrevSwitchStatus[SWITCH_NUM];
	/*Declare counter for each switch --> array of counters*/
	static u8 Counter[SWITCH_NUM];
	for(Loc_u16Iterator = 0 ; Loc_u16Iterator< SWITCH_NUM ; Loc_u16Iterator++)
	{
		/*Set switch config*/
		/*Switches_strCfg is a global var holds the configuration of all switches in the cfg.c file*/
		Loc_strCfg.port  = Switches_strCfg[Loc_u16Iterator].port;
		Loc_strCfg.pin  = Switches_strCfg[Loc_u16Iterator].pin;
		/*Read pin value*/
		Gpio_enuGetPinValue(Loc_strCfg.port ,Loc_strCfg.pin, &Loc_u32CurSwitchStatus);
		if(Loc_u32CurSwitchStatus == Loc_u8PrevSwitchStatus[Loc_u16Iterator])
		{
			Counter[Loc_u16Iterator]++;
		}
		else
		{
			Counter[Loc_u16Iterator]=0;
		}

		if(Counter[Loc_u16Iterator] == 5)
		{
			Counter[Loc_u16Iterator] = 0;
			SwitchStatus[Loc_u16Iterator] = (u8) Loc_u32CurSwitchStatus;
		}
		Loc_u8PrevSwitchStatus[Loc_u16Iterator] = (u8) Loc_u32CurSwitchStatus;
	}
}

