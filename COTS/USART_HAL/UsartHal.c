/*
 * UsartHal.c
 *
 *  Created on: May 2, 2022
 *      Author: Abdelrahman Yousry Ahmed
 */
#include "Std_types.h"
#include "NVIC.h"
#include "Rcc.h"
#include "Gpio.h"
#include "Uart.h"
#include "Dma.h"
#include "UsartHal.h"
#include "UsartHal_cfg.h"
#include "UsartHal_prv.h"


//*These function will be registered as a call back function which will be called by the MCAL layer*//
static void Usart1_vidHandlerCbf(void);
static void Usart2_vidHandlerCbf(void);
static void Usart6_vidHandlerCbf(void);



//*These function will be registered from a regfunc in DMA-mcal as a call back function which will be called by the MCAL layer*//
/*DMA1 CallBack Functions prototype*/
/*Usart 2 Rx*/
static void Dma1_vidStream5HandlerCbf(void);
/*Usart 6 Rx*/
static void Dma2_vidStream2HandlerCbf(void);
/*Usart 1 Rx*/
static void Dma2_vidStream5HandlerCbf(void);

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

/************CALL BACK FUNCTION FOR USART USING USART DRIVER************/
pcbf Usart_pcbfTxNotifyApp[MAX_NUM_OF_BUSNUM];
pcbf Usart_pcbfRxNotifyApp[MAX_NUM_OF_BUSNUM];

/************CALL BACK FUNCTION FOR USART USING DMA DRIVER************/
pcbf Usart_pcbfDma1NotifyApp[MAX_NUM_OF_CHANNELS];
pcbf Usart_pcbfDma2NotifyApp[MAX_NUM_OF_CHANNELS];


extern const Uart_tCfg Usart_DeviceCfg[MAX_NUM_OF_DEVICES];
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
		Uart_cfg.Usart_u16BaudRate=Usart_DeviceCfg[iterator].Usart_u16BaudRate;
		Uart_cfg.Usart_u16DataLength=Usart_DeviceCfg[iterator].Usart_u16DataLength;
		Uart_cfg.Usart_u16InterruptCtrl=Usart_DeviceCfg[iterator].Usart_u16InterruptCtrl;
		Uart_cfg.Usart_u16NumStopBit=Usart_DeviceCfg[iterator].Usart_u32NumStopBit;
		Uart_cfg.Usart_u16OverSampling=Usart_DeviceCfg[iterator].Usart_u16OverSampling;
		Uart_cfg.Usart_u16RecieveCtrl=Usart_DeviceCfg[iterator].Usart_u16RecieveCtrl;
		Uart_cfg.Usart_u16TransmitCtrl=Usart_DeviceCfg[iterator].Usart_u16TransmitCtrl;
		Uart_cfg.Usart_u64Clock=Usart_DeviceCfg[iterator].Usart_u64Clock;
		Uart_cfg.Usart_u16DmaCtrl=Usart_DeviceCfg[iterator].Usart_u16DmaCtrl;
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
		/*Configuration of Pin A1*/
		GpioCfg1.mode=GPIO_u8MODE_AF_PP;
		GpioCfg1.port=GPIO_A;
		GpioCfg1.pin=GPIO_u8PIN_1;
		GpioCfg1.AF=GPIO_u8ALTERNATE_FUNC_07;
		GpioCfg1.speed=GPIO_u8SPEED_HIGH;
		/*Configuration of Pin A2*/
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
		/*Configuration of Pin A6*/
		GpioCfg1.mode=GPIO_u8MODE_AF_PP;
		GpioCfg1.port=GPIO_C;
		GpioCfg1.pin=GPIO_u8PIN_6;
		GpioCfg1.AF=GPIO_u8ALTERNATE_FUNC_08;
		GpioCfg1.speed=GPIO_u8SPEED_HIGH;
		/*Configuration of Pin A7*/
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
	Uart_enuRegisterHalCbf(Usart1_vidHandlerCbf,Usart_enuBusNum1);
	Uart_enuRegisterHalCbf(Usart2_vidHandlerCbf,Usart_enuBusNum2);
	Uart_enuRegisterHalCbf(Usart6_vidHandlerCbf,Usart_enuBusNum6);

	Dma_enuRegHalCbf(Dma1_vidStream5HandlerCbf,DMA_1, Dma_Stream_5);
	Dma_enuRegHalCbf(Dma2_vidStream2HandlerCbf,DMA_1, Dma_Stream_2);
	Dma_enuRegHalCbf(Dma2_vidStream5HandlerCbf,DMA_1, Dma_Stream_5);

}


UsartHal_tenuErrorStatus Usart_enuSendBufferZc(pu8 Z_pu8Buffer, u16 copy_u16Size, Usart_tenuBusNum Copy_enuBusNum)
{
	UsartHal_tenuErrorStatus Loc_enuErrorStatus = UsartHal_enuOk;
	if(Z_pu8Buffer == NULL)
	{
		Loc_enuErrorStatus = UsartHal_enuNullptr;
	}
	else if(Copy_enuBusNum > Usart_enuMaxNum )
	{
		Loc_enuErrorStatus =UsartHal_enuInvalidBusNum;
	}
	else if(Usart1_TxBsy == 0)
	{
		switch(Copy_enuBusNum)
		{
		case Usart_enuBusNum1:
			Usart1_TxBsy = 1;
			Usart1_TxGlobalBuffer.buffer = Z_pu8Buffer;
			Usart1_TxGlobalBuffer.size = copy_u16Size;
			Usart1_TxGlobalBuffer.used = 1;
			Usart_enuSendDataAsync(Usart1_TxGlobalBuffer.buffer[0],Usart_DeviceCfg->Usart_pvChannel);
			Usart_enuTcInterruptCtrl(USART_1,Usart_enuIntEnabled);
			break;

		case Usart_enuBusNum2:
			Usart2_TxBsy = 1;
			Usart2_TxGlobalBuffer.buffer = Z_pu8Buffer;
			Usart2_TxGlobalBuffer.size = copy_u16Size;
			Usart2_TxGlobalBuffer.used = 1;
			Usart_enuSendDataAsync(Usart2_TxGlobalBuffer.buffer[0],Usart_DeviceCfg->Usart_pvChannel);
			Usart_enuTcInterruptCtrl(USART_2,Usart_enuIntEnabled);
			break;

		case Usart_enuBusNum6:
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
UsartHal_tenuErrorStatus Usart_enuRecieveBufferZc(pu8 Z_pu8Buffer, u16 copy_u16Size,Usart_tenuBusNum Copy_enuBusNum)
{
	UsartHal_tenuErrorStatus Loc_enuErrorStatus = UsartHal_enuOk;
	if(Z_pu8Buffer == NULL)
	{
		Loc_enuErrorStatus = UsartHal_enuNullptr;
	}
	else if(Copy_enuBusNum > Usart_enuMaxNum )
	{
		Loc_enuErrorStatus =UsartHal_enuInvalidBusNum;
	}
	else
	{
		switch(Copy_enuBusNum)
		{
		case Usart_enuBusNum1:
			if(Usart1_RxBsy == 0)
			{
				Usart1_RxBsy = 1;
				Usart1_RxGlobalBuffer.buffer = Z_pu8Buffer;
				Usart1_RxGlobalBuffer.size = copy_u16Size;
				Usart1_RxGlobalBuffer.used = 0;
				Usart_enuRxInterruptCtrl(USART_1,Usart_enuIntEnabled);//******xxxxxxxxxxx**********//
			}
			break;

		case Usart_enuBusNum2:
			if(Usart2_RxBsy == 0)
			{
				Usart2_RxBsy = 1;
				Usart2_RxGlobalBuffer.buffer = Z_pu8Buffer;
				Usart2_RxGlobalBuffer.size = copy_u16Size;
				Usart2_RxGlobalBuffer.used = 0;
				Usart_enuRxInterruptCtrl(USART_2,Usart_enuIntEnabled);//******xxxxxxxxxxx**********//
			}
			break;

		case Usart_enuBusNum6:
			if(Usart6_RxBsy == 0)
			{
				Usart6_RxBsy = 1;
				Usart6_RxGlobalBuffer.buffer = Z_pu8Buffer;
				Usart6_RxGlobalBuffer.size = copy_u16Size;
				Usart6_RxGlobalBuffer.used = 0;
				Usart_enuRxInterruptCtrl(USART_6,Usart_enuIntEnabled);//******xxxxxxxxxxx**********//
			}
			break;
		}
	}
	return Loc_enuErrorStatus;
}

/*********************************SEND/RECIEVE BUFFER USING DMA************************************/
UsartHal_tenuErrorStatus Usart_enuSendBufferDmaZc(pu8 Copy_pu8Buffer, u16 copy_u16Size, Usart_tenuBusNum Copy_enuBusNum)
{
	UsartHal_tenuErrorStatus Loc_enuErrorStatus = UsartHal_enuOk;
	Dma_tstrCfg Dma_strCfg;
	if(Copy_pu8Buffer == NULL)
	{
		Loc_enuErrorStatus = UsartHal_enuNullptr;
	}
	else
	{
		Dma_strCfg.Dma_pu32Mem1Add=(void *) Copy_pu8Buffer;
		Dma_strCfg.Dma_u32CircModeCtrl=DMA_u32CIRC_MODE_DISABLED;
		Dma_strCfg.Dma_u32DoubBuffModeCtrl=DMA_u32DOUBLE_BUFFER_MODE_DiSABLED;
		Dma_strCfg.Dma_u32IncMode=DMA_u32PERIPH_INC_MODE_DISABLED;
		Dma_strCfg.Dma_u32InterruptCtrl=(DMA_u32HALF_TRANS_COMPLETE_INT_ENABLE|DMA_u32TRANS_COMPLETE_INT_ENABLE);
		Dma_strCfg.Dma_u32SwPriority=DMA_u32PRIORITY_LEVEL_MEDIUM;
		Dma_strCfg.Dma_u32NumOfData=copy_u16Size;// size of the array/bufffer
		Dma_strCfg.Dma_u32PeriSize=DMA_u32PERIPH_DATASIZE_32bits;
		Dma_strCfg.Dma_u32TransmissionDir=DMA_u32DIR_PERIPH_TO_MEM;
		Dma_strCfg.Dma_u32MemorySize=DMA_u32MEM_DATASIZE_8bits;
		switch (Copy_enuBusNum)
		{
		case Usart_enuBusNum1:
			Dma_strCfg.Dma_tstrCfg_DmaAdd=DMA_2;
			Dma_strCfg.Dma_enuChannelID=Dma_Channel_4;
			Dma_strCfg.Dma_enuStreamNum=Dma_Stream_7;
			Dma_strCfg.Dma_pu32periphAdd=(void *)(USART_1 + 0x04);
			Dma_enuClearFlags(DMA_2,DMA_u64CLEAR_ALL_INTERRUPT_FLAGS);
			Dma_enuControl(DMA_2,Dma_Stream_7,DMA_u32STREAM_START);
			Dma_enuRegHalCbf(Usart_pcbfRxNotifyApp[Usart_enuBusNum1],DMA_2,Dma_Stream_7);
			break;
		case Usart_enuBusNum2:
			Dma_strCfg.Dma_tstrCfg_DmaAdd=DMA_1;
			Dma_strCfg.Dma_enuChannelID=Dma_Channel_4;
			Dma_strCfg.Dma_enuStreamNum=Dma_Stream_6;
			Dma_strCfg.Dma_pu32periphAdd=(u32 *)(USART_2 + 0x04);;
			Dma_enuClearFlags(DMA_1,DMA_u64CLEAR_ALL_INTERRUPT_FLAGS);
			Dma_enuControl(DMA_1,Dma_Stream_6,DMA_u32STREAM_START);
			break;
		case Usart_enuBusNum6:
			Dma_strCfg.Dma_tstrCfg_DmaAdd=DMA_2;
			Dma_strCfg.Dma_enuChannelID=Dma_Channel_5;
			Dma_strCfg.Dma_enuStreamNum=Dma_Stream_7;
			Dma_strCfg.Dma_pu32periphAdd=(u32 *)(USART_6 + 0x04);
			Dma_enuClearFlags(DMA_2,DMA_u64CLEAR_ALL_INTERRUPT_FLAGS);
			Dma_enuControl(DMA_2,Dma_Stream_7,DMA_u32STREAM_START);
			break;
		}
		Dma_enuInit(&Dma_strCfg);
	}
	return Loc_enuErrorStatus;
}
UsartHal_tenuErrorStatus Usart_enuRecieveBufferDmaZc(pu8 Copy_pu8Buffer, u16 copy_u16Size, Usart_tenuBusNum Copy_enuBusNum)
{
	UsartHal_tenuErrorStatus Loc_enuErrorStatus = UsartHal_enuOk;
	Dma_tstrCfg Dma_strCfg;
	if(Copy_pu8Buffer == NULL)
	{
		Loc_enuErrorStatus = UsartHal_enuNullptr;
	}
	else
	{
		Dma_strCfg.Dma_pu32Mem1Add=Copy_pu8Buffer;
		Dma_strCfg.Dma_u32CircModeCtrl=DMA_u32CIRC_MODE_DISABLED;
		Dma_strCfg.Dma_u32DoubBuffModeCtrl=DMA_u32DOUBLE_BUFFER_MODE_DiSABLED;
		Dma_strCfg.Dma_u32IncMode=DMA_u32PERIPH_INC_MODE_DISABLED;
		Dma_strCfg.Dma_u32InterruptCtrl=(DMA_u32HALF_TRANS_COMPLETE_INT_ENABLE|DMA_u32TRANS_COMPLETE_INT_ENABLE);
		Dma_strCfg.Dma_u32SwPriority=DMA_u32PRIORITY_LEVEL_MEDIUM;
		Dma_strCfg.Dma_u32NumOfData=10;// size of the array/bufffer
		Dma_strCfg.Dma_u32PeriSize=DMA_u32PERIPH_DATASIZE_32bits;
		Dma_strCfg.Dma_u32TransmissionDir=DMA_u32DIR_PERIPH_TO_MEM;
		Dma_strCfg.Dma_u32MemorySize=DMA_u32MEM_DATASIZE_8bits;
		switch (Copy_enuBusNum)
		{
		case Usart_enuBusNum1:
			Dma_strCfg.Dma_tstrCfg_DmaAdd=DMA_2;
			Dma_strCfg.Dma_enuChannelID=Dma_Channel_4;
			Dma_strCfg.Dma_enuStreamNum=Dma_Stream_7;
			Dma_strCfg.Dma_pu32periphAdd=(u32 *)(USART_1 + 0x04);;
			Dma_enuClearFlags(DMA_2,DMA_u64CLEAR_ALL_INTERRUPT_FLAGS);
			Dma_enuControl(DMA_2,Dma_Stream_7,DMA_u32STREAM_START);
			break;
		case Usart_enuBusNum2:
			Dma_strCfg.Dma_tstrCfg_DmaAdd=DMA_1;
			Dma_strCfg.Dma_enuChannelID=Dma_Channel_4;
			Dma_strCfg.Dma_enuStreamNum=Dma_Stream_6;
			Dma_strCfg.Dma_pu32periphAdd=(u32 *)(USART_2 + 0x04);;
			Dma_enuClearFlags(DMA_1,DMA_u64CLEAR_ALL_INTERRUPT_FLAGS);
			Dma_enuControl(DMA_1,Dma_Stream_6,DMA_u32STREAM_START);
			break;
		case Usart_enuBusNum6:
			Dma_strCfg.Dma_tstrCfg_DmaAdd=DMA_2;
			Dma_strCfg.Dma_enuChannelID=Dma_Channel_5;
			Dma_strCfg.Dma_enuStreamNum=Dma_Stream_7;
			Dma_strCfg.Dma_pu32periphAdd=(u32 *)(USART_6 + 0x04);;
			Dma_enuClearFlags(DMA_2,DMA_u64CLEAR_ALL_INTERRUPT_FLAGS);
			Dma_enuControl(DMA_2,Dma_Stream_7,DMA_u32STREAM_START);
			break;
		}
		Dma_enuInit(&Dma_strCfg);
	}
	return Loc_enuErrorStatus;

}

/********************************Wrapper Functions*************************************************/
UsartHal_tenuErrorStatus Usart_enuHalSendDataSync(u32 Copy_u32Data,Usart_tenuBusNum Copy_enuBusNum)
{
	UsartHal_tenuErrorStatus Loc_enuErrorStatus = Usart_enuOk;
	switch (Copy_enuBusNum)
	{
	case Usart_enuBusNum1:
		Usart_enuSendDataSync(Copy_u32Data,USART_1);
		break;
	case Usart_enuBusNum2:
		Usart_enuSendDataSync(Copy_u32Data,USART_2);
		break;
	case Usart_enuBusNum6:
		Usart_enuSendDataSync(Copy_u32Data,USART_6);
		break;
	default:
		Loc_enuErrorStatus = UsartHal_enuInvalidBusNum;
		break;
	}
	return Loc_enuErrorStatus;
}
/****************************************************************************/
pu32 Usart_pu32ReciveDataSync(u32 Copy_u32Data,Usart_tenuBusNum Copy_enuBusNum)
{
	UsartHal_tenuErrorStatus Loc_enuErrorStatus = Usart_enuOk;
	pu32 Loc_Result;
	switch (Copy_enuBusNum)
	{
	case Usart_enuBusNum1:
		Usart_enuRecieveDataSync(USART_1,Loc_Result);
		break;
	case Usart_enuBusNum2:
		Usart_enuRecieveDataSync(USART_2,Loc_Result);
		break;
	case Usart_enuBusNum6:
		Usart_enuRecieveDataSync(USART_6,Loc_Result);
		break;
	default:
		Loc_enuErrorStatus = UsartHal_enuInvalidBusNum;
		break;
	}
	return Loc_Result;
}

/************************************************************************************************/
UsartHal_tenuErrorStatus Usart_enuRegTxCompNotifyCbf(pcallback Usart_pcbfNotifyApp,Usart_tenuBusNum Copy_enuUsartBusNum)
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
		case Usart_enuBusNum1:
			Usart_pcbfTxNotifyApp[Usart_enuBusNum1]=Usart_pcbfNotifyApp;
			break;

		case Usart_enuBusNum2:
			Usart_pcbfTxNotifyApp[Usart_enuBusNum2]=Usart_pcbfNotifyApp;
			break;

		case Usart_enuBusNum6:
			Usart_pcbfTxNotifyApp[Usart_enuBusNum6]=Usart_pcbfNotifyApp;
			break;
		}
	}
	return Loc_enuErrorStatus;
}
UsartHal_tenuErrorStatus Usart_enuRegRxCompNotifyCbf(pcallback Usart_pcbfNotifyApp,Usart_tenuBusNum Copy_enuUsartBusNum)
{
	Usart_tenuErrorStatus Loc_enuErrorStatus;
	if(Usart_pcbfNotifyApp==NULL)
	{
		Loc_enuErrorStatus = Usart_enuNullptr;
	}
	else
	{
		Usart_pcbfRxNotifyApp[Copy_enuUsartBusNum]=Usart_pcbfNotifyApp;
	}

	return Loc_enuErrorStatus;
}



static void Usart1_vidHandlerCbf(void)
{
	if(Usart_u8ReadTcFlag(USART_1) && (Usart1_TxBsy == 1)) // checking on TC flag because we may enter

	{
		if(Usart1_TxGlobalBuffer.used == Usart1_TxGlobalBuffer.size)
		{
			Usart1_TxBsy = 0;
			Usart1_TxGlobalBuffer.used = 0;
			Usart1_TxGlobalBuffer.size = 0; // may not clear this flags bec if the user send another buffer, he will corrupt them
			Usart_enuTcInterruptCtrl(USART_1,Usart_enuIntDisabled);
			Uart_ClearTcFlag(USART_1);
			if(Usart_pcbfTxNotifyApp[Usart_enuBusNum1]!=NULL)
			{
				Usart_pcbfTxNotifyApp[Usart_enuBusNum1]();
			}
		}
		else
		{
			Usart_enuSendDataAsync(Usart1_TxGlobalBuffer.buffer[Usart1_TxGlobalBuffer.used], USART_1);
			Usart1_TxGlobalBuffer.used++;
		}
	}

	//Should be if condition because I may enter this interrupt becasue of TX/ Rx etc..
	if(Usart_u8ReadRxFlag(USART_1) && (Usart1_RxBsy== 1)) // which means that data came form outside in your shift reg
		/*I should check on bsy also bec I may enter the interrupt becasue of Tx so I will enter here if only the user
		 * request this */
	{
		/**xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx**/
		// here will send the address of the loc then after finshing here he will
		// = the loc var with the buffer sent by the user
		Usart_enuRecieveDataAsync(USART_1,Usart1_RxGlobalBuffer.buffer+Usart1_RxGlobalBuffer.used);
		Usart1_RxGlobalBuffer.used++;


		if (Usart1_RxGlobalBuffer.used > Usart1_RxGlobalBuffer.size)
		{
			Usart1_RxBsy = 0;// must clear this flag
			Usart1_RxGlobalBuffer.used = 0;
			// may not clear this flags bec if the user send another buffer, he will corrupt them
			Usart1_RxGlobalBuffer.size = 0;
			// Disable the RX interrupt
			Usart_enuRxInterruptCtrl(USART_1,Usart_enuIntDisabled);
			if(Usart_pcbfRxNotifyApp[Usart_enuBusNum1]!=NULL)
			{
				Usart_pcbfRxNotifyApp[Usart_enuBusNum1]();
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
			if(Usart_pcbfTxNotifyApp[Usart_enuBusNum2]!=NULL)
			{
				Usart_pcbfTxNotifyApp[Usart_enuBusNum2]();
			}
		}
		else
		{
			Usart_enuSendDataAsync(Usart2_TxGlobalBuffer.buffer[Usart2_TxGlobalBuffer.used], USART_2);
			Usart2_TxGlobalBuffer.used++;
			Uart_ClearTcFlag(USART_2);
		}
	}


	//Should be if condition because I may enter this interrupt becasue of TX/ Rx etc..
	if(Usart_u8ReadRxFlag(USART_2) && (Usart2_RxBsy== 1)) // which means that data came form outside in your shift reg
		/*I should check on bsy also bec I may enter the interrupt becasue of Tx so I will enter here if only the user
		 * request this */
	{

		if (Usart2_RxGlobalBuffer.used == Usart2_RxGlobalBuffer.size)
		{
			Usart2_RxBsy = 0;// must clear this flag
			Usart2_RxGlobalBuffer.used = 0;
			// may not clear this flags bec if the user send another buffer, he will corrupt them
			Usart2_RxGlobalBuffer.size = 0;
			// Disable the RX interrupt
			Usart_enuRxInterruptCtrl(USART_2,Usart_enuIntDisabled);
			if(Usart_pcbfRxNotifyApp[Usart_enuBusNum2]!=NULL)
			{
				Usart_pcbfRxNotifyApp[Usart_enuBusNum2]();
			}
		}
		else
		{
			Usart_enuRecieveDataAsync(USART_2,Usart2_RxGlobalBuffer.buffer+Usart2_RxGlobalBuffer.used);
			Usart1_RxGlobalBuffer.used++;
			Uart_ClearRxFlag(USART_2);

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
			if(Usart_pcbfTxNotifyApp[Usart_enuBusNum6]!=NULL)
			{
				Usart_pcbfTxNotifyApp[Usart_enuBusNum6]();
			}
		}
		else
		{
			Usart_enuSendDataAsync(Usart6_TxGlobalBuffer.buffer[Usart6_TxGlobalBuffer.used], USART_6);
			Usart1_TxGlobalBuffer.used++;
			Uart_ClearTcFlag(USART_6);
		}
	}

	//Should be if condition because I may enter this interrupt becasue of Tx/ Rx etc..
	if(Usart_u8ReadRxFlag(USART_6) && (Usart6_RxBsy== 1)) // which means that data came form outside in your shift reg
		/*I should check on bsy also bec I may enter the interrupt becasue of Tx so I will enter here if only the user
		 * request this */
	{

		if (Usart6_RxGlobalBuffer.used == Usart6_RxGlobalBuffer.size)
		{
			Usart6_RxBsy = 0;// must clear this flag
			Usart6_RxGlobalBuffer.used = 0;
			// may not clear this flags bec if the user send another buffer, he will corrupt them
			Usart6_RxGlobalBuffer.size = 0;
			// Disable the RX interrupt
			Usart_enuRxInterruptCtrl(USART_6,Usart_enuIntDisabled);
			if(Usart_pcbfRxNotifyApp[Usart_enuBusNum1]!=NULL)
			{
				Usart_pcbfRxNotifyApp[Usart_enuBusNum1]();
			}
		}
		else
		{
			Usart_enuRecieveDataAsync(USART_6,Usart6_RxGlobalBuffer.buffer+Usart6_RxGlobalBuffer.used);
			Usart6_RxGlobalBuffer.used++;
			Uart_ClearRxFlag(USART_6);

		}
	}
}



static void Dma1_vidStream5HandlerCbf(void)
{

}

static void Dma2_vidStream2HandlerCbf(void)
{

}

static void Dma2_vidStream5HandlerCbf(void)
{

}

