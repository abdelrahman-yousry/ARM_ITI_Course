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
const t_UsartCfg Usart_DeviceCfg[MAX_NUM_OF_DEVICES]=
{
		[Blutooth]={
				.Usart_pvChannel=USART_1,
				.Usart_u32Clock=16000000,
				.Usart_u16BaudRate=9600,
				.Usart_u16TransmitCtrl=USART_u16MASK_TX_ENABLE,
				.Usart_u16RecieveCtrl=USART_u16MASK_RX_ENABLE,
				.Usart_u16OverSampling=USART_u16MASK_OVERSAMPLING_16,
				.Usart_u32NumStopBit=USART_u16MASK_ONE_STOP_BIT,
				.Usart_u16InterruptCtrl=USART_u16INTERRUPT_RXNE_ENABLE,// I shouldn't enable Tc int
				.Usart_u16DataLength=USART_u16DATA_LENGTH_9BIT,
				.Usart_u32NumStopBit=USART_u16MASK_ONE_STOP_BIT,

		}
};



