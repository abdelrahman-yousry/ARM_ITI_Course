/*
 * Sched.h
 *
 *  Created on: Apr 15, 2022
 *      Author: Abdelrahman Yousry
 */

#ifndef SCHED_H_
#define SCHED_H_

/*You should follow this sequence when using this driver
 * 1-call Sched_vidInit() func
 * 2-call
 * */


typedef enum
{
	Sched_enuOk,
	Sched_enuNullPointer
}Sched_tenuErrorStatus;

typedef struct
{
	void(*cbf)(void);
	u32 CyclicTimeMs;

}Sched_tstrRunnable;

void Sched_vidInit(void);
/****************************************************************
* Description: 	this function to init the sched by initialize the systick timer
*
* 				this function is to interface with the systick driver to initialize the
* 				systick with the desired time which will be determined by the user according
* 				to the highest common factor between the cyclic time of all runnables
*
* input args: 	Sched_tstrRunnable* Runnable / u8 copy_u8Priority
*
* Return type: 	Sched_tenuErrorStatus
* */
/****************************************************************
* Description: 	this function to register the call back function
*
* 				but in the implementation you will take the address of the struct sent by the user
* 				in pointer to the same struct created in the sched.c (array of pointer to struct)
*
* input args: 	Sched_tstrRunnable* Runnable / u8 copy_u8Priority
*
* Return type: 	Sched_tenuErrorStatus
* */
Sched_tenuErrorStatus Sched_enuRegisterCbf(Sched_tstrRunnable* Runnable, u16 copy_u16Priority);

void Sched_vidStart(void);


#endif /* SCHED_H_ */
