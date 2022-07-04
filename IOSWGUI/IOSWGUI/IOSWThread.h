#pragma once


class CIOSWThread
{
public:
	CIOSWThread();
	virtual ~CIOSWThread();

	//////////////////////////////////////////////////////////////////////////
	// Operations
public:
	BOOL StartThread();
	BOOL EndThread();
	BOOL KillThread();

	virtual DWORD ThreadProc();

	//////////////////////////////////////////////////////////////////////////
	// Attributes
protected:
	HANDLE   m_hThread;
	DWORD   m_dwThreadID;

	BOOL    m_bEndThread;

};

