
#include "Std_types.h"
#include "diag/Trace.h"
#include "NVIC.h"

//typedef void
//(* const pHandler)(void);
//extern pHandler __isr_vectors[];
int
main(void)
{
	u8 result;
	volatile u8 x;
	//	Nvic_tenuIRQn enu_IRQ= WWDG_IRQn ;
	NVIC_enuEnableIRQ(NVIC_WWDG_IRQn);
	NVIC_enuDisableIRQ(0);
	NVIC_enuSetPendingIRQ(0);
	//NVIC_ClearPendingIRQ(0);
	NVIC_enuGetPendingIRQ(0,&result);
	x =NVIC_enuEncodePriority(1,2,1);
	x++;
	//	x = (sizeof(__isr_vectors))/4;
	//	trace_printf("%d",x);
	// Infinite loop
	while (1)
	{
		// Add your code here.
	}
}

