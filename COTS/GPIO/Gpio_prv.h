/*
 * Gpio_prv.h
 *
 *  Created on: Apr 4, 2022
 *      Author: Abdelrahman Yousry
 */

#ifndef GPIO_PRV_H_
#define GPIO_PRV_H_


typedef struct
{
	u32 GPIOx_MODER;
	u32 GPIOx_OTYPER;
	u32 GPIOx_OSPEEDR;
	u32 GPIOx_PUPDR;
	u32 GPIOx_IDR;
	u32 GPIOx_ODR;
	u32 GPIOx_BSRR;
	u32 GPIOx_LCKR;
	u32 GPIOx_AFRL;
	u32 GPIOx_AFRH;

}GpioReg_t;



#define ONE_BIT_MASK 	0b00000001U	//for clearing the req bits
#define TWO_BIT_MASK 	0b00000011U	//for clearing the required bits
#define FOUR_BIT_MASK	0b00001111U

#define MODER_MASK	0b00000011U		//for getting the specific config from macro
#define OTYPER_MASK	0b00000100U
#define PUPDR_MASK	0b00011000U
#define SPEEDR_MASK 0b00000011U

#define ALTERNATIVE_FUNCTION_MODE	0x02
#endif /* GPIO_PRV_H_ */
