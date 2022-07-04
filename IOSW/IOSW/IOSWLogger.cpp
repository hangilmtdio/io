#include "stdafx.h"
#include "IOSWLogger.h"
#include "IOSWUtility.h"
#include <iostream>
#include <fstream>

CIOSWLogger* CIOSWLogger::g_Instance = NULL;

CIOSWLogger* CIOSWLogger::Instance()
{
	if (g_Instance == NULL) {
		g_Instance = new CIOSWLogger;
	}

	return g_Instance;
}

void CIOSWLogger::DestroyInstance()
{
	if (g_Instance != NULL){
		delete g_Instance;
		g_Instance = NULL;
	}
}

CIOSWLogger::CIOSWLogger()
{
}


CIOSWLogger::~CIOSWLogger()
{
}


bool CIOSWLogger::AddLog(const LogType& eType, string strContents)
{
	CString strPath;
	CString strLogPath;

	strPath = LoadConfigString(_T("LOG"), _T("PATH"));
	
	string strCurDate = GetCurrentDateString();
	//strLogPath.Format(_T("%s\\[IOSW LOG]_%s.log"), strPath, CA2CT(strCurDate.c_str()));
	strLogPath.Format(_T("%s\\[IOSW LOG]_%s.log"), strPath, strCurDate.c_str());

	m_rwLock.LockWriter();

	ofstream oFileStream(strLogPath, std::ios::out | std::ios::app);

	if (!oFileStream.is_open())
		return false;

	std::string strCurTime = GetCurrentTimeString();

	oFileStream << strCurTime << " " << eType << " " << strContents << std::endl;
	oFileStream.close();

	m_rwLock.UnlockWriter();

	return true;
}

string CIOSWLogger::GetCurrentDateString() {
	time_t now = time(NULL);
	struct tm tstruct;
	char buf[40];
	tstruct = *localtime(&now);
	//format: day YYYY-MM-DD
	strftime(buf, sizeof(buf), "%Y_%m_%d", &tstruct);
	return buf;
}

string CIOSWLogger::GetCurrentTimeString() {
	time_t now = time(NULL);
	struct tm tstruct;
	char buf[40];
	tstruct = *localtime(&now);
	//format: HH:mm:ss
	strftime(buf, sizeof(buf), "%X", &tstruct);
	return buf;
}