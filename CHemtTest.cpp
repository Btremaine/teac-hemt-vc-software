// Copyright 2013 Prysm Inc.
// San Jose, CA, 95134
// btremaine@prysm.com
// btremaine@omnificsolutions.com
//
// CHemtTest.cpp
//

#include "StdAfx.h"
#include "CHemtTest.h"
#include "DacBoardIO.h"


//--------------------------------------------------------------------------
// Functions required for each module
//
// Set HV register value							| done
// Set HV channel enable bits                       | --- need rework
// Set HV dac enable								| done         
// Set Threshold gain High/Low						| done 
// Set Gate register value							| done
// Set ILEAK threshold level						| need work, calibrate

// Read Temperatures (I2C)							| need to implement I2C
// Set TC heater enable								| done, need to verify
// Set Tref values (I2C)							| need to implement I2C
// Set TC Servo Parameters (I2C)					| done, need to verify

// Read Safety SW state                             | done
// Read ADC sensor channels (raw ADC value)         | done
// Read HV value (Read ADC converted to fp)         | need calibration
// Read Ileak value (Read ADC converted to fp)      | need calibration


// NOTE: MODULE 2 ON THE GUI DISPLAY IS BRD_ID [2'b10] and module 1 in software.


// ---------------------------------------------------------------------------
CHemtTest::CHemtTest(CString serial_num)
{
	niDAQwrap = new CniDAQ();

	int absent = niDAQwrap->ChkNiDaqAvail(serial_num);

	m_NIDAQ_absent = absent;

	CDacIO = new CDacBoardIO();
	CDacIO->niDAQwrap = niDAQwrap;  // tell CDacIO where NI is accessed

	// initialize struct Rack, an instance of Module
	InitModuleDefault();

	if (!absent)
	{

		CDacIO->SetAltOutChnls(TRUE);   // initialize output channels to push-pull

#define debug_hdw 1
		while (debug_hdw)
		{
			int val;
			//ReadSensorChan(0, 20, &val); // VREF_CHAN
			//Sleep(50);

			int fp_value = -155;  // -15.5v
			int module = 1;
			int dut = 0;


			// *** turn off high voltage
			SetHvChanEn(module, 20, false);
			SetHvEnable(module, false);
			SetHvDac(module, 0, false);

			if (1)  // debug I2C
			{
				// ser pre-scalers & enable port
				EnableWBport(module);
				
				while (1)
				{
				       Sleep(10);
				    // === WRITE to SLAVE, works 5/17/15 ===
					   WriteI2C_Reg(module, CMD_DBND, 0x03);
					   Sleep(5);
					   WriteI2C_Reg(module, CMD_TMR_CNT, 60);
					   Sleep(5);
					   WriteI2C_Reg(module, CMD_TON_CNT, 48);
					   Sleep(5);
					   WriteI2C_Reg(module, CMD_TOFF_CNT, 12);

					// === END WRITE section, start READ from SLAVE ===

					   /*
					   // ------ load slave address
					   SetTXR(module, (0xaa | 0x01)); // read
					   Sleep(1);
					   // enable start & write slave address
					   SetCR(module, 0x90);
					   Sleep(1);
					   // ------- send data byte register to read
					   SetTXR(module, 0x0D);          // Dbnd
					   Sleep(1);
					   SetCR(module, 0x10);
					   Sleep(10);

					   // ------- send data byte
					   SetTXR(module, 0x03);
					   Sleep(1);
					   SetCR(module, 0x50);  // last byte
					   Sleep(10);
					*/

                    // === END READ section ====
				}
			}


			if (0)
			{  // read SWin status

				while (0)
				{
					// GetStatus(module, val)   +++ FIX
					Sleep(2);
					ReadHTword(module, HT3, &val);           // hardware not working 3/22
					Sleep(100);
				}

				while (1)
				{
					for (int j = 20; j < 21; j++)
					{
						SetHvChanEn(module, j, true);        // enable HV channels
						Sleep(2000);
						// SetHvChanEn(module, j, false);
						// Sleep(2000);
						ReadHTword(module, HT3, &val);        // hardware not working 3/22
						Sleep(2000);
						ReadAnlg(module, DEV0, &val);
						Sleep(500);
					}
				}
			}

			if (0) {
				SetGate(module, 255, false);		     // ** R188 s/b 1k, not 11k **
				// dac 0 == 16.3, dac 255 == -14.1
				// DAC working! 3/8/15
				Sleep(3000);
			}

			if (0) {
				// Iaram in 10's of nA
				SetIalarm(module, 0, false);		// DAC working! 3/1/15 
				Sleep(100);							// dac=0 (0.002), dac=255 (3.34)
			}
			if (0) {
				while (1)
				{
					// enable Ch1 HV relay then disable     
					int chan = 0;
					SetHvChanEn(module, 0, 1);		// working! when HT== 1, 3/1/15
					Sleep(1500);					// could be HT hardware error
					SetHvChanEn(module, 0, 0);		// 
					Sleep(1500);					//
					//
					SetHvChanEn(module, 1, 1);		// working! when HT== 1, 3/1/15
					Sleep(1500);					// could be HT hardware error
					SetHvChanEn(module, 1, 0);		// 
					Sleep(1500);
				}
			}

			if (0) {
				// set high gain then low
				bool state = 0;
				SetThrGain(module, state);			//	works! 3/1/15 all channel
				Sleep(1000);
				SetThrGain(module, !state);
				Sleep(1000);
			}
			if (0) {
				// set high voltage on/off  (relay output enable)
				bool state = 0;
				SetHvEnable(module, state);			//	works! 3/7/15
				Sleep(2000);
				SetHvEnable(module, !state);
				Sleep(2000);
			}
			if (1) {
				SetHvEnable(module, true);
				SetHvDac(module, 128, false);			// DAC working! 3/8/15
				Sleep(3000);						// need to re-scale
				SetHvDac(module, 0, false);
				Sleep(3000);
			}										// dac=0 (474), dac=255 (1252)

			if (0)
			{
				// check HV adc
				// ***** read adc for standby voltage
				int val;
				int dut;
				//ReadAnlg(module, HV_ANLG, &val);
				ReadAnlg(module, DEV19, &val);
				Sleep(500);
				Sleep(100);

			}

			if (0)
			{
				// read HT values

			}


			if (0)
			{
				// set HV Dac value
				SetHvDac(module, 255, false) ;				// dac 0:   U32-6 0.679 HVin: 1.227 HVout:  544
				                                            // dac 255: U32-6 0.09  HVin: 3.09  HVout: 1363   
				Sleep(1000);
				// set high voltage on (relay output enable)
				SetHvEnable(module, true) ;
				Sleep(1000);

				// enable all channels
				SetHvChanEn(module, 0, true) ;
				Sleep(4000) ;
				// check HV adc
				// ***** read adc for standby voltage
				int val;

				ReadAnlg(module, HV_ANLG, &val);  // HV_ANLG

				SetHvChanEn(module, 0, true);
				Sleep(500);
				SetThrGain(module, true);
				Sleep(500);

				// *** turn off high voltage
				SetHvChanEn(module, 20, false);
				SetHvEnable(module, false);
				SetHvDac(module, 255, false); 
				SetThrGain(module, false);
			}


		} // end while

		// *******************************************************

	} // end if

}
// ---------------------------------------------------------------------
void CHemtTest::InitModuleDefault() 
{

   // initialize module[] at creation to defaults
	for (int j=0; j<Nmod; j++) // {0,1,2}
	{
		Module[j].state = IDLE ;
		Module[j].ET = 0 ;
		Module[j].runComment = _T("Dummy comment xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx") ;
		Module[j].op_mode = 2 ;        // test mode off
		Module[j].HV = (int) HV_DEFAULT;     // fixed point voltage x 10
		Module[j].gate = (int) GTE_DEFAULT;  // fixed point voltage x 10

		// initialize each of 4 heaters
		Module[j].TREF[0] = (int) TREF_DEFAULT;  // fixed point degC x 10
		Module[j].TREF[1] = (int) TREF_DEFAULT;
		Module[j].TREF[2] = (int) TREF_DEFAULT;
		Module[j].TREF[3] = (int) TREF_DEFAULT;

		Module[j].Alarm = (int) ALRM_DEFAULT;

		for (int i=0; i<Ndut; i++)
		{			
			Module[j].lastVal[i] = 0 ;
			Module[j].HVref = 0 ;
			Module[j].IlkLim[j] = ILK_DEFAULT;
			Module[j].resTime[j] = 0;
		}
	}
}
// ---------------------------------------------------------------------
int CHemtTest::SetHvEnable(int module, bool value)
{
	// turn main HV Relay ON or OFF bit[0], TRUE = ENABLE, FALSE = DISABLE
	// bit[7:1] don't-care
	// module # is set {0,1,2}
	int error ;

	if (error = CheckNiDAQ())
	{
		return (error) ;
	}
	
	int state = 0;
	if (value) { state = 1; }

	error = CDacIO->WriteDataByte(module, CMD_HV_ONOFF, state);

	return error ;
}

// ---------------------------------------------------------------------
int CHemtTest::SetThrGain(int module, bool value)
{
	// turn Threshold gain ON or OFF bit[0], TRUE = ENABLE, FALSE = DISABLE
	// bit[7:1] don't-care
	// module # is set {0,1,2}
	int error;

	if (error = CheckNiDAQ())
	{
		return (error);
	}

	int data = 0x0;
	if (value) { data = 0x01; }
	else
	{
		data = 0x00;
	}

	error = CDacIO->WriteDataByte(module, CMD_GAIN, data);

	return error;
}

// ---------------------------------------------------------------------
int CHemtTest::SetHvDac(int module, int fp_value, bool type)
{
	// Set HV DAC register in specified module to value
	//    fp_value is in 10th's of a volt
	// module # is set {0,1,2}
	// value is DAC setting

	int error ;

	if (error = CheckNiDAQ())
	{
		return (error) ;
	}

	int dac;
	  
	if (type)
	{
		float x = ((float)fp_value / FLOAT2FXD);
		if (x > HV_LIMIT)
		{
			x = HV_LIMIT;
		}
		// convert fixed point HV to DAC
		x =  x * HV_COEFF1 + HV_COEFF0;
		dac = (int)x;
	}
	else
	{
		dac = fp_value;
	}

	if (dac<0) {
		dac = 0;
	}
	
	if(dac>255)
	{
		dac = 255;
	}
	else
	{
		// TODO --- fix address
		error = CDacIO->WriteDataByte(module, CMD_HV_DAC, dac);
	}

	return error ;
}

// ---------------------------------------------------------------------
int CHemtTest::SetHvChanEn(int module, int chan, bool state)
{
	// Set HV channel enable bit in specified module
	// module # is set {0,1,2}

	// type 1 command, send command address & 1 byte of data.

	int error;

	if (error = CheckNiDAQ())
	{
		return (error);
	}

	int reg = 0;
	if (state) {
		reg = 1;
	}

	int data = (reg << 7) | chan ;

	// TODO --- fix address
	error = CDacIO->WriteDataByte(module, CMD_HVCHN_ENBL, data);

	return error;
}

// ---------------------------------------------------------------------
int CHemtTest::SetIalarm(int module, int fp_value, bool type)
{
    // Set ILEAK threshold in specified module to value (hardware limit)
	// if type==true fp_value is 10's of nA, else fp_value = dac value
	// module # is set {0,1,2} 
	int error ;

	if (error = CheckNiDAQ())
	{
		return (error) ;
	}

	int dac;
	if (type) // fixed point type
	{
		// convert fixed point ILEAK to DAC
		float x = ((float)fp_value / FLOAT2FXD) * ILK_COEFF1 + ILK_COEFF0;
		dac = (int)x;
	}
	else
	{
		dac = fp_value;
	}

	if (dac<0 || dac>255)
	{
		error = (-1);
	}
	else
	{
		// TO DO: --- fix address
		error = CDacIO->WriteDataByte(module, CMD_THR_DAC, dac);
	}

	return error ;
}

// ---------------------------------------------------------------------
int CHemtTest::SetGate(int module, int fp_value, bool type)
{
	// Set Gate voltage in specified module to value
	// if type == true then fp_value is 10's of volts
	// else fp_value is DAC value
	// module # is set {0,1,2} 

	int error;

	if (error = CheckNiDAQ())
	{
		return (error);
	}

	int dac;

	if (type) // fixed point
	{
		// convert fixed point Gate to DAC 
		float x = ((float)fp_value / FLOAT2FXD) * GT_COEFF1 + GT_COEFF0;
		dac = (int)x;
	}
	else
	{
		dac = fp_value;
	}

	if (dac<0 )
	{
		dac = 0;
		error = (-1);
	}

	if (dac > 255)
	{
		dac = 255;
	}

	// TO DO: --- fix address
	error = CDacIO->WriteDataByte(module, CMD_BIAS_DAC, dac);

	return error;
}

// ---------------------------------------------------------------------
int CHemtTest::ReadHTword(int module, HT_WORD ht, int * val)
{
	int error = 0;

	// Read HT status word.
	// module:		module #
	// ht:			HT word #, 1,2,3
	// val:			pointer to int result

	// select module and read byte

	int cmd;
	switch (ht)
	{
		case HT1:	
			cmd = CMD_HVT_WD1;
			break;
		case HT2:	
			cmd = CMD_HVT_WD2;
			break;
		case HT3:	
			cmd = CMD_HVT_WD3;
			break;
		default:	
			cmd = CMD_HVT_WD3;
	}

	error = CDacIO->ReadDataChanByte(module, cmd, 0, val, true);

	return (error);
}

// ---------------------------------------------------------------------
int CHemtTest::SetTref(int module, HTR_ID htr, int value)
{
	// Set Tref in specified module
	// 'chan' is reg ID of parameter
	// 'value' is f.p. integer value
	// module # is set {0,1,2}

	// This is a type 2 command write-only, sending the command
	// address and 2 bytes.

	int error ;

	if (error = CheckNiDAQ()) 
	{
		return (error) ;
	}

	int chan;
	switch (htr)
	{
	case HTR1:
		chan = 0;
		break;
	case HTR2:
		chan = 1;
		break;
	case HTR3:
		chan = 2;
		break;
	case HTR4:
		chan = 3;
		break;
	default:
		chan = 0;
	}
	if (value > TMAX_LIMIT || value < 0)
	{
		error = -1;
	}
	else
	{
		// TO DO: --- fix address  **FIX
	// 	error = CDacIO->WriteDataChanByte(module, SET_TC_ADDR, chan, value);
	}

	return error ;
}

// ---------------------------------------------------------------------
int CHemtTest::ReadILEAK(int module, int chan, int * data)
{
	// Read ILEAK in specified module & channel to value
	// module:   # is set {0,1,2}
	// chan:     dut 0:19
	// data:     returned *data is ADC value

	int error = 0 ;

#ifndef DEBUG_NO_NIDAQ
	if (error = CheckNiDAQ())
	{
		return (error) ;
	}

	error = ReadAnlg(module, (VoltID)chan, data);

#else
	*data = NO_NIDAQ_ILK;
#endif

	return error ;
}
// -----------------------------------------------------------------------------
int CHemtTest::ReadTref(int module, enum HTR_ID chan, int * data)
{
	// Read Tref in specified module & heater to value
	// module # is set {0,1,2}
	int error = 0;

#ifndef DEBUG_NO_NIDAQ
	if (error = CheckNiDAQ())
	{
		return (error) ;
	}
	// TO DO: --- fix address

    //error = CDacIO->ReadDataChanByte(module, SET_TC_ADDR, chan, data, true) ;
#else
	// data is fixed point degC * 10
	*data = NO_NIDAQ_TREF;
#endif

	return error ;
}
// -----------------------------------------------------------------------------
int CHemtTest::ReadTemp(int module, enum TC_ID chan, int * data)
{
	// Read Temp in specified module & TC to value
	// module:   # is set {0,1,2}
	// chan:     TC_ID enum
	// *data:    temperature fixed point 10ths of deg C i.e. 102.3 == 1023


	int error = 0;

#ifndef DEBUG_NO_NIDAQ
	if (error = CheckNiDAQ()) { return (error); }


	// TO DO: --- fix address // i2c work
	//error = CDacIO->ReadDataChanByte(module, SET_TC_ADDR, chan, data, true);

	*data = 1234;
	if (chan == TC8) { *data = 250; }

#else
	// data is fixed point degC * 10
	*data = NO_NIDAQ_TREF;
#endif

	return error;
}

// ---------------------------------------------------------------------------
int CHemtTest::ReadAnlg(int module, VoltID device, int * val)
{
	// module: module #
	// dut:    device #
	// ch:     voltage source
	// val:    address of voltage in ADC counts

	int error = 0;

#ifdef HARDWARE_INSTALLED
	if (error = CheckNiDAQ())
	{
		return (error);
	}

	// decode analog channel from device ID
	int ch = device & 0x7;				// lower 3-bits define channel within mux
	int mux = (device >> 3) & 0x3;		// select 1 of 3 muxes

	// select mux channel
	if (SetAnlgMux(module, mux, ch))
	{
		return error;
	}

	// read analog signal, analog mux & channel already selected
	// (two transactions, start ADC & read data)
	error = CDacIO->ReadAdcChan(module, NULL, val, false);

#endif

	return error;

}

// ---------------------------------------------------------------------
int CHemtTest::SetAnlgMux(int module, int mux, int chan)
{
	// On module set the analog mux for selecting ADC channel to read
	// module: module #
	// mux:    mux # 0, 1 or 2
	// ch:     channel of voltage source, 1 of 8 in selcted mux

	int error = 0;

#ifdef HARDWARE_INSTALLED
	if (error = CheckNiDAQ())
	{
		return (error);
	}

	mux  = mux & 0x3;  // limit to 3 devices
	chan = chan & 0x7; // limit to 8 channels per mux

	error = CDacIO->WriteDataByte(module, (CMD_ADC_MUX), (mux <<3 |chan));
#endif

	return error;

}

// ----------------------------------------------------------------------
int CHemtTest::ReadSensorChan(int module, int chan, int * val )
{
	// Read ADC channel chan from module and return in val
	int error = 0 ;

#ifndef DEBUG_NO_NIDAQ
	// TO DO: do automatic gain selection

	if (error = CheckNiDAQ())
	{
		*val = 4097;
		return (-1) ;  
	}
    error = CDacIO->ReadAdcChan(module, chan, val ) ;
#else
	*val= 128;

#endif

	return error ;
}

// ---------------------------------------------------------------------------
int CHemtTest::GetStatus(int module, int id, int * val)
{
	// execute status command
	// module:		module #0,1,2
	// id:			enum STATUS_ID, status word ID #
	// val:			address pointer to 16-bit word

	int error = 0;

	// select module
	// send command
	// retrieve two data bytes (16-bit word)

	// TO DO --- create routine



	return (error);

}

// ---------------------------------------------------------------------------
int CHemtTest::ReadModuleSensorChan(int module, int chan, int * val)
{
	// Read module ADC channel, in this instance module already selected.
	// //////////////////////////////////////////////////////////////////
	int error = 0;

#ifndef DEBUG_NO_NIDAQ
	if (error = CheckNiDAQ())
	{
		*val = 4097;
		return (-1);
	}

	// Select channel to convert
	if (CDacIO->WriteDataByte(module, CMD_ADC_MUX, chan))
	{
		error = (-1);
		return error;
	}

	// Do conversion & get data
	if (niDAQwrap->NiDaqReadDacBoardByte(module, (CMD_ADC_CNVRT), val, false))  // ADC reads during ALE & CS High
	{
		error = (-1);
		return error;
	}
#else
	*val = NO_NIDAQ_ADC;

#endif

	return error;
}
// ---------------------------------------------------------------------------
int CHemtTest::CheckNiDAQ(void)
{
	// check NiDAQ present
	if (CDacIO->niDAQwrap->m_niDAQmx_online)
	{
		return (-1) ;
	}

	return (0) ;
}
// ----------------------------------------------------------------------------
int CHemtTest::SetModSel(int module)
{
	int error = 0;
#ifndef DEBUG_NO_NIDAQ
	error = CDacIO->niDAQwrap->SetModSel(module);
#endif

	return error;
}

// ----------------------------------------------------------------------------
int CHemtTest::LoadConfigToFpga(int module)
{

	SetHvDac(module, Module[module].HV);
	HTR_ID j;
	for (int i = 0; i < 4; i++)
	{
		switch (i)
		{
		case 0:
			j = HTR1;
			break;
		case 1:
			j = HTR2;
			break;
		case 2:
			j = HTR3;
			break;
		case 3:
			j = HTR4;
			break;
		default:
			j = HTR1;
		}

		SetTref(module, j, Module[module].TREF[i]);
	}

    SetIalarm(module, Module[module].Alarm);

	return (0);
}

// -----------------------------------------------------------------------------
int CHemtTest::LoadSelectedDeviceConfig(int module, int dut)
{
	// setup Ndut for test / Ndut # >= 0
	// set all other Nduts tp PA == 0

	// TO DO: --- handle all unused channels, disable channels

	for (int i = 0; i<Ndut; i++)
	{
		// disable all channels
	}

	if (dut>=0)
	{
		SetIalarm(module, Module[module].Alarm);
	}
	else
		return (-1);

	return (0);

}
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// ------- functions to implement I2C Wishbone interface -----------------------
// -----------------------------------------------------------------------------
//
// CMD_TXR_REG:	Transmit register
// CMD_CR_REG:	Command register
// CMD_CTL_REG:	Control register
// CMD_SR_REG:	Status register
//
// -----------------------------------------------------------------------------
int CHemtTest::SetTXR(int module, int addr)
{
	// send 1 byte to the Wishbone intrerface TXR register
	// module:	 # is set {0,1,2}
	// addr:

	int error;

	if (error = CheckNiDAQ())
	{
		return (error);
	}

	addr = addr & 0xff;
	error = CDacIO->WriteDataByte(module, CMD_TXR_REG, addr);

	return error;
}

// -----------------------------------------------------------------------------
int CHemtTest::SetCR(int module, int addr)
{
	// send 1 byte to the Wishbone intrerface CR register
	// module:	 # is set {0,1,2}
	// addr:

	int error;

	if (error = CheckNiDAQ())
	{
		return (error);
	}

	addr = addr & 0xff;
	error = CDacIO->WriteDataByte(module, CMD_CR_REG, addr);

	return error;
}

// ------------------------------------------------------------------------------
int CHemtTest::SetCTL(int module, int addr)
{
	// send 1 byte to the Wishbone intrerface CTL register
	// module:	 # is set {0,1,2}
	// addr:

	int error;

	if (error = CheckNiDAQ())
	{
		return (error);
	}

	addr = addr & 0xff;
	error = CDacIO->WriteDataByte(module, CMD_CTL_REG, addr);

	return error;
}

// ------------------------------------------------------------------------------
int CHemtTest::SetPreLo(int module, int value)
{
	// send 1 byte to the Wishbone interface Prescale low register
	// module:		# is set {0,1,2}
	// value:		register value

	int error;

	if (error = CheckNiDAQ())
	{
		return (error);
	}

	value = value & 0xff;
	error = CDacIO->WriteDataByte(module, CMD_PRELO_REG, value);

	return error;
}

// ---------------------------------------------------------------------------------
int CHemtTest::SetPreHi(int module, int value)
{
	// send 1 byte to the Wishbone interface Prescale high register
	// module:		# is set {0,1,2}
	// value:		register value

	int error;

	if (error = CheckNiDAQ())
	{
		return (error);
	}

	value = value & 0xff;
	error = CDacIO->WriteDataByte(module, CMD_PREHI_REG, value);

	return error;
}

// ------------------------------------------------------------------------------
int CHemtTest::ReadSR(int module, int * val)
{
	// read 1 byte from the Wishbone intrerface SR register
	// module:		module #
	// val:			pointer to int result

	// select module and read byte

	int error = 0;

	error = CDacIO->ReadDataChanByte(module, CMD_SR_REG, 0, val, true);

	return (error);
}

// ------------------------------------------------------------------------------
int CHemtTest::EnableWBport(int module)
{
	// enable wb port
	// module:	module #
	// setup pre-scalers then enable the core

	int error = -1;

	// set up prescale registers div by 49 decimal
	if (SetPreLo(module, 0x31) == 0)
	{
		if (SetPreHi(module, 0x00) == 0)
		{
			// enable the core
			error = SetCTL(module, 0x80);
		}
	}

	return (error);
}

// ------------------------------------------------------------------------------
int CHemtTest::ReadI2C(int module, int i2c_reg, int * data)
{
	// read a 16-bit word (two bytes) from i2c_reg 
	// module:		module #
	// i2c_reg:		8-bit i2c register address
	// data:		pointer to concantinated 16-bit word

	int error = -1;


	return (error);
}

// ------------------------------------------------------------------------------
int CHemtTest::WriteI2C(int module, int i2c_reg, int data)
{
	// write a 16-bit word (two bytes) to i2c_reg 
	// module:		module #
	// i2c_reg:		8-bit i2c register address
	// data:		concantinated 16-bit word sent as two bytes

	int error = -1;

	int msb = data >> 8;
	int lsb = data & 0x00ff;

//	SendSlaveAddr(module, I2CADDR, true);
	SetCR(module, 0x90);
	// check TIP in SR register for completion
	// check SR here
	//

	SetTXR(module, i2c_reg);	// send i2c_reg for data
	SetCR(module, 0x10);		// start write
	// check TIP in SR register for completion
	// check SR here
	//

	SetTXR(module, lsb);		// send lsb data
	SetCR(module, 0x10);		// start write
	// check TIP in SR register for completion
	// check SR here
	//

	SetTXR(module, msb);		// send msb data
	SetCR(module, 0x50);		// start last write
	// check TIP in SR register for completion
	// check SR here
	//

	return (error);

}

// --------------------------------------------------------------------------------
int CHemtTest::WriteI2C_Reg(int module, unsigned char  reg, unsigned char data)
{

	// === WRITE to SLAVE, works 5/17/15 ===
	// ------ load slave address
	SetTXR(module, (0xaa | 0x00));
	Sleep(1);
	// enable start & write slave address
	SetCR(module, 0x90);
	Sleep(1);
	// ------- send data byte register #
	SetTXR(module, reg);
	Sleep(1);
	SetCR(module, 0x10);
	Sleep(5);
	// ------- send data byte
	SetTXR(module, data);
	Sleep(1);
	SetCR(module, 0x50);  // last byte
	Sleep(5);

	return (0);
}

// --------------------------------------------------------------------------------
int CHemtTest::EnableTcServo(int module, int chan, bool fp)
{
	// enable or disable heater temp control
	// Uses I2C interface to TC board

	unsigned char data = 0;
	int error = 0;

	unsigned char reg = CMD_SSR_ENB;

	// get heater status in reg_stat     FIX 
	unsigned char reg_stat = 0;
	// need to update here ....

	
	unsigned char bit_field = 0;
	unsigned char bit = 0;

	if (fp) bit = 0x1;

	switch (chan)
	{
	case HTR1: 
		bit_field = !(1 << 0);
		data = reg_stat & bit_field;
		data = reg_stat | (bit << 0);
		break;

	case HTR2:
		bit_field = !(1 << 1);
		data = reg_stat & bit_field;
		data = reg_stat | (bit << 1);
		break;

	case HTR3:
		bit_field = !(1 << 2);
		data = reg_stat & bit_field;
		data = reg_stat | (bit << 2);

	case HTR4:
		bit_field = !(1 << 3);
		data = reg_stat & bit_field;
		data = reg_stat | (bit << 3);

	default:
		error = (-1);
	}

	if (!error)
	{
		error = WriteI2C_Reg(module, reg, data);
	}

	return (error);

}

// --------------------------------------------------------------------------------
int CHemtTest::SetServoParam(int module, enum ServoID id, unsigned char val)
{
	// set servo parameters in TC controller
	// Uses I2C interface

	unsigned char reg;
	int error = -1;

	switch (id)
	{
	case ID_DBND:
		reg = CMD_DBND;
		break;
	case ID_TMR:
		reg = CMD_TMR_CNT;
		break;
	case ID_TON:
		reg = CMD_TON_CNT;
		break;
	case ID_TOFF:
		reg = CMD_TOFF_CNT;
		break;
	default:
		error = (-1);
	}

	if (!error)
	{
		error = WriteI2C_Reg(module, reg, val);
	}

	return(error);
	
}


