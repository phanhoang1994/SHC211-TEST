//**************************************
//* File: 			display.c
//*	Date: 			10/11/12
//*	Creator:		TrongHieu(tronghieu@tne.vn)
//* Last modify:	14/01/13
//* Description:	This file is in CAN communication lift control system project.
//*					The functions in this file representated to display matrix led of ThienNam 
//*					elevator indicator. The hardware was designed by LeDuy(leduy@tne.vn).
//*					The hardware was edited by TrongHieu.
//*					This file is copywritghted by ThienNam Join Stock Company (www.tne.vn).
//* Version: 		V1.0. 
//*************************************
// define de su dung chuong trinh trong ROM
#define TARGET_IS_TM4C123_RA1

#include <stdint.h>
#include <stdbool.h>

#include "inc/hw_gpio.h"
#include "inc/hw_types.h"
#include "inc/hw_can.h"
#include "inc/hw_memmap.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_ints.h"

#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/systick.h"
#include "driverlib/can.h"
#include "driverlib/watchdog.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"

#include "inc/sysclock.h"
#include "inc/global.h"
#include "inc/display.h"
#include "inc/function.h"

const unsigned long MASK[32] =
{
	0x00000001, 0x00000002, 0x00000004, 0x00000008, 0x00000010, 0x00000020, 0x00000040, 0x00000080,
	0x00000100, 0x00000200, 0x00000400, 0x00000800, 0x00001000, 0x00002000, 0x00004000, 0x00008000,
	0x00010000, 0x00020000, 0x00040000, 0x00080000, 0x00100000, 0x00200000, 0x00400000, 0x00800000,	
	0x01000000, 0x02000000, 0x04000000, 0x08000000, 0x10000000, 0x20000000, 0x40000000, 0x80000000
};

extern void vPoll(void);
extern void vSysTickConfig(void);
extern void vDispConfig(void);
extern void vCANConfig(void);

void vHardwareConfig(void);
volatile unsigned char ucWDT;

void vWDTHandler(void)
{ 
	if(ucWDT == 0){ WatchdogIntClear(WATCHDOG0_BASE);}
	ucWDT = 1;
}

int main(void)
{
	vHardwareConfig();
	while(1) 
	{
	  	vPoll();
		ucWDT = 0;
	};
}

void vWDTConfig(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_WDOG0);
   	IntEnable(INT_WATCHDOG);
    WatchdogReloadSet(WATCHDOG0_BASE, SysCtlClockGet());
    WatchdogResetEnable(WATCHDOG0_BASE);
    WatchdogEnable(WATCHDOG0_BASE);
}

void vHardwareConfig(void)
{
	volatile unsigned char i;
	
	#if (LM3S2965_EVB_DEBUG == 1)
		#warning "We are debugging, please to config LM3S2965_EVB_DEBURG = 0 in global.h"
	#endif
	
	/* Set the clocking to run from the PLL at 80 MHz */
  	SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_8MHZ);

	// Enable the peripherals used by the application.
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);	//Data
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);	//Input
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOG);	//Latch
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA); 	//Button
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);	// Big and vertical

	// set up outport
	GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, 0xFF); 	//Data
	GPIOPinTypeGPIOOutput(GPIO_PORTG_BASE, 0x3F);	//Latch - PG0 .. PG5
	GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_3 | GPIO_PIN_5 | GPIO_PIN_7);	//Button
	GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_0); 	//Data
	GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0, 0);
	
	// set up inport
	// Enable the peripherals used by the application.
	HWREG(GPIO_PORTD_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
	HWREG(GPIO_PORTD_BASE + GPIO_O_CR) |= 0x80;
	HWREG(GPIO_PORTD_BASE + GPIO_O_AFSEL) &= ~0x80;
	HWREG(GPIO_PORTD_BASE + GPIO_O_DEN) |= 0x80;
	HWREG(GPIO_PORTD_BASE + GPIO_O_LOCK) = 0;
	
//	GPIOPinTypeGPIOInput(GPIO_PORTD_BASE, 0xFF);
//	GPIOPadConfigSet(GPIO_PORTD_BASE, 0xFF,	GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

	GPIOPinTypeGPIOInput(GPIO_PORTA_BASE, GPIO_PIN_2 | GPIO_PIN_4 | GPIO_PIN_6);
	GPIOPadConfigSet(GPIO_PORTA_BASE, GPIO_PIN_2 | GPIO_PIN_4 | GPIO_PIN_6,	GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

	HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
	HWREG(GPIO_PORTF_BASE + GPIO_O_CR) |= 0x01;
	HWREG(GPIO_PORTF_BASE + GPIO_O_AFSEL) &= ~0x01;
	HWREG(GPIO_PORTF_BASE + GPIO_O_DEN) |= 0x01;
	HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = 0;

	GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2);
	GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
	
	// clear screen
	_write_data(0xFF);
	_latch_col1();

	_write_data(0xFF);
	_latch_col2();	

	_write_data(0xFF);
	_latch_block1_1();

	_write_data(0xFF);
	_latch_block1_2();

	_write_data(0xFF);
	_latch_block2_1();

	_write_data(0xFF);
	_latch_block2_2();
		
	vDispConfig();
	vCANConfig();
	vSysTickConfig();
	SysTickEnable();
	vWDTConfig();
		
	IntMasterEnable();
} 

