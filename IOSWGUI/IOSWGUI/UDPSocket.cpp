#include "stdafx.h"
#include "UDPSocket.h"


CUDPSocket::CUDPSocket()
{
	WSADATA wsaData;
	WORD wVersionRequested = MAKEWORD(2, 2);
	int err = WSAStartup(wVersionRequested, &wsaData);

	if (0 != err) {
		TRACE(_T("[IOSW] Winsock DLL not found\n"));
		WSACleanup();
	}

	m_sDescriptor = INVALID_SOCKET;
}


CUDPSocket::~CUDPSocket()
{
	closesocket(m_sDescriptor);
	WSACleanup();
}




CUDPSendSocket::CUDPSendSocket()
{

}

CUDPSendSocket::~CUDPSendSocket()
{

}

bool CUDPSendSocket::InitSendSocket(int nSendPort, char* chAddress)
{
	int nSendBuffer = 1024 * 32;
	unsigned long ulMode = 1;

	ZeroMemory(&m_siRemote, sizeof(SOCKADDR_IN));
	m_siRemote.sin_family = AF_INET;
	m_siRemote.sin_port = htons(nSendPort);
	m_siRemote.sin_addr.s_addr = inet_addr(chAddress);

	m_sDescriptor = socket(AF_INET, SOCK_DGRAM, 0);

	if (m_sDescriptor == INVALID_SOCKET) {
		TRACE(_T("[IOSW] send socket create error \n"));
		WSACleanup();
		return false;
	}

	if (setsockopt(m_sDescriptor, SOL_SOCKET, SO_SNDBUF, (char*)&nSendBuffer, sizeof(nSendBuffer)) < 0){
		TRACE(_T("[IOSW] send buffer size expended failed, used default buffer\n"));
	}

	if (NO_ERROR != ioctlsocket(m_sDescriptor, FIONBIO, &ulMode)) {
		TRACE(_T("[IOSW] send socket ioctlsocket error\n"));
	}

	return true;
}

int CUDPSendSocket::SendTo(char* chData, int nLen)
{
	int nResult = 0;

	nResult = sendto(m_sDescriptor, chData, nLen, 0, (SOCKADDR *) &m_siRemote, sizeof(m_siRemote));

	return nResult;
}

CUDPReceiveSocket::CUDPReceiveSocket()
{

}

CUDPReceiveSocket::~CUDPReceiveSocket()
{

}

bool CUDPReceiveSocket::InitReceiveSocket(int nReceivePort)
{
	int nReceiveBuffer = 1024 * 32;
	int nResult;
	unsigned long ulMode = 1;

	m_sDescriptor = socket(AF_INET, SOCK_DGRAM, 0);

	if (m_sDescriptor == INVALID_SOCKET) {
		TRACE(_T("[IOSW] receive socket create error \n"));
		WSACleanup();
		return false;
	}

	if (setsockopt(m_sDescriptor, SOL_SOCKET, SO_RCVBUF, (char*)&nReceiveBuffer, sizeof(nReceiveBuffer)) < 0) {
		TRACE(_T("[IOSW] receive buffer size expended failed, used default buffer\n"));
	}

	ZeroMemory(&m_siLocal, sizeof(SOCKADDR_IN));

	m_siLocal.sin_family = AF_INET;
	m_siLocal.sin_port = htons(nReceivePort);
	m_siLocal.sin_addr.s_addr = htonl(INADDR_ANY);

	nResult = bind(m_sDescriptor, (SOCKADDR*)&m_siLocal, sizeof(SOCKADDR_IN));

	if (nResult == SOCKET_ERROR) {
		TRACE(_T("[IOSW] receive socket bind error\n"));
	}

	if (NO_ERROR != ioctlsocket(m_sDescriptor, FIONBIO, &ulMode)) {
		TRACE(_T("[IOSW] receive socket ioctlsocket error\n"));
	}

	return true;
}


bool CUDPReceiveSocket::InitReceiveSocket(int nReceivePort, char* chAddress)
{
	int nReceiveBuffer = 1024 * 32;
	int nResult;
	unsigned long ulMode = 1;

	m_sDescriptor = socket(AF_INET, SOCK_DGRAM, 0);

	if (m_sDescriptor == INVALID_SOCKET) {
		TRACE(_T("[IOSW] receive socket create error \n"));
		WSACleanup();
		return false;
	}

	if (setsockopt(m_sDescriptor, SOL_SOCKET, SO_RCVBUF, (char*)&nReceiveBuffer, sizeof(nReceiveBuffer)) < 0) {
		TRACE(_T("[IOSW] receive buffer size expended failed, used default buffer\n"));
	}

	ZeroMemory(&m_siLocal, sizeof(SOCKADDR_IN));

	m_siLocal.sin_family = AF_INET;
	m_siLocal.sin_port = htons(nReceivePort);
	m_siLocal.sin_addr.s_addr = inet_addr(chAddress); //htonl(INADDR_ANY);

	nResult = bind(m_sDescriptor, (SOCKADDR*)&m_siLocal, sizeof(SOCKADDR_IN));

	if (nResult == SOCKET_ERROR) {
		TRACE(_T("[IOSW] receive socket bind error\n"));
	}

	if (NO_ERROR != ioctlsocket(m_sDescriptor, FIONBIO, &ulMode)) {
		TRACE(_T("[IOSW] receive socket ioctlsocket error\n"));
	}

	return true;
}

int	 CUDPReceiveSocket::ReceiveFrom(char* chData, int nLen)
{
	int nResult = 0;
	struct sockaddr_in siRemote;
	int nDummy = sizeof (siRemote);

	nResult = recvfrom(m_sDescriptor, chData, nLen, 0, (SOCKADDR*) & siRemote, &nDummy);

	return nResult;
}