/*
 * Hswitch.h
 *
 *  Created on: Apr 11, 2022
 *      Author: Abdelrahman Yousry
 */

#ifndef SWITCH_H_
#define SWITCH_H_
#include "Switch_cfg.h"

typedef enum
{
	Switch_enuNok,
	Switch_enuOk,
	Switch_enuInvalidPort,
    Switch_enuInvalidPin,
    Switch_enuInvalidPupdConfig

}Switch_enuErrorStatus_t;


/*this struct is to describe the output device*/
typedef struct
{
    void* port;
    u8 pin;
    u8 pupd;
}SwitchCfg_t;

/**/
#define SWITCH_PU			0
#define SWITCH_PD			1
#define SWITCH_FLOAT		2



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
Switch_enuErrorStatus_t Switch_enuInit(void);
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
Switch_enuErrorStatus_t Switch_enuGetState(u16 copy_u16SwitchNum,pu8 copy_pu8Result);





#endif /* SWITCH_H_ */
