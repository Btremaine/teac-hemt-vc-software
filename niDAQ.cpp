// Copyright 2013 Prysm Inc.
// San Jose, CA, 95134
// btremaine@prysm.com
// btremaine@omnificsolutions.com
//
// niDAQ.cpp : implementation file
//

#include "stdafx.h"
#include "MFCHemtALTApp.h"
#include "MFCHemtALTDlg.h"
#include "niDAQ.h"
#include "math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CniDAQ

CniDAQ::CniDAQ()
{
	m_taskHandle = 0 ;
}

CniDAQ::~CniDAQ()
{
}


//---------------------------------------------------------------------------
int CniDAQ::ChkNiDaqAvail(CString serial_num)
{
	
    // Check for availability of DAQ by getting do self check & getting serial number
	// //////////////////////////////////////////////////////////////////////////////

	int32 error = 0;
	unsigned long int data;
	// char device[] =  "Dev1" ;
	CString str = "00000000000000000000000000000000000000000000000000000000000000000000000000000000";

	// get list of devices then check each one for assigned serial number
	int bufferSize = 30;
	char * list = new char[30];
	strcpy(list, _T("000000000000000000000000000\0")) ;
	if( DAQmxGetSysDevNames( list, bufferSize) )
	{
		str = "Error Initializing NI-USB-6501,\r\ncan't get serial number: " ;
		str += serial_num ;
		AfxMessageBox(str) ;
		m_niDAQmx_online = -1 ;
		niDAQserialNum = 0 ;
		delete [] list;
		return (m_niDAQmx_online) ;
	}

	// check devices in 'list' against serial number
	m_niDAQmx_online = 0 ; // initialize to PASS

	CString szBuff = list ;
	CString buf ;
	boolean found = false ;

	wchar_t *end = NULL;
    long value = strtol (serial_num, NULL, 16);

	while(!found && error == 0)  // will exit with found true or error
	{
		int pos = szBuff.Find("Dev") ;
		buf= szBuff.Mid(pos,4) ;
		szBuff.Delete(pos,4) ;
		error = DAQmxGetDevSerialNum(buf, &data) ;
		if( value == data ) found = true ;
	}

    if( error )
	{
		str.Format(_T("Error Initializing NI-USB-6501,\r\ncan't get serial number: ")+serial_num) ;
	    //AfxMessageBox(str) ;

		m_niDAQmx_online = -1 ;
		niDAQserialNum = 0 ;
	}
	else
	{
		// device name in buf and serial # is in data		
		// use SelfTest to indicate presence of the physical device on the bus

		// Driver could report present when it is physically removed
		if(DAQmxSelfTestDevice(buf))
		{
			str = "Error Initializing NI-USB-6501,\r\nfailed self-test: " ;
			str += m_device ;
			//AfxMessageBox(str) ;
			m_niDAQmx_online = -1 ;
			niDAQserialNum = 0 ;
		}
		else
		{
			niDAQserialNum = data ;
		    m_device = buf ;
			m_niDAQmx_online = 0 ;
		}
	}

	delete[] list;

    return (m_niDAQmx_online) ;
}

//---------------------------------------------------------------------------
int CniDAQ::GetNiDAQmxStatus(void)
{
    return m_niDAQmx_online ; // 0 PASS / -1 FAIL
}

//---------------------------------------------------------------------------
unsigned long int CniDAQ::GetNiDAQmxSerialNum(void)
{
    return niDAQserialNum ;
}

//-------------------------------------------------------------------------------
float64 CniDAQ::NiDaqMeasSingleVoltage(const char * str)
{
   // measure single voltage on selected channel
   // //////////////////////////////////////////
		
	int32       error=0;
	TaskHandle  taskHandle=0;
	int32       read;
	float64     data[2];
	char        errBuff[2048]={'\0'};

	//---------------------
	// DAQmx Configure Code
	//---------------------
	DAQmxErrChk (DAQmxCreateTask("",&taskHandle));
	DAQmxErrChk (DAQmxCreateAIVoltageChan(taskHandle, str,"",DAQmx_Val_RSE,-10.0,10.0,DAQmx_Val_Volts,NULL));
	DAQmxErrChk (DAQmxCfgSampClkTiming(taskHandle,"",1000.0,DAQmx_Val_Rising,DAQmx_Val_FiniteSamps,2));

	//--------------------
	// DAQmx Start Code
	//--------------------
	DAQmxErrChk (DAQmxStartTask(taskHandle));

	//-------------------
	// DAQmx Read Code
	//-------------------
	DAQmxErrChk (DAQmxReadAnalogF64(taskHandle,2,DEFAULT_RD_DLY,DAQmx_Val_GroupByChannel,data,2,&read,NULL));


Error:
	if( DAQmxFailed(error) )
	{
		DAQmxGetExtendedErrorInfo(errBuff,2048);
	}

	NiDaqKillTask(&taskHandle) ;

	if( DAQmxFailed(error) )
	{
		AfxMessageBox( errBuff) ;
		data[0] = 0 ;
		//throw "Error reading voltage NI-USB-6XXX" ;
		AfxMessageBox("Error Initializing NI-USB-6XXX") ;	
	}

    return (data[0]) ;
}
//-------------------------------------------------------------------------------------------
int CniDAQ::NiDaqSetOutputVoltage(const char * str, float64 data)
{
    // set analog voltage out on a given channel
	// /////////////////////////////////////////

	int			error=0;
	TaskHandle	taskHandle=0;
	char		errBuff[2048]={'\0'};
	float64 buf[1] = {data} ;

	//-----------------------
	// DAQmx Configure Code
	//-----------------------
	DAQmxErrChk (DAQmxCreateTask("",&taskHandle));
	DAQmxErrChk (DAQmxCreateAOVoltageChan(taskHandle,str,"",-5.0,5.0,DAQmx_Val_Volts,""));

	//----------------------
	// DAQmx Start Code
	//----------------------
	DAQmxErrChk (DAQmxStartTask(taskHandle));

	//----------------------
	// DAQmx Write Code
	//----------------------
	DAQmxErrChk (DAQmxWriteAnalogF64(taskHandle,1,1,DEFAULT_RD_DLY,DAQmx_Val_GroupByChannel,buf,NULL,NULL));

Error:
	if( DAQmxFailed(error) )
		DAQmxGetExtendedErrorInfo(errBuff,2048);

	NiDaqKillTask(&taskHandle) ;

	if( DAQmxFailed(error) )
	{
		AfxMessageBox(errBuff) ;
		return (-1) ;
	}

	return (0) ;
}
//-------------------------------------------------------------------------------
int CniDAQ::NiDaqSetDigitalOutput(const char * str, const unsigned char input[]) 
{
	// Output a digital value to the selected port
	// ///////////////////////////////////////////

	int         error=0;
	TaskHandle  taskHandle=0;

	char        errBuff[2048]={'\0'};

	//-----------------------
	// DAQmx Configure Code
	//-----------------------
	DAQmxErrChk (DAQmxCreateTask("",&taskHandle));

	DAQmxErrChk (DAQmxCreateDOChan(taskHandle,str,"",DAQmx_Val_ChanForAllLines));

	// set output drive type to active push-pull (not open drain).
	DAQmxErrChk(DAQmxSetDOOutputDriveType(taskHandle, str, DAQmx_Val_ActiveDrive)); // 4/14/14 DAQmx_Val_ActiveDrive));

	//----------------------
	// DAQmx Start Code
	//----------------------
	DAQmxErrChk (DAQmxStartTask(taskHandle));

	//---------------------
	// DAQmx Write Code
	//---------------------
	DAQmxErrChk (DAQmxWriteDigitalLines(taskHandle,1,1,DEFAULT_RD_DLY,DAQmx_Val_GroupByChannel,input,NULL,NULL));

Error:
	if( DAQmxFailed(error) )
		DAQmxGetExtendedErrorInfo(errBuff,2048);

	NiDaqKillTask(&taskHandle) ;


	if( DAQmxFailed(error) )
	{
		AfxMessageBox(errBuff) ;
		return (-1) ;
	}
	
	return (0);
}
// -----------------------------------------------------------------------------------------------
int CniDAQ::NiDaqSetDigitalOutputType(const char * chnl, bool iotype )
{
	// 
    // DAQmx_Val_ActiveDrive - Value for push-pull drive
	// DAQmx_Val_OpenCollector - Value for open-drain
    // 

	// Set digital output drive type to the selected port
	// //////////////////////////////////////////////////
	int         error=0;
	TaskHandle  taskHandle=0;
	char        errBuff[2048]={'\0'};
	//-----------------------
	// DAQmx Configure Code
	//-----------------------
	
	DAQmxErrChk (DAQmxCreateTask("",&taskHandle));
	DAQmxErrChk (DAQmxCreateDOChan(taskHandle,chnl,"",DAQmx_Val_ChanForAllLines));

	int val ;

	if (iotype) val = DAQmx_Val_ActiveDrive ;
	else val = DAQmx_Val_OpenCollector ;

	DAQmxErrChk (DAQmxSetDOOutputDriveType(taskHandle, chnl, val)) ;

	DAQmxErrChk (DAQmxStartTask(taskHandle));

Error:
	if( DAQmxFailed(error) )
		DAQmxGetExtendedErrorInfo(errBuff,2048);

	NiDaqKillTask(&taskHandle) ;

	if( DAQmxFailed(error) )
	{
		AfxMessageBox(errBuff) ;
		return (-1) ;
	}
	
	return (0);

}

//-------------------------------------------------------------------------------------------
int CniDAQ::NiDaqSetPortTristateMode(const char * chnl, bool iotype)
{
	// 
    // Set or clear tri-state mode of selected port
    // On bi-directional IO set tri-state true before enabling external data in
	// ////////////////////////////////////////////////////////////////////////

	int         error=0;
	TaskHandle  taskHandle=0;
	char        errBuff[2048]={'\0'};
	//-----------------------
	// DAQmx Configure Code
	//-----------------------
	
	DAQmxErrChk (DAQmxCreateTask("NiDaqSetPortTristateMode",&taskHandle));
	DAQmxErrChk (DAQmxCreateDOChan(taskHandle,chnl,"NiDaqSetPortTristateMode",DAQmx_Val_ChanForAllLines));


	DAQmxErrChk (DAQmxSetDOTristate(taskHandle, chnl, iotype)) ;

	DAQmxErrChk (DAQmxStartTask(taskHandle));

Error:
	if( DAQmxFailed(error) )
		DAQmxGetExtendedErrorInfo(errBuff,2048);

	NiDaqKillTask(&taskHandle) ;

	if( DAQmxFailed(error) )
	{
		AfxMessageBox(errBuff) ;
		return (-1) ;
	}
	
	return (0);

}

// ------------------------------------------------------------------------------------------
float64 CniDAQ::NiDaqMeasDigitalFreqLf(const char * str, float minFreq, float maxFreq, char * str2 ) 
{
	// Measure the frequency of a digital signal (low frequency mode)
	// ////////////////////////////////////////////////////////////// 
	
	int         error=0;
	TaskHandle  taskHandle=0;
	float64     data[1];
	char        errBuff[2048]={'\0'};

	unsigned int  bufferSize = 21 ;
	char str3[20]={'\0'} ;

	//----------------------
	// DAQmx Configure Code
	//----------------------
	DAQmxErrChk (DAQmxCreateTask("",&taskHandle));
	DAQmxErrChk (DAQmxCreateCIFreqChan(taskHandle,str,"",minFreq,maxFreq,DAQmx_Val_Hz,DAQmx_Val_Rising,DAQmx_Val_LowFreq1Ctr,0.001,4,""));

	if (str2 != NULL)
	{  // re-assign pin number
		DAQmxGetCIFreqTerm(taskHandle, str, str3, bufferSize);
	    DAQmxSetCIFreqTerm(taskHandle, str, str2);
	    DAQmxGetCIFreqTerm(taskHandle, str, str3, bufferSize);

       DAQmxSetCIFreqTerm(taskHandle, str, str2);
	}

	//---------------------
	// DAQmx Start Code
	//---------------------
	DAQmxErrChk (DAQmxStartTask(taskHandle));

	//---------------------
	// DAQmx Read Code
	//---------------------
	DAQmxErrChk (DAQmxReadCounterScalarF64(taskHandle,DEFAULT_RD_DLY,&data[0],0));


Error:
	if( DAQmxFailed(error) )
		DAQmxGetExtendedErrorInfo(errBuff,2048);

	NiDaqKillTask(&taskHandle) ;

	if( DAQmxFailed(error) )
	{
		AfxMessageBox(errBuff) ;
		data[0] = 0 ;
		//throw "Error reading freq NI-USB-6XXX" ;
	}
	
	return (data[0]);
}

//--------------------------------------------------------------------------------------------
int CniDAQ::NiDaqMeasSimpleDigitalInput(const char * str ) 
{

    // measure single digital input channel
	// ////////////////////////////////////

	int32		error=0;
	int32       read, bytes ;
	TaskHandle	taskHandle=0;

	unsigned char data[1] ;
	
	char		errBuff[2048]={'\0'};

	//-----------------------
	// DAQmx Configure Code
	//-----------------------
	DAQmxErrChk (DAQmxCreateTask("",&taskHandle));
	DAQmxErrChk (DAQmxCreateDIChan(taskHandle,str,"",DAQmx_Val_ChanForAllLines));

	//-----------------------
	// DAQmx Start Code
	//-----------------------
	DAQmxErrChk (DAQmxStartTask(taskHandle));

	//----------------------
	// DAQmx Read Code
	//----------------------
	DAQmxErrChk (DAQmxReadDigitalLines(taskHandle,1,10.0,DAQmx_Val_GroupByChannel,data,1,&read,&bytes,NULL));

Error:
	if( DAQmxFailed(error) )
		DAQmxGetExtendedErrorInfo(errBuff,2048);

	NiDaqKillTask(&taskHandle) ;
		
	if( DAQmxFailed(error) )
	{
		AfxMessageBox(errBuff) ;
		data[0] = 0 ;
		//throw "Error reading digital input NI-USB-6XXX" ;
	}
	
	return (data[0]);
}

//--------------------------------------------------------------------------------------------
int CniDAQ::NiDaqMeasPortDigitalInput(const char * str, unsigned long int * data ) 
{

    // measure multiple consecutive digital input channels 
	// ///////////////////////////////////////////////////

	int32		error=0;
	TaskHandle	taskHandle=0;
	char		errBuff[2048]={'\0'};
	int32		read;

	//-----------------------
	// DAQmx Configure Code
	//-----------------------
	DAQmxErrChk (DAQmxCreateTask("",&taskHandle));
	DAQmxErrChk (DAQmxCreateDIChan(taskHandle,str,"",DAQmx_Val_ChanForAllLines));

	//----------------------
	// DAQmx Start Code
	//----------------------
	DAQmxErrChk (DAQmxStartTask(taskHandle));

	//---------------------
	// DAQmx Read Code
	//---------------------
	DAQmxErrChk (DAQmxReadDigitalU32(taskHandle, 1, DEFAULT_RD_DLY, DAQmx_Val_GroupByChannel, data, 1, &read, NULL));

Error:
	if( DAQmxFailed(error) )
		DAQmxGetExtendedErrorInfo(errBuff,2048);

	NiDaqKillTask(&taskHandle) ;
		
	if( DAQmxFailed(error) )
	{
		AfxMessageBox(errBuff) ;
		data = 0 ;
		//throw "Error reading digital input NI-USB-6XXX" ;
	}
	
	return (0);
}

//-------------------------------------------------------------------------------------------
int CniDAQ::NiDaqCountEventsWithinPeriod(const char * str, unsigned long int *data, unsigned int period, char * str2)
{
	int         error=0;
	TaskHandle  taskHandle=0;
	char        errBuff[2048]={'\0'};

    // measure digital events within a specified time period
	// /////////////////////////////////////////////////////


	//-----------------------
	// DAQmx Configure Code
	//-----------------------
	DAQmxErrChk (DAQmxCreateTask("",&taskHandle));
	DAQmxErrChk (DAQmxCreateCICountEdgesChan(taskHandle,str,"",DAQmx_Val_Rising,0,DAQmx_Val_CountUp));
    
	if (str2 != NULL)
	{   // re-assign pin number
        DAQmxSetCICountEdgesTerm(taskHandle, str, str2) ;
	}
    
	//---------------------
	// DAQmx Start Code
	//---------------------
	DAQmxErrChk (DAQmxStartTask(taskHandle));

	Sleep(period) ;
		
	DAQmxErrChk (DAQmxReadCounterScalarU32(taskHandle,DEFAULT_RD_DLY,data,NULL));

Error:
	if( DAQmxFailed(error) )
		DAQmxGetExtendedErrorInfo(errBuff,2048);

	NiDaqKillTask(&taskHandle) ;

	if( DAQmxFailed(error) )
	{
		AfxMessageBox(errBuff) ;
		data = 0 ;
		//throw "Error reading digital input NI-USB-6XXX" ;
	}
		
	return 0;
}

//--------------------------------------------------------------------------------------------
int CniDAQ::NiDaqSetSineOutputVoltage(TaskHandle *taskHandle, char * chnl, float64 freq, float64 value) 
{
	
	// setup sine wave with 200 points per cycle
	//===============================================
#define Npcy 200
	
	int32       error=0;
	float64     data[Npcy];
	char        errBuff[2048]={'\0'};
	int         i=0 ;
    

	for(;i<Npcy;i++)
	{
		data[i] = value*sin((double)i*2.0*PI/Npcy);
	}

	float64 fout = freq * Npcy ;

	//-------------------------
	// DAQmx Configure Code
	//-------------------------
	DAQmxErrChk (DAQmxCreateTask("",taskHandle));
	DAQmxErrChk (DAQmxCreateAOVoltageChan(*taskHandle,chnl,"",-5,5,DAQmx_Val_Volts,NULL));
	DAQmxErrChk (DAQmxCfgSampClkTiming(*taskHandle,"",fout,DAQmx_Val_Rising,DAQmx_Val_ContSamps,Npcy));

	DAQmxErrChk (DAQmxRegisterDoneEvent(*taskHandle,0,CniDAQ::DoneCallback,NULL));

	//-------------------------
	// DAQmx Write Code
	//-------------------------
	DAQmxErrChk (DAQmxWriteAnalogF64(*taskHandle,Npcy,0,10.0,DAQmx_Val_GroupByChannel,data,NULL,NULL));

	//-------------------------
	// DAQmx Start Code
	//-------------------------
	DAQmxErrChk (DAQmxStartTask(*taskHandle));


	// TO DO - calling code needs to stop & clear task when done with use.

Error:
	if( DAQmxFailed(error) )
	{
		DAQmxGetExtendedErrorInfo(errBuff,2048);
	}
	
	return (error);
}

//--------------------------------------------------------------------------------------------
int CniDAQ::NiDaqSetPulseGen(TaskHandle *taskHandle, char * chnl, char * ctr, float64 freq, float64  duty, 
							 uInt32 initDelay, uInt32 edge, const char triggerSource[])
{
	int32   error=0;
	int numSamples=1;

	DAQmxErrChk (DAQmxCreateTask("", taskHandle));
	DAQmxErrChk (DAQmxCreateCOPulseChanFreq(*taskHandle, ctr,"",DAQmx_Val_Hz,DAQmx_Val_Low,0,freq,duty));

    // re-assign pin    
	DAQmxSetCOPulseTerm(*taskHandle, ctr, chnl) ;          

	DAQmxErrChk (DAQmxCfgDigEdgeStartTrig(*taskHandle,triggerSource,edge));
	DAQmxErrChk (DAQmxCfgImplicitTiming(*taskHandle,DAQmx_Val_ContSamps ,numSamples));

	DAQmxStartTask(*taskHandle);

   // TO DO: calling code later stops & clears taskhandle and resets pin-out.

Error:
	return error;
}

//--------------------------------------------------------------------------------------------
int CniDAQ::NiDaqSetTwoPulseGen(TaskHandle *taskHandle, char * chnl0, char * chnl1,
								float64 freq0, float64  duty0, float64 freq1, float64  duty1,
							    uInt32 initDelay0, uInt32 initDelay1,
								uInt32 edge, const char triggerSource[])
{
	// Generate two pulse outputs. chnl0 uses ctr0 and chnl1 uses ctr1
	// ---------------------------------------------------------------

	int32   error=0;
	int numSamples=1;

	DAQmxErrChk (DAQmxCreateTask("", taskHandle));
	DAQmxErrChk (DAQmxCreateCOPulseChanFreq(*taskHandle, CTR0_OUT,"",DAQmx_Val_Hz,DAQmx_Val_Low,0,freq0,duty0));
    DAQmxErrChk (DAQmxCreateCOPulseChanFreq(*taskHandle, CTR1_OUT,"",DAQmx_Val_Hz,DAQmx_Val_Low,0,freq1,duty1));

    // re-assign pin    
	DAQmxSetCOPulseTerm(*taskHandle, CTR0_OUT, chnl0) ;   
	DAQmxSetCOPulseTerm(*taskHandle, CTR1_OUT, chnl1) ; 

	DAQmxErrChk (DAQmxCfgDigEdgeStartTrig(*taskHandle,triggerSource,edge));
	DAQmxErrChk (DAQmxCfgImplicitTiming(*taskHandle,DAQmx_Val_ContSamps,numSamples));

	DAQmxStartTask(*taskHandle);

   // TO DO: calling code later stops & clears taskhandle and resets pin-out.

Error:
	return error;
}

//--------------------------------------------------------------------------------------------
int CniDAQ::NiDaqMeasAnalogSamples(char * RdChnl, float64 *data, float smplRate, 
				unsigned int numSample, bool type, float64 threshold, float64 hyster)
{
	// Read analog numSamples from RdChnl.'type' allows triggering on same channel
	// ////////////////////////////////////////////////////////////////////////////

	int32       error=0;
	int32		read =0;
	TaskHandle  taskHandle=0;
	char        errBuff[2048]={'\0'};

	// DAQmx Configure Code
	//-----------------------
	DAQmxErrChk (DAQmxCreateTask("",&taskHandle));
	DAQmxErrChk (DAQmxCreateAIVoltageChan(taskHandle, RdChnl,"",DAQmx_Val_RSE,-5.0,5.0,DAQmx_Val_Volts,NULL));
	DAQmxErrChk (DAQmxCfgSampClkTiming(taskHandle,"",smplRate,DAQmx_Val_Rising,DAQmx_Val_FiniteSamps,numSample));

    if (type)
	{
	    DAQmxErrChk (DAQmxCfgAnlgEdgeStartTrig(taskHandle,RdChnl,DAQmx_Val_Rising,threshold));
	    DAQmxErrChk (DAQmxSetAnlgEdgeStartTrigHyst(taskHandle, hyster));
	}

	//---------------------
	// DAQmx Start Code
	//---------------------
	DAQmxErrChk (DAQmxStartTask(taskHandle));

	//--------------------- // DEFAULT_RD_DLY
	// DAQmx Read Code
	//---------------------
	DAQmxErrChk (DAQmxReadAnalogF64(taskHandle,-1,DEFAULT_RD_DLY,DAQmx_Val_GroupByChannel,data,numSample,&read,NULL));

Error:
	if( DAQmxFailed(error) )
	{ DAQmxGetExtendedErrorInfo(errBuff,2048);}

	NiDaqKillTask(&taskHandle) ;

	if( DAQmxFailed(error) )
	{
		AfxMessageBox(errBuff) ;
		//throw "Error reading analog input NI-USB-6XXX" ;
	}

	return error;

}

// -------------------------------------------------------------------------------------------
int CniDAQ::NiDaqMeasStepperSamples(char * RdChnl, float64 *data, float smplRate, 
				unsigned int numSample, bool type, float64 threshold, float64 hyster)
{
	// Read analog numSamples from RdChnl.'type' allows triggering on same channel
	// after starting read issue 8051 command and kill task afterward
	// ////////////////////////////////////////////////////////////////////////////

	int32       error=0;
	int32		read =0;
	TaskHandle  taskHandle=0;
	char        errBuff[2048]={'\0'};

	// DAQmx Configure Code
	//-----------------------
	DAQmxErrChk (DAQmxCreateTask("",&taskHandle));
	DAQmxErrChk (DAQmxCreateAIVoltageChan(taskHandle, RdChnl,"",DAQmx_Val_RSE,-5.0,5.0,DAQmx_Val_Volts,NULL));
	DAQmxErrChk (DAQmxCfgSampClkTiming(taskHandle,"",smplRate,DAQmx_Val_Rising,DAQmx_Val_FiniteSamps,numSample));

    if (type)
	{
	    DAQmxErrChk (DAQmxCfgAnlgEdgeStartTrig(taskHandle,RdChnl,DAQmx_Val_Rising,threshold));
	    DAQmxErrChk (DAQmxSetAnlgEdgeStartTrigHyst(taskHandle, hyster));
	}

	//---------------------
	// DAQmx Start Code
	//---------------------
	DAQmxErrChk (DAQmxStartTask(taskHandle));

	//---------------------
	// DAQmx Read Code
	//---------------------
	DAQmxErrChk (DAQmxReadAnalogF64(taskHandle,-1,DEFAULT_RD_DLY,DAQmx_Val_GroupByChannel,data,numSample,&read,NULL));

Error:
	if( DAQmxFailed(error) )
	{ DAQmxGetExtendedErrorInfo(errBuff,2048);}

	NiDaqKillTask(&taskHandle) ;

	if( DAQmxFailed(error) )
	{
		AfxMessageBox(errBuff) ;
		//throw "Error reading analog input NI-USB-XXXX" ;
	}

	return 0;
}
// -------------------------------------------------------------------------------------------
int CniDAQ::NiDaqWriteDacBoardAddr(int module, int addr)
{
	unsigned char value[12];

	// write Addr to module
	// module already selected.
	/////////////////////////////////////////

	CString dev = m_device;
	CString port;
	int error = 0;

	// write address
	if (!error) {
		ConvertDecToDaqCharArray(addr, value, 8);
		port = dev;
		port.Append((LPCTSTR)ADDR_PORT);
		error = NiDaqSetDigitalOutput(port, value);
	}

	// set ALE true
	if (!error) {
		ConvertDecToDaqCharArray(ALE_ADDR, value, 1);
		port = dev;
		port.Append((LPCTSTR)ALE_PORT);
		error = NiDaqSetDigitalOutput(port, value);
	}

	// set CS true
	if (!error) {
		error = StrobeCSelHi();
	}

	// set CS false
	if (!error) {
		error = StrobeCSelLow();
	}

	// set ALE false
	if (!error) {
		ConvertDecToDaqCharArray(ALE_DATA, value, 1);
		port = dev;
		port.Append((LPCTSTR)ALE_PORT);
		error = NiDaqSetDigitalOutput(port, value);
	}

	return error;

}

// -------------------------------------------------------------------------------------------
int CniDAQ::NiDaqWriteDacBoardByte(int module, int addr, int data) 
{
	unsigned char value[12] ;

	// write addr and data byte to module address addr
	// module already selected.
	/////////////////////////////////////////

	CString dev = m_device ;
	CString port ;
	int error = 0;

	// write address
	if(!error) {
		ConvertDecToDaqCharArray(addr, value, 8 ) ;
		port = dev ;
		port.Append((LPCTSTR) ADDR_PORT) ;
		error = NiDaqSetDigitalOutput( port, value) ;
	}

	// set ALE true
    if(!error) {
		ConvertDecToDaqCharArray(ALE_ADDR, value, 1 ) ;
		port = dev ;
		port.Append((LPCTSTR) ALE_PORT) ;
		error = NiDaqSetDigitalOutput(port, value) ;
	}

	// set CS true
	if(!error) {
		error = StrobeCSelHi() ;
	}

	// set CS false
	if(!error) {
		error = StrobeCSelLow() ;
	}

	// set ALE false
    if(!error) {
		ConvertDecToDaqCharArray(ALE_DATA, value, 1 ) ;
		port = dev ;
		port.Append((LPCTSTR) ALE_PORT) ;
		error = NiDaqSetDigitalOutput(port, value) ;
	}

	// write data
    if(!error) {
		ConvertDecToDaqCharArray(data, value, 8 ) ;
		port = dev ;
		port.Append((LPCTSTR) ADDR_PORT) ;
		error = NiDaqSetDigitalOutput(port, value) ;
	}

	// strobe  CS high then back low to latch data & address
    if(!error)
	{
		error = StrobeCsHiLow() ;
	}

	return error ;
}

//--------------------------------------------------------------------------------------------
int CniDAQ::NiDaqReadDacBoardByte(int module, int addr, int * data, bool flag)
{
	unsigned char value[12] ;

	CString dev = m_device ;
	CString port ;

	// read data byte from module at address addr during 2nd CS & !ALE
	// ////////////////////////////////////////////////////////////////

	// set module ID select active for module
	int error = 0;
	if (flag) {
		error = SetModSel(module);
	}

	// write address
	if(!error) {
		ConvertDecToDaqCharArray(addr, value, 8 ) ;
		port = dev ;
		port.Append((LPCTSTR) ADDR_PORT) ;
		error = NiDaqSetDigitalOutput(port, value) ;
	}

	// set ALE true
    if(!error) {
		ConvertDecToDaqCharArray(ALE_ADDR, value, 1 ) ;
		port = dev ;
		port.Append((LPCTSTR) ALE_PORT) ;
		error = NiDaqSetDigitalOutput(port, value) ;
	}

	// set CS true
	if(!error) {
		error = StrobeCSelHi() ;
	}

	Sleep(5);					// ###### let ADC convert complete before reading

	// set CS false
	if(!error) {
		error = StrobeCSelLow() ;
	}

	// set ALE false
	if (!error) {
		ConvertDecToDaqCharArray(ALE_DATA, value, 1);
		port = dev;
		port.Append((LPCTSTR)ALE_PORT);
		error = NiDaqSetDigitalOutput(port, value);
	}

	// set CS true
	if (!error) {
		error = StrobeCSelHi();
	}

	// read data from DOUT port
	if (!error) {
		port = dev;
		port.Append((LPCTSTR)DOUT_UPR_PORT);
		port.Append(dev);
		port.Append((LPCTSTR)DOUT_LWR_PORT);
		error = NiDaqMeasPortDigitalInput(port, (unsigned long *)data);
	}

	// set CS false
	if (!error) {
		error = StrobeCSelLow();
	}


	// set module ID select inactive for module
	if (flag)
	{
		error = SetModSel(NULL_MODULE);  // NULL module
	}

	return error ;
}

//---------------------------------------------------------------------------------------------
int CniDAQ::NiDaqReadDacBoardAdc(int module, int chan, int * data, bool type)
{
	// read 12-bit adc chan data from module
	/////////////////////////////////////////////////
	// unsigned char value[12] ;

	// read data byte from module sensor at address addr
	// --- set ADC channel mux in FPGA if type==TRUE (default)
	// --- start convert & read back adc value
	int error = 0;

	// set module ID select active for module
	if (SetModSel(module))
	{
		error = -1;
		return error;
	}

	if (type)
	{
		error = NiDaqWriteDacBoardByte(module, CMD_ADC_MUX, chan);
	}

	if (!error) {
		error = NiDaqReadDacBoardAdcChan(module, CMD_ADC_CNVRT, data);
	}

	return error;
}

// ---------------------------------------------------------------------------------------------
int CniDAQ::NiDaqReadDacBoardAdcChan(int module, int addr, int * data)
{
	// Command to start ADC convert & reading of chan
	// need to select module prior to ADC convert

	int error = 0;
	SetModSel(module);
#ifndef DEBUG_NO_NIDAQ
	error = NiDaqReadDacBoardByte(module, (CMD_ADC_CNVRT), data, false);
	SetModSel(NULL_MODULE);
#endif

	return error;
}

// --------------------------------------------------------------------
int CniDAQ::NiDaqWriteDacBoardWord(int module, int addr, int chan, int data)
{
	// write two-byte word to module (16-bit)
	// //////////////////////////////////////////

	// TO DO  fix
	// 

	int error = 0;

	// set module ID select active for module
	if (SetModSel(module))
	{
		error = -1;
		return error;
	}
    // ------------------------------------------------------
	// fix below
	// write addr and data byte to module address addr
	// module already selected.
	/////////////////////////////////////////

	CString dev = m_device;
	CString port;
	unsigned char value[12];

	// write address
	if (!error) {
		ConvertDecToDaqCharArray(addr, value, 8);
		port = dev;
		port.Append((LPCTSTR)ADDR_PORT);
		error = NiDaqSetDigitalOutput(port, value);
	}

	// set ALE true
	if (!error) {
		ConvertDecToDaqCharArray(ALE_ADDR, value, 1);
		port = dev;
		port.Append((LPCTSTR)ALE_PORT);
		error = NiDaqSetDigitalOutput(port, value);
	}

	// set CS true
	if (!error) {
		error = StrobeCSelHi();
	}

	// set CS false
	if (!error) {
		error = StrobeCSelLow();
	}

	// set ALE false
	if (!error) {
		ConvertDecToDaqCharArray(ALE_DATA, value, 1);
		port = dev;
		port.Append((LPCTSTR)ALE_PORT);
		error = NiDaqSetDigitalOutput(port, value);
	}

	// write 1st data byte (MSB) 
	if (!error) {
		ConvertDecToDaqCharArray(((data>>8) & 0xFF), value, 8);
		port = dev;
		port.Append((LPCTSTR)ADDR_PORT);
		error = NiDaqSetDigitalOutput(port, value);
	}

	// strobe  CS high then back low to latch data
	if (!error)
	{
		error = StrobeCsHiLow();
	}

	// write 2nd data byte (LSB)
	if (!error) {
		ConvertDecToDaqCharArray((data & 0xFF), value, 8);
		port = dev;
		port.Append((LPCTSTR)ADDR_PORT);
		error = NiDaqSetDigitalOutput(port, value);
	}

	// strobe  CS high then back low to latch data
	if (!error)
	{
		error = StrobeCsHiLow();
	}

	// set module ID select inactive for module
	error = SetModSel(NULL_MODULE);  // NULL module

	return error;

}

// --------------------------------------------------------------------
int CniDAQ::NiDaqReadDacBoardWord(int module, int addr, int chan, int * data, bool flag)
{
	// read two-byte word from module addr (16-bit)
	// This routine selects module if flag is true
	// ////////////////////////////////////////////

	unsigned char value[12];

	CString dev = m_device;
	CString port;

	// read two data bytes from module at address addr & chan
	// //////////////////////////////////////////////////////

	// set module ID select active for module
	int error = 0;
	if (flag) {
		error = SetModSel(module);
	}

	// write address
	if (!error) {
		ConvertDecToDaqCharArray(addr + chan, value, 8);
		port = dev;
		port.Append((LPCTSTR)ADDR_PORT);
		error = NiDaqSetDigitalOutput(port, value);
	}

	// set ALE true
	if (!error) {
		ConvertDecToDaqCharArray(ALE_ADDR, value, 1);
		port = dev;
		port.Append((LPCTSTR)ALE_PORT);
		error = NiDaqSetDigitalOutput(port, value);
	}

	// set ALE false
	if (!error) {
		ConvertDecToDaqCharArray(ALE_DATA, value, 1);
		port = dev;
		port.Append((LPCTSTR)ALE_PORT);
		error = NiDaqSetDigitalOutput(port, value);
	}

	// read MSB byte data from DOUT port
	//

	// set CS true
	if (!error) {
		error = StrobeCSelHi();
	}
	Sleep(5);					// ###### let ADC convert complete before reading

	int result = 0;
	if (!error) {
		port = dev;
		port.Append((LPCTSTR)DOUT_UPR_PORT);
		port.Append(dev);
		port.Append((LPCTSTR)DOUT_LWR_PORT);
		error = NiDaqMeasPortDigitalInput(port, (unsigned long *)data);
		result = ((*data) & 0xFF) << 8;
	}

	// set CS false
	if (!error) {
		error = StrobeCSelLow();
	}

	// -----------------------------------
	// read LSB byte data from DOUT port
	//

	// set CS true
	if (!error) {
		error = StrobeCSelHi();
	}

	if (!error) {
		port = dev;
		port.Append((LPCTSTR)DOUT_UPR_PORT);
		port.Append(dev);
		port.Append((LPCTSTR)DOUT_LWR_PORT);
		error = NiDaqMeasPortDigitalInput(port, (unsigned long *)data);
		result += ((*data) & 0xFF);
		*data = result;
	}

	// set CS false
	if (!error) {
		error = StrobeCSelLow();
	}

	// set module ID select inactive for module
	if (flag)
	{
		error = SetModSel(NULL_MODULE);  // NULL module
	}
	return error;

}
//---------------------------------------------------------------------
// ////////////////////////////////////////////////////////////////////
//
// utilities
//
// --------------------------------------------------------------------
int CniDAQ::SetModSel( int module)
{
	// DAC board MOD_SEL is active high on two encoded bits
	// this routine sets bits per module ID

	unsigned char value[4] ;

	CString dev = m_device ;
	CString port ;

	int error = GetModSelValue(module, value) ;
#ifndef DEBUG_NO_NIDAQ
	port = dev ;
	port.Append((LPCTSTR) MOD_SEL_PORT) ;    
	error = NiDaqSetDigitalOutput(port, value) ;
#endif

	return error ;
}

// --------------------------------------------------------------------------
int CniDAQ::StrobeCSelHi(void)
{
    // DAC board CS is active high
	// This rountine sets the prescribed bit high (active)
	
	unsigned char result[16] ;

	CString dev = m_device ;
	CString port ;

	ConvertDecToDaqCharArray(HIGH, result, 1 ) ;
	port = dev ;
	port.Append((LPCTSTR) MOD_CS_PORT) ;        
	int error = NiDaqSetDigitalOutput(port, result) ;

	Sleep(1) ;

	return error ;
}

// --------------------------------------------------------------------------
int CniDAQ::StrobeCSelLow(void)
{
    // DAC board CS is active high
	// This rountine sets the prescribed bit low (in-active)
	
	unsigned char result[16] ;

	CString dev = m_device ;
	CString port ;

	ConvertDecToDaqCharArray(LOW, result, 1 ) ;
	port = dev ;
	port.Append((LPCTSTR) MOD_CS_PORT) ;    
	int error = NiDaqSetDigitalOutput(port, result) ;

	return error ;
}

//---------------------------------------------------------------------------
int CniDAQ::StrobeCsHiLow(void)
{
	int error = StrobeCSelHi() ;
	if(!error) {
		error = StrobeCSelLow() ;
	}

	return error ;
}
// --------------------------------------------------------------------------
int CniDAQ::GetModSelValue(int module, unsigned char * value)
{
	// convert logical module # {0,1,2,3} to NiDAQ channel name
	// note bit order reversed ...

    // initialize to in-active 
	value[0]= 0;         // ########## 
	value[1]= 0;

	int error = 0;

	switch (module)
	{
	case 0:
		value[0] = 1 ;
		value[1] = 0 ;
		break;
	case 1:
		value[0] = 0 ;
		value[1] = 1 ;
		break;
	case 2:
        value[0] = 1 ;  
		value[1] = 1 ;
		break;
	case 3:             // NULL module
		value[0] = 0;
		value[1] = 0;
		break;
	default:
		// in-active
		error = 1 ;
		CString str = "Error: Invalid module # in GetModSelValue" ; 
		AfxMessageBox(str) ;
		break;
	}

	return error ;
}

//--------------------------------------------------------------------------------------------
int CniDAQ::ConvertDecToDaqCharArray(unsigned int input, unsigned char *result, int size )
{
    // converts an unsigned decimal number to a unsigned char array in NI DAQ format
	// for example input= 30, result= {0,1,1,1,1}. Note LSB of input is first char.
	// valid values for result are (0,1).
	// /////////////////////////////////////////////////////////////////////////////

    int i ;
	for(i=0; i<size; i++)
	{
		result[i]= 0;
	}

	for (i=0; i<size; i++)
	{
        int j = i ;
		int val = input & 1;
		if(val)
		{
			result[j] = 1 ;
		}
		else
		{
			result[j] = 0 ;
		}

		input = input >> 1 ;
	}
	result[size] = '\0' ;

	return (0) ;
}

//---------------------------------------------------------------------------------------------
int32 CVICALLBACK CniDAQ::DoneCallback(TaskHandle taskHandle, int32 status, void *callbackData)
{
	int32   error=0;
	char    errBuff[2048]={'\0'};

	// Check to see if an error stopped the task.
	DAQmxErrChk (status);

Error:
	if( DAQmxFailed(error) ) {
		DAQmxGetExtendedErrorInfo(errBuff,2048);
		DAQmxClearTask(taskHandle);
		printf("DAQmx Error: %s\n",errBuff);
	}
	return 0;
}

// --------------------------------------------------------------------------------------------
int CniDAQ::NiDaqKillTask(TaskHandle * taskHandle)
{
	if( taskHandle!=0 ) 
	{
	   //------------------
	   // DAQmx Stop Code
	   //------------------
	   if(DAQmxStopTask(*taskHandle))
	   {
		   return (-1) ;
	   }
	   if(DAQmxClearTask(*taskHandle))
	   {
		   return (-1) ;
	   }

	   return (0) ;
	}
	else
	{
		return (-1) ;
	}

}

// --------------------------------------------------------------------------------------------
int CniDAQ::NiDaqResetTerm(TaskHandle *taskHandle, const char channel[] )
{
	int retVal = 0 ;

    retVal= DAQmxResetCOPulseTerm(*taskHandle, channel) ;

	return (retVal) ;

}
