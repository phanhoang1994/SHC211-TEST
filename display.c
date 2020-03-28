#include <stdint.h>
#include <stdbool.h>

/* Standard includes. */
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"

#include "inc/global.h"
#include "inc/display.h"
#include "inc/function.h"

#if (JAPANESE==1)
	/*
	const unsigned int uiStringJapanese1[] = 
	{
		0xFFFE, 0xFFFD, 0xFC13, 0xFDDF, 0xFDD7, 0xFDD8, 0xFDDF, 0x01DF,
		0xDDDF, 0xDDD7, 0xDDD8, 0xDDDF, 0xDC17, 0xDFFB, 0xFFFC, 0x0000,
		0xEF1F, 0xECFF, 0x0000, 0xEBFF, 0xEDFF, 0xF7FE, 0xEA0E, 0xDADD,
		0xBADB, 0x7AD7, 0x780F, 0xBAD7, 0xDADB, 0xEADD, 0xF60E, 0xFFFE,
		0x0000, 0x0000, 0xE03F, 0xEFBF, 0xEFBF, 0xEFBF, 0xEFBF, 0xEFBF,
		0x0000, 0xEFBF, 0xEFBF, 0xEFBF, 0xEFBF, 0xEFBF, 0xE03F, 0x0000,
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF
	};
	*/
	
	// kiem tra thang - inspection
	const unsigned int uiStringKiemTraThang[80] = 
	{
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	};

	#if(PASSENGER==1)
		// Qua tai tai khach - overload
		const unsigned int uiStringQuaTai[] = 
		{
			0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
			0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
			0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
			0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
		};
	#else
		// Qua tai tai hang - overload
		const unsigned int uiStringQuaTai[] = 
		{
			0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
			0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
			
			0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
			0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
	 	};
	#endif

	// Dong dat - eqt
	const unsigned int uiStringDongDat[] = 
	{
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
		
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
	};
	
	// rescue
	const unsigned int uiStringCuuHoMatDien[] = 
	{
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,	0x0000, 
		
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
	};
	
	// Bao chay - fireman
	const unsigned int uiStringCuuHoa[] = 
	{
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,	0x0000, 
		
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	};
	
	// Thang dang su dung
	const unsigned int uiStringDangSuDung[] = 
	{
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
		
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	};

	const unsigned int uiStringTrucTang[]=
	{
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,	0x0000, 
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,	0x0000, 0x0000,
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	};

	const unsigned int uiStringTamDung[] =
	{
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,	0x0000, 
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,	0x0000, 0x0000,
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	}; //tiengnhat
	 
	const unsigned int uiStringXacLapViTri[73] =  {
	 	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	 	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
		 		
		0x0000, 0x0000, 0x0000, 0x0000,	0x0000, 0x0000, 0x0000, 0x0000, 
		0x0000, 0x0000, 0x0000,	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
	}; 	//Reset

	const unsigned int uiStringXayRaLoi[]; 		//E

	xStringCodeHandler xStringTable[]=					   
	{
		{uiStringTamDung, 64},			//0
	 	{uiStringKiemTraThang, 80},		//1
		{uiStringCuuHoMatDien, 144},	//2
		{uiStringCuuHoa, 144},			//3
		{uiStringXayRaLoi, 0},			//Don't used
		{uiStringQuaTai, 64},			//5
		{uiStringXacLapViTri, 73},		//6
		{uiStringDongDat, 144},			//7
		{uiStringDangSuDung, 80},		//8
		{uiStringTrucTang, 64},			//9
	};
#else
	
	const unsigned int uiStringKiemTraThang[121]=
	{
	 	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	 	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	 	
	 			 
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,	0x0000, 
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,	0x0000,
	};																						  

	const unsigned int uiStringTamDung[100]=
	{
	 	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	 	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,

	 	 			 	
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,	0x0000, 
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,	0x0000, 
	};
	
	const unsigned int uiStringCuuHo[82]=
	{
	 	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	 	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,

	 	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,	0x0000, 
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000
	};
	
	const unsigned int uiStringCuuHoa[83]=
	{
	 	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	 	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,

	 	
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,	0x0000, 
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000
	};
	
	const unsigned int uiStringUuTienCabin[116]=
	{
	 	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	 	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	 		 		 		 		 		 		 	
		0x0000, 0x0000, 0x0000, 0x0000,	0x0000, 0x0000, 0x0000, 0x0000, 
		0x0000, 0x0000, 0x0000,	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
	};
	
	const unsigned int uiStringQuaTai[78]=
	{
	 	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	 	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	 		 		 		 		
		0x0000, 0x0000, 0x0000, 0x0000,	0x0000, 0x0000, 0x0000, 0x0000, 
		0x0000, 0x0000, 0x0000,	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
	};
	
	const unsigned int uiStringReset[73]=
	{
	 	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	 	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	 		
		0x0000, 0x0000, 0x0000, 0x0000,	0x0000, 0x0000, 0x0000, 0x0000, 
		0x0000, 0x0000, 0x0000,	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
	};
	
		const unsigned int uiStringDayTai[90]=
	{
	 	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	 	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,

		
		0x0000, 0x0000, 0x0000, 0x0000,	0x0000, 0x0000, 0x0000, 0x0000, 
		0x0000, 0x0000, 0x0000,	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
	};
	const unsigned int uiStringDongDat[72];
	const unsigned int uiStringDangSuDung[72];
	
	xStringCodeHandler xStringTable[]=					   
	{
		{uiStringTamDung, 100},			//0
	 	{uiStringKiemTraThang, 121},	//1
		{uiStringCuuHo, 82},			//2
		{uiStringCuuHoa, 83},			//3
	//	{uiStringUuTienCabin, 116},		//4
		{uiStringQuaTai, 78},			//5
		{uiStringReset, 73},			//6
		{uiStringDongDat, 72},			//7
		{uiStringDangSuDung, 72},		//8
		{uiStringDayTai, 90},			//9
	};

#endif

// Bien phuc vu hien thi led
unsigned long ulNumberDelay;
unsigned long ulArrowDelay;
unsigned long ulStringDelay;

unsigned char ucBlock11;
unsigned char ucBlock12;
unsigned char ucBlock21;
unsigned char ucBlock22;

unsigned long ulBlock1Data[16];
unsigned long ulBlock2Data[16];

unsigned long ulPWMCnt;
extern unsigned long ulPWMSet;

unsigned char ucColumn;
xNumberHandler xNumber;
xArrowHandler xArrow;
xScanHandler xBlock;
xStringHandler xString;
extern xStatusHandler xData;

void (*pvScroll)(void);
void vScanled(void);

extern void vScrollV(void);
extern void vScrollH(void);

extern unsigned char ucScrollNumberV(void);
extern unsigned char ucScrollNumberH(void);
extern unsigned char ucScrollArrowV(void);
extern unsigned char ucScrollArrowH(void);
extern unsigned char ucScrollStringV(void);
extern unsigned char ucScrollStringH(void);

void vDispConfig(void)
{
	unsigned char i=0;
	
	// intinialize
	ucColumn = 0;

	xNumber.ucCur=0;
	xNumber.ucNext=0;
	
	xString.ucStr=0;
	xBlock.pucBlock1=ucScrollNumberV;	
	xBlock.pucBlock2=ucScrollArrowV;

	_clear(xData.ucStatus,DIR_UP);  	//Up
	_clear(xData.ucStatus,DIR_DOWN);	//Down
	//_clear(xData.ucStatus,RUN);	//Run

	/* Broadcast Frame: 8byte
		BYTE0: 	NumOfFloor
		BYTE1: 	Display
		BYTE2: 	Status 
				Bit0: Up
				Bit1: Down
				Bit2: Run
				Bit3: Earthquake
				Bit4: Fireman
				Bit5: Overload
				Bit6: Busy
				Bit7: Big digits

		BYTE3: 	Current floor
		BYTE4: 	Unused
		BYTE5: 	Unused
		BYTE6: 	Unused
		BYTE7: 	Unused
	*/
	i = 0;
	//i = 0x79;
	xData.ucLed7Seg = i;

	i = 0;
	//_set(i,RUN);
	//_set(i,DIR_UP);
	//_set(i,DIR_DOWN);
	//_set(i, EARTHQUAKE);
	//_set(i, FIREMAN);	
	//_set(i, OVERLOAD);
	//_set(i, NHB);	
	xData.ucStatus = i;

	i = 0;
	//_set(i, FULLLOAD);
	xData.ucStatus1 = i;

	ulPWMSet = HIGHPWM;
	
	pvScroll=vScrollV;
}

void vClearDisp(void)
{
	ucBlock11 = 0xFF;
	ucBlock12 = 0xFF;
	ucBlock21 = 0xFF;
	ucBlock22 = 0xFF;
}

void vDisplay(void)
{
	DWORD tmp;
	volatile unsigned char i;
	
	// if BIG	
	// if(VER == 0){ pvScroll = vScrollV} else { pvScroll = vScrollH;}

	//vClearDisp();

	// nap gia tri vao bo dem	
	if((pvScroll!=0) & (ucColumn==0))
	{
		for(i=0;i<16;i++){ ulBlock1Data[i]=0; ulBlock2Data[i]=0;}
		if(pvScroll!=0) pvScroll();	
		if(xBlock.pucBlock1!=0) xBlock.pucBlock1();
		if(xBlock.pucBlock2!=0) xBlock.pucBlock2();
	}
	// Dao bit cac gia tri vua nap
	tmp.LONG=ulBlock1Data[ucColumn];
	tmp.LONG^=0xFFFFFFFF;
	ucBlock21=tmp.BYTE[1];
	ucBlock22=tmp.BYTE[0];

	tmp.LONG=ulBlock2Data[ucColumn];
	tmp.LONG^=0xFFFFFFFF;
	ucBlock11=tmp.BYTE[1];
	ucBlock12=tmp.BYTE[0]; 

}

void vScanled(void)
{
	DWORD tmp;
	volatile unsigned char i;
	
	vDisplay();

	// All column is off;
	// clear screen
	_write_data(0xFF);
	_latch_col1();

	_write_data(0xFF);
	_latch_col2();	

   	_write_data(ucBlock11);
	_latch_block2_2();

	_write_data(ucBlock21);
	_latch_block2_1();

	tmp.LONG = 0xFFFFFFFF;
	_clear(tmp.LONG, ucColumn);
 	if(++ulPWMCnt >= HIGHPWM){ ulPWMCnt = 0;}
	if(ulPWMCnt <= ulPWMSet)
	{
		_write_data(tmp.BYTE[0]);
		_latch_col1();

		_write_data(tmp.BYTE[1]);
		_latch_col2();	
	}			
	
	if(++ucColumn>15){ ucColumn = 0;}
}