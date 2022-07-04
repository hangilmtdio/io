#include "stdafx.h"
#include "IOSInterface.h"
#include "SM_Interface.h"
#include "IOSW.h"
#include "IOSWDlg.h"

CIOSInterface::CIOSInterface()
{
	m_pSender		= NULL;
	m_pReceiver		= NULL;
	m_pDataManager	= NULL;
	m_pSendThread	= NULL;
	m_pRecvThread	= NULL;

	m_bInitialize	 = false;
	m_bEndSendThread = false;
	m_bEndRecvThread = false;

	m_eNetworkStatus = NS_DISCONNECTED;
}


CIOSInterface::~CIOSInterface()
{
	if (m_pSendThread != NULL) {

		m_bEndSendThread = true;
		m_pSendThread->Join();

		delete m_pSendThread;
		m_pSendThread = NULL;
	}

	if (m_pRecvThread != NULL) {

		m_bEndRecvThread = true;
		m_pRecvThread->Join();

		delete m_pRecvThread;
		m_pRecvThread = NULL;
	}

	if (m_pSender != NULL) {
		delete m_pSender;
		m_pSender = NULL;
	}

	if (m_pReceiver != NULL) {
		delete m_pReceiver;
		m_pReceiver = NULL;
	}
}

bool CIOSInterface::Initialize(char* chIOSAddr, const int& nIOSPort, char* chIOSWAddr, const int& nIOSWPort)
{
	m_pSender = new CUDPSendSocket();

	if (m_pSender == NULL) 
		return false;

	if (!m_pSender->InitSendSocket(nIOSPort, chIOSAddr))
		return false;

	m_pReceiver = new CUDPReceiveSocket();

	if (m_pReceiver == NULL)
		return false;

	if (!m_pReceiver->InitReceiveSocket(nIOSWPort, chIOSWAddr))
		return false;
	
	m_bInitialize = true;

	return true;
}

void CIOSInterface::SetDataManager(CIOSWDataManager* pManager)
{
	if (pManager != NULL) {
		m_pDataManager = pManager;
	}
}

bool CIOSInterface::StartInterface()
{
	if (IsInitialize()) {

		if (m_pSendThread != NULL) {
			m_bEndSendThread = true;
			m_pSendThread->Join();

			delete m_pSendThread;
			m_pSendThread = NULL;
		}

		m_pSendThread = new CIOSWThreadObject();

		if (m_pRecvThread != NULL) {
			m_bEndRecvThread = true;
			m_pRecvThread->Join();

			delete m_pRecvThread;
			m_pRecvThread = NULL;
		}

		m_pRecvThread = new CIOSWThreadObject();

		m_pSendThread->Create(CIOSInterface::_WorkSendThread, this);
		m_pRecvThread->Create(CIOSInterface::_WorkRecvThread, this);

		return true;
	}

	return false;
}

bool CIOSInterface::StopInterface()
{
	if (IsInitialize()) {

		m_bEndSendThread = true;
		m_bEndRecvThread = true;

		if (m_pSendThread != NULL) {
			m_pSendThread->Join();

			delete m_pSendThread;
			m_pSendThread = NULL;
		}

		if (m_pRecvThread != NULL) {
			m_pRecvThread->Join();

			delete m_pRecvThread;
			m_pRecvThread = NULL;
		}

		return true;
	}

	return false;

}

void CIOSInterface::UpdateNetworkStatus(bool bConnected)
{
	if (m_pDataManager != NULL) {
		IOSW_to_IOSWGUI stIOSW2GUI;
		m_pDataManager->GetIOSW2GUIData(&stIOSW2GUI);

		static int nCount = 0;
		NETWORKSTATUS_TYPE eNetworkStatus = stIOSW2GUI.eIOSNetworkStatus;

		if (bConnected == true) {
			eNetworkStatus = NS_CONNECTED;
			nCount = 0;
		}
		else {
			nCount++;
			if (nCount >= 30)
				eNetworkStatus = NS_DISCONNECTED;
		}

		stIOSW2GUI.eIOSNetworkStatus = eNetworkStatus;

		m_pDataManager->SetIOSW2GUIData(stIOSW2GUI);
	}
}

void CIOSInterface::UpdateInstrumentStatus(bool bConnected)
{
	if (m_pDataManager != NULL) {
		bool bInstStatus = m_pDataManager->GetInstConnected();
		bool bChanged = false;

		static int nCount = 0;

		if (bInstStatus != bConnected){
			bChanged = true;
			nCount++;
		}
		else{
			bChanged = false;
			nCount = 0;
		}

		if (nCount >= m_pDataManager->GetInstCheckTime())
		{
			m_pDataManager->SetInstConnected(bConnected);
		}
	}
}

//
//DWORD CIOSInterface::ThreadProc()
//{
//	bool bResult = 1;
//
////	SM_IOS_To_Cockpit	stIOS2Cockpit;
////	SM_Cockpit_To_IOS	stCockpit2IOS;
//	int nReceiveSize = sizeof(SM_IOS_To_Cockpit);
//	int nSendSize = sizeof(SM_Cockpit_To_IOS);
//
//	char chReceiveBuff[sizeof(SM_IOS_To_Cockpit)];
//	char chSendBuff[sizeof(SM_Cockpit_To_IOS)];
//
//	ZeroMemory(chReceiveBuff, nReceiveSize);
//	ZeroMemory(chSendBuff, nSendSize);
////	ZeroMemory(&stIOS2Cockpit, sizeof(stIOS2Cockpit));
////	ZeroMemory(&stCockpit2IOS, sizeof(stCockpit2IOS));
//
//	DWORD nOld = GetTickCount();
//
//	while (1)
//	{
//		DWORD nNew = GetTickCount();
//
//		if (nNew - nOld >= 20) {	// 50Hz
//
//			if (m_pReceiver != NULL && m_pSender != NULL) 
//			{
//				// Receive
//				if (m_pReceiver->ReceiveFrom(chReceiveBuff, nReceiveSize) > 0)
//				{
//					UpdateNetworkStatus(true);
//
//					if (m_pDataManager != NULL) {
//						SM_IOS_To_Cockpit stRecvData;
//
//						::memcpy(&stRecvData, &chReceiveBuff, nReceiveSize);
//						m_pDataManager->SetIOS2CockpitData(stRecvData);
//
//						// Send
//						SM_Cockpit_To_IOS stSendData;
//						m_pDataManager->GetCockpit2IOSData(&stSendData);
//
//						::memcpy(&chSendBuff, &stSendData, nSendSize);
//						m_pSender->SendTo(chSendBuff, nSendSize);
//					}
//				}
//				else
//				{
//					UpdateNetworkStatus(false);
//				}
//			}
//
//			nOld = GetTickCount();
//		}
//
//		Sleep(1);
//
//		if (m_bEndThread == TRUE) break;   // Thread 종료 조건
//	}
//
//	return bResult;
//}


void CIOSInterface::WorkSendThread()
{
	int nSendSize = sizeof(SM_Cockpit_To_IOS);
	char chSendBuff[sizeof(SM_Cockpit_To_IOS)];

	ZeroMemory(chSendBuff, nSendSize);

	DWORD nOld = GetTickCount();
	int nTimeTag = 0;
	int nBITCount = 0;

	while (1)
	{
		DWORD nNew = GetTickCount();

		if (nNew - nOld >= 20) {	// 50Hz

			if (m_pSender != NULL && m_pDataManager != NULL)
			{

				// Send
				SM_Cockpit_To_IOS stSendData;
				::memset(&stSendData, 0x00, nSendSize);

				nBITCount++;

				if (nBITCount >= 50)
				{
					m_pDataManager->DecodeBITResult();
					nBITCount = 0;
				}
				
				m_pDataManager->GetCockpit2IOSData(&stSendData);

				// Timetag Update
				stSendData.Timetag = nTimeTag++;

				::memcpy(&chSendBuff, &stSendData, nSendSize);

				// UDP Send
				m_pSender->SendTo(chSendBuff, nSendSize);

			}

			nOld = GetTickCount();
		}

		Sleep(1);

		if (m_bEndSendThread == TRUE) break;   // Thread 종료 조건
	}
}

void CIOSInterface::WorkRecvThread()
{
	int nReceiveSize = sizeof(SM_IOS_To_Cockpit);
	char chReceiveBuff[sizeof(SM_IOS_To_Cockpit)];

	ZeroMemory(chReceiveBuff, nReceiveSize);

	while (1)
	{
		if (m_pReceiver != NULL && m_pDataManager != NULL)
		{
			// Receive
			if (m_pReceiver->ReceiveFrom(chReceiveBuff, nReceiveSize) > 0)
			{
				// Network Status Update
				UpdateNetworkStatus(true);

				SM_IOS_To_Cockpit stRecvData;
				::memcpy(&stRecvData, &chReceiveBuff, nReceiveSize);

				m_pDataManager->SetIOS2CockpitData(stRecvData);

				if (stRecvData.System_Off == bTRUE) // System Off
				{ 
					m_pDataManager->DoSystemOnOff(0x01, true);
					
					CIOSWDlg * pDlg = (CIOSWDlg*) theApp.m_pMainWnd;
					
					if (pDlg != NULL) {
						pDlg->DoSystemOff();
					}
				}

				if (stRecvData.In_Out == bTRUE) // Lamp Test
				{
					m_pDataManager->SetIOSLampTest(true);
				}
				else
				{
					m_pDataManager->SetIOSLampTest(false);
				}

				// Inst Check
				if (m_pDataManager->GetInstTimeTagMode() == false)
				{
					if(stRecvData.Sub_SPT_Flag == bTRUE)
						UpdateInstrumentStatus(false);
					else
						UpdateInstrumentStatus(true);
				}

			}
			else
			{
				// Network Status Update
				UpdateNetworkStatus(false);
			}
		}

		Sleep(1);

		if (m_bEndRecvThread == TRUE) break;   // Thread 종료 조건
	}
}

void CIOSInterface::_WorkSendThread(void* pOwner)
{
	CIOSInterface* pIF = (CIOSInterface*)pOwner;

	if (pIF != NULL) {
		pIF->WorkSendThread();
	}
}

void CIOSInterface::_WorkRecvThread(void* pOwner)
{
	CIOSInterface* pIF = (CIOSInterface*)pOwner;

	if (pIF != NULL) {
		pIF->WorkRecvThread();
	}
}