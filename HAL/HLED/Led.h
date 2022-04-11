/*
 * Led.h
 *
 *  Created on: Apr 11, 2022
 *      Author: Abdelrhman Yousry
 */

#ifndef LED_H_
#define LED_H_


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
typedef struct
{
    void* port;
    u8 pin;
    u8 activeState;
    u8 otype;
}LedCfg_t;

/**/
#define LED_STATE_OFF			1
#define LED_STATE_ON			0
/**/
#define LED_ACTIVE_STATE_HIGH	1
#define LED_ACTIVE_STATE_LOW	0
/**/
#define LED_OTYPE_PP			0
#define LED_OTYPE_OD			1



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
