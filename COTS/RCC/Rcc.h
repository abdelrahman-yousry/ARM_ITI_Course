#ifndef RCC_H_
#def RCC_H_

/*Clock source control flag*/
#define  RCC_enuOFF  0
#define  RCC_enuON   1

/*HSE control flag options*/
#define RCC_u32_HSE_ON 		        (u32)0x00010000 //ON
#define RCC_u32_HSE_OFF		        (u32)0x00000000 //OFF

/*HSI control flag options*/
#define RCC_u32_HSI_ON 		        (u32)0x00000001 //ON
#define RCC_u32_HSI_OFF		        (u32)0x00000000 //OFF

/*pll control flag options*/
#define RCC_u32_PLL_ON 		        0x01000000 //ON
#define RCC_u32_PLL_OFF		        (u32)0x00000000 //OFF

/**********************************************************/

/*Clock source Ready flag*/
#define RCC_u32HSI_READY			    (u32)(0x00000002)
#define RCC_u32HSE_READY			    (u32)(0x00020000)
#define RCC_u32PLL_READY			    (u32)(0x02000000)

/*Clock control flag masks*/
#define RCC_HSI_CONTROL_FLAG       (u32)0x00000001
#define RCC_HSE_CONTROL_FLAG       (u32)0x00010000
#define RCC_PLL_CONTROL_FLAG       (u32)0x01000000

/*System clocks*/
#define RCC_u32SYSCLK_HSI		      (u32)(0x00000000)
#define RCC_u32SYSCLK_HSE		      (u32)(0x00000001)
#define RCC_u32SYSCLK_PLL		      (u32)(0x00000002)

/*SWS mask for detecting the selected system clock
* it consists of two bits 2,3 in the CFGR register
* and it was set by hardware 
*/
#define RCC_CFGR_SWS               0x000000012 

/*Clear mask for sw*/
#define RCC_SW_CLEAR_MASK          (u32)0x000000003


#define RCC_HSI_SYSCLK             (u32)0x000000000
#define RCC_HSE_SYSCLK             (u32)0x000000003
#define RCC_PLL_SYSCLK             (u32)0x000000008

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
#define RCC_PLLP_2_MASK            0x00020000
#define RCC_PLLP_4_MASK            0x00040000
#define RCC_PLLP_6_MASK            0x00060000
#define RCC_PLLP_8_MASK            0x00080000

/* PLL M mask */
#define RCC_PLLM_2_MASK            0x00000002

/* PLL N mask */
#define RCC_PLLN_MASK              0x

/* PLL SRC mask*/

#define RCC_PLLSRC_HSE_MASK        0x00010000
#define RCC_PLLSRC_HSI_MASK        0x00000000


#define RCC_HSE_CLOCK_MAX          0x54


/*Peripheral status*/
#define ENABLE_
#define DISABLE_


/*Bus prescaler masks*/


/*Clock names*/
typedef enum{
  HSE,
  HSI,
  PLL
}RCC_tenuclock;

typedef enum{
  RCC_enuNOK,
  RCC_enuOK,
  RCC_enuWrongConfig
}Rcc_tenuErrorStatus;

typedef enum{
  APB2,
  APB1,
  AHB
}RCC_tenuBus;
Rcc_tenuErrorStatus Rcc_enuHseControl(u8 Control_value);
Rcc_tenuErrorStatus Rcc_enuHsiControl(u8 Control_value);
Rcc_tenuErrorStatus Rcc_enuPllControl(u8 Control_value);
Rcc_tenuErrorStatus Rcc_enuGetControlflag(RCC_tenuclock clock_name);
Rcc_tenuErrorStatus RCC_enuPllConfig(u32 u32M,u32 u32N,u32 u32Q,u32 u32P,u32 u32scr);
Rcc_tenuErrorStatus RCC_enuReadyCheck(RCC_tenuclock clock_name);
Rcc_tenuErrorStatus RCC_enuSelectSysClk(RCC_tenuclock clock_name);
Rcc_tenuErrorStatus Rcc_enuGetSysClk(pu32 Add_pu32ClkSrc);
Rcc_tenuErrorStatus RCC_enuControlPeripheralClk(RCC_tenuBus RCC_enuBusName, u32 Copy_u32Peripheral, u32 Copy_u32PeripheralStatus);
Rcc_tenuErrorStatus RCC_enuControlBusPrescaler(RCC_tenuBus RCC_enuBusName, u32 Copy_u32BusPrescaler);
#endif



