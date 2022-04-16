/*
 * Led.h
 *
 *  Created on: Apr 11, 2022
 *      Author: Abdelrhman Yousry
 */

#ifndef LED_H_
#define LED_H_
#include "Led_cfg.h"

typedef enum
{
	led_enuNok,
	led_enuOk,
	led_enuInvalidPort,
    led_enuInvalidPin,
    led_enuInvalidOtype,
    led_enuInvalidState

}Led_enuErrorStatus_t;


/*this struct is to describe the output device*/
/*2na mdtloo4 #define ll pin w 2l port 34an mtdr4 25leh y include 2l file
 *bta3 gpio.h f 2l app.c f 2oltloh 2na mtdeeek file cfg.c ro7 jnak 7ot 2nta 3awz 2l pin tb2a 3la a ?
 * */
typedef struct
{
    void* port;
    u8 pin;
    u8 activeState;
    u8 otype;
}LedCfg_t;

/*Led state value should be inverse of the Led active state
 * so if they are XOR with each other it will work regardless the connection in
 * the hw outside
 * */
#define LED_STATE_OFF			1
#define LED_STATE_ON			0
/**/
#define LED_ACTIVE_STATE_HIGH	1
#define LED_ACTIVE_STATE_LOW	0
/*these macros should be with a magic number not a mask bec
 * if the mcal was changed so the reg may be changed so if i put mask it may not be fi t
 * the new reg
 *
 * also you shouldn't put the value with the macros of the GPIO otherwise you will include
 * the GPIO.h in the app.c and this violate the abstraction*/
#define LED_OTYPE_PP			0
#define LED_OTYPE_OD			1

// active state High 1
//active state Low 	 0
//Led state on  0
//Led state off 1
//					active state high		active state low
//Led state on (0) 	   1          								---xor-> 1
//Led state on (0)	             					0			---xor-> 0
//Led state off(1)     1          								---xor-> 0
//Led state off(1) 	   			  					0			---xor-> 1

//

/**/
/****************************************************************
 * Description: 		this function to set init Leds defined by the user
 *
 * input args: 			void

 * Return type: 		Led_enuErrorStatus_t for checking and make validation on the input arg
 * 						if it correct it will return Led_enuOk
 * 						else will return one of these options
 * 							led_enuNok,
							led_enuOk,
							led_enuInvalidPort,
							led_enuInvalidPin,
							led_enuInvalidOtype,
							led_enuInvalidState
 * */
extern Led_enuErrorStatus_t Led_enuInit(void);
/****************************************************************
 * Description: 		this function to set state for specific Led
 *
 * input args: 			1- u16 copy_u16ledNum ---> Led number
 * 						2- u8 copy_u8ledState ---> Led state (LED_STATE_ON/LED_STATE_OFF)
 *

 * Return type: 		Led_enuErrorStatus_t for checking and make validation on the input arg
 * 						if it correct it will return Led_enuOk
 * 						else will return one of these options
 * 							led_enuNok,
 *							led_enuOk,
 *							led_enuInvalidPort,
 *	 						led_enuInvalidPin,
 *							led_enuInvalidOtype,
 *							led_enuInvalidState
 * */
// u16 --> 2na keda b2ool dmnyn 2n 3dd la nha2i mn 2l leds
extern Led_enuErrorStatus_t Led_enuSetState(u16 copy_u16ledNum, u8 copy_u8ledState);

#endif /* LED_H_ */
