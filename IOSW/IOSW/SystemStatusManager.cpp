#include "stdafx.h"
#include "SystemStatusManager.h"
#include <Windows.h>
#include "IOSWUtility.h"


static float CalculateCPULoad(unsigned long long idleTicks, unsigned long long totalTicks)
{
	static unsigned long long _previousTotalTicks = 0;
	static unsigned long long _previousIdleTicks = 0;

	unsigned long long totalTicksSinceLastTime = totalTicks - _previousTotalTicks;
	unsigned long long idleTicksSinceLastTime = idleTicks - _previousIdleTicks;

	float ret = 1.0f - ((totalTicksSinceLastTime > 0) ? ((float)idleTicksSinceLastTime) / totalTicksSinceLastTime : 0);

	_previousTotalTicks = totalTicks;
	_previousIdleTicks = idleTicks;
	return ret;
}

static unsigned long long FileTimeToInt64(const FILETIME & ft) 
{ 
	return (((unsigned long long)(ft.dwHighDateTime)) << 32) | ((unsigned long long)ft.dwLowDateTime); 
}


CSystemStatusManager::CSystemStatusManager()
{
	m_stSystemStatusInfo.fCPUUsageAmount = 0.0f;
	m_stSystemStatusInfo.fDiskUsageAmount = 0.0f;
	m_stSystemStatusInfo.fMemoryUsageAmount = 0.0f;

}


CSystemStatusManager::~CSystemStatusManager()
{

}

void CSystemStatusManager::UpdateSystemStatusInfo(SYSTEMSTATUSINFO* psInfo)
{
	UpdateMemoryStatusInfo();
	UpdateDiskStatusInfo();
	UpdateCPUStatusInfo();

	memcpy(psInfo, &m_stSystemStatusInfo, sizeof(SYSTEMSTATUSINFO));
}

void CSystemStatusManager::UpdateMemoryStatusInfo()
{
	MEMORYSTATUSEX  MemInfo;
	
	MemInfo.dwLength = sizeof(MEMORYSTATUSEX);
	GlobalMemoryStatusEx(&MemInfo);

	m_stSystemStatusInfo.fMemoryUsageAmount = (float) MemInfo.dwMemoryLoad;
}

void CSystemStatusManager::UpdateCPUStatusInfo()
{
	FILETIME idleTime, kernelTime, userTime;

	float fUsage = 0.0f;
	
	if (GetSystemTimes(&idleTime, &kernelTime, &userTime)) {
		fUsage = CalculateCPULoad(FileTimeToInt64(idleTime), FileTimeToInt64(kernelTime) + FileTimeToInt64(userTime));
		m_stSystemStatusInfo.fCPUUsageAmount = fUsage * 100;
	}
}

void CSystemStatusManager::UpdateDiskStatusInfo()
{
	ULARGE_INTEGER uiFreeBytesAvailableToCaller;
	ULARGE_INTEGER uiTotalNumberOfBytes;
	ULARGE_INTEGER uiTotalNumberBytesOfFree;

	if (GetDiskFreeSpaceEx(L"C:\\", &uiFreeBytesAvailableToCaller, &uiTotalNumberOfBytes, &uiTotalNumberBytesOfFree)){
		m_stSystemStatusInfo.fDiskUsageAmount =((GetByte(uiTotalNumberOfBytes) - GetByte(uiTotalNumberBytesOfFree)) / GetByte(uiTotalNumberOfBytes)) * 100;
	}
}
