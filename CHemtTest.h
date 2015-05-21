// Copyright 2013 Prysm Inc.
// San Jose, CA, 95134
// btremaine@prysm.com
// btremaine@omnificsolutions.com
//
// CHemtTest.h : header file
//

#if !defined __MBT
#define __MBT

// Class for EUT testing
#include "niDAQ.h"
#include "DacBoardIO.h"
#include "common.h"
#include "math.h"

#define HARDWARE_INSTALLED 1
#undef DEBUG_NO_NIDAQ



class CHemtTest : public CWnd
{

public:
	CHemtTest(CString serial_num);

public:

	CniDAQ * niDAQwrap ;
	CDacBoardIO * CDacIO ;

	void InitModuleDefault(void) ;
	int SetHvEnable(int module, bool val) ;

	int SetAnlgMux(int module, int mux, int chan);
	int SetThrGain(int module, bool value);
	int GetStatus(int module, int id, int * val) ;
	int SetHvDac(int module, int val, bool fp= true) ;
	int SetIalarm(int module, int val, bool fp=true) ;
	int SetGate(int module, int fp_value, bool fp= true);
	int SetHvChanEn(int module, int chan, bool state);
	int SetTref(int module, enum HTR_ID htr, int val) ;
	int SetServoParam(int module, enum ServoID, unsigned char val);
	int EnableTcServo(int module, int chan, bool fp);

	int ReadHTword(int module, HT_WORD ht, int * val);
	int ReadAnlg(int module, VoltID ch, int * val);
	int ReadStatus(int module, int * stat );
	int ReadILEAK(int module, int chan, int * val) ;
	int ReadTref(int module, enum HTR_ID htr, int * val) ;
	int ReadTemp(int module, enum TC_ID TC, int * val) ;

	int LoadSelectedDeviceConfig(int module, int Ndut);
	int LoadConfigToFpga (int module ) ;
	
	int ReadSensorChan(int module, int chan, int * val ) ;
	int ReadModuleSensorChan(int module, int chan, int * val);
	int CheckNiDAQ(void) ;
	int SetModSel(int);

	// Wishbone I2C funcs
	int SetTXR(int module, int value);
	int SetCR(int module, int value);
	int SetCTL(int module, int value);
	int ReadSR(int module, int * val);
	int EnableWBport(int module);
	int SetPreLo(int module, int value);
	int SetPreHi(int module, int value);
	int ReadI2C(int module, int i2c_reg, int * data);
	int WriteI2C(int module, int i2c_reg, int data);
	int SendSlaveAddr(int module, int slave_addr, bool flag );

	int InitI2CModule(int module);
	int WriteI2C_Reg(int module, unsigned char  reg, unsigned char data);


// wishbone IO

#define I2CADDR 0xAE

	enum wb_reg {
		PRElo = 0x00,   // R/W
		PREhi = 0x01,   // R/W
		CTL =	0x02,   // R/W
		TXR =	0x03,   // W
		RXR =	0x03,   // R
		CR =	0x04,   // W
		SR =	0x04    // R
	};

	enum TC_CMD {
		CMD_NONE = 0, 
		CMD_SSR_ENB, 
		CMD_TEMP0, 
		CMD_TEMP1, 
		CMD_TEMP3, 
		CMD_TEMP4,
		CMD_TEMP5, 
		CMD_TEMP6, 
		CMD_TEMP7, 
		CMD_TREF0, 
		CMD_TREF1, 
		CMD_TREF2,
		CMD_TREF3, 
		CMD_DBND, 
		CMD_TMR_CNT, 
		CMD_TON_CNT, 
		CMD_TOFF_CNT
	};



#define FLOAT2FXD (10)
#define UA2TEN_NA (100)

#define Ndut (20)
#define Nmod (3)
// HV voltage dac counts
#define HV_LIMIT     (1100.0)
#define HV_DEFAULT   (600*FLOAT2FXD)
#define HV_COEFF0    (-140.0)   // okay board #2
#define HV_COEFF1    (0.2829)   // 

#define A0_ADC2HV    (0.00000)  // okay board #2
#define A1_ADC2HV    (0.51500)  // 

// gate voltage 
#define GTE_DEFAULT  (-3.0*FLOAT2FXD)
#define GT_COEFF0    (140.7)
#define GT_COEFF1    (-7.6293)
// leakage (uAmps)
#define ALRM_DEFAULT (100*UA2TEN_NA)
#define ILK_DEFAULT  (0.1*UA2TEN_NA)
#define ILK_COEFF0   (120)
#define ILK_COEFF1   (2.35)
// temperature
#define TMAX_LIMIT   (205*FLOAT2FXD)
#define TREF_DEFAULT (50*FLOAT2FXD)
#define TREF_COEFF0  (125.0)
#define TREF_COEFF1  (15.0)
// time increment in msec
#define TIME_INCR   (60000)
// ADC scaling
#define ADC2ILK_LOW_GN  (0.40290)
#define ADC2ILK_HI_GN   (0.04029)



#define SETUP1 20


#define NUM_AVG_ADC (1)

#define ANLG_CHAN20 (20)
#define ANLG_CHAN21 (21)
#define ANLG_CHAN22 (22)
#define HVREF_CHAN  (23)

#define NUM_HTRS   (4)

	struct ModuleT {
		int state ;               // see enum STATE
		int HV ;                  // drain voltage, tenths of a volt  (setting)
		int gate;                 // gate voltage, tenths of a volt   (setting)
		int Alarm;                // hardware alarm value, tens of nA (setting)
		float thr_gain;           // Alarm threshold gain             (setting)
		int IlkLim[Ndut] ;        // software threshold, tens of nA   (setting)
		int TREF[NUM_HTRS] ;      // tenths of deg C                  (setting)
		int TMEA[TCE];            // tenths of deg C                  (measured)
		bool Enable[Ndut] ;       // enable/disable HV chan 
		bool Heater[NUM_HTRS];    // enable/disable temp control 
		int lastVal[Ndut];        // measured leakage, tens of nA     (measured)
		int HVref;                // HV voltage, tenths of a volt     (measured)
		int op_mode ;
        SYSTEMTIME st ;           // system time at start
		ULONGLONG tick_start;     // system tick count at start
		ULONGLONG ET;             // elapsed time in msec
		ULONGLONG resTime[Ndut];  // resume time in msec
		ULONGLONG totTime[Ndut];  // total time in msec
		CString runComment ;      // run comment
		CString SampleID[Ndut];   // Sample ID comment
		rackID rack ;             // rack #
	};	

	int m_active_module ;         // current active module for GUI interface
	int m_NIDAQ_absent ;          // status of NiDaq presence
	int m_timer_status ;          // true==1 if master timing running, otherwise false==0

	ModuleT Module[Nmod] ;


protected:



};
#endif