// FunctionRudder.cpp : implementation file
//

#include "stdafx.h"
#include "IOSWGUI.h"
#include "FunctionRudder.h"
#include "afxdialogex.h"
#include "IOSWUtilities.h"


// CFunctionRudder dialog

IMPLEMENT_DYNAMIC(CFunctionRudder, CDialogEx)

CFunctionRudder::CFunctionRudder(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_RUDDER_FUNCTION, pParent)
{
	m_pInitObject = NULL;
	m_pLeftTrimObject = NULL;
	m_pRightTrimObject = NULL;
	m_eTrimCommand = TC_NONE;
}

CFunctionRudder::~CFunctionRudder()
{
	if (m_pInitObject != NULL) {
		delete m_pInitObject;
		m_pInitObject = NULL;
	}

	if (m_pLeftTrimObject != NULL) {
		delete m_pLeftTrimObject;
		m_pLeftTrimObject = NULL;
	}

	if (m_pRightTrimObject != NULL) {
		delete m_pRightTrimObject;
		m_pRightTrimObject = NULL;
	}
}

void CFunctionRudder::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CFunctionRudder, CDialogEx)
	ON_BN_CLICKED(IDOK, &CFunctionRudder::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CFunctionRudder::OnBnClickedCancel)
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CFunctionRudder message handlers


void CFunctionRudder::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}


void CFunctionRudder::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}


BOOL CFunctionRudder::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_bmpBackgound.LoadBitmap(IDB_BITMAP_RUDDER);

	BITMAP BmpInfo;
	CWnd* pParent = GetParent();
	CRect rect;

	pParent->GetWindowRect(&rect);
	m_bmpBackgound.GetBitmap(&BmpInfo);

	this->MoveWindow(rect.left + 475, rect.top + 115, (int)BmpInfo.bmWidth, (int)BmpInfo.bmHeight);

	m_pInitObject = new CImageObject();

	if (m_pInitObject) {
		m_pInitObject->SetXPosition(5);
		m_pInitObject->SetYPosition(5);
		m_pInitObject->RegisterImage(0, CIOSWUtilities::GetImagePathFile(_T("InitTrim_btn_Default.bmp")));
		m_pInitObject->RegisterImage(1, CIOSWUtilities::GetImagePathFile(_T("InitTrim_btn_Over.bmp")));
	}

	m_pLeftTrimObject = new CImageObject();

	if (m_pLeftTrimObject) {
		m_pLeftTrimObject->SetXPosition(5);
		m_pLeftTrimObject->SetYPosition(45);
		m_pLeftTrimObject->RegisterImage(0, CIOSWUtilities::GetImagePathFile(_T("LeftTrim_btn_Default.bmp")));
		m_pLeftTrimObject->RegisterImage(1, CIOSWUtilities::GetImagePathFile(_T("LeftTrim_btn_Over.bmp")));
	}

	m_pRightTrimObject = new CImageObject();

	if (m_pRightTrimObject) {
		m_pRightTrimObject->SetXPosition(5);
		m_pRightTrimObject->SetYPosition(85);
		m_pRightTrimObject->RegisterImage(0, CIOSWUtilities::GetImagePathFile(_T("RightTrim_btn_Default.bmp")));
		m_pRightTrimObject->RegisterImage(1, CIOSWUtilities::GetImagePathFile(_T("RightTrim_btn_Over.bmp")));
	}

	SetTimer(400, 200, NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


BOOL CFunctionRudder::OnEraseBkgnd(CDC* pDC)
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

//	return CDialogEx::OnEraseBkgnd(pDC);
}


void CFunctionRudder::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (m_pInitObject != NULL) {
		if (m_pInitObject->GetOver())
		{
			//GetParent()->PostMessage(UM_FUNCTION_RUDDER, 0);
			m_eTrimCommand = TC_INIT;
		}
	}

	if (m_pLeftTrimObject != NULL) {
		if (m_pLeftTrimObject->GetOver())
		{
			//GetParent()->PostMessage(UM_FUNCTION_RUDDER, 1);
			m_eTrimCommand = TC_LEFT;
		}
	}

	if (m_pRightTrimObject != NULL) {
		if (m_pRightTrimObject->GetOver())
		{
			//GetParent()->PostMessage(UM_FUNCTION_RUDDER, 2);
			m_eTrimCommand = TC_RIGHT;
		}
	}

	CDialogEx::OnOK();

//	CDialogEx::OnLButtonDown(nFlags, point);
}


void CFunctionRudder::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_pInitObject != NULL) {

		BOOL bOver = m_pInitObject->IsPtInRect(point);

		m_pInitObject->SetOver(bOver);
	}

	if (m_pLeftTrimObject != NULL) {

		BOOL bOver = m_pLeftTrimObject->IsPtInRect(point);

		m_pLeftTrimObject->SetOver(bOver);
	}

	if (m_pRightTrimObject != NULL) {

		BOOL bOver = m_pRightTrimObject->IsPtInRect(point);

		m_pRightTrimObject->SetOver(bOver);
	}

	CDialogEx::OnMouseMove(nFlags, point);
}


void CFunctionRudder::OnTimer(UINT_PTR nIDEvent)
{
	CDC* pDC = GetDC();

	if (pDC->GetSafeHdc()) {

		if (m_pInitObject != NULL) {
			BOOL bOver = m_pInitObject->GetOver();
			m_pInitObject->DrawObject(pDC, (int)bOver);// , RGB(255, 0, 255));
		}

		if (m_pLeftTrimObject != NULL) {
			BOOL bOver = m_pLeftTrimObject->GetOver();
			m_pLeftTrimObject->DrawObject(pDC, (int)bOver);// , RGB(255, 0, 255));
		}

		if (m_pRightTrimObject != NULL) {
			BOOL bOver = m_pRightTrimObject->GetOver();
			m_pRightTrimObject->DrawObject(pDC, (int)bOver);// , RGB(255, 0, 255));
		}
	}


	CDialogEx::OnTimer(nIDEvent);
}
