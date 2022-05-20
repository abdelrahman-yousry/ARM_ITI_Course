/*
 * Dma_prv.h
 *
 *  Created on: May 4, 2022
 *      Author: Abdelrahman Yousry
 */

#ifndef DMA_PRV_H_
#define DMA_PRV_H_
/*IN DMA
 * WE HAVE TWO STATUS REGISTER REPRESENTS THE 7 CHANNELS
 * ALSO WE HAVE TWO CONTROL INTERRUPT FLAGS REGISTER REPRESENTS 7 DMA CHANNELS
 *
 * */
/********************************************************************************/

/********************************************************************************/
#define DMA_u8CHSEL_SHIFTING_MASK			(u8)25

/******************CR REG CLEAR MASK for assigning this configuration by |= to the reg******************/
#define DMA_u32CR_CLEAR_MASK 				((u32)0xE37FD9)//will be &=~
/******************this macro is to know if the user select the double buffer mode or not***************/
#define DMA_u32GET_DOUBLE_MODE_STATUS		((u32)0x00080000) // will be &

/******************this macro is to validate on the Num of data which should not exceed 2^16************/
#define DMA_u16DATA_NUM_VALIDATION			((u16)0xFFFF)// will be &

/*when you create strcut inside struct the inner struct will be created as instance*/
typedef struct
{
	u32 LISR;
	u32 HISR;
	u32 LIFCR;
	u32 HIFCR;
	struct
	{
		u32 SxCR;
		u32 SxNDTR;
		u32 SxPAR;
		u32 SxM0AR;
		u32 SxM1AR;
		u32 SxFCR;
	}Dma_tStreamRegCfg[8];
}Dma_tRegCfg;


/*This function is to read EN flag in the reg SCxR reg because you should clear this bit before configuration*/
static u8 Dma_u8ReadEnFlag(void* pvidDmaNum,Dma_tenuStreamNum Copy_enuStreamNum);


#endif /* DMA_PRV_H_ */
