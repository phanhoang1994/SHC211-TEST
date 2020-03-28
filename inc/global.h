#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#define DEBUG 				(0)
#define DEBUG_VIEW		(0)
#define JAPANESE			(0)
#define PASSENGER			(0)

#define TR_INP				(25)
#define TR_JAM				(180)
#define TR_HOLDING			300
#define TR_UPDATE0				50
#define TR_UPDATE1				50
#define TR_HOLDING_1		1000
#define TR_RESET				5000
#define TR_CAN_RESET		5000
#define TR_PWM					3

#define LOWPWM					10
#define HIGHPWM					10

#if (JAPANESE == 0)
	#define NUMBER_SPEED	100
	#define ARROW_SPEED		100
	#define STRING_SPEED	35
#else
	#define NUMBER_SPEED	35
	#define ARROW_SPEED		50
	#define STRING_SPEED	70
#endif

#define RESPONSE_INTERVAL	3

#define CPU_CLOCK_HZ			80000000
#define TICK_RATE_HZ			2000
#define TICK_RATE_1MS		(TICK_RATE_HZ / 1000)

#define TRUE	1
#define FALSE	0

#define True	1
#define False	0

#define true	1
#define false	0

typedef union
{
	unsigned long LONG;
	unsigned int INT[2];
	unsigned char BYTE[4];
} DWORD;

typedef union
{
	unsigned int INT;
	unsigned char BYTE[2];
} WORD;

typedef unsigned char boolean;

extern const unsigned long MASK[];

#define _clear(x,y) (x &= ~MASK[y]) 
#define _set(x,y) (x |= MASK[y])
#define _toggle(x,y)(x ^= MASK[y])
#define _isset(x,y) ((x & MASK[y]) != 0)
#define _isclear(x,y) ((x & MASK[y]) == 0) 

#endif
