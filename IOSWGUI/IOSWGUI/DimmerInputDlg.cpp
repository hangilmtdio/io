// DimmerInputDlg.cpp : implementation file
//

#include "stdafx.h"
#include "IOSWGUI.h"
#include "DimmerInputDlg.h"
#include "afxdialogex.h"


// CDimmerInputDlg dialog

IMPLEMENT_DYNAMIC(CDimmerInputDlg, CDialogEx)

CDimmerInputDlg::CDimmerInputDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_DIMMERINPUT, pParent)
	, m_nDimmerValue(0)
	, m_nDimmerTrackValue(0)
{
	m_ptPosition.x = 550;
	m_pDataMgr = NULL;
	m_pIOInfo = NULL;
	m_nBoardID = 0;
}

CDimmerInputDlg::~CDimmerInputDlg()
{
}

void CDimmerInputDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_DIMMERVALUE, m_nDimmerValue);
	DDX_Slider(pDX, IDC_SLIDER_DIMMER, m_nDimmerTrackValue);
	DDX_Control(pDX, IDC_SLIDER_DIMMER, m_ctrlDimmerSlider);
}


BEGIN_MESSAGE_MAP(CDimmerInputDlg, CDialogEx)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_WM_HSCROLL()
END_MESSAGE_MAP()


// CDimmerInputDlg message handlers

void CDimmerInputDlg::SetIOInformation(sIOInformation* pInfo)
{
	m_pIOInfo		= pInfo;
	m_nDimmerValue	= pInfo->usValue;
}

BOOL CDimmerInputDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_bmpBackgound.LoadBitmap(IDB_BITMAP_DIMMERINPUT);
	m_hEditBrush = CreateSolidBrush(RGB(55, 59, 72));

	BITMAP BmpInfo;
	CWnd* pParent = GetParent();
	CRect rect;

	m_bmpBackgound.GetBitmap(&BmpInfo);

	pParent->GetWindowRect(&rect);

	this->MoveWindow(rect.left + m_ptPosition.x, rect.top + m_ptPosition.y, (int)BmpInfo.bmWidth, (int)BmpInfo.bmHeight);

	CWnd* pWnd = GetDlgItem(IDC_EDIT_DIMMERVALUE);
	pWnd->MoveWindow(15 , 3, 60, 26);

	pWnd = GetDlgItem(IDC_SLIDER_DIMMER);
	pWnd->MoveWindow(1, 32, 88, 17);

	if (m_pIOInfo != NULL)
	{
		m_ctrlDimmerSlider.SetRange(m_pIOInfo->nMin, m_pIOInfo->nMax);
		m_ctrlDimmerSlider.SetRangeMin(m_pIOInfo->nMin);
		m_ctrlDimmerSlider.SetRangeMax(m_pIOInfo->nMax);
		m_ctrlDimmerSlider.SetPos(m_nDimmerValue);
		m_ctrlDimmerSlider.SetTicFreq(100);
		m_ctrlDimmerSlider.SetLineSize(1);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


BOOL CDimmerInputDlg::DestroyWindow()
{
	// Delete oject for bitmap
	m_bmpBackgound.DeleteObject();

	DeleteObject(m_hEditBrush);

	return CDialogEx::DestroyWindow();
}


BOOL CDimmerInputDlg::OnEraseBkgnd(CDC* pDC)
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


HBRUSH CDimmerInputDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	switch (nCtlColor)
	{
		case CTLCOLOR_EDIT:
		{
			pDC->SetTextColor(RGB(224, 224, 224));
			pDC->SetBkMode(TRANSPARENT);
			return m_hEditBrush;


		}
	}
	return hbr;
}


void CDimmerInputDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if (pScrollBar)
	{
		if (pScrollBar == (CScrollBar*)&m_ctrlDimmerSlider)
		{
			int nPos = m_ctrlDimmerSlider.GetPos();
			m_nDimmerValue = nPos;
			m_nDimmerTrackValue = nPos;
			
			UpdateData(FALSE);

			if (m_pDataMgr != NULL && m_pIOInfo != NULL)
			{
				m_pDataMgr->SetMaintenaceDimmingData(m_nBoardID, m_pIOInfo->nChannel, (unsigned short)m_nDimmerValue);
			}
		}
	}
	else
	{
		
	}
	
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CDimmerInputDlg::OnOK()
{
	UpdateData(TRUE);

	if (m_pDataMgr != NULL && m_pIOInfo != NULL)
	{
		if ((m_nDimmerValue >= m_pIOInfo->nMin) && (m_nDimmerValue <= m_pIOInfo->nMax)) 
		{
			
			m_pDataMgr->SetMaintenaceDimmingData(m_nBoardID, m_pIOInfo->nChannel, (unsigned short)m_nDimmerValue);
			CDialogEx::OnOK();
		}
		else
		{
			CString strTemp;
			strTemp.Format(_T("입력값 min = %d, max = %d 를 확인하세요."), m_pIOInfo->nMin, m_pIOInfo->nMax);
			MessageBox(strTemp, _T("F-15K MTD I/O SW"), MB_ICONINFORMATION);
			GetDlgItem(IDC_EDIT_DIMMERVALUE)->SetFocus();
		}
	}	
}


void CDimmerInputDlg::OnCancel()
{
	// TODO: Add your specialized code here and/or call the base class

	CDialogEx::OnCancel();
}
