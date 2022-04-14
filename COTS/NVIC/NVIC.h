/*
 * NVIC.h
 *
 *  Created on: Apr 13, 2022
 *      Author: Abdelrahman Yousry
 */

#ifndef NVIC_H_
#define NVIC_H_

/*this is the Error options which will be the return of the functions below*/
typedef enum
{
	Nvic_enuOk,
	Nvic_enuInvalidIRQn,
	Nvic_enuNullPointer
}Nvic_tenuErrorStatus;



typedef enum
{
	Red,
	Green

}color1;
/*this enum is specific for the IRQn of stm32f401 but cortex m4 is have 240 pins */
typedef enum
{
  NVIC_WWDG_IRQn            = 0,
  NVIC_PVD_IRQn             = 1,
  NVIC_TAMP_STAMP_IRQn      = 2,
  NVIC_RTC_WKUP_IRQn        = 3,
  NVIC_FLASH_IRQn           = 4,
  NVIC_RCC_IRQn             = 5,
  NVIC_EXTI0_IRQn           = 6,
  NVIC_EXTI1_IRQn           = 7,
  NVIC_EXTI2_IRQn           = 8,
  NVIC_EXTI3_IRQn           = 9,
  NVIC_EXTI4_IRQn           = 10,
  NVIC_DMA1_Stream0_IRQn    = 11,
  NVIC_DMA1_Stream1_IRQn    = 12,
  NVIC_DMA1_Stream2_IRQn    = 13,
  NVIC_DMA1_Stream3_IRQn    = 14,
  NVIC_DMA1_Stream4_IRQn    = 15,
  NVIC_DMA1_Stream5_IRQn    = 16,
  NVIC_DMA1_Stream6_IRQn    = 17,
  NVIC_ADC_IRQn             = 18,
  NVIC_EXTI9_5_IRQn         = 23,
  NVIC_TIM1_BRK_TIM9_IRQn   = 24,
  NVIC_TIM1_UP_TIM10_IRQn   = 25,
  NVIC_TIM1_TRG_COM_TIM11_IR= 26,
  NVIC_TIM1_CC_IRQn         = 27,
  NVIC_TIM2_IRQn            = 28,
  NVIC_TIM3_IRQn            = 29,
  NVIC_TIM4_IRQn            = 30,
  NVIC_I2C1_EV_IRQn         = 31,
  NVIC_I2C1_ER_IRQn         = 32,
  NVIC_I2C2_EV_IRQn         = 33,
  NVIC_I2C2_ER_IRQn         = 34,
  NVIC_SPI1_IRQn            = 35,
  NVIC_SPI2_IRQn            = 36,
  NVIC_USART1_IRQn          = 37,
  NVIC_USART2_IRQn          = 38,
  NVIC_EXTI15_10_IRQn       = 40,
  NVIC_RTC_Alarm_IRQn       = 41,
  NVIC_OTG_FS_WKUP_IRQn     = 42,
  NVIC_DMA1_Stream7_IRQn    = 47,
  NVIC_SDIO_IRQn            = 49,
  NVIC_TIM5_IRQn            = 50,
  NVIC_SPI3_IRQn            = 51,
  NVIC_DMA2_Stream0_IRQn    = 56,
  NVIC_DMA2_Stream1_IRQn    = 57,
  NVIC_DMA2_Stream2_IRQn    = 58,
  NVIC_DMA2_Stream3_IRQn    = 59,
  NVIC_DMA2_Stream4_IRQn    = 60,
  NVIC_OTG_FS_IRQn          = 67,
  NVIC_DMA2_Stream5_IRQn    = 68,
  NVIC_DMA2_Stream6_IRQn    = 69,
  NVIC_DMA2_Stream7_IRQn    = 70,
  NVIC_USART6_IRQn          = 71,
  NVIC_I2C3_EV_IRQn         = 72,
  NVIC_I2C3_ER_IRQn         = 73,
  NVIC_FPU_IRQn             = 81,
  NVIC_SPI4_IRQn            = 84
}Nvic_tenuIRQn;




/*****************************************************************
 * Description: 		Enables an interrupt or exception.
 *
 * input args: 			Pin number
 *
 * Return type: 		Nvic_enuErrorStatus_t for checking and make validation on the input arg
 * 						if it correct it will return Nvic_enuOk
 * 						else will return Nvic_enuNok
 *
 */
Nvic_tenuErrorStatus NVIC_enuEnableIRQ(Nvic_tenuIRQn copy_IRQn);
/****************************************************************
 * Description: 		Disables an interrupt or exception.
 *
 * input args: 			Pin number
 *
 * Return type: 		Nvic_enuErrorStatus_t for checking and make validation on the input arg
 * 						if it correct it will return Nvic_enuOk
 * 						else will return Nvic_enuNok
 *
 */
Nvic_tenuErrorStatus NVIC_enuDisableIRQ(Nvic_tenuIRQn copy_IRQn);

/****************************************************************
 * Description: 		Sets the pending status of interrupt or exception to 1.
 *
 * input args: 			Pin number
 *
 * Return type: 		Nvic_enuErrorStatus_t for checking and make validation on the input arg
 * 						if it correct it will return Nvic_enuOk
 * 						else will return Nvic_enuNok
 *
 */
Nvic_tenuErrorStatus NVIC_enuSetPendingIRQ(Nvic_tenuIRQn copy_IRQn);
/****************************************************************
 * Description: 		Clears the pending status of interrupt or exception to 1.
 *
 * input args: 			Pin number
 *
 * Return type: 		Nvic_enuErrorStatus_t for checking and make validation on the input arg
 * 						if it correct it will return Nvic_enuOk
 * 						else will return Nvic_enuNok
 *
 */
Nvic_tenuErrorStatus NVIC_enuClearPendingIRQ(Nvic_tenuIRQn copy_IRQn);
/****************************************************************
 * Description: 		Reads the pending status of interrupt or exception. This function returns nonzero
 *						value if the pending status is set to 1.
 *
 * input args: 			Pin number
 *
 * Return type: 		Nvic_enuErrorStatus_t for checking and make validation on the input arg
 * 						if it correct it will return Nvic_enuOk
 * 						else will return Nvic_enuNok
 *
 */
Nvic_tenuErrorStatus NVIC_enuGetPendingIRQ(Nvic_tenuIRQn copy_IRQn, pu8 copy_pu8AddActiveStatus);
/****************************************************************
 * Description: 		Sets the priority of an interrupt or exception
 * 						with configurable priority level to 1.
 *
 * input args: 			Pin number
 *
 * Return type: 		Nvic_enuErrorStatus_t for checking and make validation on the input arg
 * 						if it correct it will return Nvic_enuOk
 * 						else will return Nvic_enuNok
 *
 */
u8 NVIC_enuEncodePriority(u8 copy_u8SubGpNum, u8 copy_u8PreemptionValue, u8 copy_u8SubGpValue);
Nvic_tenuErrorStatus NVIC_enuSetPriority(Nvic_tenuIRQn copy_IRQn, u8 priority);
///****************************************************************


#endif /* NVIC_H_ */

