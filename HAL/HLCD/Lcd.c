/*
 * Lcd.c
 *
 *  Created on: Apr 17, 2022
 *      Author: U3
 */
#include "Std_types.h"
#include "Bit_utils.h"
#include "Gpio.h"
#include "Lcd.h"
#include "Lcd_prv.h"
#include "Sched.h"
#include "Rcc.h"

/******************************ENUMS******************************/

typedef enum {
	Lcd_enuPaused,
	Lcd_enuStart,
	Lcd_enuFunctionSet,
	Lcd_enuDisplayCtrl,
	Lcd_enuDisplayClr,
	Lcd_enuModeSet,
	Lcd_enuDone

} Lcd_tenuInitState;

typedef enum {
	Lcd_enuNoReq,
	Lcd_enuWrite,
	Lcd_enuClear
} Lcd_tenuRequestState;


typedef enum{
	WriteState,
	ClearEnable,
	WriteDone
}Lcd_tenuSendCommand;

typedef enum {
	NotBusy,
	SendCommand,
	WriteData,
	ClearDisplay

} Lcd_tenuState;


typedef enum
{
	SetPosXY,
	WriteString,
	Done
}Lcd_tenuWritingSequence;



/**********************Declaring global vars**********************/
static Lcd_tenuInitState InitProcess=Lcd_enuPaused ;
extern Lcd_strCfg Lcd_strPinsCfg[11];
static Lcd_tenuSendCommand WriteCommandStatus=WriteState ;
static Lcd_tenuSendCommand WriteDataStatus=WriteState ;
static Lcd_tenuState Lcd_State = NotBusy ;
static u8 UserCommand ;
static u8 PositionX;
static u8 PositionY;
static u8 *Buffer;


/*****************************************************************/



void Lcd_vidSendCommandProcess(u8 Command)
{
	if(WriteCommandStatus==WriteDone)
	{
		WriteCommandStatus = WriteState;
	}
	switch (WriteCommandStatus)
	{
	case WriteState:
		/*********************************************ctrl pins********************************************************/
		Gpio_enuSetPinValue(Lcd_strPinsCfg[LCD_u8PIN_RS].LcdPort,Lcd_strPinsCfg[LCD_u8PIN_RS].LcdPin,GPIO_u8PIN_LOW);
		Gpio_enuSetPinValue(Lcd_strPinsCfg[LCD_u8PIN_RW].LcdPort,Lcd_strPinsCfg[LCD_u8PIN_RW].LcdPin,GPIO_u8PIN_LOW);
		Gpio_enuSetPinValue(Lcd_strPinsCfg[LCD_u8PIN_EN].LcdPort,Lcd_strPinsCfg[LCD_u8PIN_EN].LcdPin,GPIO_u8PIN_HIGH);

		/************************************************Data**********************************************************/
		Gpio_enuSetPinValue(Lcd_strPinsCfg[LCD_u8PIN_D0].LcdPort,Lcd_strPinsCfg[LCD_u8PIN_D0].LcdPin,GET_BIT(Command,0));
		Gpio_enuSetPinValue(Lcd_strPinsCfg[LCD_u8PIN_D1].LcdPort,Lcd_strPinsCfg[LCD_u8PIN_D1].LcdPin,GET_BIT(Command,1));
		Gpio_enuSetPinValue(Lcd_strPinsCfg[LCD_u8PIN_D2].LcdPort,Lcd_strPinsCfg[LCD_u8PIN_D2].LcdPin,GET_BIT(Command,2));
		Gpio_enuSetPinValue(Lcd_strPinsCfg[LCD_u8PIN_D3].LcdPort,Lcd_strPinsCfg[LCD_u8PIN_D3].LcdPin,GET_BIT(Command,3));
		Gpio_enuSetPinValue(Lcd_strPinsCfg[LCD_u8PIN_D4].LcdPort,Lcd_strPinsCfg[LCD_u8PIN_D4].LcdPin,GET_BIT(Command,4));
		Gpio_enuSetPinValue(Lcd_strPinsCfg[LCD_u8PIN_D5].LcdPort,Lcd_strPinsCfg[LCD_u8PIN_D5].LcdPin,GET_BIT(Command,5));
		Gpio_enuSetPinValue(Lcd_strPinsCfg[LCD_u8PIN_D6].LcdPort,Lcd_strPinsCfg[LCD_u8PIN_D6].LcdPin,GET_BIT(Command,6));
		Gpio_enuSetPinValue(Lcd_strPinsCfg[LCD_u8PIN_D7].LcdPort,Lcd_strPinsCfg[LCD_u8PIN_D7].LcdPin,GET_BIT(Command,7));
		WriteCommandStatus++;
		break ;
	case ClearEnable:
		// EN pin low
		Gpio_enuSetPinValue(Lcd_strPinsCfg[LCD_u8PIN_EN].LcdPort,Lcd_strPinsCfg[LCD_u8PIN_EN].LcdPin,GPIO_u8PIN_LOW);
		WriteCommandStatus=WriteDone;
		Lcd_State = NotBusy;
		break ;
	}
}


void Lcd_vidWriteDataProcess(u8 Command)
{
	if(WriteDataStatus==WriteDone)
	{
		WriteDataStatus = WriteState;
	}
	switch (WriteDataStatus)
	{
	case WriteState:
		/*********************************************ctrl pins********************************************************/
		Gpio_enuSetPinValue(Lcd_strPinsCfg[LCD_u8PIN_RS].LcdPort,Lcd_strPinsCfg[LCD_u8PIN_RS].LcdPin,GPIO_u8PIN_HIGH);
		Gpio_enuSetPinValue(Lcd_strPinsCfg[LCD_u8PIN_RW].LcdPort,Lcd_strPinsCfg[LCD_u8PIN_RW].LcdPin,GPIO_u8PIN_LOW);
		Gpio_enuSetPinValue(Lcd_strPinsCfg[LCD_u8PIN_EN].LcdPort,Lcd_strPinsCfg[LCD_u8PIN_EN].LcdPin,GPIO_u8PIN_HIGH);

		/************************************************Data**********************************************************/

		Gpio_enuSetPinValue(Lcd_strPinsCfg[LCD_u8PIN_D0].LcdPort,Lcd_strPinsCfg[LCD_u8PIN_D0].LcdPin,GET_BIT(Command,0));
		Gpio_enuSetPinValue(Lcd_strPinsCfg[LCD_u8PIN_D1].LcdPort,Lcd_strPinsCfg[LCD_u8PIN_D1].LcdPin,GET_BIT(Command,1));
		Gpio_enuSetPinValue(Lcd_strPinsCfg[LCD_u8PIN_D2].LcdPort,Lcd_strPinsCfg[LCD_u8PIN_D2].LcdPin,GET_BIT(Command,2));
		Gpio_enuSetPinValue(Lcd_strPinsCfg[LCD_u8PIN_D3].LcdPort,Lcd_strPinsCfg[LCD_u8PIN_D3].LcdPin,GET_BIT(Command,3));
		Gpio_enuSetPinValue(Lcd_strPinsCfg[LCD_u8PIN_D4].LcdPort,Lcd_strPinsCfg[LCD_u8PIN_D4].LcdPin,GET_BIT(Command,4));
		Gpio_enuSetPinValue(Lcd_strPinsCfg[LCD_u8PIN_D5].LcdPort,Lcd_strPinsCfg[LCD_u8PIN_D5].LcdPin,GET_BIT(Command,5));
		Gpio_enuSetPinValue(Lcd_strPinsCfg[LCD_u8PIN_D6].LcdPort,Lcd_strPinsCfg[LCD_u8PIN_D6].LcdPin,GET_BIT(Command,6));
		Gpio_enuSetPinValue(Lcd_strPinsCfg[LCD_u8PIN_D7].LcdPort,Lcd_strPinsCfg[LCD_u8PIN_D7].LcdPin,GET_BIT(Command,7));
		WriteDataStatus++;
		break ;
	case ClearEnable:
		// EN pin low
		Gpio_enuSetPinValue(Lcd_strPinsCfg[LCD_u8PIN_EN].LcdPort,Lcd_strPinsCfg[LCD_u8PIN_EN].LcdPin,GPIO_u8PIN_LOW);
		WriteDataStatus=WriteDone;
		break ;
	}
}


void Lcd_vidInit(void)
{
	GpioPinCfg_t Gpio_CfgInit ;
	u8 iterator = 0;
	switch ((u32)(Lcd_strPinsCfg[iterator].LcdPort))
	{
	case (u32)GPIO_A:
			Rcc_enuEnablePeripheralClk(RCC_u8BUS_AHB1,RCC_u32AHB1_GPIOA);
	break ;
	case (u32)GPIO_B:
			Rcc_enuEnablePeripheralClk(RCC_u8BUS_AHB1,RCC_u32AHB1_GPIOB);
	break;
	case (u32)GPIO_C:
			Rcc_enuEnablePeripheralClk(RCC_u8BUS_AHB1,RCC_u32AHB1_GPIOC);
	break;
	}
	Gpio_CfgInit.mode = GPIO_u8MODE_OUTPUT_PP;
	Gpio_CfgInit.speed = GPIO_u8SPEED_HIGH;
	for (iterator = 0 ;iterator<11; iterator ++)
	{
		Gpio_CfgInit.port = Lcd_strPinsCfg[iterator].LcdPort;
		Gpio_CfgInit.pin = Lcd_strPinsCfg[iterator].LcdPin;
		Gpio_enuInit(&Gpio_CfgInit);
	}

	InitProcess =Lcd_enuStart;
}
void Lcd_vidWriteString(u8* string , u8 posX , u8 posY)
{
	if(Lcd_State == NotBusy )
	{
		PositionX= posX;
		PositionY= posY;
		Buffer = string;
		Lcd_State = WriteData;
	}
}





/*****************************************************************************************************/

void Lcd_vidSendCommand(u8 command)
{
	Lcd_State = SendCommand ;
	UserCommand = command ;
}

void Lcd_vidWriteStringProcess(void)
{
	Lcd_tenuWritingSequence writeSequence = SetPosXY;
	switch(writeSequence)
	{
	static u8 counter=0;
	case SetPosXY:
		switch(PositionX)
		{
		case Row_0 :

			if (PositionY>=0 && PositionY < LCD_MAX_CHAR_IN_LINE)
			{
				Lcd_vidSendCommand(FIRST_ROW + PositionY);
			}
			break ;

		case Row_1 :
			if (PositionY>=0 && PositionY < LCD_MAX_CHAR_IN_LINE)
			{
				Lcd_vidSendCommand(SECOND_ROW + PositionY);
			}
			break ;
		}
		writeSequence ++;
		break;
		case WriteString:
			if(Buffer[counter]=='\0')
			{
				writeSequence = Done;
				Lcd_State == NotBusy;
			}
			else
			{
				Lcd_vidWriteDataProcess(Buffer[counter]);
				counter ++ ;
			}
			break;
	}
}



void Lcd_vidSchedTask(void)
{
	static u8 counter =0;
	if (InitProcess != Lcd_enuDone && InitProcess!=Lcd_enuPaused)
	{

		switch (InitProcess)
		{
		case Lcd_enuStart:
			counter ++;
			if (counter == 30)
			{
				InitProcess = Lcd_enuFunctionSet;
			}
			break;
		case Lcd_enuFunctionSet:
			Lcd_vidSendCommandProcess(TWO_LINES_5x7);
			break ;
		case Lcd_enuDisplayCtrl:
			Lcd_vidSendCommandProcess(LCD_DISPLAYCONTROL);
			break ;
		case Lcd_enuDisplayClr:
			Lcd_vidSendCommandProcess(LCD_CLR_DISPLAY);
			break;
		case Lcd_enuModeSet:
			Lcd_vidSendCommandProcess(LCD_MODE_SET);
			break;
		case Lcd_enuDone:

			break ;
		}
		if(WriteCommandStatus==WriteDone )
		{
			InitProcess++;
		}
	}
	else
	{
		switch (Lcd_State)

		{
		case WriteData:
			Lcd_vidWriteStringProcess();
			break;
		case SendCommand:
			Lcd_vidSendCommandProcess(UserCommand);
			break;
		}
	}
}

