// Copyright 2013 Prysm Inc.
// San Jose, CA, 95134
// btremaine@prysm.com
//
//
// Common.h : common header file for the CBoardTest.cpp
//

#define HARDWARE_INSTALLED 1
#undef DEBUG_NO_NIDAQ
//#define DEBUG_NO_NIDAQ

#ifdef DEBUG_NO_NIDAQ
#undef HARDWARE_INSTALLED
#endif


	enum State {
		IDLE = 0,     // Channel idle, heater may or maynot be on
		PAUSED,       // data collection paused
		RUNNING       // data collection running
	};

	enum rackID {
		ONE = 1,
		TWO,
		THREE
	} ;

	enum TC_ID {
		TC1 = 0,
		TC2 = 1,
		TC3 = 2,
		TC4 = 3,
		TC5 = 4,
		TC6 = 5,
		TC7 = 6,
		TC8 = 7,
		TCE = 8    // # of temp sensors
	};

	enum HTR_ID {
		HTR1 = 0,
		HTR2 = 1,
		HTR3 = 2,
		HTR4 = 3,
		HTRE = 4  // # of heater
	};

	enum OP_MODE {
		AUTO_MODE = 0,
		TEST1_MODE,
		TEST2_MODE,
		IDLE_MODE
	};

	enum VoltID {
		DEV0 = 0,
		DEV1,
		DEV2,
		DEV3,
		DEV4,
		DEV5,
		DEV6,
		DEV7,
		DEV8,
		DEV9,
		DEV10,
		DEV11,
		DEV12,
		DEV13,
		DEV14,
		DEV15,
		DEV16,
		DEV17,
		DEV18,
		DEV19,
		ANLG20,
		ANLG21,
		ANLG22,
		HV_ANLG,
		NUM_VOLTAGES
	};

	enum STAT_ID {



	};

	enum HT_WORD {
		HT1 = 0,
		HT2,
		HT3
	};

	enum ServoID  {
		ID_DBND,
		ID_TMR,
		ID_TON,
		ID_TOFF
	};



#define	MSTR_TIMER_ID	1
