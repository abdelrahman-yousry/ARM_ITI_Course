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
	Switch_enuNullPointer,
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
 * Description: 		this function to set init array of Switches defined by the user
 *
 * input args: 			void

 * Return type: 		Switch_enuErrorStatus_t for checking and make validation on the input arg
 * 						if it correct it will return Switch_enuOk
 * 						else will return one of these options
 * 							Switch_enuNok,
							Switch_enuOk,
							Switch_enuInvalidPort,
							Switch_enuInvalidPin,
							Switch_enuInvalidPupdConfig

 * */
Switch_enuErrorStatus_t Switch_enuInit(void);
/****************************************************************
 * Description: 		this function to set state for specific Switch
 *
 * input args: 			1- u16 copy_u16SwitchNum ---> Switch number
 * 						2- pu8 copy_pu8Result ---> pointer for getting the result
 *

 * Return type: 		Switch_enuErrorStatus_t for checking and make validation on the input arg
 * 						if it correct it will return Switch_enuOk
 * 						else will return one of these options
 * 							Switch_enuNok,
 *							Switch_enuOk,
 *							Switch_enuInvalidPort,
 *	 						Switch_enuInvalidPin,
 *							Switch_enuInvalidPupdConfig
 *
 * */
Switch_enuErrorStatus_t Switch_enuGetState(u16 copy_u16SwitchNum,pu8 copy_pu8Result);

extern void Switch_Task(void);



#endif /* SWITCH_H_ */
