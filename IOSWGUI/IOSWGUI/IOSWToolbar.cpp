#include "stdafx.h"
#include "IOSWGUI.h"
#include "IOSWToolbar.h"
#include "CommonDefine.h"
#include "IOSWUtilities.h"


CIOSWToolbar::CIOSWToolbar()
{
	m_pBGImage = NULL;
	m_pLeftBtnImage = NULL;
	m_pMainBtnImage = NULL;
	m_pRightBtnImage = NULL;
	m_pDIBtnImage	= NULL;
	m_pDOBtnImage	= NULL;
	m_pAIBtnImage	= NULL;
	m_pAOBtnImage	= NULL;
	m_pDIMMERBtnImage = NULL;

	m_nCockpitType = DP_LEFT;
	m_nIOType = IK_DI;
}


CIOSWToolbar::~CIOSWToolbar()
{
	if (m_pBGImage != NULL) {
		delete m_pBGImage;
		m_pBGImage = NULL;
	}

	if (m_pLeftBtnImage != NULL) {
		delete m_pLeftBtnImage;
		m_pLeftBtnImage = NULL;
	}

	if (m_pMainBtnImage != NULL) {
		delete m_pMainBtnImage;
		m_pMainBtnImage = NULL;
	}

	if (m_pRightBtnImage != NULL) {
		delete m_pRightBtnImage;
		m_pRightBtnImage = NULL;
	}

	if (m_pDOBtnImage != NULL) {
		delete m_pDOBtnImage;
		m_pDOBtnImage = NULL;
	}

	if (m_pDIBtnImage != NULL) {
		delete m_pDIBtnImage;
		m_pDIBtnImage = NULL;
	}

	if (m_pAIBtnImage != NULL) {
		delete m_pAIBtnImage;
		m_pAIBtnImage = NULL;
	}

	if (m_pAOBtnImage != NULL) {
		delete m_pAOBtnImage;
		m_pAOBtnImage = NULL;
	}

	if (m_pDIMMERBtnImage != NULL) {
		delete m_pDIMMERBtnImage;
		m_pDIMMERBtnImage = NULL;
	}

}
BEGIN_MESSAGE_MAP(CIOSWToolbar, CIOSWWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


void CIOSWToolbar::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: Add your message handler code here
					   // Do not call CIOSWWnd::OnPaint() for painting messages
	if (m_pBGImage != NULL) {
		m_pBGImage->DrawObject(&dc);
	}

	if (m_pLeftBtnImage != NULL) {
		if(m_nCockpitType == DP_LEFT)
			m_pLeftBtnImage->DrawObject(&dc, 1);
		else
			m_pLeftBtnImage->DrawObject(&dc, 0);
	}

	if (m_pMainBtnImage != NULL) {
		if(m_nCockpitType == DP_MAIN)
			m_pMainBtnImage->DrawObject(&dc, 1);
		else
			m_pMainBtnImage->DrawObject(&dc, 0);
	}

	if (m_pRightBtnImage != NULL) {
		if(m_nCockpitType == DP_RIGHT)
			m_pRightBtnImage->DrawObject(&dc, 1);
		else
			m_pRightBtnImage->DrawObject(&dc, 0);
	}

	//
	if (m_pDIBtnImage != NULL) {
		if (m_nIOType == IK_DI)
			m_pDIBtnImage->DrawObject(&dc, 1);
		else
			m_pDIBtnImage->DrawObject(&dc, 0);
	}	
	
	if (m_pDOBtnImage != NULL) {
		if (m_nIOType == IK_DO)
			m_pDOBtnImage->DrawObject(&dc, 1);
		else
			m_pDOBtnImage->DrawObject(&dc, 0);
	}	
	
	if (m_pAIBtnImage != NULL) {
		if (m_nIOType == IK_AI)
			m_pAIBtnImage->DrawObject(&dc, 1);
		else
			m_pAIBtnImage->DrawObject(&dc, 0);
	}	
	
	if (m_pAOBtnImage != NULL) {
		if (m_nIOType == IK_AO)
			m_pAOBtnImage->DrawObject(&dc, 1);
		else
			m_pAOBtnImage->DrawObject(&dc, 0);
	}

	if (m_pDIMMERBtnImage != NULL) {
		if (m_nIOType == IK_DIMMER)
			m_pDIMMERBtnImage->DrawObject(&dc, 1);
		else
			m_pDIMMERBtnImage->DrawObject(&dc, 0);
	}
}


int CIOSWToolbar::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CIOSWWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here

	return 0;
}

void CIOSWToolbar::LoadResource()
{

	m_pBGImage = new CImageObject();

	if (m_pBGImage) {
		m_pBGImage->RegisterImage(0, CIOSWUtilities::GetImagePathFile(_T("toolbar_bg.bmp")));
	}

	m_pLeftBtnImage = new CImageObject();

	if (m_pLeftBtnImage) {
		m_pLeftBtnImage->SetXPosition(21);
		m_pLeftBtnImage->SetYPosition(5);

		m_pLeftBtnImage->RegisterImage(0, CIOSWUtilities::GetImagePathFile(_T("Left_btn_off.bmp")));
		m_pLeftBtnImage->RegisterImage(1, CIOSWUtilities::GetImagePathFile(_T("Left_btn.bmp")));
	}

	m_pMainBtnImage = new CImageObject();

	if (m_pMainBtnImage) {
		m_pMainBtnImage->SetXPosition(148);
		m_pMainBtnImage->SetYPosition(5);
		m_pMainBtnImage->RegisterImage(0, CIOSWUtilities::GetImagePathFile(_T("Main_btn_off.bmp")));
		m_pMainBtnImage->RegisterImage(1, CIOSWUtilities::GetImagePathFile(_T("Main_btn.bmp")));
	}

	m_pRightBtnImage = new CImageObject();

	if (m_pRightBtnImage) {
		m_pRightBtnImage->SetXPosition(276);
		m_pRightBtnImage->SetYPosition(5);
		m_pRightBtnImage->RegisterImage(0, CIOSWUtilities::GetImagePathFile(_T("Right_btn_off.bmp")));
		m_pRightBtnImage->RegisterImage(1, CIOSWUtilities::GetImagePathFile(_T("Right_btn.bmp")));
	}

	m_pDIBtnImage = new CImageObject();

	if (m_pDIBtnImage) {
		m_pDIBtnImage->SetXPosition(919);
		m_pDIBtnImage->SetYPosition(12);
		m_pDIBtnImage->RegisterImage(0, CIOSWUtilities::GetImagePathFile(_T("DI_Normal.bmp")));
		m_pDIBtnImage->RegisterImage(1, CIOSWUtilities::GetImagePathFile(_T("DI_Over.bmp")));
	}

	m_pDOBtnImage = new CImageObject();

	if (m_pDOBtnImage) {
		m_pDOBtnImage->SetXPosition(968);
		m_pDOBtnImage->SetYPosition(12);
		m_pDOBtnImage->RegisterImage(0, CIOSWUtilities::GetImagePathFile(_T("DO_Normal.bmp")));
		m_pDOBtnImage->RegisterImage(1, CIOSWUtilities::GetImagePathFile(_T("DO_Over.bmp")));
	}

	m_pAIBtnImage = new CImageObject();

	if (m_pAIBtnImage) {
		m_pAIBtnImage->SetXPosition(1017);
		m_pAIBtnImage->SetYPosition(12);
		m_pAIBtnImage->RegisterImage(0, CIOSWUtilities::GetImagePathFile(_T("AI_Normal.bmp")));
		m_pAIBtnImage->RegisterImage(1, CIOSWUtilities::GetImagePathFile(_T("AI_Over.bmp")));
	}

	m_pAOBtnImage = new CImageObject();

	if (m_pAOBtnImage) {
		m_pAOBtnImage->SetXPosition(1066);
		m_pAOBtnImage->SetYPosition(12);
		m_pAOBtnImage->RegisterImage(0, CIOSWUtilities::GetImagePathFile(_T("AO_Normal.bmp")));
		m_pAOBtnImage->RegisterImage(1, CIOSWUtilities::GetImagePathFile(_T("AO_Over.bmp")));
	}

	m_pDIMMERBtnImage = new CImageObject();

	if (m_pDIMMERBtnImage) {
		m_pDIMMERBtnImage->SetXPosition(1115);
		m_pDIMMERBtnImage->SetYPosition(12);
		m_pDIMMERBtnImage->RegisterImage(0, CIOSWUtilities::GetImagePathFile(_T("DIMMER_Normal.bmp")));
		m_pDIMMERBtnImage->RegisterImage(1, CIOSWUtilities::GetImagePathFile(_T("DIMMER_Over.bmp")));
	}
}

void CIOSWToolbar::OnLButtonDown(UINT nFlags, CPoint point)
{
	CRect rect;

	if (m_pLeftBtnImage != NULL) {
		if (m_pLeftBtnImage->IsPtInRect(point) && m_nCockpitType != DP_LEFT)
		{
			m_nCockpitType = DP_LEFT;
			theApp.GetMainDlg()->PostMessage(UM_UPDATE_COCKPIT_LIST, DP_LEFT);
		}
	}

	if (m_pMainBtnImage != NULL) {
		if (m_pMainBtnImage->IsPtInRect(point) && m_nCockpitType != DP_MAIN)
		{
			m_nCockpitType = DP_MAIN;
			theApp.GetMainDlg()->PostMessage(UM_UPDATE_COCKPIT_LIST, DP_MAIN);
		}
	}

	if (m_pRightBtnImage != NULL) {
		if (m_pRightBtnImage->IsPtInRect(point) && m_nCockpitType != DP_RIGHT)
		{
			m_nCockpitType = DP_RIGHT;
			theApp.GetMainDlg()->PostMessage(UM_UPDATE_COCKPIT_LIST, DP_RIGHT);
		}
	}

	if (m_pDIBtnImage != NULL) {
		if (m_pDIBtnImage->IsPtInRect(point) && m_nIOType != IK_DI)
		{
			m_nIOType = IK_DI;
			theApp.GetMainDlg()->PostMessage(UM_UPDATE_COCKPITIO_LIST, IK_DI);
		}
	}

	if (m_pDOBtnImage != NULL) {
		if (m_pDOBtnImage->IsPtInRect(point) && m_nIOType != IK_DO)
		{
			m_nIOType = IK_DO;
			theApp.GetMainDlg()->PostMessage(UM_UPDATE_COCKPITIO_LIST, IK_DO);
		}
	}

	if (m_pAIBtnImage != NULL) {
		if (m_pAIBtnImage->IsPtInRect(point) && m_nIOType != IK_AI)
		{
			m_nIOType = IK_AI;
			theApp.GetMainDlg()->PostMessage(UM_UPDATE_COCKPITIO_LIST, IK_AI);
		}
	}

	if (m_pAOBtnImage != NULL) {
		if (m_pAOBtnImage->IsPtInRect(point) && m_nIOType != IK_AO)
		{
			m_nIOType = IK_AO;
			theApp.GetMainDlg()->PostMessage(UM_UPDATE_COCKPITIO_LIST, IK_AO);
		}
	}

	if (m_pDIMMERBtnImage != NULL) {
		if (m_pDIMMERBtnImage->IsPtInRect(point) && m_nIOType != IK_DIMMER)
		{
			m_nIOType = IK_DIMMER;
			theApp.GetMainDlg()->PostMessage(UM_UPDATE_COCKPITIO_LIST, IK_DIMMER);
		}
	}

	RedrawWindow();

	CIOSWWnd::OnLButtonDown(nFlags, point);
}


void CIOSWToolbar::OnMouseMove(UINT nFlags, CPoint point)
{
	/*if (m_pLeftBtnImage != NULL) {

		BOOL bOver = m_pLeftBtnImage->IsPtInRect(point);

		m_pLeftBtnImage->SetOver(bOver);
	}

	if (m_pMainBtnImage != NULL) {

		BOOL bOver = m_pMainBtnImage->IsPtInRect(point);

		m_pMainBtnImage->SetOver(bOver);
	}

	if (m_pRightBtnImage != NULL) {

		BOOL bOver = m_pRightBtnImage->IsPtInRect(point);

		m_pRightBtnImage->SetOver(bOver);
	}
*/
	CIOSWWnd::OnMouseMove(nFlags, point);
}

/*
DWORD CIOSWToolbar::ThreadProc()
{
	DWORD nOld = GetTickCount();

	while (1)
	{
		DWORD nNew = GetTickCount();

		if (nNew - nOld >= 100) {

			UpdateRender();

			nOld = GetTickCount();
		}

		Sleep(1);

		if (m_bEndThread == TRUE) break;   // Thread 종료 조건
	}

	return 1;
}

void CIOSWToolbar::UpdateRender()
{
	CDC* pDC = GetDC();

	if (pDC->GetSafeHdc()) {

		if (m_pLeftBtnImage != NULL) {
			BOOL bOver = m_pLeftBtnImage->GetOver();
			m_pLeftBtnImage->DrawObject(pDC, (int)bOver);// , RGB(255, 0, 255));

		}

	}

	ReleaseDC(pDC);
}
*/

