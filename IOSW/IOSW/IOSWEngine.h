#pragma once

#include "IOSInterface.h"
#include "HostInterface.h"
#include "IOSWGUIInterface.h"
#include "ANToIOBoardInterface.h"
#include "ThrottleInterface.h"
#include "IOSWDataManager.h"
#include "NexwareIOBoardInterface.h"
#include "IOPowerInterface.h"
#include <list>

typedef std::list <CANToIOBoardInterface*> LIST_IOBOARDINTERFACE;
typedef LIST_IOBOARDINTERFACE::iterator	   LIST_IOBOARDINTERFACE_ITR;

typedef std::list <CNexwareIOBoardInterface*> LIST_NEXWARETERFACE;
typedef LIST_NEXWARETERFACE::iterator	   LIST_NEXWAREINTERFACE_ITR;


class CIOSWEngine
{
public:
	CIOSWEngine();
	~CIOSWEngine();

	//////////////////////////////////////////////////////////////////////////
	// Operations
public:

	// Initialize
	bool InitEngine();

	// System On/Off Command
	void DoSystemOnOff(unsigned char cValue, bool bGUIOff = false);

	CIOSWDataManager* GetDataManager() { return m_pIOSWDataManager;  }
	// Start Interface
	bool StartIOSInterface();
	bool StartHostInterface();
	bool StartGUIInterface();
	bool StartIOBoardInterface();
	bool StartThrottleInterface();
	bool StartNexwareInterface();
	bool StartPowerInterface(const POWER_ON_OFF_TYPE eOnOff);

	// Stop Interface
	bool StopHostInterface();
	bool StopIOSInterface();
	bool StopGUIInterface();
	bool StopIOBoardInterface();
	bool StopThrottleInterface();
	bool StopNexwareInterface();
	bool StopPowerInterface();

protected:

	// Load Configuration File
	bool	LoadConfiguration();
	bool	LoadIOInformation(LPCTSTR lpszFileName);

	CANToIOBoardInterface* GetIOBoardInterface(const int& nBoardID);
	CNexwareIOBoardInterface* GetNexwareInterface(const int& nBoardID);

	void	ClearAllIOBoardInterface();
	void	ClearAllNexwareInterface();

	
	//////////////////////////////////////////////////////////////////////////
	// Attributes
private:
	CIOSInterface*			m_pIOSInterface;
	CHostInterface*			m_pHostInterface;
	CIOSWGUIInterface*		m_pGUIInterface;
	CIOPowerInterface*		m_pPowerInterface;
	LIST_IOBOARDINTERFACE*	m_pIOBoardInterfaceList;
	LIST_NEXWARETERFACE*	m_pNexwareInterfaceList;
	CThrottleInterface*		m_pThrottleInterface;

	CIOSWDataManager*		m_pIOSWDataManager;

};

