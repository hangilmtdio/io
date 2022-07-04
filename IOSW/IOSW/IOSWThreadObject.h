#pragma once

typedef void(*thread_function)(void * arg);

class CIOSWThreadObject
{
public:
	CIOSWThreadObject();
	~CIOSWThreadObject();
	//////////////////////////////////////////////////////////////////////////
	// Operations
public:
	// Thread Create
	bool   Create(thread_function func, void * lpParam); 

	// Thread Destroy
	void   Destroy();

	// Thread Suspend
	void   Suspend();

	// Thread Resume
	void   Resume();         

	void   Join();

	UINT32   GetPriority();
	UINT32   SetPriority(UINT32 priority);

	static unsigned long __stdcall _InternalThreadFunction(void* arg);

	UINT32   InternalThreadFunction();

	//////////////////////////////////////////////////////////////////////////
	// Attributes
protected:
	HANDLE             m_threadHandle;
	unsigned long      m_threadId;
	thread_function    m_function;
	void *             m_arg;
};

