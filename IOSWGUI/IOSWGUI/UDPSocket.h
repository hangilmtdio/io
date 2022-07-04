#pragma once

#include <stdlib.h>
#include <WinSock2.h>
#include <windows.h>
#include <tlhelp32.h> 

#pragma comment(lib, "ws2_32.lib")


class CUDPSocket
{
public:
	//////////////////////////////////////////////////////////////////////////
	// Operations
	CUDPSocket();
	~CUDPSocket();

	//////////////////////////////////////////////////////////////////////////
	// Attributes
protected:
	SOCKET	m_sDescriptor;
};

class CUDPSendSocket : public CUDPSocket
{
public:
	//////////////////////////////////////////////////////////////////////////
	// Operations
	CUDPSendSocket();
	~CUDPSendSocket();

	bool InitSendSocket(int nSendPort, char* chAddress);
	int  SendTo(char* chData, int nLen);
	//////////////////////////////////////////////////////////////////////////
	// Attributes
protected:
	SOCKADDR_IN m_siRemote;
};

class CUDPReceiveSocket : public CUDPSocket
{
public:
	//////////////////////////////////////////////////////////////////////////
	// Operations
	CUDPReceiveSocket();
	~CUDPReceiveSocket();

	//////////////////////////////////////////////////////////////////////////
	// Attributes
	bool InitReceiveSocket(int nReceivePort);
	bool InitReceiveSocket(int nReceivePort, char* chAddress);

	int	 ReceiveFrom(char* chData, int nLen);

protected:
	SOCKADDR_IN m_siLocal;
};

