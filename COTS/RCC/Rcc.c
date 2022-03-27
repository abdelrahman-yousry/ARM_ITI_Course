#include "Std_types.h"
#include "Rcc.h"

typedef struct{
  volatile u32 RCC_CR;
  volatile u32 RCC_PLLCFGR;
  volatile u32 RCC_CFGR;
  volatile u32 RCC_CIR;
  volatile u32 RCC_AHB1RSTR;
  volatile u32 RCC_AHB2RSTR;
  volatile u32 Reserved1[2];
  volatile u32 RCC_APB1RSTR;
  volatile u32 RCC_APB2RSTR;
  volatile u32 Reserved2[2];
  volatile u32 RCC_AHB1ENR;
  volatile u32 RCC_AHB2ENR;
  volatile u32 Reserved3[2];
  volatile u32 RCC_APB1ENR;
  volatile u32 RCC_APB2ENR;
  volatile u32 Reserved4[2];
  volatile u32 RCC_AHB1LPENR;
  volatile u32 RCC_AHB2LPENR;
  volatile u32 Reserved5[2];
  volatile u32 RCC_APB1LPENR;
  volatile u32 RCC_APB2LPENR;
  volatile u32 Reserved6[2];
  volatile u32 RCC_BDCR;
  volatile u32 RCC_CSR;
  volatile u32 Reserved7[2];
  volatile u32 RCC_SSCGR;
  volatile u32 RCC_PLLI2SCFGR;
  volatile u32 Reserved8;
  volatile u32 RCC_DCKCFGR;
}Rcc_t;

#define RCC_32_BASE_ADDRESS   (0x40023800)

Rcc_t *const RCC = (Rcc_t *const) RCC_32_BASE_ADDRESS;

Rcc_tenuErrorStatus Rcc_enuHseControl(u8 Control_value)
{
  Rcc_tenuErrorStatus Loc_enuReturnStatus = RCC_enuNOK;
  if (Control_value==1)
  {
    u32 timeout=50;
    RCC->RCC_CR|=RCC_u32_HSE_ON;
    while(timeout&&!(RCC->RCC_CR&RCC_u32HSI_READY))
    {
      timeout--;
    }
    if(RCC->RCC_CR &(RCC_u32HSI_READY))
    {
      Loc_enuReturnStatus = RCC_enuOK;
    }
  }
  else if(Control_value==0)
  {
    u32 ClkSrc;
    Rcc_enuGetSysClk(&ClkSrc);
    if (ClkSrc==RCC_HSE_SYSCLK)
    {
      Loc_enuReturnStatus = RCC_enuNOK;
    }
    else
    {
      RCC->RCC_CR&=~RCC_u32_HSE_OFF;
      Loc_enuReturnStatus = RCC_enuOK;
    }
  }
  else{
    return Loc_enuReturnStatus;
  }
  return Loc_enuReturnStatus;
}


Rcc_tenuErrorStatus Rcc_enuHsiControl(u8 Control_value)
{
	  Rcc_tenuErrorStatus Loc_enuReturnStatus = RCC_enuNOK;
  if (Control_value==1)
  {
    RCC->RCC_CR|=RCC_u32_HSI_ON;
    if(RCC_enuReadyCheck(HSI))
    {
      Loc_enuReturnStatus = RCC_enuOK;
    }
    else{
      //#warning the HSI cant be ready
    }
  }
  else if(Control_value==0)
  {
    u32 ClkSrc;
    Rcc_enuGetSysClk(&ClkSrc);
    if (ClkSrc==RCC_HSI_SYSCLK)
    {
      Loc_enuReturnStatus = RCC_enuNOK;
    }
    else
    {
      RCC->RCC_CR&=~RCC_u32_HSI_OFF;
      Loc_enuReturnStatus = RCC_enuOK;
    }
  }
  else{
    //#warning the HSI cant be ready
  }
  return Loc_enuReturnStatus;
}
Rcc_tenuErrorStatus Rcc_enuPllControl(u8 Control_value)
{
	  Rcc_tenuErrorStatus Loc_enuReturnStatus = RCC_enuNOK;
  if (Control_value==1)
  {
    RCC->RCC_CR|=RCC_u32_PLL_ON ;
    if(RCC_enuReadyCheck(PLL))
    {
      Loc_enuReturnStatus = RCC_enuOK;
    }
    else{
      //#warning the PLL cant be ready
    }
  }
  else if(Control_value==0)
  {
    u32 ClkSrc;
    Rcc_enuGetSysClk(&ClkSrc);
    if (ClkSrc==RCC_PLL_SYSCLK)
    {
      Loc_enuReturnStatus = RCC_enuNOK;
    }
    else
    {
      RCC->RCC_CR&=~RCC_u32_PLL_OFF;
      Loc_enuReturnStatus = RCC_enuOK;
    }
  }
  else{
    //#warning the PLL cant be ON/OFF
  }
  return Loc_enuReturnStatus;
}


Rcc_tenuErrorStatus Rcc_enuGetControlflag(RCC_tenuclock clock_name)
{
  Rcc_tenuErrorStatus Loc_enuReturnStatus = RCC_enuNOK;
  switch (clock_name)
  {
    case HSI:
      if (((RCC->RCC_CR)&(RCC_HSI_CONTROL_FLAG))==RCC_u32_HSI_ON)
      {
        Loc_enuReturnStatus = RCC_enuOK;
      }
      break ;
    case HSE:
      if (((RCC->RCC_CR)&(RCC_HSE_CONTROL_FLAG))==RCC_u32_HSE_ON)
      {
        Loc_enuReturnStatus = RCC_enuOK;
      }
      break ;      
    case PLL:
      if (((RCC->RCC_CR)&(RCC_PLL_CONTROL_FLAG))==RCC_u32_PLL_ON)
      {
        Loc_enuReturnStatus = RCC_enuOK;
      }
      break ;      
  }
  return Loc_enuReturnStatus ;
}




Rcc_tenuErrorStatus RCC_enuReadyCheck(RCC_tenuclock clock_name)
{
  Rcc_tenuErrorStatus Loc_enuReturnStatus = RCC_enuNOK;
  switch(clock_name)
  {
    u32 Loc_u32timeout=50;
    case HSI:
      while(Loc_u32timeout&&!(RCC->RCC_CR&RCC_u32HSI_READY))
      {
        Loc_u32timeout--;
      }
      if(RCC->RCC_CR &(RCC_u32HSI_READY))
      {
        Loc_enuReturnStatus = RCC_enuOK;
      }
      break;
    case HSE:
      while(Loc_u32timeout&&!(RCC->RCC_CR&RCC_u32HSE_READY))
      {
        Loc_u32timeout--;
      }
      if(RCC->RCC_CR &(RCC_u32HSE_READY))
      {
        Loc_enuReturnStatus = RCC_enuOK;
      }
      break;
    case PLL:
      while(Loc_u32timeout&&!(RCC->RCC_CR&RCC_u32PLL_READY))
      {
    	  Loc_u32timeout--;
      }
      if(RCC->RCC_CR &(RCC_u32PLL_READY))
      {
        Loc_enuReturnStatus = RCC_enuOK;
      } 
      break;
  }
  return Loc_enuReturnStatus;
}

Rcc_tenuErrorStatus Rcc_enuGetSysClk(pu32 Add_pu32ClkSrc)
{
  Rcc_tenuErrorStatus Loc_enuReturnStatus=RCC_enuOK ;
  if (Add_pu32ClkSrc == NULL)
  {
    Loc_enuReturnStatus=RCC_enuNOK;
  }
  else 
  {
    *Add_pu32ClkSrc= (RCC->RCC_CFGR&RCC_CFGR_SWS);
  }
  return Loc_enuReturnStatus;
}

Rcc_tenuErrorStatus RCC_enuSelectSysClk(RCC_tenuclock clock_name)
{
  Rcc_tenuErrorStatus Loc_enuReturnStatus=RCC_enuNOK ;
  u32 Loc_u32timeout=2000;
  u32 Loc_u32Temp;
  u32 Loc_u32SysClk;
  switch (clock_name)
  {
    case HSE:
      if((RCC->RCC_CFGR&(RCC_CFGR_SWS))==RCC_HSE_SYSCLK)
      {
        Loc_enuReturnStatus = RCC_enuWrongConfig;
      }
      else if(Rcc_enuGetControlflag(HSE))
      {
        Loc_u32Temp=RCC->RCC_CFGR;
        Loc_u32Temp &=~ RCC_SW_CLEAR_MASK;
        Loc_u32Temp |= RCC_HSE_SYSCLK;
        RCC->RCC_CFGR = Loc_u32Temp;
        while(Loc_u32timeout&&(Loc_u32SysClk==RCC_HSE_SYSCLK))
        {
          Loc_u32timeout--;
        }
        if(Loc_u32SysClk==RCC_HSE_SYSCLK)
        {
          Loc_enuReturnStatus = RCC_enuOK;
        }
      }
    break;
    case HSI:
      if((RCC->RCC_CFGR&(RCC_CFGR_SWS))==RCC_HSI_SYSCLK)
      {
        Loc_enuReturnStatus = RCC_enuWrongConfig;
      }
      else if(Rcc_enuGetControlflag(HSI))
      {
        Loc_u32Temp=RCC->RCC_CFGR;
        Loc_u32Temp &=~ RCC_SW_CLEAR_MASK;
        Loc_u32Temp |= RCC_HSI_SYSCLK;
        RCC->RCC_CFGR = Loc_u32Temp;
        Rcc_enuGetSysClk(&Loc_u32SysClk);
        while(Loc_u32timeout&&(Loc_u32SysClk==RCC_HSI_SYSCLK))
        {
          Loc_u32timeout--;
        }
        if(Loc_u32SysClk==RCC_HSI_SYSCLK)
        {
          Loc_enuReturnStatus = RCC_enuOK;
        }
      }
    break;
    case PLL:
      if((RCC->RCC_CFGR&(RCC_CFGR_SWS))==RCC_PLL_SYSCLK)
      {
        Loc_enuReturnStatus = RCC_enuWrongConfig;
      }
      else if(Rcc_enuGetControlflag(PLL))
      {
        Loc_u32Temp=RCC->RCC_CFGR;
        Loc_u32Temp &=~ RCC_SW_CLEAR_MASK;
        Loc_u32Temp |= RCC_PLL_SYSCLK;
        RCC->RCC_CFGR = Loc_u32Temp;
        while(Loc_u32timeout&&(Loc_u32SysClk==RCC_PLL_SYSCLK))
        {
          Loc_u32timeout--;
        }
        if(Loc_u32SysClk==RCC_PLL_SYSCLK)
        {
          Loc_enuReturnStatus = RCC_enuOK;
        }
      }
    break;    
  }
return Loc_enuReturnStatus;
}

Rcc_tenuErrorStatus RCC_enuPllConfig(u32 u32M,u32 u32N,u32 u32Q,u32 u32P,u32 u32scr)
{
  Rcc_tenuErrorStatus Loc_enuReturnStatus=RCC_enuOK;
  if(((u32scr>RCC_HSE_CLOCK_MAX))||((u32M>63&&u32M<2)||(u32N>432&&u32N<2))||(u32P>8&&u32P<2)&&(u32Q<2&&u32Q>15))
  {
    Loc_enuReturnStatus=RCC_enuNOK;
  }
  else if(Rcc_enuGetControlflag(PLL))
  {
    Loc_enuReturnStatus=RCC_enuNOK;
  }
  else
  {
      RCC->RCC_PLLCFGR &=~ (u32scr|u32M|u32N|u32P|u32Q);
      RCC->RCC_PLLCFGR |= (u32scr|u32M|u32N|u32P|u32Q);     
  }
  return Loc_enuReturnStatus;
}

Rcc_tenuErrorStatus RCC_enuControlBusPrescaler(RCC_tenuBus RCC_enuBusName, u32 Copy_u32BusPrescaler)
{
  Rcc_tenuErrorStatus Loc_enuReturnStatus=RCC_enuOK;
  
  if(RCC_enuBusName>2)
  {
    Loc_enuReturnStatus=RCC_enuNOK;
  }
  else
  {
  switch(RCC_enuBusName)
  {
    case APB2:
      RCC->RCC_CFGR &=~(Copy_u32BusPrescaler);
      RCC->RCC_CFGR |=(Copy_u32BusPrescaler);
    break;
    case APB1:
      RCC->RCC_CFGR &=~(Copy_u32BusPrescaler);
      RCC->RCC_CFGR |=(Copy_u32BusPrescaler);
    
    break;
    case AHB:
      RCC->RCC_CFGR &=~(Copy_u32BusPrescaler);
      RCC->RCC_CFGR |=(Copy_u32BusPrescaler);
    
    break;
  }
  }
  return Loc_enuReturnStatus;
}

Rcc_tenuErrorStatus RCC_enuControlPeripheralClk(RCC_tenuBus RCC_enuBusName, u32 Copy_u32Peripheral, u32 Copy_u32PeripheralStatus)
{
    Rcc_tenuErrorStatus Loc_enuReturnStatus=RCC_enuOK;
    return Loc_enuReturnStatus;
}
