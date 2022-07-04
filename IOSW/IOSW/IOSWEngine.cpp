#include "stdafx.h"
#include "IOSWEngine.h"
#include "InitFile.h"
#include "IOSWUtility.h"
#include <fstream>
#include "IOSWLogger.h"

CIOSWEngine::CIOSWEngine()
{
	m_pIOSInterface = NULL;
	m_pHostInterface = NULL;
	m_pGUIInterface = NULL;
	m_pIOBoardInterfaceList = NULL;
	m_pNexwareInterfaceList = NULL;
	m_pPowerInterface = NULL;
	m_pThrottleInterface = NULL;
	m_pIOSWDataManager = NULL;
}


CIOSWEngine::~CIOSWEngine()
{
	if (m_pIOSInterface != NULL) {

		m_pIOSInterface->StopInterface();

		delete m_pIOSInterface;
		m_pIOSInterface = NULL;
	}

	if (m_pHostInterface != NULL) {

		m_pHostInterface->StopInterface();

		delete m_pHostInterface;
		m_pHostInterface = NULL;
	}

	if (m_pGUIInterface != NULL) {

		m_pGUIInterface->StopInterface();

		delete m_pGUIInterface;
		m_pGUIInterface = NULL;
	}

	if (m_pIOBoardInterfaceList != NULL) {

		ClearAllIOBoardInterface();

		delete m_pIOBoardInterfaceList;
		m_pIOBoardInterfaceList = NULL;
	}

	if (m_pNexwareInterfaceList != NULL) {
		ClearAllNexwareInterface();

		delete m_pNexwareInterfaceList;
		m_pNexwareInterfaceList = NULL;
	}

	if (m_pPowerInterface != NULL) {

		m_pPowerInterface->StopInterface();

		delete m_pPowerInterface;
		m_pPowerInterface = NULL;
	}

	if (m_pThrottleInterface != NULL) {
		
		m_pThrottleInterface->StopInterface();

		delete m_pThrottleInterface;
		m_pThrottleInterface = NULL;
	}

	if (m_pIOSWDataManager != NULL) {

		delete m_pIOSWDataManager;
		m_pIOSWDataManager = NULL;
	}

	CIOSWLogger::DestroyInstance();

}

bool CIOSWEngine::LoadConfiguration()
{
	CString strSendIP;
	CString strRecvIP;
	int nSendPort = 0;
	int nRecvPort = 0;

	char szSendIP[16];
	char szRecvIP[16];

	memset(&szSendIP, 0x00, sizeof(szSendIP));
	memset(&szRecvIP, 0x00, sizeof(szRecvIP));

	m_pIOSInterface = new CIOSInterface();
	m_pHostInterface = new CHostInterface();
	m_pGUIInterface = new CIOSWGUIInterface();
	m_pThrottleInterface = new CThrottleInterface();
	m_pIOBoardInterfaceList = new LIST_IOBOARDINTERFACE;
	m_pNexwareInterfaceList = new LIST_NEXWARETERFACE;

	m_pIOSInterface->SetDataManager(m_pIOSWDataManager);
	m_pHostInterface->SetDataManager(m_pIOSWDataManager);
	m_pGUIInterface->SetDataManager(m_pIOSWDataManager);
	m_pThrottleInterface->SetDataManager(m_pIOSWDataManager);

	// Stick Value
	m_pIOSWDataManager->SetControlStickLimitValue(
		LoadConfigNumber(_T("STICK_VALUE"), _T("LEFT_CENTER")),
		LoadConfigNumber(_T("STICK_VALUE"), _T("RIGHT_CENTER")),
		LoadConfigNumber(_T("STICK_VALUE"), _T("FRONT_CENTER")),
		LoadConfigNumber(_T("STICK_VALUE"), _T("REAR_CENTER")),
		LoadConfigNumber(_T("STICK_VALUE"), _T("LEFT_LIMIT")),
		LoadConfigNumber(_T("STICK_VALUE"), _T("RIGHT_LIMIT")),
		LoadConfigNumber(_T("STICK_VALUE"), _T("FRONT_LIMIT")),
		LoadConfigNumber(_T("STICK_VALUE"), _T("REAR_LIMIT"))
	);

	// small Instrument gauge Mode
	bool bTimetag = (bool) LoadConfigNumber(_T("INSTRUMENT"), _T("TIMETAGMODE"));
	int  nCheckCount  = (int) LoadConfigNumber(_T("INSTRUMENT"), _T("IOSCHECKCOUNT"));
	m_pIOSWDataManager->SetInstTimeTagMode(bTimetag);
	m_pIOSWDataManager->SetInstCheckTime(nCheckCount);

	// IOS Network info. 
	strSendIP = LoadConfigString(_T("IOS_INTERFACE"), _T("IOS_IP"));
	strRecvIP = LoadConfigString(_T("IOS_INTERFACE"), _T("IOSW_IP"));
	nSendPort = LoadConfigNumber(_T("IOS_INTERFACE"), _T("IOS_PORT"));
	nRecvPort = LoadConfigNumber(_T("IOS_INTERFACE"), _T("IOSW_PORT"));

	// UDP Initialize
	MtoWChar(strSendIP, szSendIP);
	MtoWChar(strRecvIP, szRecvIP);
	if (!m_pIOSInterface->Initialize(szSendIP, nSendPort, szRecvIP, nRecvPort))
		return false;

	// HOST Network Info.
	strSendIP = LoadConfigString(_T("HOST_INTERFACE"), _T("HOST_IP"));
	strRecvIP = LoadConfigString(_T("HOST_INTERFACE"), _T("IOSW_IP"));
	nSendPort = LoadConfigNumber(_T("HOST_INTERFACE"), _T("HOST_PORT"));
	nRecvPort = LoadConfigNumber(_T("HOST_INTERFACE"), _T("IOSW_PORT"));

	// UDP Initialize
	MtoWChar(strSendIP, szSendIP);
	MtoWChar(strRecvIP, szRecvIP);
	if (!m_pHostInterface->Initialize(szSendIP, nSendPort, szRecvIP, nRecvPort))
		return false;

	// IOSW GUI Network Info.
	strSendIP = LoadConfigString(_T("IOGUI_INTERFACE"), _T("GUI_IP"));
	nSendPort = LoadConfigNumber(_T("IOGUI_INTERFACE"), _T("GUI_PORT"));
	strRecvIP = LoadConfigString(_T("IOGUI_INTERFACE"), _T("IOSW_IP"));
	nRecvPort = LoadConfigNumber(_T("IOGUI_INTERFACE"), _T("IOSW_PORT"));

	// UDP Initialize
	MtoWChar(strSendIP, szSendIP);
	MtoWChar(strRecvIP, szRecvIP);

	if (!m_pGUIInterface->Initialize(szSendIP, nSendPort, szRecvIP, nRecvPort))
		return false;

	// ANToIOBoard Count Info.
	int nIOBoardCount = LoadConfigNumber(_T("IOBOARD_INFO"), _T("IOBOARD_COUNT"));

	for (int i = 0; i < nIOBoardCount; i++) {
		CString strTemp;
		strTemp.Format(_T("IOBOARD_%d"), i + 1);

		// ANToIOBoard Network Info.
		strSendIP = LoadConfigString(strTemp, _T("IOBOARD_IP"));
		strRecvIP = LoadConfigString(strTemp, _T("IOSW_IP"));
		nSendPort = LoadConfigNumber(strTemp, _T("IOBOARD_PORT"));
		nRecvPort = LoadConfigNumber(strTemp, _T("IOSW_PORT"));

		// Create ANToIOBoard Interface
		CANToIOBoardInterface* pIF = new CANToIOBoardInterface();
		pIF->SetDataManager(m_pIOSWDataManager);
		pIF->SetBoardID(LoadConfigNumber(strTemp, _T("IOBOARD_ID")));

		// UDP Initialize
		MtoWChar(strSendIP, szSendIP);
		MtoWChar(strRecvIP, szRecvIP);

		// Set LCD Display 
		if (pIF->GetBoardID() >= 41 && pIF->GetBoardID() <= 49)
		{
			int nBrightness = LoadConfigNumber(strTemp, _T("DISPLAY_BRIGHTNESS"));
			int nDegree = LoadConfigNumber(strTemp, _T("DISPLAY_DEGREE"));
			int nX = LoadConfigNumber(strTemp, _T("DISPLAY_X"));
			int nY = LoadConfigNumber(strTemp, _T("DISPLAY_Y"));
			int nHor = LoadConfigNumber(strTemp, _T("DISPLAY_WIDTH"));
			int nVer = LoadConfigNumber(strTemp, _T("DISPLAY_HEIGHT"));
			IOSW_to_IOBOARD sData;
			memset(&sData, 0x00, sizeof(IOSW_to_IOBOARD));

			m_pIOSWDataManager->GetIOSW2IOBoardData(&sData, pIF->GetBoardID());

			sData.CH0_FREQ_28V = (unsigned short)nBrightness;
			sData.CH0_WIDTH_28V = (unsigned short)nDegree;
			sData.CH1_FREQ_28V = (unsigned short)nX;
			sData.CH1_WIDTH_28V = (unsigned short)nY;
			sData.CH2_FREQ_28V = (unsigned short)nHor;
			sData.CH2_WIDTH_28V = (unsigned short)nVer;

			m_pIOSWDataManager->SetIOSW2IOBoardData(sData, pIF->GetBoardID());
			
		}

		if (pIF->Initialize(szSendIP, nSendPort, szRecvIP, nRecvPort)) {
			m_pIOBoardInterfaceList->push_back(pIF);
		}
	}
	
	// Nexware Main Board Count Info.
	int nNexwareCount = LoadConfigNumber(_T("IOBOARD_INFO"), _T("NEXWARE_COUNT"));

	for (int i = 0; i < nNexwareCount; i++) {
		CString strTemp;
		strTemp.Format(_T("NEXWARE_%d"), i + 1);

		// Nexware Main Board Network Info.
		strSendIP = LoadConfigString(strTemp, _T("NEXWARE_IP"));
		strRecvIP = LoadConfigString(strTemp, _T("IOSW_IP"));
		nSendPort = LoadConfigNumber(strTemp, _T("NEXWARE_PORT"));
		nRecvPort = LoadConfigNumber(strTemp, _T("IOSW_PORT"));

		// Create Nexware Main Board Interface
		CNexwareIOBoardInterface* pIF = new CNexwareIOBoardInterface();
		pIF->SetDataManager(m_pIOSWDataManager);
		pIF->SetBoardID(LoadConfigNumber(strTemp, _T("NEXWARE_ID")));

		// UDP Initialize
		MtoWChar(strSendIP, szSendIP);
		MtoWChar(strRecvIP, szRecvIP);

		if (pIF->Initialize(szSendIP, nSendPort, szRecvIP, nRecvPort)) {
			m_pNexwareInterfaceList->push_back(pIF);
		}
	}

	// Trhottle HID Initialize
	if (!m_pThrottleInterface->Initialize()) {
		CIOSWLogger::Instance()->AddLog(LT_ERROR, "Throttle Quadrant HID를 찾을 수 없습니다.");
	}

	// IO Configuration Info.
	CString strValue;

	if (!GetProcessPath(strValue))
		return false;

	strValue.Append(_T("\\IOConfig.ini"));

	return LoadIOInformation(strValue);
}

bool CIOSWEngine::LoadIOInformation(LPCTSTR lpszFileName)
{
	std::ifstream iFileStream(lpszFileName);

	if (!iFileStream.is_open())
		return FALSE;

	int nThrottleID = LoadConfigNumber(_T("THROTTLE_INTERFACE"), _T("IOBOARD_ID"));
	int nBoardID = 0;

	while (true) {
		if (iFileStream.eof()) break;

		char szBuf[MAX_PATH];
		::memset(szBuf, 0x00, MAX_PATH);

		iFileStream >> szBuf;

		if (::strncmp(szBuf, "@@", 2) == 0)			// Board ID
		{
			char szPos[MAX_PATH];
			::memset(szPos, 0x00, MAX_PATH);

			iFileStream >> nBoardID >> szPos;
		}
		else if (::strncmp(szBuf, "**", 2) == 0)	// IO Information
		{
			int nDeviceNo = 0;
			int nIndex = 0;
			char szLRU[MAX_PATH];
			char szIO[MAX_PATH];
			char szKind[MAX_PATH];
			int nChannel = 0;
			int nMin = 0;
			int nMax = 0;

			::memset(szLRU, 0x00, MAX_PATH);
			::memset(szIO, 0x00, MAX_PATH);
			::memset(szKind, 0x00, MAX_PATH);

			iFileStream >> nDeviceNo >>  nIndex >> szLRU >> szIO >> szKind >> nChannel >> nMin >> nMax ;

			IOBOARD_INFORMATION stInfo;

			stInfo.nIndex = nIndex;

			if (::strcmp(szKind, "DI") == 0)
				stInfo.eKind = IK_DI;
			else if (::strcmp(szKind, "DO") == 0)
				stInfo.eKind = IK_DO;
			else if (::strcmp(szKind, "AI") == 0)
				stInfo.eKind = IK_AI;
			else if (::strcmp(szKind, "AO") == 0)
				stInfo.eKind = IK_AO;
			else if (::strcmp(szKind, "DIMMER") == 0)
				stInfo.eKind = IK_DIMMER;
			else 
				stInfo.eKind = IK_ETC;

			stInfo.nChannel = nChannel;
			stInfo.nMin = nMin;
			stInfo.nMax = nMax;
//			stInfo.nIOValue = 0;

			if (nThrottleID == nBoardID)
			{
				if (m_pThrottleInterface != NULL)
				{
					m_pThrottleInterface->SetBoardID(nBoardID);
					m_pThrottleInterface->SetBoardInformation(nIndex, stInfo);
				}
			}
			else
			{

				CANToIOBoardInterface* pIF = GetIOBoardInterface(nBoardID);

				if (pIF != NULL)
					pIF->SetBoardInformation(nIndex, stInfo);

			}
		}
	}

	return true;
}

CANToIOBoardInterface* CIOSWEngine::GetIOBoardInterface(const int& nBoardID)
{
	LIST_IOBOARDINTERFACE_ITR itr;

	for (itr = m_pIOBoardInterfaceList->begin(); itr != m_pIOBoardInterfaceList->end(); ++itr)
	{
		CANToIOBoardInterface * pIF = *itr;

		if (pIF != NULL)
		{
			if (pIF->GetBoardID() == nBoardID) {
				return pIF;
			}

		}
	}

	return NULL;
}

CNexwareIOBoardInterface* CIOSWEngine::GetNexwareInterface(const int& nBoardID)
{
	LIST_NEXWAREINTERFACE_ITR itr;

	for (itr = m_pNexwareInterfaceList->begin(); itr != m_pNexwareInterfaceList->end(); ++itr)
	{
		CNexwareIOBoardInterface * pIF = *itr;

		if (pIF != NULL)
		{
			if (pIF->GetBoardID() == nBoardID) {
				return pIF;
			}

		}
	}

	return NULL;
}

void CIOSWEngine::ClearAllIOBoardInterface()
{
	LIST_IOBOARDINTERFACE_ITR itr;

	for (itr = m_pIOBoardInterfaceList->begin(); itr != m_pIOBoardInterfaceList->end(); ++itr)
	{
		CANToIOBoardInterface * pIF = *itr;

		if (pIF != NULL) {
			delete pIF;
			pIF = NULL;
		}
	}

	m_pIOBoardInterfaceList->clear();
}

void CIOSWEngine::ClearAllNexwareInterface()
{
	LIST_NEXWAREINTERFACE_ITR itr;

	for (itr = m_pNexwareInterfaceList->begin(); itr != m_pNexwareInterfaceList->end(); ++itr)
	{
		CNexwareIOBoardInterface * pIF = *itr;

		if (pIF != NULL) {
			delete pIF;
			pIF = NULL;
		}
	}

	m_pNexwareInterfaceList->clear();
}

bool CIOSWEngine::InitEngine()
{
	bool bResult = false;

	m_pIOSWDataManager = new CIOSWDataManager();

	m_pIOSWDataManager->Initialize();

	bResult = LoadConfiguration();

	if (bResult) {
		CIOSWLogger::Instance()->AddLog(LT_INFORMATION, "I/O Software Initialize success!");
	}
	else{
		CIOSWLogger::Instance()->AddLog(LT_ERROR, "I/O Software Initialize fail!");
	}

	return bResult;
}

void CIOSWEngine::DoSystemOnOff(unsigned char cValue, bool bGUIOff)
{
	if (m_pIOSWDataManager != NULL)
	{
		m_pIOSWDataManager->DoSystemOnOff(cValue, bGUIOff);
	}
}

bool CIOSWEngine::StartIOSInterface()
{
	if (m_pIOSInterface == NULL)
		return false;

	return m_pIOSInterface->StartInterface();
}

bool CIOSWEngine::StopIOSInterface()
{
	if (m_pIOSInterface == NULL)
		return false;

	if (!m_pIOSInterface->IsInitialize())
		return false;

	return m_pIOSInterface->StopInterface();
}

bool CIOSWEngine::StartHostInterface()
{
	bool bResult = false;

	if (m_pHostInterface == NULL)
		return false;

	return m_pHostInterface->StartInterface();
}

bool CIOSWEngine::StopHostInterface()
{
	if (m_pHostInterface == NULL)
		return false;

	if (!m_pHostInterface->IsInitialize())
		return false;

	return m_pHostInterface->StopInterface();

}

bool CIOSWEngine::StartGUIInterface()
{
	if (m_pGUIInterface == NULL)
		return false;

	return m_pGUIInterface->StartInterface();
}

bool CIOSWEngine::StopGUIInterface()
{
	if (m_pGUIInterface == NULL)
		return false;

	if (!m_pGUIInterface->IsInitialize())
		return false;

	return m_pGUIInterface->StopInterface();

}

bool CIOSWEngine::StartPowerInterface(const POWER_ON_OFF_TYPE eOnOff)
{
	CString strSendIP;
	CString strRecvIP;
	int nSendPort = 0;
	int nRecvPort = 0;

	char szSendIP[16];
	char szRecvIP[16];

	memset(&szSendIP, 0x00, sizeof(szSendIP));
	memset(&szRecvIP, 0x00, sizeof(szRecvIP));

	m_pPowerInterface = new CIOPowerInterface();

	if (m_pPowerInterface == NULL)
		return false;

	// Initialize Power
	m_pPowerInterface->SetDataManager(m_pIOSWDataManager);
	m_pPowerInterface->SetPower(eOnOff);

	// IOS Network info. 
	strSendIP = LoadConfigString(_T("PWR_INTERFACE"), _T("PWR_IP"));
	strRecvIP = LoadConfigString(_T("PWR_INTERFACE"), _T("IOSW_IP"));
	nSendPort = LoadConfigNumber(_T("PWR_INTERFACE"), _T("PWR_PORT"));
	nRecvPort = LoadConfigNumber(_T("PWR_INTERFACE"), _T("IOSW_PORT"));

	// UDP Initialize
	MtoWChar(strSendIP, szSendIP);
	MtoWChar(strRecvIP, szRecvIP);

	if (!m_pPowerInterface->Initialize(szSendIP, nSendPort, szRecvIP, nRecvPort))
		return false;

	return m_pPowerInterface->StartInterface();
}

bool CIOSWEngine::StopPowerInterface()
{
	if (m_pPowerInterface == NULL)
		return false;

	if (!m_pPowerInterface->IsInitialize())
		return false;

	if (!m_pPowerInterface->StopInterface())
		return false;

	delete m_pPowerInterface;
	m_pPowerInterface = NULL;

	return true;

}
bool CIOSWEngine::StartIOBoardInterface()
{
	if (m_pIOBoardInterfaceList == NULL)
		return false;

	LIST_IOBOARDINTERFACE_ITR itr;
	bool bResult = false;

	for (itr = m_pIOBoardInterfaceList->begin(); itr != m_pIOBoardInterfaceList->end(); ++itr)
	{
		CANToIOBoardInterface * pIF = *itr;

		if (pIF != NULL) {
			bResult = pIF->StartInterface();
		}
	}

	return bResult;
}

bool CIOSWEngine::StopIOBoardInterface()
{
	if (m_pIOBoardInterfaceList == NULL)
		return false;

	LIST_IOBOARDINTERFACE_ITR itr;
	bool bResult = false;

	for (itr = m_pIOBoardInterfaceList->begin(); itr != m_pIOBoardInterfaceList->end(); ++itr)
	{
		CANToIOBoardInterface * pIF = *itr;

		if (pIF != NULL) {
			bResult = pIF->StopInterface();
		}
	}

	return bResult;
}

bool CIOSWEngine::StartThrottleInterface()
{
	if (m_pThrottleInterface == NULL)
		return false;

	if (!m_pThrottleInterface->IsInitialize())
		return false;

	return m_pThrottleInterface->StartInterface();
}

bool CIOSWEngine::StopThrottleInterface()
{
	if (m_pThrottleInterface == NULL)
		return false;

	if (!m_pThrottleInterface->IsInitialize())
		return false;

	return m_pThrottleInterface->StopInterface();
}

bool CIOSWEngine::StartNexwareInterface()
{
	if (m_pNexwareInterfaceList == NULL)
		return false;

	LIST_NEXWAREINTERFACE_ITR itr;
	bool bResult = false;

	for (itr = m_pNexwareInterfaceList->begin(); itr != m_pNexwareInterfaceList->end(); ++itr)
	{
		CNexwareIOBoardInterface * pIF = *itr;

		if (pIF != NULL) {
			bResult = pIF->StartInterface();
		}
	}

	return bResult;
}

bool CIOSWEngine::StopNexwareInterface()
{
	if (m_pNexwareInterfaceList == NULL)
		return false;

	LIST_NEXWAREINTERFACE_ITR itr;
	bool bResult = false;

	for (itr = m_pNexwareInterfaceList->begin(); itr != m_pNexwareInterfaceList->end(); ++itr)
	{
		CNexwareIOBoardInterface * pIF = *itr;

		if (pIF != NULL) {
			bResult = pIF->StopInterface();
		}
	}

	return bResult;
}