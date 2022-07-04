#include "stdafx.h"
#include "NexwareIOBoardInterface.h"


CNexwareIOBoardInterface::CNexwareIOBoardInterface()
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


CNexwareIOBoardInterface::~CNexwareIOBoardInterface()
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


bool CNexwareIOBoardInterface::Initialize(char* chIOBoardAddr, const int& nIOBoardPort, char* chIOSWAddr, const int& nIOSWPort)
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

void CNexwareIOBoardInterface::SetDataManager(CIOSWDataManager* pManager)
{
	if (pManager != NULL) {
		m_pDataManager = pManager;
	}
}

bool CNexwareIOBoardInterface::StartInterface()
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

		m_pSendThread->Create(CNexwareIOBoardInterface::_WorkSendThread, this);
		m_pRecvThread->Create(CNexwareIOBoardInterface::_WorkRecvThread, this);

		return true;
	}

	return false;
}

bool CNexwareIOBoardInterface::StopInterface()
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


bool CNexwareIOBoardInterface::SetBoardInformation(const int& nIndex, const IOBOARD_INFORMATION& stInfo)
{
	if (nIndex >= MAX_IOBOARD_IO)
		return false;

	memcpy(&m_stIOInformation[nIndex], &stInfo, sizeof(IOBOARD_INFORMATION));

	return true;
}

void CNexwareIOBoardInterface::UpdateNetworkStatus(bool bConnected)
{
	if (m_pDataManager != NULL) {
		IOSW_to_IOSWGUI stIOSW2GUI;
		m_pDataManager->GetIOSW2GUIData(&stIOSW2GUI);
		int nBID = GetBoardID();

		NETWORKSTATUS_TYPE eNetworkStatus = stIOSW2GUI.eIONetworkStatus[nBID];

		if (bConnected == true) {
			eNetworkStatus = NS_CONNECTED;
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

void CNexwareIOBoardInterface::WorkSendThread()
{
	int nSendSize = sizeof(IOSW_to_Nexware);
	char chSendBuff[sizeof(IOSW_to_Nexware)];

	ZeroMemory(chSendBuff, nSendSize);

	DWORD nOld = GetTickCount();

	while (1)
	{
		DWORD nNew = GetTickCount();

		if (nNew - nOld >= 20) {	// 50Hz

			if (m_pSender != NULL && m_pDataManager != NULL)
			{
				// Send
				IOSW_to_Nexware stSendData;
				IOSW_to_IOBOARD stIOBoardData;
				::memset(&stSendData, 0x00, sizeof(IOSW_to_Nexware));

				// Encode(host data)
				m_pDataManager->EncodeIOBoardData(m_nBoardID, m_stIOInformation);
				m_pDataManager->GetIOSW2IOBoardData(&stIOBoardData, m_nBoardID);

				// Convert IOBoard to Nexware Data
				ConvertIOBoardStatetoSend(stIOBoardData, &stSendData);

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

void CNexwareIOBoardInterface::WorkRecvThread()
{
	int nReceiveSize = sizeof(Nexware_to_IOSW);
	char chReceiveBuff[sizeof(Nexware_to_IOSW)];

	ZeroMemory(chReceiveBuff, nReceiveSize);

	while (1)
	{
		if (m_pReceiver != NULL && m_pDataManager != NULL)
		{
			// Receive
			if (m_pReceiver->ReceiveFrom(chReceiveBuff, nReceiveSize) > 0)
			{
				UpdateNetworkStatus(true);

				Nexware_to_IOSW stRecvData;
				IOBOARD_to_IOSW stIOBoardData;

				::memset(&stIOBoardData, 0x00, sizeof(IOBOARD_to_IOSW));
				::memcpy(&stRecvData, &chReceiveBuff, nReceiveSize);

				int nBoardID = (int)stRecvData.Device_No;

				m_nBoardID = ConvertNexwareIDtoIOBoardID(nBoardID);

				// Conveter Nexware to IOBoardData
				ConvertRecvtoIOBoardState(stRecvData, &stIOBoardData);

				m_pDataManager->SetIOBoard2IOSWData(stIOBoardData, m_nBoardID);
				m_pDataManager->DecodeIOBoardData(m_nBoardID, m_stIOInformation);
			}
			else
			{
				UpdateNetworkStatus(false);
			}
		}

		Sleep(1);

		if (m_bEndRecvThread == TRUE) break;   // Thread 종료 조건
	}
}

void CNexwareIOBoardInterface::_WorkSendThread(void* pOwner)
{
	CNexwareIOBoardInterface* pIF = (CNexwareIOBoardInterface*)pOwner;

	if (pIF != NULL) {
		pIF->WorkSendThread();
	}
}

void CNexwareIOBoardInterface::_WorkRecvThread(void* pOwner)
{
	CNexwareIOBoardInterface* pIF = (CNexwareIOBoardInterface*)pOwner;

	if (pIF != NULL) {
		pIF->WorkRecvThread();
	}
}

bool CNexwareIOBoardInterface::ConvertIOBoardStatetoSend(const IOSW_to_IOBOARD & sInfo, IOSW_to_Nexware * psInfo)
{
	// Board NO Convert
	psInfo->Device_No = ConvertIOBoardIDtoNexwareID(sInfo.Board_No);

	// BIT Command Convert
	psInfo->BIT_Command			= sInfo.BIT_COMMAND;

	// Reboot/Shutdown Convert
	psInfo->Reboot_Command		= sInfo.REBOOT_COMMAND;
	psInfo->Shutdown_Command	= sInfo.SHUTDOWN_COMMAND;
	
	// AO Convert
	psInfo->AO_0 = sInfo.CH0_WIDTH_28V;
	psInfo->AO_1 = sInfo.CH1_WIDTH_28V;
	psInfo->AO_2 = sInfo.CH2_WIDTH_28V;
	psInfo->AO_3 = sInfo.CH3_WIDTH_28V;
	psInfo->AO_4 = sInfo.CH4_WIDTH_28V;
	psInfo->AO_5 = sInfo.CH5_WIDTH_28V;
	psInfo->AO_6 = sInfo.CH6_WIDTH_28V;
	psInfo->AO_7 = sInfo.CH7_WIDTH_28V;

	// DO Convert
	psInfo->DO_1 = sInfo.DO_28V;

	return true;

}

bool CNexwareIOBoardInterface::ConvertRecvtoIOBoardState(const Nexware_to_IOSW & sInfo, IOBOARD_to_IOSW * psInfo)
{
	// Board NO Convert
	psInfo->Board_No = m_nBoardID;

	// BIT Result Convert
	psInfo->BIT_RESULT = sInfo.BIT_Result;

	// AI Data Convert
	psInfo->AI_CH_0 = sInfo.AI_0;
	psInfo->AI_CH_1 = sInfo.AI_1;
	psInfo->AI_CH_2 = sInfo.AI_2;
	psInfo->AI_CH_3 = sInfo.AI_3;
	psInfo->AI_CH_4 = sInfo.AI_4;
	psInfo->AI_CH_5 = sInfo.AI_5;
	psInfo->AI_CH_6 = sInfo.AI_6;
	psInfo->AI_CH_7 = sInfo.AI_7;

	// DI Data Convert
	psInfo->DI_CH_LOW  = sInfo.DI_1;
	psInfo->DI_CH_HIGH = sInfo.DI_2;

	return true;
}

int CNexwareIOBoardInterface::ConvertNexwareIDtoIOBoardID(const int& nNexwareID)
{
	int nIOBoardID = 0;

	switch (nNexwareID)
	{
	case NEXWARE_UFC_ID:
		nIOBoardID = IOBOARD_UFC_ID;
		break;
	case NEXWARE_HCP_ID:
		nIOBoardID = IOBOARD_HCP_ID;
		break;
	case NEXWARE_SAI_ID:
		nIOBoardID = IOBOARD_SAI_ID;
		break;
	case NEXWARE_AOA_ID:
		nIOBoardID = IOBOARD_AOA_ID;
		break;
	case NEXWARE_VVI_ID:
		nIOBoardID = IOBOARD_VVI_ID;
		break;
	case NEXWARE_CPA_ID:
		nIOBoardID = IOBOARD_CPA_ID;
		break;
	case NEXWARE_ALT_ID:
		nIOBoardID = IOBOARD_ALT_ID;
		break;
	case NEXWARE_SA_ID:
		nIOBoardID = IOBOARD_SA_ID;
		break;
	case NEXWARE_CLOCK_ID:
		nIOBoardID = IOBOARD_CLOCK_ID;
		break;
	case NEXWARE_EEMD_ID:
		nIOBoardID = IOBOARD_EEMD_ID;
		break;
	case NEXWARE_FQI_ID:
		nIOBoardID = IOBOARD_FQI_ID;
		break;
	default:
		break;
	}

	return nIOBoardID;
}

int CNexwareIOBoardInterface::ConvertIOBoardIDtoNexwareID(const int& nIOBoardID)
{
	int nNexwareID = 0;

	switch (nIOBoardID)
	{
	case IOBOARD_UFC_ID:
		nNexwareID = NEXWARE_UFC_ID;
		break;
	case IOBOARD_HCP_ID:
		nNexwareID = NEXWARE_HCP_ID;
		break;
	case IOBOARD_SAI_ID:
		nNexwareID = NEXWARE_SAI_ID;
		break;
	case IOBOARD_AOA_ID:
		nNexwareID = NEXWARE_AOA_ID;
		break;
	case IOBOARD_VVI_ID:
		nNexwareID = NEXWARE_VVI_ID;
		break;
	case IOBOARD_CPA_ID:
		nNexwareID = NEXWARE_CPA_ID;
		break;
	case IOBOARD_ALT_ID:
		nNexwareID = NEXWARE_ALT_ID;
		break;
	case IOBOARD_SA_ID:
		nNexwareID = NEXWARE_SA_ID;
		break;
	case IOBOARD_CLOCK_ID:
		nNexwareID = NEXWARE_CLOCK_ID;
		break;
	case IOBOARD_EEMD_ID:
		nNexwareID = NEXWARE_EEMD_ID;
		break;
	case IOBOARD_FQI_ID:
		nNexwareID = NEXWARE_FQI_ID;
		break;
	default:
		break;
	}

	return nNexwareID;
}
