
// IOSWGUI.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "IOSWGUI.h"
#include "IOSWGUIDlg.h"
#include "IOSWLoginDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define IOSWGUI_UNIQUE_MUTEXT _T( "6332341A7-1119-1219-804E-86A49BE36D21" )


// CIOSWGUIApp

BEGIN_MESSAGE_MAP(CIOSWGUIApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CIOSWGUIApp construction

CIOSWGUIApp::CIOSWGUIApp()
{
	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	m_pIOSWGUIDlg = NULL;

}


// The one and only CIOSWGUIApp object

CIOSWGUIApp theApp;


// CIOSWGUIApp initialization

BOOL CIOSWGUIApp::InitInstance()
{
	// 단일 SW 실행 코드 시작
	HANDLE hMutexOneInstance = ::CreateMutex(NULL, TRUE, IOSWGUI_UNIQUE_MUTEXT);
	BOOL bFound = FALSE;

	// 만약 이미 만들어져 있다면 Instance가 이미 존재함
	if (::GetLastError() == ERROR_ALREADY_EXISTS)
		bFound = TRUE;

	if (hMutexOneInstance)
		::ReleaseMutex(hMutexOneInstance);

	// 이미 하나의 Instance가 존재하면 프로그램 종료
	if (bFound) {
		AfxMessageBox(_T("이미 입출력 GUI 소프트웨어가 실행중입니다"));
		return FALSE;
	}
	// 단일 SW 실행 코드 종료

	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// Create the shell manager, in case the dialog contains
	// any shell tree view or shell list view controls.
	CShellManager *pShellManager = new CShellManager;

	// Activate "Windows Native" visual manager for enabling themes in MFC controls
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	// Login
	CIOSWLoginDlg dlg;
	
	INT_PTR nResponse = dlg.DoModal();

	// IOSW Mode
	int nIOSMode = dlg.GetIOSWMode();

	BOOL bResult = FALSE;

	if (nResponse == IDOK)
	{
		// Create Main Dialog
		m_pIOSWGUIDlg = new CIOSWGUIDlg;
		
		m_pIOSWGUIDlg->SetIOSWMode((IOSW_MODE)nIOSMode);
		m_pIOSWGUIDlg->Create(CIOSWGUIDlg::IDD);
//		m_pIOSWGUIDlg->SetWindowPos(NULL, 0, 0, 1920, 1080, SWP_SHOWWINDOW);
		m_pIOSWGUIDlg->SetWindowPos(NULL, 0, 0, 1600, 1200, SWP_SHOWWINDOW);

		m_pIOSWGUIDlg->UpdateWindow();


		m_pMainWnd = m_pIOSWGUIDlg;

		bResult = TRUE;
	}
	else 
	{
		bResult = FALSE;
	}

	// Delete the shell manager created above.
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}
	
	return bResult;

}



int CIOSWGUIApp::ExitInstance()
{

	if (m_pIOSWGUIDlg != NULL) {

		delete m_pIOSWGUIDlg;
		m_pIOSWGUIDlg = NULL;
	}

	return CWinApp::ExitInstance();
}
