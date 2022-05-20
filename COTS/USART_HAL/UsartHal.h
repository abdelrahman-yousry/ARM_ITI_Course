/*
 * UsartHal.h
 *
 *  Created on: May 2, 2022
 *      Author: Abdelrahman Yousry
 */

#ifndef USARTHAL_H_
#define USARTHAL_H_

typedef enum
{
	Usart_enuBusNum1,
	Usart_enuBusNum2,
	Usart_enuBusNum6,
	Usart_enuMaxNum,
}Usart_tenuBusNum;

//*Uart channels base addresses*//
#define USART_1									(void*)0x40011000//channel 1
#define USART_2									(void*)0x40004400//channel 2
#define USART_6									(void*)0x40011400//channel 6

typedef enum
{
	UsartHal_enuOk,
	UsartHal_enuNok,
	UsartHal_enuNullptr,
	UsartHal_enuInvalidBusNum,

}UsartHal_tenuErrorStatus;



typedef void(*pcallback)(void);


void Usart_vidHalInit(void);

/**************************************REG Call Back Functions****************************************/
UsartHal_tenuErrorStatus Usart_enuRegTxCompNotifyCbf(pcallback Usart_pcbfNotifyApp, Usart_tenuBusNum Copy_enuUsartBusNum);
UsartHal_tenuErrorStatus Usart_enuRegRxCompNotifyCbf(pcallback Usart_pcbfNotifyApp, Usart_tenuBusNum Copy_enuUsartBusNum);

//UsartHal_tenuErrorStatus Usart_enuRegDma1CompNotifyCbf(pcallback Dma1_pcbfNotifyApp,Dma_tenuChannelId Copy_enuDmaChNum);
//UsartHal_tenuErrorStatus Usart_enuRegDma2CompNotifyCbf(pcallback Dma2_pcbfNotifyApp,Dma_tenuChannelId Copy_enuDmaChNum);

/*******************************Async Functions using Interrupts**********************************/
UsartHal_tenuErrorStatus Usart_enuSendBufferZc(pu8 Z_pu8Buffer, u16 copy_u16Size, Usart_tenuBusNum Copy_enuBusNum);
UsartHal_tenuErrorStatus Usart_enuRecieveBufferZc(pu8 Z_pu8Buffer, u16 copy_u16Size,Usart_tenuBusNum Copy_enuBusNum);

UsartHal_tenuErrorStatus Usart_enuSendBufferDmaZc(pu8 Copy_pu8Buffer, u16 copy_u16Size, Usart_tenuBusNum Copy_enuBusNum);
UsartHal_tenuErrorStatus Usart_enuRecieveBufferDmaZc(pu8 Copy_pu8Buffer, u16 copy_u16Size, Usart_tenuBusNum Copy_enuBusNum);
/*********************************************Sync Functions**************************************/
UsartHal_tenuErrorStatus Usart_enuHalSendDataSync(u32 Copy_u32Data,Usart_tenuBusNum Copy_enuBusNum);
pu32 Usart_pu32ReciveDataSync(u32 Copy_u32Data,Usart_tenuBusNum Copy_enuBusNum);




#endif /* USARTHAL_H_ */
