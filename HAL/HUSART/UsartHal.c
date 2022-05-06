/*
 * UsartHal.c
 *
 *  Created on: May 2, 2022
 *      Author: U3
 */
#include "Std_types.h"
#include "NVIC.h"
#include "Rcc.h"
#include "Gpio.h"
#include "Uart.h"
#include "UsartHal.h"
#include "UsartHal_cfg.h"
#include "UsartHal_prv.h"


//*These function will be registered as a call back function which will be called by the MCAL layer*//
static void Usart1_vidHandlerCbf(void);
static void Usart2_vidHandlerCbf(void);
static void Usart6_vidHandlerCbf(void);


static u8 Usart1_TxBsy ;
static u8 Usart2_TxBsy ;
static u8 Usart6_TxBsy ;

static u8 Usart1_RxBsy ;
static u8 Usart2_RxBsy ;
static u8 Usart6_RxBsy ;


static t_Buffer Usart1_TxGlobalBuffer;
static t_Buffer Usart2_TxGlobalBuffer;
static t_Buffer Usart6_TxGlobalBuffer;

static t_Buffer Usart1_RxGlobalBuffer;
static t_Buffer Usart2_RxGlobalBuffer;
static t_Buffer Usart6_RxGlobalBuffer;

pcbf Usart_pcbfTxNotifyApp[MAX_NUM_OF_BUSNUM];
pcbf Usart_pcbfRxNotifyApp[MAX_NUM_OF_BUSNUM];


extern const t_UsartCfg Usart_DeviceCfg[MAX_NUM_OF_DEVICES];
/*before call this func in app you should go to the cfg file and put your configuration
 * this function then will handle the RCC clk ad enable the USART in the NVIC
 *
 * */
void Usart_vidHalInit(void)
{
	Uart_tCfg Uart_cfg;
	/*Declaring GpioCfg var to configure Pin A9 and Pin A10 as a Tx and Rx*/
	GpioPinCfg_t GpioCfg1,GpioCfg2;
	u8 iterator;
	for(iterator=0; iterator<MAX_NUM_OF_DEVICES ; iterator ++)
	{
		Uart_cfg.Usart_pvChannel=Usart_DeviceCfg[iterator].Usart_pvChannel;
		Uart_cfg.Usart_u32BaudRate=Usart_DeviceCfg[iterator].Usart_u16BaudRate;
		Uart_cfg.Usart_u32DataLength=Usart_DeviceCfg[iterator].Usart_u16DataLength;
		Uart_cfg.Usart_u32InterruptCtrl=Usart_DeviceCfg[iterator].Usart_u16InterruptCtrl;
		Uart_cfg.Usart_u32NumStopBit=Usart_DeviceCfg[iterator].Usart_u32NumStopBit;
		Uart_cfg.Usart_u32OverSampling=Usart_DeviceCfg[iterator].Usart_u16OverSampling;
		Uart_cfg.Usart_u32RecieveCtrl=Usart_DeviceCfg[iterator].Usart_u16RecieveCtrl;
		Uart_cfg.Usart_u32TransmitCtrl=Usart_DeviceCfg[iterator].Usart_u16TransmitCtrl;
		Uart_cfg.Usart_u32Clock=Usart_DeviceCfg[iterator].Usart_u32Clock;
		switch ((u32)Usart_DeviceCfg[iterator].Usart_pvChannel)
		{
		case (u32)USART_1:
				/*Enable GPIO clock peripheral*/
				Rcc_enuEnablePeripheralClk(RCC_u8BUS_AHB1,RCC_u32AHB1_GPIOA);
		/*Configuration of Pin A9*/
		GpioCfg1.mode=GPIO_u8MODE_AF_PP;
		GpioCfg1.port=GPIO_A;
		GpioCfg1.pin=GPIO_u8PIN_9;
		GpioCfg1.AF=GPIO_u8ALTERNATE_FUNC_07;
		GpioCfg1.speed=GPIO_u8SPEED_HIGH;
		/*Configuration of Pin A10*/
		GpioCfg2.mode=GPIO_u8MODE_AF_PP;
		GpioCfg2.port=GPIO_A;
		GpioCfg2.pin=GPIO_u8PIN_10;
		GpioCfg2.AF=GPIO_u8ALTERNATE_FUNC_07;
		GpioCfg2.speed=GPIO_u8SPEED_HIGH;
		Gpio_enuInit(&GpioCfg1);
		Gpio_enuInit(&GpioCfg2);

		/*Enable Usart*/
		Rcc_enuEnablePeripheralClk(RCC_u8BUS_APB2,RCC_u32APB2_USART1);
		NVIC_enuEnableIRQ(NVIC_USART1_IRQn);
		Uart_ClearTcFlag(USART_1);
		break;
		case (u32)USART_2:
				/*Enable GPIO clock peripheral*/
				Rcc_enuEnablePeripheralClk(RCC_u8BUS_AHB1,RCC_u32AHB1_GPIOA);
		/*Configuration of Pin A9*/
		GpioCfg1.mode=GPIO_u8MODE_AF_PP;
		GpioCfg1.port=GPIO_A;
		GpioCfg1.pin=GPIO_u8PIN_1;
		GpioCfg1.AF=GPIO_u8ALTERNATE_FUNC_07;
		GpioCfg1.speed=GPIO_u8SPEED_HIGH;
		/*Configuration of Pin A10*/
		GpioCfg2.mode=GPIO_u8MODE_AF_PP;
		GpioCfg2.port=GPIO_A;
		GpioCfg2.pin=GPIO_u8PIN_2;
		GpioCfg2.AF=GPIO_u8ALTERNATE_FUNC_07;
		GpioCfg2.speed=GPIO_u8SPEED_HIGH;
		Gpio_enuInit(&GpioCfg1);
		Gpio_enuInit(&GpioCfg2);

		/*Enable Usart*/
		Rcc_enuEnablePeripheralClk(RCC_u8BUS_APB1,RCC_u32APB1_USART2);
		NVIC_enuEnableIRQ(NVIC_USART2_IRQn);
		Uart_ClearTcFlag(USART_2);
		break;
		case (u32)USART_6:
				Rcc_enuEnablePeripheralClk(RCC_u8BUS_AHB1,RCC_u32AHB1_GPIOC);
		/*Configuration of Pin A9*/
		GpioCfg1.mode=GPIO_u8MODE_AF_PP;
		GpioCfg1.port=GPIO_C;
		GpioCfg1.pin=GPIO_u8PIN_6;
		GpioCfg1.AF=GPIO_u8ALTERNATE_FUNC_08;
		GpioCfg1.speed=GPIO_u8SPEED_HIGH;
		/*Configuration of Pin A10*/
		GpioCfg2.mode=GPIO_u8MODE_AF_PP;
		GpioCfg2.port=GPIO_C;
		GpioCfg2.pin=GPIO_u8PIN_7;
		GpioCfg2.AF=GPIO_u8ALTERNATE_FUNC_08;
		GpioCfg2.speed=GPIO_u8SPEED_HIGH;
		Gpio_enuInit(&GpioCfg1);
		Gpio_enuInit(&GpioCfg2);

		/*Enable Usart*/
		Rcc_enuEnablePeripheralClk(RCC_u8BUS_APB2,RCC_u32APB2_USART6);
		NVIC_enuEnableIRQ(NVIC_USART6_IRQn);
		Uart_ClearTcFlag(USART_6);
		break;
		}
		Uart_enuInit(&Uart_cfg);
	}

	/*Registering the CBF which will be called by the MCAL uart driver in the handler*/
	Uart_enuRegisterHalCbf(Usart1_vidHandlerCbf,USART_BUSNUM_1);
	Uart_enuRegisterHalCbf(Usart2_vidHandlerCbf,USART_BUSNUM_2);
	Uart_enuRegisterHalCbf(Usart6_vidHandlerCbf,USART_BUSNUM_6);

}


UsartHal_tenuErrorStatus Usart_enuSendBufferZc(pu8 Z_pu8Buffer, u16 copy_u16Size, t_enuUsartBusNum Copy_enuBusNum)
{
	UsartHal_tenuErrorStatus Loc_enuErrorStatus = UsartHal_enuOk;
	if(Z_pu8Buffer == NULL)
	{
		Loc_enuErrorStatus = UsartHal_enuNullptr;
	}
	else if(Copy_enuBusNum > Usart_enuMaxBusNum )
	{
		Loc_enuErrorStatus =UsartHal_enuInvalidBusNum;
	}
	else if(Usart1_TxBsy == 0)
	{
		switch(Copy_enuBusNum)
		{
		case Usart_enuBusNum_1:
			Usart1_TxBsy = 1;
			Usart1_TxGlobalBuffer.buffer = Z_pu8Buffer;
			Usart1_TxGlobalBuffer.size = copy_u16Size;
			Usart1_TxGlobalBuffer.used = 1;
			Usart_enuSendDataAsync(Usart1_TxGlobalBuffer.buffer[0],Usart_DeviceCfg->Usart_pvChannel);
			Usart_enuTcInterruptCtrl(USART_1,Usart_enuIntEnabled);
			break;

		case Usart_enuBusNum_2:
			Usart2_TxBsy = 1;
			Usart2_TxGlobalBuffer.buffer = Z_pu8Buffer;
			Usart2_TxGlobalBuffer.size = copy_u16Size;
			Usart2_TxGlobalBuffer.used = 1;
			Usart_enuSendDataAsync(Usart2_TxGlobalBuffer.buffer[0],Usart_DeviceCfg->Usart_pvChannel);
			Usart_enuTcInterruptCtrl(USART_2,Usart_enuIntEnabled);
			break;

		case Usart_enuBusNum_6:
			Usart6_TxBsy = 1;
			Usart6_TxGlobalBuffer.buffer = Z_pu8Buffer;
			Usart6_TxGlobalBuffer.size = copy_u16Size;
			Usart6_TxGlobalBuffer.used = 1;
			Usart_enuSendDataAsync(Usart6_TxGlobalBuffer.buffer[0],Usart_DeviceCfg->Usart_pvChannel);
			Usart_enuTcInterruptCtrl(USART_6,Usart_enuIntEnabled);
			break;
		}
	}
	else
	{
		/*do nothing (MISRA)*/
	}

	return Loc_enuErrorStatus;
}
/*first arg is pointer to the buffer created by the user in the app layer which will be filled after the notify cbf which will
 * be called by the handler of the bus which is the thirdarg
 * second arg is the size of the buffer sent
 * */
UsartHal_tenuErrorStatus Usart_enuRecieveBufferZc(pu8 Z_pu8Buffer, u16 copy_u16Size,t_enuUsartBusNum Copy_enuBusNum)
{
	UsartHal_tenuErrorStatus Loc_enuErrorStatus = UsartHal_enuOk;
	if(Z_pu8Buffer == NULL)
	{
		Loc_enuErrorStatus = UsartHal_enuNullptr;
	}
	else if(Copy_enuBusNum > Usart_enuMaxBusNum )
	{
		Loc_enuErrorStatus =UsartHal_enuInvalidBusNum;
	}
	else
	{
		switch(Copy_enuBusNum)
		{
		case Usart_enuBusNum_1:
			if(Usart1_RxBsy == 0)
			{
				Usart1_RxBsy = 1;
				Usart1_RxGlobalBuffer.buffer = Z_pu8Buffer;
				Usart1_RxGlobalBuffer.size = copy_u16Size;
				Usart1_RxGlobalBuffer.used = 1;
				/*Action we did that we tell that the next byte which will come is imp for me*/
				Usart_enuRxInterruptCtrl(USART_1,Usart_enuIntEnabled);//******xxxxxxxxxxx**********//
			}
			break;

		case Usart_enuBusNum_2:
			if(Usart2_RxBsy == 0)
			{
				Usart2_RxBsy = 1;
				Usart2_RxGlobalBuffer.buffer = Z_pu8Buffer;
				Usart2_RxGlobalBuffer.size = copy_u16Size;
				Usart2_RxGlobalBuffer.used = 1;
				Usart_enuRxInterruptCtrl(USART_2,Usart_enuIntEnabled);//******xxxxxxxxxxx**********//
			}
			break;

		case Usart_enuBusNum_6:
			if(Usart6_RxBsy == 0)
			{
				Usart6_RxBsy = 1;
				Usart6_RxGlobalBuffer.buffer = Z_pu8Buffer;
				Usart6_RxGlobalBuffer.size = copy_u16Size;
				Usart6_RxGlobalBuffer.used = 1;
				Usart_enuRxInterruptCtrl(USART_6,Usart_enuIntEnabled);//******xxxxxxxxxxx**********//
			}
			break;
		}
	}
	return Loc_enuErrorStatus;
}

/********************************Wrapper Functions*************************************************/

UsartHal_tenuErrorStatus Usart_enuSendDataSync(u32 Copy_u32Data,t_enuUsartBusNum Copy_enuBusNum)
{
	UsartHal_tenuErrorStatus Loc_enuErrorStatus = Usart_enuOk;
	switch (Copy_enuBusNum)
	{
	case Usart_enuBusNum_1:
		Usart_vidSendDataSync(Copy_u32Data,USART_1);
		break;
	case Usart_enuBusNum_2:
		Usart_vidSendDataSync(Copy_u32Data,USART_2);
		break;
	case Usart_enuBusNum_6:
		Usart_vidSendDataSync(Copy_u32Data,USART_6);
		break;
	default:
		Loc_enuErrorStatus = UsartHal_enuInvalidBusNum;
		break;
	}
	return Loc_enuErrorStatus;
}
/****************************************************************************/
pu32 Usart_pu32ReciveDataSync(u32 Copy_u32Data,t_enuUsartBusNum Copy_enuBusNum)
{
	UsartHal_tenuErrorStatus Loc_enuErrorStatus = Usart_enuOk;
	pu32 Loc_Result;
	switch (Copy_enuBusNum)
	{
	case Usart_enuBusNum_1:
		Usart_vidRecieveDataSync(USART_1,Loc_Result);
		break;
	case Usart_enuBusNum_2:
		Usart_vidRecieveDataSync(USART_2,Loc_Result);
		break;
	case Usart_enuBusNum_6:
		Usart_vidRecieveDataSync(USART_6,Loc_Result);
		break;
	default:
		Loc_enuErrorStatus = UsartHal_enuInvalidBusNum;
		break;
	}
	return Loc_Result;
}

/************************************************************************************************/
UsartHal_tenuErrorStatus Usart_enuRegTxCompNotifyCbf(pcallback Usart_pcbfNotifyApp,t_enuUsartBusNum Copy_enuUsartBusNum)
{
	Usart_tenuErrorStatus Loc_enuErrorStatus;
	if(Usart_pcbfNotifyApp==NULL)
	{
		Loc_enuErrorStatus = Usart_enuNullptr;
	}
	else
	{
		switch((u32)(Copy_enuUsartBusNum))
		{
		case Usart_enuBusNum_1:
			Usart_pcbfTxNotifyApp[Usart_enuBusNum_1]=Usart_pcbfNotifyApp;
			break;

		case Usart_enuBusNum_2:
			Usart_pcbfTxNotifyApp[Usart_enuBusNum_2]=Usart_pcbfNotifyApp;
			break;

		case Usart_enuBusNum_6:
			Usart_pcbfTxNotifyApp[Usart_enuBusNum_6]=Usart_pcbfNotifyApp;
			break;
		}
	}
	return Loc_enuErrorStatus;
}
UsartHal_tenuErrorStatus Usart_enuRegRxCompNotifyCbf(pcallback Usart_pcbfNotifyApp,t_enuUsartBusNum Copy_enuUsartBusNum)
{
	Usart_tenuErrorStatus Loc_enuErrorStatus;
	if(Usart_pcbfNotifyApp==NULL)
	{
		Loc_enuErrorStatus = Usart_enuNullptr;
	}
	else
	{
		switch((u32)(Copy_enuUsartBusNum))
		{
		case Usart_enuBusNum_1:
			Usart_pcbfRxNotifyApp[Usart_enuBusNum_1]=Usart_pcbfNotifyApp;
			break;

		case Usart_enuBusNum_2:
			Usart_pcbfRxNotifyApp[Usart_enuBusNum_2]=Usart_pcbfNotifyApp;
			break;

		case Usart_enuBusNum_6:
			Usart_pcbfRxNotifyApp[Usart_enuBusNum_6]=Usart_pcbfNotifyApp;
			break;
		}
	}

	return Loc_enuErrorStatus;
}

// in this controller we have only one handler for the BUS
// so we should in this handler checking on the flags to know we enter the handler because of what?
// in AVR we have handler for Tx and another one for Rx
static void Usart1_vidHandlerCbf(void)
{
	if(Usart_u8ReadTcFlag(USART_1) && (Usart1_TxBsy == 1)) // checking on TC flag because we may enter
		// the handler because of RX also and for parity ..etc..
		// also we check on TxBsy because if the TC flag is raised after finishing Sending the data, if we not check the
		//TxBsy flag we will enter in this condition while we sent the req data and we may come to this handler for recieving data
		// not sending
	{
		if(Usart1_TxGlobalBuffer.used == Usart1_TxGlobalBuffer.size)
		{
			Usart1_TxBsy = 0;
			Usart1_TxGlobalBuffer.used = 0;
			Usart1_TxGlobalBuffer.size = 0; // may not clear this flags bec if the user send another buffer, he will corrupt them
			Usart_enuTcInterruptCtrl(USART_1,Usart_enuIntDisabled);
			if(Usart_pcbfTxNotifyApp[Usart_enuBusNum_1]!=NULL)
			{
				Usart_pcbfTxNotifyApp[Usart_enuBusNum_1]();
			}
		}
		else
		{
			Usart_enuSendDataAsync(Usart1_TxGlobalBuffer.buffer[Usart1_TxGlobalBuffer.used], USART_1);
			Usart1_TxGlobalBuffer.used++;
		}
	}
	if(Usart_u8ReadRxFlag(USART_1) && (Usart1_RxBsy== 1)) // which means that data came form outside in your shift reg
		/*I should check on bsy also bec I may enter the interrupt becasue of Tx so I will enter here if only the user
		 * request this */
	{
		Usart_enuRecieveDataAsync(Usart1_RxGlobalBuffer.buffer+Usart1_RxGlobalBuffer.used, USART_1);
		Usart1_RxGlobalBuffer.used++;

		if (Usart1_RxGlobalBuffer.used == Usart1_RxGlobalBuffer.size)
		{
			Usart1_RxBsy = 0;// must clear this flag
			Usart1_RxGlobalBuffer.used = 0;
			Usart1_RxGlobalBuffer.size = 0; // may not clear this flags bec if the user send another buffer, he will corrupt them
			Usart_enuRxInterruptCtrl(USART_1,Usart_enuIntDisabled);
			if(Usart_pcbfTxNotifyApp[Usart_enuBusNum_1]!=NULL)
			{
				Usart_pcbfTxNotifyApp[Usart_enuBusNum_1]();
			}
		}
	}

}

static void Usart2_vidHandlerCbf(void)
{
	if(Usart_u8ReadTcFlag(USART_2) == 1) // checking on TC flag because we may enter
		// the handler because of RX also and for parity ..etc..
	{
		if(Usart2_TxGlobalBuffer.used == Usart2_TxGlobalBuffer.size)
		{
			Usart2_TxBsy = 0;
			Usart2_TxGlobalBuffer.used = 0;
			Usart2_TxGlobalBuffer.size = 0; // may not clear this flags bec if the user send another buffer, he will corrupt them
			Usart_enuTcInterruptCtrl(USART_2,Usart_enuIntDisabled);
			if(Usart_pcbfTxNotifyApp[Usart_enuBusNum_2]!=NULL)
			{
				Usart_pcbfTxNotifyApp[Usart_enuBusNum_2]();
			}
		}
		else
		{
			Usart_enuSendDataAsync(Usart2_TxGlobalBuffer.buffer[Usart2_TxGlobalBuffer.used], USART_2);
			Usart2_TxGlobalBuffer.used++;
		}
	}
}

static void Usart6_vidHandlerCbf(void)
{
	if(Usart_u8ReadTcFlag(USART_6) == 1) // checking on TC flag because we may enter
		// the handler because of RX also and for parity ..etc..
	{
		if(Usart6_TxGlobalBuffer.used == Usart6_TxGlobalBuffer.size)
		{
			Usart6_TxBsy = 0;
			Usart6_TxGlobalBuffer.used = 0;
			Usart6_TxGlobalBuffer.size = 0; // may not clear this flags bec if the user send another buffer, he will corrupt them
			Usart_enuTcInterruptCtrl(USART_2,Usart_enuIntDisabled);
			if(Usart_pcbfTxNotifyApp[Usart_enuBusNum_6]!=NULL)
			{
				Usart_pcbfTxNotifyApp[Usart_enuBusNum_6]();
			}		}
		else
		{
			Usart_enuSendDataAsync(Usart6_TxGlobalBuffer.buffer[Usart6_TxGlobalBuffer.used], USART_6);
			Usart1_TxGlobalBuffer.used++;
		}
	}
}











//Uart_RegisterHalCbf(Usart1_vidHandlerCbf,USART_BUSNUM_1);
//static void Usart1_vidHandlerCbf(void)
//{
//	if(Usart_ReadTcFlag(USART_1) == 1 && (Usart1_GlobalBuffer.used < Usart1_GlobalBuffer.size)) // checking on TC flag because we may enter
//		// the handler because of RX also and for parity ..etc..
//	{
//		Usart1_GlobalBuffer.used++;
//		Usart_vidSendDataAsync(Usart1_GlobalBuffer.buffer[Usart1_GlobalBuffer.used], USART_1);
//	}
//	else
//	{
//		Usart1_TxBsy = 0;
//		Usart1_GlobalBuffer.used = 0;
//		Usart_pcbfTxNotifyApp[Usart_enuBusNum_1]();
//	}
//}
