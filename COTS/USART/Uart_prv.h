/*
 * Uart_prv.h
 *
 *  Created on: Apr 28, 2022
 *      Author: Abdelrahman Yousry
 */

#ifndef UART_PRV_H_
#define UART_PRV_H_

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

#define USART_u16DR_VALIDATE					((u16)0xFE00) // because maximum data length is 9 bits

#define USART_u16TXE							((u16) 0x0080)// to get the TXE flag value which will be set if the DR reg is empty

#define USART_u16DATA_LENGTH_VALIDATION			((u16) 0xFE00)//11111110 0000 0000 becasue DR reg should have data between 8 to 9 bits

#define USART_u16CR1_CLR_MASK					((u16) 0xB0EC)//1011 0000 1110 1100
#define USART_u16CR2_CLR_MASK					((u16) 0xCFFF)//0011 1111 1111 0000


#define USART_u16TC_MASK						((u16)0x0040) // to get the value of the Transmit complete flag
#define USART_u16RXNE_MASK						((u16)0x0020) // to get the value of the Recieve Not Empty flag

#define UART_u16CLEAR_TC_MASK					((u16) 0xFFBF)// to be & to clear the TC flag
#define UART_u16CLEAR_RXNEIE_MASK				((u16) 0xFFDF)// to be & to clear the RXNEIE flag


// I commented them because they are defined at cmsis lib
//void USART1_IRQHandler(void);
//void USART2_IRQHandler(void);
//void USART6_IRQHandler(void);



#endif /* UART_PRV_H_ */
