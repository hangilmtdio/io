
// IOSWGUIDlg.cpp : implementation file
//

#include "stdafx.h"
#include "IOSWGUI.h"
#include "IOSWGUIDlg.h"
#include "afxdialogex.h"
#include "CommonDefine.h"
#include "IOSWUtilities.h"
#include "SettingDlg.h"
#include "IODetailDlg.h"
#include <fstream>

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


// CIOSWGUIDlg dialog



CIOSWGUIDlg::CIOSWGUIDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_IOSWGUI_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);

	m_pTitleBar = NULL;
	m_pSystemStatus = NULL;
	m_pToolBar = NULL;
	m_pLogImage = NULL;
	m_pKAIImage = NULL;

	m_pIOSWInterface = NULL;
	m_pDataManager = NULL;
	m_pIODeviceInfoManager = NULL;
	m_pLogManager = NULL;
}

void CIOSWGUIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CIOSWGUIDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_ERASEBKGND()
	ON_WM_DESTROY()
	ON_WM_CLOSE()
	ON_MESSAGE(UM_UPDATE_COCKPIT_LIST, OnUpdateCockpitList)
	ON_MESSAGE(UM_UPDATE_COCKPITIO_LIST, OnUpdateCockpitIOList)
	ON_MESSAGE(UM_SELECT_SETTING, OnSelectSetting)
	ON_MESSAGE(UM_UPDATE_LOGEVENT, OnUpdateLogEvent)	
	ON_WM_TIMER()
	ON_NOTIFY(NM_DBLCLK, IDC_LISTCTRL_IO, &CIOSWGUIDlg::OnClickIOList)
END_MESSAGE_MAP()


// CIOSWGUIDlg message handlers

BOOL CIOSWGUIDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_fontListHeader.CreateFont(16, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH, _T("나눔고딕"));

	m_fontListBody.CreateFont(15, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH, _T("나눔고딕"));

	m_pIOSWInterface = new CIOSWInterface();
	m_pDataManager = new CIOSWDataManager();
	m_pIODeviceInfoManager = new CIODeviceInformationManager();

	// 설정파일에서 읽어와서 설정해야 함.
	if (!LoadConfiguration())
		return FALSE;

	if (!LoadIOInformation())
		return FALSE;

	if (m_pIOSWInterface->IsInitialize())
	{
		m_pDataManager->Initialize(m_pIODeviceInfoManager);
		m_pDataManager->SetIOSWMode(m_eIOSWMode);

		m_pIOSWInterface->SetDataManager(m_pDataManager);
		m_pIOSWInterface->StartThread();
	}

	m_bmpBackgound.LoadBitmap(IDB_BITMAP_MAIN);

	m_pTitleBar = new CIOSWTitle;
	//m_pTitleBar->CreateEx(NULL, NULL, NULL, WS_CHILD | WS_VISIBLE, CRect(0, 0, 1920, 58), this, ID_TITLE_BAR);
	//m_pTitleBar->MoveWindow(0, 0, 1920, 58);
	//m_pTitleBar->SetWindowPos(NULL, 0, 0, 1920, 58, SWP_SHOWWINDOW);
	m_pTitleBar->CreateEx(NULL, NULL, NULL, WS_CHILD | WS_VISIBLE, CRect(0, 0, 1600, 58), this, ID_TITLE_BAR);
	m_pTitleBar->MoveWindow(0, 0, 1600, 58);
	m_pTitleBar->SetWindowPos(NULL, 0, 0, 1600, 58, SWP_SHOWWINDOW);

	m_pTitleBar->LoadResource();
	m_pTitleBar->UpdateWindow();
	
	m_pSystemStatus = new CIOSWSystemStatus;
	m_pSystemStatus->CreateEx(NULL, NULL, NULL, WS_CHILD | WS_VISIBLE, CRect(0, 0, 385, 961), this, ID_SYSTEMSTATUS_BAR);
//	m_pSystemStatus->MoveWindow(1513, 65, 1898, 1024);
	m_pSystemStatus->MoveWindow(1187, 65, 1572, 1024);
	m_pSystemStatus->SetWindowPos(NULL, 1187, 65, 1572, 1024, SWP_SHOWWINDOW);
	m_pSystemStatus->SetDataManager(m_pDataManager);
	m_pSystemStatus->LoadResource(m_pIODeviceInfoManager);
	m_pSystemStatus->UpdateWindow();

	m_pToolBar = new CIOSWToolbar;
	m_pToolBar->CreateEx(NULL, NULL, NULL, WS_CHILD | WS_VISIBLE, CRect(0, 0, 1499, 43), this, ID_TOOL_BAR);
	m_pToolBar->MoveWindow(0, 59, 1499, 102);
	m_pToolBar->SetWindowPos(NULL, 0, 59, 1499, 102, SWP_SHOWWINDOW);
	m_pToolBar->LoadResource();
	m_pToolBar->UpdateWindow();

	m_pLogImage = new CImageObject;
	m_pKAIImage = new CImageObject;

	m_pLogImage->SetXPosition(20);
//	m_pLogImage->SetYPosition(810);
	m_pLogImage->SetYPosition(930);

	m_pKAIImage->SetXPosition(1185);
	m_pKAIImage->SetYPosition(1038);
	
	 
	m_eCockpitType = DP_LEFT;
	m_eCockpitIOType = IK_DI;

	m_pLogImage->RegisterImage(0, CIOSWUtilities::GetImagePathFile(_T("Systemlog.bmp")));
	m_pKAIImage->RegisterImage(0, CIOSWUtilities::GetImagePathFile(_T("KAI.bmp")));

	m_listCtrlIO.Create(WS_VISIBLE | WS_CHILD | LVS_REPORT | LVS_SINGLESEL,	CRect(0, 0, 0, 0), this, IDC_LISTCTRL_IO);
//	m_listCtrlIO.SetWindowPos(NULL, 20, 105, 1159, 700, SWP_FRAMECHANGED);
	m_listCtrlIO.SetWindowPos(NULL, 20, 105, 1159, 820, SWP_FRAMECHANGED);
	m_listCtrlIO.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_DOUBLEBUFFER);


	m_listCtrlIO.SetFont(&m_fontListBody);
	m_listCtrlIO.SetItemHeight(28);
	m_listCtrlIO.SetBkColor(RGB(67, 79, 95));
	m_listCtrlIO.SetTextBkColor(RGB(67, 79, 95));
	m_listCtrlIO.SetTextColor(RGB(224, 224, 224));
	m_listCtrlIO.SetGridColor(RGB(44, 63, 78));
	m_listCtrlIO.SetGridLineWidth(1);
	m_listCtrlIO.SetGridHMode(TRUE);
	m_listCtrlIO.SetSelBkColor(RGB(47, 59, 75));
	m_listCtrlIO.SetSelTextColor(RGB(102, 153, 255));

	m_listCtrlIO.SetHeaderFont(&m_fontListHeader);
	m_listCtrlIO.SetHeaderHeight(31);
	m_listCtrlIO.SetHeaderBkColor(RGB(44, 63, 78));
	m_listCtrlIO.SetHeaderTextColor(RGB(255, 255, 255));
	m_listCtrlIO.SetHeaderLineColor(RGB(44, 63, 78));
	m_listCtrlIO.SetHeaderLineWidth(1);
	m_listCtrlIO.SetHeaderEnableResizing(FALSE);

	// Insert columns -------------------------------------------------------------------------------------------------------------------------------

	//// Insert Columns
	m_listCtrlLog.Create(WS_VISIBLE | WS_CHILD | LVS_REPORT | LVS_SINGLESEL, CRect(0, 0, 0, 0), this, IDC_LISTCTRL_LOG);
//	m_listCtrlLog.SetWindowPos(NULL, 20, 850, 1159, 180, SWP_FRAMECHANGED);
	m_listCtrlLog.SetWindowPos(NULL, 20, 970, 1159, 180, SWP_FRAMECHANGED);
	m_listCtrlLog.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_DOUBLEBUFFER);


	m_listCtrlLog.SetFont(&m_fontListBody);
	m_listCtrlLog.SetItemHeight(28);
	m_listCtrlLog.SetBkColor(RGB(67, 79, 95));
	m_listCtrlLog.SetTextBkColor(RGB(67, 79, 95));
	m_listCtrlLog.SetTextColor(RGB(224, 224, 224));
	m_listCtrlLog.SetGridColor(RGB(44, 63, 78));
	m_listCtrlLog.SetGridLineWidth(1);
	m_listCtrlLog.SetGridHMode(TRUE);
	m_listCtrlLog.SetSelBkColor(RGB(47, 59, 75));
	m_listCtrlLog.SetSelTextColor(RGB(102, 153, 255));

	m_listCtrlLog.SetHeaderFont(&m_fontListHeader);
	m_listCtrlLog.SetHeaderHeight(31);
	m_listCtrlLog.SetHeaderBkColor(RGB(44, 63, 78));
	m_listCtrlLog.SetHeaderTextColor(RGB(255, 255, 255));
	m_listCtrlLog.SetHeaderLineColor(RGB(44, 63, 78));
	m_listCtrlLog.SetHeaderLineWidth(1);
	m_listCtrlLog.SetHeaderEnableResizing(FALSE);

	// Insert columns -------------------------------------------------------------------------------------------------------------------------------
	m_listCtrlLog.InsertColumn(0, _T(""), LVCFMT_CENTER, 0, -1);
	m_listCtrlLog.InsertColumn(1, _T("Time"), LVCFMT_CENTER, 100, -1);
	m_listCtrlLog.InsertColumn(2, _T("Item"), LVCFMT_CENTER, 140, -1);
	m_listCtrlLog.InsertColumn(3, _T("Description"), LVCFMT_LEFT,919, -1);


	m_listCtrlIO.InsertColumn(0, _T(""), LVCFMT_CENTER, 0, -1);
	m_listCtrlIO.InsertColumn(1, _T("ID"), LVCFMT_CENTER, 40, -1);
	m_listCtrlIO.InsertColumn(2, _T("Name"), LVCFMT_CENTER, 200, -1);

	m_listCtrlLog.SetTextColor(RGB(245, 245, 245));

	for (int i = 0; i < 30; i++)
		m_listCtrlIO.InsertItem(i, _T(""));

	m_listCtrlIO.DeleteAllItems();

	for (int i = 0; i < 10; i++)
		m_listCtrlLog.InsertItem(i, _T(""));
	m_listCtrlLog.DeleteAllItems();

	UpdateLRUInformationHeader(m_eCockpitIOType);
	UpdateLRUInformation(m_eCockpitType, m_eCockpitIOType);

	LoadLogFile();

//	StartThread();

	SetTimer(300, 500, NULL);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

bool CIOSWGUIDlg::LoadConfiguration()
{
	if (m_pIOSWInterface == NULL)
		return false;

	CString strSendIP;
	CString strRecvIP;

	int nSendPort = 0;
	int nRecvPort = 0;

	char szSendIP[16];
	char szRecvIP[16];

	memset(&szSendIP, 0x00, sizeof(szSendIP));
	memset(&szRecvIP, 0x00, sizeof(szRecvIP));

	strSendIP = CIOSWUtilities::LoadConfigString(_T("NETWORK"), _T("IOSW_IP"));
	strRecvIP = CIOSWUtilities::LoadConfigString(_T("NETWORK"), _T("GUI_IP"));
	nSendPort = CIOSWUtilities::LoadConfigNumber(_T("NETWORK"), _T("IOSW_PORT"));
	nRecvPort = CIOSWUtilities::LoadConfigNumber(_T("NETWORK"), _T("GUI_PORT"));

	CIOSWUtilities::MtoWChar(strSendIP, szSendIP);
	CIOSWUtilities::MtoWChar(strRecvIP, szRecvIP);

	if (!m_pIOSWInterface->Initialize(szSendIP, nSendPort, szRecvIP, nRecvPort))
		return false;

	return true;
}

bool CIOSWGUIDlg::LoadIOInformation()
{
	if (m_pIODeviceInfoManager == NULL)
		return false;

	bool bResult = m_pIODeviceInfoManager->LoadDeviceInfo();

	if(bResult)
		bResult = m_pIODeviceInfoManager->LoadDeviceImageInfo();

	return bResult;

}


bool CIOSWGUIDlg::LoadLogFile()
{
	m_pLogManager = new CIOSWLogManager;

	CString strPath;
	CString strLogFile;

	strPath = CIOSWUtilities::LoadConfigString(_T("LOG"), _T("PATH"));

	//	strLogFile.Format(_T("%s\\[IOSW LOG]_%s.log"), strPath, CA2CT(CIOSWUtilities::GetCurrentDateString().c_str()));
	strLogFile.Format(_T("%s\\[IOSW LOG]_%s.log"), strPath, CIOSWUtilities::GetCurrentDateString().c_str());
	std::string strTemp;
	strTemp = std::string(CT2CA(strLogFile.operator LPCWSTR()));

	m_pLogManager->SetMonitoringLogFile(strTemp);
	m_pLogManager->SetLogWnd(this);
	m_pLogManager->StartMonitoring();

	return true;

}


void CIOSWGUIDlg::SetIOSWMode(IOSW_MODE eMode)
{
	m_eIOSWMode = eMode;

	if (m_pDataManager != NULL)
		m_pDataManager->SetIOSWMode(eMode);
}

IOSW_MODE CIOSWGUIDlg::GetIOSWMode()
{
	return m_eIOSWMode;
}

void CIOSWGUIDlg::StopIOMonitoring()
{
	// EndThread();
	//KillThread();
}

void CIOSWGUIDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CIOSWGUIDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		if (m_pLogImage != NULL) {
			m_pLogImage->DrawObject(&dc);
		}

		if (m_pKAIImage != NULL) {
			m_pKAIImage->DrawObject(&dc);
		}
/*
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);*/
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CIOSWGUIDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



BOOL CIOSWGUIDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
	if (m_bmpBackgound.m_hObject)
	{
		CDC MemDC;

		if (MemDC.CreateCompatibleDC(pDC) == FALSE)
			return FALSE;

		CBitmap *pOldBitmap = MemDC.SelectObject(&m_bmpBackgound);

		BITMAP BmpInfo;
		m_bmpBackgound.GetBitmap(&BmpInfo);

		if (m_pLogImage != NULL) {
			m_pLogImage->DrawObject(&MemDC);
		}

		if (m_pKAIImage != NULL) {
			m_pKAIImage->DrawObject(&MemDC);
		}

		pDC->BitBlt(0, 0, BmpInfo.bmWidth, BmpInfo.bmHeight, &MemDC, 0, 0, SRCCOPY);
		
		MemDC.SelectObject(pOldBitmap);
		MemDC.DeleteDC();

		return TRUE;
	}
	else
		return CDialogEx::OnEraseBkgnd(pDC);
}


void CIOSWGUIDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	
	m_bmpBackgound.DeleteObject();
}


void CIOSWGUIDlg::OnClose()
{
	//EndThread();
	
	if (m_pIOSWInterface != NULL) {
		delete m_pIOSWInterface;
		m_pIOSWInterface = NULL;
	}

	if (m_pIODeviceInfoManager != NULL)
	{
		delete m_pIODeviceInfoManager;
		m_pIODeviceInfoManager = NULL;
	}

	if (m_pTitleBar != NULL) {
		m_pTitleBar->CloseWindow();

		delete m_pTitleBar;
		m_pTitleBar = NULL;
	}

	if (m_pSystemStatus != NULL) {
		m_pSystemStatus->EndMonitoring();
		m_pSystemStatus->CloseWindow();

		delete m_pSystemStatus;
		m_pSystemStatus = NULL;
	}

	if (m_pToolBar != NULL) {
		m_pToolBar->CloseWindow();

		delete m_pToolBar;
		m_pToolBar = NULL;
	}

	if (m_pLogImage != NULL) {
		delete m_pLogImage;
		m_pLogImage = NULL;
	}

	if (m_pKAIImage != NULL) {
		delete m_pKAIImage;
		m_pKAIImage = NULL;
	}

	if (m_pLogManager != NULL)
	{
		m_pLogManager->StopMonitoring();

		delete m_pLogManager;
		m_pLogManager = NULL;
	}

	if (m_pDataManager != NULL)
	{
		delete m_pDataManager;
		m_pDataManager = NULL;
	}


	m_fontListHeader.DeleteObject();
	m_fontListBody.DeleteObject();

	this->DestroyWindow();

	CDialogEx::OnClose();
}

LRESULT CIOSWGUIDlg::OnUpdateCockpitList(WPARAM wParam, LPARAM lParam)
{
	LRESULT lResult = 1;

	m_eCockpitType = (DEVICE_POSITION)wParam;

//	UpdateLRUInformationHeader(m_eCockpitIOType);
	UpdateLRUInformation(m_eCockpitType, m_eCockpitIOType);

	return lResult;
}

LRESULT CIOSWGUIDlg::OnUpdateCockpitIOList(WPARAM wParam, LPARAM lParam)
{
	LRESULT lResult = 1;

	m_eCockpitIOType = (IO_KIND)wParam;

	UpdateLRUInformationHeader(m_eCockpitIOType);
	UpdateLRUInformation(m_eCockpitType, m_eCockpitIOType);

	return lResult;
}

LRESULT CIOSWGUIDlg::OnSelectSetting(WPARAM wParam, LPARAM lParam)
{
	LRESULT lResult = 1;

	CSettingDlg dlg;
	dlg.DoModal();

	return lResult;

}

LRESULT CIOSWGUIDlg::OnUpdateLogEvent(WPARAM wParam, LPARAM lParam)
{
	LRESULT lResult = 1;
	int nIndex = 0;
	//return 1;

	if (m_pLogManager != NULL) {

		LOGEVENT_LIST* pList = m_pLogManager->GetEventLogList();
		int nItemCount = m_listCtrlLog.GetItemCount();
		CString strTemp;

		for (LOGEVENT_LIST_ITR itr = pList->begin(); itr != pList->end(); ++itr)
		{
			IOSWEventLog* pLog = *itr;

			if (pLog) {
				nIndex++;

				if (nItemCount < nIndex) 
				{
					strTemp.Format(_T("%d"), pLog->nID);
					m_listCtrlLog.InsertItem(0, strTemp);
					//strTemp.Format(_T("%s"), CA2CT(pLog->szTime));
					strTemp.Format(_T("%s"), pLog->szTime);
					m_listCtrlLog.SetItemText(0, 1, strTemp);
					m_listCtrlLog.SetItemText(0, 2, alpszLogType[pLog->eType]);
					//strTemp.Format(_T("%s"), CA2CT(pLog->szContents));
					strTemp.Format(_T("%s"), pLog->szContents);
					m_listCtrlLog.SetItemText(0, 3, strTemp);
					
				}
			}
		}
	}
	
	return lResult;
}

void CIOSWGUIDlg::UpdateLRUInformationHeader(IO_KIND eIOType)
{
	CHeaderCtrl* pHeader = m_listCtrlIO.GetHeaderCtrl();
	int nCount = pHeader->GetItemCount();

	int nColumns = 0;
	int nColumnWidth = 0;

	switch (eIOType)
	{
	case IK_DI:
		nColumns = 36;
		nColumnWidth = 40;
		break;
	case IK_DO:
		nColumns = 16;
		nColumnWidth = 42;
		break;
	case IK_AI:
		nColumns = 10;
		nColumnWidth = 70;
		break;
	case IK_AO:
		nColumns = 22;
		nColumnWidth = 60;
		break;
	case IK_DIMMER:
		nColumns = 2;
		nColumnWidth = 70;
		break;
	default:
		break;
	}

	if ((nColumns+4) != nCount)
	{
		int i = 0;

		if (nCount != 3) {
			for (i = nCount; i >= 3; i--) {
				m_listCtrlIO.DeleteColumn(i);
			}
		}

		for ( i = 0; i < nColumns; i++) {
			CString strHeader;
			strHeader.Format(_T("Ch%02d"), i + 1);
			m_listCtrlIO.InsertColumn(3 + i, strHeader, LVCFMT_CENTER, nColumnWidth, -1);
		}

		int nTemp = nColumns * nColumnWidth;
		m_listCtrlIO.InsertColumn(nColumns + 4, _T(" "), LVCFMT_CENTER, (1239- nTemp), -1);
	}

}

void CIOSWGUIDlg::UpdateLRUInformation(DEVICE_POSITION eType, IO_KIND eIOType)
{
	if (m_pIODeviceInfoManager == NULL)
		return;

	m_listCtrlIO.DeleteAllItems();

	LIST_DEVICEINFO* plist = m_pIODeviceInfoManager->GetDeviceInforList();

	int nItemCount = 0;

	for (LIST_DEVICEINFO_ITR itr = plist->begin(); itr != plist->end(); ++itr)
	{
		CIODeviceInfo* pInfo = *itr;// m_pIODeviceInfoManager->GetDeivceInfo(nID);

		if (pInfo != NULL && pInfo->GetDevicePosition() == m_eCockpitType) {

			CString strTitle;

			strTitle.Format(_T("%d"), pInfo->GetDeviceID());
			m_listCtrlIO.InsertItem(nItemCount, strTitle);

			strTitle.Format(_T("%d"), pInfo->GetBoardID());
			m_listCtrlIO.SetItemText(nItemCount, 1, strTitle);

			pInfo->GetDeviceName(strTitle);
			m_listCtrlIO.SetItemText(nItemCount, 2, strTitle);

			LIST_IOINFO* pIOInfoList = pInfo->GetIOInfoList();

			for (LIST_IOINFO_ITR ioitr = pIOInfoList->begin(); ioitr != pIOInfoList->end(); ++ioitr)
			{
				sIOInformation* pIOInfo = *ioitr;

				if (pIOInfo != NULL && pIOInfo->eKind == m_eCockpitIOType)
				{

					int nNewData = 0;
					switch (pIOInfo->eKind)
					{
					case IK_DI:
					case IK_DO:
						//						strTemp.Format(_T("%d"), pIOInfo->szValue);
						nNewData = (int)pIOInfo->szValue;
						break;
					case IK_AI:
						nNewData = pIOInfo->nValue;
						break;
					case IK_AO:
					case IK_DIMMER:
						nNewData = (int)pIOInfo->usValue;
						//						strTemp.Format(_T("%d"), pIOInfo->usValue);
						break;
					default:
						break;
					}

	
					CString strTemp;
					strTemp.Format(_T("%d"), nNewData);

					m_listCtrlIO.SetItemText(nItemCount, pIOInfo->nChannel + 2, strTemp);

				}

				if (m_eCockpitIOType == IK_AO && pIOInfo->eKind == IK_AO_IDC)
				{
					CString strTemp;
					strTemp.Format(_T("%d"), (int) pIOInfo->fValue);

					m_listCtrlIO.SetItemText(nItemCount, pIOInfo->nChannel + 20, strTemp);

					
				}

				if (m_eCockpitIOType == IK_AI && pIOInfo->eKind == IK_AI_SR)
				{
					CString strTemp;
					strTemp.Format(_T("%0.1f"), pIOInfo->fValue);

					m_listCtrlIO.SetItemText(nItemCount, pIOInfo->nChannel + 8, strTemp);


				}
			}

			nItemCount++;
		}
	}
	//LIST_ID IDList;
	//LIST_ID_ITR itr;

	//m_pIODeviceInfoManager->GetDeviceIDList(&IDList, eType);
	//int nItemCount = 0;
	//for (itr = IDList.begin(); itr != IDList.end(); ++itr)
	//{
	//	int nID = *itr;

	//	CIODeviceInfo* pInfo = m_pIODeviceInfoManager->GetDeivceInfo(nID);

	//	if (pInfo != NULL) {
	//		CString strTemp;

	//		strTemp.Format(_T("%d"), pInfo->GetDeviceID());
	//		m_listCtrlIO.InsertItem(nItemCount, strTemp);

	//		strTemp.Format(_T("%d"), pInfo->GetBoardID());
	//		m_listCtrlIO.SetItemText(nItemCount, 1, strTemp);

	//		pInfo->GetDeviceName(strTemp);
	//		m_listCtrlIO.SetItemText(nItemCount, 2,strTemp);

	//		LIST_ID IndexList;
	//		LIST_ID_ITR IndexItr;

	//		pInfo->GetIOIndexList(&IndexList, eIOType);

	//		for (IndexItr = IndexList.begin(); IndexItr != IndexList.end(); ++IndexItr) 
	//		{
	//			int nIndex = *IndexItr;

	//			sIOInformation* pIOInfo = pInfo->GetIOInfo(nIndex);
	//
	//			if (pIOInfo != NULL)
	//			{	
	//				switch (pIOInfo->eKind)
	//				{
	//				case IK_DI:
	//				case IK_DO:
	//					strTemp.Format(_T("%d"), pIOInfo->szValue);
	//					break;
	//				case IK_AI:
	//				case IK_AO:
	//				case IK_DIMMER:
	//					strTemp.Format(_T("%d"), pIOInfo->usValue);
	//					break;
	//				default:
	//					break;
	//				}

	//				m_listCtrlIO.SetItemText(nItemCount, pIOInfo->nChannel+2, strTemp);
	//			}
	//		}


	//		nItemCount++;
	//	}
	//}

}

void CIOSWGUIDlg::UpdateLRUIOMonitoring()
{
	if (m_pDataManager == NULL || m_pIODeviceInfoManager == NULL)
		return;

	//LIST_ID IDList;
	//LIST_ID_ITR itr;

	//m_pIODeviceInfoManager->GetDeviceIDList(&IDList, m_eCockpitType);
	//int nItemCount = 0;
	//for (itr = IDList.begin(); itr != IDList.end(); ++itr)
	//{
	//	int nID = *itr;

	//	CIODeviceInfo* pInfo = m_pIODeviceInfoManager->GetDeivceInfo(nID);

	//	if (pInfo != NULL) {
	//		CString strTemp;

	//		LIST_ID IndexList;
	//		LIST_ID_ITR IndexItr;

	//		pInfo->GetIOIndexList(&IndexList, m_eCockpitIOType);

	//		for (IndexItr = IndexList.begin(); IndexItr != IndexList.end(); ++IndexItr)
	//		{
	//			int nIndex = *IndexItr;

	//			sIOInformation* pIOInfo = pInfo->GetIOInfo(nIndex);

	//			if (pIOInfo != NULL)
	//			{	///
	//				switch (pIOInfo->eKind)
	//				{
	//				case IK_DI:
	//				case IK_DO:
	//					strTemp.Format(_T("%d"), pIOInfo->szValue);
	//					break;
	//				case IK_AI:
	//				case IK_AO:
	//				case IK_DIMMER:
	//					strTemp.Format(_T("%d"), pIOInfo->usValue);
	//					break;
	//				default:
	//					break;
	//				}

	//				m_listCtrlIO.SetItemText(nItemCount, pIOInfo->nChannel + 2, strTemp);
	//				
	//			}
	//		}

	//		nItemCount++;
	//	}
	//}


	// m_pIODeviceInfoManager->GetDeviceIDList(&IDList, m_eCockpitType);
	LIST_DEVICEINFO* plist = m_pIODeviceInfoManager->GetDeviceInforList();

	int nItemCount = 0;

	for (LIST_DEVICEINFO_ITR itr = plist->begin(); itr != plist->end(); ++itr)
	{
		CIODeviceInfo* pInfo = *itr;// m_pIODeviceInfoManager->GetDeivceInfo(nID);

		if (pInfo != NULL && pInfo->GetDevicePosition() == m_eCockpitType) {
			
			LIST_IOINFO* pIOInfoList = pInfo->GetIOInfoList();

			for (LIST_IOINFO_ITR ioitr = pIOInfoList->begin(); ioitr != pIOInfoList->end(); ++ioitr)
			{
				sIOInformation* pIOInfo = *ioitr;

				if (pIOInfo != NULL && pIOInfo->eKind == m_eCockpitIOType)
				{	
					
					int nNewData = 0;
					switch (pIOInfo->eKind)
					{
					case IK_DI:
					case IK_DO:
//						strTemp.Format(_T("%d"), pIOInfo->szValue);
						nNewData = (int) pIOInfo->szValue;
						break;
					case IK_AI:
						nNewData = pIOInfo->nValue;
						break;
					case IK_AO:
					case IK_DIMMER:
						nNewData = (int)pIOInfo->usValue;
//						strTemp.Format(_T("%d"), pIOInfo->usValue);
						break;
				default:
						break;
					}
	
					int nOldData = _ttoi(m_listCtrlIO.GetItemText(nItemCount, pIOInfo->nChannel + 2));

					if (nOldData != nNewData)
					{
						CString strTemp;
						strTemp.Format(_T("%d"), nNewData);

						m_listCtrlIO.SetItemText(nItemCount, pIOInfo->nChannel + 2, strTemp);

					}					

				}

				if (m_eCockpitIOType == IK_AO && pIOInfo->eKind == IK_AO_IDC)
				{
					int nNewData = (int)pIOInfo->fValue;
					int nOldData = _ttoi(m_listCtrlIO.GetItemText(nItemCount, pIOInfo->nChannel + 20));

					if (nOldData != nNewData)
					{
						CString strTemp;
						strTemp.Format(_T("%d"), nNewData);

						m_listCtrlIO.SetItemText(nItemCount, pIOInfo->nChannel + 20, strTemp);

					}
				}

				if (m_eCockpitIOType == IK_AI && pIOInfo->eKind == IK_AI_SR)
				{
					float fNewData = pIOInfo->fValue;
					float fOldData = (float) _ttof(m_listCtrlIO.GetItemText(nItemCount, pIOInfo->nChannel + 8));

					if (fOldData != fNewData)
					{
						CString strTemp;
						strTemp.Format(_T("%0.1f"), fNewData);

						m_listCtrlIO.SetItemText(nItemCount, pIOInfo->nChannel + 8, strTemp);

					}
				}
			}

			nItemCount++;
		}
	}

}

void CIOSWGUIDlg::OnClickIOList(NMHDR *pNMHDR, LRESULT *pResult)
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int nClickItem = pNMListView->iItem;

	if (nClickItem < 0)	
		return;

	int nDeviceID = 0;
	int nBoardID = 0;

	nDeviceID = _ttoi(m_listCtrlIO.GetItemText(nClickItem, 0));
	nBoardID = _ttoi(m_listCtrlIO.GetItemText(nClickItem, 1));


	CIODetailDlg dlg;
	
	dlg.SetLRUInfo(nDeviceID, nBoardID);
	dlg.SetIODeviceInfoManager(m_pIODeviceInfoManager);
	dlg.SetDataManager(m_pDataManager);

	dlg.DoModal();
	
	*pResult = 0;
}

//DWORD CIOSWGUIDlg::ThreadProc()
//{
	//DWORD nOld = GetTickCount();

	//while (1)
	//{
	//	DWORD nNew = GetTickCount();

	//	if (nNew - nOld >= 500)
	//	{

	//		UpdateLRUIOMonitoring();

	//		nOld = nNew;
	//	}

	//	Sleep(1);

	//	if (m_bEndThread == TRUE) 
	//		break;   // Thread 종료 조건
	//}

//	return 1;

//}

void CIOSWGUIDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 300) {
		UpdateLRUIOMonitoring();
	}
	
	CDialogEx::OnTimer(nIDEvent);
}


BOOL CIOSWGUIDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)	// ESC 동작 막기
	{
		return TRUE;
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


//void CIOSWGUIDlg::PostNcDestroy()
//{
//	EndThread();
//
//	CDialogEx::PostNcDestroy();
//}


void CIOSWGUIDlg::OnCancel()
{
	// TODO: Add your specialized code here and/or call the base class

	//CDialogEx::OnCancel();
}


void CIOSWGUIDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class

	//CDialogEx::OnOK();
}
