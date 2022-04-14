/*
 * NVIC.c
 *
 *  Created on: Apr 13, 2022
 *      Author: Abdelrahman Yousry
 */
#include "Std_types.h"
#include "NVIC.h"
#include "NVIC_prv.h"

//THIS FUNCTION TO ENABLE IRQn WHERE n MAY BE 0--->239
Nvic_tenuErrorStatus NVIC_enuEnableIRQ(Nvic_tenuIRQn copy_IRQn)
{
	Nvic_tenuErrorStatus Loc_ErrorStatus=Nvic_enuOk;
	/*CHECKING IF THE IRQ EXIST OR NOT*/
	if(copy_IRQn>NUMBERS_OF_IRQn)
	{
		Loc_ErrorStatus=Nvic_enuInvalidIRQn;
	}
	else
	{
		//GET THE INDEX OF THE REGISTER WHICH ONE WILL BE
		//(NVIC_ISER_X) WHICH X MAY BE 0-->7
		u8 Loc_RegIndex = (u8)(copy_IRQn/32);
		u8 Loc_PinIndex = (u8)(copy_IRQn%32);

		NVIC->NVIC_ISER[Loc_RegIndex]=(u32)(ONE_BIT_MASK<<Loc_PinIndex);
	}
	return Loc_ErrorStatus;
}
//THIS FUNCTION TO DISABLE IRQn WHERE n MAY BE 0--->239
Nvic_tenuErrorStatus NVIC_enuDisableIRQ(Nvic_tenuIRQn copy_IRQn)
{
	Nvic_tenuErrorStatus Loc_ErrorStatus=Nvic_enuOk;
	/*CHECKING IF THE IRQ EXIST OR NOT*/
	if(copy_IRQn>NUMBERS_OF_IRQn)
	{
		Loc_ErrorStatus=Nvic_enuInvalidIRQn;
	}
	else
	{
		//GET THE INDEX OF THE REGISTER WHICH ONE WILL BE
		//(NVIC_ISER_X) WHICH X MAY BE 0-->7
		u8 Loc_RegIndex = copy_IRQn/32;
		u8 Loc_PinIndex = copy_IRQn%32;

		NVIC->NVIC_ICER[Loc_RegIndex]=(u32)(ONE_BIT_MASK<<Loc_PinIndex);
	}
	return Loc_ErrorStatus;
}

//THIS FUNCTION TO SET IRQn PENDING WHERE n MAY BE 0--->239
Nvic_tenuErrorStatus NVIC_enuSetPendingIRQ(Nvic_tenuIRQn copy_IRQn)
{
	Nvic_tenuErrorStatus Loc_ErrorStatus=Nvic_enuOk;
	/*CHECKING IF THE IRQ EXIST OR NOT*/
	if(copy_IRQn>NUMBERS_OF_IRQn)
	{
		Loc_ErrorStatus=Nvic_enuInvalidIRQn;
	}
	else
	{
		//GET THE INDEX OF THE REGISTER WHICH ONE WILL BE
		//(NVIC_ISPR_X) WHICH X MAY BE 0-->7
		u8 Loc_RegIndex = copy_IRQn/32;
		u8 Loc_PinIndex = copy_IRQn%32;

		NVIC->NVIC_ISPR[Loc_RegIndex]=(u32)(ONE_BIT_MASK<<Loc_PinIndex);
	}
	return Loc_ErrorStatus;
}

//THIS FUNCTION TO CLEAR IRQn PENDING WHERE n MAY BE 0--->239
Nvic_tenuErrorStatus NVIC_enuClearPendingIRQ(Nvic_tenuIRQn copy_IRQn)
{
	Nvic_tenuErrorStatus Loc_ErrorStatus=Nvic_enuOk;
	/*CHECKING IF THE IRQ EXIST OR NOT*/
	if(copy_IRQn>NUMBERS_OF_IRQn)
	{
		Loc_ErrorStatus=Nvic_enuInvalidIRQn;
	}
	else
	{
		//GET THE INDEX OF THE REGISTER WHICH ONE WILL BE
		//(NVIC_ISPR_X) WHICH X MAY BE 0-->7
		u8 Loc_RegIndex = copy_IRQn/32;
		u8 Loc_PinIndex = copy_IRQn%32;

		NVIC->NVIC_ICPR[Loc_RegIndex]=(u32)(ONE_BIT_MASK<<Loc_PinIndex);
	}
	return Loc_ErrorStatus;
}
/************************************************xxxxxxxxxxxxxx*******************************************************************/
//THIS FUNCTION TO CLEAR IRQn PENDING WHERE n MAY BE 0--->239
Nvic_tenuErrorStatus NVIC_enuGetPendingIRQ(Nvic_tenuIRQn copy_IRQn, pu8 copy_pu8AddActiveStatus)
{
	Nvic_tenuErrorStatus Loc_ErrorStatus=Nvic_enuOk;
	/*CHECKING IF THE IRQ EXIST OR NOT*/
	if(copy_pu8AddActiveStatus == NULL)
	{
		Loc_ErrorStatus=Nvic_enuNullPointer;
	}
	if(copy_IRQn>NUMBERS_OF_IRQn)
	{
		Loc_ErrorStatus=Nvic_enuInvalidIRQn;
	}
	else
	{
		//GET THE INDEX OF THE REGISTER WHICH ONE WILL BE
		//(NVIC_ISPR_X) WHICH X MAY BE 0-->7
		u8 Loc_RegIndex = copy_IRQn/32;
		u8 Loc_PinIndex = copy_IRQn%32;
		*copy_pu8AddActiveStatus=(u8)(NVIC->NVIC_ISPR[Loc_RegIndex]&((u32)(ONE_BIT_MASK<<Loc_PinIndex)));
	}
	return Loc_ErrorStatus;
}
/*******************************************************************************************************************/

/*This Function is specific to mcu STM32f401 for getting the priority value*/
/*STM32f401 is used 4 bit implemented*/
u8 NVIC_enuEncodePriority(u8 copy_u8SubGpNum, u8 copy_u8PreemptionValue, u8 copy_u8SubGpValue)
{
	u8 Loc_u8Temp ;
	if(copy_u8SubGpNum>=FOUR_BITS_IMPLEMENTEd)
	{
		Loc_u8Temp = 0xff;
	}
	switch(copy_u8SubGpNum)
	{
	case 1:
		if(copy_u8SubGpValue>1&&copy_u8PreemptionValue>7)
		{
			Loc_u8Temp = 0xff;
		}
		else
		{
			Loc_u8Temp|=(u8)((copy_u8PreemptionValue<<(FOUR_BITS_IMPLEMENTEd+(u8)1))|(copy_u8SubGpValue<<FOUR_BITS_IMPLEMENTEd));
		}
		break;
	case 2:
		if(copy_u8SubGpValue>3&&copy_u8PreemptionValue>3)
		{
			Loc_u8Temp = 0xff;
		}
		else
		{
			Loc_u8Temp|=(u8)((copy_u8PreemptionValue<<(FOUR_BITS_IMPLEMENTEd+2))|(copy_u8SubGpValue<<FOUR_BITS_IMPLEMENTEd));
		}
		break ;
	case 3:
		if(copy_u8SubGpValue>7&&copy_u8PreemptionValue>1)
		{
			Loc_u8Temp = 0xff;
		}
		else
		{
			Loc_u8Temp|=(u8)((copy_u8PreemptionValue<<(FOUR_BITS_IMPLEMENTEd+3))|(copy_u8SubGpValue<<FOUR_BITS_IMPLEMENTEd));
		}
		break ;
	case 4:
		if(copy_u8SubGpValue>4)
		{
			Loc_u8Temp = 0xff;
		}
		else
		{
			Loc_u8Temp|=(u8)(copy_u8SubGpValue<<FOUR_BITS_IMPLEMENTEd);
		}
		break;
	default:
		Loc_u8Temp=0xff;
		break;

	}
	return Loc_u8Temp;
}

Nvic_tenuErrorStatus NVIC_enuSetPriority(Nvic_tenuIRQn copy_IRQn, u8 priority)
{
	Nvic_tenuErrorStatus Loc_ErrorStatus=Nvic_enuOk;
	/*CHECKING IF THE IRQ EXIST OR NOT*/
	if(copy_IRQn>NUMBERS_OF_IRQn)
	{
		Loc_ErrorStatus=Nvic_enuInvalidIRQn;
	}
	else
	{
		NVIC->NVIC_IPR[copy_IRQn]=priority&NVIC_PRIORITY_MASK;
	}
	return Loc_ErrorStatus;
}
