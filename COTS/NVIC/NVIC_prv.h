/*
 * NVIC_prv.h
 *
 *  Created on: Apr 13, 2022
 *      Author: Abdelrahman Yousry
 */

#ifndef NVIC_PRV_H_
#define NVIC_PRV_H_

/*this is an image for the registers of NVIC arm processor*/
typedef struct{
	volatile u32 NVIC_ISER[8];
	volatile u32 Reserved0[24];
	volatile u32 NVIC_ICER[8];
	volatile u32 Reserved1[24];
	volatile u32 NVIC_ISPR[8];
	volatile u32 Reserved2[24];
	volatile u32 NVIC_ICPR[8];
	volatile u32 Reserved3[24];
	volatile u32 NVIC_IABR[8];
	volatile u32 Reserved4[56];
	volatile u8 NVIC_IPR[240];
	volatile u32 Reserved5[644];
	volatile u32 NVIC_STIR;
}NVIC_Registers_t;

/*BASE ADDRESS*/
#define NVIC_BASE_ADDRESS		0xE000E100

#define NVIC				   ((NVIC_Registers_t*)NVIC_BASE_ADDRESS)

//this value is to make the Driver generic for any vendor
//but if I put the value 84, this mean that I specified this driver for stm_401
#define NUMBERS_OF_IRQn		240


#define ONE_BIT_MASK					(u8)1
#define FOUR_BITS_IMPLEMENTEd			(u8)4
#define NVIC_PRIORITY_MASK				(u8)0xf0

#endif /* NVIC_PRV_H_ */
