#include "stdafx.h"
#include "IOSWSystemStatus.h"
#include "IOSWUtilities.h"
#include "IOSWGUI.h"
#include "CommonDefine.h"



CIOSWSystemStatus::CIOSWSystemStatus()
{
	m_pBGImage 	= NULL;
	m_pSetImage = NULL;

	m_pCPUImage = NULL;
	m_pMEMImage = NULL;
	m_pHDDImage = NULL;

	m_pHOSTImage = NULL;
	m_pIOSImage	 = NULL;
	m_pIOImage = NULL;

	//m_pPWROnImage = NULL;
	//m_pPWROffImage = NULL;
	//m_pThrottleImage = NULL;

	m_pDataManager = NULL;
	m_pDeviceInfoManager = NULL;
	m_pListLRUImage = NULL;

	m_fNormalValue = 0.0f;
	m_fErrorValue = 0.0f;
} 


CIOSWSystemStatus::~CIOSWSystemStatus()
{
	//EndThread();

	if (m_pBGImage != NULL) {
		delete m_pBGImage;
		m_pBGImage = NULL;
	}

	if (m_pSetImage != NULL) {
		delete m_pSetImage;
		m_pSetImage = NULL;
	}

	if (m_pCPUImage != NULL) {
		delete m_pCPUImage;
		m_pCPUImage = NULL;
	}

	if (m_pMEMImage != NULL) {
		delete m_pMEMImage;
		m_pMEMImage = NULL;
	}

	if (m_pHDDImage != NULL) {
		delete m_pHDDImage;
		m_pHDDImage = NULL;
	}

	if (m_pHOSTImage != NULL) {
		delete m_pHOSTImage;
		m_pHOSTImage = NULL;
	}

	if (m_pIOSImage != NULL) {
		delete m_pIOSImage;
		m_pIOSImage = NULL;
	}

	if (m_pIOImage != NULL) {
		delete m_pIOImage;
		m_pIOImage = NULL;
	}

	//if (m_pPWROnImage != NULL) {
	//	delete m_pPWROnImage;
	//	m_pPWROnImage = NULL;
	//}

	//if (m_pPWROffImage != NULL) {
	//	delete m_pPWROffImage;
	//	m_pPWROffImage = NULL;
	//}

	//if (m_pThrottleImage != NULL) {
	//	delete m_pThrottleImage;
	//	m_pThrottleImage = NULL;
	//}

	if (m_pListLRUImage != NULL) {
		ClearAllLRUImageList();

		delete m_pListLRUImage;
		m_pListLRUImage = NULL;
	}

}

void CIOSWSystemStatus::ClearAllLRUImageList()
{
	LRUIMAGE_LIST_ITR itr;

	for (itr = m_pListLRUImage->begin(); itr != m_pListLRUImage->end(); ++itr)
	{
		sLRUImageInfo* psInfo = *itr;

		delete psInfo;
		psInfo = NULL;
	}

	m_pListLRUImage->clear();
}

BEGIN_MESSAGE_MAP(CIOSWSystemStatus, CIOSWWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_CLOSE()
	ON_WM_ERASEBKGND()
	ON_WM_TIMER()
END_MESSAGE_MAP()


void CIOSWSystemStatus::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: Add your message handler code here
					   // Do not call __super::OnPaint() for painting messages
	
}


int CIOSWSystemStatus::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CIOSWWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_font.CreateFont(16, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH, _T("Arial"));

	// 설정 파일에서 System 상태 값 불러오기
	m_fNormalValue = (float)CIOSWUtilities::LoadConfigNumber(_T("SYSTEM_STATUS"), _T("NORMAL"));
	m_fErrorValue = (float)CIOSWUtilities::LoadConfigNumber(_T("SYSTEM_STATUS"), _T("ERROR"));

	//StartThread();
	SetTimer(300, 500, NULL);

	return 0;
}

void CIOSWSystemStatus::LoadResource(CIODeviceInformationManager* pMgr)
{
	m_pBGImage = new CImageObject();

	if (m_pBGImage) {
		m_pBGImage->SetXPosition(0);
		m_pBGImage->SetYPosition(0);
		m_pBGImage->RegisterImage(0, CIOSWUtilities::GetImagePathFile(_T("SystemStatus_bg.bmp")));
	}

	m_pSetImage = new CImageObject();

	if (m_pSetImage) {
		m_pSetImage->SetXPosition(345);
		m_pSetImage->SetYPosition(2);
		m_pSetImage->RegisterImage(0, CIOSWUtilities::GetImagePathFile(_T("Setting_normal.bmp")));
		m_pSetImage->RegisterImage(1, CIOSWUtilities::GetImagePathFile(_T("Setting_over.bmp")));
	}
	
	m_pCPUImage = new CImageObject();

	if (m_pCPUImage) {
		m_pCPUImage->SetXPosition(123);
		m_pCPUImage->SetYPosition(261);
		m_pCPUImage->RegisterImage(0, CIOSWUtilities::GetImagePathFile(_T("SystemStatus_Normal.bmp")));
		m_pCPUImage->RegisterImage(1, CIOSWUtilities::GetImagePathFile(_T("SystemStatus_Warnning.bmp")));
		m_pCPUImage->RegisterImage(2, CIOSWUtilities::GetImagePathFile(_T("SystemStatus_Error.bmp")));
	}

	m_pMEMImage = new CImageObject();

	if (m_pMEMImage) {
		m_pMEMImage->SetXPosition(171);
		m_pMEMImage->SetYPosition(261);
		m_pMEMImage->RegisterImage(0, CIOSWUtilities::GetImagePathFile(_T("SystemStatus_Normal.bmp")));
		m_pMEMImage->RegisterImage(1, CIOSWUtilities::GetImagePathFile(_T("SystemStatus_Warnning.bmp")));
		m_pMEMImage->RegisterImage(2, CIOSWUtilities::GetImagePathFile(_T("SystemStatus_Error.bmp")));
	}

	m_pHDDImage = new CImageObject();

	if (m_pHDDImage) {
		m_pHDDImage->SetXPosition(219);
		m_pHDDImage->SetYPosition(261);
		m_pHDDImage->RegisterImage(0, CIOSWUtilities::GetImagePathFile(_T("SystemStatus_Normal.bmp")));
		m_pHDDImage->RegisterImage(1, CIOSWUtilities::GetImagePathFile(_T("SystemStatus_Warnning.bmp")));
		m_pHDDImage->RegisterImage(2, CIOSWUtilities::GetImagePathFile(_T("SystemStatus_Error.bmp")));
	}

	m_pHOSTImage = new CImageObject();

	if (m_pHOSTImage) {
		m_pHOSTImage->SetXPosition(62);
		m_pHOSTImage->SetYPosition(136);
		m_pHOSTImage->RegisterImage(0, CIOSWUtilities::GetImagePathFile(_T("HOST_Disconnect.bmp")));
		m_pHOSTImage->RegisterImage(1, CIOSWUtilities::GetImagePathFile(_T("HOST_Connect.bmp")));
		m_pHOSTImage->RegisterImage(2, CIOSWUtilities::GetImagePathFile(_T("HOST_Error.bmp")));
	}

	m_pIOSImage = new CImageObject();
	
	if (m_pIOSImage) {
		m_pIOSImage->SetXPosition(265);
		m_pIOSImage->SetYPosition(136);
		m_pIOSImage->RegisterImage(0, CIOSWUtilities::GetImagePathFile(_T("IOS_Disconnect.bmp")));
		m_pIOSImage->RegisterImage(1, CIOSWUtilities::GetImagePathFile(_T("IOS_Connect.bmp")));
		m_pIOSImage->RegisterImage(2, CIOSWUtilities::GetImagePathFile(_T("IOS_Error.bmp")));
	}

	m_pIOImage = new CImageObject();

	if (m_pIOImage) {
		m_pIOImage->SetXPosition(188);
		m_pIOImage->SetYPosition(310);
		m_pIOImage->RegisterImage(0, CIOSWUtilities::GetImagePathFile(_T("IO_Disconnect.bmp")));
		m_pIOImage->RegisterImage(1, CIOSWUtilities::GetImagePathFile(_T("IO_Connect.bmp")));
		m_pIOImage->RegisterImage(2, CIOSWUtilities::GetImagePathFile(_T("IO_Error.bmp")));
	}

	m_pListLRUImage = new LRUIMAGE_LIST;

	if (pMgr != NULL) {

		LIST_ID IDList;
		LIST_ID_ITR itr;

		m_pDeviceInfoManager = pMgr;

		pMgr->GetDeviceIDList(&IDList);

		for (itr = IDList.begin(); itr != IDList.end(); ++itr) {
			int nDeviceID = *itr;

			CIODeviceInfo * pInfo = pMgr->GetDeivceInfo(nDeviceID);

			if (pInfo) {
				sLRUImageInfo* psInfo = new sLRUImageInfo();
				CString strTemp;

				psInfo->nDeviceID = nDeviceID;

				psInfo->pObject->SetXPosition(pInfo->GetDeviceImageXPosition());
				psInfo->pObject->SetYPosition(pInfo->GetDeviceImageYPosition());

				strTemp.Format(_T("%d_Disconnect.bmp"), nDeviceID);
				psInfo->pObject->RegisterImage(0, CIOSWUtilities::GetImagePathFile(strTemp));

				strTemp.Format(_T("%d_Connect.bmp"), nDeviceID);
				psInfo->pObject->RegisterImage(1, CIOSWUtilities::GetImagePathFile(strTemp));

				strTemp.Format(_T("%d_Error.bmp"), nDeviceID);
				psInfo->pObject->RegisterImage(2, CIOSWUtilities::GetImagePathFile(strTemp));

				m_pListLRUImage->push_back(psInfo);
			}
		}
	}

	//m_pPWROnImage = new CImageObject();

	//if (m_pPWROnImage) {
	//	m_pPWROnImage->SetXPosition(280);
	//	m_pPWROnImage->SetYPosition(380);
	//	m_pPWROnImage->RegisterImage(0, CIOSWUtilities::GetImagePathFile(_T("PWR_ON.bmp")));

	//}

	//m_pPWROffImage = new CImageObject();

	//if (m_pPWROffImage) {
	//	m_pPWROffImage->SetXPosition(330);
	//	m_pPWROffImage->SetYPosition(380);
	//	m_pPWROffImage->RegisterImage(0, CIOSWUtilities::GetImagePathFile(_T("PWR_OFF.bmp")));

	//}
	/*
	m_pThrottleImage = new CImageObject();

	if (m_pThrottleImage) {
		m_pThrottleImage->SetXPosition(96);
		m_pThrottleImage->SetYPosition(696);
		m_pThrottleImage->RegisterImage(0, CIOSWUtilities::GetImagePathFile(_T("Throttle_Disconnect.bmp")));
		m_pThrottleImage->RegisterImage(1, CIOSWUtilities::GetImagePathFile(_T("Throttle_Connect.bmp")));
		m_pThrottleImage->RegisterImage(2, CIOSWUtilities::GetImagePathFile(_T("Throttle_Error.bmp")));
	}*/
}

void CIOSWSystemStatus::UpdateCPUStatus(CDC* pDC, const SYSTEMSTATUSINFO& sInfo)
{
	if (m_pCPUImage != NULL)
	{
		int nStatus = 0;
		CString strValue;

		if (sInfo.fCPUUsageAmount < m_fNormalValue)
			nStatus = 0;
		else if (sInfo.fCPUUsageAmount > m_fErrorValue)
			nStatus = 2;
		else
			nStatus = 1;

		strValue.Format(_T("%.1f%%"), sInfo.fCPUUsageAmount);

		m_pCPUImage->DrawObject(pDC, strValue, &m_font, RGB(255, 255, 255), nStatus);

	}
}

void CIOSWSystemStatus::UpdateMemoryStatus(CDC* pDC, const SYSTEMSTATUSINFO& sInfo)
{
	if (m_pMEMImage != NULL)
	{
		int nStatus = 0;
		CString strValue;

		if (sInfo.fMemoryUsageAmount < m_fNormalValue)
			nStatus = 0;
		else if (sInfo.fMemoryUsageAmount > m_fErrorValue)
			nStatus = 2;
		else
			nStatus = 1;

		strValue.Format(_T("%.1f%%"), sInfo.fMemoryUsageAmount);

		m_pMEMImage->DrawObject(pDC, strValue, &m_font, RGB(255, 255, 255), nStatus);

	}
}

void CIOSWSystemStatus::UpdateHDDStatus(CDC* pDC, const SYSTEMSTATUSINFO& sInfo)
{
	if (m_pHDDImage != NULL)
	{
		int nStatus = 0;
		CString strValue;

		if (sInfo.fDiskUsageAmount < m_fNormalValue)
			nStatus = 0;
		else if (sInfo.fDiskUsageAmount > m_fErrorValue)
			nStatus = 2;
		else
			nStatus = 1;

		strValue.Format(_T("%.1f%%"), sInfo.fDiskUsageAmount);

		m_pHDDImage->DrawObject(pDC, strValue, &m_font, RGB(255, 255, 255), nStatus);

	}
}

void CIOSWSystemStatus::UpdateHOSTStatus(CDC* pDC, const NETWORKSTATUS_TYPE& eStatus)
{
	if (m_pHOSTImage != NULL) {
		m_pHOSTImage->DrawObject(pDC, eStatus-1);
	}
}

void CIOSWSystemStatus::UpdateIOSStatus(CDC* pDC, const NETWORKSTATUS_TYPE& eStatus)
{
	if (m_pIOSImage != NULL) {
		m_pIOSImage->DrawObject(pDC, eStatus-1);
	}
}

void CIOSWSystemStatus::UpdateIOStatus(CDC* pDC, const NETWORKSTATUS_TYPE& eStatus)
{
	if (m_pIOImage != NULL) {
		m_pIOImage->DrawObject(pDC, eStatus-1);
	}
}

//void CIOSWSystemStatus::UpdatePWRStatus(CDC* pDC, const IOSW_to_IOSWGUI& sData)
//{
//	if (m_pPWROnImage != NULL) {
//		m_pPWROnImage->DrawObject(pDC);
//	}
//
//	if (m_pPWROffImage != NULL) {
//		m_pPWROffImage->DrawObject(pDC);
//	}
//}

void CIOSWSystemStatus::UpdateLRUStatus(CDC* pDC, const IOSW_to_IOSWGUI& sData)
{
	if (m_pListLRUImage != NULL) {

		LRUIMAGE_LIST_ITR itr;

		for (itr = m_pListLRUImage->begin(); itr != m_pListLRUImage->end(); ++itr)
		{
			sLRUImageInfo* psInfo = *itr;

			if (psInfo != NULL && m_pDeviceInfoManager != NULL)
			{
				CIODeviceInfo* pInfo = m_pDeviceInfoManager->GetDeivceInfo(psInfo->nDeviceID);

				switch (sData.eIONetworkStatus[pInfo->GetBoardID()])
				{
				case NS_DISCONNECTED:
				case NS_ERROR:
					psInfo->pObject->DrawObject(pDC, 2);
					break;
				case NS_CONNECTED:
					psInfo->pObject->DrawObject(pDC, 0);
					break;
				default:
					break;
				}
				
			}
		}
	}
	/*if (m_pThrottleImage != NULL) {
		m_pThrottleImage->DrawObject(pDC, eStatus);
	}*/
}

void CIOSWSystemStatus::UpdateRender()
{
	CDC* pDC = GetDC();

	if (pDC->GetSafeHdc()) {

		if (m_pSetImage != NULL) {
			BOOL bOver = m_pSetImage->GetOver();
			m_pSetImage->DrawObject(pDC, (int)bOver);// , RGB(255, 0, 255));
		}

		if (m_pDataManager != NULL) {
			IOSW_to_IOSWGUI stData;
			m_pDataManager->GetIOSW2GUIData(&stData);

			UpdateCPUStatus(pDC, stData.stSystemStatus);
			UpdateMemoryStatus(pDC, stData.stSystemStatus);
			UpdateHDDStatus(pDC, stData.stSystemStatus);
			UpdateHOSTStatus(pDC, stData.eHOSTNetworkStatus);
			UpdateIOSStatus(pDC, stData.eIOSNetworkStatus);
			UpdateIOStatus(pDC, NS_DISCONNECTED);
			UpdateLRUStatus(pDC, stData);
			//UpdatePWRStatus(pDC, stData);

		}

	}

	ReleaseDC(pDC);
	
}

void CIOSWSystemStatus::EndMonitoring()
{
	//EndThread();
}
//
//DWORD CIOSWSystemStatus::ThreadProc()
//{
//	DWORD nOld = GetTickCount();
//
//	while (1)
//	{
//		DWORD nNew = GetTickCount();
//
//		if (nNew - nOld >= 200) {
//
//			UpdateRender();
//
//			nOld = GetTickCount();
//		}
//
//		Sleep(1);
//
//		if (m_bEndThread == TRUE) break;   // Thread 종료 조건
//	}
//
//	return 1;
//}


void CIOSWSystemStatus::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_pSetImage != NULL) {

		BOOL bOver = m_pSetImage->IsPtInRect(point);

		m_pSetImage->SetOver(bOver);
	}


	CIOSWWnd::OnMouseMove(nFlags, point);
}


void CIOSWSystemStatus::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (m_pSetImage != NULL) {
		if (m_pSetImage->GetOver())
		{
			//theApp.GetMainDlg()->PostMessage(UM_SELECT_SETTING, 0);
		}
	}

	//if (m_pPWROnImage != NULL) {
	//	if (m_pPWROnImage->IsPtInRect(point))
	//	{
	//		if (m_pDataManager != NULL) {
	//			IOSWGUI_to_IOSW stData;
	//			m_pDataManager->GetGUI2IOSWData(&stData);

	//			stData.bPowerON = true;

	//			m_pDataManager->SetGUI2IOSWData(stData);
	//		}
	//	}
	//}

	//if (m_pPWROffImage != NULL) {
	//	if (m_pPWROffImage->IsPtInRect(point))
	//	{
	//		if (m_pDataManager != NULL) {
	//			IOSWGUI_to_IOSW stData;
	//			m_pDataManager->GetGUI2IOSWData(&stData);

	//			stData.bPowerON = false;

	//			m_pDataManager->SetGUI2IOSWData(stData);
	//		}
	//	}
	//}

	CIOSWWnd::OnLButtonDown(nFlags, point);
}


void CIOSWSystemStatus::OnClose()
{

	m_font.DeleteObject();

	CIOSWWnd::OnClose();
}


BOOL CIOSWSystemStatus::OnEraseBkgnd(CDC* pDC)
{
	if (m_pBGImage != NULL)
	{
		m_pBGImage->DrawObject(pDC);

		return TRUE;
	}
	else
		return CIOSWWnd::OnEraseBkgnd(pDC);
}


void CIOSWSystemStatus::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 300)
	{
		UpdateRender();

	}

	CIOSWWnd::OnTimer(nIDEvent);
}
