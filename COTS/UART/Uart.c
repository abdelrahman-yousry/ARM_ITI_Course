/*
 * Uart.c
 *
 *  Created on: Apr 26, 2022
 *      Author: Abdelrahman Yousry
 */
#include "Std_types.h"
#include "Uart.h"
typedef struct
{
	u32 USART_SR;
	u32 USART_DR;
	u32 USART_BRR;
	u32 USART_CR1;
	u32 USART_CR2;
	u32 USART_CR3;
	u32 USART_GTPR;
}Uart_tstrReg;

void Uart_vidInit(Uart_tCfg* copy_UartCfg)
{
	u32 UsartDiv =0 ;
	u32 UsartMantissa= 0 ;
	u32 UsartFraction = 0;
	Uart_tstrReg* Loc_ptrReg = copy_UartCfg->Uart_pvChannel ;
	if(copy_UartCfg->Uart_u32OverSampling==UART_u32UART_MASK_OVERSAMPLING_16)
	{
		UsartDiv = ((copy_UartCfg->Uart_u64Clock)*1000)/(16*copy_UartCfg->Uart_u32BaudRate);
		UsartFraction = UsartDiv%1000;
		UsartFraction *=16 ;
	}
	else if(copy_UartCfg->Uart_u32OverSampling==UART_u32UART_MASK_OVERSAMPLING_8)
	{
		//16000000000/8*9600=208 333
		UsartDiv = ((copy_UartCfg->Uart_u64Clock)*1000)/(8*copy_UartCfg->Uart_u32BaudRate);
		UsartFraction = UsartDiv%1000;
		UsartFraction *=8;
	}
	UsartFraction=(UsartFraction+500)/1000;
	UsartMantissa=UsartDiv/1000;
	Loc_ptrReg->USART_BRR=(UsartMantissa<<4)|UsartFraction;
	Loc_ptrReg->USART_CR1=0;
	Loc_ptrReg->USART_CR1=(copy_UartCfg->Uart_u32OverSampling|
			copy_UartCfg->Uart_u32DataLength|
			copy_UartCfg->Uart_u32InterruptCtrl|
			copy_UartCfg->Uart_u32TransmitCtrl|
			copy_UartCfg->Uart_u32RecieveCtrl);
	Loc_ptrReg->USART_CR1|=UART_32MASK_ENABLE;//enable uart UE in CTRl1 reg

}

void Uart_vidSendByteSync(u32 Byte, void* Channel)
{
	while(((((Uart_tstrReg*)Channel)->USART_SR)&UART_32TC_MASK)==0);
	((Uart_tstrReg*)Channel)->USART_DR = Byte;
}

