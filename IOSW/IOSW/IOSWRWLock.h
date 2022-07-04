#pragma once


class CIOSWRWLock
{
public:
	CIOSWRWLock();
	virtual ~CIOSWRWLock();

	//////////////////////////////////////////////////////////////////////////
	// Operatins
	void LockReader();
	void UnlockReader();
	void LockWriter();
	void UnlockWriter();
private:
	CIOSWRWLock(const CIOSWRWLock &cReadWriteLock);
	const CIOSWRWLock& operator=(const CIOSWRWLock &cReadWriteLock);
	void IncrementReaderCount();
	void DecrementReaderCount();

	//////////////////////////////////////////////////////////////////////////
	// Attributes
	HANDLE m_hWriteMutex;
	HANDLE m_hNoReadersEvent;
	int m_nReaderCount;

};

