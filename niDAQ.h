// Copyright 2013 Prysm Inc.
// San Jose, CA, 95134
// btremaine@prysm.com
// btremaine@omnificsolutions.com
//
// niDAQ.h
//


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// niDAQ.h : header file
//
#include "NIDAQmx.h"

#define DAQmxErrChk(functionCall) if( DAQmxFailed(error=(functionCall)) ) goto Error; else
#define DEFAULT_RD_DLY  (3.0)

#define CTR0_OUT "/Dev1/ctr0"
#define CTR1_OUT "/Dev1/ctr1"

#define LOW  0
#define HIGH 1

#define PI	3.1415926535

#define NULL_MODULE  3

/////////////////////////////////////////////////////////////////////////////
// CniDAQ window

class CniDAQ
{
// Construction
public:
	CniDAQ();

// Attributes
public:

// Operations
public:
	int     ChkNiDaqAvail(CString serial_num) ;
    float64 NiDaqMeasSingleVoltage(const char * str) ;
	int     NiDaqSetOutputVoltage(const char * str, float64 value) ;
	int     NiDaqSetDigitalOutput(const char * str, const unsigned char input[]) ;
	int     NiDaqMeasSimpleDigitalInput(const char * str ) ;
	int     NiDaqMeasPortDigitalInput(const char * str, unsigned long int * data ) ;
	float64 NiDaqMeasDigitalFreqLf(const char * str, float minVal, float maxVal, char * str2 = '\0' ) ;
	int     NiDaqCountEventsWithinPeriod(const char * str, unsigned long int *data, unsigned int period, char * str2 = '\0');
	 
    int     NiDaqMeasAnalogSamples(char * RdChnl, float64 *data, float smplRate, unsigned int numSample, bool type = false, float64 threshold = 0, float64 hyster=0 ) ;


	int     NiDaqSetPulseGen(TaskHandle *taskHandle, char * chnl, char * ctr, float64 freq, float64  duty,
		                     uInt32 initDelay=0, uInt32 edge=DAQmx_Val_Rising, const char triggerSource[]="80MHzTimebase") ;

	int     NiDaqSetSineOutputVoltage(TaskHandle *taskHandle, char * str, float64 freq, float64 value) ;

    int     NiDaqSetTwoPulseGen(TaskHandle *taskHandle, char * chnl0, char * chnl1,
								float64 freq0, float64  duty0, float64 freq1, float64  duty1,
							    uInt32 initDelay0, uInt32 initDelay1,
								uInt32 edge, const char triggerSource[]) ;
   
    int     NiDaqMeasStepperSamples(char * RdChnl, float64 *data, float smplRate, 
				             unsigned int numSample, bool type, float64 threshold, float64 hyster) ;

    
	int     GetNiDAQmxStatus(void) ;
	unsigned long int GetNiDAQmxSerialNum(void) ;
	int     ConvertDecToDaqCharArray(unsigned int input, unsigned char *result, int size ) ;
	int     NiDaqKillTask(TaskHandle *taskHandle) ;
	int     NiDaqResetTerm(TaskHandle *taskHandle, const char channel[]) ;

	int     NiDaqWriteDacBoardByte(int module, int addr, int data) ; // write addr & data 
	int     NiDaqWriteDacBoardAddr(int module, int addr);  // write addr only
	int     NiDaqReadDacBoardByte(int module, int addr, int * data, bool flag) ;

	int     NiDaqWriteDacBoardWord(int module, int addr, int chan, int data);
	int     NiDaqReadDacBoardWord(int module, int addr, int chan, int * data, bool flag);

	int     NiDaqReadDacBoardAdcChan(int module, int chan, int * data) ;
	int		NiDaqReadDacBoardAdc(int module, int chan, int * data, bool type);

	int     GetModSelValue(int module, unsigned char * value) ;
	int     SetModSel(int module) ;
	int     StrobeCSelHi(void) ;
	int     StrobeCSelLow(void) ; 
	int     StrobeCsHiLow(void) ;

	int     NiDaqSetDigitalOutputType(const char * chnl, bool iotype ) ;
	int     NiDaqSetPortTristateMode(const char * chnl, bool iotype) ;

	static int32 CVICALLBACK DoneCallback(TaskHandle taskHandle, int32 status, void *callbackData) ;

    int m_niDAQmx_online ;
	unsigned long int niDAQserialNum ;
	CString m_device ;


private:
	TaskHandle  m_taskHandle ;
	

// Implementation
public:
	virtual ~CniDAQ();


protected:

};

/////////////////////////////////////////////////////////////////////////////