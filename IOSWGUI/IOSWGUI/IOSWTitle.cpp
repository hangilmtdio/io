#include "stdafx.h"
#include "IOSWGUI.h"
#include "IOSWTitle.h"
#include "IOSWUtilities.h"
#include "IOSW_Interface.h"

CIOSWTitle::CIOSWTitle()
{
	m_pBGImage = NULL;
	m_pExitBtn = NULL;
	m_pMode = NULL;
	m_pCurrTime = NULL;
}


CIOSWTitle::~CIOSWTitle()
{
	EndThread();

	if (m_pBGImage != NULL) {
		delete m_pBGImage;
		m_pBGImage = NULL;
	}

	if (m_pExitBtn != NULL) {
		delete m_pExitBtn;
		m_pExitBtn = NULL;
	}

	if (m_pMode != NULL) {
		delete m_pMode;
		m_pMode = NULL;
	}

	if (m_pCurrTime != NULL) {
		delete m_pCurrTime;
		m_pCurrTime = NULL;
	}
}

void CIOSWTitle::LoadResource()
{

	m_pBGImage = new CImageObject();

	if (m_pBGImage){
		m_pBGImage->RegisterImage(0, CIOSWUtilities::GetImagePathFile(_T("Title.bmp")));
	}

	m_pExitBtn = new CImageObject();

	if (m_pExitBtn) {
		m_pExitBtn->SetXPosition(1545);
		m_pExitBtn->SetYPosition(15);
		m_pExitBtn->RegisterImage(0, CIOSWUtilities::GetImagePathFile(_T("Title_exit.bmp")));
		m_pExitBtn->RegisterImage(1, CIOSWUtilities::GetImagePathFile(_T("Title_exit_over.bmp")));
	}

	m_pMode = new CImageObject();

	if (m_pMode) {
		m_pMode->SetXPosition(1140);
		m_pMode->SetYPosition(15);
		m_pMode->RegisterImage(0, CIOSWUtilities::GetImagePathFile(_T("Mode_bg.bmp")));
	}

	m_pCurrTime = new CImageObject();

	if (m_pCurrTime) {
		m_pCurrTime->SetXPosition(1340);
		m_pCurrTime->SetYPosition(15);
		m_pCurrTime->RegisterImage(0, CIOSWUtilities::GetImagePathFile(_T("Title_Time.bmp")));
	}

}


BEGIN_MESSAGE_MAP(CIOSWTitle, CIOSWWnd)
ON_WM_PAINT()
ON_WM_TIMER()
ON_WM_CREATE()
ON_WM_MOUSEMOVE()
//ON_WM_MBUTTONDOWN()
ON_WM_LBUTTONDOWN()
ON_WM_CLOSE()
ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()


void CIOSWTitle::OnPaint()
{
	CPaintDC dc(this);

	if (m_pBGImage != NULL) {
		m_pBGImage->DrawObject(&dc);
	}
	
}


void CIOSWTitle::OnTimer(UINT_PTR nIDEvent)
{
	CDC *pDC = GetDC();

	CTime cTime = CTime::GetCurrentTime();

	CString strTime;
	strTime.Format(_T("%04d.%02d.%02d  %02d:%02d:%02d"), cTime.GetYear(), cTime.GetMonth(), cTime.GetDay(), cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond());

	if (pDC->GetSafeHdc() != NULL) {
		RedrawWindow();
		pDC->SetBkMode(TRANSPARENT);
		pDC->DrawText(strTime, CRect(1670, 20, 1900, 50), DT_CENTER);
		pDC->SetBkMode(OPAQUE);
	}

	CIOSWWnd::OnTimer(nIDEvent);
}


int CIOSWTitle::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CIOSWWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_fontTime.CreateFont(18, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH, _T("나눔고딕"));

	StartThread();
	

	return 0;
}


void CIOSWTitle::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (m_pExitBtn != NULL) {

		BOOL bOver = m_pExitBtn->IsPtInRect(point);

		m_pExitBtn->SetOver(bOver);
	}

	if (m_pMode != NULL) {

		BOOL bOver = m_pMode->IsPtInRect(point);

		m_pMode->SetOver(bOver);
	}

	CIOSWWnd::OnMouseMove(nFlags, point);
}


void CIOSWTitle::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (m_pExitBtn != NULL) {
		if (m_pExitBtn->GetOver())
		{
			if (MessageBox(_T("입출력 소프트웨어를 종료하시겠습니까?"), _T("F-15K MTD I/O SW"), MB_ICONQUESTION | MB_YESNO | MB_DEFBUTTON2) == IDYES)
			{
				theApp.GetMainDlg()->StopIOMonitoring();
				theApp.GetMainDlg()->PostMessage(WM_CLOSE);
			}

		}
	}

	CIOSWWnd::OnLButtonDown(nFlags, point);
}


void CIOSWTitle::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	if (m_pMode != NULL) {
		if (m_pMode->GetOver())
		{
			IOSW_MODE eMode = theApp.GetMainDlg()->GetIOSWMode();
			IOSW_MODE eNewMode;
			
			if (eMode == IM_MONITORING)
				eNewMode = IM_MAINTENANCE;
			else
				eNewMode = IM_MONITORING;

			CString strTemp;
			strTemp.Format(_T("입출력 소프트웨어 모드를 %s로 변경하시겠습니까?"), alpszIOSWMODEType[eNewMode]);

			if (MessageBox(strTemp, _T("F-15K MTD I/O SW"), MB_ICONQUESTION | MB_YESNO | MB_DEFBUTTON2) == IDYES)
			{
				theApp.GetMainDlg()->SetIOSWMode(eNewMode);
			}
			
		}
	}

	CIOSWWnd::OnLButtonDblClk(nFlags, point);
}

void CIOSWTitle::UpdateRender()
{
	CDC* pDC = GetDC();

	if (pDC->GetSafeHdc()) {

		if (m_pExitBtn != NULL)	{
			BOOL bOver = m_pExitBtn->GetOver();
			m_pExitBtn->DrawObject(pDC, (int)bOver);// , RGB(255, 0, 255));
			
		}
		
		if (m_pCurrTime != NULL) {
	
				CTime cTime = CTime::GetCurrentTime();
				CString strTime;
				strTime.Format(_T("%04d.%02d.%02d  %02d:%02d:%02d"), cTime.GetYear(), cTime.GetMonth(), cTime.GetDay(), cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond());

				m_pCurrTime->DrawObject(pDC, strTime, &m_fontTime, RGB(255, 255, 0));
		}
		
		if (m_pMode != NULL) {
			CString strMode;
			strMode.Format(_T("%s Mode"), alpszIOSWMODEType[theApp.GetMainDlg()->GetIOSWMode()]);
			m_pMode->DrawObject(pDC, strMode, &m_fontTime, RGB(255, 255, 0));
		}
	}

	ReleaseDC(pDC);
}

DWORD CIOSWTitle::ThreadProc()
{
	DWORD nOld = GetTickCount();

	while (1)
	{
		DWORD nNew = GetTickCount();

		if (nNew - nOld >= 200){
		
			UpdateRender();

			nOld = GetTickCount();
		}

		Sleep(1);

		if (m_bEndThread == TRUE) break;   // Thread 종료 조건
	}

	return 1;
}


void CIOSWTitle::OnClose()
{
	m_fontTime.DeleteObject();

	CIOSWWnd::OnClose();
}


