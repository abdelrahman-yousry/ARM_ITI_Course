
#include <stdio.h>
#include <stdlib.h>
#include "diag/Trace.h"
#include "Std_types.h"
#include "Rcc.h"

int main(void)
{
//	Rcc_enuHseControl(RCC_u64HSE_ON);
//	Rcc_enuHseControl(RCC_u64HSE_OFF);
//	Rcc_enuHsiControl(RCC_u64HSI_ON);
//	Rcc_enuHsiControl(RCC_u64HSI_OFF);
//	Rcc_enuPllControl(RCC_u64PLL_ON);
//	Rcc_enuPllControl(RCC_u64PLL_OFF);
//	Rcc_enuSelectSysClk(RCC_u64SYSCLK_HSE);
//	Rcc_enuSelectBusPrescaler(RCC_u32APB1_DIV_BY_4);
	Rcc_enuEnablePeripheralClk(RCC_u8BUS_AHB1,RCC_u32AHB1_GPIOA);
	while(1)
	{

	}
}

//static int varX=10;
//static int varY;
//static const int varZ = 100;
//register int reg asm("r7");
//static void logZ(int *var);
//int
//main(int argc, char* argv[])
//{
//	static const int varA =0;
//	register double varf
//	(void)argc;
//	(void)argv;
//  while (1)
//    {
//       // Add your code here.
//	  varX++;
//	  varY++;
//	  if (varY==100||varX==100)
//	  {
//		  logZ(&varZ);
//	  }
//
//    }
//
//}
//
//static void logZ(int *var)
//  {
//	trace_printf("%x\n",*var);
//  }
