/*
 * Rcc.c
 *
 *  Created on: Mar 28, 2022
 *      Author: Abdelrahman Yousry
 */
#include "Std_types.h"
#include "Rcc.h"
#include "Rcc_priv.h"

Rcc_tenuSysClkStatus Rcc_vidGetSysClkStatus(void)
{
	//	Rcc_tenuSysClkStatus Loc_SysClkStatus = Rcc_NotApllicable;
	//	if(((Rcc->RCC_CFGR &RCC_u32CFGR_SWS_Checking)>>2)==Rcc_enuHsi)//we can meke it like==(u32)RCC_u64SYSCLK_HSI
	//	{
	//		//		Loc_SysClkStatus = Rcc_enuHsi;
	//		Loc_SysClkStatus = (u32)RCC_u64SYSCLK_HSI;
	//	}
	//	else if(((Rcc->RCC_CFGR &RCC_u32CFGR_SWS_Checking)>>2)==Rcc_enuHse)
	//	{
	//		//		Loc_SysClkStatus = Rcc_enuHse;
	//		Loc_SysClkStatus = (u32)RCC_u64SYSCLK_HSE;
	//	}
	//	else if(((Rcc->RCC_CFGR &RCC_u32CFGR_SWS_Checking)>>2)==Rcc_enuPll)
	//	{
	//		//		Loc_SysClkStatus = Rcc_enuPll;
	//		Loc_SysClkStatus = (u32)RCC_u64SYSCLK_PLL;
	//	}
	//	else
	//	{
	//		/*do nothing*/
	//	}
	Rcc_tenuSysClkStatus Loc_SysClkStatus ;
	Loc_SysClkStatus = (Rcc->RCC_CFGR &RCC_u32CFGR_SWS_Checking)>>2;
	return Loc_SysClkStatus;
}



Rcc_tenuErrorStatus Rcc_enuHseControl(u64 Copy_ControlValue)
{
	u16 Loc_TimeOut=500;
	Rcc_tenuErrorStatus Loc_enuErrorStatus = Rcc_enuNok;
	//checking that the user pass the right argument or not
	if (Copy_ControlValue&CLEAR_MAGIC_NUMBER_MASK)
	{
		//checking the user need the HSE to be ON or OFF
		if(Copy_ControlValue==RCC_u64HSE_ON)
		{
			//enable HSE clock
			Rcc->RCC_CR |= (u32)RCC_u64HSE_ON;
			// i put not here because if while will be false i will break it
			//I make this block of code to check whether clock is on or not
			while(Loc_TimeOut && !(Rcc->RCC_CR&RCC_u32HSE_READY))
			{
				Loc_TimeOut--;
			}
			if(Rcc->RCC_CR &(RCC_u32HSE_READY))
			{
				Loc_enuErrorStatus = Rcc_enuOk;
			}
		}
		/*at anytime you will close any clock source
		 * you must check first that this clk
		 * not the clock of the sysclk
		 * so in the else condition we
		 * will make this validation first
		 **/
		else if (Copy_ControlValue==RCC_u64HSE_OFF)
		{
			if(Rcc_vidGetSysClkStatus()==(u32)RCC_u64SYSCLK_HSE)
			{
				// m4 3arf 27ot 2eh l2ny 2sln fow 3aml initialization ll status b notOk
				Loc_enuErrorStatus =Rcc_enuWrongConfiguration;
			}
			else
			{
				Rcc->RCC_CR &=(u32)(RCC_u64HSE_OFF) ;
				Loc_enuErrorStatus = Rcc_enuOk;
			}
		}
		else
		{
			/*do nothing*/
		}
	}
	else
	{
		Loc_enuErrorStatus =Rcc_enuWrongConfiguration;
	}

	return Loc_enuErrorStatus;
}



Rcc_tenuErrorStatus Rcc_enuHsiControl(u64 Copy_ControlValue)
{
	u16 Loc_TimeOut=500;
	Rcc_tenuErrorStatus Loc_enuErrorStatus = Rcc_enuNok;
	//checking that the user pass the right argument or not
	if (Copy_ControlValue&CLEAR_MAGIC_NUMBER_MASK)
	{
		//checking the user need the HSI to be ON or OFF
		if(Copy_ControlValue==RCC_u64HSI_ON)
		{
			//enable HSI clock
			Rcc->RCC_CR |= (u32)RCC_u64HSI_ON;
			// i put not here because if while will be false i will break it
			//I make this block of code to check wether
			while(Loc_TimeOut && !(Rcc->RCC_CR&RCC_u32HSI_READY))
			{
				Loc_TimeOut--;
			}
			if(Rcc->RCC_CR &(RCC_u32HSI_READY))
			{
				Loc_enuErrorStatus = Rcc_enuOk;
			}
		}
		/*at anytime you will close any clock source
		 * you must check first that this clk
		 * not the clock of the sysclk
		 * so in the else condition we
		 * will make this validation first
		 **/
		else if (Copy_ControlValue==RCC_u64HSI_OFF)
		{
			if(Rcc_vidGetSysClkStatus()==(u32)RCC_u64SYSCLK_HSI)
			{
				// m4 3arf 27ot 2eh l2ny 2sln fow 3aml initialization ll status b notOk
				Loc_enuErrorStatus =Rcc_enuWrongConfiguration;
			}
			else
			{
				Rcc->RCC_CR &=(u32)(RCC_u64HSI_OFF) ;
				Loc_enuErrorStatus = Rcc_enuOk;
			}
		}
		else
		{
			/*do nothing*/
		}
	}
	else
	{
		Loc_enuErrorStatus =Rcc_enuWrongConfiguration;
	}

	return Loc_enuErrorStatus;
}


Rcc_tenuErrorStatus Rcc_enuPllControl(u64 Copy_ControlValue)
{
	u16 Loc_TimeOut=500;
	Rcc_tenuErrorStatus Loc_enuErrorStatus = Rcc_enuNok;
	//checking that the user pass the right argument or not
	if (Copy_ControlValue&CLEAR_MAGIC_NUMBER_MASK)
	{
		//checking the user need the PLL to be ON or OFF
		if(Copy_ControlValue==RCC_u64PLL_ON)
		{
			//enable PLL clock
			Rcc->RCC_CR |= (u32)RCC_u64PLL_ON;
			// i put not here because if while will be false i will break it
			//I make this block of code to check whether
			while(Loc_TimeOut && !(Rcc->RCC_CR&RCC_u32PLL_READY))
			{
				Loc_TimeOut--;
			}
			if(Rcc->RCC_CR &(RCC_u32PLL_READY))
			{
				Loc_enuErrorStatus = Rcc_enuOk;
			}
		}
		/*at anytime you will close any clock source
		 * you must check first that this clk
		 * not the clock of the sysclk
		 * so in the else condition we
		 * will make this validation first
		 **/
		else if (Copy_ControlValue==RCC_u64PLL_OFF)
		{
			if(Rcc_vidGetSysClkStatus()==(u32)RCC_u64SYSCLK_PLL)
			{
				// m4 3arf 27ot 2eh l2ny 2sln fow 3aml initialization ll status b notOk
			}
			else
			{
				Rcc->RCC_CR &=(u32)RCC_u64PLL_OFF ;
				Loc_enuErrorStatus = Rcc_enuOk;
			}
		}
		else
		{
			/*do nothing*/
		}
	}
	else
	{
		Loc_enuErrorStatus =Rcc_enuWrongConfiguration;
	}

	return Loc_enuErrorStatus;
}

/**************************************************************************************/
/**************************************************************************************/
//Hal lazm 2tcheck 2l clk ready wla la2 wla 2sebha keda wla 2l user m4 3aml 2l clk on 2l func htrg3 leh error?
/**************************************************************************************/
/**************************************************************************************/
Rcc_tenuErrorStatus Rcc_enuSelectSysClk(u64 Copy_SysClk)
{
	Rcc_tenuErrorStatus Loc_ErrorStatus = Rcc_enuNok;
	u32 Temp;
	u32 timeout=2000;
	// validate user input
	if(Copy_SysClk&CLEAR_MAGIC_NUMBER_MASK)
	{
		//check if the input arg is the sysclk itself
		if(Rcc_vidGetSysClkStatus()==((u32)Copy_SysClk))
		{
			Loc_ErrorStatus = Rcc_enuOk;
		}
		else
		{
			Temp = Rcc->RCC_CFGR; // because if we clearing the first two bits in reg directly
			//This mean that we will go to different state
			// so when we configure we should make changes in temp var
			// then assign this var to the reg
			Temp &=RCC_SYS_CLK_CLEAR_MASK; // clearing first two bits in the reg
			Temp |=(u32)Copy_SysClk;
			// assigning the sys clk
			Rcc->RCC_CFGR = Temp;
			while (timeout-- && (((Rcc->RCC_CFGR)&SWS_MSK)>>SWS0) != (u32)Copy_SysClk );

			if((((Rcc->RCC_CFGR)&SWS_MSK)>>SWS0) == (u32)Copy_SysClk)
			{
				Loc_ErrorStatus = Rcc_enuOk;
			}
		}
	}
	else
	{
		Loc_ErrorStatus= Rcc_enuWrongConfiguration;
	}
	return Loc_ErrorStatus;
}

Rcc_tenuErrorStatus RCC_enuGetClockRdyStatus(u64 Copy_u8Clock,pu8 Add_pu8RdyStatus)
{
	/*Return Error Variable*/
	Rcc_tenuErrorStatus Loc_ErrorStatus=Rcc_enuNok;

	//	if (Copy_u8Clock & RCC_u32CFGR_SWS_Checking)
	//	{
	if(Add_pu8RdyStatus == NULL)
	{
		Loc_ErrorStatus=Rcc_enuErrorNullPointer;
	}
	else
	{
		Loc_ErrorStatus=Rcc_enuOk;
		switch (Copy_u8Clock)
		{

		case RCC_u64SYSCLK_HSI:
			/*CHECK IF CLK IS RDY AND STORE IT TO THE PASSED ADDRESS*/
			if (Rcc->RCC_CR & RCC_u32HSI_READY) {
				*Add_pu8RdyStatus = RCC_u8Ready;
			} else {
				*Add_pu8RdyStatus = RCC_u8NotReady;
			}
			break;
		case RCC_u64SYSCLK_HSE:
			/*CHECK IF CLK IS RDY AND STORE IT TO THE PASSED ADDRESS*/
			if (Rcc->RCC_CR & RCC_u32HSE_READY) {
				*Add_pu8RdyStatus = RCC_u8Ready;
			} else {
				*Add_pu8RdyStatus = RCC_u8NotReady;
			}
			break;
		case RCC_u64SYSCLK_PLL:
			/*CHECK IF CLK IS RDY AND STORE IT TO THE PASSED ADDRESS*/
			if (Rcc->RCC_CR & RCC_u32PLL_READY) {
				*Add_pu8RdyStatus = RCC_u8Ready;
			} else {
				*Add_pu8RdyStatus = RCC_u8NotReady;
			}
			break;
		}
	}
	//	}
	/*RETURN THE ERROR STATUS*/
	return Loc_ErrorStatus;
}


/*VCO = SCR * (N/M)*/
Rcc_tenuErrorStatus RCC_enuSelectPllConfig(u32 Copy_PLLM,
		u32 Copy_PLLN,
		u32 Copy_PLLP,
		u32 Copy_PLLQ,
		u32 Copy_PLLSRC)
{
	u8 Loc_clkStatus=0;
	Rcc_tenuErrorStatus Loc_ErrorStatus=Rcc_enuNok;
	/*first we will check if the pll is off to have the ability to configure*/
	RCC_enuGetClockRdyStatus((u32)RCC_u64SYSCLK_PLL,&Loc_clkStatus);
	if (Loc_clkStatus==RCC_u8Ready)
	{
		Loc_ErrorStatus=Rcc_enuWrongConfiguration;
	}
	else if(Loc_clkStatus== RCC_u8NotReady)
	{
		/*validation on the inputs*/
		if((Copy_PLLM>=2&&Copy_PLLM<=63)&&
				(Copy_PLLN>=192&&Copy_PLLN<=432)&&
				((Copy_PLLP>=2 &&Copy_PLLP<=8)&&Copy_PLLP%2==0)&&
				(Copy_PLLQ>=2&&Copy_PLLQ<=15)&&
				(Copy_PLLSRC==RCC_PLLSRC_HSI_MASK || Copy_PLLSRC==RCC_PLLSRC_HSE_MASK))
		{
			Loc_ErrorStatus=Rcc_enuOk;
			Rcc->RCC_PLLCFGR = (Copy_PLLM|Copy_PLLN|Copy_PLLQ|Copy_PLLP|Copy_PLLSRC);

		}
		else
		{
			Loc_ErrorStatus=Rcc_enuWrongConfiguration;
		}
	}
	return Loc_ErrorStatus;
}
/*this fucntion is to enable the clock of a desired peripheral*/
Rcc_tenuErrorStatus Rcc_enuEnablePeripheralClk(u8 copy_u8Bus ,u64 copy_u64RccPeripheralClk)
{
	Rcc_tenuErrorStatus Loc_enuErrorStatus=Rcc_enuNok;
	//checking if the user pass the right args or wrong one
	if((copy_u64RccPeripheralClk&CLEAR_MAGIC_NUMBER_MASK)==0)
	{
		Loc_enuErrorStatus=Rcc_enuWrongPeripheralClk;
	}
	else
	{
		Loc_enuErrorStatus = Rcc_enuOk;
		//switch on the desired bus to be enabled
		switch(copy_u8Bus)
		{
		case RCC_u8BUS_APB1:
			Rcc->RCC_APB1ENR |= (u32)copy_u64RccPeripheralClk;
			break;
		case RCC_u8BUS_APB2:
			Rcc->RCC_APB2ENR |= (u32)copy_u64RccPeripheralClk;
			break;
		case RCC_u8BUS_AHB1:
			Rcc->RCC_AHB1ENR |= (u32)copy_u64RccPeripheralClk;
			break;
		case RCC_u8BUS_AHB2:
			Rcc->RCC_AHB2ENR |= (u32)copy_u64RccPeripheralClk;
			break;

		default:
			Loc_enuErrorStatus=Rcc_enuWrongBus;
			break;
		}
	}
	return Loc_enuErrorStatus;
}
/*this fucntion is to disable the clock of a desired peripheral*/
Rcc_tenuErrorStatus Rcc_enuDisablePeripheralClk(u8 copy_u8Bus ,u64 copy_u64RccPeripheralClk)
{
	Rcc_tenuErrorStatus Loc_enuErrorStatus=Rcc_enuNok;
	//checking if the user pass the right args or wrong one
	if((copy_u64RccPeripheralClk&CLEAR_MAGIC_NUMBER_MASK)==0)
	{
		Loc_enuErrorStatus=Rcc_enuWrongPeripheralClk;
	}
	else
	{
		Loc_enuErrorStatus = Rcc_enuOk;
		//switch on the desired bus to be disabled
		switch(copy_u8Bus)
		{
		case RCC_u8BUS_APB1:
			Rcc->RCC_APB1ENR &=~ (u32)copy_u64RccPeripheralClk;
			break;
		case RCC_u8BUS_APB2:
			Rcc->RCC_APB2ENR &=~ (u32)copy_u64RccPeripheralClk;
			break;
		case RCC_u8BUS_AHB1:
			Rcc->RCC_AHB1ENR &=~ (u32)copy_u64RccPeripheralClk;
			break;
		case RCC_u8BUS_AHB2:
			Rcc->RCC_AHB2ENR &=~ (u32)copy_u64RccPeripheralClk;
			break;

		default:
			Loc_enuErrorStatus=Rcc_enuWrongBus;
			break;
		}

	}
	return Loc_enuErrorStatus;
}

Rcc_tenuErrorStatus Rcc_enuSelectBusPrescaler(u64 Copy_u64Prescaler)
{
	Rcc_tenuErrorStatus Loc_enuErrorStatus=Rcc_enuNok;
	if((Copy_u64Prescaler&CLEAR_MAGIC_NUMBER_MASK)==0)
	{
		Loc_enuErrorStatus=Rcc_enuWrongConfiguration;
	}
	else
	{
		Loc_enuErrorStatus=Rcc_enuOk;
		u32 temp;
//		temp = Rcc->RCC_CFGR;
//		temp &= Copy_u64Prescaler;
//		switch()
//		{
//
//		}
		switch(Copy_u64Prescaler)
		{
		case RCC_u32APB1_NOT_DIVIDED:
			temp = Rcc->RCC_CFGR;
			temp &= (u32)RCC_u32APB1_NOT_DIVIDED;
			temp |= (u32)Copy_u64Prescaler;
			Rcc->RCC_CFGR = temp;
			break;
		case RCC_u32APB1_DIV_BY_2:
			temp = Rcc->RCC_CFGR;
			temp &= (u32)RCC_u32APB1_NOT_DIVIDED;
			temp |= (u32)Copy_u64Prescaler;
			Rcc->RCC_CFGR = temp;
			break;
		case RCC_u32APB1_DIV_BY_4:
			temp = Rcc->RCC_CFGR;
			temp &= (u32)RCC_u32APB1_NOT_DIVIDED;
			temp |= (u32)Copy_u64Prescaler;
			Rcc->RCC_CFGR = temp;
			break;
		case RCC_u32APB1_DIV_BY_8:
			temp = Rcc->RCC_CFGR;
			temp &= (u32)RCC_u32APB1_NOT_DIVIDED;
			temp |= (u32)Copy_u64Prescaler;
			Rcc->RCC_CFGR = temp;
			break;
		case RCC_u32APB1_DIV_BY_16:
			temp = Rcc->RCC_CFGR;
			temp &= (u32)RCC_u32APB1_NOT_DIVIDED;
			temp |= (u32)Copy_u64Prescaler;
			Rcc->RCC_CFGR = temp;
			break;
		case RCC_u32APB2_NOT_DIVIDED:
			temp = Rcc->RCC_CFGR;
			temp &= (u32)RCC_u32APB2_NOT_DIVIDED;
			temp |= (u32)Copy_u64Prescaler;
			Rcc->RCC_CFGR = temp;
			break;
		case RCC_u32APB2_DIV_BY_2:
			temp = Rcc->RCC_CFGR;
			temp &= (u32)RCC_u32APB2_NOT_DIVIDED;
			temp |= (u32)Copy_u64Prescaler;
			Rcc->RCC_CFGR = temp;
			break;
		case RCC_u32APB2_DIV_BY_4:
			temp = Rcc->RCC_CFGR;
			temp &= (u32)RCC_u32APB2_NOT_DIVIDED;
			temp |= (u32)Copy_u64Prescaler;
			Rcc->RCC_CFGR = temp;
			break;
		case RCC_u32APB2_DIV_BY_8:
			temp = Rcc->RCC_CFGR;
			temp &= (u32)RCC_u32APB2_NOT_DIVIDED;
			temp |= (u32)Copy_u64Prescaler;
			Rcc->RCC_CFGR = temp;
			break;
		case RCC_u32APB2_DIV_BY_16:
			temp = Rcc->RCC_CFGR;
			temp &= (u32)RCC_u32APB2_NOT_DIVIDED;
			temp |= (u32)Copy_u64Prescaler;
			Rcc->RCC_CFGR = temp;
			break;
		case RCC_u32AHB_NOT_DIVIDED:
			temp = Rcc->RCC_CFGR;
			temp &= (u32)RCC_u32AHB_NOT_DIVIDED;
			temp |= (u32)Copy_u64Prescaler;
			Rcc->RCC_CFGR = temp;
			break;
		case RCC_u32AHB_DIV_BY_2:
			temp = Rcc->RCC_CFGR;
			temp &= (u32)RCC_u32AHB_NOT_DIVIDED;
			temp |= (u32)Copy_u64Prescaler;
			Rcc->RCC_CFGR = temp;
			break;
		case RCC_u32AHB_DIV_BY_4:
			temp = Rcc->RCC_CFGR;
			temp &= (u32)RCC_u32AHB_NOT_DIVIDED;
			temp |= (u32)Copy_u64Prescaler;
			Rcc->RCC_CFGR = temp;
			break;
		case RCC_u32AHB_DIV_BY_8:
			temp = Rcc->RCC_CFGR;
			temp &= (u32)RCC_u32AHB_NOT_DIVIDED;
			temp |= (u32)Copy_u64Prescaler;
			Rcc->RCC_CFGR = temp;
			break;
		case RCC_u32AHB_DIV_BY_16:
			temp = Rcc->RCC_CFGR;
			temp &= (u32)RCC_u32AHB_NOT_DIVIDED;
			temp |= (u32)Copy_u64Prescaler;
			Rcc->RCC_CFGR = temp;
			break;
		case RCC_u32AHB_DIV_BY_64:
			temp = Rcc->RCC_CFGR;
			temp &= (u32)RCC_u32AHB_NOT_DIVIDED;
			temp |= (u32)Copy_u64Prescaler;
			Rcc->RCC_CFGR = temp;
			break;
		case RCC_u32AHB_DIV_BY_128:
			temp = Rcc->RCC_CFGR;
			temp &= (u32)RCC_u32AHB_NOT_DIVIDED;
			temp |= (u32)Copy_u64Prescaler;
			Rcc->RCC_CFGR = temp;
			break;
		case RCC_u32AHB_DIV_BY_256:
			temp = Rcc->RCC_CFGR;
			temp &= (u32)RCC_u32AHB_NOT_DIVIDED;
			temp |= (u32)Copy_u64Prescaler;
			Rcc->RCC_CFGR = temp;
			break;
		case RCC_u32AHB_DIV_BY_512:
			temp = Rcc->RCC_CFGR;
			temp &= (u32)RCC_u32AHB_NOT_DIVIDED;
			temp |= (u32)Copy_u64Prescaler;
			Rcc->RCC_CFGR = temp;
			break;
		default:
			Loc_enuErrorStatus=Rcc_enuNok;
			break;
		}
	}
	return Loc_enuErrorStatus;
}
