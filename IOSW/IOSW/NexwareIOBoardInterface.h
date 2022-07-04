#pragma once

#include "UDPSocket.h"
#include "IOSWDataManager.h"
#include "IOSWThreadObject.h"
#include "Nexware_Interface.h"


class CNexwareIOBoardInterface
{
public:
	CNexwareIOBoardInterface();
	~CNexwareIOBoardInterface();

	//////////////////////////////////////////////////////////////////////////
	// Operations
	bool	Initialize(char* chIOBoardAddr, const int& nIOBoardPort, char* chIOSWAddr, const int& nIOSWPort);
	void	SetDataManager(CIOSWDataManager* pManager);

	bool	IsInitialize() { return m_bInitialize; }
	bool	StartInterface();
	bool	StopInterface();

	bool	SetBoardInformation(const int& nIndex, const IOBOARD_INFORMATION& stInfo);

	void	SetBoardID(const int& nID) { m_nBoardID = nID; }
	int		GetBoardID() { return m_nBoardID; }

protected:
	void	UpdateNetworkStatus(bool bConnected);
	void	WorkSendThread();
	void	WorkRecvThread();
	static	void _WorkSendThread(void* pOwner);
	static	void _WorkRecvThread(void* pOwner);
	bool	ConvertRecvtoIOBoardState(const Nexware_to_IOSW & sInfo, IOBOARD_to_IOSW * psInfo);
	bool	ConvertIOBoardStatetoSend(const IOSW_to_IOBOARD & sInfo, IOSW_to_Nexware * psInfo);
	int		ConvertNexwareIDtoIOBoardID(const int& nNexwareID);
	int		ConvertIOBoardIDtoNexwareID(const int& nIOBoardID);

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

