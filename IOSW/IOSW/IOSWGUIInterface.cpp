#include "stdafx.h"
#include "IOSWGUIInterface.h"
#include "IOSW.h"
#include "IOSWDlg.h"


CIOSWGUIInterface::CIOSWGUIInterface()
{
	m_pSender = NULL;
	m_pReceiver = NULL;
	m_pDataManager = NULL;
	m_pSystemManager = NULL;

	m_bInitialize = false;
}


CIOSWGUIInterface::~CIOSWGUIInterface()
{
	if (m_pSender != NULL) {
		delete m_pSender;
		m_pSender = NULL;
	}

	if (m_pReceiver != NULL) {
		delete m_pReceiver;
		m_pReceiver = NULL;
	}

	if (m_pSystemManager != NULL) {
		delete m_pSystemManager;
		m_pSystemManager = NULL;
	}
}

bool CIOSWGUIInterface::Initialize(char* chGUIAddr, const int& nGUIPort, char* chIOSWAddr, const int& nIOSWPort)
{
	m_pSender = new CUDPSendSocket();

	if (m_pSender == NULL)
		return false;

	if (!m_pSender->InitSendSocket(nGUIPort, chGUIAddr))
		return false;

	m_pReceiver = new CUDPReceiveSocket();

	if (m_pReceiver == NULL)
		return false;

	if (!m_pReceiver->InitReceiveSocket(nIOSWPort, chIOSWAddr))
		return false;

	m_pSystemManager = new CSystemStatusManager;
	
	if (m_pSystemManager == NULL)
		return false;

	m_bInitialize = true;

	return true;
}

void CIOSWGUIInterface::SetDataManager(CIOSWDataManager* pManager)
{
	if (pManager != NULL) {
		m_pDataManager = pManager;
	}
}

bool CIOSWGUIInterface::StartInterface()
{
	if (IsInitialize()) {
		StartThread();

		return true;
	}

	return false;
}

bool CIOSWGUIInterface::StopInterface()
{
	if (IsInitialize()) {
		EndThread();

		return true;
	}

	return false;

}

void CIOSWGUIInterface::UpdateSystemStatusInfo()
{
	if (m_pSystemManager != NULL && m_pDataManager != NULL)
	{
		SYSTEMSTATUSINFO sInfo;
		IOSW_to_IOSWGUI	 sData;

		m_pDataManager->GetIOSW2GUIData(&sData);
		m_pSystemManager->UpdateSystemStatusInfo(&sInfo);

		memcpy(&sData.stSystemStatus, &sInfo, sizeof(SYSTEMSTATUSINFO));

		m_pDataManager->SetIOSW2GUIData(sData);
	}
}

DWORD CIOSWGUIInterface::ThreadProc()
{
	bool bResult = 1;

	int nReceiveSize = sizeof(IOSWGUI_to_IOSW);
	int nSendSize = sizeof(IOSW_to_IOSWGUI);

	char chReceiveBuff[sizeof(IOSWGUI_to_IOSW)];
	char chSendBuff[sizeof(IOSW_to_IOSWGUI)];

	ZeroMemory(chReceiveBuff, nReceiveSize);
	ZeroMemory(chSendBuff, nSendSize);

	//bool bPowerOn = true;

	DWORD nOld = GetTickCount();

	while (1)
	{
		DWORD nNew = GetTickCount();

		if (m_pReceiver != NULL && m_pSender != NULL && m_pDataManager != NULL)
		{
			// Receive
			if (m_pReceiver->ReceiveFrom(chReceiveBuff, nReceiveSize) > 0)
			{
				IOSWGUI_to_IOSW stRecvData;
				::memcpy(&stRecvData, &chReceiveBuff, nReceiveSize);

				// Set Mode
				m_pDataManager->SetIOSWMode(stRecvData.eIOSWMode);

				// Set Receive Data
				m_pDataManager->SetGUI2IOSWData(stRecvData);

				//if (stRecvData.bPowerON != bPowerOn)
				//{
				//	CIOSWDlg * pDlg = (CIOSWDlg*)theApp.m_pMainWnd;
				//	bPowerOn = stRecvData.bPowerON;

				//	if (pDlg != NULL) {

				//		if (bPowerOn == true) {
				//			m_pDataManager->DoSystemOnOff(0x00, false);
				//			pDlg->DoPowerDistributorOn();
				//		}
				//		else {
				//			m_pDataManager->DoSystemOnOff(0x01, false);
				//			pDlg->DoPowerDistributorOff();
				//		}
				//	}					
				//}

			}

			// 5Hz
			if (nNew - nOld >= 200)
			{
				IOSW_to_IOSWGUI stSendData;

				m_pDataManager->GetIOSW2GUIData(&stSendData);
				::memcpy(&chSendBuff, &stSendData, nSendSize);

				// Send
				m_pSender->SendTo(chSendBuff, nSendSize);

				// Update for System Status Information.
				UpdateSystemStatusInfo();

				nOld = GetTickCount();
			}
		}

		Sleep(1);

		if (m_bEndThread == TRUE) break;   // Thread 종료 조건
	}

	return bResult;
}