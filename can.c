#include <stdint.h>
#include <stdbool.h>


#include "inc/hw_memmap.h"
#include "inc/hw_ints.h"
#include "inc/hw_can.h"

#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/can.h"

#include "inc/global.h"
#include "inc/can_shc.h"
#include "inc/function.h"
#include "inc/display.h"

#include "driverlib/pin_map.h"
#include "driverlib/rom.h"

tCANMsgObject xMsgObject0Status;
tCANMsgObject xMsgObject0InSHC;
tCANMsgObject xMsgObject0DrSHC;
tCANMsgObject xMsgObject0InX1;
tCANMsgObject xMsgObject0OutSHC;
tCANMsgObject xMsgObject0OutX1;
tCANMsgObject xMsgObject0ClearBTH;

tCANMsgObject xMsgObject1Status;
tCANMsgObject xMsgObject1InSHC;
tCANMsgObject xMsgObject1DrSHC;
tCANMsgObject xMsgObject1InX1;
tCANMsgObject xMsgObject1OutSHC;
tCANMsgObject xMsgObject1OutX1;
tCANMsgObject xMsgObject1ClearBTH;

unsigned char ucCAN0DispStatus[8];
unsigned char ucCAN1DispStatus[8]={0x05,0X00,0X00,0X00,0X00,0X00,0X00,0X00};


unsigned char ucCAN0InSHC[8];
unsigned char ucCAN1InSHC[8];
unsigned char ucCAN0DrSHC[8];
unsigned char ucCAN1DrSHC[8];
unsigned char ucCAN0InX1[8]={0xAA,0X00,0X00,0X00,0X00,0X00,0X00,0X00};
unsigned char ucCAN1InX1[8];
unsigned char ucCANOutSHC[8];
unsigned char ucCANOutX1[8];
unsigned char ucCANClearBTH[8];

volatile unsigned char ucCANBusoff;

extern unsigned char ucBTUSend;
extern unsigned char ucBTDSend;
extern unsigned char ucX1;
extern unsigned char ucIn1;
extern unsigned char ucIn2;
extern unsigned char ucIn3;
extern unsigned char ucIn4;
extern unsigned char ucIn5;
extern unsigned char ucIn6;
extern unsigned char ucIn7;
extern unsigned char ucIn8;

xStatusHandler xData;

volatile unsigned char ucSHCId;
volatile unsigned char ucPos = 0;

extern unsigned long ulTimerCAN0Tx;
extern unsigned long ulTimerCAN1Tx;
unsigned char ucCAN0TxFlag;
extern void vCAN0Send(void);
extern void vCAN1Send(void);

bool _checkcan0;
bool _checkcan1;


void vCAN0Handler(void)
{
	unsigned long ulStatus, ulCtrl;

	ulStatus = CANIntStatus(CAN0_BASE, CAN_INT_STS_CAUSE);
	switch(ulStatus)
	{
		case 23:{
			CANMessageGet(CAN0_BASE, 23, &xMsgObject0Status, 1);
			if(ucCAN0DispStatus[0] == 0x05)
			{
				_checkcan0 = 1;
				_set(xData.ucStatus,RUN);
		 	}
		 	break;
		}
		default:
		{
			ulCtrl = CANStatusGet(CAN0_BASE, CAN_STS_CONTROL);
			if(ulCtrl & CAN_STATUS_BUS_OFF){ ucCANBusoff = 1;}
		}
	}

	CANIntClear(CAN0_BASE, ulStatus);
}

void vCAN1Handler(void)
{
 	unsigned long ulStatus, ulCtrl;
	
	ulStatus = CANIntStatus(CAN1_BASE, CAN_INT_STS_CAUSE);
	switch(ulStatus)
	{
		case 14:
		{
	 	 	CANMessageGet(CAN1_BASE, 14, &xMsgObject1InX1, 1);
			if(ucCAN1InX1[0] == 0xAA)
			{
				_checkcan1 = 1;
				_set(xData.ucStatus,RUN);
		 	}
			break;
		}
		default:
		{
			ulCtrl = CANStatusGet(CAN1_BASE, CAN_STS_CONTROL);
			if(ulCtrl & CAN_STATUS_BUS_OFF){ ucCANBusoff = 1;}
			break;
		}
	}
	CANIntClear(CAN1_BASE, ulStatus);
}

void CANConfigureNetwork(void)
{
	//------------------------------------------------------------
	// CAN0
	//------------------------------------------------------------
	// DispStatus
	// Rx: SOC -> SHC	
	xMsgObject0Status.ui32MsgID = 22;
	xMsgObject0Status.ui32MsgIDMask = 0xFFFFFFFF;
	xMsgObject0Status.ui32Flags = MSG_OBJ_RX_INT_ENABLE | MSG_OBJ_USE_ID_FILTER;
	xMsgObject0Status.ui32MsgLen = 8;
	xMsgObject0Status.pui8MsgData = ucCAN0DispStatus;
	CANMessageSet(CAN0_BASE,23,&xMsgObject0Status, MSG_OBJ_TYPE_RX);
	
	// DataOutSHC
	// Rx: SOC -> SHC
	xMsgObject0OutSHC.ui32MsgID = MSGOBJ_ID_OUT_SHC;
	xMsgObject0OutSHC.ui32MsgIDMask = 0xFFFFFFFF;
	xMsgObject0OutSHC.ui32Flags = MSG_OBJ_RX_INT_ENABLE | MSG_OBJ_USE_ID_FILTER;
	xMsgObject0OutSHC.ui32MsgLen = 8;
	xMsgObject0OutSHC.pui8MsgData = ucCANOutSHC;
	CANMessageSet(CAN0_BASE, MSGOBJ0_NUM_OUT_SHC, &xMsgObject0OutSHC, MSG_OBJ_TYPE_RX);

	// DataInSHC
	// Tx: SHC -> SOC
	xMsgObject0InSHC.ui32MsgID = MSGOBJ_ID_IN_SHC;
	xMsgObject0InSHC.ui32MsgIDMask = 0;
	xMsgObject0InSHC.ui32Flags = 0;
	xMsgObject0InSHC.ui32MsgLen = 8;
	xMsgObject0InSHC.pui8MsgData = ucCAN0InSHC;

	xMsgObject0DrSHC.ui32MsgID = MSGOBJ_ID_DR_SHC;
	xMsgObject0DrSHC.ui32MsgIDMask = 0;
	xMsgObject0DrSHC.ui32Flags = 0;
	xMsgObject0DrSHC.ui32MsgLen = 8;
	xMsgObject0DrSHC.pui8MsgData = ucCAN0DrSHC;
	
	// DataOutX1
	// Rx: SOC -> X1
	xMsgObject0OutX1.ui32MsgID = MSGOBJ_ID_OUT_X1;
	xMsgObject0OutX1.ui32MsgIDMask = 0xFFFFFFFF;
	xMsgObject0OutX1.ui32Flags = MSG_OBJ_RX_INT_ENABLE | MSG_OBJ_USE_ID_FILTER;
	xMsgObject0OutX1.ui32MsgLen = 8;
	xMsgObject0OutX1.pui8MsgData = ucCANOutX1;
	CANMessageSet(CAN0_BASE, MSGOBJ0_NUM_OUT_X1, &xMsgObject0OutX1, MSG_OBJ_TYPE_RX);

	// DataInX1
	// Tx: SHC -> SOC
	xMsgObject0InX1.ui32MsgID = MSGOBJ_ID_IN_X1;//---------------------------------------------------------
	xMsgObject0InX1.ui32MsgIDMask = 0;
	xMsgObject0InX1.ui32Flags = 0;
	xMsgObject0InX1.ui32MsgLen = 8;
	xMsgObject0InX1.pui8MsgData = ucCAN0InX1;

	// ClearBTH
	// Rx: SOC -> SCC (SCC chuyen du lieu tu SOC den SCE)
	xMsgObject0ClearBTH.ui32MsgID = MSGOBJ_ID_CLR_BTH;
	xMsgObject0ClearBTH.ui32MsgIDMask = 0xFFFFFFFF;
	xMsgObject0ClearBTH.ui32Flags = MSG_OBJ_RX_INT_ENABLE | MSG_OBJ_USE_ID_FILTER;
	xMsgObject0ClearBTH.ui32MsgLen = 8;
	xMsgObject0ClearBTH.pui8MsgData = ucCANClearBTH;
	CANMessageSet(CAN0_BASE, MSGOBJ0_NUM_CLR_BTH, &xMsgObject0ClearBTH, MSG_OBJ_TYPE_RX);
		
	//------------------------------------------------------------
	// CAN1
	//------------------------------------------------------------
	// DispStatus
	// Tx: SHC -> SHC
	xMsgObject1Status.ui32MsgID = 22;
	xMsgObject1Status.ui32MsgIDMask = 0;
	xMsgObject1Status.ui32Flags = 0;
	xMsgObject1Status.ui32MsgLen = 8;
	xMsgObject1Status.pui8MsgData = ucCAN1DispStatus;

	// DataInSHC
	// Rx: SHC -> SHC
	xMsgObject1InSHC.ui32MsgID = MSGOBJ_ID_IN_SHC;
	xMsgObject1InSHC.ui32MsgIDMask = 0xFFFFFFFF;
	xMsgObject1InSHC.ui32Flags = MSG_OBJ_RX_INT_ENABLE | MSG_OBJ_USE_ID_FILTER;
	xMsgObject1InSHC.ui32MsgLen = 8;
	xMsgObject1InSHC.pui8MsgData = ucCAN1InSHC;
	CANMessageSet(CAN1_BASE, MSGOBJ1_NUM_IN_SHC, &xMsgObject1InSHC, MSG_OBJ_TYPE_RX);	

	xMsgObject1DrSHC.ui32MsgID = MSGOBJ_ID_DR_SHC;
	xMsgObject1DrSHC.ui32MsgIDMask = 0xFFFFFFFF;
	xMsgObject1DrSHC.ui32Flags = MSG_OBJ_RX_INT_ENABLE | MSG_OBJ_USE_ID_FILTER;
	xMsgObject1DrSHC.ui32MsgLen = 8;
	xMsgObject1DrSHC.pui8MsgData = ucCAN1DrSHC;
	CANMessageSet(CAN1_BASE, MSGOBJ1_NUM_DR_SHC, &xMsgObject1DrSHC, MSG_OBJ_TYPE_RX);	
		
	// DataOutSHC
	// Tx: SHC -> SHC
	xMsgObject1OutSHC.ui32MsgID = MSGOBJ_ID_OUT_SHC;
	xMsgObject1OutSHC.ui32MsgIDMask = 0;
	xMsgObject1OutSHC.ui32Flags = 0;
	xMsgObject1OutSHC.ui32MsgLen = 8;
	xMsgObject1OutSHC.pui8MsgData = ucCANOutSHC;
	
	// DataInX1
	// Rx: SHC -> SHC
	xMsgObject1InX1.ui32MsgID = MSGOBJ_ID_IN_X1;
	xMsgObject1InX1.ui32MsgIDMask = 0xFFFFFFFF;
	xMsgObject1InX1.ui32Flags = MSG_OBJ_RX_INT_ENABLE | MSG_OBJ_USE_ID_FILTER;
	xMsgObject1InX1.ui32MsgLen = 8;
	xMsgObject1InX1.pui8MsgData = ucCAN1InX1;
	CANMessageSet(CAN1_BASE, MSGOBJ1_NUM_IN_X1, &xMsgObject1InX1, MSG_OBJ_TYPE_RX);	//-------------------------------------
	
	// DataOutX1
	// Tx: SHC -> SHC
	xMsgObject1OutX1.ui32MsgID = MSGOBJ_ID_OUT_X1;
	xMsgObject1OutX1.ui32MsgIDMask = 0;
	xMsgObject1OutX1.ui32Flags = 0;
	xMsgObject1OutX1.ui32MsgLen = 8;
	xMsgObject1OutX1.pui8MsgData = ucCANOutX1;

	// ClearBTH
	// Tx: SCC -> SCE (SCC chuyen du lieu tu SOC den SCE)
	xMsgObject1ClearBTH.ui32MsgID = MSGOBJ_ID_CLR_BTH;
	xMsgObject1ClearBTH.ui32MsgIDMask = 0;
	xMsgObject1ClearBTH.ui32Flags = 0;
	xMsgObject1ClearBTH.ui32MsgLen = 8;
	xMsgObject1ClearBTH.pui8MsgData = ucCANClearBTH;
}
 
void vCANConfig(void)
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
	
	GPIOPinConfigure(GPIO_PE4_CAN0RX);
	GPIOPinConfigure(GPIO_PE5_CAN0TX);
	GPIOPinTypeCAN(GPIO_PORTE_BASE, GPIO_PIN_4 | GPIO_PIN_5);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_CAN0);
	CANInit(CAN0_BASE);

	CANBitRateSet(CAN0_BASE, SysCtlClockGet(), 100000);
	CANEnable(CAN0_BASE);
	CANIntEnable(CAN0_BASE, CAN_INT_MASTER | CAN_INT_ERROR);

	//CAN1
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	GPIOPinConfigure(GPIO_PA0_CAN1RX);
	GPIOPinConfigure(GPIO_PA1_CAN1TX); 
	GPIOPinTypeCAN(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_CAN1);
	CANInit(CAN1_BASE);

	CANBitRateSet(CAN1_BASE, SysCtlClockGet(), 100000);
	CANEnable(CAN1_BASE);
	CANIntEnable(CAN1_BASE, CAN_INT_MASTER | CAN_INT_ERROR);

	CANConfigureNetwork();
	ucCANBusoff = 0;
	
	IntEnable(INT_CAN0_TM4C123);
 	IntEnable(INT_CAN1_TM4C123);
}

void vCAN0Send(void)
{
	CANMessageSet(CAN0_BASE,14,&xMsgObject0InX1, MSG_OBJ_TYPE_TX);
	ulTimerCAN0Tx = TR_UPDATE0;
}
void vCAN1Send(void)
{
	CANMessageSet(CAN1_BASE, 23, &xMsgObject1Status, MSG_OBJ_TYPE_TX);
	ulTimerCAN1Tx = TR_UPDATE1;
}
