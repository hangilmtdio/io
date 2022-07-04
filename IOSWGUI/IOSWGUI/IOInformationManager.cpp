#include "stdafx.h"
#include <fstream>
#include "IOSWUtilities.h"
#include "IOInformationManager.h"

CIODeviceInfo::CIODeviceInfo()
{
	m_pIOInfoList = new LIST_IOINFO;
	m_nDeviceID = 0;
	m_nBoardID =  0;
	m_eDevicePos = DP_UNKNOWN;
	m_nImageXPos = 0;
	m_nImageYPos = 0;
	memset(m_szDeviceName, 0x00, 100);
}

CIODeviceInfo::~CIODeviceInfo()
{
	if (m_pIOInfoList != NULL) {
		ClearAllIOInfo();

		delete m_pIOInfoList;
		m_pIOInfoList = NULL;
	}
}

bool CIODeviceInfo::InsertIOInfo(const sIOInformation& sInfo)
{
	if (m_pIOInfoList == NULL) 
		return FALSE;

	sIOInformation* psInfo = new sIOInformation(sInfo);
	
	m_pIOInfoList->push_back(psInfo);

	return TRUE;
}

void CIODeviceInfo::ClearAllIOInfo()
{
	LIST_IOINFO_ITR itr;

	for (itr = m_pIOInfoList->begin(); itr != m_pIOInfoList->end(); ++itr)
	{
		sIOInformation* pInfo = *itr;
		delete pInfo, pInfo = NULL;
	}

	m_pIOInfoList->clear();
}


void CIODeviceInfo::SetDeviceName(CString strDeviceName)
{
	CIOSWUtilities::MtoWChar(strDeviceName, m_szDeviceName);
}

void CIODeviceInfo::GetDeviceName(CString& strDeviceName)
{
	strDeviceName = m_szDeviceName;
}

sIOInformation* CIODeviceInfo::GetIOInfo(const int& nIndex)
{
	LIST_IOINFO_ITR itr;

	for (itr = m_pIOInfoList->begin(); itr != m_pIOInfoList->end(); ++itr)
	{
		sIOInformation * pInfo = *itr;

		if (pInfo != NULL)
		{
			if (pInfo->nIndex == nIndex) {
				return pInfo;
			}
		}
	}

	return NULL;
}

void CIODeviceInfo::GetIOIndexList(LIST_ID* pIDList)
{
	LIST_IOINFO_ITR itr;

	for (itr = m_pIOInfoList->begin(); itr != m_pIOInfoList->end(); ++itr)
	{
		sIOInformation * pInfo = *itr;

		if (pInfo != NULL)
		{
			int nID = pInfo->nIndex;
			pIDList->push_back(nID);
		}
	}
}

void CIODeviceInfo::GetIOIndexList(LIST_ID* pIDList, IO_KIND eKind)
{
	LIST_IOINFO_ITR itr;

	for (itr = m_pIOInfoList->begin(); itr != m_pIOInfoList->end(); ++itr)
	{
		sIOInformation * pInfo = *itr;

		if (pInfo != NULL)
		{
			if (pInfo->eKind == eKind) {
				int nID = pInfo->nIndex;
				pIDList->push_back(nID);
			}
		}
	}
}


CIODeviceInformationManager::CIODeviceInformationManager()
{
	m_pDeviceInfoList = new LIST_DEVICEINFO;
}


CIODeviceInformationManager::~CIODeviceInformationManager()
{
	if (m_pDeviceInfoList != NULL) {

		ClearAllIODeviceInfo();

		delete m_pDeviceInfoList;
		m_pDeviceInfoList = NULL;
	}
}

void CIODeviceInformationManager::ClearAllIODeviceInfo()
{
	LIST_DEVICEINFO_ITR itr;

	for (itr = m_pDeviceInfoList->begin(); itr != m_pDeviceInfoList->end(); ++itr)
	{
		CIODeviceInfo * pInfo = *itr;

		if (pInfo != NULL) {
			delete pInfo;
			pInfo = NULL;
		}
	}

	m_pDeviceInfoList->clear();
}

bool CIODeviceInformationManager::LoadDeviceInfo()
{
	CString strPath;

	if (!CIOSWUtilities::GetProcessPath(strPath))
		return false;

	strPath.Append(_T("\\IOConfig.ini"));

	std::ifstream iFileStream(strPath);

	if (!iFileStream.is_open())
		return false;

	
	int nBoardID = 0;
	DEVICE_POSITION eDevicePos = DP_UNKNOWN;

	while (true) {
		if (iFileStream.eof()) break;

		char szBuf[MAX_PATH];
		::memset(szBuf, 0x00, MAX_PATH);

		iFileStream >> szBuf;

		if (::strncmp(szBuf, "@@", 2) == 0)			// Board ID
		{
			char szDevicePos[MAX_PATH];

			iFileStream >> nBoardID >> szDevicePos;

			if (::strcmp(szDevicePos, "LEFT") == 0)
				eDevicePos = DP_LEFT;
			else if (::strcmp(szDevicePos, "MAIN") == 0)
				eDevicePos = DP_MAIN;
			else if (::strcmp(szDevicePos, "RIGHT") == 0)
				eDevicePos = DP_RIGHT;
			else
				eDevicePos = DP_UNKNOWN;
		}
		else if (::strncmp(szBuf, "**", 2) == 0)	// IO Information
		{
			int nDeviceID = 0;
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

			iFileStream >> nDeviceID >> nIndex >> szLRU >> szIO >> szKind >> nChannel >> nMin >> nMax;

			CIODeviceInfo* pInfo = GetDeivceInfo(nDeviceID);
			bool bAddInfoFlag = false;

			if (pInfo == NULL) 
			{
				pInfo = new CIODeviceInfo();

				pInfo->SetDeviceID(nDeviceID);
				pInfo->SetDeviceName(CString(szLRU));
				pInfo->SetDevicePosition(eDevicePos);
				pInfo->SetBoardID(nBoardID);

				bAddInfoFlag = true;
			}

			sIOInformation sInfo;

			sInfo.nIndex = nIndex;

			if (::strcmp(szKind, "DI") == 0)
				sInfo.eKind = IK_DI;
			else if (::strcmp(szKind, "DO") == 0)
				sInfo.eKind = IK_DO;
			else if (::strcmp(szKind, "AI") == 0)
				sInfo.eKind = IK_AI;
			else if (::strcmp(szKind, "AO") == 0)
				sInfo.eKind = IK_AO;
			else if (::strcmp(szKind, "DIMMER") == 0)
				sInfo.eKind = IK_DIMMER;
			else if (::strcmp(szKind, "AI_SR") == 0)
				sInfo.eKind = IK_AI_SR;
			else if (::strcmp(szKind, "AO_IDC") == 0)
				sInfo.eKind = IK_AO_IDC;
			else
				sInfo.eKind = IK_UNKNOWN;


			sInfo.nChannel = nChannel;
			sInfo.nMin = nMin;
			sInfo.nMax = nMax;
			memcpy(sInfo.szIOName, szIO, 100);

			pInfo->InsertIOInfo(sInfo);

			if (bAddInfoFlag) {
				m_pDeviceInfoList->push_back(pInfo);
			}
				
		}
			
	}

	return true;
}

bool CIODeviceInformationManager::LoadDeviceImageInfo()
{
	CString strPath;

	if (!CIOSWUtilities::GetProcessPath(strPath))
		return false;

	strPath.Append(_T("\\LRUImageConfig.ini"));

	std::ifstream iFileStream(strPath);

	if (!iFileStream.is_open())
		return false;


	while (true) {
		if (iFileStream.eof()) break;

		char szBuf[MAX_PATH];
		::memset(szBuf, 0x00, MAX_PATH);

		iFileStream >> szBuf;

		if (::strncmp(szBuf, "**", 2) == 0)	// Image Information
		{
			int nDeviceID = 0;
			int nX = 0;
			int nY = 0;

			iFileStream >> nDeviceID >> nX >> nY;

			CIODeviceInfo* pInfo = GetDeivceInfo(nDeviceID);

			if (pInfo != NULL) {
				pInfo->SetDeviceImageXPosition(nX);
				pInfo->SetDeviceImageYPosition(nY);
			}

		}
	}

	return true;
}


CIODeviceInfo* CIODeviceInformationManager::GetDeivceInfo(const int& nDeviceID)
{
	LIST_DEVICEINFO_ITR itr;

	for (itr = m_pDeviceInfoList->begin(); itr != m_pDeviceInfoList->end(); ++itr)
	{
		CIODeviceInfo * pInfo = *itr;

		if (pInfo != NULL)
		{
			if (pInfo->GetDeviceID() == nDeviceID) {
				return pInfo;
			}
		}
	}

	return NULL;
}

void CIODeviceInformationManager::GetDeviceIDList(LIST_ID* pIDList)
{
	LIST_DEVICEINFO_ITR itr;

	for (itr = m_pDeviceInfoList->begin(); itr != m_pDeviceInfoList->end(); ++itr)
	{
		CIODeviceInfo * pInfo = *itr;

		if (pInfo != NULL)
		{
			int nID = pInfo->GetDeviceID();
			pIDList->push_back(nID);
		}
	}

}

void  CIODeviceInformationManager::GetDeviceIDList(LIST_ID* pIDList, DEVICE_POSITION ePosition)
{
	LIST_DEVICEINFO_ITR itr;

	for (itr = m_pDeviceInfoList->begin(); itr != m_pDeviceInfoList->end(); ++itr)
	{
		CIODeviceInfo * pInfo = *itr;

		if (pInfo != NULL)
		{
			if (pInfo->GetDevicePosition() == ePosition) {

				int nID = pInfo->GetDeviceID();
				pIDList->push_back(nID);

			}
		}
	}
}