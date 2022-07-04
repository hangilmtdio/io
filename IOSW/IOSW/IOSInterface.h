#pragma once

//#include "IOSWThread.h"
#include "UDPSocket.h"
#include "IOSWDataManager.h"
#include "IOSWThreadObject.h"

class CIOSInterface 
{
public:
	CIOSInterface();
	~CIOSInterface();

	//////////////////////////////////////////////////////////////////////////
	// Operations
public:
	bool	Initialize(char* chIOSAddr, const int& nIOSPort, char* chIOSWAddr, const int& nIOSWPort);
	void	SetDataManager(CIOSWDataManager* pManager);

	bool	IsInitialize() { return m_bInitialize;  }
	bool	StartInterface();
	bool	StopInterface();

	void	UpdateNetworkStatus(bool bConnected);
	void	UpdateInstrumentStatus(bool bConnected);

protected:
	void	WorkSendThread();
	void	WorkRecvThread();
	static	void _WorkSendThread(void* pOwner);
	static	void _WorkRecvThread(void* pOwner);

	//////////////////////////////////////////////////////////////////////////
	// Attributes
private:
	CUDPSendSocket*		m_pSender;
	CUDPReceiveSocket*	m_pReceiver;
	CIOSWDataManager*	m_pDataManager;
	CIOSWThreadObject*	m_pSendThread;
	CIOSWThreadObject*	m_pRecvThread;

	bool				m_bInitialize;
	bool				m_bEndSendThread;
	bool				m_bEndRecvThread;

	NETWORKSTATUS_TYPE	m_eNetworkStatus;
};

