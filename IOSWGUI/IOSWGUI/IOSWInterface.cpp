#include "stdafx.h"
#include "IOSWGUI.h"
#include "IOSWInterface.h"


CIOSWInterface::CIOSWInterface()
{
	m_pSender = NULL;
	m_pReceiver = NULL;
	m_pDataManager = NULL;
	m_bInitialize = false;
}


CIOSWInterface::~CIOSWInterface()
{
	EndThread();

	if (m_pSender != NULL) {
		delete m_pSender;
		m_pSender = NULL;
	}

	if (m_pReceiver != NULL) {
		delete m_pReceiver;
		m_pReceiver = NULL;
	}

}


bool CIOSWInterface::Initialize(char* chIOSWAddr, const int& nIOSWPort, char* chGUIAddr, const int& nGUIPort)
{
	m_pSender = new CUDPSendSocket();

	if (m_pSender == NULL)
		return false;

	if (!m_pSender->InitSendSocket(nIOSWPort, chIOSWAddr))
		return false;

	m_pReceiver = new CUDPReceiveSocket();

	if (m_pReceiver == NULL)
		return false;

	if (!m_pReceiver->InitReceiveSocket(nGUIPort, chGUIAddr))
		return false;


	m_bInitialize = true;

	return true;
}


void CIOSWInterface::SetDataManager(CIOSWDataManager* pManager)
{
	if (pManager != NULL) {
		m_pDataManager = pManager;
	}
}


bool CIOSWInterface::StartInterface()
{
	if (IsInitialize()) {
		StartThread();

		return true;
	}

	return false;
}

bool CIOSWInterface::StopInterface()
{
	if (IsInitialize()) {
		EndThread();

		return true;
	}

	return false;

}


DWORD CIOSWInterface::ThreadProc()
{
	bool bResult = 1;

	int nReceiveSize = sizeof(IOSW_to_IOSWGUI);
	int nSendSize = sizeof(IOSWGUI_to_IOSW);

	char chReceiveBuff[sizeof(IOSW_to_IOSWGUI)];
	char chSendBuff[sizeof(IOSWGUI_to_IOSW)];

	ZeroMemory(chReceiveBuff, nReceiveSize);
	ZeroMemory(chSendBuff, nSendSize);


	DWORD nOld = GetTickCount();
	
	while (1)
	{
		DWORD nNew = GetTickCount();

		if (m_pReceiver != NULL && m_pSender != NULL)
		{
			// Receive
			if (m_pReceiver->ReceiveFrom(chReceiveBuff, nReceiveSize) > 0)
			{
				IOSW_to_IOSWGUI stRecvData;
				::memcpy(&stRecvData, &chReceiveBuff, nReceiveSize);

				m_pDataManager->SetIOSW2GUIData(stRecvData);
				m_pDataManager->UpdateIOMonitoringData();

				// IOSW GUI Exit
				if (stRecvData.bSystemOff == true){
					theApp.GetMainDlg()->PostMessage(WM_CLOSE);
				}
			}

			if (nNew - nOld >= 200)  // 5Hz 
			{	

				// Send
				IOSWGUI_to_IOSW stSendData;

				m_pDataManager->GetGUI2IOSWData(&stSendData);
				::memcpy(&chSendBuff, &stSendData, nSendSize);
				m_pSender->SendTo(chSendBuff, nSendSize);
	
				nOld = GetTickCount();
			}

		}

		
		Sleep(1);

		if (m_bEndThread == TRUE) break;   // Thread 종료 조건
	}

	return bResult;
}