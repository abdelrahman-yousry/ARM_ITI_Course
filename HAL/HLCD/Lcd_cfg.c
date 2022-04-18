/*
 * Lcd_cfg.c
 *
 *  Created on: Apr 17, 2022
 *      Author: Abdelrahman Yousry
 */
#include "Std_types.h"
#include "Gpio.h"
#include "Lcd.h"


Lcd_strCfg Lcd_strPinsCfg[11]=
{
		[LCD_u8PIN_RS]={
				.LcdPort = GPIO_B,
				.LcdPin = GPIO_u8PIN_9
		},
		[LCD_u8PIN_RW]={
				.LcdPort = GPIO_B,
				.LcdPin = GPIO_u8PIN_10
		},
		[LCD_u8PIN_EN]={
				.LcdPort = GPIO_B,
				.LcdPin = GPIO_u8PIN_11
		},
		[LCD_u8PIN_D0]={
				.LcdPort = GPIO_A,
				.LcdPin = GPIO_u8PIN_0
		},
		[LCD_u8PIN_D1]={
				.LcdPort = GPIO_A,
				.LcdPin = GPIO_u8PIN_1
		},
		[LCD_u8PIN_D2]={
				.LcdPort = GPIO_A,
				.LcdPin = GPIO_u8PIN_2
		},
		[LCD_u8PIN_D3]={
				.LcdPort = GPIO_A,
				.LcdPin = GPIO_u8PIN_3
		},
		[LCD_u8PIN_D4]={
				.LcdPort = GPIO_A,
				.LcdPin = GPIO_u8PIN_4
		},
		[LCD_u8PIN_D5]={
				.LcdPort = GPIO_A,
				.LcdPin = GPIO_u8PIN_5
		},
		[LCD_u8PIN_D6]={
				.LcdPort = GPIO_A,
				.LcdPin = GPIO_u8PIN_6
		},
		[LCD_u8PIN_D7]={
				.LcdPort = GPIO_A,
				.LcdPin = GPIO_u8PIN_7
		}

};


