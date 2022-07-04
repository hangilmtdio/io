#pragma once

#include "IOSWThread.h"
#include "UDPSocket.h"
#include "IOSW_Interface.h"
#include "IOSWDataManager.h"

class CIOSWInterface :	public CIOSWThread
{
public:
	CIOSWInterface();
	~CIOSWInterface();

	//////////////////////////////////////////////////////////////////////////
	// Operations
	bool	Initialize(char* chIOSWAddr, const int& nIOSWPort, char* chGUIAddr, const int& nGUIPort);

	bool	IsInitialize() { return m_bInitialize; }
	bool	StartInterface();
	bool	StopInterface();

	void	SetDataManager(CIOSWDataManager* pManager);

protected:
	DWORD ThreadProc();

	//////////////////////////////////////////////////////////////////////////
	// Attributes
	CUDPSendSocket*		m_pSender;
	CUDPReceiveSocket*	m_pReceiver;

	CIOSWDataManager*	m_pDataManager;

	bool				m_bInitialize;


};

