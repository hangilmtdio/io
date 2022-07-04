#pragma once

#include "IOBoard_Interface.h"

typedef enum IOSW_MODE
{
	IM_MONITORING = 0,
	IM_MAINTENANCE,
}IOSW_MODE;

static LPCTSTR alpszIOSWMODEType[] =
{
	_T("Monitoring"),
	_T("Maintenance"),
};

typedef enum IO_KIND
{
	IK_UNKNOWN = 0,
	IK_DI,
	IK_DO,
	IK_AI,
	IK_AO,
	IK_DIMMER,
	IK_AI_SR,
	IK_AO_IDC,
	IK_ETC,
}IO_KIND;

static LPCTSTR alpszIOType[] =
{
	_T("Unknown"),
	_T("DI"),
	_T("DO"),
	_T("AI"),
	_T("AO"),
	_T("DIMMER"),
	_T("AI_S/R"),
	_T("AO_IDC"),
	_T("ETC"),
};

typedef enum DEVICE_POSITION
{
	DP_UNKNOWN = 0,
	DP_LEFT,
	DP_MAIN,
	DP_RIGHT,
} DEVICE_POSITION;

#define MAX_IOBOARD_IO 64

typedef struct IOBOARD_INFORMATION
{
	int nIndex;
	IO_KIND eKind;
	int nChannel;
	int nMin;
	int nMax;
}IOBOARD_INFORMATION;


typedef struct SYSTEMSTATUSINFO
{
	float fCPUUsageAmount;				//CPU 사용량(%)
	float fMemoryUsageAmount;			//Memory 사용량(%)
	float fDiskUsageAmount;				//디스크 사용량(%)
}SYSTEMSTATUSINFO;

typedef enum NETWORKSTATUS_TYPE {
	NS_NOTUSED = 0,						// Not Used Board
	NS_DISCONNECTED = 1,				// Network Disconnected
	NS_CONNECTED = 2,					// Network Connected and BIT OK
	NS_ERROR = 3,						// Network Connected and BIT Fail
}NETWORKSTATUS_TYPE;

typedef struct IOSW_to_IOSWGUI
{
	int			Timetag;
	SYSTEMSTATUSINFO	stSystemStatus;
	bool				bSystemOff;
	NETWORKSTATUS_TYPE	eHOSTNetworkStatus;
	NETWORKSTATUS_TYPE	eIOSNetworkStatus;
	NETWORKSTATUS_TYPE	ePowerNetworkStatus;
	NETWORKSTATUS_TYPE	eIONetworkStatus[MAX_IOBOARD];
	IOBOARD_to_IOSW		sIOBoard2IOSW[MAX_IOBOARD];
	IOSW_to_IOBOARD		sIOSW2IOBoard[MAX_IOBOARD];
} IOSW_to_IOSWGUI;


typedef struct IOSWGUI_to_IOSW
{
	int			Timetag;
	IOSW_MODE	eIOSWMode;
	bool		bPowerON;
	IOSW_to_IOBOARD		sIOSW2IOBoard[MAX_IOBOARD];
} IOSWGUI_to_IOSW;

