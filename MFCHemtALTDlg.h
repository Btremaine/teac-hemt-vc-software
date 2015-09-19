// Copyright 2013 Prysm Inc.
// San Jose, CA, 95134
// btremaine@prysm.com
// btremaine@omnificsolutions.com
//
// MFCHemtALTDlg.h : header file
//

#pragma once


#include "CHemtTest.h"
#include "afxwin.h"
#include "afxdialogex.h"

// CMFCHemtALTDlg dialog
class CMFCHemtALTDlg : public CDialogEx
{
// Construction
public:
	CMFCHemtALTDlg(CWnd* pParent = NULL );	// standard constructor
	
	CHemtTest * MBT ;
	CStatic   * m_logo;

private:
	void InitTestRadioBut(void) ;
	void InitSensStart(int module) ;
	void InitSenVal(int module) ;
	void InitCfgSettings(void) ;
	void InitElapsedTime(void) ;
	void UpdateModuleDisplay(INT module) ;
	void UpdateElapsedTimeDisp(UINT module) ;
	void UpdateModuleElapsedTime(UINT module) ;

	// *** GUI handling
	int SetActiveLasNum(int value) ;
	int GetActiveLasNum(void) ;
	int UpdateCurrentCfgDisplayfromMemory(int module, int dut) ;
	int UpdateCfgMemoryfromDisplay(int module, int dut) ;
	int SetTestMode(int mode) ;
	int GetTestMode(void) ;
	int DisplayResults(int module) ;
	int UpdateIlkLimValDisp(int module) ;
	int UpdateIlkLimValStruct(int module);
	int UpdateIdSampleValDisp(int module);
	int UpdateIdSampleValStruct(int module);
	int InitSampleID(int module);
	int InitEnables(int module);
	int InitResTime(int module);
	int UpdateAndDispTotalTime(int module);
	int UpdateSensVal(int module) ;
	int UpdateTempVal(int module);
	int CheckIdle(void);
	CString GetDeviceName(void) ;
	int DisplayHighVolts(int module);

	// file handling
	int GetIniFileData(rackID rack_num) ;
    int LoadConfigFile(int module) ;
	int SaveConfigFile(int module) ;
	void OnBnClickedOpenFile(int module) ;

	int OpenLogFile(int module) ;
	int CloseLogFile(int module) ;
	int ReOpenLogFile(int module) ;
	int AcquireLogData(int module, bool flag = false) ;
	int WriteLogFile(int module, bool flag = false);

	int ParseCvsCfgBuffer( TCHAR * tcData, int module) ;

	// System time functions
	void GetUniqueTime(CString& UnqTime) ;
	void GetSysTime(CString& systime) ;

	//
	int ChangeHVCfg(int module, float value ) ;
	int ChangeILEAKCfg(int module, int chan, float value ) ;
	int ChangeIALRMCfg(int module, float value) ;
	int ChangeTrefCfg(int module, enum HTR_ID htr, float value ) ;
	int ChangeGateCfg(int module, float value);
	int ChangeChanIDCfg(int module, int chan, LPTSTR ) ;
	int ChangeModIDCfg(int module, LPTSTR ) ;
	int XferConfigToFpga( int module ) ;
	int GrabSampleID(int val);
	int ChangeLogFileName(int module, LPTSTR value);

	int CnvrtAdc2DegC(enum TC_ID TC, int val, float *degC);
	int aquireTempValues(int module);

	int m_cfg_Ndut ;
	int m_numModules ;
	int m_operation ;
	int m_NIDAQ_absent ;

	UINT m_time_increment ;
	CFont m_font;

	// command line argumants
	rackID m_rack_number ;
	CString m_ni_serial_num ;


	CString m_logfile_path[Nmod] ;            // path only
	CString m_logfile_name[Nmod] ;            // name used to open file
    CString m_cfgfile_path[Nmod] ;
	CString m_stsfile_path ;

	CFile m_logfile_handle[Nmod] ;            // handles needed for files
    CFile m_cfgfile_handle[Nmod] ;
	CFile m_stsfile_handle ;

	UINT_PTR m_timer_hndl ;                  // Timer handle, timer ID is 1, used for all modules

	// config calibration data for HV, TC, alarm & gate
	float m_hv_b0;
	float m_hv_b1;

	float m_temp_b0[8];
	float m_temp_b1[8];

	float m_alarm_b0;
	float m_alarm_b1;

	float m_gate_b0;
	float m_gate_b1;

// Dialog Data
	enum { IDD = IDD_MFCAPPLICATION1_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedRadio5();
	afx_msg void OnBnClickedRadio6();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedCancel();
	
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	afx_msg BOOL OnToolTipNotify (UINT id, NMHDR* pNMHDR, LRESULT* pResult);

	afx_msg void OnEnChangeEditModuleComment();
	afx_msg void OnUpdateEditChanID();

	afx_msg void OnIdok();
	afx_msg void OnIdclose();
	afx_msg void OnStnClickedBitmap1();
	CStatic m_rack_setup;
	afx_msg void OnStnClickedSetupText();
	afx_msg void OnEnChangeEdit12();
	afx_msg void OnEnChangeEdit72();
	afx_msg void OnEnChangeEdit62();
	afx_msg void OnEnChangeEdit63();
	afx_msg void OnEnChangeEdit133();
	afx_msg void OnEnChangeEdit122();
	afx_msg void OnEnChangeEdit109();
	afx_msg void OnEnChangeEdit40();
	afx_msg void OnEnChangeEdit10();
	afx_msg void OnEnChangeEdit39();
	afx_msg void OnEnChangeEdit9();
	afx_msg void OnEnChangeEdit38();
	afx_msg void OnEnChangeEdit8();
	afx_msg void OnEnChangeEdit37();
	afx_msg void OnEnChangeEdit7();
	afx_msg void OnEnChangeEdit36();
	afx_msg void OnEnChangeEdit6();
	afx_msg void OnEnChangeEdit35();
	afx_msg void OnEnChangeEdit5();
	afx_msg void OnEnChangeEdit34();
	afx_msg void OnEnChangeEdit4();
	afx_msg void OnEnChangeEdit33();
	afx_msg void OnEnChangeEdit3();
	afx_msg void OnEnChangeEdit32();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnEnChangeEdit11();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeEdit112();
	afx_msg void OnEnChangeEdit115();
	afx_msg void OnEnChangeEdit118();
	afx_msg void OnEnChangeEdit121();
	afx_msg void OnEnChangeEdit124();
	afx_msg void OnEnChangeEdit127();
	afx_msg void OnEnChangeEdit130();
	afx_msg void OnEnChangeEdit136();
	afx_msg void OnEnChangeEdit139();
	afx_msg void OnEnChangeEdit82();
	afx_msg void OnEnChangeEdit85();
	afx_msg void OnEnChangeEdit88();
	afx_msg void OnEnChangeEdit91();
	afx_msg void OnEnChangeEdit94();
	afx_msg void OnEnChangeEdit97();
	afx_msg void OnEnChangeEdit100();
	afx_msg void OnEnChangeEdit103();
	afx_msg void OnEnChangeEdit106();
	afx_msg void OnEnChangeEdit143();
	afx_msg void OnBnClickedCheck25();
	afx_msg void OnBnClickedCheck26();
	afx_msg void OnBnClickedCheck21();
	afx_msg void OnBnClickedCheck22();
	afx_msg void OnBnClickedCheck23();
	afx_msg void OnBnClickedCheck24();
	afx_msg void OnBnClickedRadio7();
	afx_msg void OnBnClickedCheck27();
};
