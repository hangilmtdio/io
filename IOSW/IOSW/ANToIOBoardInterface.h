#pragma once

#include "IOSWThread.h"
#include "UDPSocket.h"
#include "IOSWDataManager.h"
#include "IOSWThreadObject.h"

class CANToIOBoardInterface //: public CIOSWThread
{
public:
	CANToIOBoardInterface();
	~CANToIOBoardInterface();

	//////////////////////////////////////////////////////////////////////////
	// Operations
	bool	Initialize(char* chIOBoardAddr, const int& nIOBoardPort, char* chIOSWAddr, const int& nIOSWPort);
	void	SetDataManager(CIOSWDataManager* pManager);

	bool	IsInitialize() { return m_bInitialize; }
	bool	StartInterface();
	bool	StopInterface();

	bool	SetBoardInformation(const int& nIndex, const IOBOARD_INFORMATION& stInfo);

	void	SetBoardID(const int& nID) { m_nBoardID = nID;  }
	int		GetBoardID() { return m_nBoardID; }

	void	UpdateNetworkStatus(bool bConnected, bool bBITResult);
protected:
	//DWORD	ThreadProc();
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

	bool				m_bInitialize;
	bool				m_bEndSendThread;
	bool				m_bEndRecvThread;

	NETWORKSTATUS_TYPE	m_eNetworkStatus;
	int					m_nNetworkStatusCount;

	int					m_nBoardID;
	IOBOARD_INFORMATION				m_stIOInformation[MAX_IOBOARD_IO];

	CIOSWThreadObject*	m_pSendThread;
	CIOSWThreadObject*	m_pRecvThread;
};

