#include "stdafx.h"
#include "IOPowerInterface.h"



CIOPowerInterface::CIOPowerInterface()
{
	m_pSender = NULL;
	m_pReceiver = NULL;
	m_pRecvThread = NULL;
	m_pSendThread = NULL;

	m_pDataManager = NULL;

	m_bInitialize = false;
	m_bEndSendThread = false;
	m_bEndRecvThread = false;
	m_eNetworkStatus = NS_DISCONNECTED;
	m_nNetworkStatusCount = 0;
	m_ePowerStatus = POWER_ON;
}


CIOPowerInterface::~CIOPowerInterface()
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

bool CIOPowerInterface::Initialize(char* chIOSAddr, const int& nIOSPort, char* chIOSWAddr, const int& nIOSWPort)
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

void CIOPowerInterface::SetDataManager(CIOSWDataManager* pManager)
{
	if (pManager != NULL) {
		m_pDataManager = pManager;
	}
}

bool CIOPowerInterface::StartInterface()
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

		m_pSendThread->Create(CIOPowerInterface::_WorkSendThread, this);
		m_pRecvThread->Create(CIOPowerInterface::_WorkRecvThread, this);

		return true;
	}

	return false;
}

bool CIOPowerInterface::StopInterface()
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

void CIOPowerInterface::UpdateNetworkStatus(bool bConnected, bool bBITResult)
{
	if (m_pDataManager != NULL) {
		IOSW_to_IOSWGUI stIOSW2GUI;
		m_pDataManager->GetIOSW2GUIData(&stIOSW2GUI);

		NETWORKSTATUS_TYPE eNetworkStatus = stIOSW2GUI.ePowerNetworkStatus;

		if (bConnected == true)		 // Network Connection
		{
			if (bBITResult == false) // BIT FAIL
			{
				eNetworkStatus = NS_ERROR;
			}
			else
			{
				eNetworkStatus = NS_CONNECTED;
			}

			m_nNetworkStatusCount = 0;
		}
		else {
			m_nNetworkStatusCount++;
			if (m_nNetworkStatusCount >= 30)
			{
				eNetworkStatus = NS_DISCONNECTED;
				m_nNetworkStatusCount = 0;
			}
		}

		stIOSW2GUI.ePowerNetworkStatus = eNetworkStatus;

		m_pDataManager->SetIOSW2GUIData(stIOSW2GUI);
	}
}

void CIOPowerInterface::WorkSendThread()
{
	int nSendSize = sizeof(IOSW_to_IOBOARD);
	char chSendBuff[sizeof(IOSW_to_IOBOARD)];

	ZeroMemory(chSendBuff, nSendSize);

	DWORD nOld = GetTickCount();

	while (1)
	{
		DWORD nNew = GetTickCount();

		if (nNew - nOld >= 500) {	// 1Hz

			if (m_pSender != NULL && m_pDataManager != NULL)
			{
				// Send
				IOSW_to_IOBOARD stSendData;
				if (m_ePowerStatus == POWER_ON)
				{
					stSendData.DO_28V = 0x01;
				}
				else
				{
					stSendData.DO_28V = 0x00;
				}
	
				stSendData.Board_No = 99;
				TRACE(_T("전원분배기 상태 = %d\n"), stSendData.DO_28V);

				::memcpy(&chSendBuff, &stSendData, nSendSize);

				// Send
				int nLen = m_pSender->SendTo(chSendBuff, nSendSize);
			}

			nOld = GetTickCount();
		}

		Sleep(1);

		if (m_bEndSendThread == TRUE) break;   // Thread 종료 조건
	}
}


void CIOPowerInterface::WorkRecvThread()
{
	int nReceiveSize = sizeof(IOBOARD_to_IOSW);
	char chReceiveBuff[sizeof(IOBOARD_to_IOSW)];

	ZeroMemory(chReceiveBuff, nReceiveSize);

	while (1)
	{
		if (m_pReceiver != NULL && m_pDataManager != NULL)
		{
			// Receive
			if (m_pReceiver->ReceiveFrom(chReceiveBuff, nReceiveSize) > 0)
			{
				IOBOARD_to_IOSW stRecvData;

				::memcpy(&stRecvData, &chReceiveBuff, nReceiveSize);
				int nBoardID = (int)stRecvData.Board_No;
				bool bBITResult = stRecvData.BIT_RESULT;

				UpdateNetworkStatus(true, bBITResult);

			}
			else
			{
				UpdateNetworkStatus(false, false);
			}
		}

		Sleep(1);

		if (m_bEndRecvThread == TRUE) break;   // Thread 종료 조건
	}
}


void CIOPowerInterface::_WorkSendThread(void* pOwner)
{
	CIOPowerInterface* pIF = (CIOPowerInterface*)pOwner;

	if (pIF != NULL) {
		pIF->WorkSendThread();
	}
}


void CIOPowerInterface::_WorkRecvThread(void* pOwner)
{
	CIOPowerInterface* pIF = (CIOPowerInterface*)pOwner;

	if (pIF != NULL) {
		pIF->WorkRecvThread();
	}
}