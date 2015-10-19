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

// Read Temperatures (I2C)							| done, need calibration offset
// Set TC heater enable								| done, need to verify
// Set Tref values (I2C)							| working 5/31 reg <= (degC*100) ex 220.12C = 0x55FC
// Set TC Servo Parameters (I2C)					| working 5/31 


// Read Safety SW state                             | done
// Read ADC sensor channels (raw ADC value)         | done
// Read HV value (Read ADC converted to fp)         | need calibration
// Read Ileak value (Read ADC converted to fp)      | need calibration


// NOTE: *** MODULE 2 ON THE GUI DISPLAY IS BRD_ID [2'b10] and module 1 in software. ***
//           MODULE 1 ON THE GUI DISPLAY IS BRD_ID [2'b01] and module 0 in software.     


// ---------------------------------------------------------------------------
CHemtTest::CHemtTest(CString serial_num)
{
	niDAQwrap = new CniDAQ();

	int absent = (niDAQwrap->ChkNiDaqAvail(serial_num));

#ifdef DEBUG_NO_NIDAQ
	absent = 0;			// force present for debug
#endif

	m_NIDAQ_absent = absent;

	if (!absent)
	{
		CDacIO = new CDacBoardIO();
		CDacIO->niDAQwrap = niDAQwrap;  // tell CDacIO where NI is accessed

		// initialize struct Rack, an instance of Module
		InitModuleDefault();

		CDacIO->SetAltOutChnls(TRUE);   // initialize output channels to push-pull

		// set I2C pre-scalers & enable port (in case they are there)
		EnableWBport(0);
		EnableWBport(1);
		EnableWBport(2);

#define debug_hdw 0
while (debug_hdw)
		{
			int tempfixed[16];
			int val;
			int nom = 0;

			int module = 1;			// {0,1 or 2)

			int dut = 0;

			// check I2C comm

			while (1)   // not working 9/5/2015
			{
				// need better method to check for missing I2C
				val = -1;
				
				ReadI2CVersion(module, &val);
				Sleep(50);
				if (val != 0xFFFF && val >= 0x1001)
				{
					nom++;
				}
			}



			while (1)
			{
				ReadSensorChan(module, HV_ANLG, &val); //
				Sleep(50);
			}

			int fp_value = -155;  // -15.5v



			// *** turn off high voltage
			SetHvChanEn(module, 20, false);
			SetHvEnable(module, false);
			SetHvDac(module, 0, false);

			if (1)  // debug I2C
			{
				// ser pre-scalers & enable port
				EnableWBport(module);
				
				unsigned char result[5];
				int word;

				while (1)
				{
					   

				       Sleep(10);
					   if (1)
					   {

						   // === WRITE to SLAVE, works 5/17/15 ===
						   WriteI2C_Reg(module, CMD_DBND, 0x03);
						   Sleep(5);
						   WriteI2C_Reg(module, CMD_TMR_CNT, 60);
						   Sleep(5);
						   WriteI2C_Reg(module, CMD_TON_CNT, 48);
						   Sleep(5);
						   WriteI2C_Reg(module, CMD_TOFF_CNT, 12);
					   }

					// === END WRITE section, start READ from SLAVE ===
					//
				   
					ReadI2C_Byte(module, CMD_TMR_CNT, &result[0]);
					ReadI2C_Byte(module, CMD_TON_CNT, &result[1]);
					ReadI2C_Byte(module, CMD_TOFF_CNT, &result[2]);
					ReadI2C_Byte(module, CMD_DBND, &result[3]);

					int data = 0x55FC;
					WriteI2C_DblByte(module, CMD_TREF0, data);
					data = 0x5660;
					WriteI2C_DblByte(module, CMD_TREF1, data);
					data = 0x56C4;
					WriteI2C_DblByte(module, CMD_TREF2, data);
					data = 0x5728;
					WriteI2C_DblByte(module, CMD_TREF3, data);
					;
					;
					data = 0x0000;
					WriteI2C_DblByte(module, CMD_TOFST0, data);
					data = 0x0000;
					WriteI2C_DblByte(module, CMD_TOFST1, data);
					data = 0x0000;
					WriteI2C_DblByte(module, CMD_TOFST2, data);
					data = 0x0000;
					WriteI2C_DblByte(module, CMD_TOFST3, data);
					data = 0x0000;
					WriteI2C_DblByte(module, CMD_TOFST4, data);
					data = 0x0000;
					WriteI2C_DblByte(module, CMD_TOFST5, data);
					data = 0x0000;
					WriteI2C_DblByte(module, CMD_TOFST6, data);
					data = 0x0000;
					WriteI2C_DblByte(module, CMD_TOFST7, data);
					;
					;

					//ReadI2C_DblByte(module, CMD_TEMP0, &word);

					for (int i = 0; i < 8; i++)
					{
						ReadTempChan(module, TC_CH0+i, &tempfixed[i]);
						Sleep(20);
					}

				    ReadTrefChan(module, TC_REF0, &tempfixed[8]);
					ReadTrefChan(module, TC_REF1, &tempfixed[9]);
					ReadTrefChan(module, TC_REF2, &tempfixed[10]);
					ReadTrefChan(module, TC_REF3, &tempfixed[11]);
					  
                    // === END READ section ====
				}
			}


			if (1)
			{  // read SWin status
				SetHvEnable(module, true);
				for (int k = 0; k < 20; k++)
				{
					SetIalarm(module, 20, false);
					SetHvChanEn(module, k, true);
				}

				while (1)
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

			if (1) {
				SetGate(module, 255, false);		     // ** R188 s/b 1k, not 11k **
				// dac 0 == 16.3, dac 255 == -16.26
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
	char * comment = new char[100];

	strcpy(comment, _T("The device run comment is to define the general configuration"));

   // initialize module[] at creation to defaults
	for (int j=0; j<Nmod; j++) // {0,1,2}
	{
		Module[j].state = IDLE ;
		Module[j].ET = 0 ;
		Module[j].runComment = comment;
		Module[j].op_mode = 2 ;        // test mode off
		Module[j].HV = (int) HV_DEFAULT;     // fixed point voltage x 10
		Module[j].gate = (int) GTE_DEFAULT;  // fixed point voltage x 10

		// initialize each of 4 heaters
		Module[j].TREF[0] = (int) TREF_DEFAULT;  // fixed point degC x 10
		Module[j].TREF[1] = (int) TREF_DEFAULT;
		Module[j].TREF[2] = (int) TREF_DEFAULT;
		Module[j].TREF[3] = (int) TREF_DEFAULT;

		Module[j].Heater[0] = HEATER_DEFAULT;
		Module[j].Heater[1] = HEATER_DEFAULT;
		Module[j].Heater[2] = HEATER_DEFAULT;
		Module[j].Heater[3] = HEATER_DEFAULT;

		Module[j].Alarm = (int) ALRM_DEFAULT;

		for (int i=0; i<Ndut; i++)
		{			
			Module[j].lastVal[i] = 0 ;
			Module[j].HVref = 0 ;
			Module[j].IlkLim[j] = ILK_DEFAULT;
			Module[j].resTime[j] = 0;
		}
	}
	delete[] comment;
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

	// default is type == true,

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
		x =  x * m_hv_set_b1[module] + m_hv_set_b0[module];
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
		float x = ((float)fp_value / FLOAT2FXD) * m_alarm_b1[module] + m_alarm_b0[module];
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
		float x = ((float)fp_value / FLOAT2FXD) * m_gate_b1[module] + m_gate_b0[module];
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
		chan = CMD_TREF0;
		break;
	case HTR2:
		chan = CMD_TREF1;
		break;
	case HTR3:
		chan = CMD_TREF2;
		break;
	case HTR4:
		chan = CMD_TREF3;
		break;
	default:
		chan = CMD_TREF0;
	}
	if (value > TMAX_LIMIT || value < 0)
	{
		error = -1;
	}
	else
	{
		// value written is 10ths of degC * 128
		value = CalTref2TC(value, htr, module);
		value = (value * 128 / FLOAT2FXD);
		WriteI2C_DblByte(module, chan, value);
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
	ReadTrefChan(module, chan, data);   // data is degC * 128

	// convert TREF used in TC back to calibrated value used in GUI display
	// part of thermocouple calibration
	*data = CnvrtTCref2TREF(*data, chan, module);

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

	ReadTempChan(module, chan, data);
#else
	*data = (198.7) * 128;  // equivalent TC value
#endif

	// temperature calibration, convert TC reading to calibrated value
	float arg;
	arg = ((*data) / 128) ;   // raw deg C float

	(*data) = CalTC2Temp( (int) (arg*FLOAT2FXD), chan, module) ;

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

#else
	*val = 0xff;
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
int CHemtTest::EnableTcServos(int module)
{
	// Enable TC servos based on heater status

	int error = 0;
	int reg;

	reg = Module[module].Heater[0];
	reg = reg | (Module[module].Heater[1] << 1);
	reg = reg | (Module[module].Heater[2] << 2);
	reg = reg | (Module[module].Heater[3] << 3);

	error = WriteI2C_Reg(module, CMD_SSR_ENB, reg);

	return (error);
}

// ---------------------------------------------------------------------------
int CHemtTest::DisableTcServos(int module)
{
	// Enable TC servos

	int error = 0;

	Module[module].Heater[0] = 0;
	Module[module].Heater[1] = 0;
	Module[module].Heater[2] = 0;
	Module[module].Heater[3] = 0;

	error = WriteI2C_Reg(module, CMD_SSR_ENB, 0);

	return (error);
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
#ifndef DEBUG_NO_NIDAQ
	if (CDacIO->niDAQwrap->m_niDAQmx_online)
	{
		return (-1) ;
	}
#endif

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
	SetGate(module,  Module[module].gate);
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
		SetServoParam(module, ID_DBND, m_tc_dbnd);
		SetServoParam(module, ID_TON, m_tc_ton_max);
		SetServoParam(module, ID_TOFF, m_tc_toff_min);
		SetServoParam(module, ID_TMR, m_tc_cntr);	

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
int CHemtTest::WrtTXR(int module, int addr)
{
	// send 1 byte to the Wishbone intrerface TXR register
	// module:	 # is set {0,1,2}
	// addr:

	int error;

	addr = addr & 0xff;
	error = CDacIO->WriteDataByte(module, CMD_TXR_REG, addr);

	return error;
}

// -----------------------------------------------------------------------------
int CHemtTest::WrtCR(int module, int addr)
{
	// send 1 byte to the Wishbone intrerface CR register
	// module:	 # is set {0,1,2}
	// addr:

	int error;

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
	WrtCR(module, 0x90);
	// check TIP in SR register for completion
	// check SR here
	//

	WrtTXR(module, i2c_reg);	// send i2c_reg for data
	WrtCR(module, 0x10);		// start write
	// check TIP in SR register for completion
	// check SR here
	//

	WrtTXR(module, lsb);		// send lsb data
	WrtCR(module, 0x10);		// start write
	// check TIP in SR register for completion
	// check SR here
	//

	WrtTXR(module, msb);		// send msb data
	WrtCR(module, 0x50);		// start last write
	// check TIP in SR register for completion
	// check SR here
	//

	return (error);

}

// --------------------------------------------------------------------------------
int CHemtTest::WriteI2C_Reg(int module, unsigned char  reg, unsigned char data)
{

	// === WRITE to SLAVE, works 5/17/15 ===
	int error;

	if (error = CheckNiDAQ())
	{
		return (error);
	}

	// ------ load slave address
	WrtTXR(module, (I2CADDR | 0x00));
	Sleep(1);
	// enable start & write slave address
	WrtCR(module, 0x90);
	Sleep(1);
	// ------- send data byte register #
	WrtTXR(module, reg);
	Sleep(1);
	WrtCR(module, 0x10);
	Sleep(5);
	// ------- send data byte
	WrtTXR(module, data);
	Sleep(1);
	WrtCR(module, 0x50);  // last byte & stop
	Sleep(5);

	return (0);
}

// --------------------------------------------------------------------------------
int CHemtTest::ReadI2C_Byte(int module, unsigned char cmnd_reg, unsigned char* data)
{
	// single byte read commands to I2C interface

	int val;
	int error = 0;

	int result;

	if (error = CheckNiDAQ())
	{
		return (error);
	}

	// ------ load slave address & write bit
	WrtTXR(module, (I2CADDR | 0x00));
	// enable start & write slave address
	WrtCR(module, 0x90);
	// check ack here
	getTIP(module, &val);
	// ------- send data byte register # to read
	WrtTXR(module, cmnd_reg);
	WrtCR(module, 0x10);
	getTIP(module, &val);
	// ------- receive data byte
	WrtTXR(module, (I2CADDR | 0x01));
	WrtCR(module, 0x90);  // start repeated write to slave
	getTIP(module, &val);
	WrtCR(module, 0x28);  // start read & NACK
	getTIP(module, &val);
	getI2Cbyte(module, &result);
	WrtCR(module, 0x40);  // send stop
	getTIP(module, &val); // ---- for debug only
	*data = (result);

	return(error);

}

// --------------------------------------------------------------------------------
int CHemtTest::ReadI2C_DblByte(int module, unsigned char cmnd_reg, int* data)
{
	// two byte read commands to I2C interface

	int val;
	int error = 0;

	int lsb;
	int msb;

	if (error = CheckNiDAQ())
	{
		return (error);
	}

	// ------ load slave address & write bit
	WrtTXR(module, (I2CADDR | 0x00));
	// enable start & write slave address
	WrtCR(module, 0x90);
	// check tip here
	getTIP(module, &val);
	// ------- send data byte register # to read
	WrtTXR(module, cmnd_reg);
	WrtCR(module, 0x10);
	getTIP(module, &val);
	// ------- receive data byte
	WrtTXR(module, (I2CADDR | 0x01));
	WrtCR(module, 0x90);  // start repeated write to slave
	getTIP(module, &val);
	//
	WrtCR(module, 0x20);  // start repeated read
	getTIP(module, &val);
	getI2Cbyte(module, &lsb);
	;
	WrtCR(module, 0x28);  // start repeated read & NACK
	getTIP(module, &val);
	getI2Cbyte(module, &msb);

	WrtCR(module, 0x40);  // send stop

	*data = (msb<<8) | (lsb & 0xFF);

	return(error);

}

// --------------------------------------------------------------------------------
int CHemtTest::WriteI2C_DblByte(int module, unsigned char reg, int data)
{
	// two byte read commands to I2C interface

	int val;
	int lsb;
	int msb;

	lsb = (data & 0xFF);
	msb = (data >> 8) & 0xFF;

	int error;

	if (error = CheckNiDAQ())
	{
		return (error);
	}

	// ------ load slave address
	WrtTXR(module, (I2CADDR | 0x00)); //1
	// enable start & write slave address
	WrtCR(module, 0x90); //2
	getTIP(module, &val);//3
	// ------- send data byte register #
	WrtTXR(module, reg); //4
	WrtCR(module, 0x10); //5
	getTIP(module, &val);//6 
	// ------- send data byte
	WrtTXR(module, lsb); //7 1st byte
	WrtCR(module, 0x10); //8
	getTIP(module, &val);//9
	WrtTXR(module, msb); //10 last byte
	WrtCR(module, 0x50); //11
	
	return (0);

}

// --------------------------------------------------------------------------------
int CHemtTest::getACK(int module, int * data )
{
	// Read WB interface STATUS reg abd return ACK bit 7
	// ACK = 1  (no ack received)
	// ACK == 0 (ack received)


	// read status byte from Wishbone interface
	// module:	 # is set {0,1,2}

	int error;

	if (error = CheckNiDAQ())
	{
		return (error);
	}

	error = CDacIO->ReadDataChanByte(module, CMD_SR_REG, (0), data, true);

	int bit;
	bit = ((*data) >> 7) & 0x01;  // bit 7 is ack

	return (error);
}

// --------------------------------------------------------------------------------
int CHemtTest::getTIP(int module, int * data)
{
	// Read WB interface STATUS reg abd return TIP bit 1
	// TIP = 1  (transfer in process)
	// TIP == 0 (no transfer in process)


	// read status byte from Wishbone interface
	// module:	 # is set {0,1,2}

	int error = 0;

	int bit=1;
	int count = 0;

	while (bit && (count< I2C_TIP_WAIT) )
	{
		error = CDacIO->ReadDataChanByte(module, CMD_SR_REG, (0), data, true);
		bit = ((*data) >> 1) & 0x01;  // bit 1 is TIP
		Sleep(1);
		count++;
	}

	return (error);
}

// --------------------------------------------------------------------------------
int CHemtTest::getI2Cbyte(int module, int * val)
{
	// read 1 byte from the Wishbone intrerface RXR register
	// module:		module #
	// val:			pointer to int result

	// select module and read byte

	int error = 0;

	error = CDacIO->ReadDataChanByte(module, CMD_RDRXR_REG, 0, val, true);
	*val = (*val) & 0xFF;

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

// --------------------------------------------------------------------------------
int CHemtTest::ReadTempChan(int module, unsigned char chan, int * data)
{
	// read temperature using single byte reads then concantinate in word

	int error = 0;

	unsigned char lsb;
	unsigned char msb;
	unsigned char cmd_lsb;
	unsigned char cmd_msb;


	switch (chan)
	{
	case TC_CH0:
		cmd_lsb = CMD_TEMP0_LSB;
		cmd_msb = CMD_TEMP0_MSB;
		break;
	case TC_CH1:
		cmd_lsb = CMD_TEMP1_LSB;
		cmd_msb = CMD_TEMP1_MSB;
		break;
	case TC_CH2:
		cmd_lsb = CMD_TEMP2_LSB;
		cmd_msb = CMD_TEMP2_MSB;
		break;
	case TC_CH3:
		cmd_lsb = CMD_TEMP3_LSB;
		cmd_msb = CMD_TEMP3_MSB;
		break;
	case TC_CH4:
		cmd_lsb = CMD_TEMP4_LSB;
		cmd_msb = CMD_TEMP4_MSB;
		break;
	case TC_CH5:
		cmd_lsb = CMD_TEMP5_LSB;
		cmd_msb = CMD_TEMP5_MSB;
		break;
	case TC_CH6:
		cmd_lsb = CMD_TEMP6_LSB;
		cmd_msb = CMD_TEMP6_MSB;
		break;
	case TC_CH7:
		cmd_lsb = CMD_TEMP7_LSB;
		cmd_msb = CMD_TEMP7_MSB;
		break;
	default:
		cmd_lsb = CMD_TEMP7_LSB;
		cmd_msb = CMD_TEMP7_MSB;
	}

	ReadI2C_Byte(module, cmd_lsb, &lsb);
	ReadI2C_Byte(module, cmd_msb, &msb);

	*data = (msb << 8 | lsb);

	return (error);

}

// --------------------------------------------------------------------------------
int CHemtTest::ReadTrefChan(int module, unsigned char chan, int * data)
{
	// read temperature ref channel using single byte reads then concantinate in word

	int error = 0;

	unsigned char lsb;
	unsigned char msb;
	unsigned char cmd_lsb;
	unsigned char cmd_msb;


	switch (chan)
	{
	case TC_REF0:
		cmd_lsb = CMD_TREF0_LSB;
		cmd_msb = CMD_TREF0_MSB;
		break;
	case TC_REF1:
		cmd_lsb = CMD_TREF1_LSB;
		cmd_msb = CMD_TREF1_MSB;
		break;
	case TC_REF2:
		cmd_lsb = CMD_TREF2_LSB;
		cmd_msb = CMD_TREF2_MSB;
		break;
	case TC_REF3:
		cmd_lsb = CMD_TREF3_LSB;
		cmd_msb = CMD_TREF3_MSB;
		break;
	default:
		cmd_lsb = CMD_TREF0_LSB;
		cmd_msb = CMD_TREF0_MSB;
	}

	ReadI2C_Byte(module, cmd_lsb, &lsb);
	ReadI2C_Byte(module, cmd_msb, &msb);

	*data = (msb << 8 | lsb);

	return (error);

}

// --------------------------------------------------------------------------------
int CHemtTest::ReadI2CVersion(int module, int * data)
{

	int error = 0;
	unsigned char lsb;
	unsigned char msb;

	ReadI2C_Byte(module, CMD_VERSION_LSB, &lsb);
	Sleep(20);
	ReadI2C_Byte(module, CMD_VERSION_MSB, &msb);

	*data = (msb << 8 | lsb);

	return (error);

}

// ----------------------------------------------------------------------------------
int CHemtTest::CalTref2TC(int value, HTR_ID j, int module)
{
	// Convert desired TREF to calibrated value for TC
	// value is 10th's of degC using define

	float arg;
	arg = (float) (value / FLOAT2FXD) ;
	value = FLOAT2FXD * (arg * m_tempref_b1[module][j] + m_tempref_b0[module][j]) ;

	return (value);
}

// -----------------------------------------------------------------------------------
int CHemtTest::CalTC2Temp(int value, TC_ID j, int module)
{
	// Convert TC Temp reading to calibrated value for display
	// value is 10th's of degC using define

	float arg;
	arg = (float)(value / FLOAT2FXD);
	value = FLOAT2FXD * (arg * m_temp_b1[module][j] + m_temp_b0[module][j]);

	return (value);
}

// ----------------------------------------------------------------------------------
int CHemtTest::CnvrtTCref2TREF(int value, HTR_ID j, int module)
{
	// Convert TREF read from TC to calibrated value for display
	// value is degC * 128
	// return: 10th's of degC

	float arg;
	arg = (float)(value / 128);   // float degC

	value = ((arg - m_tempref_b0[module][j]) / m_tempref_b1[module][j]) * FLOAT2FXD;

	return (value);
}