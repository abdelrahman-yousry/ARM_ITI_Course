/*
 * Sched.c
 *
 *  Created on: Apr 15, 2022
 *      Author: Abdelrahman Yousry
 */
#ifndef SCHED_C_
#define SCHED_C_
#include "Std_types.h"
#include "Systick.h"
#include "sched.h"
#include "Sched_cfg.h"

/*this will be list of pointers to carry the address of the struct which will be sent by the user */
static Sched_tstrRunnable const* RunnableList[MAX_NO_OF_RUNNABLES];
/**
 * Two steps needed to make sched
 * 1-create list of runnable
 * 2-call each runnable in its time
 **/
static void Sched(void);

void Sched_vidInit(void)
{
	/*systick load register loaded with the appropriate value to make interrupt every TICK_TIME*/
	Systick_enuInit(TICK_TIME);
	/*it will take the address of cbf .. in this case we will send the address of sched fn*/
	Systick_vidRegcbf(Sched);
}

/*this function will be called in the handler of the systick which will occur every TICK_TIME */
static void Sched(void)
{
	static u16 TimeStamp=0;
	u16 idx;
	for(idx = 0; idx<MAX_NO_OF_RUNNABLES ; idx++)
	{
		if((TimeStamp%RunnableList[idx]->CyclicTimeMs)==0)
		{
			(RunnableList[idx]->cbf)();
		}
	}

	TimeStamp+=TICK_TIME ; // time stamp by milli-sec
}
/**
 * Runnable is ptr to struct which will sent by the user
 * priority --> it means the location of the runnable in the array **/
Sched_tenuErrorStatus Sched_enuRegisterCbf(Sched_tstrRunnable* Runnable, u16 copy_u16Priority)
{
	Sched_tenuErrorStatus Loc_enuErrorStatus =Sched_enuOk ;
	if(Runnable == NULL)
	{
		Loc_enuErrorStatus =Sched_enuNullPointer;
	}
	//this for ensuring that it will not have two runnables with the same priority
	if((RunnableList[copy_u16Priority]== NULL) && (copy_u16Priority<=MAX_NO_OF_RUNNABLES))
	{
		//buffer the address of the struct sent by the user in the array (runnable list)
		RunnableList[copy_u16Priority] = Runnable;
	}
	else
	{
		Loc_enuErrorStatus = Sched_enuNullPointer;
	}
	return Loc_enuErrorStatus;
}


void Sched_vidStart(void)
{
	Systickv_vidStart();
	while(1);
}

#endif /* SCHED_C_ */
