/*
 * Lcd_prv.h
 *
 *  Created on: Apr 17, 2022
 *      Author: U3
 */

#ifndef LCD_PRV_H_
#define LCD_PRV_H_

#define TWO_LINES_5x7          0x38
#define LCD_CURSOR_BLINK       0x0f
#define LCD_CURSOR_OFF 	       0x0c
#define LCD_CLR_DISPLAY        0x01
#define LCD_DISPLAYCONTROL     0b00001100
#define FIRST_ROW              0x80
#define SECOND_ROW             0xc0
#define LCD_MAX_CHAR_IN_LINE   16
#define LCD_MODE_SET		   0b00000110




#endif /* LCD_PRV_H_ */
