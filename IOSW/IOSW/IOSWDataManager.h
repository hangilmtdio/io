#pragma once

#include "SM_Interface.h"
#include "cockpit2host.h"
#include "host2cockpit.h"
#include "IOSW_Interface.h"
#include "IOBoard_Interface.h"

class CIOSWDataManager
{
public:
	CIOSWDataManager();
	~CIOSWDataManager();
	//////////////////////////////////////////////////////////////////////////
	// Operations
public:

	// Initialize Data Manager
	void		Initialize();

	// IOSW Mode(Monitoring or Maintenance)
	void		SetIOSWMode(IOSW_MODE eMode);
	IOSW_MODE	GetIOSWMode();

	void		SetInstConnected(bool bConnect) { m_bInstConnected = bConnect;  }
	bool		GetInstConnected() { return m_bInstConnected; }

	void		SetInstTimeTagMode(bool bTimetag) { m_bInstTimeTagMode = bTimetag;  }
	bool		GetInstTimeTagMode() { return m_bInstTimeTagMode;  }

	void		SetInstCheckTime(int nMS) { m_nInstCheckTime = nMS;  }
	int			GetInstCheckTime() { return m_nInstCheckTime; }

	// IOS In out Test(Lamp Test)
	void		SetIOSLampTest(bool bOn);
	bool		IsIOSLampTest();

	// IOS <-> IOSW Data Interface 
	void		GetIOS2CockpitData(SM_IOS_To_Cockpit* psData);
	void		SetIOS2CockpitData(const SM_IOS_To_Cockpit & sData);
	void		GetCockpit2IOSData(SM_Cockpit_To_IOS* psData);
	void		SetCockpit2IOSData(const SM_Cockpit_To_IOS & sData);

	// HOST <-> IOSW Data Interface
	void		GetHOST2CockpitData(Host_To_Cockpit_Data_Type* psData);
	void		SetHOST2CockpitData(const Host_To_Cockpit_Data_Type & sData);
	void		GetCockpit2HOSTData(Cockpit_To_Host_Data_Type* psData);
	void		SetCockpit2HOSTData(const Cockpit_To_Host_Data_Type & sData);

	// GUI <-> IOSW Data Interface
	void		GetGUI2IOSWData(IOSWGUI_to_IOSW* psData);
	void		SetGUI2IOSWData(const IOSWGUI_to_IOSW & sData);
	void		GetIOSW2GUIData(IOSW_to_IOSWGUI* psData);
	void		SetIOSW2GUIData(const IOSW_to_IOSWGUI & sData);

	// IOSW <-> IOBOARD Data Interface 
	void		GetIOSW2IOBoardData(IOSW_to_IOBOARD* psData, const int & nBoardID);
	void		SetIOSW2IOBoardData(const IOSW_to_IOBOARD & sData, const int & nBoardID);
	void		GetIOBoard2IOSWData(IOBOARD_to_IOSW* psData, const int & nBoardID);
	void		SetIOBoard2IOSWData(const IOBOARD_to_IOSW & sData, const int & nBoardID);

	// IOBOARD Data Encode
	void		EncodeIOBoardData(const int & nBoardID, const IOBOARD_INFORMATION IOInfo[]);
	
	// IOBOARD Data Decode
	void		DecodeIOBoardData(const int & nBoardID, const IOBOARD_INFORMATION IOInfo[]);

	// BIT Result Decode
	void		DecodeBITResult();

	// System On/Off Command
	void		DoSystemOnOff(unsigned char cValue, bool bGUIOff = false);

	// Set Control Stick Limit Value
	void		SetControlStickLimitValue(int nLeftCenter, int nRightCenter, int nFrontCenter, int nRearCenter, int nLeftLimit, int nRightLimit, int nFrontLimit, int nRearLimit);

protected:
	void		UpdateIOMonitoringData(const int & nBoardID, const IOBOARD_to_IOSW & sData);
	void		UpdateIOMonitoringData(const int & nBoardID, const IOSW_to_IOBOARD & sData);

private:
	// Encode
	void		EncodeMaintenanceData(IOSW_to_IOBOARD & sData, const int & nBoardID);

	void		EncodeArrestingHookControlSwitch(IOSW_to_IOBOARD & sData, const IOBOARD_INFORMATION IOInfo[]);
	void		EncodeLandingGearControlHandle(IOSW_to_IOBOARD & sData, const IOBOARD_INFORMATION IOInfo[]);
	void		EncodeRadioCallPanel(IOSW_to_IOBOARD & sData, const IOBOARD_INFORMATION IOInfo[]);
	void		EncodeFlapPositionIndicator(IOSW_to_IOBOARD & sData, const IOBOARD_INFORMATION IOInfo[]);
	void		EncodePitchRatioIndicator(IOSW_to_IOBOARD & sData, const IOBOARD_INFORMATION IOInfo[]);
	void		EncodePitchRatioSelectSwitch(IOSW_to_IOBOARD & sData, const IOBOARD_INFORMATION IOInfo[]);
	void		EncodeArmamentControlPanel(IOSW_to_IOBOARD & sData, const IOBOARD_INFORMATION IOInfo[]);
	void		EncodeMasterCautionLight(IOSW_to_IOBOARD & sData, const IOBOARD_INFORMATION IOInfo[]);
	void		EncodeFireWarningExtinguishingPanel(IOSW_to_IOBOARD & sData, const IOBOARD_INFORMATION IOInfo[]);
	void		EncodeEmissionLimitLight(IOSW_to_IOBOARD & sData, const IOBOARD_INFORMATION IOInfo[]);
	void		EncodeEmergencyJettisonButton(IOSW_to_IOBOARD & sData, const IOBOARD_INFORMATION IOInfo[]);
	void		EncodeHCP(IOSW_to_IOBOARD & sData, const IOBOARD_INFORMATION IOInfo[]);
	void		EncodeMPD_LH(IOSW_to_IOBOARD & sData, const IOBOARD_INFORMATION IOInfo[]);
	void		EncodeMPD_RH(IOSW_to_IOBOARD & sData, const IOBOARD_INFORMATION IOInfo[]);
	void		EncodeMPCD(IOSW_to_IOBOARD & sData, const IOBOARD_INFORMATION IOInfo[]);
	void		EncodeHUDControlPanel(IOSW_to_IOBOARD & sData, const IOBOARD_INFORMATION IOInfo[]);
	void		EncodeHorizontalWarningLight(IOSW_to_IOBOARD & sData, const IOBOARD_INFORMATION IOInfo[]);
	void		EncodeVerticalCautionLight(IOSW_to_IOBOARD & sData, const IOBOARD_INFORMATION IOInfo[]);
	void		EncodeHydraulicPressureIndicatorsTop(IOSW_to_IOBOARD & sData, const IOBOARD_INFORMATION IOInfo[]);
	void		EncodeHydraulicPressureIndicatorsLeft(IOSW_to_IOBOARD & sData, const IOBOARD_INFORMATION IOInfo[]);
	void		EncodeHydraulicPressureIndicatorsRight(IOSW_to_IOBOARD & sData, const IOBOARD_INFORMATION IOInfo[]);
	void		EncodeJetFuelStrCtrlHdl_BreakeHoldSW(IOSW_to_IOBOARD & sData, const IOBOARD_INFORMATION IOInfo[]);
	void		EncodeEmergencyVentControlHandle(IOSW_to_IOBOARD & sData, const IOBOARD_INFORMATION IOInfo[]);
	void		EncodeCircuitBreakerPanel(IOSW_to_IOBOARD & sData, const IOBOARD_INFORMATION IOInfo[]);
	void		EncodeArmamentSafetyOverrideSwitch(IOSW_to_IOBOARD & sData, const IOBOARD_INFORMATION IOInfo[]);
	void		EncodeGNDTestPanel(IOSW_to_IOBOARD & sData, const IOBOARD_INFORMATION IOInfo[]);
	void		EncodeGNDPWRPanel(IOSW_to_IOBOARD & sData, const IOBOARD_INFORMATION IOInfo[]);
	void		EncodeRudderPedal(IOSW_to_IOBOARD & sData);
	void		EncodeCautionLightPanel(IOSW_to_IOBOARD & sData, const IOBOARD_INFORMATION IOInfo[]);
	void		EncodeControlStick(IOSW_to_IOBOARD & sData);
	void		EncodeStormFloodLightLH(IOSW_to_IOBOARD & sData, const IOBOARD_INFORMATION IOInfo[]);
	void		EncodeIFFAntennaSelectSwitch(IOSW_to_IOBOARD & sData, const IOBOARD_INFORMATION IOInfo[]);
	void		EncodeEmergencyAirRefuelingSwitch(IOSW_to_IOBOARD & sData, const IOBOARD_INFORMATION IOInfo[]);
	void		EncodeRemoteIntercommControlPanel(IOSW_to_IOBOARD & sData, const IOBOARD_INFORMATION IOInfo[]);
	void		EncodeFuelControlPanel(IOSW_to_IOBOARD & sData, const IOBOARD_INFORMATION IOInfo[]);
	void		EncodeMiscellaneousControlPanel(IOSW_to_IOBOARD & sData, const IOBOARD_INFORMATION IOInfo[]);
	void		EncodeCASControlPanel(IOSW_to_IOBOARD & sData, const IOBOARD_INFORMATION IOInfo[]);
	void		EncodeExteriorLightsControlPanel(IOSW_to_IOBOARD & sData, const IOBOARD_INFORMATION IOInfo[]);
	void		EncodeEngineControlPanel(IOSW_to_IOBOARD & sData, const IOBOARD_INFORMATION IOInfo[]);
	void		EncodeSensorControlPanel(IOSW_to_IOBOARD & sData, const IOBOARD_INFORMATION IOInfo[]);
	void		EncodeECSPanel(IOSW_to_IOBOARD & sData, const IOBOARD_INFORMATION IOInfo[]);
	void		EncodeOxygenRegulator(IOSW_to_IOBOARD & sData, const IOBOARD_INFORMATION IOInfo[]);
	void		EncodeEWControlPanel(IOSW_to_IOBOARD & sData, const IOBOARD_INFORMATION IOInfo[]);
	void		EncodeHMDControlPanel(IOSW_to_IOBOARD & sData, const IOBOARD_INFORMATION IOInfo[]);
	void		EncodeAirConditionControlPanel(IOSW_to_IOBOARD & sData, const IOBOARD_INFORMATION IOInfo[]);
	void		EncodeInteriorLightsControlPanel(IOSW_to_IOBOARD & sData, const IOBOARD_INFORMATION IOInfo[]);
	void		EncodeStormFloodLightRH(IOSW_to_IOBOARD & sData, const IOBOARD_INFORMATION IOInfo[]);
	void		EncodeUFC(IOSW_to_IOBOARD & sData, const IOBOARD_INFORMATION IOInfo[]);
	void		EncodeOXYCOMM(IOSW_to_IOBOARD & sData, const IOBOARD_INFORMATION IOInfo[]);
	void		EncodeSA(IOSW_to_IOBOARD & sData, const IOBOARD_INFORMATION IOInfo[]);
	void		EncodeAOA(IOSW_to_IOBOARD & sData, const IOBOARD_INFORMATION IOInfo[]);
	void		EncodeSAI(IOSW_to_IOBOARD & sData, const IOBOARD_INFORMATION IOInfo[]);
	void		EncodeVVI(IOSW_to_IOBOARD & sData, const IOBOARD_INFORMATION IOInfo[]);
	void		EncodeAltimeter(IOSW_to_IOBOARD & sData, const IOBOARD_INFORMATION IOInfo[]);
	void		EncodeClock(IOSW_to_IOBOARD & sData, const IOBOARD_INFORMATION IOInfo[]);
	void		EncodeCPA(IOSW_to_IOBOARD & sData, const IOBOARD_INFORMATION IOInfo[]);
	void		EncodeEEMD(IOSW_to_IOBOARD & sData, const IOBOARD_INFORMATION IOInfo[]);
	void		EncodeFQI(IOSW_to_IOBOARD & sData, const IOBOARD_INFORMATION IOInfo[]);
	// Decode
	void		DecodeArrestingHookControlSwitch(const IOBOARD_to_IOSW & sData, const IOBOARD_INFORMATION IOInfo[]);
	void		DecodeLandingGearControlHandle(const IOBOARD_to_IOSW & sData, const IOBOARD_INFORMATION IOInfo[]);
	void		DecodeEmergencyLandingGearHandle(const IOBOARD_to_IOSW & sData, const IOBOARD_INFORMATION IOInfo[]);
	void		DecodePitchRatioSelectSwitch(const IOBOARD_to_IOSW & sData, const IOBOARD_INFORMATION IOInfo[]);
	void		DecodeMPD_LH(const IOBOARD_to_IOSW & sData, const IOBOARD_INFORMATION IOInfo[]);
	void		DecodeArmamentControlPanel(const IOBOARD_to_IOSW & sData, const IOBOARD_INFORMATION IOInfo[]);
	void		DecodeMasterCautionLight(const IOBOARD_to_IOSW & sData, const IOBOARD_INFORMATION IOInfo[]);
	void		DecodeFireWarningExtinguishtingPanel(const IOBOARD_to_IOSW & sData, const IOBOARD_INFORMATION IOInfo[]);
	void		DecodeEmergencyJettisonButton(const IOBOARD_to_IOSW & sData, const IOBOARD_INFORMATION IOInfo[]);
	void		DecodeHCP(const IOBOARD_to_IOSW & sData, const IOBOARD_INFORMATION IOInfo[]);
	void		DecodeMPD_RH(const IOBOARD_to_IOSW & sData, const IOBOARD_INFORMATION IOInfo[]);
	void		DecodeDataTransferModuleReceptacle(const IOBOARD_to_IOSW & sData, const IOBOARD_INFORMATION IOInfo[]);
	void		DecodeJetFuelStrCtrlHDL_Break_Hold_Switch(const IOBOARD_to_IOSW & sData, const IOBOARD_INFORMATION IOInfo[]);
	void		DecodeEmergencyVentCtrlHandle(const IOBOARD_to_IOSW & sData, const IOBOARD_INFORMATION IOInfo[]);
	void		DecodeSteeringCtrlEmergecyBreakHande(const IOBOARD_to_IOSW & sData, const IOBOARD_INFORMATION IOInfo[]);
	void		DecodeCircuitBreakerPanel(const IOBOARD_to_IOSW & sData, const IOBOARD_INFORMATION IOInfo[]);
	void		DecodeMPCD(const IOBOARD_to_IOSW & sData, const IOBOARD_INFORMATION IOInfo[]);
	void		DecodeRudderPadal(const IOBOARD_to_IOSW & sData, const IOBOARD_INFORMATION IOInfo[]);
	void		DecodeControlStick(const IOBOARD_to_IOSW & sData, const IOBOARD_INFORMATION IOInfo[]);
	void		DecodeGNDPWRPanel(const IOBOARD_to_IOSW & sData, const IOBOARD_INFORMATION IOInfo[]);
	void		DecodeAntiGPanel(const IOBOARD_to_IOSW & sData, const IOBOARD_INFORMATION IOInfo[]);
	void		DecodeCanopyJettisonHandle(const IOBOARD_to_IOSW & sData, const IOBOARD_INFORMATION IOInfo[]);
	void		DecodeFlyupEnableSwitch(const IOBOARD_to_IOSW & sData, const IOBOARD_INFORMATION IOInfo[]);
	void		DecodeSeatAdjustSwitch(const IOBOARD_to_IOSW & sData, const IOBOARD_INFORMATION IOInfo[]);
	void		DecodeIFFAntennaSelectSwitch(const IOBOARD_to_IOSW & sData, const IOBOARD_INFORMATION IOInfo[]);
	void		DecodeEmergencyAirRefuelingSwitch(const IOBOARD_to_IOSW & sData, const IOBOARD_INFORMATION IOInfo[]);
	void		DecodeArmamentSafetyOverrideSwitch(const IOBOARD_to_IOSW & sData, const IOBOARD_INFORMATION IOInfo[]);
	void		DecodeRemoteIntercommControlPanel(const IOBOARD_to_IOSW & sData, const IOBOARD_INFORMATION IOInfo[]);
	void		DecodeFuelControlPanel(const IOBOARD_to_IOSW & sData, const IOBOARD_INFORMATION IOInfo[]);
	void		DecodeMiscellaneousControlPanel(const IOBOARD_to_IOSW & sData, const IOBOARD_INFORMATION IOInfo[]);
	void		DecodeCASControlPanel(const IOBOARD_to_IOSW & sData, const IOBOARD_INFORMATION IOInfo[]);
	void		DecodeExteriorLightsControlPanel(const IOBOARD_to_IOSW & sData, const IOBOARD_INFORMATION IOInfo[]);
	void		DecodeSensorControlPanel(const IOBOARD_to_IOSW & sData, const IOBOARD_INFORMATION IOInfo[]);
	void		DecodeEWControlPanel(const IOBOARD_to_IOSW & sData, const IOBOARD_INFORMATION IOInfo[]);
	void		DecodeEngineControlPanel(const IOBOARD_to_IOSW & sData, const IOBOARD_INFORMATION IOInfo[]);
	void		DecodeOxygenRegulator(const IOBOARD_to_IOSW & sData, const IOBOARD_INFORMATION IOInfo[]);
	void		DecodeECSPanel(const IOBOARD_to_IOSW & sData, const IOBOARD_INFORMATION IOInfo[]);
	void		DecodeAirConditionControlPanel(const IOBOARD_to_IOSW & sData, const IOBOARD_INFORMATION IOInfo[]);
	void		DecodeInteriorLightsControlPanel(const IOBOARD_to_IOSW & sData, const IOBOARD_INFORMATION IOInfo[]);
	void		DecodeHMDControlPanel(const IOBOARD_to_IOSW & sData, const IOBOARD_INFORMATION IOInfo[]);
	void		DecodeCanopyControlHandle(const IOBOARD_to_IOSW & sData, const IOBOARD_INFORMATION IOInfo[]);
	void		DecodeEjectionSeat(const IOBOARD_to_IOSW & sData, const IOBOARD_INFORMATION IOInfo[]);
	void		DecodeUFC(const IOBOARD_to_IOSW & sData, const IOBOARD_INFORMATION IOInfo[]);
	void		DecodeThrottleQuadrant(const IOBOARD_to_IOSW & sData, const IOBOARD_INFORMATION IOInfo[]);
	void		DecodeSAI(const IOBOARD_to_IOSW & sData, const IOBOARD_INFORMATION IOInfo[]);
	void		DecodeAltimeter(const IOBOARD_to_IOSW & sData, const IOBOARD_INFORMATION IOInfo[]);
	void		DecodeClock(const IOBOARD_to_IOSW & sData, const IOBOARD_INFORMATION IOInfo[]);
	void		DecodeFQI(const IOBOARD_to_IOSW & sData, const IOBOARD_INFORMATION IOInfo[]);

	//////////////////////////////////////////////////////////////////////////
	// Attributes
private:

	// IOS Interface Data
	SM_IOS_To_Cockpit				m_stIOS2Cockpit;
	SM_Cockpit_To_IOS				m_stCockpit2IOS;

	// HOST Interface Data
	Host_To_Cockpit_Data_Type		m_stHOST2Cockpit;
	Cockpit_To_Host_Data_Type		m_stCockpit2HOST;

	// GUI Interface Data
	IOSWGUI_to_IOSW					m_stGUI2IOSW;
	IOSW_to_IOSWGUI					m_stIOSW2GUI;

	// IO Board Interface Data
	IOSW_to_IOBOARD					m_stIOSW2IOBoard[MAX_IOBOARD];
	IOBOARD_to_IOSW					m_stIOBoard2IOSW[MAX_IOBOARD];

	// IOSW MODE
	IOSW_MODE						m_eIOSWMode;

	// IOS In Out Test(Lamp Test)
	bool							m_bIOSInOutTest;

	// Inst Connected Flag
	bool							m_bInstConnected;
	bool							m_bInstTimeTagMode;
	int								m_nInstCheckTime;

	// Rudder/Stick Init	
	bool							m_bRudderComplete;
	bool							m_bRudderInit;
	bool							m_bStickComplete;
	bool							m_bStickInit;

	// Control Stick Value
	int								m_nLeftCenter;
	int								m_nRightCenter;
	int								m_nFrontCenter;
	int								m_nRearCenter;
	int								m_nLeftLimit;
	int								m_nRightLimit;
	int								m_nFrontLimit;
	int								m_nRearLimit;
};

