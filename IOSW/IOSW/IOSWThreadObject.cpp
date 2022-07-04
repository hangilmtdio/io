#include "stdafx.h"
#include "IOSWThreadObject.h"

UINT32 priority_values[] = {
	-15,
	-2,
	-1,
	0,
	1,
	2,
	15
};

const UINT32 kNumPriorities = sizeof(priority_values) / sizeof(INT32);


CIOSWThreadObject::CIOSWThreadObject()
{
	m_arg = NULL;
	m_function = NULL;
	m_threadHandle = NULL;
	m_threadId = 0;
}


CIOSWThreadObject::~CIOSWThreadObject()
{
	if (m_threadHandle)
	{
		CloseHandle(m_threadHandle);
		m_threadHandle = NULL;
	}
}

unsigned long __stdcall CIOSWThreadObject::_InternalThreadFunction(void* arg)
{
	CIOSWThreadObject* thread = (CIOSWThreadObject*)arg;

	return thread->InternalThreadFunction();
}

UINT32 CIOSWThreadObject::InternalThreadFunction()
{
	m_function(m_arg);

	return 0;
}

bool CIOSWThreadObject::Create(thread_function func, void * lpParam)
{
	m_arg = lpParam;
	m_function = func;

	m_threadHandle = ::CreateThread( NULL,
										0,
										_InternalThreadFunction,
										this,
										0,
										&m_threadId);

	if (m_threadHandle)
		return true;

	return false;
}

void CIOSWThreadObject::Destroy()
{
	TerminateThread(m_threadHandle, 0);
}

void CIOSWThreadObject::Suspend()
{
	SuspendThread(m_threadHandle);
}

void CIOSWThreadObject::Resume()
{
	ResumeThread(m_threadHandle);
}

void CIOSWThreadObject::Join()
{
	WaitForSingleObject(m_threadHandle, INFINITE);
}

UINT32 CIOSWThreadObject::GetPriority()
{
	INT32 priority = GetThreadPriority(m_threadHandle);

	for (INT32 i = 0; i < kNumPriorities; i++)
	{
		if (priority_values[i] == (UINT32)priority)
		{
			priority = i;
			break;
		}
	}

	return priority;
}

UINT32 CIOSWThreadObject::SetPriority(UINT32 priority)
{
	INT32 old = GetThreadPriority(m_threadHandle);

	SetThreadPriority(m_threadHandle, priority_values[priority]);

	for (INT32 i = 0; i < kNumPriorities; i++)
	{
		if (priority_values[i] == (UINT32)old)
		{
			old = i;
			break;
		}
	}

	return old;
}
