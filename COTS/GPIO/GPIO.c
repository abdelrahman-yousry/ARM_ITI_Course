/*
 * GPIO.c
 *
 *  Created on: Mar 19, 2022
 *      Author: U3
 */
#include "Std_types.h"
#include"GPIO.h"

typedef struct
{
	u32 GPIOx_MODER;
	u32 GPIOx_OTYPER;
	u32 GPIOx_OSPEEDR;
	u32 GPIOx_PUPDR;
	u32 GPIOx_IDR;
	u32 GPIOx_ODR;
	u32 GPIOx_BSRR;
	u32 GPIOx_LCKR;
	u32 GPIOx_AFRL;
	u32 GPIOx_AFRH;
}GPIO_tReg;

#define MAX_PIN_NUMBERS 15

GPIO_tenuErrorStatus GPIO_enuInitPinCfg(GPIO_tConfig* Add_Reg)
{
	GPIO_tenuErrorStatus Loc_StatusError = GPIO_enu_OK;
	if((Add_Reg->pin)>MAX_PIN_NUMBERS)
	{
		Loc_StatusError = GPIO_enu_NOK;
	}
	u32 Loc_u32TempReg;
	/*SET MODE*/
	Loc_u32TempReg=((volatile GPIO_tReg*)Add_Reg->port)->GPIOx_MODER;
	Loc_u32TempReg&=(~TWO_BITs_MASK)<<(Add_Reg->pin*2);
	Loc_u32TempReg|=((Add_Reg->mode)&TWO_BITs_MASK)<<(Add_Reg->pin*2);
	((volatile GPIO_tReg*)Add_Reg->port)->GPIOx_MODER = Loc_u32TempReg;

	/*SET_TYPE (OUPUT (PUSH-PULL/OPENDRAIN))*/
	Loc_u32TempReg=((volatile GPIO_tReg*)Add_Reg->port)->GPIOx_OTYPER;
	Loc_u32TempReg=(~ONE_BIT_MASK<<(Add_Reg->pin));
	Loc_u32TempReg|=((Add_Reg->mode)>>2)&ONE_BIT_MASK<<(Add_Reg->pin);
	((volatile GPIO_tReg*)Add_Reg->port)->GPIOx_OTYPER = Loc_u32TempReg;

	/*SET_PUDR*/
	Loc_u32TempReg=((volatile GPIO_tReg*)Add_Reg->port)->GPIOx_PUPDR;
	Loc_u32TempReg=(~TWO_BITs_MASK<<(Add_Reg->pin*2));
	Loc_u32TempReg|=((Add_Reg->mode)>>3)&TWO_BITs_MASK<<(Add_Reg->pin*2);
	((volatile GPIO_tReg*)Add_Reg->port)->GPIOx_PUPDR = Loc_u32TempReg;

	/*SET_SPEED*/
	Loc_u32TempReg=((volatile GPIO_tReg*)Add_Reg->port)->GPIOx_OSPEEDR;
	Loc_u32TempReg&=(~TWO_BITs_MASK)<<(Add_Reg->pin*2);
	Loc_u32TempReg|=((Add_Reg->speed)&TWO_BITs_MASK)<<(Add_Reg->pin*2);
	((volatile GPIO_tReg*)Add_Reg->port)->GPIOx_OSPEEDR=Loc_u32TempReg;
	return Loc_StatusError;
}


GPIO_tenuErrorStatus GPIO_enuSetPinValue(GPIO_tConfig* Add_Reg, u8 Loc_u8PinValue)
{
	GPIO_tenuErrorStatus Loc_StatusError = GPIO_enu_OK;
	if(Add_Reg == NULL)
	{
		Loc_StatusError = GPIO_enu_NOK;
	}
	if((Add_Reg->pin)>MAX_PIN_NUMBERS)
	{
		Loc_StatusError = GPIO_enu_NOK;
	}
	else
	{
		switch (Loc_u8PinValue)
		{
		case HIGH:
			((volatile GPIO_tReg*)Add_Reg->port)->GPIOx_BSRR = (ONE_BIT_MASK<<(Add_Reg->pin));
			break ;
		case LOW:
			((volatile GPIO_tReg*)Add_Reg->port)->GPIOx_BSRR = (ONE_BIT_MASK<<(Add_Reg->pin)+16);
			break;
		}
	}
	return Loc_StatusError ;
}

GPIO_tenuErrorStatus GPIO_enuGetPinValue(GPIO_tConfig* Add_Reg, pu8 pu8Add_var)
{

	GPIO_tenuErrorStatus Loc_StatusError = GPIO_enu_OK;
	if((Add_Reg->pin)>MAX_PIN_NUMBERS)
	{
		Loc_StatusError = GPIO_enu_NOK;
	}
	else
	{
		*pu8Add_var = ((volatile GPIO_tReg*)Add_Reg->port)->GPIOx_IDR >>(Add_Reg->pin);
		*pu8Add_var &= ONE_BIT_MASK;
	}
	return Loc_StatusError ;
}


/*Alternative Function*/
GPIO_tenuErrorStatus GPIO_enuSelectAf(GPIO_tConfig* Add_Reg, u32 Copy_u32AlternateValue)
{
	GPIO_tenuErrorStatus Loc_StatusError = GPIO_enu_OK;
	if(Add_Reg == NULL)
	{
		Loc_StatusError = GPIO_enu_NOK;
	}
	else if((Add_Reg->pin)>MAX_PIN_NUMBERS)
	{
		Loc_StatusError = GPIO_enu_NOK;
	}

	else
	{
		u32 Loc_u32RegValue =0;
		if(Copy_u32AlternateValue<8)
		{
			Loc_u32RegValue=((volatile GPIO_tReg*)Add_Reg->port)->GPIOx_AFRL;
			Loc_u32RegValue&=~(FOUR_BITs_MASK<<Add_Reg->pin);
			Loc_u32RegValue|=Copy_u32AlternateValue;
			((volatile GPIO_tReg*)Add_Reg->port)->GPIOx_AFRL=Loc_u32RegValue;
		}
		else
		{
			Loc_u32RegValue=((volatile GPIO_tReg*)Add_Reg->port)->GPIOx_AFRH;
			Loc_u32RegValue&=~(FOUR_BITs_MASK<<Add_Reg->pin);
			Loc_u32RegValue|=Copy_u32AlternateValue;
			((volatile GPIO_tReg*)Add_Reg->port)->GPIOx_AFRH=Loc_u32RegValue;
		}
	}
	return Loc_StatusError;
}
