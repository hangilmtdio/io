#pragma once


#include <iostream>
#include "IOSW_Interface.h"


class CSystemStatusManager
{
public:
	CSystemStatusManager();
	~CSystemStatusManager();

	//////////////////////////////////////////////////////////////////////////
	// Operations
	void	UpdateSystemStatusInfo(SYSTEMSTATUSINFO* psInfo);

protected:
	void	UpdateMemoryStatusInfo();
	void	UpdateCPUStatusInfo();
	void	UpdateDiskStatusInfo();

private:
	
	//////////////////////////////////////////////////////////////////////////
	// Attributes
private:
	SYSTEMSTATUSINFO			m_stSystemStatusInfo;

};

