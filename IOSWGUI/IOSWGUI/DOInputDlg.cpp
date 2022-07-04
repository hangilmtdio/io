// DOInputDlg.cpp : implementation file
//

#include "stdafx.h"
#include "IOSWGUI.h"
#include "DOInputDlg.h"
#include "resource.h"
#include "afxdialogex.h"


// CDOInputDlg dialog

IMPLEMENT_DYNAMIC(CDOInputDlg, CDialogEx)

CDOInputDlg::CDOInputDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_DOINPUT, pParent)
	, m_nOnOFF(0)
{
	m_ptPosition.x = 550;
	m_pDataMgr = NULL;
	m_pIOInfo = NULL;
	m_nBoardID = 0;
}

CDOInputDlg::~CDOInputDlg()
{
}

void CDOInputDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_ONOFF1, m_nOnOFF);
}


BEGIN_MESSAGE_MAP(CDOInputDlg, CDialogEx)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_ONOFF1, IDC_ONOFF2, OnOffRadioCtrl)
	ON_WM_ERASEBKGND()
	ON_WM_DESTROY()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CDOInputDlg message handlers

void CDOInputDlg::SetIOInformation(sIOInformation* pInfo)
{
	m_pIOInfo = pInfo;
	m_nOnOFF = (int) pInfo->szValue;
}

void CDOInputDlg::OnOffRadioCtrl(UINT ID)
{
	UpdateData(TRUE);
	
	if (m_pDataMgr != NULL && m_pIOInfo != NULL)
	{
		m_pDataMgr->SetMaintenaceDigialOutputData(m_nBoardID, m_pIOInfo->nChannel, m_nOnOFF);
	}

	CDOInputDlg::OnOK();
}


BOOL CDOInputDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_bmpBackgound.LoadBitmap(IDB_BITMAP_DOINPUT);
	m_hRadioBrush = CreateSolidBrush(RGB(55, 59, 72));

	BITMAP BmpInfo;
	CWnd* pParent = GetParent();
	CRect rect;

	m_bmpBackgound.GetBitmap(&BmpInfo);

	pParent->GetWindowRect(&rect);

	this->MoveWindow(rect.left+ m_ptPosition.x, rect.top + m_ptPosition.y, (int)BmpInfo.bmWidth, (int)BmpInfo.bmHeight);
	
	CWnd* pWnd = GetDlgItem(IDC_ONOFF1);
	pWnd->MoveWindow(20, 7, 15, 15);

	pWnd = GetDlgItem(IDC_ONOFF2);
	pWnd->MoveWindow(20, 30, 15, 15);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


BOOL CDOInputDlg::OnEraseBkgnd(CDC* pDC)
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
		return CDialogEx::OnEraseBkgnd(pDC);

}


void CDOInputDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// Delete oject for bitmap
	m_bmpBackgound.DeleteObject();

	DeleteObject(m_hRadioBrush);
}


HBRUSH CDOInputDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	switch (nCtlColor)
	{
		case CTLCOLOR_STATIC:
		{
			pDC->SetTextColor(RGB(255, 255, 255));
			pDC->SetBkMode(TRANSPARENT);
			return m_hRadioBrush;

		}
	}
	return hbr;
}


void CDOInputDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class

	CDialogEx::OnOK();
}


void CDOInputDlg::OnCancel()
{
	// TODO: Add your specialized code here and/or call the base class

	CDialogEx::OnCancel();
}
