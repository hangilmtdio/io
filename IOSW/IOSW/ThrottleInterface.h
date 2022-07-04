#pragma once

#include "IOSWThread.h"
#include "USBHIDIO.h"
#include "IOSWDataManager.h"
#include "IOBoard_Interface.h"

typedef struct THROTTLE_IO
{
	unsigned short usHATSwitch;
	unsigned short usSlider;
	unsigned short usDial;
	unsigned short usRotationalZ;
	unsigned short usRotationalY;
	unsigned short usRotationalX;
	unsigned short usZ;
	unsigned short usY;
	unsigned short usX;
	unsigned short usDILow;			// 0~15 Channel
	unsigned short usDIHigh;		// 16~31 Channel
}THROTTLE_IO;


#define HID_VENDER	0x16c0			// Aerotronics Vender ID
#define HID_PRODUCT 0x5BA			// Aerotronics Poduct ID

class CThrottleInterface : public CIOSWThread
{
public:
	CThrottleInterface();
	~CThrottleInterface();

	//////////////////////////////////////////////////////////////////////////
	// Operations
public:
	bool	Initialize();
	void	SetDataManager(CIOSWDataManager* pManager);

	bool	IsInitialize() { return m_bInitialize; }
	bool	StartInterface();
	bool	StopInterface();

	void	UpdateNetworkStatus(bool bConnected);

	bool	SetBoardInformation(const int& nIndex, const IOBOARD_INFORMATION& stInfo);

	void	SetBoardID(const int& nID) { m_nBoardID = nID; }
	int		GetBoardID() { return m_nBoardID; }
protected:
	DWORD ThreadProc();
	bool  UpdateValuesState(THROTTLE_IO* psInfo);
	bool  UpdateButtonState(THROTTLE_IO* psInfo);
	bool  UpdateIOBoardState(const THROTTLE_IO & sInfo, IOBOARD_to_IOSW * psInfo);
	void  SetDIState(unsigned short & usData, const unsigned short & usChannel);
	unsigned short ConvertAIData(const IOBOARD_INFORMATION& stInfo, const unsigned short & usData);
	//////////////////////////////////////////////////////////////////////////
	// Attributes
private:
	CUSBHIDIO*			m_pHIDConn;
	PSP_DEVICE_INTERFACE_DETAIL_DATA	m_sThrottleDevPath;
	HIDD_ATTRIBUTES						m_sThrottleDevAttrib;
	HIDP_CAPS							m_sThrottleDevCaps;
	CIOSWDataManager*	m_pDataManager;
	int					m_nBoardID;
	IOBOARD_INFORMATION				m_stIOInformation[MAX_IOBOARD_IO];
	bool				m_bInitialize;
	NETWORKSTATUS_TYPE	m_eNetworkStatus;
};

