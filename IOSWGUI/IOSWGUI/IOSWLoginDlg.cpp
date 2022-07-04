// IOSWLoginDlg.cpp : implementation file
//

#include "stdafx.h"
#include "IOSWGUI.h"
#include "IOSWLoginDlg.h"
#include "afxdialogex.h"
#include "IOSWUtilities.h"
// CIOSWLoginDlg dialog

IMPLEMENT_DYNAMIC(CIOSWLoginDlg, CDialog)

CIOSWLoginDlg::CIOSWLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_LOGIN_DIALOG, pParent)
	, m_strID(_T(""))
	, m_strPassword(_T(""))
	, m_nIOSWMode(0)
{


}

CIOSWLoginDlg::~CIOSWLoginDlg()
{
}

void CIOSWLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ID, m_strID);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_strPassword);
	DDX_Radio(pDX, IDC_RADIO_MONITORING, m_nIOSWMode);
}


BEGIN_MESSAGE_MAP(CIOSWLoginDlg, CDialog)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDOK, &CIOSWLoginDlg::OnBnClickedOk)
	ON_STN_CLICKED(IDC_STATIC_OK, &CIOSWLoginDlg::OnStnClickedStaticOk)
	ON_STN_CLICKED(IDC_STATIC_CANCEL, &CIOSWLoginDlg::OnStnClickedStaticCancel)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_RADIO_MONITORING, IDC_RADIO_MAINTENANCE, OnIOSWModeRadioCtrl)
END_MESSAGE_MAP()


// CIOSWLoginDlg message handlers


BOOL CIOSWLoginDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_bmpBackgound.LoadBitmap(IDB_BITMAP_LOGIN);

	// Create brush
	m_hEditBrush = CreateSolidBrush(RGB(51, 68, 84));
	m_hRadioBrush = CreateSolidBrush(RGB(66, 83, 99));

	BITMAP BmpInfo;
	m_bmpBackgound.GetBitmap(&BmpInfo);

	this->MoveWindow(0 + (1600 - (int)BmpInfo.bmWidth) / 2, 0 + (1200 - (int)BmpInfo.bmHeight) / 2, (int)BmpInfo.bmWidth, (int)BmpInfo.bmHeight);

	// Set window position, size of controls
	GetDlgItem(IDC_EDIT_ID)->MoveWindow(98, 158, 191, 32);
	GetDlgItem(IDC_EDIT_PASSWORD)->MoveWindow(98, 200, 191, 32);
	GetDlgItem(IDC_STATIC_OK)->MoveWindow(294, 155, 100, 80);
	GetDlgItem(IDC_STATIC_CANCEL)->MoveWindow(394, 155, 100, 80);
	GetDlgItem(IDC_RADIO_MONITORING)->MoveWindow(242, 121, 20, 20);
	GetDlgItem(IDC_RADIO_MAINTENANCE)->MoveWindow(358, 121, 20, 20);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


BOOL CIOSWLoginDlg::OnEraseBkgnd(CDC* pDC)
{
	if (m_bmpBackgound.m_hObject)
	{
		CDC MemDC;

		if (MemDC.CreateCompatibleDC(pDC) == FALSE)
			return FALSE;

		CBitmap *pOldBitmap = MemDC.SelectObject(&m_bmpBackgound);

		BITMAP BmpInfo;
		m_bmpBackgound.GetBitmap(&BmpInfo);

		pDC->BitBlt(0, 0, BmpInfo.bmWidth, BmpInfo.bmHeight, &MemDC, 0, 0, SRCCOPY);

		MemDC.SelectObject(pOldBitmap);
		MemDC.DeleteDC();

		return TRUE;
	}
	else
		return CDialog::OnEraseBkgnd(pDC);
}


HBRUSH CIOSWLoginDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	switch (nCtlColor)
	{
		case CTLCOLOR_EDIT:
		{
			pDC->SetTextColor(RGB(224, 224, 224));
			pDC->SetBkMode(TRANSPARENT);
			return m_hEditBrush;
			

		}
		case CTLCOLOR_STATIC:
		{
			pDC->SetTextColor(RGB(255, 255, 255));
			pDC->SetBkMode(TRANSPARENT);
			return m_hRadioBrush;

		}
	}
	
	return hbr;
}


void CIOSWLoginDlg::OnDestroy()
{
	CDialog::OnDestroy();

	// Delete oject for bitmap
	m_bmpBackgound.DeleteObject();

	// Delete object for brush
	DeleteObject(m_hEditBrush);
	DeleteObject(m_hRadioBrush);
}


BOOL CIOSWLoginDlg::CheckLogin(CString strID, CString strPassword)
{
	BOOL bResult = FALSE;

	CString strSaveID;
	CString strSavePassword;
	CString strPath;

	// 설정파일에서 ID/ Password를 읽어온다. 
	strSaveID = CIOSWUtilities::LoadConfigString(_T("LOGIN"), _T("ID"));
	strSavePassword = CIOSWUtilities::LoadConfigString(_T("LOGIN"), _T("PASSWORD"));

	if (strID == strSaveID)	{
		if (strPassword == strSavePassword) {
			bResult = TRUE;
		}
		else
		{
			MessageBox(_T("Login Password를 확인하세요!"), _T("F-15K MTD I/O SW"), MB_ICONINFORMATION);
			GetDlgItem(IDC_EDIT_PASSWORD)->SetFocus();
		}
	}
	else
	{
		MessageBox(_T("Login ID를 확인하세요!"), _T("F-15K MTD I/O SW"), MB_ICONINFORMATION);
		GetDlgItem(IDC_EDIT_ID)->SetFocus();
	}

	return bResult;
}

void CIOSWLoginDlg::OnStnClickedStaticOk()
{
	BOOL bLogIn = FALSE;

	UpdateData(TRUE);

	bLogIn = CheckLogin(m_strID, m_strPassword);

	if (bLogIn == TRUE) {
		// 선택 모드 설정
		CDialog::OnOK();
	}
}

void CIOSWLoginDlg::OnIOSWModeRadioCtrl(UINT ID)
{
	UpdateData(TRUE);
	TRACE(_T("mode = %d \n"), m_nIOSWMode);
}

void CIOSWLoginDlg::OnBnClickedOk()
{

}

void CIOSWLoginDlg::OnStnClickedStaticCancel()
{
	CDialog::OnCancel();
}
