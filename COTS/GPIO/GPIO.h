/*
 * GPIO.h
 *
 *  Created on: Mar 19, 2022
 *      Author: U3
 */

#ifndef GPIO_H_
#define GPIO_H_


/*MODES*/
/*INPUT*/
#define GPIO_MODE_INPUT_PUll_UP   		 					0b01000
#define GPIO_MODE_INPUT_PUll_DOWN			 				0b10000
#define GPIO_MODE_INPUT_FLOATING							0b00000

/*OUTPUT*/
#define GPIO_MODE_OUTPUT_PUSHPULL_PULLUP    			 	0b01001
#define GPIO_MODE_OUTPUT_PUSHPULL_PULLDOWN  			 	0b10001
#define GPIO_MODE_OUTPUT_PUSHPULL_NO_PULLUP_PULLDOWN   		0b00001
#define GPIO_MODE_OUTPUT_OPENDRAIN_PULLUP  			 		0b01101
#define GPIO_MODE_OUTPUT_OPENDRAIN_PULLDOWN 			 	0b10101
#define GPIO_MODE_OUTPUT_OPENDRAIN_NO_PULLUP_PULLDOWN  		0b00101
/*AF-reserved-*/
#define GPIO_MODE_AF_PUSHPULL 				 				0b00010
#define GPIO_MODE_AF_PUSHPULL_PULLUP						0b01010
#define GPIO_MODE_AF_PUSHPULL_PULLDOWN						0b10010

#define GPIO_MODE_AF_OPENDRAIN								0b00110
#define GPIO_MODE_AF_OPENDRAIN_PULLUP						0b01110
#define GPIO_MODE_AF_OPENDRAIN_PULLDOWN						0b10110


/*Analog*/
#define Analog  		 					0b00011


/*SPEED*/
#define GPIO_SPEED_LOW						0b00
#define GPIO_SPEED_MEDIUM					0b01
#define GPIO_SPEED_HIGH						0b10
#define GPIO_SPEED_VHIGH					0b11


/*PINS*/
#define  GPIO_PIN_0			(u8)0
#define  GPIO_PIN_1			(u8)1
#define  GPIO_PIN_2			(u8)2
#define  GPIO_PIN_3			(u8)3
#define  GPIO_PIN_4			(u8)4
#define  GPIO_PIN_5			(u8)5
#define  GPIO_PIN_6			(u8)6
#define  GPIO_PIN_7			(u8)7
#define  GPIO_PIN_8			(u8)8
#define  GPIO_PIN_9			(u8)9
#define  GPIO_PIN_10		(u8)10
#define  GPIO_PIN_11		(u8)11
#define  GPIO_PIN_12		(u8)12
#define  GPIO_PIN_13		(u8)13
#define  GPIO_PIN_14		(u8)14
#define  GPIO_PIN_15		(u8)15

/*PORTS*/
/*Base address*/
#define  GPIO_PORTA		    (u32)0x40021000
#define  GPIO_PORTB			(u32)0x40020C00
#define  GPIO_PORTC			(u32)0x40020800
#define  GPIO_PORTD			(u32)0x40020400
#define  GPIO_PORTE			(u32)0x40020000
#define  GPIO_PORTH			(u32)0x40021C00

/*MASKS*/
#define TWO_BITs_MASK 		0b11
#define ONE_BIT_MASK    	0b1
#define FOUR_BITs_MASK		0b1111

/* Set pin values */
#define HIGH (u8)1
#define LOW  (u8)0


/*Alternative functions macros*/

#define  GPIO_AF0_SYSTEM	     (void*)0x00000000
#define  GPIO_AF1_TIM_1_2	     (void*)0x00000010
#define  GPIO_AF2_TIM_3_5	     (void*)0x00000200
#define  GPIO_AF3_TIM_9_11	     (void*)0x00003000
#define  GPIO_AF4_I2C_1_3	     (void*)0x00040000
#define  GPIO_AF5_SPI_1_4	     (void*)0x00500000
#define  GPIO_AF6_SPI_3		     (void*)0x06000000
#define  GPIO_AF7_USART_1	     (void*)0x70000000
#define  GPIO_AF8_USART6	     (void*)0x00000008
#define  GPIO_AF9_I2C_2_3	     (void*)0x00000090
#define  GPIO_AF10_OTG_FS	     (void*)0x00000A00
#define  GPIO_AF12_SDIO		     (void*)0x000C0000
#define  GPIO_AF15_EVENTOUT	     (void*)0xF0000000


typedef struct
{
	u8 mode;
	u8 speed;
	u8 pin;
	void* port;
}GPIO_tConfig;

typedef enum
{
	GPIO_enu_OK,
	GPIO_enu_NOK
}GPIO_tenuErrorStatus;


GPIO_tenuErrorStatus GPIO_enuInitPinCfg(GPIO_tConfig* Add_Reg);
GPIO_tenuErrorStatus GPIO_enuSetPinValue(GPIO_tConfig* Add_Reg, u8 Loc_u8PinValue);
GPIO_tenuErrorStatus GPIO_enuGetPinValue(GPIO_tConfig* Add_Reg, pu8 pu8Add_var);
GPIO_tenuErrorStatus GPIO_enuSelectAf(GPIO_tConfig* Add_Reg, u32 Copy_u32AlternateValue);

#endif /* GPIO_H_ */
