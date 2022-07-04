#pragma once

#include <string>
#include <list>
#include "IOSWThread.h"

using namespace std;

// Log Type
typedef enum _LogType
{
	LT_INFORMATION = 0,
	LT_ERROR,
	LT_WARNING,
	LT_COUNT
} LogType;


// Log Type 문자열
static LPCTSTR alpszLogType[] =
{
	_T("정보"),
	_T("오류"),
	_T("경고"),
};

typedef struct _IOSWEventLog
{
	int			nID;
	LogType		eType;
	char		szTime[12];
	char		szContents[MAX_PATH];
} IOSWEventLog;

typedef list<IOSWEventLog*>		LOGEVENT_LIST;
typedef LOGEVENT_LIST::iterator	LOGEVENT_LIST_ITR;

class CIOSWLogManager : public CIOSWThread
{
public:
	CIOSWLogManager();
	~CIOSWLogManager();

	//////////////////////////////////////////////////////////////////////////
	// Operations
	
	void SetLogWnd(CWnd* pWnd);
	bool SetMonitoringLogFile(string strFilePath);
	bool StartMonitoring();
	bool StopMonitoring();

	LOGEVENT_LIST* GetEventLogList() { return m_pLogEventList; }
protected:
	DWORD ThreadProc();
	void  LogFileChaned();
	bool LoadLogFile();
	//////////////////////////////////////////////////////////////////////////
	// Attributes
private:
	CWnd*		m_pLogWnd;
	LOGEVENT_LIST*	m_pLogEventList;
	int			m_nLogIndex;

	string		m_strFilePath;
	string		m_strFileDir;

	_WIN32_FILE_ATTRIBUTE_DATA m_fileAttData;
	HANDLE m_dwChangeHandles[2];

};

