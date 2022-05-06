/*
 * Uart.h
 *
 *  Created on: Apr 28, 2022
 *      Author: Abdelrahman Yousry
 */

#ifndef UART_H_
#define UART_H_


#define USART_u16MASK_UE_ENABLE						((u16)0x2000) // to enable The Usart peripheral

#define USART_u16MASK_TX_ENABLE						((u16)0x0008)	// will be | to set the TX bit
#define USART_u16MASK_TX_DISABLE					((u16)0xFFFB)	// will be & to clear the TX bit

#define USART_u16MASK_RX_ENABLE						((u16)0x0004)  // will be | to set the RX bit
#define USART_u16MASK_RX_DISABLE					((u16)0xFFFD)  // will be & to clear the RX bit

#define USART_u16MASK_OVERSAMPLING_8				((u16)0x8000)
#define USART_u16MASK_OVERSAMPLING_16				((u16)0x0000)

#define USART_u16MASK_ONE_STOP_BIT					((u16)0x0000)
#define USART_u16MASK_HALF_STOP_BIT					((u16)0x1000)
#define USART_u16MASK_TWO_STOP_BIT					((u16)0x2000)


#define USART_u16INTERRUPT_TXE_ENABLE				((u16) 0x0080)
#define USART_u16INTERRUPT_TC_ENABLE				((u16) 0x0040)
#define USART_u16INTERRUPT_RXNE_ENABLE			((u16) 0x0020)
#define USART_u16INTERRUPT_MASK_DISABLE			((u16) 0x0000)// for any interrupt


#define USART_u16DATA_LENGTH_8BIT					  ((u16) 0x0000)
#define USART_u16DATA_LENGTH_9BIT					  ((u16) 0x1000)

#define USART_BUSNUM_1								      (u8)0
#define USART_BUSNUM_2								      (u8)1
#define USART_BUSNUM_6								      (u8)2

//*Uart channels base addresses*//
#define USART_1									(void*)0x40011000//channel 1
#define USART_2									(void*)0x40004400//channel 2
#define USART_6									(void*)0x40011400//channel 6



typedef void(*pcbf)(void);


typedef struct{
	void * Usart_pvChannel;
	u32 Usart_u32Clock;
	u16 Usart_u32BaudRate;
	u16 Usart_u32OverSampling;
	u16 Usart_u32DataLength;
	u16 Usart_u32InterruptCtrl;// for the 5 interrupts which will be macros | with each other then assigned to the reg
	u16 Usart_u32TransmitCtrl;
	u16	Usart_u32RecieveCtrl;
	u16 Usart_u32NumStopBit;

}Uart_tCfg;

typedef enum
{
	Usart_enuOk,
	Usart_enuNok,
	Usart_enuNullptr,
	Usart_enuInvalidDataLength,

}Usart_tenuErrorStatus;

typedef enum
{
	Usart_enuIntDisabled,
	Usart_enuIntEnabled
}tenu_UsartInterruptState;
/****************************************************************
 * Description: 		this function to Init the USART peripheral
 *
 * input args: 			Uart_tCfg* copy_UartCfg --> which contains this members
 * 						void * Uart_pvChannel;    -->to select the channel
						u64 Uart_u64Clock;        -->to select the clk
						u32 Uart_u32BaudRate;     -->to select the Bauderate
						u32 Uart_u32OverSampling; -->to select the oversampling
						u32 Uart_u32DataLength;   -->to select the Datalength
						u32 Uart_u32InterruptCtrl;-->to enable/disable Interrupt of USART periph
						u32 Uart_u32TransmitCtrl; -->to enable/disable the Transmitter
						u32	Uart_u32RecieveCtrl;  -->to enable/disable the reciever

 *
 * Return type: 		Usart_tenuErrorStatus for checking and make validation on the input arg
 * 						if it correct it will return Usart_enuOk
 * 						else will return Usart_enuNok
 * */
Usart_tenuErrorStatus Uart_enuInit(Uart_tCfg* copy_UartCfg);
/****************************************************************
 * Description: 		this function to SendByteSync
 *
 * input args: 			u32 Byte ,void* Channel
 * 						Byte 		--> is the data which want to be send
						Channel		--> is the channel base address
 *
 * Return type: 		Usart_tenuErrorStatus for checking and make validation on the input arg
 * 						if it correct it will return Usart_enuOk
 * 						else will return Usart_enuNok
 * */
Usart_tenuErrorStatus Usart_vidSendDataSync(u32 Byte ,void* Channel);
/****************************************************************
 * Description: 		this function to SendByteSync
 *
 * input args: 			void* Channel, pu32 Copy_u32AddResult
 * 						Copy_u32AddResult 		--> is the data which want to be read
						Channel		--> is the channel base address
 *
 * Return type: 		Usart_tenuErrorStatus for checking and make validation on the input arg
 * 						if it correct it will return Usart_enuOk
 * 						else will return Usart_enuNok
 * */
Usart_tenuErrorStatus Usart_vidRecieveDataSync(void* Channel, pu32 Copy_u32AddResult);



/***************************************Asynchronous Functions***********************************************/

Usart_tenuErrorStatus Usart_enuSendDataAsync(u32 Byte ,void* Channel);
Usart_tenuErrorStatus Usart_enuRecieveDataAsync(void* Channel, pu32 Copy_u32AddResult);


/****************************************Control Functions***************************************************/
Usart_tenuErrorStatus Usart_enuTcInterruptCtrl(void* Copy_pvChannel, tenu_UsartInterruptState Copy_enuIntState);
Usart_tenuErrorStatus Usart_enuRxInterruptCtrl(void* Copy_pvChannel, tenu_UsartInterruptState Copy_enuIntState);

/***************************************Register Call Back Func**********************************************/
extern Usart_tenuErrorStatus Usart_enuRegisterHalCbf(pcbf Uart_pcbfManCallBack,u8 Copy_u8BusNum);

extern u8 Usart_u8ReadTcFlag(void* Copy_pvidChannel);
extern u8 Usart_u8ReadRxFlag(void* Copy_pvidChannel);
extern Usart_tenuErrorStatus Uart_ClearTcFlag(void * Copy_pvidChannel);
extern Usart_tenuErrorStatus Uart_ClearRxFlag(void * Copy_pvidChannel);


#endif /* UART_H_ */
