#include "stdafx.h"
#include "IOSWRWLock.h"


CIOSWRWLock::CIOSWRWLock():	
	m_nReaderCount(0), 
	m_hWriteMutex(NULL), 
	m_hNoReadersEvent(NULL)
{
	m_hWriteMutex = CreateMutex(NULL, FALSE, NULL);
	m_hNoReadersEvent = CreateEvent(NULL, TRUE, TRUE, NULL);
}

CIOSWRWLock::CIOSWRWLock(const CIOSWRWLock &cReadWriteLock)
{
}

const CIOSWRWLock& CIOSWRWLock::operator=(const CIOSWRWLock &cReadWriteLock)
{
	return *this;
}

CIOSWRWLock::~CIOSWRWLock()
{
	LockWriter(); // This will wait for finishing of all read/write operation.
	UnlockWriter();
	CloseHandle(m_hWriteMutex);
	CloseHandle(m_hNoReadersEvent);
}

void CIOSWRWLock::LockReader()
{
	WaitForSingleObject(m_hWriteMutex, INFINITE); // This will acquire write mutex
	IncrementReaderCount();
	ReleaseMutex(m_hWriteMutex); // Release write mutex
}

void CIOSWRWLock::UnlockReader()
{
	// Decrement number of readers.
	WaitForSingleObject(m_hWriteMutex, INFINITE); // This will acquire write mutex
	DecrementReaderCount();
	ReleaseMutex(m_hWriteMutex); // Release write mutex

}

void CIOSWRWLock::LockWriter()
{
	HANDLE handles[] = { m_hWriteMutex, m_hNoReadersEvent };
	WaitForMultipleObjects(2, handles, TRUE, INFINITE);
}

void CIOSWRWLock::UnlockWriter()
{
	// Release Write mutex.
	ReleaseMutex(m_hWriteMutex);
}

void CIOSWRWLock::IncrementReaderCount()
{
	m_nReaderCount++;
	// Reset the no readers event.
	ResetEvent(m_hNoReadersEvent);
}

void CIOSWRWLock::DecrementReaderCount()
{
	m_nReaderCount--;
	// Are all readers out?
	if (m_nReaderCount <= 0){
		// Set the no readers event.
		SetEvent(m_hNoReadersEvent);
	}
}