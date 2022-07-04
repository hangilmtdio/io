#include "stdafx.h"
#include "HostInterface.h"


CHostInterface::CHostInterface()
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
	m_eInstStatus = NS_DISCONNECTED;
}


CHostInterface::~CHostInterface()
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

bool CHostInterface::Initialize(char* chHOSTAddr, const int& nHOSTPort, char* chIOSWAddr, const int& nIOSWPort)
{
	m_pSender = new CUDPSendSocket();

	if (m_pSender == NULL)
		return false;

	if (!m_pSender->InitSendSocket(nHOSTPort, chHOSTAddr))
		return false;

	m_pReceiver = new CUDPReceiveSocket();

	if (m_pReceiver == NULL)
		return false;

	if (!m_pReceiver->InitReceiveSocket(nIOSWPort, chIOSWAddr))
		return false;

	m_bInitialize = true;

	return true;
}

void CHostInterface::SetDataManager(CIOSWDataManager* pManager)
{
	if (pManager != NULL) {
		m_pDataManager = pManager;
	}
}

bool CHostInterface::StartInterface()
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

		m_pSendThread->Create(CHostInterface::_WorkSendThread, this);
		m_pRecvThread->Create(CHostInterface::_WorkRecvThread, this);

		return true;
	}

	return false;
}

bool CHostInterface::StopInterface()
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

void CHostInterface::UpdateNetworkStatus(bool bConnected)
{
	if (m_pDataManager != NULL) {
		IOSW_to_IOSWGUI stIOSW2GUI;
		m_pDataManager->GetIOSW2GUIData(&stIOSW2GUI);
	
		static int nCount = 0;
		NETWORKSTATUS_TYPE eNetworkStatus = stIOSW2GUI.eHOSTNetworkStatus;

		if (bConnected == true) {
			eNetworkStatus = NS_CONNECTED;
			nCount = 0;
		}
		else {
			nCount++;
			if (nCount >= 30)
				eNetworkStatus = NS_DISCONNECTED;
		}

		stIOSW2GUI.eHOSTNetworkStatus = eNetworkStatus;

		m_pDataManager->SetIOSW2GUIData(stIOSW2GUI);
	}
}

void CHostInterface::UpdateInstStatus()
{
	if (m_pDataManager != NULL) {
		static int nOldTimeTag = -1;

		bool bInstConnected = m_pDataManager->GetInstConnected();
		Host_To_Cockpit_Data_Type sData;
		m_pDataManager->GetHOST2CockpitData(&sData);
	
		if (nOldTimeTag != -1)
		{
			if (nOldTimeTag != sData.INST_TIMETAG) 
			{
				bInstConnected = true;

				
			}
			else {
				bInstConnected = false;
			}

			m_pDataManager->SetInstConnected(bInstConnected);
		}
		
		nOldTimeTag = sData.INST_TIMETAG;

	}
}

//
//DWORD CHostInterface::ThreadProc()
//{
//	bool bResult = 1;
//
//	int nReceiveSize = sizeof(Host_To_Cockpit_Data_Type);
//	int nSendSize = sizeof(Cockpit_To_Host_Data_Type);
//
//	char chReceiveBuff[sizeof(Host_To_Cockpit_Data_Type)];
//	char chSendBuff[sizeof(Cockpit_To_Host_Data_Type)];
//
//	ZeroMemory(chReceiveBuff, nReceiveSize);
//	ZeroMemory(chSendBuff, nSendSize);
//
//
//	DWORD nOld = GetTickCount();
//
//	while (1)
//	{
//		DWORD nNew = GetTickCount();
//
//	
//			if (m_pReceiver != NULL && m_pSender != NULL)
//			{
//				// Receive
//				if (m_pReceiver->ReceiveFrom(chReceiveBuff, nReceiveSize) > 0)
//				{
//					UpdateNetworkStatus(true);
//
//					if (m_pDataManager != NULL) {
//						Host_To_Cockpit_Data_Type stRecvData;
//
//						::memcpy(&stRecvData, &chReceiveBuff, nReceiveSize);
//						m_pDataManager->SetHOST2CockpitData(stRecvData);
//
//						if (nNew - nOld >= 20) {	// 50Hz
//
//							// Send
//							Cockpit_To_Host_Data_Type stSendData;
//							m_pDataManager->GetCockpit2HOSTData(&stSendData);
//
//							::memcpy(&chSendBuff, &stSendData, nSendSize);
//							m_pSender->SendTo(chSendBuff, nSendSize);
//						}
//					}
//				}
//				else
//				{
//					UpdateNetworkStatus(false);
//				}
//		
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

void CHostInterface::WorkSendThread()
{
	int nSendSize = sizeof(Cockpit_To_Host_Data_Type);
	int nRecvSize = sizeof(Host_To_Cockpit_Data_Type);
	char chSendBuff[sizeof(Cockpit_To_Host_Data_Type)];

	ZeroMemory(chSendBuff, nSendSize);

	DWORD nOld = GetTickCount();
	int nTimeTag = 0;

	while (1)
	{
		DWORD nNew = GetTickCount();

		if (nNew - nOld >= 20) {	// 50Hz

			if (m_pSender != NULL && m_pDataManager != NULL)
			{
				Cockpit_To_Host_Data_Type stSendData;
				m_pDataManager->GetCockpit2HOSTData(&stSendData);

				// Timetag Update
				stSendData.TIMETAG = nTimeTag++;

				// Size Update
				stSendData.COCK2HOST_SIZE = nSendSize;
				stSendData.HOST2COCK_SIZE = nRecvSize;

				// 김한승 CDR 시험용 20220523
				static int t_cnt = 0;
				if (t_cnt++ == 0)
				{
					stSendData.IO2HOST.f16_center_console_type.cmfd_button_type.mfd_btn_1 = OFF;
				}
				else
				{
					stSendData.IO2HOST.f16_center_console_type.cmfd_button_type.mfd_btn_1 = ON;
					t_cnt = 0;
				}

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

void CHostInterface::WorkRecvThread()
{
	int nReceiveSize = sizeof(Host_To_Cockpit_Data_Type);
	char chReceiveBuff[sizeof(Host_To_Cockpit_Data_Type)];

	ZeroMemory(chReceiveBuff, nReceiveSize);
	DWORD nOld = GetTickCount();

	while (1)
	{
		DWORD nNew = GetTickCount();

		if (m_pReceiver != NULL && m_pDataManager != NULL)
		{
			// Receive
			if (m_pReceiver->ReceiveFrom(chReceiveBuff, nReceiveSize) > 0)
			{
				// Network Status Update
				UpdateNetworkStatus(true);

				Host_To_Cockpit_Data_Type stRecvData;

				::memcpy(&stRecvData, &chReceiveBuff, nReceiveSize);

				m_pDataManager->SetHOST2CockpitData(stRecvData);


			}
			else
			{
				// Network Status Update
				UpdateNetworkStatus(false);
				//UpdateInstStatus(0);
			}

			// Inst Status Update
			if (m_pDataManager->GetInstTimeTagMode())
			{
				if (nNew - nOld >= 300) {	// 0.3 sec

					UpdateInstStatus();

					nOld = GetTickCount();
				}
			}
		}

		Sleep(1);

		if (m_bEndRecvThread == TRUE) break;   // Thread 종료 조건
	}
}

void CHostInterface::_WorkSendThread(void* pOwner)
{
	CHostInterface* pIF = (CHostInterface*)pOwner;

	if (pIF != NULL) {
		pIF->WorkSendThread();
	}
}

void CHostInterface::_WorkRecvThread(void* pOwner)
{
	CHostInterface* pIF = (CHostInterface*)pOwner;

	if (pIF != NULL) {
		pIF->WorkRecvThread();
	}
}