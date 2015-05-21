// Copyright 2013 Prysm Inc.
// San Jose, CA, 95134
// btremaine@prysm.com
// btremaine@omnificsolutions.com
//
// CDacBoardIO.cpp
//

#include "stdafx.h"
#include "DacBoardIO.h"
#include "common.h"

CDacBoardIO::CDacBoardIO(void)
{
// This class performs all IO with the FPGA boards in the Ndut test system.
// each rack can have up to 3 modules. All modules are attached to the 
// parallel bus which has data/address and control signals. In this version
// there is a 8-bit multiplexed address/data bus to the FPGA and a 12-bit
// data bus from the FPGA
//
// DOUT[11..0]       data output:
//		DOUT[7..0]   output from FPGA									NiDAQ P1[7..0]
//		DOUT[11..8]  output from FPGA									NiDAQ P0[3..0]
//
// ADDR[7:0]    address/data lines to FPGA								NiDAQ P2[7..0]
//	ADDR[7:2]	ADDR[1:0]		ADDR[7:0]	ADDR[7:0]	ADDR[7:0]	
//	cmd			modifier	# data bytes	data byte1	data byte2	data byte3	mode

//  -------------------------------------------------------------------------------
//	ADDR[7:2]		ADDR[1:0]		ADDR[7:0]	ADDR[7:0]	ADDR[7:0]																																																																																																																																																																																																																																																								
//	cmd		modifier	# data bytes	databyte 1	databyte 2	databyte 3	mode	I2C ?	Base cmnd NI GUI																																																																																																																																																																																																																																																					
//	0	HV on/off cntl	-	1			d[0]		n/a			n/a			w		n																																																																																																																																																																																																																																																						
//	1	gain	-			1			d[0]		n/a			n/a			w		n																																																																																																																																																																																																																																																						
//	2	hv dac	-			1			dac value	n/a			n/a			w		n																																																																																																																																																																																																																																																						
//	3	bias dac	-		1			dac value	n/a			n/a			w		n																																																																																																																																																																																																																																																						
//	4	thresh dac (alarm)	-	1		dac value	n/a			n/a			w		n																																																																																																																																																																																																																																																						
//	5	chan enable [19:0]	-	1		chan #		n/a			n/a			w		n																																																																																																																																																																																																																																																						
//	6	adc mux sel	-		1			chan #		n/a			n/a			w		n																																																																																																																																																																																																																																																						
//	7	adc convrt	-		0			n/a			n/a			n/a			w		n																																																																																																																																																																																																																																																						
//	8	set TXR reg																																																																																																																																																																																																																																																													
//	9	set CR reg																																																																																																																																																																																																																																																													
//	10	set_CTL																																																																																																																																																																																																																																																													
//	11	set_SR																																																																																																																																																																																																																																																													
//	12	set_status																																																																																																																																																																																																																																																													
//	13																																																																																																																																																																																																																																																														
//	14																																																																																																																																																																																																																																																														
//	15																																																																																																																																																																																																																																																														
//	16																																																																																																																																																																																																																																																														
//
// ALE            address latch enable to FPGA, selects address/data	NiDAQ P0.7
// CS             chip select, strobe active high						NiDAQ P0.6
// MOD_SEL[1:0]   module select enable                          		NiDAQ P0.[5..4]
//
// module board ID is ID2:ID0

// process is in general for write is (assume CS is in-active)
//   set up address
//   set up module_sel ID
//   set ALE to FPGA
//   strobe CS active then in-active
//   set up data
//   strobe CS active then inactive
//
// process for read is: (assume mod_sel is inactive)
//   setup up address
//   set up module_sel ID
//   set ALE to FPGA
//   strobe CS high
//   read data from FPGA
//   strobe CS low
//   strobe mod_sel to active

}


CDacBoardIO::~CDacBoardIO()
{
}
// --------------------------------------------------------------------
int CDacBoardIO::WriteDataByte(int module, int addr, int data)
{
	// writes 8-bit byte to module (generic)
	int error = 0;

#ifndef DEBUG_NO_NIDAQ
	// set module ID select active for module

	if (niDAQwrap->SetModSel(module))
	{
		error = -1;
		return (error);
	}
	
	if (niDAQwrap->NiDaqWriteDacBoardByte(module, addr, data))
	{
		error = -1;
		return (error);
	}

	if (niDAQwrap->SetModSel(NULL_MODULE))
	{
		error = -1;
		return (error);
	}

#endif
	return error;

}
// --------------------------------------------------------------------
int CDacBoardIO::ReadDataByte(int module, int addr, int * data)
{
	// read 8-bit byte from module (generic)
	int stat = 0;
#ifndef DEBUG_NO_NIDAQ
	// flag ture if module to be selected else false
	bool flag = true;
	stat = niDAQwrap->NiDaqReadDacBoardByte(module, addr, data, flag) ;
#endif
	return stat ;
}
// --------------------------------------------------------------------
int CDacBoardIO::ReadAdcChan(int module, int chan, int * data, bool type)
{
	// read 12-bit word from ADC channel of module
	//
	// module: module #
	// chan: analog channel # if not already selected
	// data: pointer to adc data
	// type: default TRUE to select mux channel, FALSE mux is already set

	// set sensor board mux & sel lines if needed then read serial adc

	int stat = niDAQwrap->NiDaqReadDacBoardAdc(module, chan, data, type) ;
	return stat ;
}
// --------------------------------------------------------------------
int CDacBoardIO::ReadDataChanByte(int module, int addr, int chan, int * data, bool flag)
{
	// read 8-bit register from selected module & channel
	int stat = 0;
#ifndef DEBUG_NO_NIDAQ
	stat = niDAQwrap->NiDaqReadDacBoardChan(module, addr, chan, data, flag) ;
#endif
	return stat ; 
}
// --------------------------------------------------------------------
int CDacBoardIO::WriteDataChanByte(int module, int addr, int chan, int data)
{
	// write 8-bit register to selected module & channel with data
	// This is what is defined as a type 2 write only command
	// It transmits the command byte + 2 data bytes
	int stat = 0;
#ifndef DEBUG_NO_NIDAQ
	stat = niDAQwrap->NiDaqWriteDacBoardChan(module, addr, chan, data) ;
#endif

	return stat ;
}
// --------------------------------------------------------------------
int CDacBoardIO::ReadDataChanWord(int module, int addr, int chan, int * data, bool flag)
{
	// read 16-bit register to selected module & channel with data
	int stat = 0;
#ifndef DEBUG_NO_NIDAQ
	stat = niDAQwrap->NiDaqReadDacBoardWord(module, addr, chan, data, flag);
#endif

	return stat ;
}
// --------------------------------------------------------------------
int CDacBoardIO::WriteDataChanWord(int module, int addr, int chan, int data)
{
	// write 16-bit register to selected module & channel with data
	int stat = 0;
#ifndef DEBUG_NO_NIDAQ
	stat = niDAQwrap->NiDaqWriteDacBoardWord(module, addr, chan, data);
#endif

	return stat;
}
// --------------------------------------------------------------------
int CDacBoardIO::SetAltOutChnls(bool iotype)
{
	// configure all outputs for ALT board to iotype
	int stat1 = 0;
	int stat0 = 0;

#ifndef DEBUG_NO_NIDAQ
	CString dev = niDAQwrap->m_device ; 
	dev.Append(ADDR_PORT) ;
	stat0 = SetDigOutType(  (LPCTSTR) dev , iotype)  ;
	dev = niDAQwrap->m_device ;
	dev.Append("/port0/line4:7") ;
	stat1 = SetDigOutType( (LPCTSTR) dev, iotype)  ;
#endif
	 
	return stat0 | stat1 ;
}
// --------------------------------------------------------------------
int CDacBoardIO::SetDigOutType(const char * chnl, bool iotype)
{
	// true: active drive
	// false: open collector drive
	// Note : with 4.7kpu/5.6kpd driving with 5v results in 2.5v to FPGA

	int stat = 0;
#ifndef DEBUG_NO_NIDAQ
	stat = niDAQwrap->NiDaqSetDigitalOutputType(chnl, iotype ) ;
#endif

	return stat ;
}
// --------------------------------------------------------------------
int CDacBoardIO::SetNiDaqChnl(const char *chnl, int value)
{
    // this function for debug of system
	int error ;
	unsigned char result[1] ;
	niDAQwrap->ConvertDecToDaqCharArray(value, result, 1 ) ;
	error = niDAQwrap->NiDaqSetDigitalOutput(chnl, result) ;

	return error ;
}