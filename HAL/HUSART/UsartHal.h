/*
 * UsartHal.h
 *
 *  Created on: May 2, 2022
 *      Author: U3
 */

#ifndef USARTHAL_H_
#define USARTHAL_H_
typedef enum
{
	UsartHal_enuOk,
	UsartHal_enuNok,
	UsartHal_enuNullptr,
	UsartHal_enuInvalidBusNum,

}UsartHal_tenuErrorStatus;


typedef enum
{
	Usart_enuBusNum_1,
	Usart_enuBusNum_2,
	Usart_enuBusNum_6,
	Usart_enuMaxBusNum
}t_enuUsartBusNum;
typedef struct
{
	void * Usart_pvChannel;
	u32 Usart_u32Clock;
	u16 Usart_u16BaudRate;
	u16 Usart_u16OverSampling;
	u16 Usart_u16DataLength;
	u16 Usart_u16InterruptCtrl;// for the 5 interrupts which will be macros | with each other then assigned to the reg
	u16 Usart_u16TransmitCtrl;
	u16	Usart_u16RecieveCtrl;
	u16 Usart_u32NumStopBit;
}t_UsartCfg;

typedef void(*pcallback)(void);


void Usart_vidHalInit(void);
UsartHal_tenuErrorStatus Usart_enuRegTxCompNotifyCbf(pcallback Usart_pcbfNotifyApp,t_enuUsartBusNum Copy_enuUsartBusNum);
UsartHal_tenuErrorStatus Usart_enuRegRxCompNotifyCbf(pcallback Usart_pcbfNotifyApp,t_enuUsartBusNum Copy_enuUsartBusNum);
UsartHal_tenuErrorStatus Usart_enuSendBufferZc(pu8 Z_pu8Buffer, u16 copy_u16Size, t_enuUsartBusNum Copy_enuBusNum);
UsartHal_tenuErrorStatus Usart_enuRecieveBufferZc(pu8 Z_pu8Buffer, u16 copy_u16Size,t_enuUsartBusNum Copy_enuBusNum);
UsartHal_tenuErrorStatus Usart_enuSendDataSync(u32 Copy_u32Data,t_enuUsartBusNum Copy_enuBusNum);
pu32 Usart_pu32ReciveDataSync(u32 Copy_u32Data,t_enuUsartBusNum Copy_enuBusNum);


#endif /* USARTHAL_H_ */
