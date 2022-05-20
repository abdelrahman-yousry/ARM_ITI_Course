/*
 * Dma.h
 *
 *  Created on: May 4, 2022
 *      Author: Abdelrahman Yousry
 */


#ifndef DMA_H_
#define DMA_H_

#define DMA_1	((void*)0x40026000)
#define DMA_2	((void*)0x40026400)
// pointer to func data type
typedef void(*pcbf)(void);

/****************************************DBM Bit 18 Configuration***************************************/
#define DMA_u32DOUBLE_BUFFER_MODE_DiSABLED		((u32)0x00000000)// will be |= because this a configuration so we will clear the desired
																//bits first but in loc var after reading the reg in this var
																//and the we will | equal our config
#define DMA_u32DOUBLE_BUFFER_MODE_ENABLED		((u32)0x00040000) // will be |=

/*********************************Priority Level Bits (two bits)16-17 Configuration*********************/
#define	DMA_u32PRIORITY_LEVEL_LOW				((u32)0x00000000)
#define	DMA_u32PRIORITY_LEVEL_MEDIUM			((u32)0x00010000)
#define	DMA_u32PRIORITY_LEVEL_HIGH				((u32)0x00020000)
#define	DMA_u32PRIORITY_LEVEL_VHIGH				((u32)0x00030000)

/*********************************MEM_SIZE Bits (two bits)13-14 Configuration***************************/
#define	DMA_u32MEM_DATASIZE_8BITS				((u32)0x00000000)
#define	DMA_u32MEM_DATASIZE_16BITS             	((u32)0x00002000)
#define	DMA_u32MEM_DATASIZE_32BITS             	((u32)0x00004000)

/******************************PERIPH_SIZE Bits (two bits)11-12 Configuration***************************/
#define	DMA_u32PERIPH_DATASIZE_8BITS			((u32)0x00000000)
#define	DMA_u32PERIPH_DATASIZE_16BITS          	((u32)0x00000800)
#define	DMA_u32PERIPH_DATASIZE_32BITS          	((u32)0x00001000)

/****************************MINC --> MEMORY INCREMENT MODE Bit 10 Configuration************************/
#define DMA_u32MEM_INC_MODE_DISABLED			((u32)0x00000000)
#define DMA_u32MEM_INC_MODE_ENABLED				((u32)0x00000400)

/****************************PINC --> PERIPH INCREMENT MODE Bit 9 Configuration************************/
#define DMA_u32PERIPH_INC_MODE_DISABLED			((u32)0x00000000)
#define DMA_u32PERIPH_INC_MODE_ENABLED			((u32)0x00000200)

/****************************CIRC --> Circular MODE Bit 8 Configuration********************************/
#define DMA_u32CIRC_MODE_DISABLED				((u32)0x00000000)
#define DMA_u32CIRC_MODE_ENABLED				((u32)0x00000100)

/*********************DIR --> DATA TRANSFER DIR Bits (two bits)7-6 Configuration***********************/
#define DMA_u32DIR_PERIPH_TO_MEM				((u32)0x00000000)
#define DMA_u32DIR_MEM_TO_PERIPH				((u32)0x00000040)
#define DMA_u32DIR_MEM_TO_MEM					((u32)0x00000080)

/*********************TCIE -->Transfer complete interrupt enable Bit 4 Configuration********************/
#define DMA_u32TRANS_COMPLETE_INT_ENABLE		((u32)0x00000010)
#define DMA_u32TRANS_COMPLETE_INT_DISABLE		((u32)0x00000000)

/*********************HTIE -->Transfer complete interrupt enable Bit 3 Configuration********************/
#define DMA_u32HALF_TRANS_COMPLETE_INT_ENABLE	((u32)0x00000004)
#define DMA_u32HALF_TRANS_COMPLETE_INT_DISABLE	((u32)0x00000000)

/**********************************EN --> Stream enable Bit 0  Configuration****************************/
#define DMA_u32STREAM_START						((u32)0x00000001)
#define DMA_u32STREAM_STOP						((u32)0xFFFFFFFE)

/**********************This macros is to use it in the Dma_enuClearFlags Function***********************/
/*The interrupt flag will be cleared by setting the corresponding bit by 1*/
#define DMA_u64CLEAR_INTERRUPT_TRANS_COMP_CH0	((u64)0x0000000000000020) // should be |= with the reg
#define DMA_u64CLEAR_INTERRUPT_TRANS_COMP_CH1	((u64)0x0000000000000800)
#define DMA_u64CLEAR_INTERRUPT_TRANS_COMP_CH2	((u64)0x0000000000200000)
#define DMA_u64CLEAR_INTERRUPT_TRANS_COMP_CH3	((u64)0x0000000008000000)
#define DMA_u64CLEAR_INTERRUPT_TRANS_COMP_CH4	((u64)0x0000002000000000)
#define DMA_u64CLEAR_INTERRUPT_TRANS_COMP_CH5	((u64)0x0000080000000000)
#define DMA_u64CLEAR_INTERRUPT_TRANS_COMP_CH6	((u64)0x0020000000000000)
#define DMA_u64CLEAR_INTERRUPT_TRANS_COMP_CH7	((u64)0x0800000000000000)


#define DMA_u64INTERRUPT_HALF_TRANS_COMP_CH0	((u64) 0x0000001000000000)
#define DMA_u64INTERRUPT_HALF_TRANS_COMP_CH1	((u64) 0x0000040000000000)
#define DMA_u64INTERRUPT_HALF_TRANS_COMP_CH2	((u64) 0x0010000000000000)
#define DMA_u64INTERRUPT_HALF_TRANS_COMP_CH3	((u64) 0x0400000000000000)
#define DMA_u64INTERRUPT_HALF_TRANS_COMP_CH4	((u64) 0x0000001000000000)
#define DMA_u64INTERRUPT_HALF_TRANS_COMP_CH5	((u64) 0x0000040000000000)
#define DMA_u64INTERRUPT_HALF_TRANS_COMP_CH6	((u64) 0x0010000000000000)
#define DMA_u64INTERRUPT_HALF_TRANS_COMP_CH7	((u64) 0x0400000000000000)


typedef enum
{
	Dma_enuOk,
	Dma_enuNok,
	Dma_enuInvalidChannelId,
	Dma_enuInvalidDataNum,
	Dma_enuWrongDmaState,
	Dma_enuConfig,
	Dma_enuNullPtr,
	Dma_enuConfigDisabled
}Dma_tenuErrorStatus;

/********************************CHSEL bits configuartion************************************/
typedef enum
{
	//=33554431 I think to have this value to let me not making shift in the implementation
	Dma_Channel_0,
	Dma_Channel_1,
	Dma_Channel_2,
	Dma_Channel_3,
	Dma_Channel_4,
	Dma_Channel_5,
	Dma_Channel_6,
	Dma_Channel_7,
	Dma_Max_Num_Of_Channels
}Dma_tenuChannelId;
typedef enum
{
	Dma_Stream_0,
	Dma_Stream_1,
	Dma_Stream_2,
	Dma_Stream_3,
	Dma_Stream_4,
	Dma_Stream_5,
	Dma_Stream_6,
	Dma_Stream_7,
	Dma_Max_Num_Of_Stream
}Dma_tenuStreamNum;



typedef struct
{
	void* Dma_tstrCfg_DmaAdd;// to set the base address of the channel
	Dma_tenuChannelId Dma_enuChannelID;
	Dma_tenuStreamNum Dma_enuStreamNum;
	/**These pointers is void because I don't care of the pointer data type because I will take data
	 * according to memory size **/
	void* Dma_pvidMem1Add;	// first memory add
	void* Dma_pvidMem2Add;	// second memory add in case of double buffer mode
	void* Dma_pvidperiphAdd;	// periph add in case mem to periph
	u32 Dma_u32MemorySize;
	u32 Dma_u32PeriSize;
	u32 Dma_u32IncMode; //should be sth like this--> Dma_u32IncMode=(DMA_u32MEM_INC_MODE_ENABLED|DMA_u32PERIPH_INC_MODE_DISABLED)
	u32 Dma_u32SwPriority;
//	u32 Dma_u32MemToMemCtrl;
	u32 Dma_u32TransmissionDir;
	u32 Dma_u32NumOfData;
	u32 Dma_u32CircModeCtrl;
	u32 Dma_u32DoubBuffModeCtrl;
	u32 Dma_u32InterruptCtrl;//should be sth like this--> Dma_u32InterruptCtrl=(DMA_u32TRANS_COMPLETE_INT_ENABLE|DMA_u32HALF_TRANS_COMPLETE_INT_ENABLE)
}Dma_tstrCfg;



/****************************************************************
 * Description: 		this function to init DMA
 *
 * input args: 			Dma_tstrCfg*
 *
 *
 * Return type: 		Dma_tenuErrorStatus for checking and make validation on the input arg
 * 						if it correct it will return Dma_enuOk
 * 						else will return one of these options
 * 						Dma_enuNok /Dma_enuInvalidChannelId /Dma_enuInvalidDataNum /Dma_enuNullPtr
 *
 * */
Dma_tenuErrorStatus Dma_enuInit(Dma_tstrCfg* Copy_strDmaCfg);


/****************************************************************
 * Description: 		this function is to start/stop DMA
 *
 * input args: 			pvidDmaNum, Dma_enuStreamNum ,Copy_u8IntState
 *
 * Return type: 		Dma_tenuErrorStatus for checking and make validation on the input arg
 * 						if it correct it will return Dma_enuOk
 * 						else will return one of these options
 * 						Dma_enuNok /Dma_enuInvalidChannelId /Dma_enuInvalidDataNum /Dma_enuNullPtr
 * */
Dma_tenuErrorStatus Dma_enuControl(void* pvidDmaNum,Dma_tenuStreamNum Copy_enuStreamNum, u8 Copy_u8DmaState);

/****************************************************************
 * Description: 		this function is to start/stop DMA
 *
 * input args: 			pvidDmaNum, Dma_enuStreamNum ,Copy_u8IntState
 *
 * Return type: 		Dma_tenuErrorStatus for checking and make validation on the input arg
 * 						if it correct it will return Dma_enuOk
 * 						else will return one of these options
 * 						Dma_enuNok /Dma_enuInvalidChannelId /Dma_enuInvalidDataNum /Dma_enuNullPtr
 * */

Dma_tenuErrorStatus Dma_enuClearFlags(void* pvidDmaNum, u64 Copy_u64Flags);



Dma_tenuErrorStatus Dma_enuRegisterCallBack(void* Dma_tstrCfg_DmaAdd, Dma_tenuStreamNum Copy_enuStreamNum, pcbf Cbf);




#endif /* DMA_H_ */
