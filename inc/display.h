#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#define DIR_UP 		0
#define DIR_DOWN	1
#define RUN			2

#define EARTHQUAKE	3
#define FIREMAN		4
#define OVERLOAD	5
#define NHB			7

#define NUM_LEDCODE		84

typedef struct
{
	unsigned char (*pucBlock1)(void);
	unsigned char (*pucBlock2)(void);
} xScanHandler;

typedef struct 
{
	unsigned char ucCur;
	unsigned char ucNext;
	unsigned long *pulBuffer;
	unsigned char ucShift;
} xNumberHandler;

typedef struct 
{
	unsigned char ucLed7Seg;
	unsigned char (*pucBlock1)(void);
	unsigned char (*pucBlock2)(void);
	unsigned char ucNumber;
	unsigned char ucStr;
} xNumberCodeHandler;

typedef struct 
{
	const unsigned int *puiArrow;
	unsigned long *pulBuffer;
	unsigned char ucShift;
} xArrowHandler;
 
typedef struct
{
	unsigned char ucStr;
	unsigned long *pulBuffer;
	unsigned char ucShift;
} xStringHandler;

typedef struct
{
	const unsigned int *puiString;
	unsigned char ucLen;
} xStringCodeHandler;

typedef struct
{
	unsigned char ucID;	
	unsigned char ucLed7Seg;	
	unsigned char ucStatus;
	unsigned char ucStatus1;
} xStatusHandler;

#endif
