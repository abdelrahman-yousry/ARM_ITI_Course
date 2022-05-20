/*
 * UsartHal_cfg.c
 *
 *  Created on: May 2, 2022
 *      Author: Abdelrahman Yousry
 */
#include "Std_types.h"
#include "Uart.h"
#include "UsartHal.h"
#include "UsartHal_cfg.h"
const Uart_tCfg Usart_DeviceCfg[MAX_NUM_OF_DEVICES]=
{
		[Blutooth]={
				.Usart_pvChannel=USART_1,
				.Usart_u64Clock=16000000,
				.Usart_u16BaudRate=9600,
				.Usart_u16TransmitCtrl=USART_u16MASK_TX_ENABLE,
				.Usart_u16RecieveCtrl=USART_u16MASK_RX_ENABLE,
				.Usart_u16OverSampling=USART_u16MASK_OVERSAMPLING_16,
				.Usart_u32NumStopBit=USART_u16MASK_ONE_STOP_BIT,
				.Usart_u16InterruptCtrl=USART_u16INT_MASK_DISABLE,// I shouldn't enable Tc/Rx int
				.Usart_u16DataLength=USART_u16DATA_LENGTH_8BIT,
				.Usart_u32NumStopBit=USART_u16MASK_ONE_STOP_BIT,

		}
};



