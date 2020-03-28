//**************************************
//* File:			display.c
//*	Date:			10/11/12
//*	Creator:		PhanTrongHieu
//* Last modify:	14/01/13
//* Description:	This file is in CAN communication lift control system project.
//*					The functions in this file representated to display matrix led of ThienNam 
//*					elevator indicator. The hardware was designed by LeDuy(leduy@tne.vn).
//*					The hardware was edited by TrongHieu.
//*					This file is copywritghted by ThienNam Join Stock Company (www.tne.vn).
//* Version:		V1.0. 
//*************************************
#include <stdint.h>
#include <stdbool.h>

/* Standard includes. */
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"


#include "inc/global.h"
#include "inc/can_shc.h"
#include "inc/function.h"
#include "inc/display.h"

#define SAMPLE			4

unsigned long ulSample[SAMPLE];
unsigned char ucSampleIndex;

unsigned long ulInport;
unsigned long ulPreInp;

unsigned char ucLTUOut;
unsigned char ucLTDOut;
unsigned char ucBTUIn;
unsigned char ucBTDIn;
unsigned char ucBTUSend;
unsigned char ucBTDSend;
unsigned char ucLTURcv;
unsigned char ucLTDRcv;

extern unsigned long ulDataRxLTU;
extern unsigned long ulDataRxLTD;
extern unsigned long ulDataTxLTU;
extern unsigned long ulDataTxLTD;
extern unsigned long ulDataClearBTU;
extern unsigned long ulDataClearBTD;
extern unsigned char ucCAN0TxFlag;

unsigned long ulTimerBTUJam;
unsigned long ulTimerBTDJam;

unsigned char ucOutX1;

unsigned char ucLTU;
unsigned char ucLTD;
unsigned char ucX1;
unsigned char ucIn1;
unsigned char ucIn2;
unsigned char ucIn3;
unsigned char ucIn4;
unsigned char ucIn5;
unsigned char ucIn6;
unsigned char ucIn7;
unsigned char ucIn8;
unsigned char ucPreDisplay;

unsigned long ulTimerIn1;
unsigned long ulTimerIn2;
unsigned long ulTimerIn3;
unsigned long ulTimerIn4;
unsigned long ulTimerIn5;
unsigned long ulTimerIn6;
unsigned long ulTimerIn7;
unsigned long ulTimerIn8;
unsigned long ulTimerInport;
unsigned long ulTimerPWM;

unsigned long ulTimerCAN0Tx;
unsigned long ulTimerCAN1Tx;
unsigned long ulTimerX1;
unsigned long ulPWMSet;

extern volatile unsigned char ucCANBusoff;
extern volatile unsigned char ucPos;
extern xStatusHandler xData;

extern unsigned long ulNumberDelay;
extern unsigned long ulArrowDelay;
extern unsigned long ulStringDelay;

#define DEMO_LEDCODE	(69)

typedef struct
{
	unsigned char ucLedCode;
	unsigned char ucStatus;
	unsigned int uiDelay;
} xDemo;

	/* Broadcast Frame: 8byte
		BYTE0:	NumOfFloor
		BYTE1:	Display
		BYTE2:	Status 
				Bit0: Up
				Bit1: Down
				Bit2: Run
				
				Bit3: Earthquake
				Bit4: Fireman
				Bit5: Overload
				Bit6: Busy
				Bit7: Big digits

		BYTE3:	Current floor
		BYTE4:	Unused
		BYTE5:	Unused
		BYTE6:	Unused
		BYTE7:	Unused
	*/
	
const xDemo xDemoData[DEMO_LEDCODE]=
{
	//Led7Seg,	Status	Delay,
	{0x49,		0,	3000},	//0-Stop
	{0x64,		0,	3000},	//1-Inspection
	{0x76,		0,	3000},	//2-Reset
	{0x77,		0,	5000},	//3-Rescue
	{0x79,		0,	5000},	//4-Error
	{0x7C,		0,	3000},	//5-B
	{0x38,		0,	3000},	//6-L
	{0x37,		0,	4000},	//7-M
	{0x0E,		0,	1500},	//8-B1
	{0x0F,		0,	1500},	//9-B2
	{0x10,		0,	1500},	//10-M1
	{0x11,		0,	1500},	//11-M2
	{0x12,		0,	1500},	//12-H1
	{0x13,		0,	1500},	//13-H2
	{0x14,		0,	1500},	//14-B3
	{0x15,		0,	1500},	//15-B4
	{0x16,		0,	1500},	//16-B5
	{0x17,		0,	1500},	//17-3A
	{0x18,		0,	1500},	//18-12A
	{0x19,		0,	1500},	//19-14A
	{0x1A,		0,	1500},	//20-E0
	{0x1B,		0,	1500},	//21-E1
	{0x1C,		0,	1500},	//22-E2
	{0x1D,		0,	1500},	//23-E3
	{0x1E,		0,	1500},	//24-E4
	{0x1F,		0,	1500},	//25-E5
	{0x20,		0,	1500},	//26-E6
	{0x21,		0,	1500},	//27-E7
	{0x3F,		0,	1500},	//28-G
	{0x06,		0,	1500},	//29-1
	{0x5B,		0,	1500},	//30-2
	{0x4F,		0,	1500},	//31-3
	{0x66,		0,	1500},	//32-4
	{0x6D,		0,	1500},	//33-5
	{0x7D,		0,	1500},	//34-6
	{0x07,		0,	1500},	//35-7
	{0x7F,		0,	1500},	//36-8
	{0x6F,		0,	1500},	//37-9
	{0xBF,		0,	1500},	//38-10
	{0x86,		0,	1500},	//39-11
	{0xDB,		0,	1500},	//40-12
	{0xCF,		0,	1500},	//41-13
	{0xE6,		0,	1500},	//42-14
	{0xED,		0,	1500},	//43-15
	{0xFD,		0,	1500},	//44-16
	{0x87,		0,	1500},	//45-17
	{0x88,		0,	1500},	//46-18
	{0xEF,		0,	1500},	//47-19
	{0x22,		0,	1500},	//48-20
	{0x23,		0,	1500},	//49-21
	{0x24,		0,	1500},	//50-22
	{0x25,		0,	1500},	//51-23
	{0x26,		0,	1500},	//52-24
	{0x27,		0,	1500},	//53-25
	{0x28,		0,	1500},	//54-26
	{0x29,		0,	1500},	//55-27
	{0x2A,		0,	1500},	//56-28
	{0x2B,		0,	1500},	//57-29
	{0x2C,		0,	1500},	//58-30
	{0x2D,		0,	1500},	//59-31
	{0x2E,		0,	1500},	//60-32
	{0x2F,		0,	1500},	//61-33
	{0x30,		0,	1500},	//62-34
	{0x31,		0,	1500},	//63-35
	{0x32,		0,	1500},	//64-36
	{0x33,		0,	1500},	//65-37
	{0x34,		0,	1500},	//66-38
	{0x35,		0,	1500},	//67-39
	{0x36,		0,	1500},	//68-OFF
};

unsigned char ucDemoCode=1;
unsigned int uiTimerDemo;

extern void vCAN0Send(void);
extern void vCAN1Send(void);
extern void vCANConfig(void);
extern void vDisplay(void);
extern void vScanled(void);
extern void (*pvScroll)(void);
extern void vClearDisp(void);

extern void vScrollV(void);
extern void vScrollH(void);

void vInput(void)
{
	unsigned long result, all_or=0, all_and=0;
	unsigned char i;

	// BT
	ulSample[ucSampleIndex] = (unsigned long)GPIOPinRead(GPIO_PORTD_BASE, 0xFF) << 8;
	// IN
	ulSample[ucSampleIndex] |= (unsigned long)GPIOPinRead(GPIO_PORTA_BASE, 0x54);

	ulSample[ucSampleIndex] &= 0x0000FF54;

	all_or = ulSample[0];
	all_and = all_or;
	for(i=1;i<SAMPLE;i++)
	{
		all_or |= ulSample[i];
		all_and &= ulSample[i];
	}

	result = ~ulInport;
	result &= 0x0000FF54;

	result &= all_or;
	result |= all_and;
	
	ulInport = ~result;
	ulInport &= 0x0000FF54;

	if(++ucSampleIndex>=SAMPLE) ucSampleIndex=0;
}

void vOutput(void)
{
;
}

void vPoll(void)
{
	unsigned long *pulData;
//	unsigned long tmp;

	/* Broadcast Frame: 8byte
		BYTE0:	NumOfFloor
		BYTE1:	Display
		BYTE2:	Status 
				Bit0: Up
				Bit1: Down
				Bit2: Run
				Bit3: Earthquake
				Bit4: Fireman
				Bit5: Overload
				Bit6: DO
				Bit7: Car

		BYTE3:	Current floor
	*/

	if(ucCANBusoff == 1){
		SysCtlPeripheralReset(SYSCTL_PERIPH_CAN0);
		SysCtlPeripheralReset(SYSCTL_PERIPH_CAN1);
		vCANConfig();
		ucCANBusoff = 0;
	}
	
	if(ulTimerInport == 0){
		vInput();
		if(ulInport != ulPreInp){
			// xac dinh xung canh len.
/*			tmp = ulInport ^ ulPreInp;
			tmp &= ulInport;

			if((tmp & ((1 << PIN_BTU) | (1 << PIN_BTD))) != 0){ ucCAN0TxFlag = 0;}
			else if((tmp & (1 << PIN_X1)) != 0){ ucCAN0TxFlag = 1;}
			else { ucCAN0TxFlag = 2;}
*/

			if(_isset(ulInport, PIN_X1)){ ucCAN0TxFlag = 1;}
			if(_isset(ulInport, PIN_BTU) | _isset(ulInport, PIN_BTD)){ ucCAN0TxFlag = 0;}

			ulPreInp = ulInport;
		}

		ulTimerInport = TR_INP;
	}

	// ---------------------------------------------------------------------
	// Nut nhan IN1..8
	// ---------------------------------------------------------------------
	if(_isclear(ulInport, PIN_IN1)){ ucIn1 = 1; ulTimerIn1 = TR_HOLDING_1;}
	if(ulTimerIn1 == 0){ ucIn1 = 0;}

	if(_isclear(ulInport, PIN_IN2)){ ucIn2 = 1; ulTimerIn2 = TR_HOLDING_1;}
	if(ulTimerIn2 == 0){ ucIn2 = 0;}

	if(_isclear(ulInport, PIN_IN3)){ ucIn3 = 1; ulTimerIn3 = TR_HOLDING_1;}
	if(ulTimerIn3 == 0){ ucIn3 = 0;}

	// ---------------------------------------------------------------------
	// Nut nhan X1
	// ---------------------------------------------------------------------
	if(_isset(ulInport, PIN_X1)){ ucX1 = 1; ulTimerX1 = TR_HOLDING_1;}
	if(ulTimerX1 == 0){ ucX1 = 0;}
	
	pulData = (unsigned long *)&ucCANOutX1[0];
	if(_isset(*pulData, ucPos)){ ucOutX1 = 1;} else { ucOutX1 = 0;}

	// ---------------------------------------------------------------------
	// Nut nhan btu & btd
	// ---------------------------------------------------------------------
	pulData = (unsigned long *)&ucCANOutSHC[0];
	if(_isset(*pulData, ucPos)){ ucLTURcv = 1;}

	pulData = (unsigned long *)&ucCANOutSHC[4];
	if(_isset(*pulData, ucPos)){ ucLTDRcv = 1;}

	pulData = (unsigned long *)&ucCANClearBTH[0];
	if( _isclear(*pulData, ucPos) | ( ulTimerBTUJam == 0)){ ucLTURcv = 0; ucBTUIn = 0;}

	pulData = (unsigned long *)&ucCANClearBTH[4];
	if( _isclear(*pulData, ucPos) | ( ulTimerBTDJam == 0)){ ucLTDRcv = 0; ucBTDIn = 0;}

	if( _isset(ulInport, PIN_BTU)){ ucBTUIn = 1;} else { ulTimerBTUJam = TR_JAM;}
	if( _isset(ulInport, PIN_BTD)){ ucBTDIn = 1;} else { ulTimerBTDJam = TR_JAM;}

	if((ucLTURcv == 1) | (ucBTUIn == 1)){ ucLTUOut = 1;} else { ucLTUOut = 0;}
	if((ucLTDRcv == 1) | (ucBTDIn == 1)){ ucLTDOut = 1;} else { ucLTDOut = 0;}

	if((ucLTUOut == 1) & (ulTimerBTUJam != 0)){ ucBTUSend = 1;} else { ucBTUSend= 0;}
	if((ucLTDOut == 1) & (ulTimerBTDJam != 0)){ ucBTDSend = 1;} else { ucBTDSend= 0;}

//	if(GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_0) != 0){ _clear(xData.ucStatus, BIGFONT);} else { _set(xData.ucStatus, BIGFONT);}
	//if(GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_1) != 0){ pvScroll=vScrollV;} else { pvScroll=vScrollH;}

	if((xData.ucStatus != 0) | (xData.ucLed7Seg != ucPreDisplay))
	{
		//ucPreDisplay = xData.ucLed7Seg;
		ulTimerPWM = TR_PWM;
	}

	if(ulTimerPWM == 0){ ulPWMSet = LOWPWM;} else {ulPWMSet = HIGHPWM;}
	vOutput();
}

void vSysTickTimerExpired(void)
{
	static unsigned long ulTimer1Sec;
	static unsigned long ulTimer1ms;

	if(uiTimerDemo > 0){ --uiTimerDemo;}
	if(uiTimerDemo == 0)
	{
		xData.ucLed7Seg = xDemoData[ucDemoCode].ucLedCode;
		xData.ucStatus = xDemoData[ucDemoCode].ucStatus;
		uiTimerDemo = xDemoData[ucDemoCode].uiDelay;
		if(++ucDemoCode >= 4){ ucDemoCode = 1;}
	}

	vScanled();
	if((ulTimerCAN0Tx == 0)&&(_isset(ulInport, PIN_BTD))){vCAN0Send();}
	if((ulTimerCAN1Tx == 0)&&(_isset(ulInport, PIN_BTU))){vCAN1Send();}
	if(++ulTimer1ms >= TICK_RATE_1MS)
	{
		if(ulNumberDelay>0) --ulNumberDelay;
		if(ulArrowDelay>0) --ulArrowDelay;
		if(ulStringDelay>0) --ulStringDelay;

		if(ulTimerInport > 0){ --ulTimerInport;}
		if(ulTimerX1 > 0){ --ulTimerX1;}
		if(ulTimerIn1 > 0){ --ulTimerIn1;}
		if(ulTimerIn2 > 0){ --ulTimerIn2;}
		if(ulTimerIn3 > 0){ --ulTimerIn3;}
		if(ulTimerIn4 > 0){ --ulTimerIn4;}
		if(ulTimerIn5 > 0){ --ulTimerIn5;}
		if(ulTimerIn6 > 0){ --ulTimerIn6;}
		if(ulTimerIn7 > 0){ --ulTimerIn7;}
		if(ulTimerIn8 > 0){ --ulTimerIn8;}
		ulTimer1ms = 0;
	}
	if(ulTimerCAN0Tx > 0){ --ulTimerCAN0Tx;}
	if(ulTimerCAN1Tx > 0){ --ulTimerCAN1Tx;}

	if(++ulTimer1Sec >= TICK_RATE_HZ)
	{
		if(ulTimerBTUJam > 0){ --ulTimerBTUJam;}
		if(ulTimerBTDJam > 0){ --ulTimerBTDJam;}
		if(ulTimerPWM > 0){ --ulTimerPWM;}
		ulTimer1Sec = 0;
	}
}
