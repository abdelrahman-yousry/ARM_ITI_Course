/*
 * Uart.h
 *
 *  Created on: Apr 26, 2022
 *      Author: Abdelrahman Yousry
 */

#ifndef UART_H_
#define UART_H_

#define UART_32TC_MASK							0x0040 // to get the value of the Transmit complete flag
#define UART_32MASK_ENABLE						0x2000
#define UART_32UART_MASK_TX_ENABLE				0x0008	// will be | to set the TX bit
#define UART_32UART_MASK_TX_DISABLE				0xFFFB	// will be & to clear the TX bit
#define UART_32UART_MASK_RX_ENABLE				0x0002  // will be | to set the RX bit
#define UART_32UART_MASK_RX_DISABLE				0xFFFD  // will be & to clear the RX bit
#define UART_u32UART_MASK_OVERSAMPLING_8		0x00080000
#define UART_u32UART_MASK_OVERSAMPLING_16		0x00000000
#define UART_1									(void*)0x40011000


//#define UART1	((Uart_tstrReg*)UART1_BASEADDRESS)

typedef struct{
	void * Uart_pvChannel;
	u64 Uart_u64Clock;
	u32 Uart_u32BaudRate;
	u32 Uart_u32OverSampling;
	u32 Uart_u32DataLength;
	u32 Uart_u32InterruptCtrl;// for the 5 interrupts which will be macros | with each other then assigned to the reg
	u32 Uart_u32TransmitCtrl;
	u32	Uart_u32RecieveCtrl;

}Uart_tCfg;

void Uart_vidInit(Uart_tCfg* copy_UartCfg);
void Uart_vidSendByteSync(u32 Byte ,void* Channel);


#endif /* UART_H_ */
