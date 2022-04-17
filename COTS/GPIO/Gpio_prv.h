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




#define MODER_MASK	0b00000011
#define OTYPER_MASK	0b00000001
#define PUPDR_MASK	0b00000011
#define SPEEDR_MASK 0b00000011

#define OTYPER_CLEAR	2
#endif /* GPIO_PRV_H_ */
