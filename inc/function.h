#ifndef __FUNCTION_H__
#define __FUNCTION_H__

#define LATCH				100
#define _latch(x,y)			{GPIOPinWrite(x,y,y); for(i=0;i<LATCH;i++); GPIOPinWrite(x,y,0); for(i=0;i<LATCH;i++);}

#define _latch_col1()	{_latch(GPIO_PORTG_BASE,GPIO_PIN_5);}
#define _latch_col2()	{_latch(GPIO_PORTG_BASE,GPIO_PIN_4);}

#define _latch_block1_1()	{_latch(GPIO_PORTG_BASE,GPIO_PIN_2);}
#define _latch_block1_2()	{_latch(GPIO_PORTG_BASE,GPIO_PIN_3);}

#define _latch_block2_1()	{_latch(GPIO_PORTG_BASE,GPIO_PIN_0);}
#define _latch_block2_2()	{_latch(GPIO_PORTG_BASE,GPIO_PIN_1);}

#define _write_data(x)	{GPIOPinWrite(GPIO_PORTB_BASE, 0xFF, x);}

#define PIN_X1		2
#define PIN_BTU		4
#define PIN_BTD		6

#define PIN_IN1		15//8
#define PIN_IN2		14//9
#define PIN_IN3		13//10
#define PIN_IN4		12//11
#define PIN_IN5		8//12
#define PIN_IN6		9//13
#define PIN_IN7		10//14
#define PIN_IN8		11//15

#define X1_ON()		GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_3, GPIO_PIN_3)
#define LTD_ON()	GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_7, GPIO_PIN_7)
#define LTU_ON()	GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_5, GPIO_PIN_5)

#define X1_OFF()	GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_3, 0)
#define LTD_OFF()	GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_7, 0)
#define LTU_OFF()	GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_5, 0)

#endif
