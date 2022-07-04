#pragma once

#include "UDPSocket.h"
#include "IOSWDataManager.h"
#include "IOSWThreadObject.h"

typedef enum POWER_ON_OFF_TYPE
{
	POWER_OFF = 0,
	POWER_ON = 1,
} POWER_ON_OFF_TYPE;


class CIOPowerInterface
{
public:
	CIOPowerInterface();
	~CIOPowerInterface();

	//////////////////////////////////////////////////////////////////////////
	// Operations
public:
	bool	Initialize(char* chPWRAddr, const int& nPWRPort, char* chIOSWAddr, const int& nIOSWPort);
	bool	IsInitialize() { return m_bInitialize; }

	void	SetPower(const POWER_ON_OFF_TYPE bOnOff) { m_ePowerStatus = bOnOff;  }
	void	SetDataManager(CIOSWDataManager* pManager);

	bool	StartInterface();
	bool	StopInterface();

protected:
	void	WorkSendThread();
	void	WorkRecvThread();
	static	void _WorkSendThread(void* pOwner);
	static	void _WorkRecvThread(void* pOwner);
	void	UpdateNetworkStatus(bool bConnected, bool bBITResult);

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
	int					m_nNetworkStatusCount;
	POWER_ON_OFF_TYPE   m_ePowerStatus;
};

