
/*Author: Abdelrahman Yousry*/
// ----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "diag/Trace.h"

//first trial to prove that we can use the var created in the linker
//extern uint32_t _ebss;
//extern uint32_t _sbss;

// this case is that i reserve memory and make section in it
extern uint32_t __mysec_start;
extern uint32_t __mysec_end;

__attribute__ ((section(".mysec"),used))
uint32_t varx ;
int
main(int argc, char* argv[])
{
	varx = 100;// alias to the first location in the mysec section in the memory mymem
	__mysec_start = 50 ;// alias to the first location in the
	(void) argc;
	(void) argv;

	//	trace_printf("Hello there %d",&_ebss-&_sbss);
	trace_printf("Hello there %d",&__mysec_end-&__mysec_start);
	while (1)
	{
		varx++;
		if (varx==100)
		{
			varx = 0;
		}
	}
}


// ----------------------------------------------------------------------------
