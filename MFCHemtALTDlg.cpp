
// Copyright 2013 Prysm Inc.
// San Jose, CA, 95134
// btremaine@prysm.com
// btremaine@omnificsolutions.com
//
// MFCHemtALTDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MFCHemtALTApp.h"
#include "MFCHemtALTDlg.h"
#include "CHemtTest.h"
#include "CCfgFile.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CAboutDlg dialog used for App About
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCHemtALTDlg dialog
CMFCHemtALTDlg::CMFCHemtALTDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFCHemtALTDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCHemtALTDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SETUP_TEXT, m_rack_setup);
}

BEGIN_MESSAGE_MAP(CMFCHemtALTDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	
	ON_BN_CLICKED(IDC_RADIO1, &CMFCHemtALTDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CMFCHemtALTDlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &CMFCHemtALTDlg::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO5, &CMFCHemtALTDlg::OnBnClickedRadio5)
	ON_BN_CLICKED(IDC_RADIO6, &CMFCHemtALTDlg::OnBnClickedRadio6)
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCHemtALTDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCHemtALTDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFCHemtALTDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CMFCHemtALTDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CMFCHemtALTDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDCANCEL, &CMFCHemtALTDlg::OnBnClickedCancel)

	ON_WM_TIMER()

	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXT, 0, 0xFFFF, OnToolTipNotify)
	
	ON_COMMAND(IDOK, &CMFCHemtALTDlg::OnIdok)                             // captures edit changes
	ON_COMMAND(IDCLOSE, &CMFCHemtALTDlg::OnIdclose)
	ON_STN_CLICKED(IDB_BITMAP1, &CMFCHemtALTDlg::OnStnClickedBitmap1)

	ON_EN_CHANGE(IDC_EDIT133, &CMFCHemtALTDlg::OnEnChangeEdit133)
	ON_EN_CHANGE(IDC_EDIT122, &CMFCHemtALTDlg::OnEnChangeEdit122)
	ON_EN_CHANGE(IDC_EDIT109, &CMFCHemtALTDlg::OnEnChangeEdit109)
	ON_EN_CHANGE(IDC_EDIT40, &CMFCHemtALTDlg::OnEnChangeEdit40)
	ON_EN_CHANGE(IDC_EDIT10, &CMFCHemtALTDlg::OnEnChangeEdit10)
	ON_EN_CHANGE(IDC_EDIT39, &CMFCHemtALTDlg::OnEnChangeEdit39)
	ON_EN_CHANGE(IDC_EDIT9, &CMFCHemtALTDlg::OnEnChangeEdit9)
	ON_EN_CHANGE(IDC_EDIT38, &CMFCHemtALTDlg::OnEnChangeEdit38)
	ON_EN_CHANGE(IDC_EDIT8, &CMFCHemtALTDlg::OnEnChangeEdit8)
	ON_EN_CHANGE(IDC_EDIT37, &CMFCHemtALTDlg::OnEnChangeEdit37)
	ON_EN_CHANGE(IDC_EDIT7, &CMFCHemtALTDlg::OnEnChangeEdit7)
	ON_EN_CHANGE(IDC_EDIT36, &CMFCHemtALTDlg::OnEnChangeEdit36)
	ON_EN_CHANGE(IDC_EDIT6, &CMFCHemtALTDlg::OnEnChangeEdit6)
	ON_EN_CHANGE(IDC_EDIT35, &CMFCHemtALTDlg::OnEnChangeEdit35)
	ON_EN_CHANGE(IDC_EDIT5, &CMFCHemtALTDlg::OnEnChangeEdit5)
	ON_EN_CHANGE(IDC_EDIT34, &CMFCHemtALTDlg::OnEnChangeEdit34)
	ON_EN_CHANGE(IDC_EDIT4, &CMFCHemtALTDlg::OnEnChangeEdit4)
	ON_EN_CHANGE(IDC_EDIT33, &CMFCHemtALTDlg::OnEnChangeEdit33)
	ON_EN_CHANGE(IDC_EDIT3, &CMFCHemtALTDlg::OnEnChangeEdit3)
	ON_EN_CHANGE(IDC_EDIT32, &CMFCHemtALTDlg::OnEnChangeEdit32)
	ON_EN_CHANGE(IDC_EDIT2, &CMFCHemtALTDlg::OnEnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT11, &CMFCHemtALTDlg::OnEnChangeEdit11)
	ON_EN_CHANGE(IDC_EDIT1, &CMFCHemtALTDlg::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT112, &CMFCHemtALTDlg::OnEnChangeEdit112)
	ON_EN_CHANGE(IDC_EDIT115, &CMFCHemtALTDlg::OnEnChangeEdit115)
	ON_EN_CHANGE(IDC_EDIT118, &CMFCHemtALTDlg::OnEnChangeEdit118)
	ON_EN_CHANGE(IDC_EDIT121, &CMFCHemtALTDlg::OnEnChangeEdit121)
	ON_EN_CHANGE(IDC_EDIT124, &CMFCHemtALTDlg::OnEnChangeEdit124)
	ON_EN_CHANGE(IDC_EDIT127, &CMFCHemtALTDlg::OnEnChangeEdit127)
	ON_EN_CHANGE(IDC_EDIT130, &CMFCHemtALTDlg::OnEnChangeEdit130)
	ON_EN_CHANGE(IDC_EDIT136, &CMFCHemtALTDlg::OnEnChangeEdit136)
	ON_EN_CHANGE(IDC_EDIT139, &CMFCHemtALTDlg::OnEnChangeEdit139)
	ON_EN_CHANGE(IDC_EDIT82, &CMFCHemtALTDlg::OnEnChangeEdit82)
	ON_EN_CHANGE(IDC_EDIT85, &CMFCHemtALTDlg::OnEnChangeEdit85)
	ON_EN_CHANGE(IDC_EDIT88, &CMFCHemtALTDlg::OnEnChangeEdit88)
	ON_EN_CHANGE(IDC_EDIT91, &CMFCHemtALTDlg::OnEnChangeEdit91)
	ON_EN_CHANGE(IDC_EDIT94, &CMFCHemtALTDlg::OnEnChangeEdit94)
	ON_EN_CHANGE(IDC_EDIT97, &CMFCHemtALTDlg::OnEnChangeEdit97)
	ON_EN_CHANGE(IDC_EDIT100, &CMFCHemtALTDlg::OnEnChangeEdit100)
	ON_EN_CHANGE(IDC_EDIT103, &CMFCHemtALTDlg::OnEnChangeEdit103)
	ON_EN_CHANGE(IDC_EDIT106, &CMFCHemtALTDlg::OnEnChangeEdit106)
	ON_EN_CHANGE(IDC_EDIT143, &CMFCHemtALTDlg::OnEnChangeEdit143)
	ON_BN_CLICKED(IDC_CHECK25, &CMFCHemtALTDlg::OnBnClickedCheck25)
	ON_BN_CLICKED(IDC_CHECK26, &CMFCHemtALTDlg::OnBnClickedCheck26)
	ON_BN_CLICKED(IDC_CHECK21, &CMFCHemtALTDlg::OnBnClickedCheck21)
	ON_BN_CLICKED(IDC_CHECK22, &CMFCHemtALTDlg::OnBnClickedCheck22)
	ON_BN_CLICKED(IDC_CHECK23, &CMFCHemtALTDlg::OnBnClickedCheck23)
	ON_BN_CLICKED(IDC_CHECK24, &CMFCHemtALTDlg::OnBnClickedCheck24)
	ON_BN_CLICKED(IDC_RADIO7, &CMFCHemtALTDlg::OnBnClickedRadio7)
	ON_BN_CLICKED(IDC_CHECK27, &CMFCHemtALTDlg::OnBnClickedCheck27)
END_MESSAGE_MAP()


// CMFCHemtALTDlg message handlers

BOOL CMFCHemtALTDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	EnableToolTips();
	
	// ==================================================================================
	// get command line arguments as rack #
	if(__argc == 1)
	{
		m_rack_number = ONE ;   // racks [1 - 3]
	}
	else if(__argc>=2)
	{
		// get rack #
		int num = atoi(__argv[1]) ;

		switch (num)
		{
			case 1: 
				m_rack_number = ONE ;
				break ;
			case 2: 
				m_rack_number = TWO ;
				break ;
			case 3:
				m_rack_number = THREE ;
				break ;
			default:
				m_rack_number = ONE ;
		}
	}

	// ==================================================================================
    // ini file has default settings independent of state of the test (paths/ file names)
	//   --- read-only, nominally never changes once tester is setup & running
	//   --- default file paths for *.cfg & *.log files.
    GetIniFileData(m_rack_number) ;
	GetTempCalData(m_rack_number);
	MBT = new CHemtTest(m_ni_serial_num) ;

	m_NIDAQ_absent = MBT->m_NIDAQ_absent;

	if (m_NIDAQ_absent){
		CString str = "Exit program - No NI board found\r\nCheck serial #" + m_ni_serial_num;
		str += " or USB cable.";
		AfxMessageBox(str);
		m_cancel = 1 ;
		OnBnClickedCancel();
	}
	
	if (!m_NIDAQ_absent)
	{
		InitCfgSettings();

		// Display setup information
		CString setup;
		char * buff = new char[32];
		sprintf(&buff[0], "RACK: #%1d, Device ", m_rack_number);
		setup.SetString(buff);
		delete[] buff;

#ifdef DEBUG_NO_NIDAQ
		setup.Append(m_ni_serial_num);
#else
		setup.Append(GetDeviceName());
#endif
		GetDlgItem((IDC_SETUP_TEXT))->SetWindowText((LPCTSTR)setup);
		// ---------------------------------------------------------------
		LOGFONT lf;
		memset(&lf, 0, sizeof(LOGFONT));   // Clear out structure.
		lf.lfHeight = 20;                  // Request a 20-pixel-high font
		strcpy(lf.lfFaceName, "Arial");    //    with face name "Arial".
		m_font.DeleteObject();
		m_font.CreateFontIndirect(&lf);    // Create the font.
		// Use the font to paint a control. This code assumes
		GetDlgItem(IDC_HV_STATUS)->SetFont(&m_font);
		// ----
		memset(&lf, 0, sizeof(LOGFONT));   // Clear out structure.
		lf.lfHeight = 20;                  // Request a 20-pixel-high font
		strcpy(lf.lfFaceName, "Arial");    //    with face name "Arial".
		m_font.DeleteObject();
		m_font.CreateFontIndirect(&lf);    // Create the font.
		// Use the font to paint a control. This code assumes
		GetDlgItem(IDC_EDIT70)->SetFont(&m_font);
		// ---- IDC_STATIC_LOGO62
		//CBitmap bmp;
		//bmp.LoadBitmap(IDB_LOGO);
		//m_logo = (CStatic *)GetDlgItem(IDC_STATIC_LOGO);
		//m_logo->SetBitmap(bmp);   


		// initialize default configuration settings of window
		InitCfgSettings();

		// =================================================================================
		// cfg file has specific settings per module
		//   --- read/write
		// log file has run-in data history
		//   --- read/write
		//
		for (int i = 0; i < Nmod; i++)
		{
			// initalizes Module struc 
			LoadConfigFile(i);
		}

		// update configuration display for current selected module
		UpdateCurrentCfgDisplayfromMemory(MBT->m_active_module, m_cfg_Ndut);
		UpdateIlkLimValDisp(MBT->m_active_module);
		InitResTime(MBT->m_active_module);
		InitSampleID(MBT->m_active_module);
		InitEnables(MBT->m_active_module);

		// ==================================================================================
		// initialize sensor inital & current DISPLAY values to zero for GUI active module
		InitSenVal(MBT->m_active_module);

		// initialize Elapsed time
		InitElapsedTime();
		UpdateAndDispTotalTime(MBT->m_active_module);
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// ============================================================================
// ----------------------------------------------------------------------------
BOOL CMFCHemtALTDlg::OnToolTipNotify(UINT id, NMHDR* pNMHDR, LRESULT* pResult)
{
    // Get the tooltip structure.
    TOOLTIPTEXT *pTTT = (TOOLTIPTEXT *)pNMHDR;

    // Actually the idFrom holds Control's handle.
    UINT CtrlHandle = pNMHDR->idFrom;

    // Check once again that the idFrom holds handle itself.
    if (pTTT->uFlags & TTF_IDISHWND)
    {
        // Get the control's ID.
        UINT nID = ::GetDlgCtrlID( HWND( CtrlHandle ));

        // Now you have the ID. depends on control,
        // set your tooltip message.
        switch( nID )
        {
        case IDC_BUTTON1:
                // Set the tooltip text.
                pTTT->lpszText = _T("Start the test on this module.");
            break;

        case IDC_BUTTON2:
            // Set the tooltip text.
            pTTT->lpszText = _T("Update the configuration memory of this Ndut.");
            break;

		case IDC_BUTTON3:
            // Set the tooltip text.
            pTTT->lpszText = _T("End the test on this module.");
            break;
		
		case IDC_BUTTON4:
            // Set the tooltip text.
            pTTT->lpszText = _T("Load the configuration file for this module.");
            break;
		
		case IDC_BUTTON5:
            // Set the tooltip text.
            pTTT->lpszText = _T("Save the configuration file for this module.");
            break;

		case IDC_EDIT1:
		case IDC_EDIT2:
		case IDC_EDIT3:
		case IDC_EDIT4:
		case IDC_EDIT5:
		case IDC_EDIT6:
		case IDC_EDIT7:
		case IDC_EDIT8:
		case IDC_EDIT9:
		case IDC_EDIT10:
		case IDC_EDIT11:
		case IDC_EDIT32:
		case IDC_EDIT33:
		case IDC_EDIT34:
		case IDC_EDIT35:
		case IDC_EDIT36:
		case IDC_EDIT37:
		case IDC_EDIT38:
		case IDC_EDIT39:
		case IDC_EDIT40:
			// Set the tooltip text.
			pTTT->lpszText = _T("IlkLim in uA, software limit.");
			break;

		case IDC_EDIT143:
			// Set the tooltip text.
			pTTT->lpszText = _T("Gate voltage, V.");
			break;

		case IDC_EDIT62:
            // Set the tooltip text.
            pTTT->lpszText = _T("Ialarm in uA, hardware threshold.");
            break;

		case IDC_EDIT63:
            // Set the tooltip text.
            pTTT->lpszText = _T("Tref1  deg C .");
            break;

        case IDC_EDIT65:
            // Set the tooltip text.
            pTTT->lpszText = _T("High voltage, V.");
            break;

		case IDC_EDIT68:
            // Set the tooltip text.
            pTTT->lpszText = _T("Description of the run on this module.");
            break;

		case IDC_EDIT69:
            // Set the tooltip text.
            pTTT->lpszText = _T("Tref2 deg C .");
            break;

		case IDC_EDIT72:
			// Set the tooltip text.
			pTTT->lpszText = _T("Tref3  deg C .");
			break;

		case IDC_EDIT73:
			// Set the tooltip text.
			pTTT->lpszText = _T("Tref4  deg C .");
			break;

		case IDC_RADIO1:
		case IDC_RADIO2:
		case IDC_RADIO3:
            // Set the tooltip text.
			pTTT->lpszText = _T("Select active module");
            break;

		case IDC_RADIO5:
			pTTT->lpszText = _T("Select normal run mode");
			break ;

		case IDC_RADIO6:
			pTTT->lpszText = _T("Select setup mode with PSU on");
			break ;

		case IDC_EDIT64:
			// Set the tooltip text.
			pTTT->lpszText = _T("module run time, hrs.");
			break ;

		case IDC_EDIT140:
			// Set the tooltip text.
			pTTT->lpszText = _T("log file ex: c:\\new_file.log");
			break;

		case IDCANCEL:
            // Set the tooltip text.
			pTTT->lpszText = _T("Exit the program !!?");
            break;

		case IDC_CHECK27:
			// Set the tooltip text.
			pTTT->lpszText = _T("Ilk hi/low gain, hi=set.");
			break;

        default:
            // Set the tooltip text.
            pTTT->lpszText = _T("Tooltips everywhere!!!");
            break;
        }

        return TRUE;
    }

    // Not handled.
    return FALSE;
}

// ----------------------------------------------------------------------------
void CMFCHemtALTDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ----------------------------------------------------------------------------
// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCHemtALTDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ----------------------------------------------------------------------------
// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCHemtALTDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// ----------------------------------------------------------------------------
void CMFCHemtALTDlg::InitTestRadioBut(void)
{
	// initialize radio button for module 0 active
	CButton *pButt = (CButton*)GetDlgItem(IDC_RADIO1);
	pButt->SetFocus();
	pButt->SetCheck(true);
	MBT->m_active_module = 0;

	// test mode
	pButt = (CButton*)GetDlgItem(IDC_RADIO7);
	pButt->SetCheck(true);
	m_operation = TEST2_MODE;
}

// ----------------------------------------------------------------------------
void CMFCHemtALTDlg::OnBnClickedRadio1()
{
	// Select module #0
	// TODO: Add your control notification handler code here
    // Add check for module presence 


	MBT->m_active_module = 0 ;
	m_operation = MBT->Module[MBT->m_active_module].op_mode;
	UpdateModuleDisplay(MBT->m_active_module);
	UpdateIlkLimValDisp(MBT->m_active_module);
	UpdateIdSampleValDisp(MBT->m_active_module);
	UpdateSensVal(MBT->m_active_module);
	InitResTime(MBT->m_active_module);
	UpdateAndDispTotalTime(MBT->m_active_module);
}

// ----------------------------------------------------------------------------
void CMFCHemtALTDlg::OnBnClickedRadio2()
{
	// Select module #1
	// TODO: Add your control notification handler code here
	MBT->m_active_module = 1 ;
	m_operation = MBT->Module[MBT->m_active_module].op_mode;
	UpdateModuleDisplay(MBT->m_active_module);
	UpdateIlkLimValDisp(MBT->m_active_module);
	UpdateIdSampleValDisp(MBT->m_active_module);
	UpdateSensVal(MBT->m_active_module);
	InitResTime(MBT->m_active_module);
	UpdateAndDispTotalTime(MBT->m_active_module);
}

// ----------------------------------------------------------------------------
void CMFCHemtALTDlg::OnBnClickedRadio3()
{
	// Select module #2
	// TODO: Add your control notification handler code here
	MBT->m_active_module = 2 ;
	m_operation =   MBT->Module[2].op_mode ;
	UpdateModuleDisplay(MBT->m_active_module);
	UpdateIlkLimValDisp(MBT->m_active_module);
	UpdateIdSampleValDisp(MBT->m_active_module);
	UpdateSensVal(MBT->m_active_module);
	InitResTime(MBT->m_active_module);
	UpdateAndDispTotalTime(MBT->m_active_module);
}

// ----------------------------------------------------------------------------
void CMFCHemtALTDlg::OnBnClickedRadio5()
{
	// TODO: Add your control notification handler code here
	// Operating mode: Auto
	if (CheckIdle())
	{
		if (IsDlgButtonChecked(IDC_RADIO5))
		{
			m_operation = AUTO_MODE;   // "auto"
			MBT->Module[MBT->m_active_module].op_mode = m_operation;
			SetTestMode(m_operation);
		}
		else {
			m_operation = IDLE_MODE;   // "idle"
			MBT->Module[MBT->m_active_module].op_mode = m_operation;
			SetTestMode(m_operation);
		}
	}
	else
	{
		AfxMessageBox("State not IDLE, END first!", MB_OK);
	}
}

// ----------------------------------------------------------------------------
void CMFCHemtALTDlg::OnBnClickedRadio6()
{
	// TODO: Add your control notification handler code here
	// Operating mode: Test 1 - stop auto mode & turn ON PSU
	if (CheckIdle())
	{
		if (IsDlgButtonChecked(IDC_RADIO6))
		{
			m_operation = TEST1_MODE;  // "test mode"
			int module = MBT->m_active_module;
			MBT->Module[module].op_mode = m_operation;
			
			// Read temperature settings & display
			AcquireLogData(module);             // updates .HVref
			// aquireTempValues(module);
			UpdateTempVal(module);				// displays
			SetTestMode(m_operation);

		}
		else {
			m_operation = IDLE_MODE; // "idle"
			MBT->Module[MBT->m_active_module].op_mode = m_operation;
			SetTestMode(m_operation);
		}
	}
	else
	{
		AfxMessageBox("State not IDLE, END first!", MB_OK);
	}

}

// ----------------------------------------------------------------------------
int CMFCHemtALTDlg::CheckIdle(void)
{
	// check if active gui selection is in IDLE mode
	if (MBT->Module[MBT->m_active_module].state == IDLE)
	{
		return (1);
	}

	return (0);
}

// ----------------------------------------------------------------------------
void CMFCHemtALTDlg::InitSenVal(int module)
{
	UpdateSensVal(module) ;
}

// ----------------------------------------------------------------------------
void CMFCHemtALTDlg::InitCfgSettings()
{
	// initialize configuration settings

	m_cfg_Ndut = 1;					// allowable range 1:20
	MBT->m_active_module = 0;
	MBT->m_timer_status = 0;		// no master timer active
	m_operation = TEST1_MODE;       // test mode (0 = auto)

	for (int i = 0; i < Nmod; i++)
	{
		MBT->m_hv_set_b0[i] = m_hv_set_b0[i];	// *.ini values to set HV dac from float voltage
		MBT->m_hv_set_b1[i] = m_hv_set_b1[i];

		MBT->m_hv_rd_b0[i] = m_hv_rd_b0[i];	// *.ini values to set HV display from ADC value
		MBT->m_hv_rd_b1[i] = m_hv_rd_b1[i];

		MBT->m_gate_b0[i] = m_gate_b0[i];     // *.ini values to set gate dac from float voltage
		MBT->m_gate_b1[i] = m_gate_b1[i];

		MBT->m_alarm_b0[i] = m_alarm_b0[i];   // *.ini values to set ILK alarm DAC
		MBT->m_alarm_b1[i] = m_alarm_b1[i];
	}

	for (int j = TC1; j < TCE; j++)
	{
		for (int i = 0; i < Nmod; i++)
		{
			MBT->m_temp_b0[i][j] = m_temp_b0[i][j];		// *.ini values for temp cal
			MBT->m_temp_b1[i][j] = m_temp_b1[i][j];
		}
	}

	for (int j = HTR1; j < HTRE; j++)
	{
		for (int i = 0; i < Nmod; i++)
		{
			MBT->m_tempref_b0[i][j] = m_tempref_b0[i][j]; // *.ini values for temp TREF cal
			MBT->m_tempref_b1[i][j] = m_tempref_b1[i][j];
		}
	}

	MBT->m_tc_cntr = m_tc_cntr;
	MBT->m_tc_dbnd = m_tc_dbnd;
	MBT->m_tc_toff_min = m_tc_toff_min;
	MBT->m_tc_ton_max= m_tc_ton_max;

	InitTestRadioBut();

}

// ----------------------------------------------------------------------------
void CMFCHemtALTDlg::InitElapsedTime()
{
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT64) ;
	pEdit->SetWindowText("0") ;
}

// ----------------------------------------------------------------------------
void CMFCHemtALTDlg::OnBnClickedButton1()  // Run/Pause button
{
	// TODO: Add your control notification handler code here
	// Update button state and take action

	// get selected module
	int module = MBT->m_active_module ;

	if(GetTestMode()) 
	{
		AfxMessageBox("Put in Auto mode first!", MB_OK) ;
		return ; // don't switch out of test mode
	}

#ifdef DEBUG_NO_NIDAQ
	AfxMessageBox("Debug mode w/ No Hardware!", MB_OK);
#endif

	// based on module state, update buttons & take required action
	int current_state = MBT->Module[module].state ;

	CEdit *pEdit = (CEdit*)GetDlgItem(IDC_BUTTON1) ;
    CString message ;

	switch (current_state) {
		case IDLE: 
			if (AfxMessageBox("Is Config file okay ?",MB_YESNO) == IDNO)
			{
				return;
			}

			KillTimer(MSTR_TIMER_ID);  // kill while setting up new module for run mode then re-start
			MBT->m_timer_status = 0;

	        message.Format("Pause...") ;
			pEdit->SetWindowText(message);
			MBT->Module[module].state = RUNNING ;
			
			//   enable Ndut voltage & delay                                                                                                                                      
			MBT->SetHvEnable(module,true) ;
			Sleep(1000) ;
			if (1)
			{
				// kludge fix for adc first read 1/14/14 bpt
				int val;
				MBT->ReadSensorChan(module, 20, &val) ;
			}

			// offer recovery from power loss or re-boot
			// perform actions to start RUNNING
			//   transfer config file to FPGA

			XferConfigToFpga( module ) ;

			// enable TC servos
			MBT->EnableTcServos(module); 

			//   open logfile
			if (AfxMessageBox("Create new log file ?",MB_YESNO) == IDYES)
			{
				// Use file path/name already in:  m_logfile_path[module] 
				OpenLogFile(module);
				// created, now close until needed...
				CloseLogFile(module);
			}
			else
			{
				// TODO:     ### get path/name 
				OnBnClickedOpenFile(module);
				ReOpenLogFile(module);
				// now close until needed...
				CloseLogFile(module);
			}

			// Update logfile with initial measurement
			AcquireLogData(module, true) ;        // updates .HVref
			WriteLogFile(module, true);
			DisplayResults(module) ;
			
			//   start timer if not already running
			if (MBT->m_timer_status == 0)
			{
				m_timer_hndl = SetTimer(MSTR_TIMER_ID, m_time_increment, NULL);
				MBT->m_timer_status = 1;
			}

			break ;
		case PAUSED:
			message.Format("Pause...") ;
			pEdit->SetWindowText(message);
			MBT->Module[module].state = RUNNING ;
			// perform actions to resume RUNNING
			// -- Ndut power?
			// re-start timer if not running
			if (MBT->m_timer_status == 0)
			{
				m_timer_hndl = SetTimer(MSTR_TIMER_ID, m_time_increment, NULL);
				MBT->m_timer_status = 1;
			}

			// re-open file
			ReOpenLogFile(module) ;

			break ;
		case RUNNING:
			message.Format("Resume...") ;
			pEdit->SetWindowText(message);
			MBT->Module[module].state = PAUSED ;
			// perform actions to PAUSE
			// stop timer but leave open
			KillTimer(m_timer_hndl) ;
			// -- remove Ndut power?

			// close open file
			CloseLogFile(module) ;

			break ;
	}

}
// ----------------------------------------------------------------------------
int CMFCHemtALTDlg::SetTestMode( int mode )
{
    CString message ;
	CButton* pButt ;

	// get selected module
	int module = MBT->m_active_module ;

	// if module is running then auto mode keeps running

	// NOTE: MODULE 2 ON THE GUI DISPLAY IS BRD_ID [2'b10] and module 1 in software.

	switch (mode)
	{
	case AUTO_MODE:
		pButt = (CButton*)GetDlgItem(IDC_RADIO5) ; // Auto
		pButt->SetFocus() ;
	    pButt->SetCheck(true) ;
		MBT->SetHvEnable(module,true) ;  // PSU ON
		m_operation = mode ;
		break ;
	case TEST1_MODE:
		pButt = (CButton*)GetDlgItem(IDC_RADIO6) ;  // Test 1
		pButt->SetFocus() ;
	    pButt->SetCheck(true) ;
		MBT->SetHvDac(module, MBT->Module[module].HV);
		MBT->SetGate(module, MBT->Module[module].gate);
		MBT->SetHvEnable(module,true) ;  // PSU ON
		Sleep(100);
		DisplayHighVolts(module);
		m_operation = mode ;
		break;
	case TEST2_MODE:
		pButt = (CButton*)GetDlgItem(IDC_RADIO7);  // Test 2
		pButt->SetFocus();
		pButt->SetCheck(true);
		MBT->SetHvDac(module, 0);
		MBT->SetGate(module, 0);
		MBT->SetHvEnable(module, false);  // PSU OFF
		Sleep(100);
		DisplayHighVolts(module);
		m_operation = mode;
		break;
	default:
		m_operation = TEST2_MODE ;
		break ;
	}
  ///////////////////////////////////////////////
	return (0) ;

}

// ----------------------------------------------------------------------------
int CMFCHemtALTDlg::GetTestMode( void)
{
	return (m_operation) ;
}

// ----------------------------------------------------------------------------
void CMFCHemtALTDlg::OnBnClickedButton2()
{

	// TODO: Accept configuration change into memory

	UpdateCfgMemoryfromDisplay(MBT->m_active_module, m_cfg_Ndut) ;

}

// ----------------------------------------------------------------------------
void CMFCHemtALTDlg::OnBnClickedButton3()    // END button
{
	// TODO: Add your control notification handler code here
	// END the test on the current active module
	// get selected module
	int module = MBT->m_active_module ;

	// based on module state, update buttons & take required action
	int current_state = MBT->Module[module].state ;

	if (AfxMessageBox("End Module Run ?",MB_YESNO) == IDNO)
	{
		return;
	}

	CEdit *pEdit = (CEdit*)GetDlgItem(IDC_BUTTON1) ;
    CString message ;

	switch (current_state) {
		case IDLE: 
	        message.Format("Run...") ;
			pEdit->SetWindowText(message);
			MBT->Module[module].state = IDLE ;
			// No action required

			break ;
		case PAUSED:
			message.Format("Run...") ;
			pEdit->SetWindowText(message);
			MBT->Module[module].state = IDLE;
			// perform actions to stop test and save data

			// close file
			CloseLogFile(module) ;

			break ;
		case RUNNING:
			message.Format("Run...") ;
			pEdit->SetWindowText(message);
			MBT->Module[module].state = IDLE;
			// perform actions to stop test and save data
			{
				int timer_on = 0;
				for (int j = 0; j < Nmod; j++)
				{
					if (MBT->Module[j].state == RUNNING)
					{
						timer_on = 1;
					}
				}
				// kill timer if no process running
				if (timer_on == 0)
				{
					KillTimer(m_timer_hndl);
				}
			}

			// Close log file
			CloseLogFile(module);

			// Shutdown high voltage and Temp Control
			if (CheckModuleInstalled(module))
			{
				MBT->SetHvEnable(module, false);  // PSU OFF
				MBT->SetHvDac(module, 0);
				MBT->SetGate(module, 0);
				MBT->DisableTcServos(module);     // TC heaters off
			}

			break ;
		default:
			message.Format("ERROR !!...") ;
			pEdit->SetWindowText(message);
	}

}

// ----------------------------------------------------------------------------
void CMFCHemtALTDlg::OnBnClickedButton4()
{
	// TODO: Add your control notification handler code here

	// LOAD a configuration file for the current active module

	CCfgFile dlg;
	CWnd * pDlg = &dlg;

    LoadConfigFile(MBT->m_active_module) ;
	UpdateCurrentCfgDisplayfromMemory(MBT->m_active_module, m_cfg_Ndut ) ;
	InitResTime(MBT->m_active_module);
    
}

// ----------------------------------------------------------------------------
void CMFCHemtALTDlg::OnBnClickedButton5()
{
	// TODO: Add your control notification handler code here
	// SAVE a configuration file for the current active module

	// Update & Save Configuration file

	UpdateCfgMemoryfromDisplay(MBT->m_active_module, m_cfg_Ndut) ;
	SaveConfigFile(MBT->m_active_module) ;

}

//  ---------------------------------------------------------------------------
void CMFCHemtALTDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here

	if (AfxMessageBox("Exit Program ?", MB_YESNO) == IDNO)
	{
		return;
	}

	// TODO: add code to shut off HV & turn off heaters before exiting.
	if (!m_cancel)
	{
		ShutDown();
	}	

	CDialogEx::OnCancel();
}

// ----------------------------------------------------------------------------
void CMFCHemtALTDlg::UpdateModuleDisplay( int module)
{
	// Selected module changed - update the display
	// Elapsed Time
	UpdateElapsedTimeDisp(module) ;

	// update Run/Pause button
	CEdit * pEdit = (CEdit*)GetDlgItem(IDC_BUTTON1) ;
	CString message ; 
	int state = MBT->Module[module].state ;

	switch (state) {
		case IDLE: 
	        message.Format("Run...") ;
			pEdit->SetWindowText(message);
			break ;
		case PAUSED:
			message.Format("Resume...") ;
			pEdit->SetWindowText(message);
			break ;
		case RUNNING:
			message.Format("Pause...") ;
			pEdit->SetWindowText(message);
			break ;
		default:
			message.Format("ERROR !!...") ;
			pEdit->SetWindowText(message);
	}

	// Update configuration display from ModuleT struc
	UpdateCurrentCfgDisplayfromMemory(module, m_cfg_Ndut) ;

	// Init Val, Val & % updated in AcquireLogData
}

// -----------------------------------------------------------------------------
void CMFCHemtALTDlg::UpdateModuleElapsedTime(UINT module)
{
	// update elapsed time using GetTickCount64
	// results are mSeconds

	unsigned long long tick, tick_start, ET ;

	tick = GetTickCount64() ;
	tick_start = MBT->Module[module].tick_start ;

	ET = tick - tick_start;

	MBT->Module[module].ET = ET;
}

// ----------------------------------------------------------------------------
void CMFCHemtALTDlg::UpdateElapsedTimeDisp(UINT module)
{
	// if active module update display (in hours)
	if(module == MBT->m_active_module)
	{
	  CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT64) ;
	  CString disp_time ; 
	  disp_time.Format("%7.3f", (float)(MBT->Module[module].ET)/3600000 ) ;
	  pEdit->SetWindowText(disp_time) ;
	}
}

// ----------------------------------------------------------------------------
void CMFCHemtALTDlg::OnTimer( UINT nIDEvent1)
{
	// Check RUNNING modules
	// nIDEvent1 is the timer ID == (1)
	if(nIDEvent1!=1) {
		AfxMessageBox("Error: Timer case!!",MB_OK);
	    return ;
	}

	// switch sequence for debug
	for (int i = 0; i < Nmod; i++) // #############
	{
		int j = i;		// use as module index
		


		if (MBT->Module[j].state == RUNNING)
		{
			// let any previous process complete (? bpt)
			Sleep(1000);
			
			// update elapsed time in data structure
			UpdateModuleElapsedTime(j);

			// update elapsed time display of active module
			UpdateElapsedTimeDisp(j);

			// update and display total time of active module
			UpdateAndDispTotalTime(j);

			// Get sensor value of all Nduts & store in logfile with elapsed time
			AcquireLogData(j);     // updates .HVref
			WriteLogFile(j);
			if (MBT->m_active_module == j)
			{
				DisplayResults(j);
			}
		}
	}

}

// ----------------------------------------------------------------------------
int CMFCHemtALTDlg::DisplayResults(int module)
{
	// Display latest measurement results in GUI window for module 
	// display voltage assuming conversion of 4.095v full-scale for ADC FS=4095.
	int retVal = 0 ;
	CString str = "0.000"  ;

	retVal = UpdateSensVal(module);
	retVal += UpdateTempVal(module);

	return (retVal) ;
}
// -----------------------------------------------------------------------------
int CMFCHemtALTDlg::InitSampleID(int module)
{
	// initialize display of Sample ID 
	int retVal = 0;
	CEdit* pEdit;
	CString str = "sample_ID";

	for (int i = 0; i<Ndut; i++)
	{
		CString str = (MBT->Module[module].SampleID[i]);

		switch (i)
		{
		case 0:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT112);
			break;
		case 1:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT115);
			break;
		case 2:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT118);
			break;
		case 3:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT121);
			break;
		case 4:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT124);
			break;
		case 5:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT127);
			break;
		case 6:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT130);
			break;
		case 7:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT133);
			break;
		case 8:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT136);
			break;
		case 9:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT139);
			break;
		case 10:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT82);
			break;
		case 11:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT85);
			break;
		case 12:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT88);
			break;
		case 13:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT91);
			break;
		case 14:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT94);
			break;
		case 15:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT97);
			break;
		case 16:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT100);
			break;
		case 17:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT103);
			break;
		case 18:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT106);
			break;
		case 19:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT109);
			break;
		default:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT112); // think of better default ###
			break;
		}

		pEdit->SetWindowText(str);
	}

	return (retVal);
}

// -----------------------------------------------------------------------------
int CMFCHemtALTDlg::InitEnables(int module)
{
	// initialize channel enables display 
	int retVal = 0;
	unsigned int integer;

	for (int i = 0; i<Ndut; i++)
	{
		bool flag = (MBT->Module[module].Enable[i]);
		if (flag) integer = BST_CHECKED;
		else integer = BST_UNCHECKED;

		switch (i)
		{
		case 0:
			CheckDlgButton(IDC_CHECK1, integer);
			break;
		case 1:
			CheckDlgButton(IDC_CHECK2, integer);
			break;
		case 2:
			CheckDlgButton(IDC_CHECK3, integer);
			break;
		case 3:
			CheckDlgButton(IDC_CHECK4, integer);
			break;
		case 4:
			CheckDlgButton(IDC_CHECK5, integer);
			break;
		case 5:
			CheckDlgButton(IDC_CHECK6, integer);
			break;
		case 6:
			CheckDlgButton(IDC_CHECK7, integer);
			break;
		case 7:
			CheckDlgButton(IDC_CHECK8, integer);
			break;
		case 8:
			CheckDlgButton(IDC_CHECK9, integer);
			break;
		case 9:
			CheckDlgButton(IDC_CHECK10, integer);;
			break;
		case 10:
			CheckDlgButton(IDC_CHECK11, integer);
			break;
		case 11:
			CheckDlgButton(IDC_CHECK12, integer);
			break;
		case 12:
			CheckDlgButton(IDC_CHECK13, integer);
			break;
		case 13:
			CheckDlgButton(IDC_CHECK14, integer);
			break;
		case 14:
			CheckDlgButton(IDC_CHECK15, integer);
			break;
		case 15:
			CheckDlgButton(IDC_CHECK16, integer);
			break;
		case 16:
			CheckDlgButton(IDC_CHECK17, integer);
			break;
		case 17:
			CheckDlgButton(IDC_CHECK18, integer);
			break;
		case 18:
			CheckDlgButton(IDC_CHECK19, integer);
			break;
		case 19:
			CheckDlgButton(IDC_CHECK20, integer);
			break;
		default:
			CheckDlgButton(IDC_CHECK1, integer); // think of better default ###
			break;
		}

	}

	return (retVal);
}

// -----------------------------------------------------------------------------
int CMFCHemtALTDlg::InitResTime(int module)
{
	// init display of resume time 
	int retVal = 0;
	CEdit* pEdit;
	CString str = "0.000";

	for (int i = 0; i<Ndut; i++)
	{
		ULONGLONG integer = (MBT->Module[module].resTime[i]);   // time in msec
		float fval = ((float) integer) / (3600000);       // hours

		str.Format("%4.2f", fval);

		switch (i)
		{
		case 0:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT110);   //
			break;
		case 1:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT113);
			break;
		case 2:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT116);
			break;
		case 3:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT119);
			break;
		case 4:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT122);
			break;
		case 5:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT125);
			break;
		case 6:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT128);
			break;
		case 7:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT131);
			break;
		case 8:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT134);
			break;
		case 9:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT137);
			break;
		case 10:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT80);
			break;
		case 11:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT83);
			break;
		case 12:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT86);
			break;
		case 13:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT89);
			break;
		case 14:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT92);
			break;
		case 15:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT95);
			break;
		case 16:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT98);
			break;
		case 17:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT101);
			break;
		case 18:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT104);
			break;
		case 19:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT107);
			break;
		default:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT110); // think of better default ###
			break;
		}

		pEdit->SetWindowText(str);
	}

	return (retVal);
}

// -----------------------------------------------------------------------------
int CMFCHemtALTDlg::UpdateAndDispTotalTime(int module)
{
	// init display of total time 
	int retVal = 0;
	CEdit* pEdit;
	CString str = "0.000";

	for (int i = 0; i<Ndut; i++)
	{
		ULONGLONG integer = (MBT->Module[module].resTime[i]) + (MBT->Module[module].ET);    // time in msec
		MBT->Module[module].totTime[i] = integer;

	    // Display total time
		float fval = ((float)integer) / (3600000);       // hours
		str.Format("%4.2f", fval);

		switch (i)
		{
		case 0:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT111);   //
			break;
		case 1:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT114);
			break;
		case 2:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT117);
			break;
		case 3:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT120);
			break;
		case 4:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT123);
			break;
		case 5:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT126);
			break;
		case 6:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT129);
			break;
		case 7:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT132);
			break;
		case 8:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT135);
			break;
		case 9:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT138);
			break;
		case 10:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT81);
			break;
		case 11:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT84);
			break;
		case 12:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT87);
			break;
		case 13:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT90);
			break;
		case 14:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT93);
			break;
		case 15:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT96);
			break;
		case 16:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT99);
			break;
		case 17:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT102);
			break;
		case 18:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT105);
			break;
		case 19:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT108);
			break;
		default:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT80); // think of better default ###
			break;
		}

		pEdit->SetWindowText(str);
	}

	return (retVal);
}

// -----------------------------------------------------------------------------
int CMFCHemtALTDlg::UpdateIdSampleValDisp(int module)
{
	// update display of ID Sample text from Module struc 
	int retVal = 0;
	CEdit* pEdit;

	for (int i = 0; i<Ndut; i++)
	{
		// get string from struc
		CString str = (MBT->Module[module].SampleID[i]);

		// get ptr to edit control
		switch (i)
		{
		case 0:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT112);
			break;
		case 1:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT115);
			break;
		case 2:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT118);
			break;
		case 3:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT121);
			break;
		case 4:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT124);
			break;
		case 5:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT127);
			break;
		case 6:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT130);
			break;
		case 7:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT133);
			break;
		case 8:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT136);
			break;
		case 9:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT139);
			break;
		case 10:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT82);
			break;
		case 11:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT85);
			break;
		case 12:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT88);
			break;
		case 13:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT91);
			break;
		case 14:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT94);
			break;
		case 15:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT97);
			break;
		case 16:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT100);
			break;
		case 17:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT103);
			break;
		case 18:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT106);
			break;
		case 19:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT109);
			break;
		default:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT112); // think of better default ###
			break;
		}

		pEdit->SetWindowText(str);
	}

	return (retVal);
}

// -----------------------------------------------------------------------------
int CMFCHemtALTDlg::UpdateIdSampleValStruct(int module)
{
	// update struct of ID Sample text from display 
	int retVal = 0;
	CEdit* pEdit;

	for (int i = 0; i<Ndut; i++)
	{

		// get ptr to edit control
		switch (i)
		{
		case 0:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT112);
			break;
		case 1:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT115);
			break;
		case 2:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT118);
			break;
		case 3:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT121);
			break;
		case 4:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT124);
			break;
		case 5:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT127);
			break;
		case 6:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT130);
			break;
		case 7:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT133);
			break;
		case 8:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT136);
			break;
		case 9:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT139);
			break;
		case 10:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT82);
			break;
		case 11:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT85);
			break;
		case 12:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT88);
			break;
		case 13:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT91);
			break;
		case 14:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT94);
			break;
		case 15:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT97);
			break;
		case 16:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT100);
			break;
		case 17:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT103);
			break;
		case 18:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT106);
			break;
		case 19:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT109);
			break;
		default:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT112); // think of better default ###
			break;
		}

		// get display string into struc
		CString str;
		pEdit->GetWindowText(str);
		MBT->Module[module].SampleID[i] = str;
	}

	return (retVal);
}

// -----------------------------------------------------------------------------
int CMFCHemtALTDlg::UpdateIlkLimValDisp(int module)
{ 
	// update display of IlkLim software threshold from Module struc 
	int retVal = 0 ;
	CEdit* pEdit ;
	CString str = "0.000";

	for(int i=0; i<Ndut; i++)
	{
		int integer = (MBT->Module[module].IlkLim[i]);
		float fval = ((float)integer / UA2TEN_NA);

		str.Format("%4.2f", fval); 

		switch (i) 
		{
		case 0:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT40) ;
			break;
		case 1:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT10) ;
			break;
		case 2:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT39) ;
			break;
		case 3:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT9) ;
			break;
		case 4:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT38) ;
			break;
		case 5:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT8) ;
			break;
		case 6:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT37) ;
			break;
		case 7:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT7) ;
			break;
		case 8:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT36) ;
			break;
		case 9:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT6) ;
			break;
		case 10:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT35) ;
			break;
		case 11:
            pEdit = (CEdit*)GetDlgItem(IDC_EDIT5) ;
			break;
		case 12:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT34) ;
			break;
		case 13:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT4) ;
			break;
		case 14:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT33) ;
			break;
		case 15:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT3) ;
			break;
		case 16:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT32) ;
			break;
		case 17:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT2) ;
			break;
		case 18:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT11) ;
			break;
		case 19:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT1) ;
			break;
		default:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT1) ; // think of better default ###
			break;
		}

		pEdit->SetWindowText(str) ;
	}

	str.Format("%4.2f", ((float) MBT->Module[module].HVref) / FLOAT2FXD);
	pEdit = (CEdit*)GetDlgItem(IDC_EDIT70);
	pEdit->SetWindowText(str);

	return (retVal) ;
}

// -----------------------------------------------------------------------------
int CMFCHemtALTDlg::UpdateIlkLimValStruct(int module)
{
	// update Module struct for IlkLim from display 
	int retVal = 0;
	CEdit* pEdit;
	CString str;

	for (int i = 0; i<Ndut; i++)
	{
		
		switch (i)
		{
		case 0:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT40);
			break;
		case 1:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT10);
			break;
		case 2:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT39);
			break;
		case 3:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT9);
			break;
		case 4:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT38);
			break;
		case 5:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT8);
			break;
		case 6:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT37);
			break;
		case 7:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT7);
			break;
		case 8:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT36);
			break;
		case 9:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT6);
			break;
		case 10:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT35);
			break;
		case 11:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT5);
			break;
		case 12:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT34);
			break;
		case 13:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT4);
			break;
		case 14:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT33);
			break;
		case 15:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT3);
			break;
		case 16:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT32);
			break;
		case 17:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT2);
			break;
		case 18:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT11);
			break;
		case 19:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT1);
			break;
		default:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT1); // think of better default ###
			break;
		}


		// get display string into struc
		pEdit->GetWindowText(str);

		float fval = atof(str);
		int integer = ((float)fval * UA2TEN_NA);

		MBT->Module[module].IlkLim[i] = integer;

	}

	str.Format("%4.2f", ((float)MBT->Module[module].HVref) / FLOAT2FXD);
	pEdit = (CEdit*)GetDlgItem(IDC_EDIT70);
	pEdit->SetWindowText(str);

	return (retVal);
}

// -----------------------------------------------------------------------------
int CMFCHemtALTDlg::UpdateTempVal(int module)
{
	// Update Temperature readings
	int retVal = 0;
	CEdit* pEdit;
	CString str = "0.00";

	for (int i= TC1; i< TCE; i++)
	{
		str.Format("%4.1f", ((float)MBT->Module[module].TMEA[i] / FLOAT2FXD));

		switch (i)
		{
		case TC1:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT67);
			break;
		case TC2:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT74);
			break;
		case TC3:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT75);
			break;
		case TC4:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT76);
			break;
		case TC5:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT77);
			break;
		case TC6:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT78);
			break;
		case TC7:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT79);
			break;
		case TC8:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT141);
			break;
		default:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT67);
		}

		pEdit->SetWindowText(str);
	}

	return (retVal);
}

// -----------------------------------------------------------------------------
int CMFCHemtALTDlg::UpdateSensVal(int module)
{
	// Update current sensor value, lastVal (measured leakage)
	int retVal = 0 ;
	CEdit* pEdit ;
	CString str = "0.000";


	for(int i=0; i<Ndut; i++)
	{
		
		str.Format("%4.2f", ((float) MBT->Module[module].lastVal[i]) / UA2TEN_NA) ;

		switch (i) 
		{
		case 0:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT50) ;
			break;
		case 1:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT21) ;
			break;
		case 2:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT49) ;
			break;
		case 3:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT20) ;
			break;
		case 4:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT48) ;
			break;
		case 5:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT19) ;
			break;
		case 6:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT47) ;
			break;
		case 7:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT18) ;
			break;
		case 8:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT46) ;
			break;
		case 9:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT17) ;
			break;
		case 10:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT45) ;
			break;
		case 11:
            pEdit = (CEdit*)GetDlgItem(IDC_EDIT16) ;
			break;
		case 12:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT44) ;
			break;
		case 13:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT15) ;
			break;
		case 14:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT43) ;
			break;
		case 15:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT14) ;
			break;
		case 16:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT42) ;
			break;
		case 17:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT13) ;
			break;
		case 18:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT41) ;
			break;
		case 19:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT12) ;
			break;
		default:
			pEdit = (CEdit*)GetDlgItem(IDC_EDIT12) ; // think of better default ###
			break;
		}

		pEdit->SetWindowText(str) ;
	}

	str.Format("%4.3f", ((float) MBT->Module[module].HVref) / FLOAT2FXD);
	pEdit = (CEdit*)GetDlgItem(IDC_EDIT70);
	pEdit->SetWindowText(str);

	return (retVal) ;
}

// -----------------------------------------------------------------------------
int CMFCHemtALTDlg::SetActiveLasNum(int value)
{
	// update active Ndut # being used by GUI
	if ( (value >= 0) && (value < Ndut ) )
	{
		m_cfg_Ndut = value ;
		return (0) ;
	}
	else return (-1) ;
}

// ----------------------------------------------------------------------------
int CMFCHemtALTDlg::GetActiveLasNum(void)
{
	// get active Ndut # being used by GUI
    return (m_cfg_Ndut) ;
}

// ----------------------------------------------------------------------------
int CMFCHemtALTDlg::ChangeHVCfg(int module, float value )
{
	// Change HV value in configuration memory
	// convert (float) value in V to (int) adc value
	        // TODO
	// update in memory
	MBT->Module[module].HV = (int) (value*m_hv_rd_b1[module] + m_hv_rd_b0[module]) ;

	return (0) ;
}

// ----------------------------------------------------------------------------
int CMFCHemtALTDlg::ChangeGateCfg(int module, float value)
{
	// Change Gate value in configuration memory
	// convert (float) value in V to (int) fixed point
	// update in memory
	MBT->Module[module].gate = (int)(value * FLOAT2FXD);

	return (0);
}

// ----------------------------------------------------------------------------
int CMFCHemtALTDlg::ChangeILEAKCfg(int module, int chan, float value )
{
	// Change ILEAK value in configuration memory (software limit)
	// input is uA converted to int fixed point
	// update in memory

	MBT->Module[module].IlkLim[chan] = (int) (value * UA2TEN_NA) ;

	return (0) ;
}

// ----------------------------------------------------------------------------
int CMFCHemtALTDlg::ChangeIALRMCfg(int module, float value)
{
	// Change IALARM value in configuration memory is global limit
	// input is uA converted to int fixed point
	// update in memory

	MBT->Module[module].Alarm = (int)(value * UA2TEN_NA);

	return (0);
}

// ----------------------------------------------------------------------------
int CMFCHemtALTDlg::ChangeTrefCfg(int module, HTR_ID chan, float value )
{
	// Change Tref value in configuration memory
	// value is (float) deg C converted to fixed point int 10th's deg C
	// update in memory

	MBT->Module[module].TREF[chan] = (int) (value * FLOAT2FXD) ;

	return (0) ;
}

// ----------------------------------------------------------------------------
int CMFCHemtALTDlg::ChangeChanIDCfg(int module, int chan, LPTSTR value )
{
	// Change Chan ID string in configuration memory
	// check limits
	     // TODO  ** remove ?
	// update in memory
    //  MBT->Module[module].ID[chan] = value ;

	return (0) ;
}
// ----------------------------------------------------------------------------
int CMFCHemtALTDlg::ChangeLogFileName(int module, LPTSTR value)
{
	// Change Module logfile name string in configuration memory
	// check limits
	// TODO
	// update in memory

	m_logfile_path[module] = value;

	return (0);
}

// ----------------------------------------------------------------------------
int CMFCHemtALTDlg::ChangeModIDCfg(int module, LPTSTR value )
{
	// Change Module ID string in configuration memory
	// check limits
	     // TODO
	// update in memory
	MBT->Module[module].runComment = value ;

	return (0) ;
}

// ----------------------------------------------------------------------------
void CMFCHemtALTDlg::OnIdok()
{
	// TODO: Add your command handler code here

	// find the source of the event and process accordingly
	LPTSTR s = new TCHAR[255] ;

    CWnd* pwndCtrl = GetFocus();
	//CWnd* pwndCtrlNext = pwndCtrl;
	CWnd* pEditControl;
	int handle = pwndCtrl->GetDlgCtrlID();
    int value = 0 ;

	int module = MBT->m_active_module ;

	switch (handle) {

		// ------------------------------------------------
		// dut dependent values



		// ------------------------------------------------
		// global values

		case IDC_EDIT143: // Gate
			pEditControl = (CEdit*)GetDlgItem(IDC_EDIT143);
		    pEditControl->GetWindowText(s, 255);

			ChangeGateCfg(module, (float) atof(s)) ;                         //xxxxxxxxxx
			break ;

		case IDC_EDIT65: // HV
			pEditControl = (CEdit*)GetDlgItem(IDC_EDIT65);
			pEditControl->GetWindowText(s, 255);

			ChangeHVCfg(module, (float) atof(s));
			break;

		case IDC_EDIT62: // Ialarm
			pEditControl = (CEdit*)GetDlgItem(IDC_EDIT62);
			pEditControl->GetWindowText(s, 255);

			ChangeIALRMCfg(module, (float) atof(s));                           //xxxxxxxxxxxxxxx
			break;

		case IDC_EDIT63: // Tref1
			pEditControl = (CEdit*)GetDlgItem(IDC_EDIT63);
			pEditControl->GetWindowText(s, 255);

			ChangeTrefCfg(module, HTR1, (float) atof(s));
			break;

		case IDC_EDIT69: // Tref2
			pEditControl = (CEdit*)GetDlgItem(IDC_EDIT69);
			pEditControl->GetWindowText(s, 255);

			ChangeTrefCfg(module, HTR2, (float) atof(s));
			break;

		case IDC_EDIT72: // Tref3
			pEditControl = (CEdit*)GetDlgItem(IDC_EDIT72);
			pEditControl->GetWindowText(s, 255);

			ChangeTrefCfg(module, HTR3, (float) atof(s));
			break;

		case IDC_EDIT73: // Tref4
			pEditControl = (CEdit*)GetDlgItem(IDC_EDIT73);
			pEditControl->GetWindowText(s, 255);

			ChangeTrefCfg(module, HTR4, (float) atof(s));
			break;

		case IDC_EDIT68: // Run Comment
			pEditControl = (CEdit*)GetDlgItem(IDC_EDIT68);
		    pEditControl->GetWindowText(s, 255);
			// save text Run comment

			ChangeModIDCfg(module, s) ;
			break ;

		case IDC_EDIT140: // Logfile
			pEditControl = (CEdit*)GetDlgItem(IDC_EDIT140);
			pEditControl->GetWindowText(s, 255);
			// save new logfile name

			// TO DO change function
			ChangeLogFileName(module, s);
			break;
        // -------------------------------------------------------
	}

}
// ----------------------------------------------------------------------------
int CMFCHemtALTDlg::UpdateCurrentCfgDisplayfromMemory(int module, int dut)
{
	// update configuration display for current module & Ndut
	// This updates HV, Ialarm, TREF1-TREF4 and Run Comment from
	// the values currently in the struc RACK.

	int error = 0 ;

	if((module< Nmod) && (dut>=0) && (dut<Ndut))
	{
		// Run Comment
		CWnd * pEditControl = (CEdit*)GetDlgItem(IDC_EDIT68);
		CString s = (CString) MBT->Module[module].runComment ;
		pEditControl->SetWindowText(s);

		// HV
		pEditControl = (CEdit*)GetDlgItem(IDC_EDIT65);
		int integer = MBT->Module[module].HV;
		float fval = ((float)integer) / FLOAT2FXD ;
		s.Format("%4.1f", fval);
		pEditControl->SetWindowText(s);

		// Gate
		pEditControl = (CEdit*)GetDlgItem(IDC_EDIT143);
		integer = MBT->Module[module].gate;
		fval = ((float)integer / FLOAT2FXD);
		s.Format("%4.1f", fval);
		pEditControl->SetWindowText(s);
	
		// TREF
		pEditControl = (CEdit*)GetDlgItem(IDC_EDIT63);
		integer = MBT->Module[module].TREF[0] ;
		fval = ((float)integer / FLOAT2FXD);
		s.Format("%4.1f", fval) ;
		pEditControl->SetWindowText(s);

		pEditControl = (CEdit*)GetDlgItem(IDC_EDIT69);
		integer = MBT->Module[module].TREF[1];
		fval = ((float)integer / FLOAT2FXD);
		s.Format("%4.1f", fval);
		pEditControl->SetWindowText(s);

		pEditControl = (CEdit*)GetDlgItem(IDC_EDIT72);
		integer = MBT->Module[module].TREF[2];
		fval = ((float)integer / FLOAT2FXD);
		s.Format("%4.1f", fval);
		pEditControl->SetWindowText(s);

		pEditControl = (CEdit*)GetDlgItem(IDC_EDIT73);
		integer = MBT->Module[module].TREF[3];
		fval = ((float)integer / FLOAT2FXD);
		s.Format("%4.1f", fval);
		pEditControl->SetWindowText(s);
		
		// Ialarm
		pEditControl = (CEdit*)GetDlgItem(IDC_EDIT62);
		integer = MBT->Module[module].Alarm;
		fval = ((float)integer / UA2TEN_NA);
		s.Format("%4.1f", fval);
		pEditControl->SetWindowText(s);

		// Run status display
		switch (MBT->Module[module].op_mode)
		{
		case AUTO_MODE:
			CheckRadioButton(IDC_RADIO5,IDC_RADIO7,IDC_RADIO5) ;
			break;
		case TEST1_MODE:
			CheckRadioButton(IDC_RADIO5,IDC_RADIO7,IDC_RADIO6) ;
			break;
		case TEST2_MODE:
			CheckRadioButton(IDC_RADIO5, IDC_RADIO7, IDC_RADIO7);
			break;
		default:
			CheckRadioButton(IDC_RADIO5, IDC_RADIO7, IDC_RADIO6);
			break;
		}
		
		SetTestMode(MBT->Module[module].op_mode) ;

		// gain setting
		CheckDlgButton(IDC_CHECK27, BST_CHECKED);

		if (IsDlgButtonChecked(IDC_CHECK27) == BST_CHECKED)
		{   // set HI gain
			MBT->Module[module].thr_gain = ADC2ILK_HI_GN;
			MBT->SetThrGain(module, true);
		}
		else
		{   // set Low gain
			MBT->Module[module].thr_gain = ADC2ILK_LOW_GN;
			MBT->SetThrGain(module, false);
		}

	}
	else error = (-1) ;

	return (error) ;
}

// ----------------------------------------------------------------------------
int CMFCHemtALTDlg::UpdateCfgMemoryfromDisplay(int module, int dut)
{
	// Update configuration memory (RACK struc) from GUI display
	// for current module & Ndut. This updates HV, IlkLim, Alarm, Tref1-4 
	// and also logfile name & Run Comment from the display edit boxes.

    int error = 0 ;

	if((module< Nmod) && (dut>0) && (dut<=Ndut))
	{
		CString s ;

		// Run Comment
		CWnd * pEditControl = (CEdit*)GetDlgItem(IDC_EDIT68);
		pEditControl->GetWindowText(s);
		MBT->Module[module].runComment = s.GetBuffer(32) ;
		s.ReleaseBuffer() ;

		// HV
		pEditControl = (CEdit*)GetDlgItem(IDC_EDIT65);
		pEditControl->GetWindowText(s);
		float fval = (float) atof(s);
		int integer = (int)(fval * FLOAT2FXD);
		MBT->Module[module].HV = integer;
		s.ReleaseBuffer();

		// gate
		pEditControl = (CEdit*)GetDlgItem(IDC_EDIT143);
		pEditControl->GetWindowText(s);
		fval = (float) atof(s);
		integer = (int)(fval * FLOAT2FXD);
		MBT->Module[module].gate = integer;
		s.ReleaseBuffer();
	
		// TREF
		pEditControl = (CEdit*)GetDlgItem(IDC_EDIT63);
		pEditControl->GetWindowText(s);
		fval = (float) atof(s);
		integer = (int)(fval * FLOAT2FXD);
        MBT->Module[module].TREF[0] = integer ;	

		pEditControl = (CEdit*)GetDlgItem(IDC_EDIT69);
		pEditControl->GetWindowText(s);
		fval = (float) atof(s);
		integer = (int)(fval * FLOAT2FXD);
		MBT->Module[module].TREF[1] = integer;

		pEditControl = (CEdit*)GetDlgItem(IDC_EDIT72);
		pEditControl->GetWindowText(s);
		fval = (float) atof(s);
		integer = (int)(fval * FLOAT2FXD);
		MBT->Module[module].TREF[2] = integer;

		pEditControl = (CEdit*)GetDlgItem(IDC_EDIT73);
		pEditControl->GetWindowText(s);
		fval = (float) atof(s);
		integer = (int)(fval * FLOAT2FXD);
		MBT->Module[module].TREF[3] = integer;

		// Alarm
		pEditControl = (CEdit*)GetDlgItem(IDC_EDIT62);
		pEditControl->GetWindowText(s);
		fval = (float) atof(s);
		integer = (int)(fval * UA2TEN_NA);
        MBT->Module[module].Alarm = integer;

		UpdateIdSampleValStruct(module);
		UpdateIlkLimValStruct(module);

	}
	else error = (-1) ;

	return (error) ;


}

// ----------------------------------------------------------------------------
void CMFCHemtALTDlg::OnIdclose()
{
	// TODO: Add your command handler code here
	while (1) ;
}
//----------------------------------------------------------------------------------
int CMFCHemtALTDlg::GetIniFileData(rackID m_rack_number)
{
   // Get ini file data   [ ***  FOR ALL RACKS  *** ]
   //------------------------------------------------------------------
   char* pszFileName = new char[50];
   strcpy(pszFileName, "c:\\HemtALT\\HemtALT.ini");
 
   CFile iniFile ;
   CFileException fileException ;
 
   if ( !iniFile.Open( pszFileName, CFile::modeRead, &fileException ) )
   {
       // no ini file so use defaults
	   // post message
	   CString msg = "No " + (CString)pszFileName + " file found\r\nusing defaults." ;
       AfxMessageBox( msg, MB_OK | MB_ICONINFORMATION) ;

	   m_time_increment = TIME_INCR ;

	   for (int i = 0; i < 8; i++)
	   {
		   for (int j = 0; j < Nmod; j++)
		   {
			   m_temp_b0[j][i] = (float)TREF_COEFF0;
			   m_temp_b1[j][i] = (float)TREF_COEFF1;
		   }
	   }

	   switch (m_rack_number)
	   {
	   case ONE:
			// default logfile
			m_logfile_path[0] = "c:\\HemtALT\\R1\\HemtALT1.log" ;
			m_logfile_path[1] = "c:\\HemtALT\\R1\\HemtALT2.log" ;
			m_logfile_path[2] = "c:\\HemtALT\\R1\\HemtALT3.log" ;
			// default cfgfile
			m_cfgfile_path[0] = "c:\\HemtALT\\R1\\HemtALT1.csv" ;
			m_cfgfile_path[1] = "c:\\HemtALT\\R1\\HemtALT2.csv" ;
			m_cfgfile_path[2] = "c:\\HemtALT\\R1\\HemtALT3.csv" ;
	   case TWO:
		   // default logfile
			m_logfile_path[0] = "c:\\HemtALT\\R2\\HemtALT1.log" ;
			m_logfile_path[1] = "c:\\HemtALT\\R2\\HemtALT2.log" ;
			m_logfile_path[2] = "c:\\HemtALT\\R2\\HemtALT3.log" ;
			// default cfgfile
			m_cfgfile_path[0] = "c:\\HemtALT\\R2\\HemtALT1.csv" ;
			m_cfgfile_path[1] = "c:\\HemtALT\\R2\\HemtALT2.csv" ;
			m_cfgfile_path[2] = "c:\\HemtALT\\R2\\HemtALT3.csv" ;
	   case THREE:
		   // default logfile
			m_logfile_path[0] = "c:\\HemtALT\\R3\\HemtALT1.log" ;
			m_logfile_path[1] = "c:\\HemtALT\\R3\\HemtALT2.log" ;
			m_logfile_path[2] = "c:\\HemtALT\\R3\\HemtALT3.log" ;
			// default cfgfile
			m_cfgfile_path[0] = "c:\\HemtALT\\R3\\HemtALT1.csv" ;
			m_cfgfile_path[1] = "c:\\HemtALT\\R3\\HemtALT2.csv" ;
			m_cfgfile_path[2] = "c:\\HemtALT\\R3\\HemtALT3.csv" ;

	       // default stsfile
	       m_stsfile_path = "c:\\HemtALT\\HemtALT.sts" ;       // TO DO *** what's this
	   default:
		   AfxMessageBox("invalid m_rack_number for *.ini file") ;
	   }

   }
   else
   {
	   // using ini file to get defaults for this rack

       UINT  nActual = 0 ;

	   try
	   {
          int len = (int) iniFile.GetLength() ;
		  TCHAR *tcData = new TCHAR[len+1] ;
		  tcData[len]= '\0';

          nActual = iniFile.Read(tcData, len) ; 

		  if(nActual!=0)
		  {    // get NI serial #   /////////////////////////////////////
               CString szBuff(tcData);
			   char * target = new char[40] ;
			   char * target_log = new char[40] ;
			   char * target_cfg = new char[40] ;

			   strcpy(target,"[ni_serial]");

			   szBuff = tcData;
			   int pos = szBuff.Find(target);
			   szBuff.Delete(0,pos) ;

			   switch (m_rack_number)
			   {
			   case ONE:
				   pos = szBuff.Find(_T("s1"));
				   strcpy(target_log, _T("[logfileR1]")) ;
				   strcpy(target_cfg, _T("[cfgfileR1]")) ;
				   break;
			   case TWO:
				   pos = szBuff.Find(_T("s2"));
				   strcpy(target_log, _T("[logfileR2]")) ;
				   strcpy(target_cfg, _T("[cfgfileR2]")) ;
				   break;
			   case THREE:
				   pos = szBuff.Find(_T("s3"));
				   strcpy(target_log, _T("[logfileR3]")) ;
				   strcpy(target_cfg, _T("[cfgfileR3]")) ;
				   break;
			   default:
                   pos = szBuff.Find(_T("s1"));
				   strcpy(target_log, _T("[logfileR1]")) ;
				   strcpy(target_cfg, _T("[cfgfileR1]")) ;
			   }
			   // getting serial #
               szBuff.Delete(0,pos) ;
               pos = szBuff.Find(_T("=")) ;
			   szBuff.Delete(0,pos+1) ;
               pos = szBuff.Find(_T("\n")) ;
			   m_ni_serial_num = szBuff.Left(pos-1) ;
               m_ni_serial_num.TrimLeft(" ") ;
			   
			   // from ni_serial_num get Dev ID & change NI port names
			   // TODO:
			   // 
			   // -----------------------------------------------------



			   // -----------------------------------------------------
			   // get number of modules per rack (assumes all racks built the same)
			   // get # modules  //////////////////////////////////////
			   CString buf ;
			   szBuff = tcData;
			   pos = szBuff.Find(_T("[modules]")) ;
			   szBuff.Delete(0,pos) ;
              
               pos = szBuff.Find(_T("num_mods")) ;
			   szBuff.Delete(0,pos) ;
               pos = szBuff.Find(_T("=")) ;
			   szBuff.Delete(0,pos+1) ;
               pos = szBuff.Find(_T("\n")) ;
			   buf= szBuff.Left(pos-1) ;
               buf.TrimLeft(" ") ;
			   m_numModules = atoi(buf) ;
			   // -----------------------------------------------------
			   // get time increment
               szBuff = tcData ;
			   pos = szBuff.Find(_T("[deltaT]")) ;
			   szBuff.Delete(0,pos) ;

               pos = szBuff.Find(_T("timeincr")) ;
			   szBuff.Delete(0,pos) ;
               pos = szBuff.Find(_T("=")) ;
			   szBuff.Delete(0,pos+1) ;
               pos = szBuff.Find(_T("\n")) ;
			   buf= szBuff.Left(pos-1) ;
               buf.TrimLeft(" ") ;
			   m_time_increment = atoi(buf) ; 

			   // get logfile for selected rack # /////////////////////
			   strcpy(target,target_log) ;

			   szBuff = tcData;
			   pos = szBuff.Find(target);
			   szBuff.Delete(0,pos) ;
              
               pos = szBuff.Find(_T("logfile1"));
			   szBuff.Delete(0,pos) ;
               pos = szBuff.Find(_T("=")) ;
			   szBuff.Delete(0,pos+1) ;
               pos = szBuff.Find(_T("\n")) ;
			   m_logfile_path[0] = szBuff.Left(pos-1) ;
               m_logfile_path[0].TrimLeft(" ") ;

               pos = szBuff.Find(_T("logfile2"));
			   szBuff.Delete(0,pos) ;
               pos = szBuff.Find(_T("=")) ;
			   szBuff.Delete(0,pos+1) ;
               pos = szBuff.Find(_T("\n")) ;
			   m_logfile_path[1] = szBuff.Left(pos-1) ;
               m_logfile_path[1].TrimLeft(" ") ;

               pos = szBuff.Find(_T("logfile3"));
			   szBuff.Delete(0,pos) ;
               pos = szBuff.Find(_T("=")) ;
			   szBuff.Delete(0,pos+1) ;
               pos = szBuff.Find(_T("\n")) ;
			   m_logfile_path[2] = szBuff.Left(pos-1) ;
               m_logfile_path[2].TrimLeft(" ") ;

               // get cfgfile ///////////////////////////////////////
			   strcpy(target, target_cfg) ;

			   szBuff = tcData;
			   pos = szBuff.Find(target);
			   szBuff.Delete(0,pos) ;

               pos = szBuff.Find(_T("cfgfile1"));
			   szBuff.Delete(0,pos) ;
               pos = szBuff.Find(_T("=")) ;
			   szBuff.Delete(0,pos+1) ;
               pos = szBuff.Find(_T("\n")) ;
			   m_cfgfile_path[0] = szBuff.Left(pos-1) ;
               m_cfgfile_path[0].TrimLeft(" ") ;

               pos = szBuff.Find(_T("cfgfile2"));
			   szBuff.Delete(0,pos) ;
               pos = szBuff.Find(_T("=")) ;
			   szBuff.Delete(0,pos+1) ;
               pos = szBuff.Find(_T("\n")) ;
			   m_cfgfile_path[1] = szBuff.Left(pos-1) ;
               m_cfgfile_path[1].TrimLeft(" ") ;

               pos = szBuff.Find(_T("cfgfile3"));
			   szBuff.Delete(0,pos) ;
               pos = szBuff.Find(_T("=")) ;
			   szBuff.Delete(0,pos+1) ;
               pos = szBuff.Find(_T("\n")) ;
			   m_cfgfile_path[2] = szBuff.Left(pos-1) ;
               m_cfgfile_path[2].TrimLeft(" ") ;

			   // -----------------------------------------------

				// House cleaning 
				delete [] target;
				delete [] target_log;
				delete [] target_cfg;
			    delete [] tcData;
		  }
		  else
		  {
			  throw len ;
		  }
	   }
	   catch(...)
	   {
           AfxMessageBox("Error: Reading ini file!") ;
	   }

	   // done

	   iniFile.Close() ;
   }

   delete [] pszFileName;
   return (0);
}

// ---------------------------------------------------------------------------------
int CMFCHemtALTDlg::GetTempCalData(rackID m_rack_number)
{
	// Get Temperature Cal ini file data specified RACK
	//------------------------------------------------------------------
	char* pszFileName = new char[50];

	switch (m_rack_number)
	{
	case ONE:
		strcpy(pszFileName, "c:\\HemtALT\\R1\\HemtCal.ini");
		break;
	case TWO:
		strcpy(pszFileName, "c:\\HemtALT\\R2\\HemtCal.ini");
		break;
	case THREE:
		strcpy(pszFileName, "c:\\HemtALT\\R3\\HemtCal.ini");
		break;
	default:
		strcpy(pszFileName, "c:\\HemtALT\\R1\\HemtCal.ini");
	}

	CFile iniFile;
	CFileException fileException;

	if (!iniFile.Open(pszFileName, CFile::modeRead, &fileException))
	{
		// no ini file so use defaults
		// post message
		CString msg = "No " + (CString)pszFileName + " file found\r\nusing defaults.";
		AfxMessageBox(msg, MB_OK | MB_ICONINFORMATION);

		// set defaults here .....
		for (int j = TC1; j < TCE; j++)
		{
			for (int k = 0; k < Nmod; k++)
			{
				m_temp_b0[k][j] = (TEMP_CAL0);
				m_temp_b1[k][j] = (TEMP_CAL1);
			}
		}

		for (int j = HTR1; j < HTRE; j++)
		{
			for (int i = 1; i < Nmod; i++)
			{
				m_tempref_b0[i][j] = (TREF_CAL0);
				m_tempref_b1[i][j] = (TREF_CAL1);
			}
		}

		m_tc_cntr = TC_CNTR ;
		m_tc_dbnd = TC_DBND ;
		m_tc_toff_min = TC_TOFF;
		m_tc_ton_max = TC_TON;

		for (int i = 0; i < Nmod; i++)
		{
			m_hv_set_b0[i] = (float)HV_COEFF0;  // convert HV float to DAC setting
			m_hv_set_b1[i] = (float)HV_COEFF1;

			m_hv_rd_b0[i] = (float)A0_ADC2HV;	// convert HV ADC to float HV
			m_hv_rd_b1[i] = (float)A1_ADC2HV;

			m_alarm_b0[i] = (float)ILK_COEFF0;	// convert
			m_alarm_b1[i] = (float)ILK_COEFF1;

			m_gate_b0[i] = (float)GT_COEFF0;	// convert float volts to DAC setting
			m_gate_b1[i] = (float)GT_COEFF1;
		}

	}
	else
	{
		// using ini file to get defaults for this rack

		UINT  nActual = 0;

		try
		{
			int len = (int)iniFile.GetLength();
			TCHAR *tcData = new TCHAR[len + 1];
			tcData[len] = '\0';

			nActual = iniFile.Read(tcData, len);

			if (nActual != 0)
			{  
				CString szBuff(tcData);
				CString buf;

				// -----------------------------------------------------
				// get TC calibration values

				szBuff = tcData;
				int pos;

				for (int j = 0; j < Nmod; j++)
				{
					for (int k = 0; k < 8; k++)
					{
						// select case, create string _T("[tc1_cal1]")
						CString s = _T("[tc");
						CString a, b;
						a.Format("%d", j+1);
						b.Format("%d", k+1);
						s = s + a + "_cal" + b + "]";

						//
						int pos = szBuff.Find(s);
						szBuff.Delete(0, pos);
						pos = szBuff.Find(_T("b0"));
						szBuff.Delete(0, pos);
						pos = szBuff.Find(_T("="));
						szBuff.Delete(0, pos + 1);
						pos = szBuff.Find(_T("\n"));
						buf = szBuff.Left(pos - 1);
						buf.TrimLeft(" ");
						m_temp_b0[j][k] = (float)atof(buf);
						//
						szBuff = tcData;
						pos = szBuff.Find(s);
						szBuff.Delete(0, pos);
						pos = szBuff.Find(_T("b1"));
						szBuff.Delete(0, pos);
						pos = szBuff.Find(_T("="));
						szBuff.Delete(0, pos + 1);
						pos = szBuff.Find(_T("\n"));
						buf = szBuff.Left(pos - 1);
						buf.TrimLeft(" ");
						m_temp_b1[j][k] = (float)atof(buf);
						//
					}
				}


				//
				//  TREF calibration
				for (int j = 0; j < Nmod; j++)
				{
					for (int k = 0; k < HTRE; k++)
					{
						// select case, create string _T("[tc1_ref_cal1]")
						CString s = _T("[tc");
						CString a, b;
						a.Format("%d", j + 1);
						b.Format("%d", k + 1);
						s = s + a + "_ref_cal" + b + "]";

						pos = szBuff.Find(s);
						szBuff.Delete(0, pos);
						pos = szBuff.Find(_T("b0"));
						szBuff.Delete(0, pos);
						pos = szBuff.Find(_T("="));
						szBuff.Delete(0, pos + 1);
						pos = szBuff.Find(_T("\n"));
						buf = szBuff.Left(pos - 1);
						buf.TrimLeft(" ");
						m_tempref_b0[j][k] = (float)atof(buf);
						//
						szBuff = tcData;
						pos = szBuff.Find(s);
						szBuff.Delete(0, pos);
						pos = szBuff.Find(_T("b1"));
						szBuff.Delete(0, pos);
						pos = szBuff.Find(_T("="));
						szBuff.Delete(0, pos + 1);
						pos = szBuff.Find(_T("\n"));
						buf = szBuff.Left(pos - 1);
						buf.TrimLeft(" ");
						m_tempref_b1[j][k] = (float)atof(buf);
					}
				}
				//
				// TC servo parameters
				szBuff = tcData;
				pos = szBuff.Find(_T("[tc_count]"));
				szBuff.Delete(0, pos);
				pos = szBuff.Find(_T("tcntr"));
				szBuff.Delete(0, pos);
				pos = szBuff.Find(_T("="));
				szBuff.Delete(0, pos + 1);
				pos = szBuff.Find(_T("\n"));
				buf = szBuff.Left(pos - 1);
				buf.TrimLeft(" ");
				m_tc_cntr = atoi(buf);
				//
				szBuff = tcData;
				pos = szBuff.Find(_T("[tc_dbnd]"));
				szBuff.Delete(0, pos);
				pos = szBuff.Find(_T("tdbnd"));
				szBuff.Delete(0, pos);
				pos = szBuff.Find(_T("="));
				szBuff.Delete(0, pos + 1);
				pos = szBuff.Find(_T("\n"));
				buf = szBuff.Left(pos - 1);
				buf.TrimLeft(" ");
				m_tc_dbnd = atoi(buf);
				//
				szBuff = tcData;
				pos = szBuff.Find(_T("[tc_tmin]"));
				szBuff.Delete(0, pos);
				pos = szBuff.Find(_T("toff_min"));
				szBuff.Delete(0, pos);
				pos = szBuff.Find(_T("="));
				szBuff.Delete(0, pos + 1);
				pos = szBuff.Find(_T("\n"));
				buf = szBuff.Left(pos - 1);
				buf.TrimLeft(" ");
				m_tc_toff_min = atof(buf);
				//
				szBuff = tcData;
				pos = szBuff.Find(_T("[tc_tmax]"));
				szBuff.Delete(0, pos);
				pos = szBuff.Find(_T("ton_max"));
				szBuff.Delete(0, pos);
				pos = szBuff.Find(_T("="));
				szBuff.Delete(0, pos + 1);
				pos = szBuff.Find(_T("\n"));
				buf = szBuff.Left(pos - 1);
				buf.TrimLeft(" ");
				m_tc_ton_max = atoi(buf);
				//
				// HV read set data
				// --------------------------------------------------
				// get HV calibration values

				szBuff = tcData;
				pos = szBuff.Find(_T("[hvset1]"));
				szBuff.Delete(0, pos);
				pos = szBuff.Find(_T("b0"));
				szBuff.Delete(0, pos);
				pos = szBuff.Find(_T("="));
				szBuff.Delete(0, pos + 1);
				pos = szBuff.Find(_T("\n"));
				buf = szBuff.Left(pos - 1);
				buf.TrimLeft(" ");
				m_hv_set_b0[0] = (float)atof(buf);

				szBuff = tcData;
				pos = szBuff.Find(_T("[hvset1]"));
				szBuff.Delete(0, pos);
				pos = szBuff.Find(_T("b1"));
				szBuff.Delete(0, pos);
				pos = szBuff.Find(_T("="));
				szBuff.Delete(0, pos + 1);
				pos = szBuff.Find(_T("\n"));
				buf = szBuff.Left(pos - 1);
				buf.TrimLeft(" ");
				m_hv_set_b1[0] = (float)atof(buf);

				szBuff = tcData;
				pos = szBuff.Find(_T("[hvset2]"));
				szBuff.Delete(0, pos);
				pos = szBuff.Find(_T("b0"));
				szBuff.Delete(0, pos);
				pos = szBuff.Find(_T("="));
				szBuff.Delete(0, pos + 1);
				pos = szBuff.Find(_T("\n"));
				buf = szBuff.Left(pos - 1);
				buf.TrimLeft(" ");
				m_hv_set_b0[1] = (float)atof(buf);

				szBuff = tcData;
				pos = szBuff.Find(_T("[hvset2]"));
				szBuff.Delete(0, pos);
				pos = szBuff.Find(_T("b1"));
				szBuff.Delete(0, pos);
				pos = szBuff.Find(_T("="));
				szBuff.Delete(0, pos + 1);
				pos = szBuff.Find(_T("\n"));
				buf = szBuff.Left(pos - 1);
				buf.TrimLeft(" ");
				m_hv_set_b1[1] = (float)atof(buf);

				szBuff = tcData;
				pos = szBuff.Find(_T("[hvset3]"));
				szBuff.Delete(0, pos);
				pos = szBuff.Find(_T("b0"));
				szBuff.Delete(0, pos);
				pos = szBuff.Find(_T("="));
				szBuff.Delete(0, pos + 1);
				pos = szBuff.Find(_T("\n"));
				buf = szBuff.Left(pos - 1);
				buf.TrimLeft(" ");
				m_hv_set_b0[2] = (float)atof(buf);

				szBuff = tcData;
				pos = szBuff.Find(_T("[hvset3]"));
				szBuff.Delete(0, pos);
				pos = szBuff.Find(_T("b1"));
				szBuff.Delete(0, pos);
				pos = szBuff.Find(_T("="));
				szBuff.Delete(0, pos + 1);
				pos = szBuff.Find(_T("\n"));
				buf = szBuff.Left(pos - 1);
				buf.TrimLeft(" ");
				m_hv_set_b1[2] = (float)atof(buf);

				szBuff = tcData;
				pos = szBuff.Find(_T("[hvrd1]"));
				szBuff.Delete(0, pos);
				pos = szBuff.Find(_T("b1"));
				szBuff.Delete(0, pos);
				pos = szBuff.Find(_T("="));
				szBuff.Delete(0, pos + 1);
				pos = szBuff.Find(_T("\n"));
				buf = szBuff.Left(pos - 1);
				buf.TrimLeft(" ");
				m_hv_rd_b1[0] = (float)atof(buf);
                //
				szBuff = tcData;
				pos = szBuff.Find(_T("[hvrd1]"));
				szBuff.Delete(0, pos);
				pos = szBuff.Find(_T("b0"));
				szBuff.Delete(0, pos);
				pos = szBuff.Find(_T("="));
				szBuff.Delete(0, pos + 1);
				pos = szBuff.Find(_T("\n"));
				buf = szBuff.Left(pos - 1);
				buf.TrimLeft(" ");
				m_hv_rd_b0[0] = (float)atof(buf);	

				szBuff = tcData;
				pos = szBuff.Find(_T("[hvrd2]"));
				szBuff.Delete(0, pos);
				pos = szBuff.Find(_T("b1"));
				szBuff.Delete(0, pos);
				pos = szBuff.Find(_T("="));
				szBuff.Delete(0, pos + 1);
				pos = szBuff.Find(_T("\n"));
				buf = szBuff.Left(pos - 1);
				buf.TrimLeft(" ");
				m_hv_rd_b1[1] = (float)atof(buf);
				//
				szBuff = tcData;
				pos = szBuff.Find(_T("[hvrd2]"));
				szBuff.Delete(0, pos);
				pos = szBuff.Find(_T("b0"));
				szBuff.Delete(0, pos);
				pos = szBuff.Find(_T("="));
				szBuff.Delete(0, pos + 1);
				pos = szBuff.Find(_T("\n"));
				buf = szBuff.Left(pos - 1);
				buf.TrimLeft(" ");
				m_hv_rd_b0[1] = (float)atof(buf);

				szBuff = tcData;
				pos = szBuff.Find(_T("[hvrd3]"));
				szBuff.Delete(0, pos);
				pos = szBuff.Find(_T("b1"));
				szBuff.Delete(0, pos);
				pos = szBuff.Find(_T("="));
				szBuff.Delete(0, pos + 1);
				pos = szBuff.Find(_T("\n"));
				buf = szBuff.Left(pos - 1);
				buf.TrimLeft(" ");
				m_hv_rd_b1[2] = (float)atof(buf);
				//
				szBuff = tcData;
				pos = szBuff.Find(_T("[hvrd3]"));
				szBuff.Delete(0, pos);
				pos = szBuff.Find(_T("b0"));
				szBuff.Delete(0, pos);
				pos = szBuff.Find(_T("="));
				szBuff.Delete(0, pos + 1);
				pos = szBuff.Find(_T("\n"));
				buf = szBuff.Left(pos - 1);
				buf.TrimLeft(" ");
				m_hv_rd_b0[2] = (float)atof(buf);

				// --------------------------------------------------
				// get gate calibration values

				szBuff = tcData;
				pos = szBuff.Find(_T("[gate1]"));
				szBuff.Delete(0, pos);
				pos = szBuff.Find(_T("b0"));
				szBuff.Delete(0, pos);
				pos = szBuff.Find(_T("="));
				szBuff.Delete(0, pos + 1);
				pos = szBuff.Find(_T("\n"));
				buf = szBuff.Left(pos - 1);
				buf.TrimLeft(" ");
				m_gate_b0[0] = (float)atof(buf);
				//
				szBuff = tcData;
				pos = szBuff.Find(_T("[gate1]"));
				szBuff.Delete(0, pos);
				pos = szBuff.Find(_T("b1"));
				szBuff.Delete(0, pos);
				pos = szBuff.Find(_T("="));
				szBuff.Delete(0, pos + 1);
				pos = szBuff.Find(_T("\n"));
				buf = szBuff.Left(pos - 1);
				buf.TrimLeft(" ");
				m_gate_b1[0] = (float)atof(buf);

				szBuff = tcData;
				pos = szBuff.Find(_T("[gate2]"));
				szBuff.Delete(0, pos);
				pos = szBuff.Find(_T("b0"));
				szBuff.Delete(0, pos);
				pos = szBuff.Find(_T("="));
				szBuff.Delete(0, pos + 1);
				pos = szBuff.Find(_T("\n"));
				buf = szBuff.Left(pos - 1);
				buf.TrimLeft(" ");
				m_gate_b0[1] = (float)atof(buf);
				//
				szBuff = tcData;
				pos = szBuff.Find(_T("[gate2]"));
				szBuff.Delete(0, pos);
				pos = szBuff.Find(_T("b1"));
				szBuff.Delete(0, pos);
				pos = szBuff.Find(_T("="));
				szBuff.Delete(0, pos + 1);
				pos = szBuff.Find(_T("\n"));
				buf = szBuff.Left(pos - 1);
				buf.TrimLeft(" ");
				m_gate_b1[1] = (float)atof(buf);

				szBuff = tcData;
				pos = szBuff.Find(_T("[gate3]"));
				szBuff.Delete(0, pos);
				pos = szBuff.Find(_T("b0"));
				szBuff.Delete(0, pos);
				pos = szBuff.Find(_T("="));
				szBuff.Delete(0, pos + 1);
				pos = szBuff.Find(_T("\n"));
				buf = szBuff.Left(pos - 1);
				buf.TrimLeft(" ");
				m_gate_b0[2] = (float)atof(buf);
				//
				szBuff = tcData;
				pos = szBuff.Find(_T("[gate3]"));
				szBuff.Delete(0, pos);
				pos = szBuff.Find(_T("b1"));
				szBuff.Delete(0, pos);
				pos = szBuff.Find(_T("="));
				szBuff.Delete(0, pos + 1);
				pos = szBuff.Find(_T("\n"));
				buf = szBuff.Left(pos - 1);
				buf.TrimLeft(" ");
				m_gate_b1[2] = (float)atof(buf);

				// ----------------------------------------------
				// get alarm calibration
				szBuff = tcData;
				pos = szBuff.Find(_T("[alarm_cal1]"));
				szBuff.Delete(0, pos);
				pos = szBuff.Find(_T("b1"));
				szBuff.Delete(0, pos);
				pos = szBuff.Find(_T("="));
				szBuff.Delete(0, pos + 1);
				pos = szBuff.Find(_T("\n"));
				buf = szBuff.Left(pos - 1);
				buf.TrimLeft(" ");
				m_alarm_b1[0] = (float)atof(buf);
				//
				szBuff = tcData;
				pos = szBuff.Find(_T("[alarm_cal1]"));
				szBuff.Delete(0, pos);
				pos = szBuff.Find(_T("b0"));
				szBuff.Delete(0, pos);
				pos = szBuff.Find(_T("="));
				szBuff.Delete(0, pos + 1);
				pos = szBuff.Find(_T("\n"));
				buf = szBuff.Left(pos - 1);
				buf.TrimLeft(" ");
				m_alarm_b0[0] = (float)atof(buf);

				szBuff = tcData;
				pos = szBuff.Find(_T("[alarm_cal2]"));
				szBuff.Delete(0, pos);
				pos = szBuff.Find(_T("b1"));
				szBuff.Delete(0, pos);
				pos = szBuff.Find(_T("="));
				szBuff.Delete(0, pos + 1);
				pos = szBuff.Find(_T("\n"));
				buf = szBuff.Left(pos - 1);
				buf.TrimLeft(" ");
				m_alarm_b1[1] = (float)atof(buf);
				//
				szBuff = tcData;
				pos = szBuff.Find(_T("[alarm_cal2]"));
				szBuff.Delete(0, pos);
				pos = szBuff.Find(_T("b0"));
				szBuff.Delete(0, pos);
				pos = szBuff.Find(_T("="));
				szBuff.Delete(0, pos + 1);
				pos = szBuff.Find(_T("\n"));
				buf = szBuff.Left(pos - 1);
				buf.TrimLeft(" ");
				m_alarm_b0[1] = (float)atof(buf);

				szBuff = tcData;
				pos = szBuff.Find(_T("[alarm_cal3]"));
				szBuff.Delete(0, pos);
				pos = szBuff.Find(_T("b1"));
				szBuff.Delete(0, pos);
				pos = szBuff.Find(_T("="));
				szBuff.Delete(0, pos + 1);
				pos = szBuff.Find(_T("\n"));
				buf = szBuff.Left(pos - 1);
				buf.TrimLeft(" ");
				m_alarm_b1[2] = (float)atof(buf);
				//
				szBuff = tcData;
				pos = szBuff.Find(_T("[alarm_cal3]"));
				szBuff.Delete(0, pos);
				pos = szBuff.Find(_T("b0"));
				szBuff.Delete(0, pos);
				pos = szBuff.Find(_T("="));
				szBuff.Delete(0, pos + 1);
				pos = szBuff.Find(_T("\n"));
				buf = szBuff.Left(pos - 1);
				buf.TrimLeft(" ");
				m_alarm_b0[2] = (float)atof(buf);

			}
			else
			{
				throw len;
			}
		}
		catch (...)
		{
			AfxMessageBox("Error: Reading HemtCal.ini file!");
		}

		// done

		iniFile.Close();
	}

	delete[] pszFileName;
	return (0);
}

//-----------------------------------------------------------------------------
int CMFCHemtALTDlg::LoadConfigFile(int module)    // *.cvs //
{ 
	int retVal = 0 ;

	CFileException fileException ;
				
	// m_cfgfile_path[] initialized by default or in ini file
	// previous to this call.
    // File is a comma delimited (*.csv) file format created in Notepad or Excel
    // this approach was taken for ease of the user to manually create a config file.

	// close if already opened
	if( m_cfgfile_handle[module] != (CFile *) ~NULL ) m_cfgfile_handle[module].Close() ;

	
     if(!m_cfgfile_handle[module].Open( m_cfgfile_path[module], CFile::modeRead, &fileException ) )
	 {
         AfxMessageBox("Failed to open config file "+m_cfgfile_path[module]) ;
		 retVal = -1;
	 }
	 else
	 {
		 UINT  nActual = 0 ;
		 retVal = 0 ;

		 try
		 {
            int len = (int) m_cfgfile_handle[module].GetLength() ;
		    TCHAR *tcData = new TCHAR[len+1] ;
		    tcData[len]= '\0';

            nActual = m_cfgfile_handle[module].Read(tcData, len) ; 

			if(nActual!=0)
		    {  // get cfgfile   /////////////////////////////////////

			   ParseCvsCfgBuffer( tcData, module ) ;
			   // TODO: error handling
			}
			else
			{
                throw len ;
			}

			delete[] tcData;
        }  
        catch(...)
        {
			AfxMessageBox("Error: Reading cfg file! "+m_cfgfile_path[module]) ;
			retVal = -1 ;
		}

        // done - close file
	    if( m_cfgfile_handle[module] != (CFile *) ~NULL ) m_cfgfile_handle[module].Close() ;

	 }

     return (retVal) ;
}

//------------------------------------------------------------------------------
int CMFCHemtALTDlg::ParseCvsCfgBuffer( TCHAR * tcData, int module)
{
	// TODO: parse the tcData (cfg file) into the Rack struc parameters
	// comment,,,,
	// 0,VOLTS
	// 1,ILEAK     (in uAmps)
	// 2,TREF1     (in deg C)
	// 3,TREF2
	// 4,TREF3
	// 5,TREF4
	//END

	// tcData is preserved and szBuff is modified during operation

	CString szBuff(tcData) ;
	CString tmpBuff(tcData) ;
	CString lnBuff(tcData) ;
	szBuff = tcData ;
	tmpBuff= tcData ;
	lnBuff= tcData ;

	int len = szBuff.GetLength() ;
	int pos ;

	// ------------------------------------------------------------------
	// Get run comment 
	CString buf;
	szBuff = tcData;
	pos = szBuff.Find(_T("[run_desc]"));
	szBuff.Delete(0, pos);
	pos = szBuff.Find(_T("run_desc"));
	szBuff.Delete(0, pos);
	pos = szBuff.Find(_T("="));
	szBuff.Delete(0, pos + 1);
	pos = szBuff.Find(_T("\n"));
	buf = szBuff.Left(pos - 1);
	buf.TrimLeft(" ");
	MBT->Module[module].runComment = buf.GetBuffer(1);
	buf.ReleaseBuffer();

	// ------------------------------------------------------------------
	// Get high voltage setting (file units in (float) volts)

	szBuff = tcData;
	pos = szBuff.Find(_T("[hv_set]"));
	szBuff.Delete(0, pos);
	pos = szBuff.Find(_T("hv"));
	szBuff.Delete(0, pos);
	pos = szBuff.Find(_T("="));
	szBuff.Delete(0, pos + 1);
	pos = szBuff.Find(_T("\n"));
	buf = szBuff.Left(pos - 1);
	buf.TrimLeft(" ");
	float val = (float) atof(buf.GetBuffer(1)) * FLOAT2FXD;
	MBT->Module[module].HV = (int) val;
	buf.ReleaseBuffer();

	// ------------------------------------------------------------------
	// Get gate voltage setting (file units in (float) volts)

	szBuff = tcData;
	pos = szBuff.Find(_T("[gt_set]"));
	szBuff.Delete(0, pos);
	pos = szBuff.Find(_T("gt"));
	szBuff.Delete(0, pos);
	pos = szBuff.Find(_T("="));
	szBuff.Delete(0, pos + 1);
	pos = szBuff.Find(_T("\n"));
	buf = szBuff.Left(pos - 1);
	buf.TrimLeft(" ");
	val = (float) atof(buf.GetBuffer(1)) * FLOAT2FXD;
	MBT->Module[module].gate = (int) val;
	buf.ReleaseBuffer();

	// ------------------------------------------------------------------
	// Get Alarm current setting (file units in (float) uA)

	szBuff = tcData;
	pos = szBuff.Find(_T("[alarm]"));
	szBuff.Delete(0, pos);
	pos = szBuff.Find(_T("thresh"));
	szBuff.Delete(0, pos);
	pos = szBuff.Find(_T("="));
	szBuff.Delete(0, pos + 1);
	pos = szBuff.Find(_T("\n"));
	buf = szBuff.Left(pos - 1);
	buf.TrimLeft(" ");
	val = (float) atof(buf.GetBuffer(1)) * FLOAT2FXD;
	MBT->Module[module].Alarm = (int)val;
	buf.ReleaseBuffer();

	// -----------------------------------------------------------------
	// Get Tref (file units in (float) deg C)

	szBuff = tcData;
	pos = szBuff.Find(_T("[tref]"));
	szBuff.Delete(0, pos);
	pos = szBuff.Find(_T("tref1"));
	szBuff.Delete(0, pos);
	pos = szBuff.Find(_T("="));
	szBuff.Delete(0, pos + 1);
	pos = szBuff.Find(_T("\n"));
	buf = szBuff.Left(pos - 1);
	buf.TrimLeft(" ");
	val = (float) atof(buf.GetBuffer(1)) * FLOAT2FXD;
	MBT->Module[module].TREF[0] = (int) val;
	buf.ReleaseBuffer();

	// -----------------------------------------------
	szBuff = tcData;
	pos = szBuff.Find(_T("[tref]"));
	szBuff.Delete(0, pos);
	pos = szBuff.Find(_T("tref2"));
	szBuff.Delete(0, pos);
	pos = szBuff.Find(_T("="));
	szBuff.Delete(0, pos + 1);
	pos = szBuff.Find(_T("\n"));
	buf = szBuff.Left(pos - 1);
	buf.TrimLeft(" ");
	val = (float) atof(buf.GetBuffer(1)) * FLOAT2FXD;
	MBT->Module[module].TREF[1] = (int) val;  
	buf.ReleaseBuffer();

	// ------------------------------------------------
	szBuff = tcData;
	pos = szBuff.Find(_T("[tref]"));
	szBuff.Delete(0, pos);
	pos = szBuff.Find(_T("tref3"));
	szBuff.Delete(0, pos);
	pos = szBuff.Find(_T("="));
	szBuff.Delete(0, pos + 1);
	pos = szBuff.Find(_T("\n"));
	buf = szBuff.Left(pos - 1);
	buf.TrimLeft(" ");
	val = (float) atof(buf.GetBuffer(1)) * FLOAT2FXD;
	MBT->Module[module].TREF[2] = (int) val;
	buf.ReleaseBuffer();

	// ------------------------------------------------
	szBuff = tcData;
	pos = szBuff.Find(_T("[tref]"));
	szBuff.Delete(0, pos);
	pos = szBuff.Find(_T("tref4"));
	szBuff.Delete(0, pos);
	pos = szBuff.Find(_T("="));
	szBuff.Delete(0, pos + 1);
	pos = szBuff.Find(_T("\n"));
	buf = szBuff.Left(pos - 1);
	buf.TrimLeft(" ");
	val = (float) atof(buf.GetBuffer(1)) * FLOAT2FXD;
	MBT->Module[module].TREF[3] = (int) val;
	buf.ReleaseBuffer();

	// ------------------------------------------------------------------
	// Get hardware alarm (file units in (float) uA)

	szBuff = tcData;
	pos = szBuff.Find(_T("[alarm]"));
	szBuff.Delete(0, pos);
	pos = szBuff.Find(_T("thresh"));
	szBuff.Delete(0, pos);
	pos = szBuff.Find(_T("="));
	szBuff.Delete(0, pos + 1);
	pos = szBuff.Find(_T("\n"));
	buf = szBuff.Left(pos - 1);
	buf.TrimLeft(" ");
	val = (float) atof(buf.GetBuffer(1));    // value is 10's of nA
	MBT->Module[module].Alarm = (int) val; 
	buf.ReleaseBuffer();


	// -------------------------------------------------------------------
	// prepare to get channels
	szBuff = tcData ;
	pos = szBuff.Find("[dut]") ;
	szBuff.Delete(0,pos+7) ;         // strip off up to 1st channel ID
	tmpBuff = szBuff.GetBuffer(1) ;  // save 20 channels
	szBuff.ReleaseBuffer() ;
	// Get channels
	int len1 ;
	CString seq ;
	for (int i=0; i < Ndut; i++)
	{
		pos = szBuff.Find("\n");
		lnBuff = szBuff.Left(pos - 1);
		lnBuff.TrimLeft(" ");
		lnBuff.Append(",");
		szBuff.Delete(0, pos + 1);     // ready for next iteration, donn't alter
		// save values in lnBuff
		len1 = lnBuff.GetLength();
		tmpBuff = lnBuff.Left(len1);
		// sequence #
		pos = tmpBuff.Find(",");
		seq = tmpBuff.Left(pos);
		tmpBuff.Delete(0, pos + 1);    // chop off sequence # & ","
		seq.TrimLeft(" ");
		if ((i+1) != atoi(seq.GetBuffer(1)))
		{
			AfxMessageBox("Cfg file sequence error! " + seq);
			return(-1);
		}
		// IlkLim
		pos = tmpBuff.Find(",");
		seq = tmpBuff.Left(pos);
		tmpBuff.Delete(0, pos + 1);      // chop off ID & "'"
		seq.TrimLeft(" ");
		val = (float) atof(seq.GetBuffer(1)); 
		MBT->Module[module].IlkLim[i] = (int) val;  // value is 10's of nA
		// enable
		pos = tmpBuff.Find(",");
		seq = tmpBuff.Left(pos);
		tmpBuff.Delete(0, pos + 1);      // chop off IlkLim & "'"
		seq.TrimLeft(" ");
		int flag = (bool)(atoi(seq.GetBuffer(1)) != 0);
		if (flag)
		{
			MBT->Module[module].Enable[i] = TRUE;
		}
		else {
			MBT->Module[module].Enable[i] = FALSE;
		}
		// sample_ID
		pos = tmpBuff.Find(",") ;
		seq = tmpBuff.Left(pos) ;
		tmpBuff.Delete(0,pos+1) ;      // chop off enable & "'"
		seq.TrimLeft(" ") ;
		MBT->Module[module].SampleID[i] = seq.GetBuffer(1) ;  
		// resume time (file units in (float) hrs)
		pos = tmpBuff.Find(",");
		seq = tmpBuff.Left(pos);
		tmpBuff.Delete(0, pos + 1);   // chop off ID & "'"
		seq.TrimLeft(" ");
		val = ((float) atof(seq.GetBuffer(1)) * (3600000.0));  // time in msec)
		MBT->Module[module].resTime[i] = (ULONGLONG) val;
		seq.ReleaseBuffer();
		// ---
	}

	// free memory ?!!

	return (0) ;

	// end ParseCvsCfgBuffer
}

// ----------------------------------------------------------------------------
int CMFCHemtALTDlg::SaveConfigFile(int module)
{ 
	// Save config memory into a file for the selected module
	// offer a file menu then save to disc
	int retVal = 0 ;

	// generate data buffer from Rack struc to write to file
	TCHAR *tcData ;
	int len = 0 ;   // build up from 0

	tcData = new TCHAR[len+1] ;
	tcData[len]= '\0';
	CString fileBuf(tcData) ;

	fileBuf= tcData ;

	CString c;

	fileBuf.Append("[run_desc]\r\n");
	fileBuf.Append("run_desc=");
	fileBuf.Append(MBT->Module[module].runComment) ;	// run comment
	fileBuf.Append("\r\n") ;
	//
	fileBuf.Append("[hv_set]\r\n");
	fileBuf.Append("hv=");
	float fval = ((float) MBT->Module[module].HV) / FLOAT2FXD;
	c.Format("%4.1f", fval);
	fileBuf.Append(c);									// HV
	fileBuf.Append("\r\n");
	//
	fileBuf.Append("[gt_set]\r\n");
	fileBuf.Append("gt=");
	fval = ((float) MBT->Module[module].gate) / FLOAT2FXD;
	c.Format("%4.1f", fval);
	fileBuf.Append(c);									// gate
	fileBuf.Append("\r\n");
	//
	fileBuf.Append("[tref]\r\n");
	fileBuf.Append("tref1=");
	fval = ((float) MBT->Module[module].TREF[0]) / FLOAT2FXD ;
	c.Format("%4.1f", fval);
	fileBuf.Append(c);									// Tref1
	fileBuf.Append("\r\n");
	//
	fileBuf.Append("tref2=");
	fval = ((float) MBT->Module[module].TREF[1]) / FLOAT2FXD ;
	c.Format("%4.1f", fval);
	fileBuf.Append(c);									// Tref2
	fileBuf.Append("\r\n");
	//
	fileBuf.Append("tref3=");
	fval = ((float) MBT->Module[module].TREF[2]) / FLOAT2FXD;
	c.Format("%4.1f", fval);
	fileBuf.Append(c);									// Tref3
	fileBuf.Append("\r\n");
	//
	fileBuf.Append("tref4=");
	fval = ((float) MBT->Module[module].TREF[3]) / FLOAT2FXD;
	c.Format("%4.1f", fval);
	fileBuf.Append(c);									// Tref4
	fileBuf.Append("\r\n");
	//
	fileBuf.Append("[alarm]\r\n");
	fileBuf.Append("thresh=");
	fval = ((float) MBT->Module[module].Alarm) ;
	c.Format("%4.1f", fval);
	fileBuf.Append(c);									// Alarm (10's of nA)
	fileBuf.Append("\r\n");
	//
	fileBuf.Append("[dut]\r\n");
	int n;
	for (int i=0; i< Ndut; i++)
	{
		c.Format("%d", (i+1));							  // sequence #
		fileBuf.Append(c) ;
		fileBuf.Append(",") ;
		// ----
		fval = (float) MBT->Module[module].IlkLim[i];     // ILEAK (10's of nA)
		c.Format("%4.1f",fval) ;
		fileBuf.Append(c) ; 
        fileBuf.Append(",") ;
		// ----
		n = MBT->Module[module].Enable[i];				  // Enable
		c.Format("%d", n);
		fileBuf.Append(c);
		fileBuf.Append(",");
		//
		fileBuf.Append(MBT->Module[module].SampleID[i]); // Sample ID
		fileBuf.Append(",");
		// ----
		ULONGLONG tme = MBT->Module[module].resTime[i];
		float fval = tme / 3600000;
		c.Format("%4.2f", fval);
		fileBuf.Append(c);								 // resume time (hrs)
		fileBuf.Append("\r\n");
	}

	fileBuf.Append("END") ;
	fileBuf.Append("\0") ;

	CFileException fileException ;

	// close if already opened
	if( m_cfgfile_handle[module] != (CFile *) ~NULL ) m_cfgfile_handle[module].Close() ;

    if(!m_cfgfile_handle[module].Open( m_cfgfile_path[module], CFile::modeCreate |  CFile::modeWrite, &fileException ) )
	{
         AfxMessageBox("Failed to open config file "+m_cfgfile_path[module]) ;
		 retVal = -1;
	}
	else
	// write buffer to file                              
	if (m_cfgfile_handle[module] != (CFile*) ~NULL)
	{
	    m_cfgfile_handle[module].Write(fileBuf, fileBuf.GetLength()) ;
	}
	else {
	retVal = -1 ;

		AfxMessageBox("config file "+m_cfgfile_path[module]+" is NULL!") ;
	}

	// close file before exiting 
	if( m_cfgfile_handle[module] != (CFile *) ~NULL ) m_cfgfile_handle[module].Close() ;

	delete [] tcData ;
	return (retVal) ;
}

// ----------------------------------------------------------------------------
int CMFCHemtALTDlg::OpenLogFile(int module)
{
	int retVal = 0;

	// open (for read/write) a log file for module.
	// make unique by appending system time to text name 

	// if file handle open, then close it
	// get unique name
	// check if name unique & if not increment
	// create file

	CFileException fileException;

	// close if already opened
	if (m_logfile_handle[module] != (CFile *)~NULL) m_logfile_handle[module].Close();

	// get unique name
	CString UnqTime;

	GetUniqueTime(UnqTime);
	// get file name only and append the unique name
	CString temp = m_logfile_path[module];
	CString ext;
	CString path;
	int pos = temp.Find(".");
	int n = temp.GetLength();
	//
	if (pos < 0) {
		ext = ".log";
		path= temp;
	}
	else
	{
		ext = temp.Right(n - pos);
		path = temp.Left(pos);
	}
	
	path.Append(UnqTime) ;
	path.Append(ext) ;
	m_logfile_name[module] = path ;

	// create unique file
	if(!m_logfile_handle[module].Open( m_logfile_name[module],  CFile::modeCreate + CFile::modeReadWrite, &fileException ) )
	 {
         AfxMessageBox("Failed to open log file "+m_logfile_name[module]) ;
		 retVal = -1;
	 }
	 else
	 {
		 retVal = 0 ;
	 }

	return (retVal) ;

}

// ----------------------------------------------------------------------------
int CMFCHemtALTDlg::ReOpenLogFile( int module)
{
	int retVal = 0 ;

	// open (for read/write) an existing log file for module.
	// move to end

	CFileException fileException ;

	// open file
	if(!m_logfile_handle[module].Open( m_logfile_name[module],  CFile::modeReadWrite, &fileException ) )
	 {
         AfxMessageBox("Failed to open log file "+m_logfile_name[module]) ;
		 retVal = -1;
	 }
	 else
	 {
		// seek to end to append
		m_logfile_handle[module].SeekToEnd() ;
		retVal = 0 ;
	 }

	
	return (retVal) ;
}
// ----------------------------------------------------------------------------
int CMFCHemtALTDlg::CloseLogFile( int module)
{
	// Close log file
	int retVal = 0 ;

	CFileException fileException ;

	// close if already opened
	if( m_logfile_handle[module] != (CFile *) ~NULL ) m_logfile_handle[module].Close() ;

	return (retVal) ;
}

// -----------------------------------------------------------------------------
void CMFCHemtALTDlg::OnStnClickedBitmap1()
{
	AfxMessageBox("Need to add help menu here...");
}
// ----------------------------------------------------------------------------
void CMFCHemtALTDlg::GetUniqueTime( CString& UnqTime )
{
	SYSTEMTIME st ;

	GetSystemTime(&st) ;

	UnqTime.Format( _T("-%02d-%02d-%04d-%02d%02d"),
		st.wMonth, st.wDay, st.wYear, st.wHour, st.wMinute); 

}

// ----------------------------------------------------------------------------
void CMFCHemtALTDlg::GetSysTime(CString& systime)
{
	// formated for use in log-file spreadsheet
	// date is MO/DAY/YEAR-HR-MIN which can be
	// coverted in Excel to a manipulatable number.

	SYSTEMTIME st ;

	GetSystemTime(&st) ;

	systime.Format( _T("%02d/%02d/%04d-%02d:%02d"),
		    st.wMonth, st.wDay, st.wYear, st.wHour, st.wMinute ) ;

}

// ----------------------------------------------------------------------------
int CMFCHemtALTDlg::AcquireLogData(int module, bool flag)
{
	// Read data for module w/ leakage current data, elapsed time & time stamp
	// Update data struc for later display & logfile
	// 
	// if flag is true, also update start time
	//
	// sensor readings are a (float) value

	int v_hv;
	int num_avg = NUM_AVG_ADC;
	int retVal = 0;
	CString timestamp;

	// ---------------------------------------------------------------------
	GetSysTime(timestamp);
	if (flag)
	{   // save start time
		SYSTEMTIME start;
		GetSystemTime(&start);
		MBT->Module[module].st = start;
		MBT->Module[module].tick_start = GetTickCount64();
	}

	// Select module then read ALL channels
	// ---------------------------------------------------------------------
	MBT->SetModSel(module);

	// ---------------------------------------------------------------------
	// sample Ndut sensor adc (leakage current)

	float gain = MBT->Module[module].thr_gain;
	for (int j = 0; j < Ndut; j++)
	{
		int val = 0;
		if (MBT->ReadILEAK(module, j, &val))
		{
			AfxMessageBox("Error reading Ndut chan");
			return (-1);
		}
		
		MBT->Module[module].lastVal[j] = val * gain;  // 10's of nA
	}

	// ---------------------------------------------------------------------
	// sample Temperature adc readings
	
	aquireTempValues(module);

	// =====================================================================
	// sample & average v_hv
	v_hv = 0;
	for (int i = 0; i < num_avg; i++)
	{
		int val;
		if(MBT->ReadAnlg(module, HV_ANLG, &val))
		{
			AfxMessageBox("Error reading V_HV_CHAN");
			return (-1);
		}
		v_hv += val;
	}

	float volts = (((float)v_hv)*m_hv_rd_b1[module] + m_hv_rd_b0[module]) / num_avg;
	MBT->Module[module].HVref = int(volts * FLOAT2FXD);  // 10ths of a volt
	// ======================================================================

	// De-select module
	MBT->SetModSel(NULL_MODULE);

	return (retVal);
}

// -------------------------------------------------------------------------
int CMFCHemtALTDlg::WriteLogFile(int module, bool flag)
{

	// compose lines for file
	// Comment
	// systime, et, val1, val2, ..., val20, T1, T2, T3, T4, T5, T6, T7, Tamb, tt1, tt2, ..., tt20, hv

	int retVal = 0;
	float EThr;
	ULONGLONG ETmsec;
	CString timestamp;
	CString line ;

	GetSysTime(timestamp);
    if(flag)
	{
		line = MBT->Module[module].runComment ;
		line.Append("\r\n") ;
		line.Append("Sys-Time,ET(hrs),");
		line.Append("CH1,CH2,CH3,CH4,CH5,CH6,CH7,CH8,CH9,CH10,CH11,CH12,CH13,CH14,CH15,CH16,CH17,CH18,CH19,CH20,");
		line.Append("T1,T2,T3,T4,T5,T6,T7,Tamb,");
		line.Append("TT1,TT2,TT3,TT4,TT5,TT6,TT7,TT8,TT9,TT10,TT11,TT12,TT3,TT14,TT15,TT16,TT17,TT18,TT19,TT20,");
		line.Append("HV\r\n");

		line.Append(timestamp) ;
	}
	else
	{
		line = timestamp ;
	}

	CString data ;

	ETmsec = MBT->Module[module].ET ;  // save data in file as hours (float)
	EThr = ((float)ETmsec)/((float)3.6E6) ;
	data.Format(",%8.3f", EThr ) ;
	line.Append(data) ;

	for(int i=0; i<Ndut; i++)
	{
		float current = ((float) MBT->Module[module].lastVal[i]) / UA2TEN_NA;    // uA
		data.Format(",%.3e", current) ;
		line.Append(data) ;
	}

	// temperature values
	for (int i = TC1; i<TCE; i++)
	{
		float temp = ((float) MBT->Module[module].TMEA[i]) / FLOAT2FXD;   // degC;
		data.Format(",%5.1f", temp);
		line.Append(data);
	}

	// total run-time, hrs.
	for (int i = 0; i < Ndut; i++)
	{
		ULONGLONG RTmsec = MBT->Module[module].totTime[i];		// save data in file as hours (float)
		float TThr = ((float)RTmsec) / ((float) 3.6E6);
		data.Format(",%8.3f", TThr);
		line.Append(data);
	}

    // measured high voltage 
	float volt = ((float)MBT->Module[module].HVref) / FLOAT2FXD;
	data.Format(",%.1f", volt);
	line.Append(data) ;

	data.Format("\r\n") ;
	line.Append(data) ;

	// ** TO DO ** Modify file handling so during duration of test a user
	//    can copy the file without stopping the test. Objectives are
	//    1) to be able to examine file during test and 2) to not lose file
	//    if a power failure occurs.

    // ================================================================


	// write line to file
	if (m_logfile_handle[module] != (CFile*) NULL)
	{
		// open & write line
		ReOpenLogFile(module);
	    m_logfile_handle[module].Write(line, line.GetLength()) ;
		// close file
		CloseLogFile(module);
	}
	else {
	retVal = -1 ;

		AfxMessageBox("log file "+m_logfile_name[module]+" is NULL!") ;
	}

	// ================================================================

	Beep(750,100) ;   // ####

	return (retVal) ;
}

// --------------------------------------------------------------------------
int CMFCHemtALTDlg::aquireTempValues(int module)
{
	// sample Temperature adc readings


#undef TIME
#ifdef TIME
	 SYSTEMTIME start, end;
	 GetSystemTime(&start);
#endif

	for (int j = TC1; j < TCE; j++)
	{
		int val;
		if (MBT->ReadTemp(module, (enum TC_ID) j, &val))
		{
			AfxMessageBox("Error reading Temp chan");
			return (-1);
		}

		MBT->Module[module].TMEA[j] = val;  // 10ths of a deg C
	}
#ifdef TIME
	GetSystemTime(&end);  // 10/11/15 11.48s to read 8, ~1.4s ea
#endif

	return (0);
}

// ----------------------------------------------------------------------------
CString CMFCHemtALTDlg:: GetDeviceName(void)
{
	// return NI device name
	CString result = MBT->niDAQwrap->m_device;

	return (result) ;
}

// ----------------------------------------------------------------------------
void CMFCHemtALTDlg::OnBnClickedOpenFile(int module)
{
	// TODO: Add your control notification handler code here
	// Use existing log file on disk.
	// szFilters is a text string that includes two file name filters: 
   // "*.ini" for "ini Files" and "*.*' for "All Files."
   TCHAR szFilters[]= _T(".log Files (*.log)|*.log|All Files (*.*)|*.*||");

   // Create an Open dialog; the default file name extension is ".log".
   CFileDialog fileDlg(TRUE, _T("log"), _T("*.log"),
      OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, szFilters);

   // Display the file dialog. When user clicks OK, fileDlg.DoModal()  
   // returns IDOK. 
   if(fileDlg.DoModal() == IDOK)
   {
      CString pathName = fileDlg.GetPathName();
	  m_logfile_name[module] = pathName ;
   }

}

// ----------------------------------------------------------------------------
int CMFCHemtALTDlg::XferConfigToFpga( int module ) 
{
	// transfer configuration from memory to FPGA
	int error = MBT->LoadConfigToFpga( module ) ;
	return (error) ;
}

// ----------------------------------------------------------------------------
void CMFCHemtALTDlg::OnEnChangeEdit133()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	// SampleID[7]
	GrabSampleID(7);
}

// ----------------------------------------------------------------------------
void CMFCHemtALTDlg::OnEnChangeEdit122()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}

// ----------------------------------------------------------------------------
void CMFCHemtALTDlg::OnEnChangeEdit109()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	// SampleID[19]
	GrabSampleID(19);
}

// ----------------------------------------------------------------------------
void CMFCHemtALTDlg::OnEnChangeEdit40()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	// IlkLim[0]
}

// ---------------------------------------------------------------------------
void CMFCHemtALTDlg::OnEnChangeEdit10()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	// IlkLim[1]
}

// ---------------------------------------------------------------------------
void CMFCHemtALTDlg::OnEnChangeEdit39()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	// IlkLim[1]
}

// ---------------------------------------------------------------------------
void CMFCHemtALTDlg::OnEnChangeEdit9()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	// // IlkLim[3]
}

// ---------------------------------------------------------------------------
void CMFCHemtALTDlg::OnEnChangeEdit38()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	// // IlkLim[4]
}

// ---------------------------------------------------------------------------
void CMFCHemtALTDlg::OnEnChangeEdit8()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	// IlkLim[5]
}

// ----------------------------------------------------------------------------
void CMFCHemtALTDlg::OnEnChangeEdit37()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	// IlkLim[6]
}

// ----------------------------------------------------------------------------
void CMFCHemtALTDlg::OnEnChangeEdit7()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	// IlkLim[7]
}

// ----------------------------------------------------------------------------
void CMFCHemtALTDlg::OnEnChangeEdit36()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	// IlkLim[8]
}

// ----------------------------------------------------------------------------
void CMFCHemtALTDlg::OnEnChangeEdit6()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	// IlkLim[9]
}

// ----------------------------------------------------------------------------
void CMFCHemtALTDlg::OnEnChangeEdit35()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	// IlkLim[10]
}

// -----------------------------------------------------------------------------
void CMFCHemtALTDlg::OnEnChangeEdit5()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	// IlkLim[11]
}

// -----------------------------------------------------------------------------
void CMFCHemtALTDlg::OnEnChangeEdit34()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	// IlkLim[12]
}

// -----------------------------------------------------------------------------
void CMFCHemtALTDlg::OnEnChangeEdit4()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	// IlkLim[13]
}

// ------------------------------------------------------------------------------
void CMFCHemtALTDlg::OnEnChangeEdit33()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	// IlkLim[14]
}

// ------------------------------------------------------------------------------
void CMFCHemtALTDlg::OnEnChangeEdit3()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	// IlkLim[15]
}

// ------------------------------------------------------------------------------
void CMFCHemtALTDlg::OnEnChangeEdit32()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	// IlkLim[16]
}

// ------------------------------------------------------------------------------
void CMFCHemtALTDlg::OnEnChangeEdit2()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	// IlkLim[17]
}

// -------------------------------------------------------------------------------
void CMFCHemtALTDlg::OnEnChangeEdit11()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	// IlkLim[18]
}

// -------------------------------------------------------------------------------
void CMFCHemtALTDlg::OnEnChangeEdit1()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	// IlkLim[19]
}

// ------------------------------------------------------------------------------
void CMFCHemtALTDlg::OnEnChangeEdit112()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	// SampleID[0]
	GrabSampleID(0);

}

// ------------------------------------------------------------------------------
void CMFCHemtALTDlg::OnEnChangeEdit115()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	// SampleID[1]
	GrabSampleID(1);
}

// ------------------------------------------------------------------------------
void CMFCHemtALTDlg::OnEnChangeEdit118()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	// SampleID[2]
}

// ------------------------------------------------------------------------------
void CMFCHemtALTDlg::OnEnChangeEdit121()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	// SampleID[3]
	GrabSampleID(3);
}

// -----------------------------------------------------------------------------
void CMFCHemtALTDlg::OnEnChangeEdit124()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	// SampleID[4]
}

// -----------------------------------------------------------------------------
void CMFCHemtALTDlg::OnEnChangeEdit127()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	// SampleID[5]
	GrabSampleID(5);
}

// ----------------------------------------------------------------------------
void CMFCHemtALTDlg::OnEnChangeEdit130()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	// SampleID[6]
}

// ----------------------------------------------------------------------------
void CMFCHemtALTDlg::OnEnChangeEdit136()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	// SampleID[8]
	GrabSampleID(8);
}

// ----------------------------------------------------------------------------
void CMFCHemtALTDlg::OnEnChangeEdit139()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	// SampleID[9]
}

// ----------------------------------------------------------------------------
void CMFCHemtALTDlg::OnEnChangeEdit82()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	// SampleID[10]
	GrabSampleID(10);
}

// -----------------------------------------------------------------------------
void CMFCHemtALTDlg::OnEnChangeEdit85()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	// SampleID[11]
	GrabSampleID(11);
}

// -----------------------------------------------------------------------------
void CMFCHemtALTDlg::OnEnChangeEdit88()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	// SampleID[12]
	GrabSampleID(12);
}

// ----------------------------------------------------------------------------
void CMFCHemtALTDlg::OnEnChangeEdit91()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	// SampleID[13]
}

// ----------------------------------------------------------------------------
void CMFCHemtALTDlg::OnEnChangeEdit94()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	// SampleID[14]
	GrabSampleID(14);
}

// ---------------------------------------------------------------------------
void CMFCHemtALTDlg::OnEnChangeEdit97()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	// SampleID[15]
}

// --------------------------------------------------------------------------
void CMFCHemtALTDlg::OnEnChangeEdit100()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	// SampleID[16]
	GrabSampleID(16);
}

// --------------------------------------------------------------------------
void CMFCHemtALTDlg::OnEnChangeEdit103()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	// SampleID[17]
}

// --------------------------------------------------------------------------
void CMFCHemtALTDlg::OnEnChangeEdit106()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	// SampleID[18]
	GrabSampleID(18);
}

// --------------------------------------------------------------------------
int CMFCHemtALTDlg::GrabSampleID(int val)
{
	// get new SampleID input string



	return (0);
}

// ---------------------------------------------------------------------------
void CMFCHemtALTDlg::OnEnChangeEdit143()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}

// -------------------------------------------------------------------
void CMFCHemtALTDlg::OnBnClickedCheck25()
{
	// TODO: Add your control notification handler code here
	// Enable ALL channels

	CheckDlgButton(IDC_CHECK26, BST_UNCHECKED);

	CheckDlgButton(IDC_CHECK1, BST_CHECKED);
	CheckDlgButton(IDC_CHECK2, BST_CHECKED);
	CheckDlgButton(IDC_CHECK3, BST_CHECKED);
	CheckDlgButton(IDC_CHECK4, BST_CHECKED);
	CheckDlgButton(IDC_CHECK5, BST_CHECKED);
	CheckDlgButton(IDC_CHECK6, BST_CHECKED);
	CheckDlgButton(IDC_CHECK7, BST_CHECKED);
	CheckDlgButton(IDC_CHECK8, BST_CHECKED);
	CheckDlgButton(IDC_CHECK9, BST_CHECKED);
	CheckDlgButton(IDC_CHECK10, BST_CHECKED);
	CheckDlgButton(IDC_CHECK11, BST_CHECKED);
	CheckDlgButton(IDC_CHECK12, BST_CHECKED);
	CheckDlgButton(IDC_CHECK13, BST_CHECKED);
	CheckDlgButton(IDC_CHECK14, BST_CHECKED);
	CheckDlgButton(IDC_CHECK15, BST_CHECKED);
	CheckDlgButton(IDC_CHECK16, BST_CHECKED);
	CheckDlgButton(IDC_CHECK17, BST_CHECKED);
	CheckDlgButton(IDC_CHECK18, BST_CHECKED);
	CheckDlgButton(IDC_CHECK19, BST_CHECKED);
	CheckDlgButton(IDC_CHECK20, BST_CHECKED);



}

// -------------------------------------------------------------------
void CMFCHemtALTDlg::OnBnClickedCheck26()
{
	// TODO: Add your control notification handler code here
	// Disable ALL channels

	CheckDlgButton(IDC_CHECK25, BST_UNCHECKED);

	CheckDlgButton(IDC_CHECK1, BST_UNCHECKED);
	CheckDlgButton(IDC_CHECK2, BST_UNCHECKED);
	CheckDlgButton(IDC_CHECK3, BST_UNCHECKED);
	CheckDlgButton(IDC_CHECK4, BST_UNCHECKED);
	CheckDlgButton(IDC_CHECK5, BST_UNCHECKED);
	CheckDlgButton(IDC_CHECK6, BST_UNCHECKED);
	CheckDlgButton(IDC_CHECK7, BST_UNCHECKED);
	CheckDlgButton(IDC_CHECK8, BST_UNCHECKED);
	CheckDlgButton(IDC_CHECK9, BST_UNCHECKED);
	CheckDlgButton(IDC_CHECK10, BST_UNCHECKED);
	CheckDlgButton(IDC_CHECK11, BST_UNCHECKED);
	CheckDlgButton(IDC_CHECK12, BST_UNCHECKED);
	CheckDlgButton(IDC_CHECK13, BST_UNCHECKED);
	CheckDlgButton(IDC_CHECK14, BST_UNCHECKED);
	CheckDlgButton(IDC_CHECK15, BST_UNCHECKED);
	CheckDlgButton(IDC_CHECK16, BST_UNCHECKED);
	CheckDlgButton(IDC_CHECK17, BST_UNCHECKED);
	CheckDlgButton(IDC_CHECK18, BST_UNCHECKED);
	CheckDlgButton(IDC_CHECK19, BST_UNCHECKED);
	CheckDlgButton(IDC_CHECK20, BST_UNCHECKED);

}

// ---------------------------------------------------------------------
void CMFCHemtALTDlg::OnBnClickedCheck21()
{
	// TODO: Add your control notification handler code here
	// Heater #1

	int module = MBT->m_active_module;
	bool flag;

	if (IsDlgButtonChecked(IDC_CHECK21) == BST_CHECKED)
	{  // turn on heater flag
		flag = true;
		MBT->Module[module].Heater[0] = true;
	}
	else
	{  // turn off heater flag
		flag = false;
		MBT->Module[module].Heater[0] = false;
	}

}

// ---------------------------------------------------------------------
void CMFCHemtALTDlg::OnBnClickedCheck22()
{
	// Heater #2
	int module = MBT->m_active_module;
	bool flag;

	if (IsDlgButtonChecked(IDC_CHECK22) == BST_CHECKED)
	{  // turn on heater flag
		flag = true;
		MBT->Module[module].Heater[1] = true;
	}
	else
	{  // turn off heater flag
		flag = false;
		MBT->Module[module].Heater[1] = false;
	}

}

// ---------------------------------------------------------------------
void CMFCHemtALTDlg::OnBnClickedCheck23()
{
	// TODO: Add your control notification handler code here
	// Heater #3
	int module = MBT->m_active_module;
	bool flag;

	if (IsDlgButtonChecked(IDC_CHECK23) == BST_CHECKED)
	{  // turn on heater flag
		flag = true;
		MBT->Module[module].Heater[2] = true;
	}
	else
	{  // turn off heater flag
		flag = false;
		MBT->Module[module].Heater[2] = false;
	}

}

// ---------------------------------------------------------------------
void CMFCHemtALTDlg::OnBnClickedCheck24()
{
	// TODO: Add your control notification handler code here
	// Heater #4
	int module = MBT->m_active_module;
	bool flag;

	if (IsDlgButtonChecked(IDC_CHECK24) == BST_CHECKED)
	{  // turn on heater flag
		flag = true;
		MBT->Module[module].Heater[3] = true;
	}
	else
	{  // turn off heater flag
		flag = false;
		MBT->Module[module].Heater[3] = false;
	}

}

// -------------------------------------------------------------------------
void CMFCHemtALTDlg::OnBnClickedRadio7()
{
	// TODO: Add your control notification handler code here
	// Operating mode: Test 2 - stop auto mode & turn OFF PSU
	if (CheckIdle())
	{
		int module = MBT->m_active_module;

		if (IsDlgButtonChecked(IDC_RADIO7))
		{
			m_operation = TEST2_MODE;  // "test mode"
			
			MBT->Module[module].op_mode = m_operation;

			// Read temperature settings & display
			AcquireLogData(module);             // no use of I2C, updates .HVref
			// aquireTempValues(module);           // takes looong time...
			UpdateTempVal(module);				// displays
			SetTestMode(m_operation);
		}
		else {
			m_operation = IDLE_MODE; // "idle"
			MBT->Module[module].op_mode = m_operation;
			SetTestMode(m_operation);
		}
	}
	else
	{
		AfxMessageBox("State not IDLE, END first!", MB_OK);
	}

}

// ----------------------------------------------------------------------------
void CMFCHemtALTDlg::OnBnClickedCheck27()
{
	// TODO: Add your control notification handler code here
	// Set Ileak gain range. 
	// checked is high gain

	int module = MBT->m_active_module;

	if (IsDlgButtonChecked(IDC_CHECK27) == BST_CHECKED)
	{   // set HI gain
		MBT->Module[module].thr_gain = ADC2ILK_HI_GN;
		MBT->SetThrGain(module, true);
	}
	else
	{   // set Low gain
		MBT->Module[module].thr_gain = ADC2ILK_LOW_GN;
		MBT->SetThrGain(module, false);
	}

	// Update display
	AcquireLogData(module);   // updates.HVref
	DisplayResults(module);

}

// ----------------------------------------------------------------------------
int CMFCHemtALTDlg::DisplayHighVolts(int module)
{
	// Display high voltage value read from ADC
	// module:   module #

	int retVal = 0;
	int val;
	MBT->ReadAnlg(module, HV_ANLG, &val);  // HV_ANLG

	float volts = ((float)val)*m_hv_rd_b1[module] + m_hv_rd_b0[module];
	MBT->Module[module].HVref = int(volts * FLOAT2FXD);  // 10ths of a volt

	CString str;
	CEdit* pEdit;
	str.Format("%4.3f", (volts));
	pEdit = (CEdit*)GetDlgItem(IDC_EDIT70);
	pEdit->SetWindowText(str);

	return (retVal);

}

// -----------------------------------------------------------------------------
void CMFCHemtALTDlg::ShutDown(void)
{
	// executed on exit / cancel -- shuts down system
	// need to check for module presence before calling

	if (!MBT->CheckNiDAQ())
	{
		for (int j = 0; j < Nmod; j++)
		{
			if (CheckModuleInstalled(j))
			{
				MBT->SetHvEnable(j, false);  // PSU OFF
				MBT->SetHvDac(j, 0);
				MBT->SetGate(j, 0);
				MBT->DisableTcServos(j);     // TC heaters off
			}
		}
	}
}

// -----------------------------------------------------------------------------
int CMFCHemtALTDlg::CheckModuleInstalled(int module)
{
	// check for presence of a module
	// note: ideally would have version # in FPGA register
	// for now write HV dac with 0x37 and readback.
	// in case its already set, save value & restore.

	// TODO add implementation

	return (1);
}