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
	int GetStatus(int module, int id, int * val) ;			// not completed
	int SetHvDac(int module, int val, bool fp= true) ;
	int SetIalarm(int module, int val, bool fp=true) ;
	int SetGate(int module, int fp_value, bool fp= true);
	int SetHvChanEn(int module, int chan, bool state);
	int SetTref(int module, enum HTR_ID htr, int val) ;
	int SetServoParam(int module, enum ServoID, unsigned char val);
	int ReadHTword(int module, HT_WORD ht, int * val);
	int ReadAnlg(int module, VoltID ch, int * val);
	int ReadStatus(int module, int * stat );				// not implemented
	int ReadILEAK(int module, int chan, int * val) ;
	int ReadTref(int module, enum HTR_ID htr, int * val) ;
	int ReadTemp(int module, enum TC_ID TC, int * val) ;
	int EnableTcServos(int module);
	int DisableTcServos(int module);

	int LoadSelectedDeviceConfig(int module, int Ndut);
	int LoadConfigToFpga (int module ) ;
	
	int ReadSensorChan(int module, int chan, int * val ) ;
	int ReadModuleSensorChan(int module, int chan, int * val);
	int CheckNiDAQ(void) ;
	int SetModSel(int);
	int CalTref2TC(int value, HTR_ID j, int module);
	int CalTC2Temp(int value, TC_ID j, int module);
	int CnvrtTCref2TREF(int value, HTR_ID j, int module);

	// Wishbone I2C funcs
	int WrtTXR(int module, int value);
	int WrtCR(int module, int value);
	int SetCTL(int module, int value);
	int ReadSR(int module, int * val);
	int EnableWBport(int module);
	int SetPreLo(int module, int value);
	int SetPreHi(int module, int value);
	int ReadI2C(int module, int i2c_reg, int * data);
	int WriteI2C(int module, int i2c_reg, int data);
	int SendSlaveAddr(int module, int slave_addr, bool flag );
	int getACK(int module, int * data);
	int getTIP(int module, int * data);

	int getI2Cbyte(int module, int * val);

	int InitI2CModule(int module);
	int WriteI2C_Reg(int module, unsigned char  reg, unsigned char data);
	int ReadI2C_Byte(int module, unsigned char  reg, unsigned char* data);
	int WriteI2C_DblByte(int module, unsigned char reg, int data);
	
	int ReadTempChan(int module, unsigned char chan, int * data);
	int ReadTrefChan(int module, unsigned char chan, int * data);
	int ReadI2CVersion(int module, int * data);


	int ReadI2C_DblByte(int module, unsigned char reg, int* data);  // Needs debug, not working

// wishbone IO

#define I2CADDR 0xAA

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
		CMD_TEMP2, 
		CMD_TEMP3,
		CMD_TEMP4, 
		CMD_TEMP5, 
		CMD_TEMP6, 
		CMD_TEMP7, 
		CMD_TREF0, 
		CMD_TREF1,
		CMD_TREF2, 
		CMD_TREF3, 
		CMD_TOFST0,
		CMD_TOFST1,
		CMD_TOFST2,
		CMD_TOFST3,
		CMD_TOFST4,
		CMD_TOFST5,
		CMD_TOFST6,
		CMD_TOFST7,
		CMD_DBND, 
		CMD_TMR_CNT, 
		CMD_TON_CNT, 
		CMD_TOFF_CNT,
		CMD_TEMP0_LSB,
		CMD_TEMP0_MSB,
		CMD_TEMP1_LSB,
		CMD_TEMP1_MSB,
		CMD_TEMP2_LSB,
		CMD_TEMP2_MSB,
		CMD_TEMP3_LSB,
		CMD_TEMP3_MSB,
		CMD_TEMP4_LSB,
		CMD_TEMP4_MSB,
		CMD_TEMP5_LSB,
		CMD_TEMP5_MSB,
		CMD_TEMP6_LSB,
		CMD_TEMP6_MSB,
		CMD_TEMP7_LSB,
		CMD_TEMP7_MSB,
		CMD_TREF0_LSB,
		CMD_TREF0_MSB,
		CMD_TREF1_LSB,
		CMD_TREF1_MSB,
		CMD_TREF2_LSB,
		CMD_TREF2_MSB,
		CMD_TREF3_LSB,
		CMD_TREF3_MSB,
		CMD_VERSION_LSB,
		CMD_VERSION_MSB
	};

	enum TC_CH {
		TC_CH0 = 0,
		TC_CH1,
		TC_CH2,
		TC_CH3,
		TC_CH4,
		TC_CH5,
		TC_CH6,
		TC_CH7
	};

	enum TC_REF {
		TC_REF0 = 0,
		TC_REF1,
		TC_REF2,
		TC_REF3
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
#define GT_COEFF0    (139.0)
#define GT_COEFF1    (-5.969)
// leakage (uAmps)
#define ALRM_DEFAULT (100*UA2TEN_NA)
#define ILK_DEFAULT  (0.1*UA2TEN_NA)
#define ILK_COEFF0   (120)
#define ILK_COEFF1   (2.35)
// temperature
#define HEATER_DEFAULT (false)
#define TMAX_LIMIT   (205*FLOAT2FXD)
#define TREF_DEFAULT (50*FLOAT2FXD)

#define TREF_COEFF0  (125.0)
#define TREF_COEFF1  (15.0)
#define TEMP_CAL0    (0.00)
#define TEMP_CAL1    (1.00)
#define TREF_CAL0    (0.00)
#define TREF_CAL1    (1.00)
// TC servo
#define TC_CNTR		(50)			// PIC ISR counts/cycle
#define TC_DBND	    (5)				// Temp dead_band: degC << 5  ?? verify
#define TC_TOFF		(10)			// PIC ISR counts min OFF
#define TC_TON		(40)			// PIC ISR counts max ON

// I2C
#define I2C_TIP_WAIT (6)

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

	float m_hv_set_b1[Nmod] ;		  // HV_COEFF1
	float m_hv_set_b0[Nmod];		  // HV_COEFF0

	float m_hv_rd_b0[Nmod];		  // A0_ADC2HV  % convert HV ADC to float HV
	float m_hv_rd_b1[Nmod];       // A1_ADC2HV

	float m_gate_b1[Nmod];        // GT_COEFF1
	float m_gate_b0[Nmod];		  // GT_COEFF0

	float m_alarm_b0[Nmod];       // ILK_COEFF0
	float m_alarm_b1[Nmod];       // ILK_COEFF1

	float m_temp_b0[Nmod][TCE] ;    // TEMP_CAL0   % convert TC reading to calibrated temp
	float m_temp_b1[Nmod][TCE];     // TEMP_CAL1

	float m_tempref_b0[Nmod][HTRE] ; // TREF_CAL0   % convert GUI TREF to calibrated TC TREF
	float m_tempref_b1[Nmod][HTRE] ; // TREF_CAL1

	int m_tc_cntr ;
	int m_tc_dbnd ;
	int m_tc_toff_min ;
	int m_tc_ton_max ;


	ModuleT Module[Nmod] ;


protected:



};
#endif