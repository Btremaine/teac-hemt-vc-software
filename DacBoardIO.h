// Copyright 2013 Prysm Inc.
// San Jose, CA, 95134
// btremaine@prysm.com
// btremaine@omnificsolutions.com
//
// DacBoardIO.h
//
#pragma once

#include "niDAQ.h"

// modified 12/16/2013 to keep device name dynamic & separate from the port names
#define ADDR_PORT         "/port2/line0:7"
// #define DOUT_PORT         "/port1/line0:7,/Dev1/port0/line0:3"
#define DOUT_UPR_PORT     "/port1/line0:7,/"
#define DOUT_LWR_PORT     "/port0/line0:3"

#define MOD_SEL_PORT      "/port0/line4:5"
#define MOD_CS_PORT       "/port0/line6"
#define ALE_PORT          "/port0/line7"
// generic ports
#define PORT0			  "/port0/line0:7"
#define PORT1			  "/port1/line0:7"
#define PORT2			  "/port2/line0:7"

#define ALE_ADDR	      1
#define ALE_DATA 		  0

// verified working 9/6/2015

#define CMD_HV_ONOFF	(0 << 2)  // cmd + 1 byte, w only,
#define CMD_GAIN		(1 << 2)  // cmd + 1 byte, w only,
#define CMD_HV_DAC		(2 << 2)  // cmd + 1 byte, w only,
#define CMD_BIAS_DAC	(3 << 2)  // cmd + 1 byte, w only,
#define CMD_THR_DAC		(4 << 2)  // cmd + 1 byte, w only,
#define CMD_HVCHN_ENBL	(5 << 2)  // cmd + 1 byte, w only,
#define CMD_ADC_MUX		(6 << 2)  // cmd + 1 byte, w only, 
#define CMD_ADC_CNVRT	(7 << 2)  // cmd + 1 byte, w only, 
// i2c
#define CMD_TXR_REG	    (8 << 2)  // cmd + 1 byte, w only, 
#define CMD_CR_REG		(9 << 2)  // cmd + 1 byte, w only, 
#define CMD_CTL_REG	    (10 << 2) // cmd + 1 byte, w only, 
#define CMD_SR_REG		(11 << 2) // cmd + 1 byte, w only, 
//
#define	CMD_STATUS		(12 << 2) // cmd + ? bytes, r only,
#define CMD_HVT_WD1     (13 << 2) // cmd + 1 byte, r only,
#define CMD_HVT_WD2     (14 << 2) // cmd + 1 byte, r only,
#define CMD_HVT_WD3     (15 << 2) // cmd + 1 byte, r only,
// more i2c
#define  CMD_PRELO_REG  (16 << 2)
#define  CMD_PREHI_REG  (17 << 2)
#define  CMD_RDRXR_REG  (18 << 2)


//
#define RD_HV_ADDR        ( 0 )

//
#define ID_GATE_REG      (0x01)
#define ID_HV_REG        (0x02)
#define ID_THR_REG       (0x03)

// Temperature control registers
#define ID_TREF0_REG     (0x00)
#define ID_TREF1_REG     (0x01)
#define ID_TREF2_REG     (0x02)
#define ID_TREF3_REG     (0x03)
#define ID_TON_REG       (0x04)
#define ID_TOFF_REG      (0x05)
#define ID_TDBND_REG     (0x06)


// ADC mux-select
#define ADC_MUX0
#define ADC_MUX1
#define ADC_MUX2
#define ADC_MUX3
#define ADC_MUX4
#define ADC_MUX5
#define ADC_MUX6
#define ADC_MUX7
#define ADC_MUX8
#define ADC_MUX9
#define ADC_MUX10
#define ADC_MUX11
#define ADC_MUX12
#define ADC_MUX13
#define ADC_MUX14
#define ADC_MUX15
#define ADC_MUX16
#define ADC_MUX17
#define ADC_MUX18
#define ADC_MUX19

#define NO_NIDAQ_HV   (3600)
#define NO_NIDAQ_ILK  (1800)
#define NO_NIDAQ_TREF (1800)
#define NO_NIDAQ_TJ   (1815)
#define NO_NIDAQ_ADC  (4000)

class CDacBoardIO
{
	// construction
public:
	CDacBoardIO();
	~CDacBoardIO();

	// Operations
public:

	CniDAQ * niDAQwrap ;

	int ReadDataByte(int module, int addr, int * data) ;    // reads data during first ALE/CS
	int WriteDataByte(int module, int addr, int data) ;
	int ReadDataChanByte(int module, int addr, int chan, int * data, bool flag) ;
	int ReadDataChanWord(int module, int addr, int chan, int * data, bool flag);
	int WriteDataChanWord(int module, int addr, int chan, int data);
	int ReadAdcChan(int module, int chan, int * value, bool type=true) ;
	int SetDigOutType(const char * chnl, bool iotype) ;
	int SetAltOutChnls(bool iotype) ;
	int SetNiDaqChnl(const char *chnl, int value) ;
};
