#pragma once

#include <Windows.h>
#include <process.h>
#include <string>
#include "IOSWRWLock.h"

// Log Type
typedef enum _LogType
{
	LT_INFORMATION = 0,
	LT_ERROR,
	LT_WARNING,
	LT_COUNT
} LogType;

using namespace std;

class CIOSWLogger
{
public:
	CIOSWLogger();
	~CIOSWLogger();

	//////////////////////////////////////////////////////////////////////////
	// Operatins
	static CIOSWLogger* Instance();
	static void DestroyInstance();

	bool AddLog(const LogType& eType, string strContents);

protected:
	string GetCurrentDateString();
	string GetCurrentTimeString();

private:
	//////////////////////////////////////////////////////////////////////////
	// Attributes
	static CIOSWLogger* g_Instance; // Singleton object
	CIOSWRWLock			m_rwLock;
	
};

