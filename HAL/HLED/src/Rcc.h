/*
 * Rcc.h
 *
 *  Created on: Mar 28, 2022
 *      Author: Abdelrahman Yousry
 */
#ifndef RCC_H_
#define RCC_H_


/*Error status which may return from the functions*/
typedef enum
{
	Rcc_enuNok,
	Rcc_enuOk,
	Rcc_enuErrorNullPointer,
	Rcc_enuWrongPeripheralClk,
	Rcc_enuWrongBus,
	Rcc_enuWrongConfiguration
}Rcc_tenuErrorStatus;

typedef enum
{
	Rcc_enuHsi,
	Rcc_enuHse,
	Rcc_enuPll,
	Rcc_NotApllicable
}Rcc_tenuSysClkStatus;

/*Macros for HSE control function as an input argument
 * first most sig bit is a magic number for ensuring that the
 * args the user sent is from the macros that I provide to him
 * */
#define RCC_u64HSE_ON			(u64)0x100010000
#define RCC_u64HSE_OFF			(u64)0x1fffEffff


/*Macros for HSI control function as an input argument
 * first most sig bit is a magic number for ensuring that the
 * args the user sent is from the macros that I provide to him
 * */
#define RCC_u64HSI_ON			(u64)0x100000001
#define RCC_u64HSI_OFF			(u64)0x1fffffffE


/*Macros for HSI control function as an input argument
 * first most sig bit is a magic number for ensuring that the
 * args the user sent is from the macros that I provide to him
 * */
#define RCC_u64PLL_ON			(u64)0x101000000
#define RCC_u64PLL_OFF			(u64)0x1fEffffff


/**
 * Macros to select the system clock (reg--> RCC_CFGR)
 * it will be input args to func Rcc_enuSelectSysClk
 * */
#define RCC_u64SYSCLK_HSI       (u64)(0x100000000)
#define RCC_u64SYSCLK_HSE 		(u64)(0x100000001)
#define RCC_u64SYSCLK_PLL		(u64)(0x100000002)



/*Clock Ready Flag macros which will be a return from
this function RCC_enuGetClockRdyStatus
*/
#define RCC_u8Ready				(u8)1
#define RCC_u8NotReady			(u8)0


/* PLL Q mask */
#define RCC_PLLQ_2_MASK            (u32)0x02000000
#define RCC_PLLQ_3_MASK            (u32)0x03000000
#define RCC_PLLQ_4_MASK            (u32)0x04000000
#define RCC_PLLQ_5_MASK            (u32)0x05000000
#define RCC_PLLQ_6_MASK            (u32)0x06000000
#define RCC_PLLQ_7_MASK            (u32)0x07000000
#define RCC_PLLQ_8_MASK            (u32)0x08000000
#define RCC_PLLQ_9_MASK            (u32)0x90000000
#define RCC_PLLQ_10_MASK           (u32)0xA0000000
#define RCC_PLLQ_11_MASK           (u32)0xB0000000
#define RCC_PLLQ_12_MASK           (u32)0xC0000000
#define RCC_PLLQ_13_MASK           (u32)0xD0000000
#define RCC_PLLQ_14_MASK           (u32)0xE0000000
#define RCC_PLLQ_15_MASK           (u32)0xF0000000


/* PLL P mask */
#define RCC_PLLP_2_MASK            (u32)0x00020000
#define RCC_PLLP_4_MASK            (u32)0x00040000
#define RCC_PLLP_6_MASK            (u32)0x00060000
#define RCC_PLLP_8_MASK            (u32)0x00080000

/* PLL M mask */
#define RCC_PLLM_2_MASK            (u32)0x00000002

/* PLL N mask */
#define RCC_PLLN_MASK              0x

/* PLL SRC mask*/

#define RCC_PLLSRC_HSE_MASK        0x00010000
#define RCC_PLLSRC_HSI_MASK        0x00000000

/**
 * these masks is used as an input arg to this function
 * Rcc_enuSelectBusPrescaler()
 * to set the prescaler of specified bus
 * **/

#define RCC_u32APB1_NOT_DIVIDED			(u64)0x1ffffe3ff//this is a clear mask to clear bits 10, 11 ,12
														// so when so you can make right assignation
#define RCC_u32APB1_DIV_BY_2			(u64)0x100001000
#define RCC_u32APB1_DIV_BY_4			(u64)0x100001400
#define RCC_u32APB1_DIV_BY_8			(u64)0x100001800
#define RCC_u32APB1_DIV_BY_16			(u64)0x100001c00

#define RCC_u32APB2_NOT_DIVIDED			(u64)0x1ffff1fff
#define RCC_u32APB2_DIV_BY_2			(u64)0x100008000
#define RCC_u32APB2_DIV_BY_4			(u64)0x10000a000
#define RCC_u32APB2_DIV_BY_8			(u64)0x10000c000
#define RCC_u32APB2_DIV_BY_16			(u64)0x10000e000

#define RCC_u32AHB_NOT_DIVIDED			(u64)0x1ffffff0f
#define RCC_u32AHB_DIV_BY_2				(u64)0x100000080
#define RCC_u32AHB_DIV_BY_4			    (u64)0x100000090
#define RCC_u32AHB_DIV_BY_8			    (u64)0x1000000A0
#define RCC_u32AHB_DIV_BY_16			(u64)0x1000000B0
#define RCC_u32AHB_DIV_BY_64			(u64)0x1000000C0
#define RCC_u32AHB_DIV_BY_128			(u64)0x1000000D0
#define RCC_u32AHB_DIV_BY_256			(u64)0x1000000E0
#define RCC_u32AHB_DIV_BY_512			(u64)0x1000000F0

/*Masks for enabling peripherals*/
/*Input arg to func ---> Rcc_enuEnablePeripheralClk()
 * the most significant bit is a magic number for validating on the input args
 * */
#define RCC_u32AHB1_GPIOA				(u64)0x100000001
#define RCC_u32AHB1_GPIOB				(u64)0x100000002
#define RCC_u32AHB1_GPIOC				(u64)0x100000004
#define RCC_u32AHB1_GPIOD				(u64)0x100000008
#define RCC_u32AHB1_GPIOE				(u64)0x100000010
#define RCC_u32AHB1_GPIOH				(u64)0x100000080
#define RCC_u32AHB1_CRC					(u64)0x100001000
#define RCC_u32AHB1_DMA1				(u64)0x100200000
#define RCC_u32AHB1_DMA2				(u64)0x100400000

#define RCC_u32AHB2_OTGFS				(u64)0x100000080

#define RCC_u32APB1_TIM2				(u64)0x100000001
#define RCC_u32APB1_TIM3				(u64)0x100000002
#define RCC_u32APB1_TIM4				(u64)0x100000004
#define RCC_u32APB1_TIM5				(u64)0x100000008
#define RCC_u32APB1_WWDG				(u64)0x100000800
#define RCC_u32APB1_SPI2				(u64)0x100004000
#define RCC_u32APB1_SPI3				(u64)0x100008000
#define RCC_u32APB1_USART2				(u64)0x100020000
#define RCC_u32APB1_I2C1				(u64)0x100200000
#define RCC_u32APB1_I2C2				(u64)0x100400000
#define RCC_u32APB1_I2C3				(u64)0x100800000
#define RCC_u32APB1_PWR					(u64)0x110000000


#define RCC_u32APB2_TIM1				(u64)0x100000001
#define RCC_u32APB2_USART1				(u64)0x100000010
#define RCC_u32APB2_USART6				(u64)0x100000020
#define RCC_u32APB2_ADC1				(u64)0x100000100
#define RCC_u32APB2_SDIO				(u64)0x100000800
#define RCC_u32APB2_SPI1				(u64)0x100001000
#define RCC_u32APB2_SPI4				(u64)0x100002000
#define RCC_u32APB2_SYSCF				(u64)0x100004000
#define RCC_u32APB2_TIM9				(u64)0x100010000
#define RCC_u32APB2_TIM10				(u64)0x100020000
#define RCC_u32APB2_TIM11				(u64)0x100040000

/**types for buses macros used in these function to know which
 * bus for enabling and disabling specific peripheral
 * the func is -->Rcc_enuDisablePeripheralClk()
 * 			   -->Rcc_enuEnablePeripheralClk()
 * **/
#define RCC_u8BUS_APB1					(u8)0
#define RCC_u8BUS_APB2					(u8)1
#define RCC_u8BUS_AHB1					(u8)2
#define RCC_u8BUS_AHB2					(u8)3
/****************************************************************
 * Description: 		this function to control the HSE clock
 *
 * input args: 			RCC_u64HSE_ (you should make ctrl + enter to get the option)
 * 						which is ON / OFF
 *
 * Return type: 		Rcc_tenuErrorStatus for checking and make validation on the input arg
 * 						if it correct it will return Rcc_enuOk
 * 						else will return Rcc_enuNok
 * */
Rcc_tenuErrorStatus Rcc_enuHseControl(u64 Copy_ControlValue);


/****************************************************************
 * Description:			this function to control the HSI clock
 *
 * input args:			RCC_u64HSI_ (you should make ctrl + enter to get the option)
 * 						which is ON / OFF
 *
 * Return type:			Rcc_tenuErrorStatus for checking and make validation on the input arg
 * 						if it correct it will return Rcc_enuOk
 * 						else will return Rcc_enuNok
 * */
Rcc_tenuErrorStatus Rcc_enuHsiControl(u64 Copy_ControlValue);


/****************************************************************
 * Description: 		this function to control the HSE clock
 *
 * input args: 			RCC_u64HSE_ (you should make ctrl + enter to get the option)
 * 						which is ON / OFF
 *
 * Return type: 		Rcc_tenuErrorStatus for checking and make validation on the input arg
 * 						if it correct it will return Rcc_enuOk
 * 						else will return Rcc_enuNok
 * */
Rcc_tenuErrorStatus Rcc_enuPllControl(u64 Copy_ControlValue);

/****************************************************************
 * Description: 		this function to select system clock
 *
 * input args: 			RCC_u64SYSCLK_ (you should make ctrl + enter to get the option)
 * 						which is HSI / HSE / PLL
 *
 * Return type: 		Rcc_tenuErrorStatus for checking and make validation on the input arg
 * 						if it correct it will return Rcc_enuOk
 * 						else will return Rcc_enuNok
 * */
Rcc_tenuErrorStatus Rcc_enuSelectSysClk(u64 Copy_SysClk);

/****************************************************************
 * Description: 		this function to Clock Ready Status
 *
 * input args: 			1-RCC_u64SYSCLK_ (you should make ctrl + enter to get the option)
 * 						which is HSI / HSE / PLL
 *
 *						2- &address var to get the status
 *
 * Return type: 		Rcc_tenuErrorStatus for checking and make validation on the input arg
 * 						if it correct it will return Rcc_enuOk
 * 						else will return Rcc_enuNok
 * */
Rcc_tenuErrorStatus RCC_enuGetClockRdyStatus(u64 Copy_u8Clock,pu8 Add_pu8RdyStatus);


/**
 *Description:			This function is to configure the PLL clk with
 *						these configuration parameters
 *						PLLM , N , Q , P, SRC
 *						you should put these equns into your consideration
 *						when passing these args
 *						1-VCO IN= PPL input clk (HSE or HSI) / PPLM
 *						2-VCO OUT= VCO IN * N
 *						3-PLL system clock = VCO OUT / P
 *						4-Clock of USB peripheral = VCO OUT / Q
 *
 *Notes: 				1- You should configure PLL when it is off
 *	 					2- USB Peripheral should be fed with 48MHz clock
 *			     	  	3- VCO IN should be in range from 1 to 2MHz
 *			  	  		4- VCO OUT should be in range from 192 to 432MHz
 *			  	  		5- Sys clk shouldn't exceed 84 MHZ
 *
 *Inputs:
 *						u32 Copy_PLLM 	--> should be in range  2--to--63
 *						u32 Copy_PLLN 	--> should be in range  192--to--463
 *						u32 Copy_PLLP 	--> should be in range	2,4,6,8
 *						u32 Copy_PLLQ 	--> should be in range	2--to--15
 *						u32 Copy_PLLSRC	--> should be in range	RCC_PLLSRC_HSE_MASK or RCC_PLLSRC_HSI_MASK
 *
 *
 *Return type: 			Rcc_tenuErrorStatus
 *						will return Rcc_enuWrongConfiguration if you violate the configuration ranges
 *						or Rcc_enuOk if everything is ok
 **/
Rcc_tenuErrorStatus RCC_enuSelectPllConfig(u32 Copy_PLLM,
										   u32 Copy_PLLN,
										   u32 Copy_PLLP,
										   u32 Copy_PLLQ,
										   u32 Copy_PLLSRC);

/*
* Description: 		this function to Enabled Peripheral Clk
*
* input args: 		is the clk which need to be enabled
*					first args may be:		second args may be:
*					RCC_u8BUS_APB1			 RCC_u32AHB1_GPIOx
*					RCC_u8BUS_APB2
*					RCC_u8BUS_AHB1
*                   RCC_u8BUS_AHB2
*
* Return type: 		Rcc_tenuErrorStatus for checking and make validation on the input arg
* 						if it correct it will return Rcc_enuOk
* 						else will return Rcc_enuNok
* */
Rcc_tenuErrorStatus Rcc_enuEnablePeripheralClk(u8 copy_u8Bus,u64 copy_64RccPeripheralClk);

/*
* Description: 		this function to Disable Peripheral Clk
*
* input args: 		is the clk which need to be disabled
*
* Return type: 		Rcc_tenuErrorStatus for checking and make validation on the input arg
* 						if it correct it will return Rcc_enuOk
* 						else will return Rcc_enuNok
* */
Rcc_tenuErrorStatus Rcc_enuDisablePeripheralClk(u8 copy_u8Bus , u64 copy_u64RccPeripheralClk);

/*
* Description: 		this function to Select Bus Prescaler
*
* input args: 		Copy_u32Prescaler--> options -->
* 					prescaler macro:-
* 					RCC_u32AxB_DIV_BY_x / RCC_u32AxBx_NOT_DIVIDED
*
*
* Return type: 		Rcc_tenuErrorStatus for checking and make validation on the input arg
* 						if it correct it will return Rcc_enuOk
* 						else will return Rcc_enuNok
* */
Rcc_tenuErrorStatus Rcc_enuSelectBusPrescaler(u64 Copy_u64Prescaler);
#endif /* RCC_H_ */
