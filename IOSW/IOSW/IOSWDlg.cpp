
// IOSWDlg.cpp : implementation file
//

#include "stdafx.h"
#include "IOSW.h"
#include "IOSWDlg.h"
#include "afxdialogex.h"
#include "IOSWUtility.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CIOSWDlg dialog



CIOSWDlg::CIOSWDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_IOSW_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
	m_bTrayStatus = false;
	m_nPowerDelayTime = 0;
	m_bPWROffComplete = false;
}

void CIOSWDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_IOSCONNECTION, m_btnIOSConnection);
	DDX_Control(pDX, IDC_BUTTON_IOSDISCONNECTION, m_btnIOSDisconnection);
	DDX_Control(pDX, IDC_BUTTON_HOSTCONNECTION, m_btnHOSTConnection);
	DDX_Control(pDX, IDC_BUTTON_HOSTDISCONNECTION, m_btnHOSTDisconnection);
	DDX_Control(pDX, IDC_BUTTON_GUICONNECTION, m_btnGUIConnection);
	DDX_Control(pDX, IDC_BUTTON_GUIDISCONNECTION, m_btnGUIDisconnection);
	DDX_Control(pDX, IDC_BUTTON_IOBOARDCONNECTION, m_btnIOBoardConnection);
	DDX_Control(pDX, IDC_BUTTON_IOBOARDDISCONNECTION, m_btnIOBoardDisconnection);
	DDX_Control(pDX, IDC_BUTTON_POWERON, m_btnPowerON);
	DDX_Control(pDX, IDC_BUTTON_POWEROFF, m_btnPowerOFF);
}

BEGIN_MESSAGE_MAP(CIOSWDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_TRAYICON_MSG, OnTrayIcomMessage)
	ON_COMMAND(IOSW_TRAY_SHOW, OnTrayShow)
	ON_COMMAND(IOSW_TRAY_EXIT, OnTrayExit)
	ON_BN_CLICKED(IDC_BUTTON_IOSCONNECTION, &CIOSWDlg::OnBnClickedButtonIosconnection)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_GUICONNECTION, &CIOSWDlg::OnBnClickedButtonGuiconnection)
	ON_BN_CLICKED(IDC_BUTTON_HOSTCONNECTION, &CIOSWDlg::OnBnClickedButtonHostconnection)
	ON_BN_CLICKED(IDC_BUTTON_IOBOARDCONNECTION, &CIOSWDlg::OnBnClickedButtonIoboardconnection)
	ON_BN_CLICKED(IDOK, &CIOSWDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_IOSDISCONNECTION, &CIOSWDlg::OnBnClickedButtonIosdisconnection)
	ON_BN_CLICKED(IDC_BUTTON_HOSTDISCONNECTION, &CIOSWDlg::OnBnClickedButtonHostdisconnection)
	ON_BN_CLICKED(IDC_BUTTON_GUIDISCONNECTION, &CIOSWDlg::OnBnClickedButtonGuidisconnection)
	ON_BN_CLICKED(IDC_BUTTON_IOBOARDDISCONNECTION, &CIOSWDlg::OnBnClickedButtonIoboarddisconnection)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_BUTTON_POWEROFF, &CIOSWDlg::OnBnClickedButtonPoweroff)
	ON_BN_CLICKED(IDC_BUTTON_POWERON, &CIOSWDlg::OnBnClickedButtonPoweron)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CIOSWDlg message handlers

BOOL CIOSWDlg::OnInitDialog()
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
	m_pEngine = NULL;

	m_pEngine = new CIOSWEngine();
	m_pEngine->InitEngine();

	// Power Delay Time
	m_nPowerDelayTime = LoadConfigNumber(_T("PWR_INTERFACE"), _T("PWR_DELAY_TIME"));

	SetTimer(100, 1000, NULL);

	m_pEngine->StartIOBoardInterface();
	m_pEngine->StartThrottleInterface();
	m_pEngine->StartGUIInterface();
	m_pEngine->StartHostInterface();
	m_pEngine->StartIOSInterface();
	m_pEngine->StartNexwareInterface();

	m_bTrayStatus = false;
	m_bDebugMode = false;

	TraySetting();

	CRect rect;
	GetWindowRect(&rect);

	//SetWindowPos(NULL, rect.left, rect.top, rect.Width() - 300, rect.Height(), SWP_NOMOVE);

	//ShowWindow(SW_SHOWMINIMIZED);
	//PostMessage(WM_SHOWWINDOW, FALSE, SW_OTHERUNZOOM);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CIOSWDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else if (nID == SC_MINIMIZE)
	{
		ShowWindow(SW_HIDE);
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}

}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CIOSWDlg::OnPaint()
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

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CIOSWDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CIOSWDlg::DoPowerDistributorOn()
{
	SetTimer(100, 1000, NULL);
}

void CIOSWDlg::DoPowerDistributorOff()
{
	SetTimer(300, 1000, NULL);
}


void CIOSWDlg::OnBnClickedButtonIosconnection()
{
	if (m_pEngine != NULL) {
		m_pEngine->StartIOSInterface();
		m_btnIOSDisconnection.EnableWindow(TRUE);
		m_btnIOSConnection.EnableWindow(FALSE);
	}
}



void CIOSWDlg::OnBnClickedButtonGuiconnection()
{
	if (m_pEngine != NULL) {
		m_pEngine->StartGUIInterface();
		m_btnGUIDisconnection.EnableWindow(TRUE);
		m_btnGUIConnection.EnableWindow(FALSE);
	}
}


void CIOSWDlg::OnBnClickedButtonHostconnection()
{
	if (m_pEngine != NULL) {
		m_pEngine->StartHostInterface();
		m_btnHOSTDisconnection.EnableWindow(TRUE);
		m_btnHOSTConnection.EnableWindow(FALSE);
	}
}



void CIOSWDlg::OnBnClickedButtonIoboardconnection()
{
	if (m_pEngine != NULL) {
		m_pEngine->StartIOBoardInterface();
		m_pEngine->StartThrottleInterface();
		m_pEngine->StartNexwareInterface();

		m_btnIOBoardDisconnection.EnableWindow(TRUE);
		m_btnIOBoardConnection.EnableWindow(FALSE);
	}
}



BOOL CIOSWDlg::DestroyWindow()
{
	if (m_pEngine != NULL)
	{
		delete m_pEngine;
		m_pEngine = NULL;
	}

	if (m_bTrayStatus) 
	{
		NOTIFYICONDATA  nid;
		nid.cbSize = sizeof(nid);
		nid.hWnd = m_hWnd;			
		nid.uID = IDI_ICON1;
										
		// 작업 표시줄(TaskBar)의 상태 영역에 아이콘을 삭제한다.
		Shell_NotifyIcon(NIM_DELETE, &nid);
	}

	return CDialogEx::DestroyWindow();
}


void CIOSWDlg::OnTimer(UINT_PTR nIDEvent)
{

	if (nIDEvent == 100) // Power On;
	{
		static int nOnCount = 0;

		if (nOnCount == 3)
		{
			if (m_pEngine != NULL)
			{
				m_pEngine->StartPowerInterface(POWER_ON);
				m_btnPowerON.EnableWindow(FALSE);
				TRACE(_T("전원분배기 ON 시작\n"));
			}
		}

		if (nOnCount == 5)
		{
			if (m_pEngine != NULL)
			{
				static int nTCount = 0;

				m_pEngine->StopPowerInterface();
				KillTimer(100);
				nOnCount = 0;
				m_btnPowerOFF.EnableWindow(TRUE);

				if (nTCount == 0) {
					SetTimer(900, 1000, NULL);
					nTCount++;
				}
				
				TRACE(_T("전원분배기 ON 끝\n"));
			}
		}

		nOnCount++;

	}

	if (nIDEvent == 200) // Power Shutdown 
	{
		static int nShutDownCount = 0;

		nShutDownCount++;

		if (nShutDownCount == m_nPowerDelayTime)
		{
			if (m_pEngine != NULL)
			{
				m_pEngine->StartPowerInterface(POWER_OFF);
			}				
		}
		
		if (nShutDownCount >= (m_nPowerDelayTime + 2))
		{
			if (m_pEngine != NULL)
			{
				m_pEngine->StopPowerInterface();
			}

			char szCommand[50];
			memset(&szCommand, 0x00, 50);

			sprintf(szCommand, "shutdown -s -t %d", 5);
			system(szCommand);

			KillTimer(200);

			this->DestroyWindow();
		}
	}

	if (nIDEvent == 300) // Power Shutdown 
	{
		static int nOffCount = 0;

		nOffCount++;

		if (nOffCount == m_nPowerDelayTime)
		{
			if (m_pEngine != NULL)
			{
				m_pEngine->StartPowerInterface(POWER_OFF);
				TRACE(_T("전원분배기 OFF 시작\n"));
			}
		}

		if (nOffCount >= (m_nPowerDelayTime + 2))
		{
			if (m_pEngine != NULL)
			{
				m_pEngine->StopPowerInterface();
				m_btnPowerON.EnableWindow(TRUE);
			}

			m_bPWROffComplete = true;
			TRACE(_T("전원분배기 OFF 끝\n"));
			KillTimer(300);
			nOffCount = 0;

		}
	}

	if (nIDEvent == 500)
	{
		if (m_pEngine != NULL)
		{
			CIOSWDataManager* pMgr = m_pEngine->GetDataManager();
			IOSW_to_IOBOARD sInfo;
			Host_To_Cockpit_Data_Type sHost;

			pMgr->GetHOST2CockpitData(&sHost);
			SetDlgItemInt(IDC_EDIT_INSTTIMETAG, sHost.INST_TIMETAG);

			pMgr->GetIOSW2IOBoardData(&sInfo, 41);
			SetDlgItemInt(IDC_EDIT_DEBUG_SA, sInfo.CH3_WIDTH_28V);

			pMgr->GetIOSW2IOBoardData(&sInfo, 42);
			SetDlgItemInt(IDC_EDIT_DEBUG_SAI, sInfo.CH3_WIDTH_28V);

			pMgr->GetIOSW2IOBoardData(&sInfo, 43);
			SetDlgItemInt(IDC_EDIT_DEBUG_ALTIMETER, sInfo.CH3_WIDTH_28V);

			pMgr->GetIOSW2IOBoardData(&sInfo, 44);
			SetDlgItemInt(IDC_EDIT_DEBUG_AOA, sInfo.CH3_WIDTH_28V);

			pMgr->GetIOSW2IOBoardData(&sInfo, 45);
			SetDlgItemInt(IDC_EDIT_DEBUG_VVI, sInfo.CH3_WIDTH_28V);

			pMgr->GetIOSW2IOBoardData(&sInfo, 46);
			SetDlgItemInt(IDC_EDIT_DEBUG_CLOCK, sInfo.CH3_WIDTH_28V);

			pMgr->GetIOSW2IOBoardData(&sInfo, 47);
			SetDlgItemInt(IDC_EDIT_DEBUG_CPA, sInfo.CH3_WIDTH_28V);

			pMgr->GetIOSW2IOBoardData(&sInfo, 48);
			SetDlgItemInt(IDC_EDIT_DEBUG_EEMD, sInfo.CH3_WIDTH_28V);

			pMgr->GetIOSW2IOBoardData(&sInfo, 49);
			SetDlgItemInt(IDC_EDIT_DEBUG_FQI, sInfo.CH3_WIDTH_28V);
		
			pMgr->GetIOSW2IOBoardData(&sInfo, 10);
			SetDlgItemInt(IDC_EDIT_DEBUG_UTIL, sInfo.UTIL_GAUGE);
			SetDlgItemInt(IDC_EDIT_DEBUG_LAMP, sInfo.CH3_WIDTH_28V);

			Cockpit_To_Host_Data_Type sCockpit;
			pMgr->GetCockpit2HOSTData(&sCockpit);
			//SetDlgItemInt(IDC_EDIT_SAIKNOB, sCockpit.IO2HOST.Main_Panel.Indicator.Standby_Attitude_Knob_Value);
			//SetDlgItemInt(IDC_EDIT_ALTIMETERKNOB, sCockpit.IO2HOST.Main_Panel.Indicator.Altimeter_Knob_Value);

			pMgr->GetHOST2CockpitData(&sHost);
			SetDlgItemInt(IDC_EDIT_DEBUG_MODE, sHost.MTD_MODE);

		}
	}

	if (nIDEvent == 900)
	{
		if (m_pEngine != NULL)
		{
			CIOSWDataManager* pMgr = m_pEngine->GetDataManager();
			static int nPWRCount = 0;
			static bool_type bPWRSFlag = bFALSE;
			static bool bPWROFF = false;

			SM_IOS_To_Cockpit sIOSData;
			::memset(&sIOSData, 0x00, sizeof(SM_IOS_To_Cockpit));
			pMgr->GetIOS2CockpitData(&sIOSData);

			if (sIOSData.Sub_SPT_Flag != bPWRSFlag)
			{
				if (sIOSData.Sub_SPT_Flag == bTRUE)
				{
					m_bPWROffComplete = false;
					OnBnClickedButtonPoweroff();
					bPWROFF = true;
				}

				bPWRSFlag = sIOSData.Sub_SPT_Flag;
			}

			if (bPWROFF == true && m_bPWROffComplete == true)
			{
				OnBnClickedButtonPoweron();
				bPWROFF = false;
			}

		}
	}
	CDialogEx::OnTimer(nIDEvent);
}



void CIOSWDlg::OnBnClickedOk()
{
	PostMessage(WM_SHOWWINDOW, FALSE, SW_OTHERUNZOOM);

}


BOOL CIOSWDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)	// ESC 동작 막기
	{
		return TRUE;
	}

	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_SPACE)	// Debug 동작 막기
	{
		CRect rect;
		GetWindowRect(&rect);

		if (m_bDebugMode == false)
		{
			SetWindowPos(NULL, rect.left, rect.top, rect.Width() + 300, rect.Height(), SWP_NOMOVE);

			m_bDebugMode = true;

			SetTimer(500, 200, NULL);
		}
		else
		{
			KillTimer(500);

			SetWindowPos(NULL, rect.left, rect.top, rect.Width() - 300, rect.Height(), SWP_NOMOVE);

			m_bDebugMode = false;
		}

		return TRUE;
	}

	

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CIOSWDlg::TraySetting()
{
	NOTIFYICONDATA  nid;
	nid.cbSize = sizeof(nid);
	nid.hWnd = m_hWnd;									// 메인 윈도우 핸들
	nid.uID = IDI_ICON1;							// 아이콘 리소스 ID
	nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;		// 플래그 설정
	nid.uCallbackMessage = WM_TRAYICON_MSG;				// 콜백메시지 설정
	nid.hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);	// 아이콘 로드   
	lstrcpy(nid.szTip, _T("F-15K MTD I/O 소프트웨어"));	// Tray 출력 텍스트

	Shell_NotifyIcon(NIM_ADD, &nid);
	SendMessage(WM_SETICON, (WPARAM)TRUE, (LPARAM)nid.hIcon);
	m_bTrayStatus = true;
}


void CIOSWDlg::OnBnClickedButtonIosdisconnection()
{
	if (m_pEngine != NULL) {
		m_pEngine->StopIOSInterface();
		m_btnIOSDisconnection.EnableWindow(FALSE);
		m_btnIOSConnection.EnableWindow(TRUE);
	}
}


void CIOSWDlg::OnBnClickedButtonHostdisconnection()
{
	if (m_pEngine != NULL) {
		m_pEngine->StopHostInterface();
		m_btnHOSTDisconnection.EnableWindow(FALSE);
		m_btnHOSTConnection.EnableWindow(TRUE);
	}
}


void CIOSWDlg::OnBnClickedButtonGuidisconnection()
{
	if (m_pEngine != NULL) {
		m_pEngine->StopGUIInterface();
		m_btnGUIDisconnection.EnableWindow(FALSE);
		m_btnGUIConnection.EnableWindow(TRUE);
	}
}


void CIOSWDlg::OnBnClickedButtonIoboarddisconnection()
{
	if (m_pEngine != NULL) {
		m_pEngine->StopIOBoardInterface();
		m_pEngine->StopThrottleInterface();
		m_pEngine->StopNexwareInterface();

		m_btnIOBoardDisconnection.EnableWindow(FALSE);
		m_btnIOBoardConnection.EnableWindow(TRUE);
	}
}

void CIOSWDlg::OnTrayShow()
{
	ShowWindow(SW_SHOW);
}

void CIOSWDlg::OnTrayExit()
{
	CIOSWDlg::OnOK();
}

LRESULT CIOSWDlg::OnTrayIcomMessage(WPARAM wParam, LPARAM lParam)
{
	switch (lParam) 
	{
	case WM_LBUTTONDBLCLK:
		{
			ShowWindow(SW_SHOWDEFAULT);
		}
		break;
	case WM_RBUTTONUP:
		{
			CPoint ptMouse;
			::GetCursorPos(&ptMouse);

			CMenu menu;
			menu.LoadMenu(IDR_MENU1);
			CMenu *pMenu = menu.GetSubMenu(0);

			HWND _hwnd = GetSafeHwnd();
			::SetForegroundWindow(_hwnd);

			pMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, ptMouse.x, ptMouse.y, AfxGetMainWnd());

		}
		break;
	default:
		break;
	}


	return 0L;
}

void CIOSWDlg::OnOK()
{
	if (MessageBox(_T("입출력 소프트웨어를 종료하시겠습니까?"), _T("F-15K MTD I/O SW"), MB_ICONQUESTION | MB_YESNO | MB_DEFBUTTON2) == IDYES)
	{
		CDialogEx::OnOK();
	}
}


void CIOSWDlg::OnCancel()
{
	if (MessageBox(_T("입출력 소프트웨어를 종료하시겠습니까?"), _T("F-15K MTD I/O SW"), MB_ICONQUESTION | MB_YESNO | MB_DEFBUTTON2) == IDYES)
	{
		CDialogEx::OnCancel();
	}
}


int CIOSWDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	//ShowWindow(SW_HIDE);

	return 0;
}

void CIOSWDlg::DoSystemOff()
{
	static int nFirst = 0;

	if (nFirst == 0) {
		SetTimer(200, 1000, NULL);
		//char szCommand[50];
		//memset(&szCommand, 0x00, 50);

		//sprintf(szCommand, "shutdown -s -t %d", 5);
		//system(szCommand);

		nFirst++;
	}

	//this->DestroyWindow();

	CDialogEx::OnClose();
}

void CIOSWDlg::OnBnClickedButtonPoweroff()
{
	if (m_pEngine != NULL)
	{
		m_pEngine->DoSystemOnOff(0x01, false);
		DoPowerDistributorOff();
		m_btnPowerOFF.EnableWindow(FALSE);
	}
}


void CIOSWDlg::OnBnClickedButtonPoweron()
{
	if (m_pEngine != NULL)
	{
		m_pEngine->DoSystemOnOff(0x00, false);
		DoPowerDistributorOn();
		m_btnPowerON.EnableWindow(FALSE);
	}

}

void CIOSWDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default

	CDialogEx::OnClose();
}
