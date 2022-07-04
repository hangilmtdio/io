#pragma once

#include "IOSW_Interface.h"
#include "IOInformationManager.h"
#include "CommonDefine.h"

class CIOSWDataManager
{
public:
	CIOSWDataManager();
	~CIOSWDataManager();

	//////////////////////////////////////////////////////////////////////////
	// Operations
public:
	void		Initialize(CIODeviceInformationManager* pInfoMgr);

	void		GetGUI2IOSWData(IOSWGUI_to_IOSW* psData);
	void		SetGUI2IOSWData(const IOSWGUI_to_IOSW & sData);
	void		GetIOSW2GUIData(IOSW_to_IOSWGUI* psData);
	void		SetIOSW2GUIData(const IOSW_to_IOSWGUI & sData);

	void		GetIOSW2IOBoardData(IOSW_to_IOBOARD* psData, const int & nBoardID);
	void		GetIOBoard2IOSWData(IOBOARD_to_IOSW* psData, const int & nBoardID);

	void		GetMaintenanceIOBoardOutputData(IOSW_to_IOBOARD* psData, const int & nBoardID);
	void		SetMaintenanceIOBoardOutputData(const IOSW_to_IOBOARD & sData, const int & nBoardID);
	void		SetMaintenaceDigialOutputData(const int & nBoardID, const int & nChannel, const int & nOnOff);
	void		SetMaintenaceAnalogOutputData(const int & nBoardID, const int & nChannel, const unsigned short & usData);
	void		SetMaintenaceCautionLightPanel(const int & nBoardID, const int & nDeviceID, const int & nChannel, const unsigned short & usData);
	void		SetMaintenaceDimmingData(const int & nBoardID, const int & nChannel, const unsigned short & usData);
	void		SetMaintenaceIndicatorData(const int & nBoardID, const int & nChannel, const unsigned short & usData);
	void		SetMaintenaceRudderFunctionData(const int & nBoardID, const TRIM_COMMAND & eCommand);
	void		SetMaintenaceStickFunctionData(const int & nBoardID, const TRIM_COMMAND & eCommand);
	void		SetIOSWMode(IOSW_MODE eMode);

	void		UpdateIOMonitoringData();

protected:
	void		UpdateIOBoardMonitoring(CIODeviceInfo* pInfo);
	void		UpdateIOMonitoring(sIOInformation* psInfo, int nBoardID, int nDevice);

private:
	int			GetDigitalInputBit(const int nChannel, const IOBOARD_to_IOSW & sData);
	int			GetDigitalInputBit(const int nChannel, const int n32Data);
	int			GetDigitalOutputBit(const int nChannel, const IOSW_to_IOBOARD & sData);
	int			Get28VDigitalOutputBit(const int nChannel, const IOSW_to_IOBOARD & sData);
	int			Get24VDigitalOutputBit(const int nChannel, const IOSW_to_IOBOARD & sData);
	int			Get5VDigitalOutputBit(const int nChannel, const IOSW_to_IOBOARD & sData);
	void		SetDigitalOutputBit(const int nChannel, const int & nOnOff, IOSW_to_IOBOARD & sData);
	void		Set28VDigitalOutputBit(const int nChannel, const int & nOnOff, IOSW_to_IOBOARD & sData);
	void		Set24VDigitalOutputBit(const int nChannel, const int & nOnOff, IOSW_to_IOBOARD & sData);
	void		Set5VDigitalOutputBit(const int nChannel, const int & nOnOff, IOSW_to_IOBOARD & sData);
	unsigned short GetAnalogInputData(const int nChannel, const IOBOARD_to_IOSW & sData);
	unsigned short GetAnalogOutputData(const int nChannel, const IOSW_to_IOBOARD & sData);
	void		   SetAnalogOutputData(const int nChannel, const unsigned short & usData, IOSW_to_IOBOARD & sData);
	void		   Set28VAnalogOutputData(const int nChannel, const unsigned short & usData, IOSW_to_IOBOARD & sData);
	void		   Set24VAnalogOutputData(const int nChannel, const unsigned short & usData, IOSW_to_IOBOARD & sData);
	void		   Set5VAnalogOutputData(const int nChannel, const unsigned short & usData, IOSW_to_IOBOARD & sData);
	unsigned short GetDimmingData(const int nChannel, const IOSW_to_IOBOARD & sData);
	void		   SetDimmingData(const int nChannel, const unsigned short & usData, IOSW_to_IOBOARD & sData);
	unsigned short GetIndicatorData(const int nBoardID, const int nChannel, const IOSW_to_IOBOARD & sData);
	void		   SetIndicatorData(const int nBoardID, const int nChannel, const unsigned short & usData, IOSW_to_IOBOARD & sData);
	float		   GetStickRudderInputData(const int nBoardID, const int nChannel, const IOBOARD_to_IOSW & sData);
	unsigned short GetCautionLightPanel(const int nChannel, const IOSW_to_IOBOARD & sData);
	unsigned short GetGNDTestPanel(const int nChannel, const IOSW_to_IOBOARD & sData);

	// Attributes
private:

	// GUI Interface Data
	IOSWGUI_to_IOSW					m_stGUI2IOSW;
	IOSW_to_IOSWGUI					m_stIOSW2GUI;

	CIODeviceInformationManager*	m_pIODevieInfoMgr;
};

