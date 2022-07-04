#include "stdafx.h"
#include "IOSWThread.h"


CIOSWThread::CIOSWThread()
{
	m_hThread = NULL;
	m_dwThreadID = 0;
	m_bEndThread = FALSE;
}


CIOSWThread::~CIOSWThread()
{
	EndThread();
}

static DWORD WINAPI CThreadProc(CIOSWThread* pThis)
{
	return pThis->ThreadProc();
}

BOOL CIOSWThread::StartThread()
{
	if (m_hThread != NULL)
		EndThread();

	m_hThread = ::CreateThread(NULL,
							   0,
							  (LPTHREAD_START_ROUTINE)CThreadProc,
							  this,
							  0,
							  (LPDWORD)&m_dwThreadID);


	if (m_hThread == NULL) {
		return FALSE;
	}

	return TRUE;
}

BOOL CIOSWThread::EndThread()
{
	if (m_hThread != NULL)
	{
		m_bEndThread = TRUE;

		::WaitForSingleObject(m_hThread, INFINITE);
		::CloseHandle(m_hThread);

		m_hThread = NULL;

		return TRUE;
	}

	return FALSE;
}

BOOL CIOSWThread::KillThread()
{
	if (m_hThread != NULL)
	{
		::TerminateThread(m_hThread, 0);
		return TRUE;
	}

	return FALSE;
}

DWORD CIOSWThread::ThreadProc()
{
	return 0;
}
