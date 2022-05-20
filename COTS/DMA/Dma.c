/*
 * Dma.c
 *
 *  Created on: May 4, 2022
 *      Author: Abdelrahman Yousry
 */
#include "Std_types.h"
#include "Dma.h"
#include "Dma_prv.h"

pcbf Dma1_pcbfManCbf[8];
pcbf Dma2_pcbfManCbf[8];

Dma_tenuErrorStatus Dma_enuInit(Dma_tstrCfg* Copy_strDmaCfg)
{
	Dma_tenuErrorStatus Loc_enuErrorStatus = Dma_enuOk;
	volatile u32 Loc_u32TempVar =0;
	Dma_tRegCfg* Loc_pstrChannel = Copy_strDmaCfg->Dma_tstrCfg_DmaAdd;
	if (Loc_pstrChannel ==NULL||
			Copy_strDmaCfg->Dma_pvidMem1Add==NULL||
			Copy_strDmaCfg->Dma_pvidMem2Add==NULL||
			Copy_strDmaCfg->Dma_pvidperiphAdd==NULL)
	{
		Loc_enuErrorStatus = Dma_enuNullPtr;
	}
	else if ( Copy_strDmaCfg->Dma_enuChannelID > Dma_Max_Num_Of_Channels)
	{
		Loc_enuErrorStatus=Dma_enuInvalidChannelId;
	}
	else if(Copy_strDmaCfg->Dma_u32NumOfData > DMA_u16DATA_NUM_VALIDATION)
	{
		Loc_enuErrorStatus =Dma_enuInvalidDataNum;
	}

	//*DMA CONFIGURATION**//
	else
	{
		/*Because if you will configure you should disable the dma by resetting the EN bit*/
		if(Dma_u8ReadEnFlag(Loc_pstrChannel,Copy_strDmaCfg->Dma_enuStreamNum)==0)
		{
			Loc_u32TempVar = Loc_pstrChannel->Dma_tStreamRegCfg[Copy_strDmaCfg->Dma_enuStreamNum].SxCR;// reading the configuration reg in temp var
			Loc_u32TempVar &=~ DMA_u32CR_CLEAR_MASK;// clearing the desired bits to be configured
			Loc_u32TempVar=(
					((u32)Copy_strDmaCfg->Dma_enuChannelID<<DMA_u8CHSEL_SHIFTING_MASK)|
					(Copy_strDmaCfg->Dma_u32DoubBuffModeCtrl)|
					(Copy_strDmaCfg->Dma_u32CircModeCtrl)|
					(Copy_strDmaCfg->Dma_u32PeriSize)|
					(Copy_strDmaCfg->Dma_u32MemorySize)|
					(Copy_strDmaCfg->Dma_u32TransmissionDir)|
					(Copy_strDmaCfg->Dma_u32SwPriority)|
					(Copy_strDmaCfg->Dma_u32IncMode)|
					(Copy_strDmaCfg->Dma_u32InterruptCtrl)
			);
			Loc_pstrChannel->Dma_tStreamRegCfg[Copy_strDmaCfg->Dma_enuStreamNum].SxCR = Loc_u32TempVar;
			/*************************************ASSIGNING THE MEM ADD 1 **************************************/
			Loc_pstrChannel->Dma_tStreamRegCfg[Copy_strDmaCfg->Dma_enuStreamNum].SxM0AR= (u32)(Copy_strDmaCfg->Dma_pvidMem1Add);
			/***********************************ASSIGNING THE PERIPH ADD*****************************************/
			Loc_pstrChannel->Dma_tStreamRegCfg[Copy_strDmaCfg->Dma_enuStreamNum].SxPAR =(u32)(Copy_strDmaCfg->Dma_pvidperiphAdd);
			/****************************ASSIGN THE MEM ADD IN CASE OF DOUBLE BUFFFER MODE ACTIVATED*************/
			if((Copy_strDmaCfg->Dma_u32DoubBuffModeCtrl)&DMA_u32GET_DOUBLE_MODE_STATUS)
			{
				if(Copy_strDmaCfg->Dma_pvidMem2Add == NULL)
				{
					Loc_enuErrorStatus = Dma_enuNullPtr;
				}
				else
				{
					Loc_pstrChannel->Dma_tStreamRegCfg[Copy_strDmaCfg->Dma_enuStreamNum].SxM1AR = (u32)(Copy_strDmaCfg->Dma_pvidMem2Add);
				}
			}

			/**************************ASSIGN NUM OF DATA IN THE NDT reg****************************/
			Loc_pstrChannel->Dma_tStreamRegCfg[Copy_strDmaCfg->Dma_enuStreamNum].SxNDTR = (Copy_strDmaCfg->Dma_u32NumOfData);
		}

		else
		{
			Loc_enuErrorStatus=Dma_enuConfigDisabled;
		}
	}

	return Loc_enuErrorStatus;
}

/********************************DMA Control Function for start/Stop DMA****************************************/
Dma_tenuErrorStatus Dma_enuControl(void* pvidDmaNum,Dma_tenuStreamNum Copy_enuStreamNum, u8 Copy_u8DmaState)
{
	Dma_tenuErrorStatus Loc_enuErrorStatus = Dma_enuOk;
	if(pvidDmaNum == NULL)
	{
		Loc_enuErrorStatus = Dma_enuNullPtr;
	}
	else if((Copy_u8DmaState!= DMA_u32STREAM_START) && (Copy_u8DmaState!= DMA_u32STREAM_STOP)) // You have check only one state
	{																							// Why you check on both state
		Loc_enuErrorStatus =Dma_enuWrongDmaState;
	}
	else
	{
		((volatile Dma_tRegCfg*)pvidDmaNum)->Dma_tStreamRegCfg[Copy_enuStreamNum].SxCR |=Copy_u8DmaState;
	}

	return Loc_enuErrorStatus;
}

/*Fisrt arg should be one of these options
DMA1 / DMA2 --> BASE address
 */
Dma_tenuErrorStatus Dma_enuClearFlags(void* pvidDmaNum, u64 Copy_u64Flags)
{
	Dma_tenuErrorStatus Loc_enuErrorStatus = Dma_enuOk;

	if(pvidDmaNum == NULL)
	{
		Loc_enuErrorStatus = Dma_enuNullPtr;
	}
	else
	{
		((Dma_tRegCfg*)pvidDmaNum)->LIFCR|=(u32)Copy_u64Flags;
		((Dma_tRegCfg*)pvidDmaNum)->HIFCR|=(u32)(Copy_u64Flags>>32);
	}

	return Loc_enuErrorStatus;
}


u8 Dma_u8ReadEnFlag(void* pvidDmaNum,Dma_tenuStreamNum Copy_enuStreamNum)
{
	u8 Loc_u8FlagValue=0;
	Loc_u8FlagValue=((Dma_tRegCfg*)pvidDmaNum)->Dma_tStreamRegCfg[Copy_enuStreamNum].SxCR&DMA_u32STREAM_START;

	return Loc_u8FlagValue;
}

Dma_tenuErrorStatus Dma_enuRegisterCallBack(void* Dma_tstrCfg_DmaAdd, Dma_tenuStreamNum Copy_enuStreamNum, pcbf Cbf)
{
	Dma_tenuErrorStatus Loc_enuErrorStatus = Dma_enuOk;
	if (Cbf && Dma_tstrCfg_DmaAdd)
	{
		switch((u32)Dma_tstrCfg_DmaAdd)
		{
		case (u32)DMA_1:
			Dma1_pcbfManCbf[Copy_enuStreamNum] = Cbf;
			break;
		case (u32)DMA_2:
			Dma2_pcbfManCbf[Copy_enuStreamNum] = Cbf;
			break;
		}
	}
	else
	{
		Loc_enuErrorStatus = Dma_enuNullPtr;
	}

	return Loc_enuErrorStatus;
}

///*DMA1 HANDLERS PROTOTYPES*/
//void DMA1_Stream0_IRQHandler (void)
//{
//
//}
//void DMA1_Stream1_IRQHandler (void)
//{
//
//}
//void DMA1_Stream2_IRQHandler (void)
//{
//
//}
//void DMA1_Stream3_IRQHandler (void)
//{
//
//}
//void DMA1_Stream4_IRQHandler (void)
//{
//
//}
//void DMA1_Stream5_IRQHandler (void)
//{
//
//}
//void DMA1_Stream6_IRQHandler (void)
//{
//
//}
//void DMA1_Stream7_IRQHandler (void)
//{
//
//}
//
///*DMA1 HANDLERS PROTOTYPES*/
//void DMA2_Stream0_IRQHandler (void)
//{
//
//}
//void DMA2_Stream1_IRQHandler (void)
//{
//
//}
//void DMA2_Stream2_IRQHandler (void)
//{
//
//}
//void DMA2_Stream3_IRQHandler (void)
//{
//
//}
//void DMA2_Stream4_IRQHandler (void)
//{
//
//}
//void DMA2_Stream5_IRQHandler (void)
//{
//
//}
//void DMA2_Stream6_IRQHandler (void)
//{
//
//}
void DMA2_Stream7_IRQHandler (void)
{
	/*do checking on null pointer*/
	Dma2_pcbfManCbf[Dma_Stream_7];
}


