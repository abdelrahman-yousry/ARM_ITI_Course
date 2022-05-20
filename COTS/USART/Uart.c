/*
 * Uart.c
 *
 *  Created on: Apr 28, 2022
 *      Author: Abdelrahman Yousry
 */
#include "Std_types.h"
#include "Uart.h"
#include "Uart_prv.h"

/*Global Array for saving the address of the call back funcs */
pcbf Uart_pcbfManCbf[3];


Usart_tenuErrorStatus Uart_enuInit(Uart_tCfg* copy_UartCfg)
{
	Usart_tenuErrorStatus Loc_enuErrorStatus = Usart_enuOk;
	if ((copy_UartCfg->Usart_pvChannel) == NULL)
	{
		Loc_enuErrorStatus = Usart_enuNullptr;
	}
	u32 UsartDiv =0 ;//local var for calc the UsartDiv which is equal clk/overSampling* BaudRate
	u32 UsartMantissa= 0 ;// for calc the mantissa which is the correct number
	u32 UsartFraction = 0;// for cal the fraction number
	Uart_tstrReg* Loc_ptrReg = copy_UartCfg->Usart_pvChannel ;
	if(copy_UartCfg->Usart_u16OverSampling==USART_u16MASK_OVERSAMPLING_16)
	{
		/*Tx/Rx baud = fCK/8 × (2 – OVER8) × USARTDIV*/
		UsartDiv = (u32)(((u64)((u64)copy_UartCfg->Usart_u64Clock)*1000)/(16*copy_UartCfg->Usart_u16BaudRate));
		UsartFraction = UsartDiv%1000;
		UsartFraction *=16 ;
	}
	else if(copy_UartCfg->Usart_u16OverSampling==USART_u16MASK_OVERSAMPLING_8)
	{
		//16000000000/8*9600=208 333
		UsartDiv =(u32)( ((u64)((u64)copy_UartCfg->Usart_u64Clock)*1000)/(8*copy_UartCfg->Usart_u16BaudRate));
		UsartFraction = UsartDiv%1000;
		UsartFraction *=8;
	}
	UsartFraction=(UsartFraction+500)/1000;
	UsartMantissa=UsartDiv/1000;
	Loc_ptrReg->USART_BRR=(UsartMantissa<<4)|UsartFraction;
	Loc_ptrReg->USART_CR1&=~USART_u16CR1_CLR_MASK;
	Loc_ptrReg->USART_CR1=(
			copy_UartCfg->Usart_u16OverSampling|//Oversampling mode
			copy_UartCfg->Usart_u16DataLength|	//This bit determines the word length. It is set or cleared by software.
			//0: 1 Start bit, 8 Data bits, n Stop bit
			//1: 1 Start bit, 9 Data bits, n Stop bit
			copy_UartCfg->Usart_u16InterruptCtrl|//This bit enables/disables the interrupt.
			copy_UartCfg->Usart_u16TransmitCtrl|//This bit enables/disables the transmitter.
			copy_UartCfg->Usart_u16RecieveCtrl);//This bit enables/disables the receiver.
	Loc_ptrReg->USART_CR1|=USART_u16MASK_UE_ENABLE;//(enable uart) UE in CTRl1 reg

	Loc_ptrReg->USART_CR2&=USART_u16CR2_CLR_MASK;
	Loc_ptrReg->USART_CR2|=USART_u16MASK_ONE_STOP_BIT;

	return Loc_enuErrorStatus;


}

/**Synchronous Function for sending byte**/
Usart_tenuErrorStatus Usart_enuSendDataSync(u32 Byte, void* Channel)
{
	Usart_tenuErrorStatus Loc_enuErrorStatus = Usart_enuOk;
	if (Channel == NULL)
	{
		Loc_enuErrorStatus = Usart_enuNullptr;
	}
	//polling till the TC flag is raised to one when data has been all shifted to be sent
	while(((((Uart_tstrReg*)Channel)->USART_SR)&USART_u16TC_MASK)==0);//TXE if 1 the data in shadow reg is sent to the shift reg
	((Uart_tstrReg*)Channel)->USART_DR = Byte;

	return Loc_enuErrorStatus;
}


/**Synchronous Function to recieve byte from another mcu**/
Usart_tenuErrorStatus Usart_enuRecieveDataSync(void* Channel, pu32 Copy_u32AddResult)
{
	Usart_tenuErrorStatus Loc_enuErrorStatus = Usart_enuOk;
	if (Channel == NULL)
	{
		Loc_enuErrorStatus = Usart_enuNullptr;
	}
	//polling till the RXNE flag is raised to one when data has been all shifted to the DR register
	while(((((Uart_tstrReg*)Channel)->USART_SR)&USART_u16RXNE_MASK)==0);
	*Copy_u32AddResult=((Uart_tstrReg*)Channel)->USART_DR;
	return Loc_enuErrorStatus;
}
/**************************************Asynchronous Function*************************************************/
/**Asynchronous Function for sending byte**/
Usart_tenuErrorStatus Usart_enuSendDataAsync(u32 Copy_u32Data, void* Channel)
{

	Usart_tenuErrorStatus Loc_enuErrorStatus = Usart_enuNok;
	if (Channel == NULL)
	{
		Loc_enuErrorStatus = Usart_enuNullptr;
	}
	/*validatio on the data*/
	else if((Copy_u32Data&USART_u16DATA_LENGTH_VALIDATION) !=0)
	{
		Loc_enuErrorStatus =Usart_enuInvalidDataLength;
	}
	//check on the flag of the TXE to ensure that the DR reg is empty
	else if((((Uart_tstrReg*)Channel)->USART_SR) & USART_u16TXE)
	{
		Loc_enuErrorStatus = Usart_enuOk;
		((Uart_tstrReg*)Channel)->USART_DR =Copy_u32Data;
	}

	else
	{
		/*do nothing (MISRA)*/
	}
	return Loc_enuErrorStatus;
}


/**Asynchronous Function to recieve byte from another mcu**/
Usart_tenuErrorStatus Usart_enuRecieveDataAsync(void* Channel, pu8 Copy_u8AddResult)
{
	Usart_tenuErrorStatus Loc_enuErrorStatus = Usart_enuOk;
	if (Channel == NULL)
	{
		Loc_enuErrorStatus = Usart_enuNullptr;
	}
	//polling till the RXNE flag is raised to one when data has been all shifted to the DR reg
	else if(((Uart_tstrReg*)Channel)->USART_SR&USART_u16RXNE_MASK)
	{
		*Copy_u8AddResult=((Uart_tstrReg*)Channel)->USART_DR;
	}
	else
	{
		/*do nothing*/
	}
	return Loc_enuErrorStatus;
}
/**************************Function to get the TC flag value *********************/
/*if the transmission completed it will return 1 else will return 1*/
u8 Usart_u8ReadTcFlag(void* Copy_pvidChannel)
{
	u8 Loc_u8FlagValue=0 ;
	Loc_u8FlagValue=((((Uart_tstrReg*)Copy_pvidChannel)->USART_SR)&USART_u16TC_MASK);
	return Loc_u8FlagValue;
}
u8 Usart_u8ReadRxFlag(void* Copy_pvidChannel)
{
	u8 Loc_u8FlagValue=0 ;
	Loc_u8FlagValue=((((Uart_tstrReg*)Copy_pvidChannel)->USART_SR)&USART_u16RXNE_MASK);
	return Loc_u8FlagValue;
}
/*Clearing Tc interrupt flag*/
Usart_tenuErrorStatus Uart_ClearTcFlag(void * Copy_pvidChannel)
{
	Usart_tenuErrorStatus Loc_enuReturnStatus=Usart_enuOk;
	if (Copy_pvidChannel == NULL) {
		Loc_enuReturnStatus = Usart_enuNullptr;
	} else {
		(((Uart_tstrReg*)Copy_pvidChannel)->USART_SR) &=UART_u16CLEAR_TC_MASK;
	}
	return Loc_enuReturnStatus;
}
/*Clearing Rx interrupt flag*/
Usart_tenuErrorStatus Uart_ClearRxFlag(void * Copy_pvidChannel)
{
	Usart_tenuErrorStatus Loc_enuReturnStatus=Usart_enuOk;
	if (Copy_pvidChannel == NULL) {
		Loc_enuReturnStatus = Usart_enuNullptr;
	} else {
		(((Uart_tstrReg*)Copy_pvidChannel)->USART_SR) &=UART_u16CLEAR_RXNEIE_MASK;
	}
	return Loc_enuReturnStatus;
}

/************************************Control Function *********************************/
Usart_tenuErrorStatus Usart_enuTcInterruptCtrl(void* Copy_pvChannel, tenu_UsartInterruptState Copy_enuIntState)
{
	Usart_tenuErrorStatus Loc_enuReturnStatus=Usart_enuNok;
	if (Copy_pvChannel==NULL)
	{
		Loc_enuReturnStatus = Usart_enuNullptr;
	}
	else
	{
		Loc_enuReturnStatus=Usart_enuOk;
		switch (Copy_enuIntState)
		{
		case Usart_enuIntEnabled:
			(((Uart_tstrReg*)Copy_pvChannel)->USART_CR1) |=USART_u16INT_TC_ENABLE;
			break;
		case Usart_enuIntDisabled:
			(((Uart_tstrReg*)Copy_pvChannel)->USART_CR1) &=~(USART_u16INT_TC_ENABLE);
			break;
		}
	}
	return Loc_enuReturnStatus;
}
Usart_tenuErrorStatus Usart_enuRxInterruptCtrl(void* Copy_pvChannel, tenu_UsartInterruptState Copy_enuIntState)
{
	Usart_tenuErrorStatus Loc_enuReturnStatus=Usart_enuNok;
	if (Copy_pvChannel==NULL)
	{
		Loc_enuReturnStatus = Usart_enuNullptr;
	}
	else
	{
		Loc_enuReturnStatus=Usart_enuOk;
		switch (Copy_enuIntState)
		{
		case Usart_enuIntEnabled:
			(((Uart_tstrReg*)Copy_pvChannel)->USART_CR1) |=USART_u16INT_RXNE_ENABLE;
			break;
		case Usart_enuIntDisabled:
			(((Uart_tstrReg*)Copy_pvChannel)->USART_CR1) &=~(USART_u16INT_RXNE_ENABLE);
			break;
		}
	}
	return Loc_enuReturnStatus;
}

/********************Register call back function in the Manager/Hal layer******************/
Usart_tenuErrorStatus Uart_enuRegisterHalCbf(pcbf Uart_pcbfManCallBack,u8 Copy_u8BusNum)
{
	Usart_tenuErrorStatus Loc_enuErrorStatus;
	if(Uart_pcbfManCallBack==NULL)
	{
		Loc_enuErrorStatus = Usart_enuNullptr;
	}
	else
	{
		Uart_pcbfManCbf[Copy_u8BusNum]=Uart_pcbfManCallBack;
	}

	return Loc_enuErrorStatus;
}
/*********************************Handlers***************************************/
void USART1_IRQHandler(void)
{
  if(Uart_pcbfManCbf[USART_BUS_NUMBER_1])
  {
    Uart_pcbfManCbf[USART_BUS_NUMBER_1]();
  }
}
void USART2_IRQHandler(void)
{
  if(Uart_pcbfManCbf[USART_BUS_NUMBER_2])
  {
    Uart_pcbfManCbf[USART_BUS_NUMBER_2]();
  }
}
void USART6_IRQHandler(void)
{
  if(Uart_pcbfManCbf[USART_BUS_NUMBER_6])
  {
    Uart_pcbfManCbf[USART_BUS_NUMBER_6]();
  }
}


