#pragma once

#include "IOSWThread.h"
#include "UDPSocket.h"
#include "IOSWDataManager.h"
#include "SystemStatusManager.h"

class CIOSWGUIInterface : public CIOSWThread
{
public:
	CIOSWGUIInterface();
	~CIOSWGUIInterface();

	//////////////////////////////////////////////////////////////////////////
	// Operations
	bool	Initialize(char* chGUIAddr, const int& nGUIPort, char* chIOSWAddr, const int& nIOSWPort);
	void	SetDataManager(CIOSWDataManager* pManager);

	bool	IsInitialize() { return m_bInitialize; }
	bool	StartInterface();
	bool	StopInterface();

protected:
	DWORD ThreadProc();
	void	UpdateSystemStatusInfo();

	//////////////////////////////////////////////////////////////////////////
	// Attributes
	CUDPSendSocket*		m_pSender;
	CUDPReceiveSocket*	m_pReceiver;
	CIOSWDataManager*	m_pDataManager;
	CSystemStatusManager*	m_pSystemManager;

	bool				m_bInitialize;
};

