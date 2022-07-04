#pragma once

#include "UDPSocket.h"
#include "IOSWDataManager.h"
#include "IOSWThreadObject.h"

// HOST IP 100.100.20.30
// Receiv Port 2005
// Send Port 3005

class CHostInterface// public CIOSWThread
{
public:
	CHostInterface();
	~CHostInterface();

	//////////////////////////////////////////////////////////////////////////
	// Operations
	bool	Initialize(char* chHOSTAddr, const int& nHOSTPort, char* chIOSWAddr, const int& nIOSWPort);
	void	SetDataManager(CIOSWDataManager* pManager);

	bool	IsInitialize() { return m_bInitialize; }
	bool	StartInterface();
	bool	StopInterface();

	void	UpdateNetworkStatus(bool bConnected);
	void	UpdateInstStatus();

protected:
	void	WorkSendThread();
	void	WorkRecvThread();
	static	void _WorkSendThread(void* pOwner);
	static	void _WorkRecvThread(void* pOwner);

	//////////////////////////////////////////////////////////////////////////
	// Attributes
	CUDPSendSocket*		m_pSender;
	CUDPReceiveSocket*	m_pReceiver;
	CIOSWDataManager*	m_pDataManager;
	CIOSWThreadObject*	m_pSendThread;
	CIOSWThreadObject*	m_pRecvThread;

	bool				m_bInitialize;
	bool				m_bEndSendThread;
	bool				m_bEndRecvThread;

	NETWORKSTATUS_TYPE	m_eNetworkStatus;
	NETWORKSTATUS_TYPE	m_eInstStatus;
};

