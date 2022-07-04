// AOInputDlg.cpp : implementation file
//

#include "stdafx.h"
#include "IOSWGUI.h"
#include "AOInputDlg.h"
#include "afxdialogex.h"
#include "resource.h"
#include "IOSWUtilities.h"

// CAOInputDlg dialog

IMPLEMENT_DYNAMIC(CAOInputDlg, CDialogEx)

CAOInputDlg::CAOInputDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_AOINPUT, pParent)
	, m_nAOValue(0)
{
	m_ptPosition.x = 550;
	m_pDataMgr = NULL;
	m_pIOInfo = NULL;
	m_nBoardID = 0;
	m_nDeviceID = 0;
}

CAOInputDlg::~CAOInputDlg()
{
}

void CAOInputDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_AOVALUE, m_nAOValue);
}


BEGIN_MESSAGE_MAP(CAOInputDlg, CDialogEx)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CAOInputDlg message handlers

void CAOInputDlg::SetIOInformation(sIOInformation* pInfo)
{
	m_pIOInfo = pInfo;
	m_nAOValue = pInfo->usValue;
}

BOOL CAOInputDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_bmpBackgound.LoadBitmap(IDB_BITMAP_AOINPUT);
	m_hEditBrush = CreateSolidBrush(RGB(55, 59, 72));

	BITMAP BmpInfo;
	CWnd* pParent = GetParent();
	CRect rect;

	m_bmpBackgound.GetBitmap(&BmpInfo);

	pParent->GetWindowRect(&rect);
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_AOVALUE);

	this->MoveWindow(rect.left + m_ptPosition.x, rect.top + m_ptPosition.y, (int)BmpInfo.bmWidth, (int)BmpInfo.bmHeight);
	pEdit->MoveWindow(2, 2, (int)BmpInfo.bmWidth - 4, (int)BmpInfo.bmHeight - 4);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


BOOL CAOInputDlg::DestroyWindow()
{
	// Delete oject for bitmap
	m_bmpBackgound.DeleteObject();

	DeleteObject(m_hEditBrush);

	return CDialogEx::DestroyWindow();
}


BOOL CAOInputDlg::OnEraseBkgnd(CDC* pDC)
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


HBRUSH CAOInputDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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


void CAOInputDlg::OnOK()
{
	UpdateData(TRUE);

	if (m_pDataMgr != NULL && m_pIOInfo != NULL)
	{
		if ((m_nAOValue >= m_pIOInfo->nMin) && (m_nAOValue <= m_pIOInfo->nMax))
		{
			if (m_pIOInfo->eKind == IK_AO)
			{
				if(m_nDeviceID == 67 || m_nDeviceID == 68)
					m_pDataMgr->SetMaintenaceCautionLightPanel(m_nBoardID, m_nDeviceID, m_pIOInfo->nChannel, (unsigned short)m_nAOValue);
				else
					m_pDataMgr->SetMaintenaceAnalogOutputData(m_nBoardID, m_pIOInfo->nChannel, (unsigned short)m_nAOValue);

			}
			else if (m_pIOInfo->eKind == IK_AO_IDC)
				m_pDataMgr->SetMaintenaceIndicatorData(m_nBoardID, m_pIOInfo->nChannel, (unsigned short)m_nAOValue);

			// LCD 스크린 정보 설정 파일에 저장한다. 
			if (m_nBoardID >= 41 && m_nBoardID <= 49)
			{
				CString strTemp;
				strTemp.Format(_T("IOBOARD_%d"), 24 + (m_nBoardID - 40));

				switch (m_pIOInfo->nChannel)
				{
				case 1:	// Brightness
					CIOSWUtilities::SaveIOConfigNumber(strTemp, _T("DISPLAY_BRIGHTNESS"), m_nAOValue);
					break;
				case 2: // Degree
					CIOSWUtilities::SaveIOConfigNumber(strTemp, _T("DISPLAY_DEGREE"), m_nAOValue);
					break;
				case 3: // X Location
					CIOSWUtilities::SaveIOConfigNumber(strTemp, _T("DISPLAY_X"), m_nAOValue);
					break;
				case 4: // Y Location
					CIOSWUtilities::SaveIOConfigNumber(strTemp, _T("DISPLAY_Y"), m_nAOValue);
					break;
				case 5: // Horizontal
					CIOSWUtilities::SaveIOConfigNumber(strTemp, _T("DISPLAY_WIDTH"), m_nAOValue);
					break;
				case 6: // Vertical
					CIOSWUtilities::SaveIOConfigNumber(strTemp, _T("DISPLAY_HEIGHT"), m_nAOValue);
					break;
				default:
					break;
				}
			}

			CDialogEx::OnOK();
		}
		else
		{
			CString strTemp;
			strTemp.Format(_T("입력값 min = %d, max = %d 를 확인하세요."), m_pIOInfo->nMin, m_pIOInfo->nMax);
			MessageBox(strTemp, _T("F-15K MTD I/O SW"), MB_ICONINFORMATION);
			GetDlgItem(IDC_EDIT_AOVALUE)->SetFocus();
		}

	}

}


void CAOInputDlg::OnCancel()
{
	// TODO: Add your specialized code here and/or call the base class

	CDialogEx::OnCancel();
}
