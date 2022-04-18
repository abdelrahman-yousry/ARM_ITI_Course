/*
 * Lcd.h
 *
 *  Created on: Apr 17, 2022
 *      Author: U3
 */

#ifndef LCD_H_
#define LCD_H_



typedef struct
{
	void * LcdPort;
	u8 LcdPin;
}Lcd_strCfg;

#define LCD_u8PIN_D0	0
#define LCD_u8PIN_D1	1
#define LCD_u8PIN_D2	2
#define LCD_u8PIN_D3	3
#define LCD_u8PIN_D4	4
#define LCD_u8PIN_D5	5
#define LCD_u8PIN_D6	6
#define LCD_u8PIN_D7	7
#define LCD_u8PIN_RS	8
#define LCD_u8PIN_RW	9
#define LCD_u8PIN_EN	10


#define Row_0 0
#define Row_1 1


/***************************PROTOTYPES****************************/
void Lcd_vidSchedTask(void);
void Lcd_vidInit(void);
void Lcd_vidWriteString(u8* string , u8 posX , u8 posY);
void Lcd_vidWriteStringProcess(void);
void Lcd_vidSendCommand (u8 command);
void Lcd_vidSendCommandProcess(u8 Command);




#endif /* LCD_H_ */
