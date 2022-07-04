#include "stdafx.h"
#include "ANToIOBoardInterface.h"
#include "IOBoard_Interface.h"

CANToIOBoardInterface::CANToIOBoardInterface()
{
	m_pSender = NULL;
	m_pReceiver = NULL;
	m_pDataManager = NULL;
	m_pSendThread = NULL;
	m_pRecvThread = NULL;

	m_bInitialize = false;
	m_bEndSendThread = false;
	m_bEndRecvThread = false;

	m_eNetworkStatus = NS_DISCONNECTED;
	m_nNetworkStatusCount = 0;
	m_nBoardID = -1;

	for (int i = 0; i < MAX_IOBOARD_IO; i++) {
		ZeroMemory(&m_stIOInformation[i], sizeof(IOBOARD_INFORMATION));
	}
}


CANToIOBoardInterface::~CANToIOBoardInterface()
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

bool CANToIOBoardInterface::Initialize(char* chIOBoardAddr, const int& nIOBoardPort, char* chIOSWAddr, const int& nIOSWPort)
{
	m_pSender = new CUDPSendSocket();

	if (m_pSender == NULL)
		return false;

	if (!m_pSender->InitSendSocket(nIOBoardPort, chIOBoardAddr))
		return false;

	m_pReceiver = new CUDPReceiveSocket();

	if (m_pReceiver == NULL)
		return false;

	if (!m_pReceiver->InitReceiveSocket(nIOSWPort, chIOSWAddr))
		return false;

	m_bInitialize = true;

	return true;
}

void CANToIOBoardInterface::SetDataManager(CIOSWDataManager* pManager)
{
	if (pManager != NULL) {
		m_pDataManager = pManager;
	}
}

bool CANToIOBoardInterface::StartInterface()
{
/*	if (IsInitialize()) {
		StartThread();

		return true;
	}

	return false;*/
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

		m_pSendThread->Create(CANToIOBoardInterface::_WorkSendThread, this);
		m_pRecvThread->Create(CANToIOBoardInterface::_WorkRecvThread, this);

		return true;
	}

	return false;
}

bool CANToIOBoardInterface::StopInterface()
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


bool CANToIOBoardInterface::SetBoardInformation(const int& nIndex, const IOBOARD_INFORMATION& stInfo)
{
	if (nIndex >= MAX_IOBOARD_IO)
		return false;

	memcpy(&m_stIOInformation[nIndex], &stInfo, sizeof(IOBOARD_INFORMATION));

	return true;
}

void CANToIOBoardInterface::UpdateNetworkStatus(bool bConnected, bool bBITResult)
{
	if (m_pDataManager != NULL) {
		IOSW_to_IOSWGUI stIOSW2GUI;
		m_pDataManager->GetIOSW2GUIData(&stIOSW2GUI);
		int nBID = GetBoardID();

		NETWORKSTATUS_TYPE eNetworkStatus = stIOSW2GUI.eIONetworkStatus[nBID];

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
		
		stIOSW2GUI.eIONetworkStatus[nBID] = eNetworkStatus;

		m_pDataManager->SetIOSW2GUIData(stIOSW2GUI);
	}
}

void CANToIOBoardInterface::WorkSendThread()
{
	int nSendSize = sizeof(IOSW_to_IOBOARD);
	char chSendBuff[sizeof(IOSW_to_IOBOARD)];

	ZeroMemory(chSendBuff, nSendSize);

	DWORD nOld = GetTickCount();

	while (1)
	{
		DWORD nNew = GetTickCount();

		if (nNew - nOld >= 20) {	// 50Hz

			if (m_pSender != NULL && m_pDataManager != NULL)
			{
				// Send
				IOSW_to_IOBOARD stSendData;

				// Encode(host data)
				m_pDataManager->EncodeIOBoardData(m_nBoardID, m_stIOInformation);

				m_pDataManager->GetIOSW2IOBoardData(&stSendData, m_nBoardID);

				stSendData.Board_No = m_nBoardID;

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

void CANToIOBoardInterface::WorkRecvThread()
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

				bool bBITResult = false;
				
				if (stRecvData.BIT_RESULT == 0x01)
					bBITResult = true;

				m_nBoardID = nBoardID;
				m_pDataManager->SetIOBoard2IOSWData(stRecvData, nBoardID);
				m_pDataManager->DecodeIOBoardData(nBoardID, m_stIOInformation);


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

void CANToIOBoardInterface::_WorkSendThread(void* pOwner)
{
	CANToIOBoardInterface* pIF = (CANToIOBoardInterface*)pOwner;

	if (pIF != NULL) {
		pIF->WorkSendThread();
	}
}

void CANToIOBoardInterface::_WorkRecvThread(void* pOwner)
{
	CANToIOBoardInterface* pIF = (CANToIOBoardInterface*)pOwner;

	if (pIF != NULL) {
		pIF->WorkRecvThread();
	}
}