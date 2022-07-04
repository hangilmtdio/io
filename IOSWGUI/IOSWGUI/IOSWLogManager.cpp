#include "stdafx.h"
#include "IOSWLogManager.h"
#include "IOSWUtilities.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <time.h>
#include "CommonDefine.h"


CIOSWLogManager::CIOSWLogManager()
{
	m_pLogWnd = NULL;
	m_pLogEventList = NULL;
	m_nLogIndex = 0;

	m_pLogEventList = new LOGEVENT_LIST;
}


CIOSWLogManager::~CIOSWLogManager()
{
	//StopMonitoring();

	if (m_pLogEventList != NULL)
	{
		for (LOGEVENT_LIST_ITR itr = m_pLogEventList->begin(); itr != m_pLogEventList->end(); ++itr)
		{
			IOSWEventLog* pLog = *itr;

			if (pLog) {
				delete pLog, pLog = NULL;
			}
		}

		m_pLogEventList->clear();

		delete m_pLogEventList;
		m_pLogEventList = NULL;
	}
}

void CIOSWLogManager::SetLogWnd(CWnd* pWnd)
{
	ASSERT(pWnd);
	m_pLogWnd = pWnd;
}

bool CIOSWLogManager::SetMonitoringLogFile(string strFilePath)
{
	if (strFilePath.size() == 0)
		return false;

	int nPos = strFilePath.rfind("\\");

	if (nPos == -1)	{
		nPos = strFilePath.rfind("/");
		if (nPos == -1)
			return false;
	}

	m_strFileDir = strFilePath.substr(0, nPos + 1);
	m_strFilePath = strFilePath;

	if (!GetFileAttributesEx(CA2CT(m_strFilePath.c_str()), GetFileExInfoStandard, (void*)&m_fileAttData))
		return false;

	return true;
}

bool CIOSWLogManager::StartMonitoring()
{
	LoadLogFile();

	StartThread();
	
	return true;
}

bool CIOSWLogManager::StopMonitoring()
{
	if (!ReleaseSemaphore(m_dwChangeHandles[1], 1, NULL)){
		return false;
	}

	::Sleep(100);

	//EndThread();

	return true;
}

bool CIOSWLogManager::LoadLogFile()
{
//	return false;
	std::ifstream iFileStream(m_strFilePath);

	if (!iFileStream.is_open())
		return false;

	int nLogIdx = 0;

	while (true)
	{

		char szTime[12];
		char szContents[MAX_PATH];
//		string strTime;
//		string strContents;
		int  nType;

		::memset(szTime, 0x00, 12);
		::memset(szContents, 0x00, MAX_PATH);

		iFileStream >> szTime >> nType ;
		iFileStream.get(szContents, MAX_PATH);

		if (iFileStream.eof())
			break;


		nLogIdx++;

		if (nLogIdx > m_nLogIndex) 
		{
			IOSWEventLog* pLogEvent = NULL;
			pLogEvent = new IOSWEventLog();
			int nSize = sizeof(szContents);
			::memcpy(pLogEvent->szTime, szTime, sizeof(szTime));
			::memcpy(pLogEvent->szContents, szContents, sizeof(szContents));
			pLogEvent->nID = nLogIdx;
			pLogEvent->eType = (LogType)nType;
			m_nLogIndex = nLogIdx;

			m_pLogEventList->push_back(pLogEvent);
		}
	}

	iFileStream.close();

	if (m_pLogWnd)
		m_pLogWnd->PostMessage(UM_UPDATE_LOGEVENT, 0, 0);

	return true;
}

void CIOSWLogManager::LogFileChaned()
{
	TRACE(_T("Log 파일이 변경되었습니다. \n"));
	LoadLogFile();
}

DWORD CIOSWLogManager::ThreadProc()
{
	bool bResult = 1;
	DWORD dwWaitStatus;
	_WIN32_FILE_ATTRIBUTE_DATA fileAttData;
//	HANDLE dwChangeHandles;

	m_dwChangeHandles[0] = FindFirstChangeNotification(CA2CT(m_strFileDir.c_str()), FALSE, FILE_NOTIFY_CHANGE_LAST_WRITE);
	
	if (m_dwChangeHandles[0] == INVALID_HANDLE_VALUE){
		DWORD dError = GetLastError();
		return -1;
	}

	m_dwChangeHandles[1] = CreateSemaphore(NULL, 0, 1, NULL);

	if (m_dwChangeHandles[1] == NULL)
		return 0;


	while (true)
	{
		dwWaitStatus = WaitForMultipleObjects(2, m_dwChangeHandles, FALSE, INFINITE);

		switch (dwWaitStatus)
		{
		case WAIT_OBJECT_0:
			GetFileAttributesEx(CA2CT(m_strFilePath.c_str()), GetFileExInfoStandard, (void*)&fileAttData);

			if (CompareFileTime(&fileAttData.ftLastWriteTime, &m_fileAttData.ftLastWriteTime) != 0)
			{
				LogFileChaned();

				m_fileAttData = fileAttData;
			}

			FindNextChangeNotification(m_dwChangeHandles[0]);

			break;
		case WAIT_OBJECT_0 + 1:
			m_bEndThread = TRUE;
			break;
		default:
			break;
		}

		Sleep(1);

		if (m_bEndThread == TRUE) break;   // Thread 종료 조건
	}

	FindCloseChangeNotification(m_dwChangeHandles[0]);

	return bResult;
}
