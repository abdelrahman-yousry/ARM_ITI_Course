/*
 * Rcc_priv.h
 *
 *  Created on: Mar 30, 2022
 *      Author: Abdelrahman Yousry
 */

#ifndef RCC_PRIV_H_
#define RCC_PRIV_H_

/**This an image for the registers of the RCC peripheral
 * and it is ordered according to their offset in the reference manual
 * **/
typedef struct{

	volatile u32 RCC_CR;
	volatile u32 RCC_PLLCFGR;
	volatile u32 RCC_CFGR;
	volatile u32 RCC_CIR;
	volatile u32 RCC_AHB1RSTR;
	volatile u32 RCC_AHB2RSTR;
	volatile u32 Reserved1[2];
	volatile u32 RCC_APB1RSTR;
	volatile u32 RCC_APB2RSTR;
	volatile u32 Reserved2[2];
	volatile u32 RCC_AHB1ENR;
	volatile u32 RCC_AHB2ENR;
	volatile u32 Reserved3[2];
	volatile u32 RCC_APB1ENR;
	volatile u32 RCC_APB2ENR;
	volatile u32 Reserved4[2];
	volatile u32 RCC_AHB1LPENR;
	volatile u32 RCC_AHB2LPENR;
	volatile u32 Reserved5[2];
	volatile u32 RCC_APB1LPENR;
	volatile u32 RCC_APB2LPENR;
	volatile u32 Reserved6[2];
	volatile u32 RCC_BDCR;
	volatile u32 RCC_CSR;
	volatile u32 Reserved7[2];
	volatile u32 RCC_SSCGR;
	volatile u32 RCC_PLLI2SCFGR;
	volatile u32 Reserved8;
	volatile u32 RCC_DCKCFGR;

}Rcc_tReg;

/*Base address of the RCC registers*/
#define RCC_BASE_ADDRESS		0x40023800
/*constant pointer from the type of the the struct and static
 * because I don't need any file or(user) to access it because it is priv
 *
 * */

/*CLEAR_MAGIC_NUMBER_MASK*/
#define CLEAR_MAGIC_NUMBER_MASK		0x100000000
/*Questions
 * 1- hal keda 2na 3mlt var (pointer) 2l size bta3oh 29*32 byte!!?
 * 2l 2gaba 2ah 34an keda 3mlt maodoo3 2l #define
 */

/*This method will not reserve pointer, I just casting
 * the base address to struct and then I will access
 * the members' struct by arrow operator
 * */
#define Rcc  ((Rcc_tReg *) RCC_BASE_ADDRESS)
/*Here we will reserve pointer to struct*/
//static Rcc_tReg* const Rcc = (Rcc_tReg *)RCC_BASE_ADDRESS;


/*Clock source Ready status*/
#define RCC_u32HSI_READY			    (u32)(0x00000002)
#define RCC_u32HSE_READY			    (u32)(0x00020000)
#define RCC_u32PLL_READY			    (u32)(0x02000000)

/*get the status of the sysclk to know the running clock*/
#define RCC_u32CFGR_SWS_Checking		(u32)(0x0000000c)

/**
 * Mask for clearing first two bits which responsible for SW
 * SysClock in RCC_CFGR to assign in it the desired clock
 * */
#define RCC_SYS_CLK_CLEAR_MASK			(u32)0x1111111c



#define SWS0			2
#define SWS1			3

#define SW_MSK			0x00000003
#define SWS_MSK			0x0000000C


#define NULL 			0x00
Rcc_tenuSysClkStatus Rcc_vidGetSysClkStatus(void);

#endif /* RCC_PRIV_H_ */


/*
 * 3ndi 3 methods 34an 2a2dar access 2l registers
 *
 // 3ebha 2ny h3ml #defines kteer l kol 2l per b 2l reg bta3t kol 2l peri
  * w kman h7sb kol mrra 2l base address + ofsset bta3 2l reg
 * 1- #define GPIOA_CR 		*(uint32_t *)(0x40000)
 * 					.			.
 * ************************************************
 // hena sahlt 2ni 23ml 7sabat bas zawdt 2l #defines
 * 2-#define l kol 3l periph
 * --> #define GPIOA   (BAse address)
 * -- 			  .
 * 				  .
 * 				  E
 *
 * -- #define l kol 2l, reg offset
 * --> #define CR_OFSSET 	0
 * 				.			4
 * 				.			8
 *
 *
 *-- #define ll regs 2ll f kol periph
 * --> #define RCC_CR  (*(uint32_t)*(GPIOA+CR_Offset)
 * *************************************************
 * 3-hena deh 2fdal tre2a
 *  2ni h3ml struct feh 2l reg bta3t 2l peripherals kol wa7d hyb2a b 2l offsset bta3oh
 *  mn 8er ma 27gz mnoh varibale l2n already maogood 3ndi f 2l hardware
 *
 * */
///////////////////////////////////////////////////////////////////////////////////////
/*
 * 34an 23ml control 3la 2l Reg
 * lw 3nd func bta5od mni
 * SetEnable(name of the periph, pin , value)
 * {
 * 	peripheral -->enable|=value<< pin ;
 * }
 * mmkn badal ma 23ml 2l operation bta3t 2l sheft
 * 24of 2eh 2l mask 2lli hytla3 mn 2l shifting w 23mloh k mask talama 7aga sabta
 *
 * f yb2a keda f 7alt 2ni h3ml set
 * peripheral --> enable|= pin (which is mask)
 *  w lw h3ml clear
 * peripheral --> enable &=~ pin
 *
 *
 * */
