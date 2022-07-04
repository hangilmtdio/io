#include "stdafx.h"
#include "IOSWDataManager.h"
#include "IOSWUtility.h"
#include "IOSWLogger.h"

CIOSWDataManager::CIOSWDataManager()
{
	m_bIOSInOutTest = false;
	m_bInstConnected = false;
	m_bInstTimeTagMode = true;
	m_nInstCheckTime = 0;
	m_bRudderComplete = false;
	m_bRudderInit = false;
	m_bStickComplete = false;
	m_bStickInit = false;

	m_nLeftCenter = 0;
	m_nRightCenter = 0;
	m_nFrontCenter = 0;
	m_nRearCenter = 0;
	m_nLeftLimit = 0;
	m_nRightLimit = 0;
	m_nFrontLimit = 0;
	m_nRearLimit = 0;
}


CIOSWDataManager::~CIOSWDataManager()
{
}

void CIOSWDataManager::Initialize()
{
	ZeroMemory(&m_stIOS2Cockpit, sizeof(m_stIOS2Cockpit));
	ZeroMemory(&m_stCockpit2IOS, sizeof(m_stCockpit2IOS));

	ZeroMemory(&m_stHOST2Cockpit, sizeof(m_stHOST2Cockpit));
	ZeroMemory(&m_stCockpit2HOST, sizeof(m_stCockpit2HOST));

	ZeroMemory(&m_stGUI2IOSW, sizeof(m_stGUI2IOSW));
	ZeroMemory(&m_stIOSW2GUI, sizeof(m_stIOSW2GUI));

	for (int i = 0; i < MAX_IOBOARD; i++) {
		ZeroMemory(&m_stIOSW2IOBoard[i], sizeof(IOSW_to_IOBOARD));
		ZeroMemory(&m_stIOBoard2IOSW[i], sizeof(IOBOARD_to_IOSW));
	}


	m_eIOSWMode = IM_MONITORING;
}

void CIOSWDataManager::SetIOSWMode(IOSW_MODE eMode)
{
	m_eIOSWMode = eMode;
}

IOSW_MODE CIOSWDataManager::GetIOSWMode()
{
	return m_eIOSWMode;
}

void CIOSWDataManager::SetIOSLampTest(bool bOn)
{
	m_bIOSInOutTest = bOn;
}

bool CIOSWDataManager::IsIOSLampTest()
{
	return m_bIOSInOutTest;
}

void CIOSWDataManager::SetControlStickLimitValue(int nLeftCenter, int nRightCenter, int nFrontCenter, int nRearCenter, int nLeftLimit, int nRightLimit, int nFrontLimit, int nRearLimit)
{
	m_nLeftCenter = nLeftCenter;
	m_nRightCenter = nRightCenter;
	m_nFrontCenter = nFrontCenter;
	m_nRearCenter = nRearCenter;
	m_nLeftLimit = nLeftLimit;
	m_nRightLimit = nRightLimit;
	m_nFrontLimit = nFrontLimit;
	m_nRearLimit = nRearLimit;
}

void CIOSWDataManager::GetIOS2CockpitData(SM_IOS_To_Cockpit* psData)
{
	::memcpy(psData, &m_stIOS2Cockpit, sizeof(SM_IOS_To_Cockpit));
}

void CIOSWDataManager::SetIOS2CockpitData(const SM_IOS_To_Cockpit& sData)
{
	::memcpy(&m_stIOS2Cockpit, &sData, sizeof(SM_IOS_To_Cockpit));
}

void CIOSWDataManager::GetCockpit2IOSData(SM_Cockpit_To_IOS* psData)
{
	::memcpy(psData, &m_stCockpit2IOS, sizeof(SM_Cockpit_To_IOS));
}

void CIOSWDataManager::SetCockpit2IOSData(const SM_Cockpit_To_IOS& sData)
{
	::memcpy(&m_stCockpit2IOS, &sData, sizeof(SM_Cockpit_To_IOS));
}

void CIOSWDataManager::GetHOST2CockpitData(Host_To_Cockpit_Data_Type* psData)
{
	::memcpy(psData, &m_stHOST2Cockpit, sizeof(Host_To_Cockpit_Data_Type));
}

void CIOSWDataManager::SetHOST2CockpitData(const Host_To_Cockpit_Data_Type& sData)
{
	::memcpy(&m_stHOST2Cockpit, &sData, sizeof(Host_To_Cockpit_Data_Type));
}

void CIOSWDataManager::GetCockpit2HOSTData(Cockpit_To_Host_Data_Type* psData)
{
	::memcpy(psData, &m_stCockpit2HOST, sizeof(Cockpit_To_Host_Data_Type));
}

void CIOSWDataManager::SetCockpit2HOSTData(const Cockpit_To_Host_Data_Type& sData)
{
	::memcpy(&m_stHOST2Cockpit, &sData, sizeof(Cockpit_To_Host_Data_Type));
}

void CIOSWDataManager::GetGUI2IOSWData(IOSWGUI_to_IOSW* psData)
{
	::memcpy(psData, &m_stGUI2IOSW, sizeof(IOSWGUI_to_IOSW));
}

void CIOSWDataManager::SetGUI2IOSWData(const IOSWGUI_to_IOSW& sData)
{
	::memcpy(&m_stGUI2IOSW, &sData, sizeof(IOSWGUI_to_IOSW));
}

void CIOSWDataManager::GetIOSW2GUIData(IOSW_to_IOSWGUI* psData)
{
	::memcpy(psData, &m_stIOSW2GUI, sizeof(IOSW_to_IOSWGUI));
}

void CIOSWDataManager::SetIOSW2GUIData(const IOSW_to_IOSWGUI& sData)
{
	::memcpy(&m_stIOSW2GUI, &sData, sizeof(IOSW_to_IOSWGUI));
}

void CIOSWDataManager::GetIOSW2IOBoardData(IOSW_to_IOBOARD* psData, const int& nBoardID)
{
	::memcpy(psData, &m_stIOSW2IOBoard[nBoardID], sizeof(IOSW_to_IOBOARD));
}

void CIOSWDataManager::SetIOSW2IOBoardData(const IOSW_to_IOBOARD& sData, const int& nBoardID)
{
	::memcpy(&m_stIOSW2IOBoard[nBoardID], &sData, sizeof(IOSW_to_IOBOARD));
}

void CIOSWDataManager::GetIOBoard2IOSWData(IOBOARD_to_IOSW* psData, const int& nBoardID)
{
	::memcpy(psData, &m_stIOBoard2IOSW[nBoardID], sizeof(IOBOARD_to_IOSW));
}

void CIOSWDataManager::SetIOBoard2IOSWData(const IOBOARD_to_IOSW& sData, const int& nBoardID)
{
	::memcpy(&m_stIOBoard2IOSW[nBoardID], &sData, sizeof(IOBOARD_to_IOSW));
}

// Decode BIT Result
void CIOSWDataManager::DecodeBITResult()
{
	IOSW_to_IOSWGUI stIOSW2GUI;
	int nErrorCodes[20];

	memset(&stIOSW2GUI, 0x00, sizeof(IOSW_to_IOSWGUI));
	memset(&nErrorCodes, 0x00, sizeof(nErrorCodes));

	GetIOSW2GUIData(&stIOSW2GUI);
	int nIndex = 0;

	memset(&m_stCockpit2IOS.Err_Codes, 0x00, sizeof(m_stCockpit2IOS.Err_Codes));

	for (int i = 0; i < MAX_IOBOARD; i++)
	{
		NETWORKSTATUS_TYPE eType = stIOSW2GUI.eIONetworkStatus[i];

		if (eType != NS_NOTUSED && eType != NS_CONNECTED)
		{
			if (nIndex < 20 && i != 38)
			{
				nErrorCodes[nIndex] = ERR_IOBOARD_1 + (i - 1);
				nIndex++;
			}

		}
	}

	if (nIndex > 0)
	{
		m_stCockpit2IOS.Err_Status = bTRUE;
		memcpy(&m_stCockpit2IOS.Err_Codes, &nErrorCodes, sizeof(m_stCockpit2IOS.Err_Codes));
	}
	else {
		m_stCockpit2IOS.Err_Status = bFALSE;
	}
}


void CIOSWDataManager::DoSystemOnOff(unsigned char cValue, bool bGUIOff)
{
	// IOSW GUI Program exit 
	m_stIOSW2GUI.bSystemOff = bGUIOff;

	// IO BOARD Shutdown
	for (int i = 0; i < MAX_IOBOARD; i++)
	{
		if (i != 38)
		{
			m_stIOSW2IOBoard[i].SHUTDOWN_COMMAND = cValue;
		}
	}
}

void CIOSWDataManager::EncodeIOBoardData(const int& nBoardID, const IOBOARD_INFORMATION IOInfo[])
{
	IOSW_MODE eMode;
	eMode = GetIOSWMode();

	IOSW_to_IOBOARD sData;

	GetIOSW2IOBoardData(&sData, nBoardID);

	if (eMode == IM_MONITORING)
	{
		switch (nBoardID)
		{
		case 1: // Common B/D
			// ARRESTING_HOOK_CONTROL_SWITCH
			EncodeArrestingHookControlSwitch(sData, IOInfo);

			// LANDING_GEAR_CONTROL_HANDLE
			EncodeLandingGearControlHandle(sData, IOInfo);

			// RADIO_CALL_PANEL
			EncodeRadioCallPanel(sData, IOInfo);

			// FLAP_POSITION_INDICATOR
			EncodeFlapPositionIndicator(sData, IOInfo);

			// PITCH_RATIO_INDICATOR
			EncodePitchRatioIndicator(sData, IOInfo);

			// PITCH_RATIO_SELECT_SWITCH
			EncodePitchRatioSelectSwitch(sData, IOInfo);

			// MPD Left
			EncodeMPD_LH(sData, IOInfo);

			break;
		case 2: // ARMAMENT CONTROL PANEL
			EncodeArmamentControlPanel(sData, IOInfo);
			break;
		case 3: // Common B/D
			// MASTER_CAUTION_LIGHT
			EncodeMasterCautionLight(sData, IOInfo);

			// FIRE_WARNING/EXTINGUISHING_PANEL
			EncodeFireWarningExtinguishingPanel(sData, IOInfo);

			// EMISSION_LIMIT_LIGHT
			EncodeEmissionLimitLight(sData, IOInfo);

			// EMERGENCY_JETTISON_BUTTON
			EncodeEmergencyJettisonButton(sData, IOInfo);

			// HUD_CONTROL_PANEL
			EncodeHCP(sData, IOInfo);

			// MPD Right
			EncodeMPD_RH(sData, IOInfo);

			break;
		case 5: // HUD_CONTROL_PANEL
			EncodeHUDControlPanel(sData, IOInfo);

			break;
		case 10:// Common B/D

			// VERTICAL_CAUTION_LIGHT_ASSY
			EncodeVerticalCautionLight(sData, IOInfo);

			// HORIZONTAL_WARNING_LIGHT_ASSY
			EncodeHorizontalWarningLight(sData, IOInfo);

			// HYDRAULIC_PRESSURE_INDICATORS_TOP
			EncodeHydraulicPressureIndicatorsTop(sData, IOInfo);
			break;
		case 15: // Common B/D
			// HYDRAULIC_PRESSURE_INDICATORS_LEFT/RIGHT
			EncodeHydraulicPressureIndicatorsLeft(sData, IOInfo);
			EncodeHydraulicPressureIndicatorsRight(sData, IOInfo);

			// JET_FUEL_STR_CTRL_HDL/BRAKE_HOLD_SW	
			EncodeJetFuelStrCtrlHdl_BreakeHoldSW(sData, IOInfo);

			// EMERGENCY_VENT_CONTROL_HANDLE
			EncodeEmergencyVentControlHandle(sData, IOInfo);

			break;
		case 16:
			// CIRCUIT_BREAKER_PANEL
			EncodeCircuitBreakerPanel(sData, IOInfo);

			// MPCD
			EncodeMPCD(sData, IOInfo);

			break;
		case 17: // Common B/D
			// RUDDER_PEDAL
			EncodeRudderPedal(sData);

			// CAUTION_LIGHT_PANEL
			EncodeCautionLightPanel(sData, IOInfo);
			break;
		case 18: // CONTROL_STICK
			EncodeControlStick(sData);
			break;
		case 19: // GND_PWR_PANEL
			EncodeGNDPWRPanel(sData, IOInfo);
			break;
		case 20: // Common B/D
			// STORM_FLOOD_LIGHT_LH_FRONT
			// STORM_FLOOD_LIGHT_LH_REAR
			EncodeStormFloodLightLH(sData, IOInfo);

			// IFF_ANTENNA_SELECT_SWITCH
			EncodeIFFAntennaSelectSwitch(sData, IOInfo);

			// EMERGENCY_AIR_REFUELING_SWITCH
			EncodeEmergencyAirRefuelingSwitch(sData, IOInfo);

			// ARMAMENT_SAFETY_OVERRIDE_SWITCH
			EncodeArmamentSafetyOverrideSwitch(sData, IOInfo);

			// GND_TEST_PANEL
			EncodeGNDTestPanel(sData, IOInfo);

			break;
		case 22: // REMOTE_INTERCOMM_CONTROL_PANEL
			EncodeRemoteIntercommControlPanel(sData, IOInfo);
			break;
		case 23: // FUEL_CONTROL_PANEL
			EncodeFuelControlPanel(sData, IOInfo);
			break;
		case 24: // MISCELLANEOUS_CONTROL_PANEL
			EncodeMiscellaneousControlPanel(sData, IOInfo);
			break;
		case 25: // CAS_CONTROL_PANEL
			EncodeCASControlPanel(sData, IOInfo);
			break;
		case 26: // EXTERIOR_LIGHTS_CONTROL_PANEL
			EncodeExteriorLightsControlPanel(sData, IOInfo);
			break;
		case 27: // SENSOR_CONTROL_PANEL
			EncodeSensorControlPanel(sData, IOInfo);
			break;
		case 28: // EW_CONTROL_PANEL
			EncodeEWControlPanel(sData, IOInfo);
			break;
		case 29: // ENGINE_CONTROL_PANEL
			EncodeEngineControlPanel(sData, IOInfo);
			break;
		case 30: // OXYGEN_REGULATOR
			EncodeOxygenRegulator(sData, IOInfo);
			break;
		case 31: // ECS_PANEL
			EncodeECSPanel(sData, IOInfo);
			break;
		case 32: // AIR_CONDITION_CONTROL_PANEL
			EncodeAirConditionControlPanel(sData, IOInfo);
			break;
		case 33: // INTERIOR_LIGHTS_CONTROL_PANEL
			EncodeInteriorLightsControlPanel(sData, IOInfo);
			break;
		case 34: // Common B/D
			// HMD_CONTROL_PANEL
			EncodeHMDControlPanel(sData, IOInfo);

			// STORM_FLOOD_LIGHT_RH_FRONT
			// STORM_FLOOD_LIGHT_RH_REAR
			EncodeStormFloodLightRH(sData, IOInfo);
			break;
		case 35: // UPFRONT_CONTROL_PANEL
			EncodeUFC(sData, IOInfo);
			break;
		case 38: // OXY_COMM
			EncodeOXYCOMM(sData, IOInfo);
			break;
		case 41: // SA
			EncodeSA(sData, IOInfo);
			break;
		case 42: // SAI
			EncodeSAI(sData, IOInfo);
			break;
		case 43: // ALTIMETER
			EncodeAltimeter(sData, IOInfo);
			break;
		case 45: // VVI
			EncodeVVI(sData, IOInfo);
			break;
		case 44: // AOA
			EncodeAOA(sData, IOInfo);
			break;
		case 46: // CLOCK
			EncodeClock(sData, IOInfo);
			break;
		case 47: // CPA
			EncodeCPA(sData, IOInfo);
			break;
		case 48: // EEMD
			EncodeEEMD(sData, IOInfo);
			break;
		case 49: // FQI
			EncodeFQI(sData, IOInfo);
			break;
		default:
			break;
		}

	}
	else // IM_MAINTENANCE
	{
		EncodeMaintenanceData(sData, nBoardID);

		switch (nBoardID)
		{
		case 17: // Common B/D
			// RUDDER_PEDAL
			EncodeRudderPedal(sData);

			break;
		case 18: // CONTROL_STICK
			EncodeControlStick(sData);
			break;
		case 41: // SA
			EncodeSA(sData, IOInfo);
			break;
		case 42: // SAI
			EncodeSAI(sData, IOInfo);
			break;
		case 43: // ALTIMETER
			EncodeAltimeter(sData, IOInfo);
			break;
		case 45: // VVI
			EncodeVVI(sData, IOInfo);
			break;
		case 44: // AOA
			EncodeAOA(sData, IOInfo);
			break;
		case 46: // CLOCK
			EncodeClock(sData, IOInfo);
			break;
		case 47: // CPA
			EncodeCPA(sData, IOInfo);
			break;
		case 48: // EEMD
			EncodeEEMD(sData, IOInfo);
			break;
		case 49: // FQI
			EncodeFQI(sData, IOInfo);
			break;
		default:
			break;
		}

	}

	SetIOSW2IOBoardData(sData, nBoardID);
	UpdateIOMonitoringData(nBoardID, sData);
}
void CIOSWDataManager::EncodeMaintenanceData(IOSW_to_IOBOARD& sData, const int& nBoardID)
{
	IOSWGUI_to_IOSW sGUI2IOSW;

	GetGUI2IOSWData(&sGUI2IOSW);
	memcpy(&sData, &sGUI2IOSW.sIOSW2IOBoard[nBoardID], sizeof(IOSW_to_IOBOARD));

}

// ARRESTING_HOOK_CONTROL_SWITCH Encode
void CIOSWDataManager::EncodeArrestingHookControlSwitch(IOSW_to_IOBOARD& sData, const IOBOARD_INFORMATION IOInfo[])
{
	// IO idx  2 : BACK_LIGHT_POWER
	//SetDimmingData(IOInfo[2], m_stHOST2Cockpit.HOST2IO.Inst_Backlight, sData);
}

// LANDING_GEAR_CONTROL_HANDLE Encode
void CIOSWDataManager::EncodeLandingGearControlHandle(IOSW_to_IOBOARD& sData, const IOBOARD_INFORMATION IOInfo[])
{
	// IO idx  3 : LEFT_LAMP
	int nLampValue = 0;

	//nLampValue = IsIOSLampTest() ? 1000 : m_stHOST2Cockpit.HOST2IO.Landing_Gear_Light.Left_Gear_Light;
	//SetAnalogOutputData(IOInfo[3], nLampValue, sData);

	// IO idx  5 : NOSE_LAMP
	//nLampValue = IsIOSLampTest() ? 1000 : m_stHOST2Cockpit.HOST2IO.Landing_Gear_Light.Nose_Gear_Light;
	//SetAnalogOutputData(IOInfo[5], nLampValue, sData);

	// IO idx  7 : RIGHT_LAMP
	//nLampValue = IsIOSLampTest() ? 1000 : m_stHOST2Cockpit.HOST2IO.Landing_Gear_Light.Right_Gear_Light;
	//SetAnalogOutputData(IOInfo[7], nLampValue, sData);

	// IO idx  12 : LANDING_GEAR_LAMP
	//nLampValue = IsIOSLampTest() ? 1000 : m_stHOST2Cockpit.HOST2IO.Landing_Gear_Light.Handle_Light;
	//SetAnalogOutputData(IOInfo[12], nLampValue, sData);

	// IO idx  13 : BACK_LIGHT_POWER
	//SetDimmingData(IOInfo[13], m_stHOST2Cockpit.HOST2IO.Inst_Backlight, sData);

}

// FLAP_POSITION_INDICATOR Encode
void CIOSWDataManager::EncodeFlapPositionIndicator(IOSW_to_IOBOARD& sData, const IOBOARD_INFORMATION IOInfo[])
{
	// IO idx 14 : FLAP_UPPER_LAMP
	int nLampValue = 0;

	//nLampValue = IsIOSLampTest() ? 1000 : m_stHOST2Cockpit.HOST2IO.Flap_Light.Flap_Up_Light;
	//SetAnalogOutputData(IOInfo[14], nLampValue, sData);

	// IO idx 15 : FLAP_LOWER_LAMP
	//nLampValue = IsIOSLampTest() ? 1000 : m_stHOST2Cockpit.HOST2IO.Flap_Light.Flap_Down_Light;
	//SetAnalogOutputData(IOInfo[15], nLampValue, sData);

}

// RADIO_CALL_PANEL Encode
void CIOSWDataManager::EncodeRadioCallPanel(IOSW_to_IOBOARD& sData, const IOBOARD_INFORMATION IOInfo[])
{
	// IO idx  16 : BACK_LIGHT_POWER
	//SetDimmingData(IOInfo[13], m_stHOST2Cockpit.HOST2IO.Inst_Backlight, sData);
}

// PITCH_RATIO_INDICATOR
void CIOSWDataManager::EncodePitchRatioIndicator(IOSW_to_IOBOARD& sData, const IOBOARD_INFORMATION IOInfo[])
{
	// IO idx  19 : PITCH_RATIO_MOTOR
	unsigned short nAOData = (unsigned short)(((IOInfo[19].nMax - IOInfo[19].nMin) / 1000.0f) * 1);//m_stHOST2Cockpit.HOST2IO.Pitch_Ratio);

	if (nAOData < IOInfo[19].nMin) {
		nAOData = IOInfo[19].nMin;
	}
	else if (nAOData > IOInfo[19].nMax)
		nAOData = IOInfo[19].nMax;
	else {
	}

	sData.PITCH_RATIO_GAUGE = nAOData;

	// IO idx  20 : PITCH_RATIO_BACKLIGHT
	//SetDimmingData(IOInfo[20], m_stHOST2Cockpit.HOST2IO.Inst_Backlight, sData);
}

void CIOSWDataManager::EncodePitchRatioSelectSwitch(IOSW_to_IOBOARD& sData, const IOBOARD_INFORMATION IOInfo[])
{
	// IO idx  23 : BACK_LIGHT_POWER
	//SetDimmingData(IOInfo[23], m_stHOST2Cockpit.HOST2IO.Inst_Backlight, sData);

}

void CIOSWDataManager::EncodeArmamentControlPanel(IOSW_to_IOBOARD& sData, const IOBOARD_INFORMATION IOInfo[])
{
	/* IO idx 12 : BACK_LIGHT_POWER */
	//SetDimmingData(IOInfo[12], m_stHOST2Cockpit.HOST2IO.Inst_Backlight, sData);

}

// MASTER_CAUTION_LIGHT Encode
void CIOSWDataManager::EncodeMasterCautionLight(IOSW_to_IOBOARD& sData, const IOBOARD_INFORMATION IOInfo[])
{
	// IO idx  0 : FLAP_LOWER_LAMP
	//int nLampValue = IsIOSLampTest() ? 1000 : m_stHOST2Cockpit.HOST2IO.Main_Panel_Light.Master_Caution_Light;
	//SetAnalogOutputData(IOInfo[0], nLampValue, sData);


}

void CIOSWDataManager::EncodeFireWarningExtinguishingPanel(IOSW_to_IOBOARD& sData, const IOBOARD_INFORMATION IOInfo[])
{
	// IO idx  8 : AMAD_FIRE/PUSH_LAMP
	//int nLampValue = IsIOSLampTest() ? 1000 : m_stHOST2Cockpit.HOST2IO.Fire_Warning.AMAD_Fire_Light;
	//SetAnalogOutputData(IOInfo[8], nLampValue, sData);

	// IO idx  9 : L_ENGINE_FIRE/PUSH_LAMP
	//nLampValue = IsIOSLampTest() ? 1000 : m_stHOST2Cockpit.HOST2IO.Fire_Warning.Left_Engine_Fire_Light;
	//SetAnalogOutputData(IOInfo[9], nLampValue, sData);

	// IO idx 10 : R_ENGINE_FIRE/PUSH_LAMP	
	//nLampValue = IsIOSLampTest() ? 1000 : m_stHOST2Cockpit.HOST2IO.Fire_Warning.Right_Engine_Fire_Light;
	//SetAnalogOutputData(IOInfo[10], nLampValue, sData);

	// IO idx 11 : L_BURN_THRU_LAMP
	//nLampValue = IsIOSLampTest() ? 1000 : m_stHOST2Cockpit.HOST2IO.Fire_Warning.Left_Burn_Thru_Light;
	//SetAnalogOutputData(IOInfo[11], nLampValue, sData);

	// IO idx 12 : R_BURN_THRU_LAMP
	//nLampValue = IsIOSLampTest() ? 1000 : m_stHOST2Cockpit.HOST2IO.Fire_Warning.Right_Burn_Thru_Light;
	//SetAnalogOutputData(IOInfo[12], nLampValue, sData);

	// IO idx 13 : BACK_LIGHT_POWER 
	//SetDimmingData(IOInfo[13], m_stHOST2Cockpit.HOST2IO.Inst_Backlight, sData);

}

// EMISSION_LIMIT_LIGHT Encode
void CIOSWDataManager::EncodeEmissionLimitLight(IOSW_to_IOBOARD& sData, const IOBOARD_INFORMATION IOInfo[])
{
	// IO idx 14 : EMISSION_LIMIT_LAMP
	//int nLampValue = IsIOSLampTest() ? 1000 : m_stHOST2Cockpit.HOST2IO.Main_Panel_Light.EMIS_LMT_Light;
	//SetAnalogOutputData(IOInfo[14], nLampValue, sData);

}

// EMERGENCY_JETTISON_BUTTON Encode
void CIOSWDataManager::EncodeEmergencyJettisonButton(IOSW_to_IOBOARD& sData, const IOBOARD_INFORMATION IOInfo[])
{
	// IO idx 16 : BACK_LIGHT_POWER 
	//SetDimmingData(IOInfo[16], m_stHOST2Cockpit.HOST2IO.Inst_Backlight, sData);

}

// HUD_CONTROL_PANEL Encode
void CIOSWDataManager::EncodeHCP(IOSW_to_IOBOARD& sData, const IOBOARD_INFORMATION IOInfo[])
{
	// IO idx 27 : A/A_LIGHT
	//int nLampValue = IsIOSLampTest() ? 1000 : m_stHOST2Cockpit.HOST2IO.Master_Mode_Lights.Air_to_Air_Light;
	//SetAnalogOutputData(IOInfo[27], nLampValue, sData);

	// IO idx 29 : A/G_LIGHT
	//nLampValue = IsIOSLampTest() ? 1000 : m_stHOST2Cockpit.HOST2IO.Master_Mode_Lights.Air_to_Ground_Light;
	//SetAnalogOutputData(IOInfo[29], nLampValue, sData);

	// IO idx 31 : NAV_LIGHT
	//nLampValue = IsIOSLampTest() ? 1000 : m_stHOST2Cockpit.HOST2IO.Master_Mode_Lights.Air_to_Nav_Light;
	//SetAnalogOutputData(IOInfo[31], nLampValue, sData);

	// IO idx 33 : INST_LIGHT
	//nLampValue = IsIOSLampTest() ? 1000 : m_stHOST2Cockpit.HOST2IO.Master_Mode_Lights.Air_to_Inst_Light;
	//SetAnalogOutputData(IOInfo[33], nLampValue, sData);

	// IO idx 62 : INST_LIGHT
	//SetDimmingData(IOInfo[62], m_stHOST2Cockpit.HOST2IO.UFC_Backlight, sData);

}

// MPD LH Encode
void CIOSWDataManager::EncodeMPD_LH(IOSW_to_IOBOARD& sData, const IOBOARD_INFORMATION IOInfo[])
{
	// IO idx 50 : BACK_LIGHT_POWER 
	//SetDimmingData(IOInfo[50], m_stHOST2Cockpit.HOST2IO.Inst_Backlight, sData);

}

// MPD RH Encode
void CIOSWDataManager::EncodeMPD_RH(IOSW_to_IOBOARD& sData, const IOBOARD_INFORMATION IOInfo[])
{
	// IO idx 61 : BACK_LIGHT_POWER 
	//SetDimmingData(IOInfo[61], m_stHOST2Cockpit.HOST2IO.Inst_Backlight, sData);

}

// MPCD Encode
void CIOSWDataManager::EncodeMPCD(IOSW_to_IOBOARD& sData, const IOBOARD_INFORMATION IOInfo[])
{
	// IO idx 45 : BACK_LIGHT_POWER 
	//SetDimmingData(IOInfo[45], m_stHOST2Cockpit.HOST2IO.Inst_Backlight, sData);

	// IO idx 46 : L 
	//int nLampValue = IsIOSLampTest() ? 1000 : m_stHOST2Cockpit.HOST2IO.MPCD_Lights.L_LIGHT;
	//SetAnalogOutputData(IOInfo[46], nLampValue, sData);

	// IO idx 47 : LC 
	//nLampValue = IsIOSLampTest() ? 1000 : m_stHOST2Cockpit.HOST2IO.MPCD_Lights.LC_LIGHT;
	//SetAnalogOutputData(IOInfo[47], nLampValue, sData);

	// IO idx 48 : C 
	//nLampValue = IsIOSLampTest() ? 1000 : m_stHOST2Cockpit.HOST2IO.MPCD_Lights.C_LIGHT;
	//SetAnalogOutputData(IOInfo[48], nLampValue, sData);

	// IO idx 49 : RC 
	//nLampValue = IsIOSLampTest() ? 1000 : m_stHOST2Cockpit.HOST2IO.MPCD_Lights.RC_LIGHT;
	//SetAnalogOutputData(IOInfo[49], nLampValue, sData);

	// IO idx 50 : R 
	//nLampValue = IsIOSLampTest() ? 1000 : m_stHOST2Cockpit.HOST2IO.MPCD_Lights.R_LIGHT;
	//SetAnalogOutputData(IOInfo[50], nLampValue, sData);

}


// HUD_CONTROL_PANEL Encode
void CIOSWDataManager::EncodeHUDControlPanel(IOSW_to_IOBOARD& sData, const IOBOARD_INFORMATION IOInfo[])
{
	// IO idx 13 : LED_BRIGHTNESS
	//int nLampValue = m_stHOST2Cockpit.HOST2IO.HUD_Data.Bright;

}


// HORIZONTAL_WARNING_LIGHT_ASSY Encode
void CIOSWDataManager::EncodeHorizontalWarningLight(IOSW_to_IOBOARD& sData, const IOBOARD_INFORMATION IOInfo[])
{
	/* IO idx  0 : SPARE_LAMP
	   IO idx  1 : AI/SAM_LAMP
	   IO idx  2 : LOW_ALT_LAMP
	   IO idx  3 : OBST_LAMP
	   IO idx  4 : TF_FAIL_LAMP
	   IO idx  5 : CAN_UNLKD_LAMP	*/
	int nLampValue = 0;

	//nLampValue = IsIOSLampTest() ? 1000 : m_stHOST2Cockpit.HOST2IO.Main_Panel_Light.Spare1_Light;
	//SetAnalogOutputData(IOInfo[0], nLampValue, sData);

	//nLampValue = IsIOSLampTest() ? 1000 : m_stHOST2Cockpit.HOST2IO.Main_Panel_Light.A1_SAM_Light;
	//SetAnalogOutputData(IOInfo[1], nLampValue, sData);

	//nLampValue = IsIOSLampTest() ? 1000 : m_stHOST2Cockpit.HOST2IO.Main_Panel_Light.Low_Alt_Light;
	//SetAnalogOutputData(IOInfo[2], nLampValue, sData);

	//nLampValue = IsIOSLampTest() ? 1000 : m_stHOST2Cockpit.HOST2IO.Main_Panel_Light.OBST_Light;
	//SetAnalogOutputData(IOInfo[3], nLampValue, sData);

	//nLampValue = IsIOSLampTest() ? 1000 : m_stHOST2Cockpit.HOST2IO.Main_Panel_Light.TF_Fail_Light;
	//SetAnalogOutputData(IOInfo[4], nLampValue, sData);

	//nLampValue = IsIOSLampTest() ? 1000 : m_stHOST2Cockpit.HOST2IO.Main_Panel_Light.Can_Unlkd_Light;
	//SetAnalogOutputData(IOInfo[5], nLampValue, sData);

	//static int nOldLampValue = 0;

	//if (nOldLampValue != nLampValue)
	//{
	//	CString strTemp;
	//	strTemp.Format(_T("HorizontalWarningLight = %d"), nLampValue);
	//	std::string strOut;
	//	strOut = CT2CA(strTemp.operator LPCWSTR());

	//	CIOSWLogger::Instance()->AddLog(LT_INFORMATION, strOut);

	//	nOldLampValue = nLampValue;
	//	
	//}


}

// VERTICAL_CAUTION_LIGHT_ASSY Encode
void CIOSWDataManager::EncodeVerticalCautionLight(IOSW_to_IOBOARD& sData, const IOBOARD_INFORMATION IOInfo[])
{
	/* IO idx  6 : SPARE_LAMP2
	   IO idx  7 : SPARE_LAMP3
	   IO idx  8 : LASERMED_LAMP
	   IO idx  9 : AP_LAMP */
	int nLampValue = 0;

	//nLampValue = IsIOSLampTest() ? 1000 : m_stHOST2Cockpit.HOST2IO.Main_Panel_Light.Spare2_Light;
	//SetAnalogOutputData(IOInfo[6], nLampValue, sData);

	//nLampValue = IsIOSLampTest() ? 1000 : m_stHOST2Cockpit.HOST2IO.Main_Panel_Light.Spare3_Light;
	//SetAnalogOutputData(IOInfo[7], nLampValue, sData);

	//nLampValue = IsIOSLampTest() ? 1000 : m_stHOST2Cockpit.HOST2IO.Main_Panel_Light.Laser_Armed_Light;
	//SetAnalogOutputData(IOInfo[8], nLampValue, sData);

	//nLampValue = IsIOSLampTest() ? 1000 : m_stHOST2Cockpit.HOST2IO.Main_Panel_Light.AP_Light;
	//SetAnalogOutputData(IOInfo[9], nLampValue, sData);

	//static int nOldLampValue = 0;

	//if (nOldLampValue != nLampValue)
	//{
	//	CString strTemp;
	//	strTemp.Format(_T("VerticalWarningLight = %d"), nLampValue);
	//	std::string strOut;
	//	strOut = CT2CA(strTemp.operator LPCWSTR());

	//	CIOSWLogger::Instance()->AddLog(LT_INFORMATION, strOut);

	//	nOldLampValue = nLampValue;

	//}

}

// STORM_FLOOD_LIGHT_LH Encode
void CIOSWDataManager::EncodeStormFloodLightLH(IOSW_to_IOBOARD& sData, const IOBOARD_INFORMATION IOInfo[])
{
	/* IO idx  4 : STORM_FLOOD_LAMP
	   IO idx  5 : STORM_FLOOD_LAMP */
	int nLampValue = 0;

	//nLampValue = IsIOSLampTest() ? 1000 : m_stHOST2Cockpit.HOST2IO.Storm_Flood_Light;
	//SetAnalogOutputData(IOInfo[4], nLampValue, sData);

	//nLampValue = IsIOSLampTest() ? 1000 : m_stHOST2Cockpit.HOST2IO.Storm_Flood_Light;
	//SetAnalogOutputData(IOInfo[5], nLampValue, sData);

}

// IFF_ANTENNA_SELECT_SWITCH Encode
void CIOSWDataManager::EncodeIFFAntennaSelectSwitch(IOSW_to_IOBOARD& sData, const IOBOARD_INFORMATION IOInfo[])
{
	// IO idx 12 : BACK_LIGHT_POWER 
	//SetDimmingData(IOInfo[12], m_stHOST2Cockpit.HOST2IO.Console_Backlight, sData);
}

// EMERGENCY_AIR_REFUELING_SWITCH Encode
void CIOSWDataManager::EncodeEmergencyAirRefuelingSwitch(IOSW_to_IOBOARD& sData, const IOBOARD_INFORMATION IOInfo[])
{
	// IO idx 15 : BACK_LIGHT_POWER 
	//SetDimmingData(IOInfo[15], m_stHOST2Cockpit.HOST2IO.Console_Backlight, sData);

}

// REMOTE_INTERCOMM_CONTROL_PANEL Encode
void CIOSWDataManager::EncodeRemoteIntercommControlPanel(IOSW_to_IOBOARD& sData, const IOBOARD_INFORMATION IOInfo[])
{
	// IO idx  27 : REPLY_LAMP
	//int nLampValue = IsIOSLampTest() ? 1000 : m_stHOST2Cockpit.HOST2IO.Replay_Light;
	//SetAnalogOutputData(IOInfo[27], nLampValue, sData);

	// IO idx  31 : BACK_LIGHT_POWER 
	//SetDimmingData(IOInfo[31], m_stHOST2Cockpit.HOST2IO.Console_Backlight, sData);

}

// FUEL_CONTROL_PANEL Encode
void CIOSWDataManager::EncodeFuelControlPanel(IOSW_to_IOBOARD& sData, const IOBOARD_INFORMATION IOInfo[])
{
	//ON_OFF_TYPE eOnOFF = m_stHOST2Cockpit.HOST2IO.Solenoid_Coil_OFF[DUMP_SW];
	//SetDigitalOutputData(IOInfo[10], (int)eOnOFF, sData);
	//
	//// IO idx  19 : BACK_LIGHT_POWER 
	////SetDimmingData(IOInfo[19], m_stHOST2Cockpit.HOST2IO.Console_Backlight, sData);

}

// MISCELLANEOUS_CONTROL_PANEL Encode
void CIOSWDataManager::EncodeMiscellaneousControlPanel(IOSW_to_IOBOARD& sData, const IOBOARD_INFORMATION IOInfo[])
{
	// IO idx  19 : BACK_LIGHT_POWER 
	//SetDimmingData(IOInfo[12], m_stHOST2Cockpit.HOST2IO.Console_Backlight, sData);

}

// CAS_CONTROL_PANEL Encode
void CIOSWDataManager::EncodeCASControlPanel(IOSW_to_IOBOARD& sData, const IOBOARD_INFORMATION IOInfo[])
{
	// IO idx  10 : BIT_LAMP -> 삭제
	//int nLampValue = m_stHOST2Cockpit.HOST2IO.;
	////SetAnalogOutputData(IOInfo[10], nLampValue, sData);

	// IO idx  14 : TRIM_LIGHT_ON
	//int nLampValue = IsIOSLampTest() ? 1000 : m_stHOST2Cockpit.HOST2IO.TO_Trim_Light;
	//SetAnalogOutputData(IOInfo[14], nLampValue, sData);

	// IO idx  15 : BACK_LIGHT_POWER 
	//SetDimmingData(IOInfo[15], m_stHOST2Cockpit.HOST2IO.Console_Backlight, sData);

}

void CIOSWDataManager::EncodeExteriorLightsControlPanel(IOSW_to_IOBOARD& sData, const IOBOARD_INFORMATION IOInfo[])
{
	// IO idx  22 : BACK_LIGHT_POWER 
	//SetDimmingData(IOInfo[22], m_stHOST2Cockpit.HOST2IO.Console_Backlight, sData);

}

void CIOSWDataManager::EncodeSensorControlPanel(IOSW_to_IOBOARD& sData, const IOBOARD_INFORMATION IOInfo[])
{
	// IO idx  28 : BACK_LIGHT_POWER 
	//SetDimmingData(IOInfo[28], m_stHOST2Cockpit.HOST2IO.Console_Backlight, sData);

}

void CIOSWDataManager::EncodeEngineControlPanel(IOSW_to_IOBOARD& sData, const IOBOARD_INFORMATION IOInfo[])
{
	//ON_OFF_TYPE eONOFF = m_stHOST2Cockpit.HOST2IO.Solenoid_Coil_OFF[EMERG_GEN_SW];
	//SetDigitalOutputData(IOInfo[5], (int)eONOFF, sData);
	//
	//// IO idx  16 : STARTER_READY_LAMP
	////int nLampValue = IsIOSLampTest() ? 1000 : m_stHOST2Cockpit.HOST2IO.Starter_Light;
	////SetAnalogOutputData(IOInfo[16], nLampValue, sData);
	//
	//// IO idx  21 : BACK_LIGHT_POWER 
	////SetDimmingData(IOInfo[21], m_stHOST2Cockpit.HOST2IO.Console_Backlight, sData);

}

void CIOSWDataManager::EncodeECSPanel(IOSW_to_IOBOARD& sData, const IOBOARD_INFORMATION IOInfo[])
{
	//// IO idx   1 : OXY_BIT/BOS_LAMP
	////int nLampValue = IsIOSLampTest() ? 1000 : m_stHOST2Cockpit.HOST2IO.OXY_Bit_Light;
	////SetAnalogOutputData(IOInfo[1], nLampValue, sData);
	//
	//ON_OFF_TYPE eOnOFF = m_stHOST2Cockpit.HOST2IO.Solenoid_Coil_OFF[ANTO_FOG_SW];
	//SetDigitalOutputData(IOInfo[3], (int)eOnOFF, sData);
	//
	//
	//// IO idx 12 : BACK_LIGHT_POWER 
	////SetDimmingData(IOInfo[12], m_stHOST2Cockpit.HOST2IO.Console_Backlight, sData);

}

void CIOSWDataManager::EncodeOxygenRegulator(IOSW_to_IOBOARD& sData, const IOBOARD_INFORMATION IOInfo[])
{
	// IO idx   0 : FLOW_INDICATOR
	//ON_OFF_TYPE eOnOFF = m_stHOST2Cockpit.HOST2IO.FLOW;
	//
	//SetDigitalOutputData(IOInfo[0], (int)eOnOFF, sData);
	//
	//
	///*if (eOnOFF == ON)
	//	sData.OXYGEN_FLOW = 1;
	//else
	//	sData.OXYGEN_FLOW = 0;*/
	//
	//	// IO idx   1 : PRESSURE_MOTOR
	//unsigned short nAOData = (unsigned short)(((IOInfo[1].nMax - IOInfo[1].nMin) / 1000.0f) * m_stHOST2Cockpit.HOST2IO.OXYGEN);
	//
	//if (nAOData < IOInfo[1].nMin) {
	//	nAOData = IOInfo[1].nMin;
	//}
	//else if (nAOData > IOInfo[1].nMax)
	//	nAOData = IOInfo[1].nMax;
	//else {
	//}
	//
	//sData.OXYGEN_GAUGE = nAOData;
	//
	//// IO idx  2 : PRESSURE_BACK_LIGHT_POWER 
	////SetDimmingData(IOInfo[2], m_stHOST2Cockpit.HOST2IO.Console_Backlight, sData);
	//
	//// IO idx 11 : BACK_LIGHT_POWER 
	////SetDimmingData(IOInfo[11], m_stHOST2Cockpit.HOST2IO.Console_Backlight, sData);

}

// EW_CONTROL_PANEL Encode
void CIOSWDataManager::EncodeEWControlPanel(IOSW_to_IOBOARD& sData, const IOBOARD_INFORMATION IOInfo[])
{
	// IO idx  14 : BACK_LIGHT_POWER 
	//SetDimmingData(IOInfo[14], m_stHOST2Cockpit.HOST2IO.Console_Backlight, sData);

}

// AIR_CONDITION_CONTROL_PANEL Encode
void CIOSWDataManager::EncodeAirConditionControlPanel(IOSW_to_IOBOARD& sData, const IOBOARD_INFORMATION IOInfo[])
{
	// IO idx  11 : BACK_LIGHT_POWER 
	//SetDimmingData(IOInfo[11], m_stHOST2Cockpit.HOST2IO.Console_Backlight, sData);

}

// HYDRAULIC_PRESSURE_INDICATORS_Top Encode
void CIOSWDataManager::EncodeHydraulicPressureIndicatorsTop(IOSW_to_IOBOARD& sData, const IOBOARD_INFORMATION IOInfo[])
{
	// IO idx  10 : UTIL_MOTER
	unsigned short nAOData = (unsigned short)(((IOInfo[10].nMax - IOInfo[10].nMin) / 1000.0f) * 1);// m_stHOST2Cockpit.HOST2IO.HYD_Pressure_Util);

	if (nAOData < IOInfo[10].nMin) {
		nAOData = IOInfo[10].nMin;
	}
	else if (nAOData > IOInfo[10].nMax)
		nAOData = IOInfo[10].nMax;
	else {
	}

	sData.UTIL_GAUGE = nAOData;

	// IO idx 11 : PC1_BACK_LIGHT 
	//SetDimmingData(IOInfo[11], m_stHOST2Cockpit.HOST2IO.Inst_Backlight, sData);

	//static int nOldLampValue = 0;

	//if (nOldLampValue != nAOData)
	//{
	//	CString strTemp;
	//	strTemp.Format(_T("HydraulicPressureIndicators  = %d"), nAOData);
	//	std::string strOut;
	//	strOut = CT2CA(strTemp.operator LPCWSTR());

	//
	//	CIOSWLogger::Instance()->AddLog(LT_INFORMATION, strOut);

	//	nOldLampValue = nAOData;

	//}

}


// HYDRAULIC_PRESSURE_INDICATORS_LEFT Encode
void CIOSWDataManager::EncodeHydraulicPressureIndicatorsLeft(IOSW_to_IOBOARD& sData, const IOBOARD_INFORMATION IOInfo[])
{
	// IO idx  0 : PC1_MOTOR
	unsigned short nAOData = (unsigned short)(((IOInfo[0].nMax - IOInfo[0].nMin) / 1000.0f) * 1);// m_stHOST2Cockpit.HOST2IO.HYD_Pressure_PC1);

	if (nAOData < IOInfo[0].nMin) {
		nAOData = IOInfo[0].nMin;
	}
	else if (nAOData > IOInfo[0].nMax)
		nAOData = IOInfo[0].nMax;
	else {
	}

	sData.PC1_GAUGE = nAOData;

	// IO idx 1 : PC1_BACK_LIGHT 
	//SetDimmingData(IOInfo[1], m_stHOST2Cockpit.HOST2IO.Inst_Backlight, sData);

}

// HYDRAULIC_PRESSURE_INDICATORS_RIGHT Encode
void CIOSWDataManager::EncodeHydraulicPressureIndicatorsRight(IOSW_to_IOBOARD& sData, const IOBOARD_INFORMATION IOInfo[])
{
	// IO idx  2 : PC2_MOTOR
	unsigned short nAOData = (unsigned short)(((IOInfo[2].nMax - IOInfo[2].nMin) / 1000.0f) * 1);// m_stHOST2Cockpit.HOST2IO.HYD_Pressure_PC2);

	if (nAOData < IOInfo[2].nMin) {
		nAOData = IOInfo[2].nMin;
	}
	else if (nAOData > IOInfo[2].nMax)
		nAOData = IOInfo[2].nMax;
	else {
	}

	sData.PC2_GAUGE = nAOData;

	// IO idx 3 : BACK_LIGHT_POWER 
	//SetDimmingData(IOInfo[3], m_stHOST2Cockpit.HOST2IO.Inst_Backlight, sData);

}

// JET_FUEL_STR_CTRL_HDL/BRAKE_HOLD_SW	Encode
void CIOSWDataManager::EncodeJetFuelStrCtrlHdl_BreakeHoldSW(IOSW_to_IOBOARD& sData, const IOBOARD_INFORMATION IOInfo[])
{
	//// IO idx 8 : COIL_OFF
	//ON_OFF_TYPE eOnOFF = m_stHOST2Cockpit.HOST2IO.Solenoid_Coil_OFF[JFS_START_SW];
	//SetDigitalOutputData(IOInfo[8], (int)eOnOFF, sData);
	//
	//// IO idx 9 : BACK_LIGHT_POWER 
	////SetDimmingData(IOInfo[9], m_stHOST2Cockpit.HOST2IO.Inst_Backlight, sData);

}

// EMERGENCY_VENT_CONTROL_HANDLE Encode
void CIOSWDataManager::EncodeEmergencyVentControlHandle(IOSW_to_IOBOARD& sData, const IOBOARD_INFORMATION IOInfo[])
{
	// IO idx 12 : BACK_LIGHT_POWER 
	//SetDimmingData(IOInfo[12], m_stHOST2Cockpit.HOST2IO.Inst_Backlight, sData);

}

// CIRCUIT_BREAKER_PANEL Encode
void CIOSWDataManager::EncodeCircuitBreakerPanel(IOSW_to_IOBOARD& sData, const IOBOARD_INFORMATION IOInfo[])
{
	// IO idx  8 : BACK_LIGHT_POWER  Upper
	//SetDimmingData(IOInfo[8], m_stHOST2Cockpit.HOST2IO.Inst_Backlight, sData);
	// IO idx 14 : BACK_LIGHT_POWER  LH
	//SetDimmingData(IOInfo[14], m_stHOST2Cockpit.HOST2IO.Inst_Backlight, sData);
	// IO idx 18 : BACK_LIGHT_POWER  RH
	//SetDimmingData(IOInfo[18], m_stHOST2Cockpit.HOST2IO.Inst_Backlight, sData);

}
// RUDDER_PEDAL Encode
void CIOSWDataManager::EncodeRudderPedal(IOSW_to_IOBOARD& sData)
{
	if ((m_stHOST2Cockpit.MTD_MODE == INIT_MODE) && (m_bRudderInit == false)) {
		m_bRudderInit = true;
	}

	if (m_bRudderInit && !m_bRudderComplete)
	{
		sData.RUDDER_INIT = 1;
		sData.RUDDER_LH_TRIM = 0;
		sData.RUDDER_RH_TRIM = 0;
	}
	else
	{
		sData.RUDDER_INIT = 0;// (unsigned char)m_stHOST2Cockpit.HOST2IO.Rudderpedal_Trim.RUDDER_INIT;
		sData.RUDDER_LH_TRIM = 0;//(unsigned char)m_stHOST2Cockpit.HOST2IO.Rudderpedal_Trim.RUDDER_LH_TRIM;
		sData.RUDDER_RH_TRIM = 0;//(unsigned char)m_stHOST2Cockpit.HOST2IO.Rudderpedal_Trim.RUDDER_RH_TRIM;
	}

}

// CAUTION_LIGHT_PANEL Encode
void CIOSWDataManager::EncodeCautionLightPanel(IOSW_to_IOBOARD& sData, const IOBOARD_INFORMATION IOInfo[])
{
	//int nLampValue = IsIOSLampTest() ? 1000 : m_stHOST2Cockpit.HOST2IO.Caution_Lights.Program_Light;
	int nLampValue = 1;

	sData.CAUTION_CH0 = (unsigned short)(((IOInfo[3].nMax - IOInfo[3].nMin) / 1000.0f) * nLampValue);

	//nLampValue = IsIOSLampTest() ? 1000 : m_stHOST2Cockpit.HOST2IO.Caution_Lights.Minimum_Light;
	sData.CAUTION_CH1 = (unsigned short)(((IOInfo[4].nMax - IOInfo[4].nMin) / 1000.0f) * nLampValue);

	//nLampValue = IsIOSLampTest() ? 1000 : m_stHOST2Cockpit.HOST2IO.Caution_Lights.Chaff_Light;
	sData.CAUTION_CH2 = (unsigned short)(((IOInfo[5].nMax - IOInfo[5].nMin) / 1000.0f) * nLampValue);

	//nLampValue = IsIOSLampTest() ? 1000 : m_stHOST2Cockpit.HOST2IO.Caution_Lights.Flare_Light;
	sData.CAUTION_CH3 = (unsigned short)(((IOInfo[6].nMax - IOInfo[6].nMin) / 1000.0f) * nLampValue);

	//nLampValue = IsIOSLampTest() ? 1000 : m_stHOST2Cockpit.HOST2IO.Caution_Lights.Emer_Bst_On_Light;
	sData.CAUTION_CH4 = (unsigned short)(((IOInfo[7].nMax - IOInfo[7].nMin) / 1000.0f) * nLampValue);

	//nLampValue = IsIOSLampTest() ? 1000 : m_stHOST2Cockpit.HOST2IO.Caution_Lights.Bst_Sys_Mal_Light;
	sData.CAUTION_CH5 = (unsigned short)(((IOInfo[8].nMax - IOInfo[8].nMin) / 1000.0f) * nLampValue);

	//nLampValue = IsIOSLampTest() ? 1000 : m_stHOST2Cockpit.HOST2IO.Caution_Lights.Brk_Hld_Light;
	sData.CAUTION_CH6 = (unsigned short)(((IOInfo[9].nMax - IOInfo[9].nMin) / 1000.0f) * nLampValue);

	//nLampValue = IsIOSLampTest() ? 1000 : m_stHOST2Cockpit.HOST2IO.Caution_Lights.Fuel_Low_Light;
	sData.CAUTION_CH7 = (unsigned short)(((IOInfo[10].nMax - IOInfo[10].nMin) / 1000.0f) * nLampValue);

	//nLampValue = IsIOSLampTest() ? 1000 : m_stHOST2Cockpit.HOST2IO.Caution_Lights.Left_Gen_Light;
	sData.CAUTION_CH8 = (unsigned short)(((IOInfo[11].nMax - IOInfo[11].nMin) / 1000.0f) * nLampValue);

	//nLampValue = IsIOSLampTest() ? 1000 : m_stHOST2Cockpit.HOST2IO.Caution_Lights.Right_Gen_Light;
	sData.CAUTION_CH9 = (unsigned short)(((IOInfo[12].nMax - IOInfo[12].nMin) / 1000.0f) * nLampValue);

	//nLampValue = IsIOSLampTest() ? 1000 : m_stHOST2Cockpit.HOST2IO.Caution_Lights.Engine_Light;
	sData.CAUTION_CH10 = (unsigned short)(((IOInfo[13].nMax - IOInfo[13].nMin) / 1000.0f) * nLampValue);

	//nLampValue = IsIOSLampTest() ? 1000 : m_stHOST2Cockpit.HOST2IO.Caution_Lights.Flt_Control_Light;
	sData.CAUTION_CH11 = (unsigned short)(((IOInfo[14].nMax - IOInfo[14].nMin) / 1000.0f) * nLampValue);

	//nLampValue = IsIOSLampTest() ? 1000 : m_stHOST2Cockpit.HOST2IO.Caution_Lights.Hydraulic_Light;
	sData.CAUTION_CH12 = (unsigned short)(((IOInfo[15].nMax - IOInfo[15].nMin) / 1000.0f) * nLampValue);

	//nLampValue = IsIOSLampTest() ? 1000 : m_stHOST2Cockpit.HOST2IO.Caution_Lights.Av_Bit_Light;
	sData.CAUTION_CH13 = (unsigned short)(((IOInfo[16].nMax - IOInfo[16].nMin) / 1000.0f) * nLampValue);

	//nLampValue = IsIOSLampTest() ? 1000 : m_stHOST2Cockpit.HOST2IO.Caution_Lights.Dspl_Flo_Lo_Light;
	sData.CAUTION_CH14 = (unsigned short)(((IOInfo[17].nMax - IOInfo[17].nMin) / 1000.0f) * nLampValue);

	//nLampValue = IsIOSLampTest() ? 1000 : m_stHOST2Cockpit.HOST2IO.Caution_Lights.Oxygen_Light;
	sData.CAUTION_CH15 = (unsigned short)(((IOInfo[18].nMax - IOInfo[18].nMin) / 1000.0f) * nLampValue);

	//nLampValue = IsIOSLampTest() ? 1000 : m_stHOST2Cockpit.HOST2IO.Caution_Lights.Spare1_Light;
	sData.CAUTION_CH16 = (unsigned short)(((IOInfo[19].nMax - IOInfo[19].nMin) / 1000.0f) * nLampValue);

	//nLampValue = IsIOSLampTest() ? 1000 : m_stHOST2Cockpit.HOST2IO.Caution_Lights.Spare2_Light;
	sData.CAUTION_CH17 = (unsigned short)(((IOInfo[20].nMax - IOInfo[20].nMin) / 1000.0f) * nLampValue);

	//nLampValue = IsIOSLampTest() ? 1000 : m_stHOST2Cockpit.HOST2IO.Caution_Lights.Spare3_Light;
	sData.CAUTION_CH18 = (unsigned short)(((IOInfo[21].nMax - IOInfo[21].nMin) / 1000.0f) * nLampValue);

	//nLampValue = IsIOSLampTest() ? 1000 : m_stHOST2Cockpit.HOST2IO.Caution_Lights.Spare4_Light;
	sData.CAUTION_CH19 = (unsigned short)(((IOInfo[22].nMax - IOInfo[22].nMin) / 1000.0f) * nLampValue);


}

// CONTROL_STICK Encode
void CIOSWDataManager::EncodeControlStick(IOSW_to_IOBOARD& sData)
{
	///*	if ((m_stHOST2Cockpit.MTD_MODE == INIT_MODE) && (m_bStickInit == false)) {
	//		m_bStickInit = true;
	//	}
	//
	//	if (m_bStickInit && !m_bStickComplete)
	//	{
	//		sData.STICK_INIT		= 1;
	//		sData.STICK_TRIM_FRONT	= 0;
	//		sData.STICK_TRIM_REAR	= 0;
	//		sData.STICK_TRIM_LEFT	= 0;
	//		sData.STICK_TRIM_RIGHT	= 0;
	//
	//	}
	//	else
	//	{
	//	*/
	//sData.STICK_INIT = (unsigned char)m_stHOST2Cockpit.HOST2IO.Controlstick_Trim.CONTROLSTICK_INIT;
	//sData.STICK_TRIM_FRONT = (unsigned char)m_stHOST2Cockpit.HOST2IO.Controlstick_Trim.CONTROLSTICK_Forward_TRIM;
	//sData.STICK_TRIM_REAR = (unsigned char)m_stHOST2Cockpit.HOST2IO.Controlstick_Trim.CONTROLSTICK_Backward_TRIM;
	//sData.STICK_TRIM_LEFT = (unsigned char)m_stHOST2Cockpit.HOST2IO.Controlstick_Trim.CONTROLSTICK_Left_TRIM;
	//sData.STICK_TRIM_RIGHT = (unsigned char)m_stHOST2Cockpit.HOST2IO.Controlstick_Trim.CONTROLSTICK_Right_TRIM;
	//
	////	}
	//
	//	// update stick pwr status 2018.08.19 (if host traing_status is true then I/O board Rudder_init = 200 else 100)
	//if (m_stHOST2Cockpit.HOST2IO.Training_Status == true)
	//{
	//	sData.RUDDER_INIT = 200;
	//}
	//else
	//{
	//	sData.RUDDER_INIT = 100;
	//}

}

// GND_PWR_PANEL Encode 
void CIOSWDataManager::EncodeGNDPWRPanel(IOSW_to_IOBOARD& sData, const IOBOARD_INFORMATION IOInfo[])
{
	//ON_OFF_TYPE eOnOFF;
	//
	//eOnOFF = m_stHOST2Cockpit.HOST2IO.Solenoid_Coil_OFF[GND_PWR_1_SW];
	//SetDigitalOutputData(IOInfo[15], (int)eOnOFF, sData);
	//
	//eOnOFF = m_stHOST2Cockpit.HOST2IO.Solenoid_Coil_OFF[GND_PWR_2_SW];
	//SetDigitalOutputData(IOInfo[16], (int)eOnOFF, sData);
	//
	//eOnOFF = m_stHOST2Cockpit.HOST2IO.Solenoid_Coil_OFF[GND_PWR_3_SW];
	//SetDigitalOutputData(IOInfo[17], (int)eOnOFF, sData);
	//
	//eOnOFF = m_stHOST2Cockpit.HOST2IO.Solenoid_Coil_OFF[GND_PWR_4_SW];
	//SetDigitalOutputData(IOInfo[18], (int)eOnOFF, sData);
	//
	//eOnOFF = m_stHOST2Cockpit.HOST2IO.Solenoid_Coil_OFF[GND_PWR_PACS_SW];
	//SetDigitalOutputData(IOInfo[19], (int)eOnOFF, sData);
	//
	//eOnOFF = m_stHOST2Cockpit.HOST2IO.Solenoid_Coil_OFF[GND_PWR_ADCP_AIU_SW];
	//SetDigitalOutputData(IOInfo[20], (int)eOnOFF, sData);

}

// ARMAMENT_SAFETY_OVERRIDE_SWITCH Encode
void CIOSWDataManager::EncodeArmamentSafetyOverrideSwitch(IOSW_to_IOBOARD& sData, const IOBOARD_INFORMATION IOInfo[])
{
	//ON_OFF_TYPE eOnOFF = m_stHOST2Cockpit.HOST2IO.Solenoid_Coil_OFF[ARMAMENT_SAFETY_OVERRIDE_SW];
	//
	//SetDigitalOutputData(IOInfo[18], (int)eOnOFF, sData);

}


// GND_TEST_PANEL Encode
void CIOSWDataManager::EncodeGNDTestPanel(IOSW_to_IOBOARD& sData, const IOBOARD_INFORMATION IOInfo[])
{
	////int nLampValue = IsIOSLampTest() ? 1000 : m_stHOST2Cockpit.HOST2IO.Ground_Test_Lights.Left_Pump_Light;
	//sData.CAUTION_CH0 = (unsigned short)(((IOInfo[19].nMax - IOInfo[19].nMin) / 1000.0f) * nLampValue);
	//
	////nLampValue = IsIOSLampTest() ? 1000 : m_stHOST2Cockpit.HOST2IO.Ground_Test_Lights.Right_Pump_Light;
	//sData.CAUTION_CH1 = (unsigned short)(((IOInfo[20].nMax - IOInfo[20].nMin) / 1000.0f) * nLampValue);
	//
	////nLampValue = IsIOSLampTest() ? 1000 : m_stHOST2Cockpit.HOST2IO.Ground_Test_Lights.Util_A_Light;
	//sData.CAUTION_CH2 = (unsigned short)(((IOInfo[21].nMax - IOInfo[21].nMin) / 1000.0f) * nLampValue);
	//
	////nLampValue = IsIOSLampTest() ? 1000 : m_stHOST2Cockpit.HOST2IO.Ground_Test_Lights.Util_B_Light;
	//sData.CAUTION_CH3 = (unsigned short)(((IOInfo[22].nMax - IOInfo[22].nMin) / 1000.0f) * nLampValue);
	//
	////nLampValue = IsIOSLampTest() ? 1000 : m_stHOST2Cockpit.HOST2IO.Ground_Test_Lights.PC1_A_Light;
	//sData.CAUTION_CH4 = (unsigned short)(((IOInfo[23].nMax - IOInfo[23].nMin) / 1000.0f) * nLampValue);
	//
	////nLampValue = IsIOSLampTest() ? 1000 : m_stHOST2Cockpit.HOST2IO.Ground_Test_Lights.PC1_B_Light;
	//sData.CAUTION_CH5 = (unsigned short)(((IOInfo[24].nMax - IOInfo[24].nMin) / 1000.0f) * nLampValue);
	//
	////nLampValue = IsIOSLampTest() ? 1000 : m_stHOST2Cockpit.HOST2IO.Ground_Test_Lights.PC2_A_Light;
	//sData.CAUTION_CH6 = (unsigned short)(((IOInfo[25].nMax - IOInfo[25].nMin) / 1000.0f) * nLampValue);
	//
	////nLampValue = IsIOSLampTest() ? 1000 : m_stHOST2Cockpit.HOST2IO.Ground_Test_Lights.PC2_B_Light;
	//sData.CAUTION_CH7 = (unsigned short)(((IOInfo[26].nMax - IOInfo[26].nMin) / 1000.0f) * nLampValue);
	//
	////nLampValue = IsIOSLampTest() ? 1000 : m_stHOST2Cockpit.HOST2IO.Ground_Test_Lights.Xfer_Pump_Light;
	//sData.CAUTION_CH8 = (unsigned short)(((IOInfo[27].nMax - IOInfo[27].nMin) / 1000.0f) * nLampValue);
	//
	////nLampValue = IsIOSLampTest() ? 1000 : m_stHOST2Cockpit.HOST2IO.Ground_Test_Lights.Hook_Light;
	//sData.CAUTION_CH9 = (unsigned short)(((IOInfo[28].nMax - IOInfo[28].nMin) / 1000.0f) * nLampValue);
	//
	////nLampValue = IsIOSLampTest() ? 1000 : m_stHOST2Cockpit.HOST2IO.Ground_Test_Lights.Left_Bst_Pump_Light;
	//sData.CAUTION_CH10 = (unsigned short)(((IOInfo[29].nMax - IOInfo[29].nMin) / 1000.0f) * nLampValue);
	//
	////nLampValue = IsIOSLampTest() ? 1000 : m_stHOST2Cockpit.HOST2IO.Ground_Test_Lights.Right_Bst_Pump_Light;
	//sData.CAUTION_CH11 = (unsigned short)(((IOInfo[30].nMax - IOInfo[30].nMin) / 1000.0f) * nLampValue);
	//
	////nLampValue = IsIOSLampTest() ? 1000 : m_stHOST2Cockpit.HOST2IO.Ground_Test_Lights.Bingo_Fuel_Light;
	//sData.CAUTION_CH12 = (unsigned short)(((IOInfo[31].nMax - IOInfo[31].nMin) / 1000.0f) * nLampValue);
	//
	////nLampValue = IsIOSLampTest() ? 1000 : m_stHOST2Cockpit.HOST2IO.Ground_Test_Lights.Jfs_Low_Light;
	//sData.CAUTION_CH13 = (unsigned short)(((IOInfo[32].nMax - IOInfo[32].nMin) / 1000.0f) * nLampValue);
	//
	////nLampValue = IsIOSLampTest() ? 1000 : m_stHOST2Cockpit.HOST2IO.Ground_Test_Lights.Inlet_Ice_Light;
	//sData.CAUTION_CH14 = (unsigned short)(((IOInfo[33].nMax - IOInfo[33].nMin) / 1000.0f) * nLampValue);
	//
	////nLampValue = IsIOSLampTest() ? 1000 : m_stHOST2Cockpit.HOST2IO.Ground_Test_Lights.Ecs_Light;
	//sData.CAUTION_CH15 = (unsigned short)(((IOInfo[34].nMax - IOInfo[34].nMin) / 1000.0f) * nLampValue);
	//
	////nLampValue = IsIOSLampTest() ? 1000 : m_stHOST2Cockpit.HOST2IO.Ground_Test_Lights.Anti_Skid_Light;
	//sData.CAUTION_CH16 = (unsigned short)(((IOInfo[35].nMax - IOInfo[35].nMin) / 1000.0f) * nLampValue);
	//
	////nLampValue = IsIOSLampTest() ? 1000 : m_stHOST2Cockpit.HOST2IO.Ground_Test_Lights.Spd_Bk_Light;
	//sData.CAUTION_CH17 = (unsigned short)(((IOInfo[36].nMax - IOInfo[36].nMin) / 1000.0f) * nLampValue);
	//
	////nLampValue = IsIOSLampTest() ? 1000 : m_stHOST2Cockpit.HOST2IO.Ground_Test_Lights.Spare1_Light;
	//sData.CAUTION_CH18 = (unsigned short)(((IOInfo[37].nMax - IOInfo[37].nMin) / 1000.0f) * nLampValue);
	//
	////nLampValue = IsIOSLampTest() ? 1000 : m_stHOST2Cockpit.HOST2IO.Ground_Test_Lights.Spare2_Light;
	//sData.CAUTION_CH19 = (unsigned short)(((IOInfo[38].nMax - IOInfo[38].nMin) / 1000.0f) * nLampValue);
}


// INTERIOR_LIGHTS_CONTROL_PANEL Encode
void CIOSWDataManager::EncodeInteriorLightsControlPanel(IOSW_to_IOBOARD& sData, const IOBOARD_INFORMATION IOInfo[])
{
	// IO idx 15 : BACK_LIGHT_POWER 
	//SetDimmingData(IOInfo[15], m_stHOST2Cockpit.HOST2IO.Console_Backlight, sData);
}

void CIOSWDataManager::EncodeHMDControlPanel(IOSW_to_IOBOARD& sData, const IOBOARD_INFORMATION IOInfo[])
{
	// IO idx  2 : BACK_LIGHT_POWER 
	//SetDimmingData(IOInfo[2], m_stHOST2Cockpit.HOST2IO.Console_Backlight, sData);

}

void CIOSWDataManager::EncodeStormFloodLightRH(IOSW_to_IOBOARD& sData, const IOBOARD_INFORMATION IOInfo[])
{
	/* IO idx  7 : STORM_FLOOD_LAMP
	   IO idx  8 : STORM_FLOOD_LAMP */
	int nLampValue = 0;

	//nLampValue = IsIOSLampTest() ? 1000 : m_stHOST2Cockpit.HOST2IO.Storm_Flood_Light;
	//SetAnalogOutputData(IOInfo[7], nLampValue, sData);

	//nLampValue = IsIOSLampTest() ? 1000 : m_stHOST2Cockpit.HOST2IO.Storm_Flood_Light;
	//SetAnalogOutputData(IOInfo[8], nLampValue, sData);
}


// Encode UFC
void CIOSWDataManager::EncodeUFC(IOSW_to_IOBOARD& sData, const IOBOARD_INFORMATION IOInfo[])
{
	// IO idx 43 : BACK_LIGHT_POWER  
	//SetDimmingData(IOInfo[43], m_stHOST2Cockpit.HOST2IO.UFC_Backlight, sData);

}

// Encode OXY COMM
void CIOSWDataManager::EncodeOXYCOMM(IOSW_to_IOBOARD& sData, const IOBOARD_INFORMATION IOInfo[])
{
	// IO idx  0 : Headset Volume
	//int nVolume = 0;
	//int nNewVolume = 0;
	//
	//nVolume = m_stCockpit2HOST.IO2HOST.Left_Panel.ICS_Volume_Knob;
	//
	//if (nVolume < 150)
	//	nNewVolume = 0;
	//else if (nVolume >= 150 && nVolume < 350)
	//	nNewVolume = 20;
	//else if (nVolume >= 350 && nVolume < 550)
	//	nNewVolume = 40;
	//else if (nVolume >= 550 && nVolume < 750)
	//	nNewVolume = 60;
	//else if (nVolume >= 750 && nVolume < 950)
	//	nNewVolume = 80;
	//else
	//	nNewVolume = 100;
	//
	//if (m_stCockpit2HOST.IO2HOST.Left_Panel.MIC_Switch == ORIDE_OFF)
	//{
	//	nNewVolume = 0;
	//}
	//
	//sData.CH0_WIDTH_28V = (unsigned short)nNewVolume;
}


// Encode SA
void CIOSWDataManager::EncodeSA(IOSW_to_IOBOARD& sData, const IOBOARD_INFORMATION IOInfo[])
{
	// IO idx  0 : BRIGHTNESS
	// sData.CH0_FREQ_28V = m_stHOST2Cockpit.HOST2IO.Inst_Backlight;

	if (GetInstConnected())
		sData.CH3_WIDTH_28V = 100;
	else
		sData.CH3_WIDTH_28V = 200;

}

// Encode AOA
void CIOSWDataManager::EncodeAOA(IOSW_to_IOBOARD& sData, const IOBOARD_INFORMATION IOInfo[])
{
	// IO idx  0 : BRIGHTNESS
	// sData.CH0_FREQ_28V = m_stHOST2Cockpit.HOST2IO.Inst_Backlight;
	if (GetInstConnected())
		sData.CH3_WIDTH_28V = 100;
	else
		sData.CH3_WIDTH_28V = 200;
}

// Encode SAI
void CIOSWDataManager::EncodeSAI(IOSW_to_IOBOARD& sData, const IOBOARD_INFORMATION IOInfo[])
{
	// IO idx  0 : BRIGHTNESS
	// sData.CH0_FREQ_28V = m_stHOST2Cockpit.HOST2IO.Inst_Backlight;
	if (GetInstConnected())
		sData.CH3_WIDTH_28V = 100;
	else
		sData.CH3_WIDTH_28V = 200;
}

// Encode VVI
void CIOSWDataManager::EncodeVVI(IOSW_to_IOBOARD& sData, const IOBOARD_INFORMATION IOInfo[])
{
	// IO idx  0 : BRIGHTNESS
	// sData.CH0_FREQ_28V = m_stHOST2Cockpit.HOST2IO.Inst_Backlight;
	if (GetInstConnected())
		sData.CH3_WIDTH_28V = 100;
	else
		sData.CH3_WIDTH_28V = 200;
}

// Encode Altimeter
void CIOSWDataManager::EncodeAltimeter(IOSW_to_IOBOARD& sData, const IOBOARD_INFORMATION IOInfo[])
{
	// IO idx  0 : BRIGHTNESS
	// sData.CH0_FREQ_28V = m_stHOST2Cockpit.HOST2IO.Inst_Backlight;
	if (GetInstConnected())
		sData.CH3_WIDTH_28V = 100;
	else
		sData.CH3_WIDTH_28V = 200;

}

// Encode Clock
void CIOSWDataManager::EncodeClock(IOSW_to_IOBOARD& sData, const IOBOARD_INFORMATION IOInfo[])
{
	// IO idx  0 : BRIGHTNESS
	// sData.CH0_FREQ_28V = m_stHOST2Cockpit.HOST2IO.Inst_Backlight;
	if (GetInstConnected())
		sData.CH3_WIDTH_28V = 100;
	else
		sData.CH3_WIDTH_28V = 200;
}

// Encode CAP
void CIOSWDataManager::EncodeCPA(IOSW_to_IOBOARD& sData, const IOBOARD_INFORMATION IOInfo[])
{
	// IO idx  0 : BRIGHTNESS
	// sData.CH0_FREQ_28V = m_stHOST2Cockpit.HOST2IO.Inst_Backlight;
	if (GetInstConnected())
		sData.CH3_WIDTH_28V = 100;
	else
		sData.CH3_WIDTH_28V = 200;
}

// Encode EEMD
void CIOSWDataManager::EncodeEEMD(IOSW_to_IOBOARD& sData, const IOBOARD_INFORMATION IOInfo[])
{
	// IO idx  0 : BRIGHTNESS
	// sData.CH0_FREQ_28V = m_stHOST2Cockpit.HOST2IO.Inst_Backlight;
	if (GetInstConnected())
		sData.CH3_WIDTH_28V = 100;
	else
		sData.CH3_WIDTH_28V = 200;
}

// Encode FQI
void CIOSWDataManager::EncodeFQI(IOSW_to_IOBOARD& sData, const IOBOARD_INFORMATION IOInfo[])
{
	// IO idx  0 : BRIGHTNESS
	// sData.CH0_FREQ_28V = m_stHOST2Cockpit.HOST2IO.Inst_Backlight;
	if (GetInstConnected())
		sData.CH3_WIDTH_28V = 100;
	else
		sData.CH3_WIDTH_28V = 200;
}


void CIOSWDataManager::DecodeIOBoardData(const int& nBoardID, const IOBOARD_INFORMATION IOInfo[])
{
	IOBOARD_to_IOSW sData;

	GetIOBoard2IOSWData(&sData, nBoardID);

	switch (nBoardID)
	{
	case 1: // Common B/D 
		// ARRESTING_HOOK_CONTROL_SWITCH
		DecodeArrestingHookControlSwitch(sData, IOInfo);

		// LANDING_GEAR_CONTROL_HANDLE
		DecodeLandingGearControlHandle(sData, IOInfo);

		// EMERGENCY_LANDING_GEAR_HANDLE
		DecodeEmergencyLandingGearHandle(sData, IOInfo);

		// PITCH_RATIO_SELECT_SWITCH
		DecodePitchRatioSelectSwitch(sData, IOInfo);

		// MPD(LH) 
		DecodeMPD_LH(sData, IOInfo);

		break;
	case 2:	// ARMAMENT_CONTROL_PANEL
		DecodeArmamentControlPanel(sData, IOInfo);
		break;
	case 3: // Common B/D
		// MASTER_CAUTION_LIGHT
		DecodeMasterCautionLight(sData, IOInfo);

		// FIRE_WARNING/EXTINGUISHING_PANEL
		DecodeFireWarningExtinguishtingPanel(sData, IOInfo);

		// EMERGENCY_JETTISON_BUTTON
		DecodeEmergencyJettisonButton(sData, IOInfo);

		// HUD_CONTROL_PANEL
		DecodeHCP(sData, IOInfo);

		// MPD(RH) 
		DecodeMPD_RH(sData, IOInfo);

		break;
	case 10: // Common B/D
		// DATA_TRANSFER_MODULE_RECEPTACLE 
		DecodeDataTransferModuleReceptacle(sData, IOInfo);
		break;
	case 15: // Common B/D
		// JET_FUEL_STR_CTRL_HDL/BRAKE_HOLD_SW
		DecodeJetFuelStrCtrlHDL_Break_Hold_Switch(sData, IOInfo);

		// EMERGENCY_VENT_CONTROL_HANDLE
		DecodeEmergencyVentCtrlHandle(sData, IOInfo);
		break;
	case 16: // Common B/D
		// STEERING_CTRL/EMERGECY_BK_HANDLE
		DecodeSteeringCtrlEmergecyBreakHande(sData, IOInfo);

		// CIRCUIT_BREAKER_PANEL(UPPER)
		// CIRCUIT_BREAKER_PANEL(LH)
		// CIRCUIT_BREAKER_PANEL(RH)
		DecodeCircuitBreakerPanel(sData, IOInfo);

		// MPCD
		DecodeMPCD(sData, IOInfo);

		break;
	case 17: // RUDDER_PADAL
		DecodeRudderPadal(sData, IOInfo);
		break;
	case 18: // CONTROL_STICK
		DecodeControlStick(sData, IOInfo);
		break;
	case 19: // GND_PWR_PANEL
		DecodeGNDPWRPanel(sData, IOInfo);
		break;
	case 20: // Common B/D
		// ANTI - G_PANEL
		DecodeAntiGPanel(sData, IOInfo);

		// CANOPY_JETTISON_HANDLE
		DecodeCanopyJettisonHandle(sData, IOInfo);

		// FLYUP_ENABLE_SWITCH
		DecodeFlyupEnableSwitch(sData, IOInfo);

		// SEAT_ADJUST_SWITCH
		DecodeSeatAdjustSwitch(sData, IOInfo);

		// IFF_ANTENNA_SELECT_SWITCH
		DecodeIFFAntennaSelectSwitch(sData, IOInfo);

		// EMERGENCY_AIR_REFUELING_SWITCH
		DecodeEmergencyAirRefuelingSwitch(sData, IOInfo);

		// ARMAMENT_SAFETY_OVERRIDE_SWITCH
		DecodeArmamentSafetyOverrideSwitch(sData, IOInfo);
		break;
	case 21: // GND_TEST_MAINTENANCE_DIAGNOSTIC_PANEL
		break;
	case 22: // REMOTE_INTERCOMM_CONTROL_PANEL
		DecodeRemoteIntercommControlPanel(sData, IOInfo);
		break;
	case 23: // FUEL_CONTROL_PANEL
		DecodeFuelControlPanel(sData, IOInfo);
		break;
	case 24: // MISCELLANEOUS_CONTROL_PANEL
		DecodeMiscellaneousControlPanel(sData, IOInfo);
		break;
	case 25: // CAS_CONTROL_PANEL
		DecodeCASControlPanel(sData, IOInfo);
		break;
	case 26: // EXTERIOR_LIGHTS_CONTROL_PANEL
		DecodeExteriorLightsControlPanel(sData, IOInfo);
		break;
	case 27: // SENSOR_CONTROL_PANEL
		DecodeSensorControlPanel(sData, IOInfo);
		break;
	case 28: // EW_CONTROL_PANEL
		DecodeEWControlPanel(sData, IOInfo);
		break;
	case 29: // ENGINE_CONTROL_PANEL
		DecodeEngineControlPanel(sData, IOInfo);
		break;
	case 30: // OXYGEN_REGULATOR
		DecodeOxygenRegulator(sData, IOInfo);
		break;
	case 31: // ECS_PANEL
		DecodeECSPanel(sData, IOInfo);
		break;
	case 32: // AIR_CONDITION_CONTROL_PANEL
		DecodeAirConditionControlPanel(sData, IOInfo);
		break;
	case 33: // INTERIOR_LIGHTS_CONTROL_PANEL
		DecodeInteriorLightsControlPanel(sData, IOInfo);
		break;
	case 34: // Common B/D
		// HMD_CONTROL_PANEL
		DecodeHMDControlPanel(sData, IOInfo);

		// CANOPY_CONTROL_HANDLE
		DecodeCanopyControlHandle(sData, IOInfo);

		// EJECTION_SEAT
		DecodeEjectionSeat(sData, IOInfo);
		break;
	case 35: // UFC
		DecodeUFC(sData, IOInfo);
		break;
	case 36: // TROTTLE QUADRANT
		DecodeThrottleQuadrant(sData, IOInfo);
		break;
	case 42: // SAI
		DecodeSAI(sData, IOInfo);
		break;
	case 43: // Altimeter
		DecodeAltimeter(sData, IOInfo);
		break;
	case 46: // Clock
		DecodeClock(sData, IOInfo);
		break;
	case 49: // FQI
		DecodeFQI(sData, IOInfo);
		break;
	default:
		break;
	}

	UpdateIOMonitoringData(nBoardID, sData);
}

void CIOSWDataManager::UpdateIOMonitoringData(const int& nBoardID, const IOBOARD_to_IOSW& sData)
{
	memcpy(&m_stIOSW2GUI.sIOBoard2IOSW[nBoardID], &sData, sizeof(IOBOARD_to_IOSW));
}

void CIOSWDataManager::UpdateIOMonitoringData(const int& nBoardID, const IOSW_to_IOBOARD& sData)
{
	memcpy(&m_stIOSW2GUI.sIOSW2IOBoard[nBoardID], &sData, sizeof(IOSW_to_IOBOARD));
}

// ARRESTING_HOOK_CONTROL_SWITCH Decode
void CIOSWDataManager::DecodeArrestingHookControlSwitch(const IOBOARD_to_IOSW& sData, const IOBOARD_INFORMATION IOInfo[])
{
	///* IO idx  0 : UP
	//   IO idx  1 : DOWN */
	//
	//UP_DOWN_TYPE eUpDown = UP_DOWN__DOWN;
	//
	//if (GetDigitalInputBit(IOInfo[0].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eUpDown = UP_DOWN__UP;
	//
	////  DOWN is no signal 
	////	if (GetDigitalInputBit(IOInfo[1].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	////		eUpDown = UP_DOWN__DOWN;
	//
	//m_stCockpit2HOST.IO2HOST.Main_Panel.Arresting_Hook_Switch = eUpDown;
}

// LANDING_GEAR_CONTROL_HANDLE Decode
void CIOSWDataManager::DecodeLandingGearControlHandle(const IOBOARD_to_IOSW& sData, const IOBOARD_INFORMATION IOInfo[])
{
	///* IO idx  4 : LEFT_PUSH
	//   IO idx  6 : NOSE_PUSH
	//   IO idx  8 : RIGHT_PUSH */
	//
	//   // LEFT, NOSE, RIGHT KAI Not used!!
	//
	//   // IO idx  9 : WARN_TONE_SIL_SW
	//ON_OFF_TYPE eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[9].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.Warn_Tone_Sil_Btn = eOnOFF;
	//
	///* IO idx 10 : LANDING_GEAR_DOWN
	//   IO idx 11 : LANDING_GEAR_UP */
	//UP_DOWN_TYPE eUpDown = UP_DOWN__DOWN;
	//
	//// DOWN or Up, Default is Down
	////if (GetDigitalInputBit(IOInfo[10].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	////	eUpDown = UP_DOWN__DOWN;
	//
	//if (GetDigitalInputBit(IOInfo[11].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eUpDown = UP_DOWN__UP;
	//
	//m_stCockpit2HOST.IO2HOST.Main_Panel.LDG_Gear_Switch = eUpDown;
}

// EMERGENCY_LANDING_GEAR_HANDLE Decode
void CIOSWDataManager::DecodeEmergencyLandingGearHandle(const IOBOARD_to_IOSW& sData, const IOBOARD_INFORMATION IOInfo[])
{
	///* IO idx 17 : PULL
	//   IO idx 18 : PUSH	*/
	//
	//PULL_PUSH_TYPE	eType = PUSH;
	//
	//if (GetDigitalInputBit(IOInfo[17].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eType = PULL;
	//
	//// PUSH or PULL, Default is PUSH
	////if (GetDigitalInputBit(IOInfo[18].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	////	eType = PUSH;
	//
	//m_stCockpit2HOST.IO2HOST.Main_Panel.Emerg_LDG_Switch = eType;
}

// PITCH_RADIO_SELECT_SWITCH Decode
void CIOSWDataManager::DecodePitchRatioSelectSwitch(const IOBOARD_to_IOSW& sData, const IOBOARD_INFORMATION IOInfo[])
{
	///* IO idx 21 : PITCH_RATIO_SEL_SW_EMER
	//   IO idx 22 : PITCH_RATIO_SEL_SW_AUTO	*/
	//
	//AUTO_EMERG_TYPE eType = EMERG_AUTO;
	//
	//if (GetDigitalInputBit(IOInfo[21].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eType = EMERG;
	//
	//// AUTO is no signal
	////if (GetDigitalInputBit(IOInfo[22].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	////	eType = EMERG_AUTO;
	//
	//m_stCockpit2HOST.IO2HOST.Main_Panel.Pitch_Ratio_Switch = eType;
}

// MPD LH Decode
void CIOSWDataManager::DecodeMPD_LH(const IOBOARD_to_IOSW& sData, const IOBOARD_INFORMATION IOInfo[])
{
	///* IO idx 24 : LEFT_1_TOP
	//   IO idx 25 : LEFT_2
	//   IO idx 26 : LEFT_3
	//   IO idx 27 : LEFT_4
	//   IO idx 28 : LEFT_5_BOTTOM 	   */
	//int nTemp = sData.SPARE0;
	//ON_OFF_TYPE eOnOFF = OFF;
	//
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[24].nChannel, nTemp);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.Left_MPD.S1 = eOnOFF;
	//
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[25].nChannel, nTemp);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.Left_MPD.S2 = eOnOFF;
	//
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[26].nChannel, nTemp);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.Left_MPD.S3 = eOnOFF;
	//
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[27].nChannel, nTemp);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.Left_MPD.S4 = eOnOFF;
	//
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[28].nChannel, nTemp);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.Left_MPD.S5 = eOnOFF;
	//
	///*	IO idx 39 : BOTTOM_1_LEFT
	//	IO idx 40 : BOTTOM_2
	//	IO idx 41 : BOTTOM_3
	//	IO idx 42 : BOTTOM_4
	//	IO idx 43 : BOTTOM_5_RIGHT  */
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[39].nChannel, nTemp);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.Left_MPD.S6 = eOnOFF;
	//
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[40].nChannel, nTemp);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.Left_MPD.S7 = eOnOFF;
	//
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[41].nChannel, nTemp);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.Left_MPD.S8 = eOnOFF;
	//
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[42].nChannel, nTemp);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.Left_MPD.S9 = eOnOFF;
	//
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[43].nChannel, nTemp);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.Left_MPD.S10 = eOnOFF;
	//
	///*	IO idx 34 : RIGHT_1_TOP
	//	IO idx 35 : RIGHT_2
	//	IO idx 36 : RIGHT_3
	//	IO idx 37 : RIGHT_4
	//	IO idx 38 : RIGHT_5_BOTTOM  */
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[38].nChannel, nTemp);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.Left_MPD.S11 = eOnOFF;
	//
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[37].nChannel, nTemp);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.Left_MPD.S12 = eOnOFF;
	//
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[36].nChannel, nTemp);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.Left_MPD.S13 = eOnOFF;
	//
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[35].nChannel, nTemp);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.Left_MPD.S14 = eOnOFF;
	//
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[34].nChannel, nTemp);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.Left_MPD.S15 = eOnOFF;
	//
	///*	IO idx 29 : TOP_1_LEFT
	//	IO idx 30 : TOP_2
	//	IO idx 31 : TOP_3
	//	IO idx 32 : TOP_4
	//	IO idx 33 : TOP_5_RIGHT	   */
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[33].nChannel, nTemp);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.Left_MPD.S16 = eOnOFF;
	//
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[32].nChannel, nTemp);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.Left_MPD.S17 = eOnOFF;
	//
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[31].nChannel, nTemp);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.Left_MPD.S18 = eOnOFF;
	//
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[30].nChannel, nTemp);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.Left_MPD.S19 = eOnOFF;
	//
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[29].nChannel, nTemp);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.Left_MPD.S20 = eOnOFF;
	//
	///*	IO idx 44 : CONT_UP
	//	IO idx 45 : CONT_DN
	//	IO idx 46 : BRT_UP
	//	IO idx 47 : BRT_DN
	//	IO idx 48 : ON
	//	IO idx 49 : OFF	*/
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[44].nChannel, nTemp);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.Left_MPD.CONT_UP = eOnOFF;
	//
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[45].nChannel, nTemp);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.Left_MPD.CONT_DOWN = eOnOFF;
	//
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[46].nChannel, nTemp);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.Left_MPD.BRT_UP = eOnOFF;
	//
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[47].nChannel, nTemp);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.Left_MPD.BRT_DOWN = eOnOFF;
	//
	//if (GetDigitalInputBit(IOInfo[48].nChannel, nTemp) == DI_HIGH)
	//{
	//	m_stCockpit2HOST.IO2HOST.Main_Panel.Left_MPD.PWR_ON = ON;
	//	m_stCockpit2HOST.IO2HOST.Main_Panel.Left_MPD.PWR_OFF = OFF;
	//}
	//
	//if (GetDigitalInputBit(IOInfo[49].nChannel, nTemp) == DI_HIGH)
	//{
	//	m_stCockpit2HOST.IO2HOST.Main_Panel.Left_MPD.PWR_ON = OFF;
	//	m_stCockpit2HOST.IO2HOST.Main_Panel.Left_MPD.PWR_OFF = ON;
	//}

}

// MPD RH Decode
void CIOSWDataManager::DecodeMPD_RH(const IOBOARD_to_IOSW& sData, const IOBOARD_INFORMATION IOInfo[])
{
	///*	IO idx 35 : LEFT_1_TOP
	//	IO idx 36 : LEFT_2
	//	IO idx 37 : LEFT_3
	//	IO idx 38 : LEFT_4
	//	IO idx 39 : LEFT_5_BOTTOM 	   */
	//int nTemp = sData.SPARE0;
	//ON_OFF_TYPE eOnOFF = OFF;
	//
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[35].nChannel, nTemp);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.Right_MPD.S1 = eOnOFF;
	//
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[36].nChannel, nTemp);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.Right_MPD.S2 = eOnOFF;
	//
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[37].nChannel, nTemp);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.Right_MPD.S3 = eOnOFF;
	//
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[38].nChannel, nTemp);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.Right_MPD.S4 = eOnOFF;
	//
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[39].nChannel, nTemp);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.Right_MPD.S5 = eOnOFF;
	//
	///*	IO idx 50 : BOTTOM_1_LEFT
	//	IO idx 51 : BOTTOM_2
	//	IO idx 52 : BOTTOM_3
	//	IO idx 53 : BOTTOM_4
	//	IO idx 54 : BOTTOM_5_RIGHT  */
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[50].nChannel, nTemp);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.Right_MPD.S6 = eOnOFF;
	//
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[51].nChannel, nTemp);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.Right_MPD.S7 = eOnOFF;
	//
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[52].nChannel, nTemp);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.Right_MPD.S8 = eOnOFF;
	//
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[53].nChannel, nTemp);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.Right_MPD.S9 = eOnOFF;
	//
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[54].nChannel, nTemp);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.Right_MPD.S10 = eOnOFF;
	//
	///*	IO idx 45 : RIGHT_1_TOP
	//	IO idx 46 : RIGHT_2
	//	IO idx 47 : RIGHT_3
	//	IO idx 48 : RIGHT_4
	//	IO idx 49 : RIGHT_5_BOTTOM  */
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[49].nChannel, nTemp);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.Right_MPD.S11 = eOnOFF;
	//
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[48].nChannel, nTemp);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.Right_MPD.S12 = eOnOFF;
	//
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[47].nChannel, nTemp);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.Right_MPD.S13 = eOnOFF;
	//
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[46].nChannel, nTemp);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.Right_MPD.S14 = eOnOFF;
	//
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[45].nChannel, nTemp);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.Right_MPD.S15 = eOnOFF;
	//
	///*	IO idx 40 : TOP_1_LEFT
	//	IO idx 41 : TOP_2
	//	IO idx 42 : TOP_3
	//	IO idx 43 : TOP_4
	//	IO idx 44 : TOP_5_RIGHT	   */
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[44].nChannel, nTemp);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.Right_MPD.S16 = eOnOFF;
	//
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[43].nChannel, nTemp);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.Right_MPD.S17 = eOnOFF;
	//
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[42].nChannel, nTemp);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.Right_MPD.S18 = eOnOFF;
	//
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[41].nChannel, nTemp);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.Right_MPD.S19 = eOnOFF;
	//
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[40].nChannel, nTemp);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.Right_MPD.S20 = eOnOFF;
	//
	///*	IO idx 55 : CONT_UP
	//	IO idx 56 : CONT_DN
	//	IO idx 57 : BRT_UP
	//	IO idx 58 : BRT_DN
	//	IO idx 59 : ON
	//	IO idx 60 : OFF	*/
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[55].nChannel, nTemp);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.Right_MPD.CONT_UP = eOnOFF;
	//
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[56].nChannel, nTemp);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.Right_MPD.CONT_DOWN = eOnOFF;
	//
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[57].nChannel, nTemp);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.Right_MPD.BRT_UP = eOnOFF;
	//
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[58].nChannel, nTemp);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.Right_MPD.BRT_DOWN = eOnOFF;
	//
	//if (GetDigitalInputBit(IOInfo[59].nChannel, nTemp) == DI_HIGH)
	//{
	//	m_stCockpit2HOST.IO2HOST.Main_Panel.Right_MPD.PWR_ON = ON;
	//	m_stCockpit2HOST.IO2HOST.Main_Panel.Right_MPD.PWR_OFF = OFF;
	//}
	//
	//if (GetDigitalInputBit(IOInfo[60].nChannel, nTemp) == DI_HIGH)
	//{
	//	m_stCockpit2HOST.IO2HOST.Main_Panel.Right_MPD.PWR_ON = OFF;
	//	m_stCockpit2HOST.IO2HOST.Main_Panel.Right_MPD.PWR_OFF = ON;
	//}
	//
	///*	eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[59].nChannel, nTemp);
	//	m_stCockpit2HOST.IO2HOST.Main_Panel.Right_MPD.PWR_ON = eOnOFF;
	//
	//	eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[60].nChannel, nTemp);
	//	m_stCockpit2HOST.IO2HOST.Main_Panel.Right_MPD.PWR_OFF = eOnOFF;*/
}

// MPCD Decode
void CIOSWDataManager::DecodeMPCD(const IOBOARD_to_IOSW& sData, const IOBOARD_INFORMATION IOInfo[])
{
	///*	IO idx 19 : LEFT_1_TOP
	//	IO idx 20 : LEFT_2
	//	IO idx 21 : LEFT_3
	//	IO idx 22 : LEFT_4
	//	IO idx 23 : LEFT_5_BOTTOM 	   */
	//int nTemp = sData.SPARE0;
	//ON_OFF_TYPE eOnOFF = OFF;
	//
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[19].nChannel, nTemp);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.MPCD.S1 = eOnOFF;
	//
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[20].nChannel, nTemp);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.MPCD.S2 = eOnOFF;
	//
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[21].nChannel, nTemp);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.MPCD.S3 = eOnOFF;
	//
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[22].nChannel, nTemp);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.MPCD.S4 = eOnOFF;
	//
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[23].nChannel, nTemp);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.MPCD.S5 = eOnOFF;
	//
	///*	IO idx 34 : BOTTOM_1_LEFT
	//	IO idx 35 : BOTTOM_2
	//	IO idx 36 : BOTTOM_3
	//	IO idx 37 : BOTTOM_4
	//	IO idx 38 : BOTTOM_5_RIGHT  */
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[34].nChannel, nTemp);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.MPCD.S6 = eOnOFF;
	//
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[35].nChannel, nTemp);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.MPCD.S7 = eOnOFF;
	//
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[36].nChannel, nTemp);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.MPCD.S8 = eOnOFF;
	//
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[37].nChannel, nTemp);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.MPCD.S9 = eOnOFF;
	//
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[38].nChannel, nTemp);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.MPCD.S10 = eOnOFF;
	//
	///*	IO idx 29 : RIGHT_1_TOP
	//	IO idx 30 : RIGHT_2
	//	IO idx 31 : RIGHT_3
	//	IO idx 32 : RIGHT_4
	//	IO idx 33 : RIGHT_5_BOTTOM  */
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[33].nChannel, nTemp);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.MPCD.S11 = eOnOFF;
	//
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[32].nChannel, nTemp);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.MPCD.S12 = eOnOFF;
	//
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[31].nChannel, nTemp);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.MPCD.S13 = eOnOFF;
	//
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[30].nChannel, nTemp);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.MPCD.S14 = eOnOFF;
	//
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[29].nChannel, nTemp);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.MPCD.S15 = eOnOFF;
	//
	///*	IO idx 24 : TOP_1_LEFT
	//	IO idx 25 : TOP_2
	//	IO idx 26 : TOP_3
	//	IO idx 27 : TOP_4
	//	IO idx 28 : TOP_5_RIGHT	   */
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[28].nChannel, nTemp);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.MPCD.S16 = eOnOFF;
	//
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[27].nChannel, nTemp);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.MPCD.S17 = eOnOFF;
	//
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[26].nChannel, nTemp);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.MPCD.S18 = eOnOFF;
	//
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[25].nChannel, nTemp);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.MPCD.S19 = eOnOFF;
	//
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[24].nChannel, nTemp);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.MPCD.S20 = eOnOFF;
	//
	///*	IO idx 39 : CONT_UP
	//	IO idx 40 : CONT_DN
	//	IO idx 41 : BRT_UP
	//	IO idx 42 : BRT_DN
	//	IO idx 43 : ON
	//	IO idx 44 : OFF	*/
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[39].nChannel, nTemp);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.MPCD.CONT_UP = eOnOFF;
	//
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[40].nChannel, nTemp);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.MPCD.CONT_DOWN = eOnOFF;
	//
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[41].nChannel, nTemp);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.MPCD.BRT_UP = eOnOFF;
	//
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[42].nChannel, nTemp);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.MPCD.BRT_DOWN = eOnOFF;
	//
	//if (GetDigitalInputBit(IOInfo[43].nChannel, nTemp) == DI_HIGH)
	//{
	//	m_stCockpit2HOST.IO2HOST.Main_Panel.MPCD.PWR_ON = ON;
	//	m_stCockpit2HOST.IO2HOST.Main_Panel.MPCD.PWR_OFF = OFF;
	//}
	//
	//if (GetDigitalInputBit(IOInfo[44].nChannel, nTemp) == DI_HIGH)
	//{
	//	m_stCockpit2HOST.IO2HOST.Main_Panel.MPCD.PWR_ON = OFF;
	//	m_stCockpit2HOST.IO2HOST.Main_Panel.MPCD.PWR_OFF = ON;
	//}
	//
	///*
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[43].nChannel, nTemp);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.MPCD.PWR_ON = eOnOFF;
	//
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[44].nChannel, nTemp);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.MPCD.PWR_OFF = eOnOFF;*/
}

// ARMAMENT CONTROL PANEL Decode
void CIOSWDataManager::DecodeArmamentControlPanel(const IOBOARD_to_IOSW& sData, const IOBOARD_INFORMATION IOInfo[])
{
	///* IO idx 0 : FF
	//   IO idx 1 : RET
	//   IO idx 2 : ALTN_REL
	//   IO idx 3 : OFF
	//   IO idx 4 : COMBAT
	//   IO idx 5 : A/A
	//   IO idx 6 : A/G */
	//ARMT_CONTROL_TYPE eType = m_stCockpit2HOST.IO2HOST.Main_Panel.ARMT_Control_Switch;
	//
	//if (GetDigitalInputBit(IOInfo[0].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eType = ARMT_CONTROLFF;
	//
	//if (GetDigitalInputBit(IOInfo[1].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eType = ARMT_CONTROLRET;
	//
	//if (GetDigitalInputBit(IOInfo[2].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eType = ARMT_CONTROLREL;
	//
	//if (GetDigitalInputBit(IOInfo[3].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eType = ARMT_CONTROLOFF;
	//
	//if (GetDigitalInputBit(IOInfo[4].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eType = ARMT_CONTROLCOMBAT;
	//
	//if (GetDigitalInputBit(IOInfo[5].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eType = ARMT_CONTROLA_A;
	//
	//if (GetDigitalInputBit(IOInfo[6].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eType = ARMT_CONTROLA_G;
	//
	//m_stCockpit2HOST.IO2HOST.Main_Panel.ARMT_Control_Switch = eType;
	//
	///* IO idx 7 : ARMT_SW_JETT */
	//ON_OFF_TYPE eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[7].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.ARMT_JETT_Switch = eOnOFF;
	//
	///* IO idx 8 : GUN SW ARM
	//   IO idx 9 : GUN SW SAFE */
	//ARMT_TYPE eARMT = ARMT_SAFE;
	//
	//if (GetDigitalInputBit(IOInfo[8].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eARMT = ARMT_ARM;
	//
	////	if (GetDigitalInputBit(IOInfo[9].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	////		eARMT = ARMT_SAFE;
	//
	//m_stCockpit2HOST.IO2HOST.Main_Panel.ARMT_Gun_Switch = eARMT;
	//
	///* IO idx 10 : MASTER SW ARM
	//   IO idx 11 : MASTER SW SAFE */
	//eARMT = ARMT_SAFE;
	//
	//if (GetDigitalInputBit(IOInfo[10].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eARMT = ARMT_ARM;
	//
	////	if (GetDigitalInputBit(IOInfo[11].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	////		eARMT = ARMT_SAFE;
	//
	//m_stCockpit2HOST.IO2HOST.Main_Panel.ARMT_Master_Switch = eARMT;

}

// MASTER_CAUTION_LIGHT Decode
void CIOSWDataManager::DecodeMasterCautionLight(const IOBOARD_to_IOSW& sData, const IOBOARD_INFORMATION IOInfo[])
{
	// IO idx  1 : Master Cuation SW
	//ON_OFF_TYPE eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[1].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.Master_Caution_Btn = eOnOFF;

}

// FIRE_WARNING/EXTINGUISHING_PANEL Decode
void CIOSWDataManager::DecodeFireWarningExtinguishtingPanel(const IOBOARD_to_IOSW& sData, const IOBOARD_INFORMATION IOInfo[])
{
	///* IO idx  2 : DISCHARGE_SW_DISCHARGE
	//   IO idx  3 : DISCHARGE_SW_OFF
	//   IO idx  4 : DISCHARGE_SW_TEST */
	//DISCHARGE_TYPE eDischarge = DISCHARGE_OFF;
	//if (GetDigitalInputBit(IOInfo[2].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eDischarge = DISCHARGE_DISCHARGE;
	//
	//// DISCHARG or TEST, OFF signal not used!!
	////if (GetDigitalInputBit(IOInfo[3].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	////	eDischarge = DISCHARGE_OFF;
	//
	//if (GetDigitalInputBit(IOInfo[4].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eDischarge = DISCHARGE_TEST;
	//
	//m_stCockpit2HOST.IO2HOST.Main_Panel.Discharge_Switch = eDischarge;
	//
	//// IO idx  5 : AMAR_FIRE
	//ON_OFF_TYPE eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[5].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.AMAD_Fire_Btn = eOnOFF;
	//
	//// IO idx  6 : LEFT_ENGINE_FIRE
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[6].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.Left_Engine_Fire_Btn = eOnOFF;
	//
	//// IO idx  7 : RIGHT_ENGINE_FIRE
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[7].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.Right_Engine_Fire_Btn = eOnOFF;
}

// EMERGENCY_JETTISON_BUTTON Decode
void CIOSWDataManager::DecodeEmergencyJettisonButton(const IOBOARD_to_IOSW& sData, const IOBOARD_INFORMATION IOInfo[])
{
	//// IO idx 15 : PUSH_TO_JETT_SW_PUSH
	//ON_OFF_TYPE eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[15].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.Emergency_Jettison_Btn = eOnOFF;

}

// HUD_CONTROL_PANEL Decode
void CIOSWDataManager::DecodeHCP(const IOBOARD_to_IOSW& sData, const IOBOARD_INFORMATION IOInfo[])
{
	//unsigned short nSybolBRTKnob = 0;
	//
	//// IO idx 17 : SYMBOL_BRT_KNOB
	////nSybolBRTKnob = GetAnalogInputData(IOInfo[17], sData, m_stCockpit2HOST.IO2HOST.Main_Panel.Symbol_Brt_Knob);
	//nSybolBRTKnob = GetAnalogInputData(IOInfo[17], m_stCockpit2HOST.IO2HOST.Main_Panel.Symbol_Brt_Knob, sData);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.Symbol_Brt_Knob = nSybolBRTKnob;
	//
	//// IO idx 18 : SYMBOL_BRT_KNOB_OFF (ICD not find!!)
	//
	//// IO idx 19 : SYMBOL_DECLUTTER_NORM
	//// IO idx 20 : SYMBOL_DECLUTTER_REJ2
	//SYM_DECLUTTER_TYPE eSymDeclutter = SYM_BRT_REJ1;
	//
	//if (GetDigitalInputBit(IOInfo[19].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eSymDeclutter = SYM_BRT_NORM;
	//
	//if (GetDigitalInputBit(IOInfo[20].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eSymDeclutter = SYM_BRT_REJ2;
	//
	//m_stCockpit2HOST.IO2HOST.Main_Panel.Symbol_Declutter_Switch = eSymDeclutter;
	//
	//// IO idx 21 : DAY_NIGHT_AUTO_SWITCH_DAY
	//// IO idx 22 : DAY_NIGHT_AUTO_SWITCH_NIGHT
	//DAY_NIGHT_TYPE eDayNight = DN_AUTO;
	//
	//if (GetDigitalInputBit(IOInfo[21].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eDayNight = DN_DAY;
	//
	//if (GetDigitalInputBit(IOInfo[22].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eDayNight = DN_NIGHT;
	//
	//m_stCockpit2HOST.IO2HOST.Main_Panel.Day_Night_Switch = eDayNight;
	//
	//// IO idx 23 : TEST_BUTTON
	//ON_OFF_TYPE eOnOff = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[23].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.Test_Btn = eOnOff;
	//
	//// IO idx 24 : VIDEO_BRIGHTNESS_KNOB
	//// IO idx 25 : VIDEO_CONTRAST_KNOB
	//unsigned short nVideoBRTKnob = 0;
	//unsigned short nVideoCntKnob = 0;
	//
	////nVideoBRTKnob = GetAnalogInputData(IOInfo[24], sData, m_stCockpit2HOST.IO2HOST.Main_Panel.Video_Brt_Knob);
	//nVideoBRTKnob = GetAnalogInputData(IOInfo[24], m_stCockpit2HOST.IO2HOST.Main_Panel.Video_Brt_Knob, sData);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.Video_Brt_Knob = nVideoBRTKnob;
	//
	////nVideoCntKnob = GetAnalogInputData(IOInfo[25], sData, m_stCockpit2HOST.IO2HOST.Main_Panel.Video_Cont_Knob);
	//nVideoCntKnob = GetAnalogInputData(IOInfo[25], m_stCockpit2HOST.IO2HOST.Main_Panel.Video_Cont_Knob, sData);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.Video_Cont_Knob = nVideoCntKnob;
	//
	//// IO idx 26 : VIDEO_CONTRAST_OFF ICD not Find!!
	//
	//// IO idx 28 : A/A_SWITCH
	//// IO idx 30 : A/G_SWITCH
	//// IO idx 32 : NAV_SWITCH
	//// IO idx 34 : INST_SWITCH
	//
	//UFC_MODE_TYPE eUFCMode = m_stCockpit2HOST.IO2HOST.Main_Panel.UFC_Mode_Button;
	//bool bExtPwrReset = m_stHOST2Cockpit.HOST2IO.Ext_Pwr_Reset;
	//
	//// update by hslim 2019.08.19 HCP A/A Default Switch (if bExtPwrReset is true then A/A switch is ON)
	//if ((GetDigitalInputBit(IOInfo[28].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH) || bExtPwrReset == true)
	//	eUFCMode = UFC_MODE_A_A;
	//
	//if (GetDigitalInputBit(IOInfo[30].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eUFCMode = UFC_MODE_A_G;
	//
	//if (GetDigitalInputBit(IOInfo[32].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eUFCMode = UFC_MODE_NAV;
	//
	//if (GetDigitalInputBit(IOInfo[34].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eUFCMode = UFC_MODE_INST;
	//
	//m_stCockpit2HOST.IO2HOST.Main_Panel.UFC_Mode_Button = eUFCMode;

}


// DATA_TRANSFER_MODULE_RECEPTACLE Decode
void CIOSWDataManager::DecodeDataTransferModuleReceptacle(const IOBOARD_to_IOSW& sData, const IOBOARD_INFORMATION IOInfo[])
{
	//// IO idx 12 : DTM_RECEPTACLE
	//ON_OFF_TYPE eOnOff = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[12].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.DTM_Receptacle = eOnOff;
}

// JET_FUEL_STR_CTRL_HDL/BRAKE_HOLD_SW Decode
void CIOSWDataManager::DecodeJetFuelStrCtrlHDL_Break_Hold_Switch(const IOBOARD_to_IOSW& sData, const IOBOARD_INFORMATION IOInfo[])
{
	///* IO idx  4 : JFS_START_FIRST
	//   IO idx  5 : JFS_START_SECOND */
	//JET_STARTER_TYPE ePullPush = JET_STARTER_NORM;
	//if (GetDigitalInputBit(IOInfo[4].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	ePullPush = JET_STARTER_FIR;
	//
	//if (GetDigitalInputBit(IOInfo[5].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	ePullPush = JET_STARTER_SEC;
	//
	//m_stCockpit2HOST.IO2HOST.Main_Panel.JET_Fuel_Starter_Switch = ePullPush;
	//
	///* IO idx  6 : BRAKE_HOLD_SW_ON
	//   IO idx  7 : BRAKE_HOLD_SW_OFF */
	//ON_OFF_TYPE eOnOff = OFF;
	//if (GetDigitalInputBit(IOInfo[6].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eOnOff = ON;
	//
	//if (GetDigitalInputBit(IOInfo[7].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eOnOff = OFF;
	//
	//m_stCockpit2HOST.IO2HOST.Main_Panel.Brake_Hold_Switch = eOnOff;

}

// EMERGENCY_VENT_CONTROL_HANDLE Decode
void CIOSWDataManager::DecodeEmergencyVentCtrlHandle(const IOBOARD_to_IOSW& sData, const IOBOARD_INFORMATION IOInfo[])
{
	///* IO idx 10 : EMERG_VENT_HANDLE_PULL
	//   IO idx 11 : EMERG_VENT_HANDLE_PUSH */
	//PULL_PUSH_TYPE ePullPush = PUSH;
	//if (GetDigitalInputBit(IOInfo[10].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	ePullPush = PULL;
	//
	//// PUSH or PULL, default PUSH Signal
//	//if (GetDigitalInputBit(IOInfo[10].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
//	//	ePullPush = PUSH;
	//
	//m_stCockpit2HOST.IO2HOST.Main_Panel.Emerg_Vent_Switch = ePullPush;

}

// STEERING_CTRL/EMERGECY_BK_HANDLE Decode
void CIOSWDataManager::DecodeSteeringCtrlEmergecyBreakHande(const IOBOARD_to_IOSW& sData, const IOBOARD_INFORMATION IOInfo[])
{
	///* IO idx  0 : STEER_HANDLE_PULL
	//   IO idx  1 : EMERG_BK_PUSH */
	//PULL_PUSH_TYPE ePullPush = PUSH;
	//
	//if (GetDigitalInputBit(IOInfo[0].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	ePullPush = PULL;
	//
	//// PULL or PUSH, default PUSH signal
	////if (GetDigitalInputBit(IOInfo[1].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	////	ePullPush = PUSH;
	//
	//m_stCockpit2HOST.IO2HOST.Main_Panel.Emerg_Brake_Steer_Switch = ePullPush;

}

// CIRCUIT_BREAKER_PANEL Decode
/*	0 - AFCS ESS DC(A1)
	1 - AFCS ESS DC(A2)
	2 - AFCS ESS DC(A3)
	3 - LG(A4)
	4 - NWS(A5)
	5 - SPD BK(A6)
	6 - L PITOT HEAT(A7)
	7 - R PITOT HEAT(A8)
	8 - AFCS ESS AC(B1)
	9 - AFCS ESS AC(B2)
	10 - FLAP(B3)
	11 - AFCS DC(B4)
	12 - AFCS DC(B5)
	13 - AFCS DC(B6)
KAI ICD CB Array[index : 0 ~ 13] */
void CIOSWDataManager::DecodeCircuitBreakerPanel(const IOBOARD_to_IOSW& sData, const IOBOARD_INFORMATION IOInfo[])
{
	//// IO idx  2 : AFCS_ESS_DC_#1
	//Circuit_Breaker_Type eCB = (Circuit_Breaker_Type)GetDigitalInputBit(IOInfo[2].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.Center_CB[0] = eCB;
	//
	//// IO idx  3 : AFCS_ESS_DC_#2
	//eCB = (Circuit_Breaker_Type)GetDigitalInputBit(IOInfo[3].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.Center_CB[1] = eCB;
	//
	//// IO idx  4 : AFCS_ESS_DC_#3
	//eCB = (Circuit_Breaker_Type)GetDigitalInputBit(IOInfo[4].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.Center_CB[2] = eCB;
	//
	//// IO idx  5 : AFCS_ESS_AC_#1
	//eCB = (Circuit_Breaker_Type)GetDigitalInputBit(IOInfo[5].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.Center_CB[8] = eCB;
	//
	//// IO idx  6 : AFCS_ESS_AC_#2
	//eCB = (Circuit_Breaker_Type)GetDigitalInputBit(IOInfo[6].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.Center_CB[9] = eCB;
	//
	//// IO idx  7 : FLAP
	//eCB = (Circuit_Breaker_Type)GetDigitalInputBit(IOInfo[7].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.Center_CB[10] = eCB;
	//
	//// IO idx  9 : LG
	//eCB = (Circuit_Breaker_Type)GetDigitalInputBit(IOInfo[9].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.Center_CB[3] = eCB;
	//
	//// IO idx  10 : NWS
	//eCB = (Circuit_Breaker_Type)GetDigitalInputBit(IOInfo[10].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.Center_CB[4] = eCB;
	//
	//// IO idx  11 : SPD_BK
	//eCB = (Circuit_Breaker_Type)GetDigitalInputBit(IOInfo[11].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.Center_CB[5] = eCB;
	//
	//// IO idx  12 : L_PITOT_HEAT
	//eCB = (Circuit_Breaker_Type)GetDigitalInputBit(IOInfo[12].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.Center_CB[6] = eCB;
	//
	//// IO idx  13 : R_PITOT_HEAT
	//eCB = (Circuit_Breaker_Type)GetDigitalInputBit(IOInfo[13].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.Center_CB[7] = eCB;
	//
	//// IO idx  15 : AFCS_ESS_DC_#1
	//eCB = (Circuit_Breaker_Type)GetDigitalInputBit(IOInfo[15].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.Center_CB[11] = eCB;
	//
	//// IO idx  16 : AFCS_ESS_DC_#2
	//eCB = (Circuit_Breaker_Type)GetDigitalInputBit(IOInfo[16].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.Center_CB[12] = eCB;
	//
	//// IO idx  17 : AFCS_ESS_DC_#3
	//eCB = (Circuit_Breaker_Type)GetDigitalInputBit(IOInfo[17].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.Center_CB[13] = eCB;

}

// Rudder Padal Decode
void CIOSWDataManager::DecodeRudderPadal(const IOBOARD_to_IOSW& sData, const IOBOARD_INFORMATION IOInfo[])
{
	//m_stCockpit2HOST.IO2HOST.Main_Panel.Rudder_Pedal = (int)sData.YAW;
	//
	//if (sData.BRAKE_LH == 1)
	//	m_stCockpit2HOST.IO2HOST.Main_Panel.Left_Brake_Pedal = OFF;
	//else
	//	m_stCockpit2HOST.IO2HOST.Main_Panel.Left_Brake_Pedal = ON;
	//
	//if (sData.BRAKE_RH == 1)
	//	m_stCockpit2HOST.IO2HOST.Main_Panel.Right_Brake_Pedal = OFF;
	//else
	//	m_stCockpit2HOST.IO2HOST.Main_Panel.Right_Brake_Pedal = ON;
	//
	//ON_OFF_TYPE eTrimComplete = (ON_OFF_TYPE)sData.RUDDER_TRIM_COMPLETE;
	//
	//if (eTrimComplete == ON) {
	//	m_bRudderComplete = true;
	//	m_bRudderInit = false;
	//}
	//else
	//{
	//	m_bRudderComplete = false;
	//}
	//
	//m_stCockpit2HOST.IO2HOST.Main_Panel.Rudder_Trim_Complete = eTrimComplete;

}

// Control Stick Decode
void CIOSWDataManager::DecodeControlStick(const IOBOARD_to_IOSW& sData, const IOBOARD_INFORMATION IOInfo[])
{
	//int nPitch = (int)sData.AHRS_PITCH;
	//int nRoll = (int)sData.AHRS_ROLL;
	//
	//// IO idx  0 : GRIP_PITCH
	//m_stCockpit2HOST.IO2HOST.Main_Panel.Pitch_Stick = nPitch;
	//
	//// IO idx  1 : GRIP_ROLL
	//m_stCockpit2HOST.IO2HOST.Main_Panel.Roll_Stick = nRoll;
	//
	//
	//// 2019.03.05 Stick Enum Apply
	//STICK_POSITION_TYPE eStickType = STICK_IGNORE;
	//
	//if (nPitch >= m_nFrontCenter && nPitch <= m_nRearCenter && nRoll >= m_nRightCenter && nRoll <= m_nLeftCenter)
	//	eStickType = STICK_CENTER;
	//
	//if (nPitch <= m_nFrontLimit)
	//	eStickType = STICK_UP_LIMIT;
	//
	//if (nPitch >= m_nRearLimit)
	//	eStickType = STICK_DOWN_LIMIT;
	//
	//if (nRoll <= m_nRightLimit)
	//	eStickType = STICK_RIGHT_LIMIT;
	//
	//if (nRoll >= m_nLeftLimit)
	//	eStickType = STICK_LEFT_LIMIT;
	//
	//m_stCockpit2HOST.IO2HOST.Main_Panel.Stick_Position = eStickType;
	//
	//// IO idx  2 : PADDLE_SWITCH
	//ON_OFF_TYPE eOnOFF = OFF;
	//if (GetDigitalInputBit(IOInfo[2].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eOnOFF = ON;
	//
	//m_stCockpit2HOST.IO2HOST.Main_Panel.Paddle_Switch = eOnOFF;
	//
	//// IO idx  3 : CASTLE_UP	
	//// IO idx  4 : CASTLE_DN	
	//// IO idx  5 : CASTLE_R	
	//// IO idx  6 : CASTLE_L	
	//// IO idx  7 : CASTLE_DEPRESS
	//CASTLE_TYPE eCastle = CASTLE_CENTER;
	//
	//if (GetDigitalInputBit(IOInfo[3].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eCastle = CASTLE_UP;
	//
	//if (GetDigitalInputBit(IOInfo[4].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eCastle = CASTLE_DOWN;
	//
	//if (GetDigitalInputBit(IOInfo[5].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eCastle = CASTLE_RIGHT;
	//
	//if (GetDigitalInputBit(IOInfo[6].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eCastle = CASTLE_LEFT;
	//
	//if (GetDigitalInputBit(IOInfo[7].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eCastle = CASTLE_PUSH;
	//
	//m_stCockpit2HOST.IO2HOST.Main_Panel.Castle_Switch = eCastle;
	//
	//// IO idx  8 : WPN_DEPRESS
	//eOnOFF = OFF;
	//if (GetDigitalInputBit(IOInfo[8].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eOnOFF = ON;
	//
	//m_stCockpit2HOST.IO2HOST.Main_Panel.Weapon_Release_Btn = eOnOFF;
	//
	//// IO idx  9 : COOLIE_UP	
	//// IO idx 10 : COOLIE_DN	
	//// IO idx 11 : COOLIE_R	
	//// IO idx 12 : COOLIE_L	
	//// IO idx 13 : COOLIE_DETENT
	//TRIM_TYPE eTrim = TRIM_CENTER;
	//
	//if (GetDigitalInputBit(IOInfo[9].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eTrim = TRIM_UP;
	//
	//if (GetDigitalInputBit(IOInfo[10].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eTrim = TRIM_DOWN;
	//
	//if (GetDigitalInputBit(IOInfo[11].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eTrim = TRIM_RIGHT;
	//
	//if (GetDigitalInputBit(IOInfo[12].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eTrim = TRIM_LEFT;
	//
	//if (GetDigitalInputBit(IOInfo[13].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eTrim = TRIM_PUSH;
	//
	//m_stCockpit2HOST.IO2HOST.Main_Panel.Trim_Switch = eTrim;
	//
	//// IO idx 14 : CHAFF_FORWARD	
	//// IO idx 15 : CHAFF_BACKWARD	
	//// IO idx 16 : CHAFF_DEPRESS	
	//AUTO_ACQUISITION_TYPE eAutoAcquisition = AUTO_ACQUISITION_CENTER;
	//
	//if (GetDigitalInputBit(IOInfo[14].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eAutoAcquisition = AUTO_ACQUISITION_FWD;
	//
	//if (GetDigitalInputBit(IOInfo[15].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eAutoAcquisition = AUTO_ACQUISITION_AFT;
	//
	//if (GetDigitalInputBit(IOInfo[16].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eAutoAcquisition = AUTO_ACQUISITION_DOWN;
	//
	//m_stCockpit2HOST.IO2HOST.Main_Panel.Auto_Acquisition_Switch = eAutoAcquisition;
	//
	//// IO idx  17 : TRIGGER_DEPRESS_1
	//// IO idx  20 : TRIGGER_DEPRESS_2
	//STICK_TRIGGER_TYPE eStickTrigger = TRIGGER_OFF;
	//if (GetDigitalInputBit(IOInfo[17].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eStickTrigger = TRIGGER_DVR;
	//
	//if (GetDigitalInputBit(IOInfo[20].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eStickTrigger = TRIGGER_FIRE;
	//
	//m_stCockpit2HOST.IO2HOST.Main_Panel.Stick_Trigger_Btn = eStickTrigger;
	//
	//// IO idx  18 : PINK_OPEN (KAI ICD Mapping 확인 필요함.)
	//// IO idx  19 : PINK_CLOSE
	//eOnOFF = OFF;
	//if (GetDigitalInputBit(IOInfo[18].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eOnOFF = ON;
	//
	//m_stCockpit2HOST.IO2HOST.Main_Panel.Nose_Gear_Steering_Btn = eOnOFF;
	//
	//ON_OFF_TYPE eTrimComplete = (ON_OFF_TYPE)sData.STICK_TRIM_COMPLETE;
	//
	//if (m_bStickInit && eTrimComplete == ON)
	//{
	//	m_bStickComplete = true;
	//	m_bStickInit = false;
	//}
	//else
	//{
	//	m_bStickComplete = false;
	//}
	//
	//m_stCockpit2HOST.IO2HOST.Main_Panel.Stick_Trim_Complete = eTrimComplete;

}

// GND PWR Panel Decode
void CIOSWDataManager::DecodeGNDPWRPanel(const IOBOARD_to_IOSW& sData, const IOBOARD_INFORMATION IOInfo[])
{
	///* IO idx  0 : GND_PWR_1SW_A_ON
	//   IO idx  1 : GND_PWR_1SW_AUTO
	//   IO idx  2 : GND_PWR_1SW_B_ON */
	//ON_OFF_AUTO_TYPE eOnOffAuto = AUTO_AUTO;
	//
	//if (GetDigitalInputBit(IOInfo[0].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eOnOffAuto = AUTO_ON;
	//
	//// AUTO is no signal, default value
	////if (GetDigitalInputBit(IOInfo[1].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	////	eOnOffAuto = AUTO_AUTO;
	//
	//if (GetDigitalInputBit(IOInfo[2].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eOnOffAuto = AUTO_OFF;
	//
	//m_stCockpit2HOST.IO2HOST.Left_Panel.Ground_Power_1_Switch = eOnOffAuto;
	//
	///* IO idx  3 : GND_PWR_2SW_ON
	//   IO idx  4 : GND_PWR_2SW_AUTO */
	//GROUND_PWR_TYPE eGroundPWR = GND_PWR_AUTO;
	//
	//if (GetDigitalInputBit(IOInfo[3].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eGroundPWR = GND_PWR_ON;
	//
	//if (GetDigitalInputBit(IOInfo[4].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eGroundPWR = GND_PWR_AUTO;
	//
	//m_stCockpit2HOST.IO2HOST.Left_Panel.Ground_Power_2_Switch = eGroundPWR;
	//
	///* IO idx  5 : GND_PWR_3SW_ON
	//   IO idx  6 : GND_PWR_3SW_AUTO */
	//eGroundPWR = GND_PWR_AUTO;
	//
	//if (GetDigitalInputBit(IOInfo[5].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eGroundPWR = GND_PWR_ON;
	//
	//if (GetDigitalInputBit(IOInfo[6].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eGroundPWR = GND_PWR_AUTO;
	//
	//m_stCockpit2HOST.IO2HOST.Left_Panel.Ground_Power_3_Switch = eGroundPWR;
	//
	///* IO idx  7 : GND_PWR_4SW_ON
	//   IO idx  8 : GND_PWR_4SW_AUTO */
	//eGroundPWR = GND_PWR_AUTO;
	//
	//if (GetDigitalInputBit(IOInfo[7].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eGroundPWR = GND_PWR_ON;
	//
	//if (GetDigitalInputBit(IOInfo[8].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eGroundPWR = GND_PWR_AUTO;
	//
	//m_stCockpit2HOST.IO2HOST.Left_Panel.Ground_Power_4_Switch = eGroundPWR;
	//
	///* IO idx  9 : GND_PWR_PACS_SW_ON
	//   IO idx 10 : GND_PWR_PACS_SW_AUTO
	//   IO idx 11 : GND_PWR_PACS_SW_OFF */
	//eOnOffAuto = AUTO_AUTO;
	//
	//if (GetDigitalInputBit(IOInfo[9].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eOnOffAuto = AUTO_ON;
	//
	//// AUTO is no signal, default value
	////if (GetDigitalInputBit(IOInfo[10].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	////	eOnOffAuto = AUTO_AUTO;
	//
	//if (GetDigitalInputBit(IOInfo[11].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eOnOffAuto = AUTO_OFF;
	//
	//m_stCockpit2HOST.IO2HOST.Left_Panel.Ground_Power_PACS_Switch = eOnOffAuto;
	//
	///* IO idx 12 : GND_PWR_ADCP/AIU_1SW_ON
	//   IO idx 13 : GND_PWR_ADCP/AIU_1SW_AUTO
	//   IO idx 14 : GND_PWR_ADCP/AIU_1SW_OFF	*/
	//eOnOffAuto = AUTO_AUTO;
	//
	//if (GetDigitalInputBit(IOInfo[12].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eOnOffAuto = AUTO_ON;
	//
	//// AUTO is no signal, default value
	////if (GetDigitalInputBit(IOInfo[13].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	////	eOnOffAuto = AUTO_AUTO;
	//
	//if (GetDigitalInputBit(IOInfo[14].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eOnOffAuto = AUTO_OFF;
	//
	//m_stCockpit2HOST.IO2HOST.Left_Panel.Ground_Power_ADCPAIU1_Switch = eOnOffAuto;
}

// ANTI-G_PANEL Decode
void CIOSWDataManager::DecodeAntiGPanel(const IOBOARD_to_IOSW& sData, const IOBOARD_INFORMATION IOInfo[])
{
	//// IO idx  0 : ANTI-G_SW_PUSH
	//ON_OFF_TYPE eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[0].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH);
	//m_stCockpit2HOST.IO2HOST.Left_Panel.Anti_G_Btn = eOnOFF;
}

// CANOPY_JETTISON_HANDLE Decode
void CIOSWDataManager::DecodeCanopyJettisonHandle(const IOBOARD_to_IOSW& sData, const IOBOARD_INFORMATION IOInfo[])
{
	//// IO idx  1 : CANOPY_EMERG_JETT_HANDLE_PIN
	//CANOPY_LOCK_TYPE eLock = CANOPY_LOCK;
	//
	//if (GetDigitalInputBit(IOInfo[1].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_LOW)
	//	eLock = CANOPY_UNLOCK;
	//
	//m_stCockpit2HOST.IO2HOST.Left_Panel.Canopy_Lock_Handle = eLock;
	//
	///*  IO idx  2 : CANOPY_EMERG_JETT_HANDLE_PUSH
	//	IO idx  3 : CANOPY_EMERG_JETT_HANDLE_PULL */
	//CANOPY_JETTISON_TYPE eCanopy = CANOPY_JETTISON_PUSH;
	//
	//// PUSH or PULL, defualt signal is PUSH
	////if (GetDigitalInputBit(IOInfo[2].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	////	eCanopy = CANOPY_JETTISON_PUSH;
	//
	//if (GetDigitalInputBit(IOInfo[3].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eCanopy = CANOPY_JETTISON_PULL;
	//
	//m_stCockpit2HOST.IO2HOST.Left_Panel.Canopy_Jettison_Btn = eCanopy;
}

// FLYUP_ENABLE_SWITCH Decode
void CIOSWDataManager::DecodeFlyupEnableSwitch(const IOBOARD_to_IOSW& sData, const IOBOARD_INFORMATION IOInfo[])
{
	///* IO idx  6 : FLYUP_ENABLE_SW_OFF
	//   IO idx  7 : FLYUP_ENABLE_SW_ON */
	//ON_OFF_TYPE eOnOFF = OFF;
	//
	//// OFF or ON, Default Signal is OFF
	////if (GetDigitalInputBit(IOInfo[6].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	////	eOnOFF = OFF;
	//
	//if (GetDigitalInputBit(IOInfo[7].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eOnOFF = ON;
	//
	//m_stCockpit2HOST.IO2HOST.Left_Panel.Flyup_Enable_Switch = eOnOFF;
}

// SEAT_ADJUST_SWITCH Decode
void CIOSWDataManager::DecodeSeatAdjustSwitch(const IOBOARD_to_IOSW& sData, const IOBOARD_INFORMATION IOInfo[])
{
	///* IO idx  8 : SEAT_ADJUST_SW_UP
	//   IO idx  9 : SEAT_ADJUST_SW_DOWN */
	//POSITION_TYPE eUpDown = POSITION_CTR;
	//
	//if (GetDigitalInputBit(IOInfo[8].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eUpDown = POSITION_FWD;
	//
	//if (GetDigitalInputBit(IOInfo[9].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eUpDown = POSITION_AFT;
	//
	//m_stCockpit2HOST.IO2HOST.Left_Panel.Seat_Adjust_Switch = eUpDown;
}

// IFF_ANTENNA_SELECT_SWITCH Decode
void CIOSWDataManager::DecodeIFFAntennaSelectSwitch(const IOBOARD_to_IOSW& sData, const IOBOARD_INFORMATION IOInfo[])
{
	///* IO idx 10 : IFF_ANT_SEL_SW_LOWER
	//   IO idx 11 : IFF_ANT_SEL_SW_UPPER   */
	//IFF_ANTENNA_TYPE eIFFAntenna = IFF_ANTENNA_BOTH;
	//
	//if (GetDigitalInputBit(IOInfo[10].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eIFFAntenna = IFF_ANTENNA_LOWER;
	//
	//// BOTH signal not used!!
	////if (GetDigitalInputBit(IOInfo[11].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	////	eIFFAntenna = IFF_ANTENNA_BOTH;
	//
	//if (GetDigitalInputBit(IOInfo[11].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eIFFAntenna = IFF_ANTENNA_UPPER;
	//
	//m_stCockpit2HOST.IO2HOST.Left_Panel.IFF_Antenna_Switch = eIFFAntenna;
}

// EMERGENCY_AIR_REFUELING_SWITCH Decode
void CIOSWDataManager::DecodeEmergencyAirRefuelingSwitch(const IOBOARD_to_IOSW& sData, const IOBOARD_INFORMATION IOInfo[])
{
	///* IO idx 13 : EMERG_A/R_SW_OPEN
	//   IO idx 14 : EMERG_A/R_SW_NORM */
	//OPEN_NORM_TYPE eOpenNorm = NORM;
	//
	//if (GetDigitalInputBit(IOInfo[13].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eOpenNorm = NORM_OEPN;
	//
	//// Defualt is NORM Switch
	////if (GetDigitalInputBit(IOInfo[14].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	////	eOpenNorm = NORM;
	//
	//m_stCockpit2HOST.IO2HOST.Left_Panel.Emerg_Air_Refuel_Switch = eOpenNorm;
}

// ARMAMENT_SAFETY_OVERRIDE_SWITCH Decode
void CIOSWDataManager::DecodeArmamentSafetyOverrideSwitch(const IOBOARD_to_IOSW& sData, const IOBOARD_INFORMATION IOInfo[])
{
	///* IO idx 16 : OVERRIDE_SW_SAFE
	//   IO idx 17 : OVERRIDE_SW_OVERRIDE */
	//SEAT_ARMAMENT_TYPE eSeatArmament = SEAT_ARMAMENT_SEAT;
	//
	//// Default is SAFE Swtich
	////if (GetDigitalInputBit(IOInfo[16].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	////	eSeatArmament = SEAT_ARMAMENT_SEAT;
	//
	//if (GetDigitalInputBit(IOInfo[17].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eSeatArmament = SEAT_ARMAMENT_OVERRIDE;
	//
	//m_stCockpit2HOST.IO2HOST.Left_Panel.Armament_Override_Switch = eSeatArmament;
}

// REMOTE_INTERCOMM_CONTROL_PANEL Decode
void CIOSWDataManager::DecodeRemoteIntercommControlPanel(const IOBOARD_to_IOSW& sData, const IOBOARD_INFORMATION IOInfo[])
{
	//// IO idx  0 : TEWS_VOL_CONTROL_CAUTION
	////m_stCockpit2HOST.IO2HOST.Left_Panel.Caution_Volume_Knob = (int) GetAnalogInputData(IOInfo[0], sData, m_stCockpit2HOST.IO2HOST.Left_Panel.Caution_Volume_Knob);
	//m_stCockpit2HOST.IO2HOST.Left_Panel.Caution_Volume_Knob = (int)GetAnalogInputData(IOInfo[0], m_stCockpit2HOST.IO2HOST.Left_Panel.Caution_Volume_Knob, sData);
	//
	//// IO idx  1 : TEWS_VOL_CONTROL_LAUNCH
	////m_stCockpit2HOST.IO2HOST.Left_Panel.Launch_Volume_Knob = (int) GetAnalogInputData(IOInfo[1], sData, m_stCockpit2HOST.IO2HOST.Left_Panel.Launch_Volume_Knob);
	//m_stCockpit2HOST.IO2HOST.Left_Panel.Launch_Volume_Knob = (int)GetAnalogInputData(IOInfo[1], m_stCockpit2HOST.IO2HOST.Left_Panel.Launch_Volume_Knob, sData);
	//
	//// IO idx  2 : ICS/WPN_VOL_CONTROL_ICS
	////m_stCockpit2HOST.IO2HOST.Left_Panel.ICS_Volume_Knob = (int) GetAnalogInputData(IOInfo[2], sData, m_stCockpit2HOST.IO2HOST.Left_Panel.ICS_Volume_Knob);
	//m_stCockpit2HOST.IO2HOST.Left_Panel.ICS_Volume_Knob = (int)GetAnalogInputData(IOInfo[2], m_stCockpit2HOST.IO2HOST.Left_Panel.ICS_Volume_Knob, sData);
	//
	//// IO idx  3 : ICS/WPN_VOL_CONTROL_WPN
	////m_stCockpit2HOST.IO2HOST.Left_Panel.WPN_Volume_Knob = (int) GetAnalogInputData(IOInfo[3], sData, m_stCockpit2HOST.IO2HOST.Left_Panel.WPN_Volume_Knob);
	//m_stCockpit2HOST.IO2HOST.Left_Panel.WPN_Volume_Knob = (int)GetAnalogInputData(IOInfo[3], m_stCockpit2HOST.IO2HOST.Left_Panel.WPN_Volume_Knob, sData);
	//
	//// IO idx  4 : ILS/TACAN_VOL_CONTROL_TACAN
	////m_stCockpit2HOST.IO2HOST.Left_Panel.TACAN_Volume_Knob = (int) GetAnalogInputData(IOInfo[4], sData, m_stCockpit2HOST.IO2HOST.Left_Panel.TACAN_Volume_Knob);
	//m_stCockpit2HOST.IO2HOST.Left_Panel.TACAN_Volume_Knob = (int)GetAnalogInputData(IOInfo[4], m_stCockpit2HOST.IO2HOST.Left_Panel.TACAN_Volume_Knob, sData);
	//
	//// IO idx  5 : ILS / TACAN_VOL_CONTROL_ILS
	////m_stCockpit2HOST.IO2HOST.Left_Panel.ILS_Volume_Knob = (int) GetAnalogInputData(IOInfo[5], sData, m_stCockpit2HOST.IO2HOST.Left_Panel.ILS_Volume_Knob);
	//m_stCockpit2HOST.IO2HOST.Left_Panel.ILS_Volume_Knob = (int)GetAnalogInputData(IOInfo[5], m_stCockpit2HOST.IO2HOST.Left_Panel.ILS_Volume_Knob, sData);
	//
	///* IO idx  6 : CRYPTO_SW_HOLD
	//   IO idx  7 : CRYPTO_SW_NORM
	//   IO idx  8 : CRYPTO_SW_ZERO */
	//CRYPTO_TYPE eCrypto = CRYPTO_NORM;
	//
	//if (GetDigitalInputBit(IOInfo[6].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eCrypto = CRYPTO_HOLD;
	//
	//// Norm signal is not used!!
	////if (GetDigitalInputBit(IOInfo[7].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	////	eCrypto = CRYPTO_NORM;
	//
	//if (GetDigitalInputBit(IOInfo[8].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eCrypto = CRYPTO_ZERO;
	//
	//m_stCockpit2HOST.IO2HOST.Left_Panel.Crypto_Switch = eCrypto;
	//
	///* IO idx  9 : MIC_SW_RAD_ORIDE
	//   IO idx 10 : MIC_SW_RAD_ON
	//   IO idx 11 : MIC_SW_RAD_OFF	 */
	//ON_OFF_ORIDE_TYPE eOnOFFOride = ORIDE_ON;
	//
	//if (GetDigitalInputBit(IOInfo[9].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eOnOFFOride = ORIDE;
	//
	//// RAD ON Signal is Not Used!! 
	////if (GetDigitalInputBit(IOInfo[10].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	////	eOnOFFOride = ORIDE_ON;
	//
	//if (GetDigitalInputBit(IOInfo[11].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eOnOFFOride = ORIDE_OFF;
	//
	//m_stCockpit2HOST.IO2HOST.Left_Panel.MIC_Switch = eOnOFFOride;
	//
	//// IO idx  12 : VW/TONE_SILENCE_SW_PUSH	
	//m_stCockpit2HOST.IO2HOST.Left_Panel.VM_Tone_Silence_Btn = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[12].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH);
	//
	///* IO idx 13 : RAD_1_ANT_SW_UPPER
	//   IO idx 14 : RAD_1_ANT_SW_AUTO
	//   IO idx 15 : RAD_1_ANT_SW_LOWER */
	//RAD1_ANT_TYPE eRAD1 = RAD1_ANT_AUTO;
	//
	//if (GetDigitalInputBit(IOInfo[13].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eRAD1 = RAD1_ANT_UPPER;
	//
	//// AUTO Signal is Not Used!!
	////if (GetDigitalInputBit(IOInfo[14].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	////	eRAD1 = RAD1_ANT_AUTO;
	//
	//if (GetDigitalInputBit(IOInfo[15].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eRAD1 = RAD1_ANT_LOWER;
	//
	//m_stCockpit2HOST.IO2HOST.Left_Panel.Rad1_Ant_Switch = eRAD1;
	//
	///* IO idx 16 : TONE_SW_RAD1
	//   IO idx 17 : TONE_SW_OFF
	//   IO idx 18 : TONE_SW_RAD2 */
	//TONE_TYPE eTone = TONE_OFF;
	//
	//if (GetDigitalInputBit(IOInfo[16].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eTone = TONE_RAD1;
	//
	//// OFF Singal is Not Used!!
	////if (GetDigitalInputBit(IOInfo[17].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	////	eTone = TONE_OFF;
	//
	//if (GetDigitalInputBit(IOInfo[18].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eTone = TONE_RAD2;
	//
	//m_stCockpit2HOST.IO2HOST.Left_Panel.Tone_Switch = eTone;
	//
	///* IO idx 19 : CIPHER_TEXT_SW_ONLY
	//   IO idx 20 : CIPHER_TEXT_SW_NORM */
	//CIPHER_TEXT_TYPE eCipher = CIPHER_TEXT_NORM;
	//
	//if (GetDigitalInputBit(IOInfo[19].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eCipher = CIPHER_TEXT_ONLY;
	//
	//// NORM Signal is Default!!
	////if (GetDigitalInputBit(IOInfo[20].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	////	eCipher = CIPHER_TEXT_NORM;
	//
	//m_stCockpit2HOST.IO2HOST.Left_Panel.Cipher_Text_Switch = eCipher;
	//
	///* IO idx 21 : IFF_MODE_SW_B
	//   IO idx 22 : IFF_MODE_SW_A
	//   IO idx 23 : IFF_MODE_SW_OUT	 */
	//IFF_MODE_TYPE eIFFMode = IFF_MODE_MODE_A;
	//
	//if (GetDigitalInputBit(IOInfo[21].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eIFFMode = IFF_MODE_MODE_B;
	//
	//// Mode A Signal is Not Used!!
	////if (GetDigitalInputBit(IOInfo[22].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	////	eIFFMode = IFF_MODE_MODE_A;
	//
	//if (GetDigitalInputBit(IOInfo[23].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eIFFMode = IFF_MODE_MODE_OUT;
	//
	//m_stCockpit2HOST.IO2HOST.Left_Panel.IFF_Mode_Switch = eIFFMode;
	//
	///* IO idx 24 : IFF_LIGHT_SW_LIGHT
	//   IO idx 25 : IFF_LIGHT_SW_AUDIO_REC
	//   IO idx 26 : IFF_LIGHT_SW_OFF			 */
	//IFF_LIGHT_TYPE eIFFLight = IFF_LIGHT_AUDIO_REC;
	//
	//if (GetDigitalInputBit(IOInfo[24].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eIFFLight = IFF_LIGHT_LIGHT;
	//
	//// Audio rec signal is not used!!
	////if (GetDigitalInputBit(IOInfo[25].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	////	eIFFLight = IFF_LIGHT_AUDIO_REC;
	//
	//if (GetDigitalInputBit(IOInfo[26].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eIFFLight = IFF_LIGHT_OFF;
	//
	//m_stCockpit2HOST.IO2HOST.Left_Panel.IFF_Light_Switch = eIFFLight;
	//
	///* IO idx 28 : IFF_MASTER_SW_LOW
	//   IO idx 29 : IFF_MASTER_SW_NORM
	//   IO idx 30 : IFF_MASTER_SW_EMER	 */
	//IFF_MASTER_TYPE eIFFMaster = IFF_MASTER_NORM;
	//
	//if (GetDigitalInputBit(IOInfo[28].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eIFFMaster = IFF_MASTER_LOW;
	//
	//// Norm signal is not used!!
	////if (GetDigitalInputBit(IOInfo[29].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	////	eIFFMaster = IFF_MASTER_NORM;
	//
	//if (GetDigitalInputBit(IOInfo[30].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eIFFMaster = IFF_MASTER_EMERG;
	//
	//m_stCockpit2HOST.IO2HOST.Left_Panel.IFF_Master_Switch = eIFFMaster;
}

// FUEL_CONTROL_PANEL Decode
void CIOSWDataManager::DecodeFuelControlPanel(const IOBOARD_to_IOSW& sData, const IOBOARD_INFORMATION IOInfo[])
{
	///* IO idx  0 : WING_SW_STOP_TRANS
	//   IO idx  1 : WING_SW_NORM
	//   IO idx  2 : WING_SW_STOP_REFUEL	 */
	//FUEL_CONTROL_TYPE eFuelCtrl = FUEL_CONTROL_NORM;
	//
	//if (GetDigitalInputBit(IOInfo[0].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eFuelCtrl = FUEL_CONTROL_STOP_TRANS;
	//
	//// NORM signal is not Used!!
	////if (GetDigitalInputBit(IOInfo[1].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	////	eFuelCtrl = FUEL_CONTROL_NORM;
	//
	//if (GetDigitalInputBit(IOInfo[2].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eFuelCtrl = FUEL_CONTROL_STOP_REFUEL;
	//
	//m_stCockpit2HOST.IO2HOST.Left_Panel.Wing_Fuel_Control_Switch = eFuelCtrl;
	//
	///* IO idx  3 : CTR_SW_STOP_TRANS
	//   IO idx  4 : CTR_SW_NORM
	//   IO idx  5 : CTR_SW_STOP_REFUEL	 */
	//eFuelCtrl = FUEL_CONTROL_NORM;
	//
	//if (GetDigitalInputBit(IOInfo[3].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eFuelCtrl = FUEL_CONTROL_STOP_TRANS;
	//
	//// NORM signal is not used!!
	////if (GetDigitalInputBit(IOInfo[4].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	////	eFuelCtrl = FUEL_CONTROL_NORM;
	//
	//if (GetDigitalInputBit(IOInfo[5].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eFuelCtrl = FUEL_CONTROL_STOP_REFUEL;
	//
	//m_stCockpit2HOST.IO2HOST.Left_Panel.CTR_Fuel_Control_Switch = eFuelCtrl;
	//
	///* IO idx  6 : CONF_TANK_SW_STOP_TRANS
	//   IO idx  7 : CONF_TANK_SW_STOP_REFUEL	 */
	//eFuelCtrl = FUEL_CONTROL_NORM;
	//
	//if (GetDigitalInputBit(IOInfo[6].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eFuelCtrl = FUEL_CONTROL_STOP_TRANS;
	//
	//// NORM signal is not used!!
	////if (GetDigitalInputBit(IOInfo[7].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	////	eFuelCtrl = FUEL_CONTROL_NORM;
	//
	//if (GetDigitalInputBit(IOInfo[7].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eFuelCtrl = FUEL_CONTROL_STOP_REFUEL;
	//
	//m_stCockpit2HOST.IO2HOST.Left_Panel.Conf_Tank_Fuel_Control_Switch = eFuelCtrl;
	//
	///* IO idx  8 : DUMP_SW_DUMP
	//   IO idx  9 : DUMP_SW_NORM  */
	//DUMP_TYPE eDump = DUMP_NORM;
	//
	//if (GetDigitalInputBit(IOInfo[8].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eDump = DUMP;
	//
	//// NORM signal is defualt
	////if (GetDigitalInputBit(IOInfo[19].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	////	eDump = DUMP_NORM;
	//
	//m_stCockpit2HOST.IO2HOST.Left_Panel.Dump_Switch = eDump;
	//
	///* IO idx 11 : CONF_TANK_EMERG_TRANS_SW_L
	//   IO idx 12 : CONF_TANK_EMERG_TRANS_SW_NORM
	//   IO idx 13 : CONF_TANK_EMERG_TRANS_SW_R			 */
	//LEFT_RIGHT_NORMAL_TYPE eLRN = CT_NORMAL;
	//
	//if (GetDigitalInputBit(IOInfo[11].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eLRN = CT_LEFT;
	//
	//// Norm signal is not used
	////if (GetDigitalInputBit(IOInfo[12].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	////	eLRN = CT_NORMAL;
	//
	//if (GetDigitalInputBit(IOInfo[13].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eLRN = CT_RIGHT;
	//
	//m_stCockpit2HOST.IO2HOST.Left_Panel.Conf_Tank_Emerg_Trans_Switch = eLRN;
	//
	///* IO idx 14 : EXT_TRANS_CONF_TANK_SW_CONF_TANK
	//   IO idx 15 : EXT_TRANS_CONF_TANK_SW_WING/CTR	  */
	//EXT_TRANS_TYPE eExtTrans = WING_CTR;
	//
	//if (GetDigitalInputBit(IOInfo[14].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eExtTrans = CONF_TANK;
	//
	//// WING CTR signal is defualt
	////if (GetDigitalInputBit(IOInfo[15].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	////	eExtTrans = WING_CTR;
	//
	//m_stCockpit2HOST.IO2HOST.Left_Panel.Ext_Trans_Switch = eExtTrans;
	//
	///* IO idx 16 : SLIPWAY_SW_ORIDE
	//   IO idx 17 : SLIPWAY_SW_OPEN
	//   IO idx 18 : SLIPWAY_SW_CLOSE		 */
	//OPEN_CLOSE_ORIDE_TYPE eOpenCloseOride = SWITCH_OEPN;
	//
	//if (GetDigitalInputBit(IOInfo[16].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eOpenCloseOride = SWITCH_ORIDE;
	//
	//// OPEN signal is not used!!
	////if (GetDigitalInputBit(IOInfo[17].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	////	eOpenCloseOride = SWITCH_OEPN;
	//
	//if (GetDigitalInputBit(IOInfo[18].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eOpenCloseOride = SWITCH_CLOSE;
	//
	//m_stCockpit2HOST.IO2HOST.Left_Panel.Slipway_Switch = eOpenCloseOride;

}

// MISCELLANEOUS_CONTROL_PANEL Decode
void CIOSWDataManager::DecodeMiscellaneousControlPanel(const IOBOARD_to_IOSW& sData, const IOBOARD_INFORMATION IOInfo[])
{
	///* IO idx  0 : ANTI_SKID_SW_NORM
	//   IO idx  1 : ANTI_SKID_SW_PULSER
	//   IO idx  2 : ANTI_SKID_SW_OFF			 */
	//ANTI_SKID_TYPE eAntiSkid = ANTISKID_PULSER;
	//
	//if (GetDigitalInputBit(IOInfo[0].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eAntiSkid = ANTISKID_NORM;
	//
	//// Pulser signal is not used!!
	////if (GetDigitalInputBit(IOInfo[1].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	////	eAntiSkid = ANTISKID_PULSER;
	//
	//if (GetDigitalInputBit(IOInfo[2].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eAntiSkid = ANTISKID_OFF;
	//
	//m_stCockpit2HOST.IO2HOST.Left_Panel.Anti_Skid_Switch = eAntiSkid;
	//
	///* IO idx  3 : ROLL_RATIO_SW_AUTO
	//   IO idx  4 : ROLL_RATIO_SW_EMER		 */
	//AUTO_EMERG_TYPE eAutoEmerg = EMERG;
	//
	//if (GetDigitalInputBit(IOInfo[3].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eAutoEmerg = EMERG_AUTO;
	//
	//// AUTO or EMER, EMER is defualt
	////if (GetDigitalInputBit(IOInfo[4].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	////	eAutoEmerg = EMERG;
	//
	//m_stCockpit2HOST.IO2HOST.Left_Panel.Roll_Ratio_Switch = eAutoEmerg;
	//
	///* IO idx  5 : L_INLET_RAMP_SW_AUTO
	//   IO idx  6 : L_INLET_RAMP_SW_EMER		 */
	//eAutoEmerg = EMERG;
	//
	//if (GetDigitalInputBit(IOInfo[5].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eAutoEmerg = EMERG_AUTO;
	//
	//// EMERG or ATUO, Default is EMERG
	////if (GetDigitalInputBit(IOInfo[6].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	////	eAutoEmerg = EMERG;
	//
	//m_stCockpit2HOST.IO2HOST.Left_Panel.Left_Inlet_Ramp_Switch = eAutoEmerg;
	//
	///* IO idx  7 : R_INLET_RAMP_SW_AUTO
	//   IO idx  8 : R_INLET_RAMP_SW_EMER		 */
	//eAutoEmerg = EMERG;
	//
	//if (GetDigitalInputBit(IOInfo[7].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eAutoEmerg = EMERG_AUTO;
	//
	//// EMERG or ATUO, Default is EMERG 
	////if (GetDigitalInputBit(IOInfo[8].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	////	eAutoEmerg = EMERG;
	//
	//m_stCockpit2HOST.IO2HOST.Left_Panel.Right_Inlet_Ramp_Switch = eAutoEmerg;
	//
	///* IO idx  9 : LDG/TAXI_LIGHT_SW_LDG_LIGHT
	//   IO idx 10 : LDG/TAXI_LIGHT_SW_OFF
	//   IO idx 11 : LDG/TAXI_LIGHT_SW_TAXI_LIGHT		 */
	//LDG_TAXI_LIGHT_TYPE eLdgTaxiLight = LDG_OFF;
	//
	//if (GetDigitalInputBit(IOInfo[9].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eLdgTaxiLight = LDG_LDG_LIGHT;
	//
	//// OFF Signal is not used!!
	////if (GetDigitalInputBit(IOInfo[10].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	////	eLdgTaxiLight = LDG_OFF;
	//
	//if (GetDigitalInputBit(IOInfo[11].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eLdgTaxiLight = LDG_TAXI_LIGHT;
	//
	//m_stCockpit2HOST.IO2HOST.Left_Panel.LDG_Taxi_Light_Switch = eLdgTaxiLight;
}

// CAS_CONTROL_PANEL Decode
void CIOSWDataManager::DecodeCASControlPanel(const IOBOARD_to_IOSW& sData, const IOBOARD_INFORMATION IOInfo[])
{
	///* IO idx  0 : YAW_ON
	//   IO idx  1 : YAW_RESET
	//   IO idx  2 : YAW_OFF		 */
	//
	//static int nYAWCount = 0;
	//static int nRollCount = 0;
	//static int nPitchCount = 0;
	//ON_OFF_RESET_TYPE eOnOffReset = m_stCockpit2HOST.IO2HOST.Left_Panel.Yaw_Switch;
	//
	//if (GetDigitalInputBit(IOInfo[0].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eOnOffReset = RESET_ON;
	//
	//if (GetDigitalInputBit(IOInfo[1].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eOnOffReset = RESET;
	//
	//if (GetDigitalInputBit(IOInfo[2].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eOnOffReset = RESET_OFF;
	//
	//if (eOnOffReset == RESET_ON)
	//{
	//	nYAWCount++;
	//
	//	if (nYAWCount >= 50)
	//	{
	//		m_stCockpit2HOST.IO2HOST.Left_Panel.Yaw_Switch = eOnOffReset;
	//	}
	//}
	//else
	//{
	//	nYAWCount = 0;
	//	m_stCockpit2HOST.IO2HOST.Left_Panel.Yaw_Switch = eOnOffReset;
	//}
	//
	///* 2019. 08. 19 test
	//
	//ON_OFF_RESET_TYPE eOnOffReset = RESET_OFF;
	//ON_OFF_RESET_TYPE eOldOnOffReset = m_stCockpit2HOST.IO2HOST.Left_Panel.Yaw_Switch;
	//
	//
	//if (GetDigitalInputBit(IOInfo[0].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eOnOffReset = RESET_ON;
	//
	//if (GetDigitalInputBit(IOInfo[1].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eOnOffReset = RESET;
	//
	//if (GetDigitalInputBit(IOInfo[2].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eOnOffReset = RESET_OFF;
	//
	//if(eOldOnOffReset == RESET_OFF && eOnOffReset == RESET_ON)
	//	eOnOffReset = RESET_OFF;
	//
	//if (eOnOffReset == RESET_ON)
	//{
	//	nYAWCount++;
	//
	//	if (nYAWCount >= 10)
	//	{
	//		m_stCockpit2HOST.IO2HOST.Left_Panel.Yaw_Switch = eOnOffReset;
	//	}
	//}
	//else
	//{
	//	nYAWCount = 0;
	//	m_stCockpit2HOST.IO2HOST.Left_Panel.Yaw_Switch = eOnOffReset;
	//}
	//
	//*/
	//
	///* IO idx  3 : ROLL_ON
	//   IO idx  4 : ROLL_RESET
	//   IO idx  5 : ROLL_OFF	 */
	//
	//eOnOffReset = m_stCockpit2HOST.IO2HOST.Left_Panel.Roll_Switch;
	//if (GetDigitalInputBit(IOInfo[3].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eOnOffReset = RESET_ON;
	//
	//if (GetDigitalInputBit(IOInfo[4].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eOnOffReset = RESET;
	//
	//// OFF signal is default
	//if (GetDigitalInputBit(IOInfo[5].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eOnOffReset = RESET_OFF;
	//
	//if (eOnOffReset == RESET_ON)
	//{
	//	nRollCount++;
	//
	//	if (nRollCount >= 50)
	//	{
	//		m_stCockpit2HOST.IO2HOST.Left_Panel.Roll_Switch = eOnOffReset;
	//	}
	//}
	//else
	//{
	//	nRollCount = 0;
	//	m_stCockpit2HOST.IO2HOST.Left_Panel.Roll_Switch = eOnOffReset;
	//}
	//
	///* 2019. 08. 19 test
	//eOnOffReset = RESET_OFF;
	//eOldOnOffReset = m_stCockpit2HOST.IO2HOST.Left_Panel.Roll_Switch;
	//
	//if (GetDigitalInputBit(IOInfo[3].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eOnOffReset = RESET_ON;
	//
	//if (GetDigitalInputBit(IOInfo[4].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eOnOffReset = RESET;
	//
	//// OFF signal is default
	//if (GetDigitalInputBit(IOInfo[5].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eOnOffReset = RESET_OFF;
	//
	//if (eOldOnOffReset == RESET_OFF && eOnOffReset == RESET_ON)
	//	eOnOffReset = RESET_OFF;
	//
	//if (eOnOffReset == RESET_ON)
	//{
	//	nRollCount++;
	//
	//	if (nRollCount >= 10)
	//	{
	//		m_stCockpit2HOST.IO2HOST.Left_Panel.Roll_Switch = eOnOffReset;
	//	}
	//}
	//else
	//{
	//	nRollCount = 0;
	//	m_stCockpit2HOST.IO2HOST.Left_Panel.Roll_Switch = eOnOffReset;
	//}
	//
	//*/
	///* IO idx  6 : PITCH_ON
	//   IO idx  7 : PITCH_RESET
	//   IO idx  8 : PITCH_OFF	*/
	//
	//eOnOffReset = m_stCockpit2HOST.IO2HOST.Left_Panel.Pitch_Switch;
	//
	//if (GetDigitalInputBit(IOInfo[6].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eOnOffReset = RESET_ON;
	//
	//if (GetDigitalInputBit(IOInfo[7].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eOnOffReset = RESET;
	//
	//if (GetDigitalInputBit(IOInfo[8].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eOnOffReset = RESET_OFF;
	//
	//if (eOnOffReset == RESET_ON)
	//{
	//	nPitchCount++;
	//
	//	if (nPitchCount >= 50)
	//	{
	//		m_stCockpit2HOST.IO2HOST.Left_Panel.Pitch_Switch = eOnOffReset;
	//	}
	//}
	//else
	//{
	//	nPitchCount = 0;
	//	m_stCockpit2HOST.IO2HOST.Left_Panel.Pitch_Switch = eOnOffReset;
	//}
	//
	///* 2019. 08. 19 test
	//eOnOffReset = RESET_OFF;
	//eOldOnOffReset = m_stCockpit2HOST.IO2HOST.Left_Panel.Pitch_Switch;
	//
	//if (GetDigitalInputBit(IOInfo[6].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eOnOffReset = RESET_ON;
	//
	//if (GetDigitalInputBit(IOInfo[7].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eOnOffReset = RESET;
	//
	//if (GetDigitalInputBit(IOInfo[8].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eOnOffReset = RESET_OFF;
	//
	//if (eOldOnOffReset == RESET_OFF && eOnOffReset == RESET_ON)
	//	eOnOffReset = RESET_OFF;
	//
	//// OFF signal is default
	//if (eOnOffReset == RESET_ON)
	//{
	//	nPitchCount++;
	//
	//	if (nPitchCount >= 10)
	//	{
	//		m_stCockpit2HOST.IO2HOST.Left_Panel.Pitch_Switch = eOnOffReset;
	//	}
	//}
	//else
	//{
	//	nPitchCount = 0;
	//	m_stCockpit2HOST.IO2HOST.Left_Panel.Pitch_Switch = eOnOffReset;
	//}
	//*/
	//
	//// IO idx  9 : BIT_PUSH
	//ON_OFF_TYPE eOnOFF = OFF;
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[9].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH);
	//m_stCockpit2HOST.IO2HOST.Left_Panel.CAS_Bit_Btn = eOnOFF;
	//
	///* IO idx 11 : TF_COUPLE_ON
	//   IO idx 12 : TF_COUPLE_OFF  */
	//TF_TYPE eTFType = TF_OFF;
	//
	//if (GetDigitalInputBit(IOInfo[11].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eTFType = TF_COUPLE;
	//
	//// OFF Signal is defualt
	////if (GetDigitalInputBit(IOInfo[12].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	////	eOnOFF = OFF;
	//
	//m_stCockpit2HOST.IO2HOST.Left_Panel.TF_Switch = eTFType;
	//
	//// IO idx  13 : T/O_TRIM_ON
	//eOnOFF = OFF;
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[13].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH);
	//m_stCockpit2HOST.IO2HOST.Left_Panel.TO_Trim_Btn = eOnOFF;
}

// EXTERIOR_LIGHTS_CONTROL_PANEL Decode
void CIOSWDataManager::DecodeExteriorLightsControlPanel(const IOBOARD_to_IOSW& sData, const IOBOARD_INFORMATION IOInfo[])
{
	///* IO idx  0 : FORMATION_ROTARY_OFF
	//   IO idx  1 : FORMATION_ROTARY_1
	//   IO idx  2 : FORMATION_ROTARY_2
	//   IO idx  3 : FORMATION_ROTARY_3
	//   IO idx  4 : FORMATION_ROTARY_4
	//   IO idx  5 : FORMATION_ROTARY_5
	//   IO idx  6 : FORMATION_ROTARY_BRT*/
	//EXTERIOR_LIGHT_TYPE  eExteriorLight = m_stCockpit2HOST.IO2HOST.Left_Panel.Formation_Mode_Switch;
	//
	//if (GetDigitalInputBit(IOInfo[0].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eExteriorLight = EXTERIOR_LIGHT_OFF;
	//
	//if (GetDigitalInputBit(IOInfo[1].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eExteriorLight = EXTERIOR_LIGHT_ONE;
	//
	//if (GetDigitalInputBit(IOInfo[2].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eExteriorLight = EXTERIOR_LIGHT_TWO;
	//
	//if (GetDigitalInputBit(IOInfo[3].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eExteriorLight = EXTERIOR_LIGHT_THREE;
	//
	//if (GetDigitalInputBit(IOInfo[4].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eExteriorLight = EXTERIOR_LIGHT_FOUR;
	//
	//if (GetDigitalInputBit(IOInfo[5].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eExteriorLight = EXTERIOR_LIGHT_FIVE;
	//
	//if (GetDigitalInputBit(IOInfo[6].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eExteriorLight = EXTERIOR_LIGHT_BRT;
	//
	//m_stCockpit2HOST.IO2HOST.Left_Panel.Formation_Mode_Switch = eExteriorLight;
	//
	///* IO idx  7 : POSITION_ROTARY_OFF
	//   IO idx  8 : POSITION_ROTARY_1
	//   IO idx  9 : POSITION_ROTARY_2
	//   IO idx 10 : POSITION_ROTARY_3
	//   IO idx 11 : POSITION_ROTARY_4
	//   IO idx 12 : POSITION_ROTARY_5
	//   IO idx 13 : POSITION_ROTARY_BRT
	//   IO idx 14 : POSITION_ROTARY_FLASH	   */
	//
	//eExteriorLight = m_stCockpit2HOST.IO2HOST.Left_Panel.Position_Mode_Switch;
	//
	//if (GetDigitalInputBit(IOInfo[7].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eExteriorLight = EXTERIOR_LIGHT_OFF;
	//
	//if (GetDigitalInputBit(IOInfo[8].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eExteriorLight = EXTERIOR_LIGHT_ONE;
	//
	//if (GetDigitalInputBit(IOInfo[9].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eExteriorLight = EXTERIOR_LIGHT_TWO;
	//
	//if (GetDigitalInputBit(IOInfo[10].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eExteriorLight = EXTERIOR_LIGHT_THREE;
	//
	//if (GetDigitalInputBit(IOInfo[11].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eExteriorLight = EXTERIOR_LIGHT_FOUR;
	//
	//if (GetDigitalInputBit(IOInfo[12].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eExteriorLight = EXTERIOR_LIGHT_FIVE;
	//
	//if (GetDigitalInputBit(IOInfo[13].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eExteriorLight = EXTERIOR_LIGHT_BRT;
	//
	//if (GetDigitalInputBit(IOInfo[14].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eExteriorLight = EXTERIOR_LIGHT_FLASH;
	//
	//m_stCockpit2HOST.IO2HOST.Left_Panel.Position_Mode_Switch = eExteriorLight;
	//
	///* IO idx 15 : FORMATION_SW_NORMAL
	//   IO idx 16 : FORMATION_SW_NVIS	  */
	//FORMATION_LIGHT_TYPE eFormationLight = FORMATION_LIGHT_NORMAL;
	//
	//// Normal signal is not used!!
	////if (GetDigitalInputBit(IOInfo[15].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	////	eFormationLight = FORMATION_LIGHT_NORMAL;
	//
	//if (GetDigitalInputBit(IOInfo[16].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eFormationLight = FORMATION_LIGHT_NVIS;
	//
	//m_stCockpit2HOST.IO2HOST.Left_Panel.Formation_Light_Switch = eFormationLight;
	//
	///* IO idx 17 : ANTI_COLLISION_SW_ON
	//   IO idx 18 : ANTI_COLLISION_SW_OFF  */
	//ON_OFF_TYPE eOnOFF = OFF;
	//
	//if (GetDigitalInputBit(IOInfo[17].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eOnOFF = ON;
	//
	//// OFF Signal is not used!!
	//if (GetDigitalInputBit(IOInfo[18].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eOnOFF = OFF;
	//
	//m_stCockpit2HOST.IO2HOST.Left_Panel.Anti_Collision_Switch = eOnOFF;
	//
	///* IO idx 19 : VERT_TAIL_FLOOD_SW_BRT
	//   IO idx 20 : VERT_TAIL_FLOOD_SW_DIM
	//   IO idx 21 : VERT_TAIL_FLOOD_SW_OFF  */
	//VERT_TAIL_FLOOD_LIGHT_TYPE eVertTailFloodLight = VERT_TAIL_FLOOD_LIGHT_DIM;
	//
	//if (GetDigitalInputBit(IOInfo[19].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eVertTailFloodLight = VERT_TAIL_FLOOD_LIGHT_BRT;
	//
	//// DIM Signal is not used!!
	////if (GetDigitalInputBit(IOInfo[20].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	////	eVertTailFloodLight = VERT_TAIL_FLOOD_LIGHT_DIM;
	//
	//if (GetDigitalInputBit(IOInfo[21].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eVertTailFloodLight = VERT_TAIL_FLOOD_LIGHT_OFF;
	//
	//m_stCockpit2HOST.IO2HOST.Left_Panel.Vert_Tail_Flood_Switch = eVertTailFloodLight;
}

// SENSOR_CONTROL_PANEL Decode
void CIOSWDataManager::DecodeSensorControlPanel(const IOBOARD_to_IOSW& sData, const IOBOARD_INFORMATION IOInfo[])
{
	///* IO idx  0 : TF_RDR_SW_ON
	//   IO idx  1 : TF_RDR_SW_STBY
	//   IO idx  2 : TF_RDR_SW_OFF	  */
	//ON_OFF_STBY_TYPE eOnOFFSTBY = STBY;
	//
	//if (GetDigitalInputBit(IOInfo[0].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eOnOFFSTBY = STBY_ON;
	//
	//// STBY signal is not used!!
	////if (GetDigitalInputBit(IOInfo[1].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	////	eOnOFFSTBY = STBY;
	//
	//if (GetDigitalInputBit(IOInfo[2].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eOnOFFSTBY = STBY_OFF;
	//
	//m_stCockpit2HOST.IO2HOST.Left_Panel.TF_Radar_Switch = eOnOFFSTBY;
	//
	///* IO idx  3 : RDR_ALT_SW_OVERRIDE
	//   IO idx  4 : RDR_ALT_SW_ON
	//   IO idx  5 : RDR_ALT_SW_OFF		  */
	//RDR_ALT_TYPE eRDRALT = RDRALT_ON;
	//
	//if (GetDigitalInputBit(IOInfo[3].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eRDRALT = RDRALT_OVERRIDE;
	//
	//// ON Signal is not used!!
	////if (GetDigitalInputBit(IOInfo[4].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	////	eRDRALT = RDRALT_ON;
	//
	//if (GetDigitalInputBit(IOInfo[5].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eRDRALT = RDRALT_OFF;
	//
	//m_stCockpit2HOST.IO2HOST.Left_Panel.Radar_Alt_Switch = eRDRALT;
	//
	///* IO idx  6 : RADAR_POWER_SW_OFF
	//   IO idx  7 : RADAR_POWER_SW_STBY
	//   IO idx  8 : RADAR_POWER_SW_ON
	//   IO idx  9 : RADAR_POWER_SW_EMERG */
	//RADAR_MODE_TYPE eRadarMode = m_stCockpit2HOST.IO2HOST.Left_Panel.Radar_Mode_Switch;
	//
	//// OFF Signal is default
	//if (GetDigitalInputBit(IOInfo[6].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eRadarMode = RADAR_MODE_OFF;
	//
	//if (GetDigitalInputBit(IOInfo[7].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eRadarMode = RADAR_MODE_STBY;
	//
	//if (GetDigitalInputBit(IOInfo[8].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eRadarMode = RADAR_MODE_ON;
	//
	//if (GetDigitalInputBit(IOInfo[9].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eRadarMode = RADAR_MODE_EMERG;
	//
	//m_stCockpit2HOST.IO2HOST.Left_Panel.Radar_Mode_Switch = eRadarMode;
	//
	///* IO idx 10 : FDL_MODE_OFF
	//   IO idx 11 : FDL_MODE_POLL
	//   IO idx 12 : FDL_MODE_NORM
	//   IO idx 13 : FDL_MODE_SIL
	//   IO idx 14 : FDL_MODE_HOLD */
	//FDL_TYPE eFDL = m_stCockpit2HOST.IO2HOST.Left_Panel.FDL_Switch;
	//
	//
	//if (GetDigitalInputBit(IOInfo[10].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eFDL = FDL_OFF;
	//
	//if (GetDigitalInputBit(IOInfo[11].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eFDL = FDL_POLL;
	//
	//if (GetDigitalInputBit(IOInfo[12].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eFDL = FDL_NORM;
	//
	//if (GetDigitalInputBit(IOInfo[13].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eFDL = FDL_SIL;
	//
	//if (GetDigitalInputBit(IOInfo[14].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eFDL = FDL_HOLD;
	//
	//m_stCockpit2HOST.IO2HOST.Left_Panel.FDL_Switch = eFDL;
	//
	//// IO idx 15 : NAV_FLIR_SW_GAIN
	////m_stCockpit2HOST.IO2HOST.Left_Panel.Nav_Flir_Gain = (int)GetAnalogInputData(IOInfo[15], sData, m_stCockpit2HOST.IO2HOST.Left_Panel.Nav_Flir_Gain);
	//m_stCockpit2HOST.IO2HOST.Left_Panel.Nav_Flir_Gain = (int)GetAnalogInputData(IOInfo[15], m_stCockpit2HOST.IO2HOST.Left_Panel.Nav_Flir_Gain, sData);
	//// IO idx 16 : NAV_FLIR_SW_LEVEL
	////m_stCockpit2HOST.IO2HOST.Left_Panel.Nav_Flir_Level = (int)GetAnalogInputData(IOInfo[16], sData, m_stCockpit2HOST.IO2HOST.Left_Panel.Nav_Flir_Level);
	//m_stCockpit2HOST.IO2HOST.Left_Panel.Nav_Flir_Level = (int)GetAnalogInputData(IOInfo[16], m_stCockpit2HOST.IO2HOST.Left_Panel.Nav_Flir_Level, sData);
	//
	///* IO idx 17 : NAV_FLIR_POWER_ON
	//   IO idx 18 : NAV_FLIR_POWER_STBY
	//   IO idx 19 : NAV_FLIR_POWER_OFF   */
	//eOnOFFSTBY = STBY;
	//
	//if (GetDigitalInputBit(IOInfo[17].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eOnOFFSTBY = STBY_ON;
	//
	//// STBY signal is not used!!
	////if (GetDigitalInputBit(IOInfo[18].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	////	eOnOFFSTBY = STBY;
	//
	//if (GetDigitalInputBit(IOInfo[19].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eOnOFFSTBY = STBY_OFF;
	//
	//m_stCockpit2HOST.IO2HOST.Left_Panel.Nav_Flir_Switch = eOnOFFSTBY;
	//
	///* IO idx 20 : EGI1_SW_ON
	//   IO idx 21 : EGI1_SW_OFF	 */
	//ON_OFF_TYPE eOnOFF = OFF;
	//
	//if (GetDigitalInputBit(IOInfo[20].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eOnOFF = ON;
	//
	//// OFF Signal is not used!!
	////if (GetDigitalInputBit(IOInfo[21].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	////	eOnOFF = OFF;
	//
	//m_stCockpit2HOST.IO2HOST.Left_Panel.EGI_1_Switch = eOnOFF;
	//
	///* IO idx 22 : EGI2_SW_ON
	//   IO idx 23 : EGI2_SW_OFF	 */
	//eOnOFF = OFF;
	//
	//if (GetDigitalInputBit(IOInfo[22].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eOnOFF = ON;
	//
	//// OFF Signal is not used!!
	////if (GetDigitalInputBit(IOInfo[23].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	////	eOnOFF = OFF;
	//
	//m_stCockpit2HOST.IO2HOST.Left_Panel.EGI_2_Switch = eOnOFF;
	//
	///* IO idx 24 : IRST_SW_ON
	//   IO idx 25 : IRST_SW_STBY
	//   IO idx 26 : IRST_SW_OFF	  */
	//eOnOFFSTBY = STBY;
	//
	//if (GetDigitalInputBit(IOInfo[24].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eOnOFFSTBY = STBY_ON;
	//
	//// STBY Signal is not used!!
	////if (GetDigitalInputBit(IOInfo[25].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	////	eOnOFFSTBY = STBY;
	//
	//if (GetDigitalInputBit(IOInfo[26].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eOnOFFSTBY = STBY_OFF;
	//
	//m_stCockpit2HOST.IO2HOST.Left_Panel.IRST_Switch = eOnOFFSTBY;
	//
	//// IO idx 27 : ADCP_RESET_SW_PUSH
	//eOnOFF = (ON_OFF_TYPE)(GetDigitalInputBit(IOInfo[27].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH));
	//m_stCockpit2HOST.IO2HOST.Left_Panel.ADCP_Reset_Btn = eOnOFF;
}

// EW_CONTROL_PANEL Decode
void CIOSWDataManager::DecodeEWControlPanel(const IOBOARD_to_IOSW& sData, const IOBOARD_INFORMATION IOInfo[])
{
	///* IO idx  0 : RWR_POWER_SW_ON
	//   IO idx  1 : RWR_POWER_SW_OFF	*/
	//ON_OFF_TYPE eOnOFF = OFF;
	//
	//if (GetDigitalInputBit(IOInfo[0].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eOnOFF = ON;
	//
	//// OFF is Default 
	////if (GetDigitalInputBit(IOInfo[1].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	////	eOnOFF = OFF;
	//
	//m_stCockpit2HOST.IO2HOST.Right_Panel.RWR_Power_Switch = eOnOFF;
	//
	///* IO idx  2 : RWR_COMBAT_SW_COMBAT
	//   IO idx  3 : RWR_COMBAT_SW_TRNG	 */
	//RWR_COMBAT_TYPE eRWRCombat = RWR_SWITCH_TRNG;
	//
	//if (GetDigitalInputBit(IOInfo[2].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eRWRCombat = RWR_SWITCH_COMBAT;
	//
	//// TRNG is Default
	////if (GetDigitalInputBit(IOInfo[3].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	////	eRWRCombat = RWR_SWITCH_TRNG;
	//
	//m_stCockpit2HOST.IO2HOST.Right_Panel.RWR_Combat_Switch = eRWRCombat;
	//
	///* IO idx  4 : ICS_POWER_SW_ON
	//   IO idx  5 : ICS_POWER_SW_OFF	*/
	//eOnOFF = OFF;
	//
	//if (GetDigitalInputBit(IOInfo[4].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eOnOFF = ON;
	//
	//// OFF Signal is Default
	////if (GetDigitalInputBit(IOInfo[5].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	////	eOnOFF = OFF;
	//
	//m_stCockpit2HOST.IO2HOST.Right_Panel.ICS_Power_Switch = eOnOFF;
	//
	///* IO idx  6 : ICS_STBY_SW_MAN
	//   IO idx  7 : ICS_STBY_SW_AUTO
	//   IO idx  8 : ICS_STBY_SW_STBY   */
	//ICS_SWITCH_TYPE eICSSW = ICS_SWITCH_AUTO;
	//
	//if (GetDigitalInputBit(IOInfo[6].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eICSSW = ICS_SWITCH_MAN;
	//
	//// Auto signal is not used!!
	////if (GetDigitalInputBit(IOInfo[7].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	////	eICSSW = ICS_SWITCH_AUTO;
	//
	//if (GetDigitalInputBit(IOInfo[8].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eICSSW = ICS_SWITCH_STBY;
	//
	//m_stCockpit2HOST.IO2HOST.Right_Panel.ICS_Stby_Switch = eICSSW;
	//
	///* IO idx  9 : ICMD_SW_BYPASS
	//   IO idx 10 : ICMD_SW_ON
	//   IO idx 11 : ICMD_SW_OFF		  */
	//CMD_BYPASS_TYPE eCMDBYPASS = CMD_BYPASS_ON;
	//
	//if (GetDigitalInputBit(IOInfo[9].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eCMDBYPASS = CMD_BYPASS_BYPASS;
	//
	//// ON Signal is not used!!
	////if (GetDigitalInputBit(IOInfo[10].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	////	eCMDBYPASS = CMD_BYPASS_ON;
	//
	//if (GetDigitalInputBit(IOInfo[11].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eCMDBYPASS = CMD_BYPASS_OFF;
	//
	//m_stCockpit2HOST.IO2HOST.Right_Panel.CMD_Switch = eCMDBYPASS;
	//
	///* IO idx 12 : FLARE_SW_JETT
	//   IO idx 13 : FLARE_SW_NORM 	  */
	//CMD_JETTISON_TYPE eCMDJet = CMD_SWITCH_NORM;
	//
	//if (GetDigitalInputBit(IOInfo[12].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eCMDJet = CMD_SWITCH_JETT;
	//
	//// NORM Signal is defualt
	////if (GetDigitalInputBit(IOInfo[13].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	////	eCMDJet = CMD_SWITCH_NORM;
	//
	//
	//m_stCockpit2HOST.IO2HOST.Right_Panel.CMD_Jettison_Switch = eCMDJet;

}

// ENGINE_CONTROL_PANEL Decode
void CIOSWDataManager::DecodeEngineControlPanel(const IOBOARD_to_IOSW& sData, const IOBOARD_INFORMATION IOInfo[])
{
	///* IO idx  0 : L-GEN_SW_ON
	//   IO idx  1 : L-GEN_SW_OFF	*/
	//ON_OFF_TYPE eOnOFF = OFF;
	//
	//if (GetDigitalInputBit(IOInfo[0].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eOnOFF = ON;
	//
	//// OFF is default
	////if (GetDigitalInputBit(IOInfo[1].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	////	eOnOFF = OFF;
	//
	//m_stCockpit2HOST.IO2HOST.Right_Panel.Left_Engine_Gen_Switch = eOnOFF;
	//
	///* IO idx  2 : R-GEN_SW_ON
	//   IO idx  3 : R-GEN_SW_OFF	*/
	//eOnOFF = OFF;
	//
	//if (GetDigitalInputBit(IOInfo[2].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eOnOFF = ON;
	//
	//// OFF is default
	////if (GetDigitalInputBit(IOInfo[3].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	////	eOnOFF = OFF;
	//
	//m_stCockpit2HOST.IO2HOST.Right_Panel.Right_Engine_Gen_Switch = eOnOFF;
	//
	///* IO idx  4 : EMERG_GEN_SW_AUTO
	//   IO idx  6 : EMERG_GEN_SW_ISOLATE	*/
	//ENGINE_EMERG_TYPE eEngineEmerg = ENGINE_EMERG_MAN;
	//
	//if (GetDigitalInputBit(IOInfo[4].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eEngineEmerg = ENGINE_EMERG_AUTO;
	//
	//
	//if (GetDigitalInputBit(IOInfo[6].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eEngineEmerg = ENGINE_EMERG_ISOLATE;
	//
	//m_stCockpit2HOST.IO2HOST.Right_Panel.Engine_EmergeGen_Switch = eEngineEmerg;
	//
	///* IO idx  7 : L_ENG_CONTR_SW_ON
	//   IO idx  8 : L_ENG_CONTR_SW_OFF	*/
	//eOnOFF = OFF;
	//
	//if (GetDigitalInputBit(IOInfo[7].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eOnOFF = ON;
	//
	//// Off is default
	////if (GetDigitalInputBit(IOInfo[8].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	////	eOnOFF = OFF;
	//
	//m_stCockpit2HOST.IO2HOST.Right_Panel.Left_Engine_Control_Switch = eOnOFF;
	//
	///* IO idx  9 : R_ENG_CONTR_SW_ON
	//   IO idx 10 : R_ENG_CONTR_SW_OFF		*/
	//eOnOFF = OFF;
	//
	//if (GetDigitalInputBit(IOInfo[9].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eOnOFF = ON;
	//
	//// Off is default
	////if (GetDigitalInputBit(IOInfo[10].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	////	eOnOFF = OFF;
	//
	//m_stCockpit2HOST.IO2HOST.Right_Panel.Right_Engine_Control_Switch = eOnOFF;
	//
	///* IO idx 11 : L_ENG_MASTER_SW_ON
	//   IO idx 12 : L_ENG_MASTER_SW_OFF		*/
	//eOnOFF = ON;
	//
	////if (GetDigitalInputBit(IOInfo[11].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	////	eOnOFF = ON;
	//
	//if (GetDigitalInputBit(IOInfo[12].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eOnOFF = OFF;
	//
	//m_stCockpit2HOST.IO2HOST.Right_Panel.Left_Engine_Master_Switch = eOnOFF;
	//
	///* IO idx 13 : EXT_PWR_SW_RESET
	//   IO idx 14 : EXT_PWR_SW_NORM
	//   IO idx 15 : EXT_PWR_SW_OFF		*/
	//ENGINE_EXTPWR_TYPE eEngineExtpwr = ENGINE_EXTPWR_NORM;
	//
	//if (GetDigitalInputBit(IOInfo[13].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eEngineExtpwr = ENGINE_EXTPWR_RESET;
	//
	//// Norm signal is not used!!
	////if (GetDigitalInputBit(IOInfo[14].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	////	eEngineExtpwr = ENGINE_EXTPWR_NORM;
	//
	//if (GetDigitalInputBit(IOInfo[15].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eEngineExtpwr = ENGINE_EXTPWR_OFF;
	//
	//m_stCockpit2HOST.IO2HOST.Right_Panel.Engine_ExtPwr_Switch = eEngineExtpwr;
	//
	///* IO idx 17 : STARTER_SW_ON
	//   IO idx 18 : STARTER_SW_OFF		*/
	//eOnOFF = OFF;
	//
	//if (GetDigitalInputBit(IOInfo[17].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eOnOFF = ON;
	//
	//// Off is default
	////if (GetDigitalInputBit(IOInfo[18].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	////	eOnOFF = OFF;
	//
	//m_stCockpit2HOST.IO2HOST.Right_Panel.Engine_Starter_Switch = eOnOFF;
	//
	///* IO idx 19 : R_ENG_MASTER_SW_ON
	//   IO idx 20 : R_ENG_MASTER_SW_OFF			*/
	//eOnOFF = ON;
	//
	////if (GetDigitalInputBit(IOInfo[19].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	////	eOnOFF = ON;
	//
	//// Off is default
	//if (GetDigitalInputBit(IOInfo[20].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eOnOFF = OFF;
	//
	//m_stCockpit2HOST.IO2HOST.Right_Panel.Right_Engine_Master_Switch = eOnOFF;
}

void CIOSWDataManager::DecodeOxygenRegulator(const IOBOARD_to_IOSW& sData, const IOBOARD_INFORMATION IOInfo[])
{
	///* IO idx  3 : EMERGENCY_LEVER_SW_EMER
	//   IO idx  4 : EMERGENCY_LEVER_SW_NORM
	//   IO idx  5 : EMERGENCY_LEVER_SW_TEST_MASK	 */
	//OXYGEN_EMERG_TYPE eOxygenEmerg = OXYGEN_EMERG_NORM;
	//
	//if (GetDigitalInputBit(IOInfo[3].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eOxygenEmerg = OXYGEN_EMERG_EMERG;
	//
	//// NORM signal is not used!!
	////if (GetDigitalInputBit(IOInfo[4].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	////	eOxygenEmerg = OXYGEN_EMERG_NORM;
	//
	//if (GetDigitalInputBit(IOInfo[5].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eOxygenEmerg = OXYGEN_EMERG_TEST_MASK;
	//
	//m_stCockpit2HOST.IO2HOST.Right_Panel.Oxygen_Emerg_Switch = eOxygenEmerg;
	//
	///* IO idx  6 : OXYGEN_100%
	//   IO idx  7 : OXYGEN_NORM				*/
	//OXYGEN_TYPE eOxygen = OXY_NORM;
	//
	//if (GetDigitalInputBit(IOInfo[6].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eOxygen = OXY_MAX;
	//
	//// NORM is Default
	////if (GetDigitalInputBit(IOInfo[7].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	////	eOxygen = OXY_NORM;
	//
	//m_stCockpit2HOST.IO2HOST.Right_Panel.Oxygen_Switch = eOxygen;
	//
	///* IO idx  8 : SUPLY_SW_PBG
	//   IO idx  9 : SUPLY_SW_ON
	//   IO idx 10 : SUPLY_SW_OFF	 */
	//OXYGEN_SUPPLY_TYPE eOxygenSupply = OXYGEN_SUPPLY_ON;
	//
	//if (GetDigitalInputBit(IOInfo[8].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eOxygenSupply = OXYGEN_SUPPLY_PBG;
	//
	//// ON signal is Not used!!
	////if (GetDigitalInputBit(IOInfo[9].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	////	eOxygenSupply = OXYGEN_SUPPLY_ON;
	//
	//if (GetDigitalInputBit(IOInfo[10].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eOxygenSupply = OXYGEN_SUPPLY_OFF;
	//
	//m_stCockpit2HOST.IO2HOST.Right_Panel.Oxygen_Supply_Switch = eOxygenSupply;

}

// ECS_PANEL Decode
void CIOSWDataManager::DecodeECSPanel(const IOBOARD_to_IOSW& sData, const IOBOARD_INFORMATION IOInfo[])
{
	//// IO idx  0 : OXY_BIT/BOS_SW_PRESS
	//ON_OFF_TYPE eOnOFF = OFF;
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[0].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH);
	//
	//m_stCockpit2HOST.IO2HOST.Right_Panel.Oxy_Bit_Btn = eOnOFF;
	//
	///* IO idx  2 : ANTI-FOG_SW_HOT
	//   IO idx  4 : ANTI-FOG_SW_COLD	 */
	//ANTI_FOG_TYPE eANTIFog = ANTI_FOG_NORM;
	//
	//if (GetDigitalInputBit(IOInfo[2].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eANTIFog = ANTI_FOG_HOT;
	//
	//
	//if (GetDigitalInputBit(IOInfo[4].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eANTIFog = ANTI_FOG_COLD;
	//
	//m_stCockpit2HOST.IO2HOST.Right_Panel.Anti_Fog_Switch = eANTIFog;
	//
	///* IO idx  5 : ANTI-ICE_WINDSHIELD_SW_ON
	//   IO idx  6 : ANTI-ICE_WINDSHIELD_SW_OFF	*/
	//eOnOFF = OFF;
	//
	//if (GetDigitalInputBit(IOInfo[5].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eOnOFF = ON;
	//
	//// OFF signal is default
	////if (GetDigitalInputBit(IOInfo[6].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	////	eOnOFF = OFF;
	//
	//m_stCockpit2HOST.IO2HOST.Right_Panel.Anti_Ice_Windshield_Switch = eOnOFF;
	//
	///* IO idx  7 : ANTI-ICE_PITOT_HEAT_SW_ON
	//   IO idx  8 : ANTI-ICE_PITOT_HEAT_SW_OFF	*/
	//eOnOFF = OFF;
	//
	//if (GetDigitalInputBit(IOInfo[7].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eOnOFF = ON;
	//
	//// OFF Signal is Not used!!
	////if (GetDigitalInputBit(IOInfo[8].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	////	eOnOFF = OFF;
	//
	//m_stCockpit2HOST.IO2HOST.Right_Panel.Anti_Ice_PitotHeat_Switch = eOnOFF;
	//
	///* IO idx  9 : ANTI-ICE_ENG_HEAT_SW_ON
	//   IO idx 10 : ANTI-ICE_ENG_HEAT_SW_OFF
	//   IO idx 11 : ANTI-ICE_ENG_HEAT_SW_TEST  */
	//ON_OFF_TEST_TYPE eOnOFFTest = TEST_OFF;
	//
	//if (GetDigitalInputBit(IOInfo[9].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eOnOFFTest = TEST_ON;
	//
	//// OFF Signal is not used!!
	////if (GetDigitalInputBit(IOInfo[10].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	////	eOnOFFTest = TEST_OFF;
	//
	//if (GetDigitalInputBit(IOInfo[11].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eOnOFFTest = TEST_TEST;
	//
	//m_stCockpit2HOST.IO2HOST.Right_Panel.Anti_Ice_EngHeat_Switch = eOnOFFTest;
}

// AIR_CONDITION_CONTROL_PANEL Decode
void CIOSWDataManager::DecodeAirConditionControlPanel(const IOBOARD_to_IOSW& sData, const IOBOARD_INFORMATION IOInfo[])
{
	///* IO idx  0 : TEMP_SW_AUTO
	//   IO idx  1 : TEMP_SW_MAN
	//   IO idx  2 : TEMP_SW_OFF */
	//AIRCOND_TEMP_TYPE eAircondTemp = AIRCOND_TEMP_MAN;
	//
	//if (GetDigitalInputBit(IOInfo[0].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eAircondTemp = AIRCOND_TEMP_AUTO;
	//
	//// MAN signal is not used!!
	////if (GetDigitalInputBit(IOInfo[1].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	////	eAircondTemp = AIRCOND_TEMP_MAN;
	//
	//if (GetDigitalInputBit(IOInfo[2].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eAircondTemp = AIRCOND_TEMP_OFF;
	//
	//m_stCockpit2HOST.IO2HOST.Right_Panel.Aircond_Temp_Switch = eAircondTemp;
	//
	///* IO idx  3 : FLOW_SW_MAX
	//   IO idx  4 : FLOW_SW_NORM
	//   IO idx  5 : FLOW_SW_MIN	*/
	//AIRCOND_FLOW_TYPE eAircondFlow = AIRCOND_FLOW_NORM;
	//
	//if (GetDigitalInputBit(IOInfo[3].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eAircondFlow = AIRCOND_FLOW_MAX;
	//
	//// Norm signal is not used!!
	////if (GetDigitalInputBit(IOInfo[4].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	////	eAircondFlow = AIRCOND_FLOW_NORM;
	//
	//if (GetDigitalInputBit(IOInfo[5].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eAircondFlow = AIRCOND_FLOW_MIN;
	//
	//m_stCockpit2HOST.IO2HOST.Right_Panel.Aircond_Flow_Switch = eAircondFlow;
	//
	//// IO idix 6 : TEMP_CONTROL
	////m_stCockpit2HOST.IO2HOST.Right_Panel.Temp_Control_Knob = (int) GetAnalogInputData(IOInfo[6], sData, m_stCockpit2HOST.IO2HOST.Right_Panel.Temp_Control_Knob);
	//m_stCockpit2HOST.IO2HOST.Right_Panel.Temp_Control_Knob = (int)GetAnalogInputData(IOInfo[6], m_stCockpit2HOST.IO2HOST.Right_Panel.Temp_Control_Knob, sData);
	//
	///* IO idx  7 : AIR_SOURCE_OFF
	//   IO idx  8 : AIR_SOURCE_L_ENG
	//   IO idx  9 : AIR_SOURCE_BOTH
	//   IO idx 10 : AIR_SOURCE_R_ENG*/
	//AIR_SOURCE_TYPE eAirSource = m_stCockpit2HOST.IO2HOST.Right_Panel.Air_Source_Switch;
	//
	//if (GetDigitalInputBit(IOInfo[7].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eAirSource = FLOW_SWITCH_OFF;
	//
	//if (GetDigitalInputBit(IOInfo[8].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eAirSource = FLOW_SWITCH_L_ENG;
	//
	//if (GetDigitalInputBit(IOInfo[9].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eAirSource = FLOW_SWITCH_BOTH;
	//
	//if (GetDigitalInputBit(IOInfo[10].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eAirSource = FLOW_SWITCH_R_ENG;
	//
	//m_stCockpit2HOST.IO2HOST.Right_Panel.Air_Source_Switch = eAirSource;

}

// INTERIOR_LIGHTS_CONTROL_PANEL Decode
void CIOSWDataManager::DecodeInteriorLightsControlPanel(const IOBOARD_to_IOSW& sData, const IOBOARD_INFORMATION IOInfo[])
{
	//unsigned short nConsoleKnob = 0;
	//unsigned short nInstPnlKnob = 0;
	//unsigned short nUFCKnob = 0;
	//unsigned short nChartLTKnob = 0;
	//unsigned short nWarningKnob = 0;
	//unsigned short nStormKnob = 0;
	//ON_OFF_TYPE eOnOff = OFF;
	//
	//// IO idx  0 : CONSOLE_KNOB
	////nConsoleKnob = GetAnalogInputData(IOInfo[0], sData, m_stCockpit2HOST.IO2HOST.Right_Panel.Console_Light_Knob);
	////nConsoleKnob = GetAnalogInputData(IOInfo[0], m_stCockpit2HOST.IO2HOST.Right_Panel.Console_Light_Knob, sData);
	//nConsoleKnob = GetAnalogInputData(IOInfo[0], m_stCockpit2HOST.IO2HOST.Right_Panel.Console_Light_Knob, sData, 0.0, 1.0, 1.8, 2.8, 4.0, 5.0, 0.0, 200.0, 400.0, 600.0, 800.0, 1000.0);
	//m_stCockpit2HOST.IO2HOST.Right_Panel.Console_Light_Knob = nConsoleKnob;
	//
	//// IO idx  1 : INST_PNL_KNOB
	////nInstPnlKnob = GetAnalogInputData(IOInfo[1], sData, m_stCockpit2HOST.IO2HOST.Right_Panel.Inst_Pnl_Light_Knob);
	//nInstPnlKnob = GetAnalogInputData(IOInfo[1], m_stCockpit2HOST.IO2HOST.Right_Panel.Inst_Pnl_Light_Knob, sData, 0.0, 1.0, 1.8, 2.8, 4.0, 5.0, 0.0, 200.0, 400.0, 600.0, 800.0, 1000.0);
	//m_stCockpit2HOST.IO2HOST.Right_Panel.Inst_Pnl_Light_Knob = nInstPnlKnob;
	//
	//// IO idx  2 : INST_PNL_OFF
	//eOnOff = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[2].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH);
	//m_stCockpit2HOST.IO2HOST.Right_Panel.Inst_Pnl_Light_Off_Switch = eOnOff;
	//
	//// IO idx  3 : LT_TEST_SW_ON
	//// IO idx  4 : LT_TEST_SW_OFF
	//eOnOff = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[3].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH);
	//m_stCockpit2HOST.IO2HOST.Right_Panel.Light_Test_Switch = eOnOff;
	//
	//// IO idx  5 : UFC_KNOB
	////nUFCKnob = GetAnalogInputData(IOInfo[5], sData, m_stCockpit2HOST.IO2HOST.Right_Panel.UFC_Light_Knob);
	//nUFCKnob = GetAnalogInputData(IOInfo[5], m_stCockpit2HOST.IO2HOST.Right_Panel.UFC_Light_Knob, sData, 0.0, 1.0, 1.8, 2.8, 4.0, 5.0, 0.0, 200.0, 400.0, 600.0, 800.0, 1000.0);
	//m_stCockpit2HOST.IO2HOST.Right_Panel.UFC_Light_Knob = nUFCKnob;
	//
	//// IO idx  6 : STBY_COMP_SW_ON	
	//// IO idx  7 : STBY_COMP_SW_OFF
	//eOnOff = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[6].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH);
	//m_stCockpit2HOST.IO2HOST.Right_Panel.Stby_Comp_Switch = eOnOff;
	//
	//// IO idx  8 : CHART_LT_KNOB
	////nChartLTKnob = GetAnalogInputData(IOInfo[8], sData, m_stCockpit2HOST.IO2HOST.Right_Panel.Chart_Light_Knob);
	//nChartLTKnob = GetAnalogInputData(IOInfo[8], m_stCockpit2HOST.IO2HOST.Right_Panel.Chart_Light_Knob, sData, 0.0, 1.0, 1.7, 2.3, 3.6, 5.0, 0.0, 200.0, 400.0, 600.0, 800.0, 1000.0);
	//m_stCockpit2HOST.IO2HOST.Right_Panel.Chart_Light_Knob = nChartLTKnob;
	//
	//// IO idx  9 : DISPLAY_SW_NIGHT
	//// IO idx 10 : DISPLAY_SW_DAY	
	//DAY_NIGHT_TYPE eDayNight = DN_NIGHT;
	//
	//if (GetDigitalInputBit(IOInfo[9].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eDayNight = DN_DAY;
	//
	////if (GetDigitalInputBit(IOInfo[10].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	////	eDayNight = DN_NIGHT;
	//
	//m_stCockpit2HOST.IO2HOST.Right_Panel.Dislplay_Switch = eDayNight;
	//
	//// IO idx 11 : WARNING_CAUTION_KNOB
	////nWarningKnob = GetAnalogInputData(IOInfo[11], sData, m_stCockpit2HOST.IO2HOST.Right_Panel.Caution_Light_Knob);
	//nWarningKnob = GetAnalogInputData(IOInfo[11], m_stCockpit2HOST.IO2HOST.Right_Panel.Caution_Light_Knob, sData, 0.0, 1.0, 1.8, 2.8, 4.0, 5.0, 0.0, 200.0, 400.0, 600.0, 800.0, 1000.0);
	//m_stCockpit2HOST.IO2HOST.Right_Panel.Caution_Light_Knob = nWarningKnob;
	//
	//// IO idx 12 : WARNING_CAUTION_KNOB_RESET
	//eOnOff = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[12].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH);
	//m_stCockpit2HOST.IO2HOST.Right_Panel.Caution_Light_Reset = eOnOff;
	//
	//// IO idx 13 : STORM_FLOOD_KNOB
	////nStormKnob = GetAnalogInputData(IOInfo[13], sData, m_stCockpit2HOST.IO2HOST.Right_Panel.Storm_Flood_Light_Knob);
	//nStormKnob = GetAnalogInputData(IOInfo[13], m_stCockpit2HOST.IO2HOST.Right_Panel.Storm_Flood_Light_Knob, sData, 0.0, 0.3, 0.9, 2.2, 2.8, 4.7, 0.0, 200.0, 400.0, 600.0, 800.0, 1000.0);
	//m_stCockpit2HOST.IO2HOST.Right_Panel.Storm_Flood_Light_Knob = nStormKnob;
	//
	//// IO idx 14 : STORM_FLOOD_BRT
	//eOnOff = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[14].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH);
	//m_stCockpit2HOST.IO2HOST.Right_Panel.Storm_Flood_BRT_Switch = eOnOff;

}

// HMD_CONTROL_PANEL Decode
void CIOSWDataManager::DecodeHMDControlPanel(const IOBOARD_to_IOSW& sData, const IOBOARD_INFORMATION IOInfo[])
{
	//// IO idx  0 : HMD_CONTROL
	////int nHMDKnob = GetAnalogInputData(IOInfo[0], sData, m_stCockpit2HOST.IO2HOST.Right_Panel.HMD_Control_Knob);
	//int nHMDKnob = GetAnalogInputData(IOInfo[0], m_stCockpit2HOST.IO2HOST.Right_Panel.HMD_Control_Knob, sData, 0.0, 0.7, 1.5, 2.2, 3.6, 5.0, 0.0, 200.0, 400.0, 600.0, 800.0, 1000.0);
	//m_stCockpit2HOST.IO2HOST.Right_Panel.HMD_Control_Knob = nHMDKnob;
	//
	//// IO idx  1 : HMD_OFF
	//ON_OFF_TYPE eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[1].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH);
	//
	//if (eOnOFF == ON) {
	//	m_stCockpit2HOST.IO2HOST.Right_Panel.HMD_Power = OFF;
	//}
	//else
	//{
	//	m_stCockpit2HOST.IO2HOST.Right_Panel.HMD_Power = ON;
	//}

}

// CANOPY_CONTROL_HANDLE Decode
void CIOSWDataManager::DecodeCanopyControlHandle(const IOBOARD_to_IOSW& sData, const IOBOARD_INFORMATION IOInfo[])
{
	///* IO idx  3 : CANOPY_CONTROL_UP
	//   IO idx  4 : CANOPY_CONTROL_HOLD
	//   IO idx  5 : CANOPY_CONTROL_DOWN
	//   IO idx  6 : CANOPY_CONTROL_LOCKED		*/
	//CANOPY_CONTROL_TYPE eCanopyControl = m_stCockpit2HOST.IO2HOST.Right_Panel.Canopy_Control_Switch;
	//
	//if (GetDigitalInputBit(IOInfo[3].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eCanopyControl = CANOPY_CTR_UP;
	//
	//if (GetDigitalInputBit(IOInfo[4].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eCanopyControl = CANOPY_CTR_HOLD;
	//
	//if (GetDigitalInputBit(IOInfo[5].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eCanopyControl = CANOPY_CTR_DOWN;
	//
	//if (GetDigitalInputBit(IOInfo[6].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eCanopyControl = CANOPY_CTR_LOCKED;
	//
	//m_stCockpit2HOST.IO2HOST.Right_Panel.Canopy_Control_Switch = eCanopyControl;
}

// EJECTION_SEAT Decode
void CIOSWDataManager::DecodeEjectionSeat(const IOBOARD_to_IOSW& sData, const IOBOARD_INFORMATION IOInfo[])
{
	//// IO idx  9 : LEFT_HANDLE
	//UP_DOWN_TYPE eUpDown = UP_DOWN__DOWN;
	//
	//if (GetDigitalInputBit(IOInfo[9].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eUpDown = UP_DOWN__UP;
	//
	//m_stCockpit2HOST.IO2HOST.Main_Panel.Left_Ejection_Handle = eUpDown;
	//
	//// IO idx 10 : RIGHT_HANDLE
	//eUpDown = UP_DOWN__DOWN;
	//
	//if (GetDigitalInputBit(IOInfo[10].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eUpDown = UP_DOWN__UP;
	//
	//m_stCockpit2HOST.IO2HOST.Main_Panel.Right_Ejection_Handle = eUpDown;
}

// UFC Decode
void CIOSWDataManager::DecodeUFC(const IOBOARD_to_IOSW& sData, const IOBOARD_INFORMATION IOInfo[])
{
	//// IO idx  0 : R1
	////int nR1Knob = GetAnalogInputData(IOInfo[0], sData, m_stCockpit2HOST.IO2HOST.Main_Panel.UFC_Panel.Vol_R1_Knob);
	//int nR1Knob = GetAnalogInputData(IOInfo[0], m_stCockpit2HOST.IO2HOST.Main_Panel.UFC_Panel.Vol_R1_Knob, sData);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.UFC_Panel.Vol_R1_Knob = nR1Knob;
	//
	//// IO idx  1 : R3
	////int nR3Knob = GetAnalogInputData(IOInfo[1], sData, m_stCockpit2HOST.IO2HOST.Main_Panel.UFC_Panel.Vol_R3_Knob);
	//int nR3Knob = GetAnalogInputData(IOInfo[1], m_stCockpit2HOST.IO2HOST.Main_Panel.UFC_Panel.Vol_R3_Knob, sData);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.UFC_Panel.Vol_R3_Knob = nR3Knob;
	//
	//// IO idx  2 : R2
	////int nR2Knob = GetAnalogInputData(IOInfo[2], sData, m_stCockpit2HOST.IO2HOST.Main_Panel.UFC_Panel.Vol_R2_Knob);
	//int nR2Knob = GetAnalogInputData(IOInfo[2], m_stCockpit2HOST.IO2HOST.Main_Panel.UFC_Panel.Vol_R2_Knob, sData);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.UFC_Panel.Vol_R2_Knob = nR2Knob;
	//
	//// IO idx  3 : R4
	////int nR4Knob = GetAnalogInputData(IOInfo[3], sData, m_stCockpit2HOST.IO2HOST.Main_Panel.UFC_Panel.Vol_R4_Knob);
	//int nR4Knob = GetAnalogInputData(IOInfo[3], m_stCockpit2HOST.IO2HOST.Main_Panel.UFC_Panel.Vol_R4_Knob, sData);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.UFC_Panel.Vol_R4_Knob = nR4Knob;
	//
	//// IO idx  4 : BRT
	////int nBRTKnob = GetAnalogInputData(IOInfo[4], sData, m_stCockpit2HOST.IO2HOST.Main_Panel.UFC_Panel.Brt_Knob);
	//int nBRTKnob = GetAnalogInputData(IOInfo[4], m_stCockpit2HOST.IO2HOST.Main_Panel.UFC_Panel.Brt_Knob, sData);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.UFC_Panel.Brt_Knob = nBRTKnob;
	//
	//// IO idx  5 : ROTARY_LEFT
	//static int nLeftOldKnob = 0;
	//LEFT_RIGHT_NORMAL_TYPE nLeftValue = CT_NORMAL;
	//
	//if (nLeftOldKnob != 0)
	//{
	//	if (nLeftOldKnob < sData.SPARE1)
	//		nLeftValue = CT_RIGHT;
	//	else if (nLeftOldKnob > sData.SPARE1)
	//		nLeftValue = CT_LEFT;
	//	else
	//		nLeftValue = CT_NORMAL;
	//}
	//m_stCockpit2HOST.IO2HOST.Main_Panel.UFC_Panel.Left_Channel_Select_Knob = nLeftValue;
	//nLeftOldKnob = sData.SPARE1;
	//
	////int nLeftKnob = GetAnalogInputData(IOInfo[5], sData, m_stCockpit2HOST.IO2HOST.Main_Panel.UFC_Panel.Left_Channel_Select_Knob);
	////m_stCockpit2HOST.IO2HOST.Main_Panel.UFC_Panel.Left_Channel_Select_Knob = nLeftKnob;
	//
	//// IO idx  6 : ROTARY_RIGHT
	//static int nRightOldKnob = 0;
	//LEFT_RIGHT_NORMAL_TYPE nRightValue = CT_NORMAL;
	//
	//if (nRightOldKnob != 0)
	//{
	//	if (nRightOldKnob < sData.SPARE2)
	//		nRightValue = CT_RIGHT;
	//	else if (nRightOldKnob > sData.SPARE2)
	//		nRightValue = CT_LEFT;
	//	else
	//		nRightValue = CT_NORMAL;
	//}
	//m_stCockpit2HOST.IO2HOST.Main_Panel.UFC_Panel.Right_Channel_Select_Knob = nRightValue;
	//nRightOldKnob = sData.SPARE2;
	////int nRightKnob = GetAnalogInputData(IOInfo[6], sData, m_stCockpit2HOST.IO2HOST.Main_Panel.UFC_Panel.Right_Channel_Select_Knob);
	////m_stCockpit2HOST.IO2HOST.Main_Panel.UFC_Panel.Right_Channel_Select_Knob = nRightKnob;
	//
	//// IO idx  7 :  LH_SW1
	//ON_OFF_TYPE eOnOFF = OFF;
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[7].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.UFC_Panel.S1 = eOnOFF;
	//
	//// IO idx  8 :  LH_SW2
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[8].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.UFC_Panel.S2 = eOnOFF;
	//
	//// IO idx  9 :  LH_SW3
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[9].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.UFC_Panel.S3 = eOnOFF;
	//
	//// IO idx  10 :  LH_SW4
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[10].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.UFC_Panel.S4 = eOnOFF;
	//
	//// IO idx  11 :  LH_SW5
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[11].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.UFC_Panel.S5 = eOnOFF;
	//
	//// IO idx  12 :  RH_SW1
	//eOnOFF = OFF;
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[12].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.UFC_Panel.S10 = eOnOFF;
	//
	//// IO idx  13 :  RH_SW2
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[13].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.UFC_Panel.S9 = eOnOFF;
	//
	//// IO idx  14 :  RH_SW3
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[14].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.UFC_Panel.S8 = eOnOFF;
	//
	//// IO idx  15 :  RH_SW4
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[15].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.UFC_Panel.S7 = eOnOFF;
	//
	//// IO idx  16 :  RH_SW5
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[16].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.UFC_Panel.S6 = eOnOFF;
	//
	///* IO idx  17 :  DAY
	//   IO idx  18 :  NIGHT
	//   IO idx  19 :  OFF */
	//UFC_PWR_MODE_TYPE eUFCPWR = UFC_PWR_OFF;
	//if (GetDigitalInputBit(IOInfo[17].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eUFCPWR = UFC_PWR_D;
	//
	//if (GetDigitalInputBit(IOInfo[18].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eUFCPWR = UFC_PWR_N;
	//
	//m_stCockpit2HOST.IO2HOST.Main_Panel.UFC_Panel.UFC_Pwr_MODE_Switch = eUFCPWR;
	//
	//// IO idx  20 :  EMIS_LMT_SW
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[20].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.UFC_Panel.EMIS_Btn = eOnOFF;
	//
	//// IO idx  21 :  ROTARY_LEFT_SW
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[21].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.UFC_Panel.Left_Channel_Select_Btn = eOnOFF;
	//
	//// IO idx  22 :  ROTARY_RIGHT_SW
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[22].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH);
	//m_stCockpit2HOST.IO2HOST.Main_Panel.UFC_Panel.Right_Channel_Select_Btn = eOnOFF;
	//
	//// 2019. 09. 24 UFC Button Update 
	//int nSkipCount = 10;
	//
	//// IO idx  23 :  GREC_C/M_LEFT
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[23].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH);
	//
	//if (eOnOFF == OFF)
	//{
	//	static int n23 = 0;
	//
	//	n23++;
	//
	//	if (n23 > nSkipCount) {
	//		eOnOFF = OFF;
	//		n23 = 0;
	//	}
	//	else
	//		eOnOFF = m_stCockpit2HOST.IO2HOST.Main_Panel.UFC_Panel.LEFT_GREC;
	//}
	//
	//m_stCockpit2HOST.IO2HOST.Main_Panel.UFC_Panel.LEFT_GREC = eOnOFF;
	//
	//// IO idx  24 :  A1
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[24].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH);
	//if (eOnOFF == OFF)
	//{
	//	static int n24 = 0;
	//
	//	n24++;
	//
	//	if (n24 > nSkipCount) {
	//		eOnOFF = OFF;
	//		n24 = 0;
	//	}
	//	else
	//		eOnOFF = m_stCockpit2HOST.IO2HOST.Main_Panel.UFC_Panel.KEY_1;
	//}
	//
	//m_stCockpit2HOST.IO2HOST.Main_Panel.UFC_Panel.KEY_1 = eOnOFF;
	//
	//// IO idx  25 :  N2
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[25].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH);
	//
	//if (eOnOFF == OFF)
	//{
	//	static int n25 = 0;
	//
	//	n25++;
	//
	//	if (n25 > nSkipCount) {
	//		eOnOFF = OFF;
	//		n25 = 0;
	//	}
	//	else
	//		eOnOFF = m_stCockpit2HOST.IO2HOST.Main_Panel.UFC_Panel.KEY_2;
	//}
	//
	//m_stCockpit2HOST.IO2HOST.Main_Panel.UFC_Panel.KEY_2 = eOnOFF;
	//
	//// IO idx  26 :  B3
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[26].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH);
	//if (eOnOFF == OFF)
	//{
	//	static int n26 = 0;
	//
	//	n26++;
	//
	//	if (n26 > nSkipCount) {
	//		eOnOFF = OFF;
	//		n26 = 0;
	//	}
	//	else
	//		eOnOFF = m_stCockpit2HOST.IO2HOST.Main_Panel.UFC_Panel.KEY_3;
	//}
	//
	//m_stCockpit2HOST.IO2HOST.Main_Panel.UFC_Panel.KEY_3 = eOnOFF;
	//
	//// IO idx  27 :  GREC_C/M_RIGHT
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[27].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH);
	//if (eOnOFF == OFF)
	//{
	//	static int n27 = 0;
	//
	//	n27++;
	//
	//	if (n27 > nSkipCount) {
	//		eOnOFF = OFF;
	//		n27 = 0;
	//	}
	//	else
	//		eOnOFF = m_stCockpit2HOST.IO2HOST.Main_Panel.UFC_Panel.RIGHT_GREC;
	//}
	//
	//m_stCockpit2HOST.IO2HOST.Main_Panel.UFC_Panel.RIGHT_GREC = eOnOFF;
	//
	//// IO idx  28 :  MARK
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[28].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH);
	//if (eOnOFF == OFF)
	//{
	//	static int n28 = 0;
	//
	//	n28++;
	//
	//	if (n28 > nSkipCount) {
	//		eOnOFF = OFF;
	//		n28 = 0;
	//	}
	//	else
	//		eOnOFF = m_stCockpit2HOST.IO2HOST.Main_Panel.UFC_Panel.MARK;
	//}
	//m_stCockpit2HOST.IO2HOST.Main_Panel.UFC_Panel.MARK = eOnOFF;
	//
	//// IO idx  29 :  W4
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[29].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH);
	//if (eOnOFF == OFF)
	//{
	//	static int n29 = 0;
	//
	//	n29++;
	//
	//	if (n29 > nSkipCount) {
	//		eOnOFF = OFF;
	//		n29 = 0;
	//	}
	//	else
	//		eOnOFF = m_stCockpit2HOST.IO2HOST.Main_Panel.UFC_Panel.KEY_4;
	//}
	//m_stCockpit2HOST.IO2HOST.Main_Panel.UFC_Panel.KEY_4 = eOnOFF;
	//
	//// IO idx  30 :  M5
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[30].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH);
	//if (eOnOFF == OFF)
	//{
	//	static int n30 = 0;
	//
	//	n30++;
	//
	//	if (n30 > nSkipCount) {
	//		eOnOFF = OFF;
	//		n30 = 0;
	//	}
	//	else
	//		eOnOFF = m_stCockpit2HOST.IO2HOST.Main_Panel.UFC_Panel.KEY_5;
	//}
	//m_stCockpit2HOST.IO2HOST.Main_Panel.UFC_Panel.KEY_5 = eOnOFF;
	//
	//// IO idx  31 :  E6
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[31].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH);
	//if (eOnOFF == OFF)
	//{
	//	static int n31 = 0;
	//
	//	n31++;
	//
	//	if (n31 > nSkipCount) {
	//		eOnOFF = OFF;
	//		n31 = 0;
	//	}
	//	else
	//		eOnOFF = m_stCockpit2HOST.IO2HOST.Main_Panel.UFC_Panel.KEY_6;
	//}
	//m_stCockpit2HOST.IO2HOST.Main_Panel.UFC_Panel.KEY_6 = eOnOFF;
	//
	//// IO idx  32 :  I/P
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[32].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH);
	//if (eOnOFF == OFF)
	//{
	//	static int n32 = 0;
	//
	//	n32++;
	//
	//	if (n32 > nSkipCount) {
	//		eOnOFF = OFF;
	//		n32 = 0;
	//	}
	//	else
	//		eOnOFF = m_stCockpit2HOST.IO2HOST.Main_Panel.UFC_Panel.IP;
	//}
	//m_stCockpit2HOST.IO2HOST.Main_Panel.UFC_Panel.IP = eOnOFF;
	//
	//// IO idx  33 :  DOT
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[33].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH);
	//if (eOnOFF == OFF)
	//{
	//	static int n33 = 0;
	//
	//	n33++;
	//
	//	if (n33 > nSkipCount) {
	//		eOnOFF = OFF;
	//		n33 = 0;
	//	}
	//	else
	//		eOnOFF = m_stCockpit2HOST.IO2HOST.Main_Panel.UFC_Panel.DOT;
	//}
	//m_stCockpit2HOST.IO2HOST.Main_Panel.UFC_Panel.DOT = eOnOFF;
	//
	//// IO idx  34 :  :7
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[34].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH);
	//if (eOnOFF == OFF)
	//{
	//	static int n34 = 0;
	//
	//	n34++;
	//
	//	if (n34 > nSkipCount) {
	//		eOnOFF = OFF;
	//		n34 = 0;
	//	}
	//	else
	//		eOnOFF = m_stCockpit2HOST.IO2HOST.Main_Panel.UFC_Panel.KEY_7;
	//}
	//m_stCockpit2HOST.IO2HOST.Main_Panel.UFC_Panel.KEY_7 = eOnOFF;
	//
	//// IO idx  35 :  S8
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[35].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH);
	//if (eOnOFF == OFF)
	//{
	//	static int n35 = 0;
	//
	//	n35++;
	//
	//	if (n35 > nSkipCount) {
	//		eOnOFF = OFF;
	//		n35 = 0;
	//	}
	//	else
	//		eOnOFF = m_stCockpit2HOST.IO2HOST.Main_Panel.UFC_Panel.KEY_8;
	//}
	//m_stCockpit2HOST.IO2HOST.Main_Panel.UFC_Panel.KEY_8 = eOnOFF;
	//
	//// IO idx  36 :  C9
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[36].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH);
	//if (eOnOFF == OFF)
	//{
	//	static int n36 = 0;
	//
	//	n36++;
	//
	//	if (n36 > nSkipCount) {
	//		eOnOFF = OFF;
	//		n36 = 0;
	//	}
	//	else
	//		eOnOFF = m_stCockpit2HOST.IO2HOST.Main_Panel.UFC_Panel.KEY_9;
	//}
	//m_stCockpit2HOST.IO2HOST.Main_Panel.UFC_Panel.KEY_9 = eOnOFF;
	//
	//// IO idx  37 :  SHF
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[37].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH);
	//if (eOnOFF == OFF)
	//{
	//	static int n37 = 0;
	//
	//	n37++;
	//
	//	if (n37 > nSkipCount) {
	//		eOnOFF = OFF;
	//		n37 = 0;
	//	}
	//	else
	//		eOnOFF = m_stCockpit2HOST.IO2HOST.Main_Panel.UFC_Panel.SHF;
	//}
	//m_stCockpit2HOST.IO2HOST.Main_Panel.UFC_Panel.SHF = eOnOFF;
	//
	//// IO idx  38 :  A/P
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[38].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH);
	//if (eOnOFF == OFF)
	//{
	//	static int n38 = 0;
	//
	//	n38++;
	//
	//	if (n38 > nSkipCount) {
	//		eOnOFF = OFF;
	//		n38 = 0;
	//	}
	//	else
	//		eOnOFF = m_stCockpit2HOST.IO2HOST.Main_Panel.UFC_Panel.AP;
	//}
	//m_stCockpit2HOST.IO2HOST.Main_Panel.UFC_Panel.AP = eOnOFF;
	//
	//// IO idx  39 :  CLR
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[39].nChannel - 32, sData.SPARE0, 0);
	//if (eOnOFF == OFF)
	//{
	//	static int n39 = 0;
	//
	//	n39++;
	//
	//	if (n39 > nSkipCount) {
	//		eOnOFF = OFF;
	//		n39 = 0;
	//	}
	//	else
	//		eOnOFF = m_stCockpit2HOST.IO2HOST.Main_Panel.UFC_Panel.CLR;
	//}
	//m_stCockpit2HOST.IO2HOST.Main_Panel.UFC_Panel.CLR = eOnOFF;
	//
	//// IO idx  40 :  0
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[40].nChannel - 32, sData.SPARE0, 0);
	//if (eOnOFF == OFF)
	//{
	//	static int n40 = 0;
	//
	//	n40++;
	//
	//	if (n40 > nSkipCount) {
	//		eOnOFF = OFF;
	//		n40 = 0;
	//	}
	//	else
	//		eOnOFF = m_stCockpit2HOST.IO2HOST.Main_Panel.UFC_Panel.KEY_0;
	//}
	//m_stCockpit2HOST.IO2HOST.Main_Panel.UFC_Panel.KEY_0 = eOnOFF;
	//
	//// IO idx  41 :  DATA
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[41].nChannel - 32, sData.SPARE0, 0);
	//if (eOnOFF == OFF)
	//{
	//	static int n41 = 0;
	//
	//	n41++;
	//
	//	if (n41 > nSkipCount) {
	//		eOnOFF = OFF;
	//		n41 = 0;
	//	}
	//	else
	//		eOnOFF = m_stCockpit2HOST.IO2HOST.Main_Panel.UFC_Panel.DATA;
	//}
	//m_stCockpit2HOST.IO2HOST.Main_Panel.UFC_Panel.DATA = eOnOFF;
	//
	//// IO idx  42 :  MENU
	//eOnOFF = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[42].nChannel - 32, sData.SPARE0, 0);
	//if (eOnOFF == OFF)
	//{
	//	static int n42 = 0;
	//
	//	n42++;
	//
	//	if (n42 > nSkipCount) {
	//		eOnOFF = OFF;
	//		n42 = 0;
	//	}
	//	else
	//		eOnOFF = m_stCockpit2HOST.IO2HOST.Main_Panel.UFC_Panel.MENU;
	//}
	//m_stCockpit2HOST.IO2HOST.Main_Panel.UFC_Panel.MENU = eOnOFF;
	//
	//// 2019.09.24 Button Update
}

// THROTTLE QUADRANT Decode
void CIOSWDataManager::DecodeThrottleQuadrant(const IOBOARD_to_IOSW& sData, const IOBOARD_INFORMATION IOInfo[])
{
	//// IO idx  0 : Target Designator Azimuth 
	//m_stCockpit2HOST.IO2HOST.Left_Panel.TDC_X = (int)GetAnalogInputData(IOInfo[0].nChannel, sData, m_stCockpit2HOST.IO2HOST.Left_Panel.TDC_X, 6);
	//
	//// IO idx  1 : Target Designator Range
	//m_stCockpit2HOST.IO2HOST.Left_Panel.TDC_Y = (int)GetAnalogInputData(IOInfo[1].nChannel, sData, m_stCockpit2HOST.IO2HOST.Left_Panel.TDC_Y, 6);
	//
	//// IO idx  2 : Right Throttle Position
	//m_stCockpit2HOST.IO2HOST.Left_Panel.Right_Throttle_Position = (int)GetAnalogInputData(IOInfo[2].nChannel, sData, m_stCockpit2HOST.IO2HOST.Left_Panel.Right_Throttle_Position, 6);
	//
	//// IO idx  3 : Left Throttle Position
	//m_stCockpit2HOST.IO2HOST.Left_Panel.Left_Throttle_Position = (int)GetAnalogInputData(IOInfo[3].nChannel, sData, m_stCockpit2HOST.IO2HOST.Left_Panel.Left_Throttle_Position, 6);
	//
	//// IO idx  4 : Antenna Elevation Knob
	//m_stCockpit2HOST.IO2HOST.Left_Panel.Antenna_Elev_Knob = (int)GetAnalogInputData(IOInfo[4].nChannel, sData, m_stCockpit2HOST.IO2HOST.Left_Panel.Antenna_Elev_Knob, 6);
	//
	//// IO idx  5 : CMD Up
	//// IO idx  6 : CMD Down
	//POSITION_TYPE ePosition = POSITION_CTR;
	//
	//if (GetDigitalInputBit(IOInfo[5].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	ePosition = POSITION_AFT;
	//
	//if (GetDigitalInputBit(IOInfo[6].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	ePosition = POSITION_FWD;
	//
	//m_stCockpit2HOST.IO2HOST.Left_Panel.CMD_Dispenser_Switch = ePosition;
	//
	//// IO idx  7 : Left Multifunction SW
	//ON_OFF_TYPE eOnOff = OFF;
	//
	//eOnOff = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[7].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH);
	//m_stCockpit2HOST.IO2HOST.Left_Panel.Laser_Fire_Btn = eOnOff;
	//
	//// IO idx  8 : Microphone AFT
	//// IO idx  9 : Microphone FWD
	//ePosition = POSITION_CTR;
	//
	//if (GetDigitalInputBit(IOInfo[8].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	ePosition = POSITION_AFT;
	//
	//if (GetDigitalInputBit(IOInfo[9].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	ePosition = POSITION_FWD;
	//
	//m_stCockpit2HOST.IO2HOST.Left_Panel.Microphone_Switch = ePosition;
	//
	//// IO idx 10 : Target Designate down select
	//eOnOff = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[10].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH);
	//m_stCockpit2HOST.IO2HOST.Left_Panel.TDC_Press_Btn = eOnOff;
	//
	//// IO idx 11 : Undesignate/Missle_reject AFT
	//// IO idx 12 : Undesignate/Missle_reject FWD
	//ePosition = POSITION_CTR;
	//
	//if (GetDigitalInputBit(IOInfo[11].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	ePosition = POSITION_AFT;
	//
	//if (GetDigitalInputBit(IOInfo[12].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	ePosition = POSITION_FWD;
	//
	//m_stCockpit2HOST.IO2HOST.Left_Panel.Undesignate_Missle_Reject_Switch = ePosition;
	//
	//// IO idx 13 : Weapon/mode AFT
	//// IO idx 14 : Weapon/mode FWD
	//ePosition = POSITION_CTR;
	//
	//if (GetDigitalInputBit(IOInfo[13].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	ePosition = POSITION_AFT;
	//
	//if (GetDigitalInputBit(IOInfo[14].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	ePosition = POSITION_FWD;
	//
	//m_stCockpit2HOST.IO2HOST.Left_Panel.Weapon_Mode_Switch = ePosition;
	//
	//// IO idx 15 : Speed Break AFT
	//// IO idx 16 : Speed Break FWD 
	//ePosition = POSITION_CTR;
	//
	//if (GetDigitalInputBit(IOInfo[15].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	ePosition = POSITION_AFT;
	//
	//if (GetDigitalInputBit(IOInfo[16].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	ePosition = POSITION_FWD;
	//
	//m_stCockpit2HOST.IO2HOST.Left_Panel.Speed_Brake_Switch = ePosition;
	//
	//// IO idx 17 : Right Multifunction Up
	//// IO idx 18 : Right Multifunction Right
	//// IO idx 19 : Right Multifunction Down
	//// IO idx 20 : Right Multifunction left
	//MULTIFUNCTION_TYPE eMultiType = HAT_CENTER;
	//
	//if (GetDigitalInputBit(IOInfo[17].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eMultiType = HAT_UP;
	//
	//if (GetDigitalInputBit(IOInfo[18].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eMultiType = HAT_RIGHT;
	//
	//if (GetDigitalInputBit(IOInfo[19].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eMultiType = HAT_DOWN;
	//
	//if (GetDigitalInputBit(IOInfo[20].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eMultiType = HAT_LEFT;
	//
	//m_stCockpit2HOST.IO2HOST.Left_Panel.HAT_Switch = eMultiType;
	//
	//// IO idx 21 : Rudder Trim Right
	//// IO idx 22 : Rudder Trim Left
	//ePosition = POSITION_CTR;
	//
	//if (GetDigitalInputBit(IOInfo[21].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	ePosition = POSITION_AFT;
	//
	//if (GetDigitalInputBit(IOInfo[22].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	ePosition = POSITION_FWD;
	//
	//// Rudder trip swtich is Right or left, KAI ICD is POSITION_TYPE - ICD ? left = POSITION_FWD, right = POSITION_AFT
	//m_stCockpit2HOST.IO2HOST.Left_Panel.Rudder_Trim_Switch = ePosition;
	//
	//// IO idx 23 : Left Finger lift
	//eOnOff = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[23].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH);
	//m_stCockpit2HOST.IO2HOST.Left_Panel.Left_Throttle_Lift = eOnOff;
	//
	//// IO idx 24 : Left_Gate_OFF_SW 
	//// IO idx 25 : Left_Gate_MIL_SW
	//// IO idx 26 : Left_Gate_MAX_SW -> No signal (2019.2.28)
	//// THROTTLE_POSITION_TYPE eThrottlePos = m_stCockpit2HOST.IO2HOST.Left_Panel.Left_Gate_Switch;
	//
/*	//if (GetDigitalInputBit(IOInfo[24].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eThrottlePos = THROTTLE_OFF;
	//
	//if (GetDigitalInputBit(IOInfo[25].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eThrottlePos = THROTTLE_MIL;
	//
	//if (GetDigitalInputBit(IOInfo[26].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eThrottlePos = THROTTLE_MAX;
*/	//
	//
// D//I 신호가 정상적으로 들어오지 않아 아날로그 위치로 DI 처리함 (2019.2.28)
	//THROTTLE_POSITION_TYPE eThrottlePos = m_stCockpit2HOST.IO2HOST.Left_Panel.Left_Gate_Switch;
	//
	//if (GetDigitalInputBit(IOInfo[24].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eThrottlePos = THROTTLE_IDLE;
	//
	//if (GetDigitalInputBit(IOInfo[25].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eThrottlePos = THROTTLE_MIL;
	//
	//int nLeftPosition = m_stCockpit2HOST.IO2HOST.Left_Panel.Left_Throttle_Position;
	//
	//if (nLeftPosition <= 100)
	//	eThrottlePos = THROTTLE_OFF;
	//
	//if (GetDigitalInputBit(IOInfo[26].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eThrottlePos = THROTTLE_MAX;
	//
	////	if (nLeftPosition >= 1000)
	////		eThrottlePos = THROTTLE_MAX;
	//
	//m_stCockpit2HOST.IO2HOST.Left_Panel.Left_Gate_Switch = eThrottlePos;
	//
	//// IO idx 27 : Right Finger lift
	//eOnOff = (ON_OFF_TYPE)GetDigitalInputBit(IOInfo[27].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH);
	//m_stCockpit2HOST.IO2HOST.Left_Panel.Right_Throttle_Lift = eOnOff;
	//
	//// IO idx 28 : Right_Gate_OFF_SW
	//// IO idx 29 : Right_Gate_MIL_SW
	//// IO idx 30 : Right_Gate_MAX_SW -> No signal (2019.2.28)
	//// DI 신호가 정상적으로 들어오지 않아 아날로그 위치로 DI 처리함 (2019.2.28)
	//// eThrottlePos = m_stCockpit2HOST.IO2HOST.Left_Panel.Right_Gate_Switch;
	//
	///*
	//if (GetDigitalInputBit(IOInfo[28].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eThrottlePos = THROTTLE_OFF;
	//
	//if (GetDigitalInputBit(IOInfo[29].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eThrottlePos = THROTTLE_MIL;
	//
	//if (GetDigitalInputBit(IOInfo[30].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eThrottlePos = THROTTLE_MAX;
	//*/
// D//I 신호가 정상적으로 들어오지 않아 아날로그 위치로 DI 처리함 (2019.2.28)
	//eThrottlePos = m_stCockpit2HOST.IO2HOST.Left_Panel.Right_Gate_Switch;
	//
	//if (GetDigitalInputBit(IOInfo[28].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eThrottlePos = THROTTLE_IDLE;
	//
	//if (GetDigitalInputBit(IOInfo[29].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eThrottlePos = THROTTLE_MIL;
	//
	//int nRightPosition = m_stCockpit2HOST.IO2HOST.Left_Panel.Right_Throttle_Position;
	//
	//if (nRightPosition <= 100)
	//	eThrottlePos = THROTTLE_OFF;
	//
	//if (GetDigitalInputBit(IOInfo[30].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eThrottlePos = THROTTLE_MAX;
	//
	//m_stCockpit2HOST.IO2HOST.Left_Panel.Right_Gate_Switch = eThrottlePos;
	//
	//
	//// IO idx 31 : Flap Switch
	//ePosition = POSITION_FWD;
	//
	//if (GetDigitalInputBit(IOInfo[31].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	ePosition = POSITION_AFT;
	//
	//// Flap swtich is On or Off, KAI ICD is POSITION_TYPE - ICD ? off = POSITION_FWD, on = POSITION_AFT
	//m_stCockpit2HOST.IO2HOST.Left_Panel.Flap_Switch = ePosition;

}

void CIOSWDataManager::DecodeSAI(const IOBOARD_to_IOSW& sData, const IOBOARD_INFORMATION IOInfo[])
{
	//// IO idx 6 : SAI Knob
	//int nKnob = GetAnalogInputData(IOInfo[6], sData, m_stCockpit2HOST.IO2HOST.Main_Panel.Indicator.Standby_Attitude_Knob_Value);
	//
	//m_stCockpit2HOST.IO2HOST.Main_Panel.Indicator.Standby_Attitude_Knob_Value = nKnob;
	//
	//// IO idx 7 : SAI_PULL_SW
	//PULL_TO_CAGE_KNOB_TYPE ePull = PULL_TO_CAGE_OFF;
	//
	//if (GetDigitalInputBit(IOInfo[7].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_LOW)
	//	ePull = PULL_TO_CAGE_PULLED;
	//
	//m_stCockpit2HOST.IO2HOST.Main_Panel.Indicator.Pull_To_Cage_Knob = ePull;
}

void CIOSWDataManager::DecodeAltimeter(const IOBOARD_to_IOSW& sData, const IOBOARD_INFORMATION IOInfo[])
{
	//// IO idx 6 : Altimeter Knob
	//static int nOldKnob = 0;
	//int nValue = 0;
	//
	//if (nOldKnob != 0)
	//{
	//	if (nOldKnob < sData.SPARE0)
	//		nValue = 1;
	//	else if (nOldKnob > sData.SPARE0)
	//		nValue = -1;
	//	else
	//	{
	//		static int nTemp = 0;
	//
	//		nTemp++;
	//
	//		if (nTemp > 10)
	//		{
	//			nValue = 0;
	//			nTemp = 0;
	//		}
	//		else
	//		{
	//			nValue = m_stCockpit2HOST.IO2HOST.Main_Panel.Indicator.Altimeter_Knob_Value;
	//		}
	//
	//	}
	//}
	//m_stCockpit2HOST.IO2HOST.Main_Panel.Indicator.Altimeter_Knob_Value = nValue;
	//
	//nOldKnob = sData.SPARE0;
}


void CIOSWDataManager::DecodeClock(const IOBOARD_to_IOSW& sData, const IOBOARD_INFORMATION IOInfo[])
{
	//// IO idx  6 : PUSH HARD		
	//ON_OFF_TYPE eONOff = OFF;
	//
	//if (GetDigitalInputBit(IOInfo[6].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eONOff = ON;
	//
	//m_stCockpit2HOST.IO2HOST.Main_Panel.Indicator.Clock_Push_Btn = eONOff;
}

void CIOSWDataManager::DecodeFQI(const IOBOARD_to_IOSW& sData, const IOBOARD_INFORMATION IOInfo[])
{
	//// IO idx  6 : BIT		
	//// IO idx  7 : FEED	
	//// IO idx  8 : INTL_WING
	//// IO idx  9 : TANK	
	//// IO idx  10 : EXT_WING
	//// IO idx  11 : EXT_CTR	
	//// IO idx  12 : CONF_TANK
	//
	//FUEL_QTY_SELECT_TYPE eFQIType = m_stCockpit2HOST.IO2HOST.Main_Panel.Indicator.Fuel_Qty_Select_Switch;
	//
	//if (GetDigitalInputBit(IOInfo[6].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eFQIType = BIT;
	//
	//if (GetDigitalInputBit(IOInfo[7].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eFQIType = FEED;
	//
	//if (GetDigitalInputBit(IOInfo[8].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eFQIType = INTL_WING;
	//
	//if (GetDigitalInputBit(IOInfo[9].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eFQIType = TANK;
	//
	//if (GetDigitalInputBit(IOInfo[10].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eFQIType = EXT_WING;
	//
	//if (GetDigitalInputBit(IOInfo[11].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eFQIType = EXT_CTR;
	//
	//if (GetDigitalInputBit(IOInfo[12].nChannel, sData.DI_CH_LOW, sData.DI_CH_HIGH) == DI_HIGH)
	//	eFQIType = CONF__TANK;
	//
	//m_stCockpit2HOST.IO2HOST.Main_Panel.Indicator.Fuel_Qty_Select_Switch = eFQIType;
	//
	//// IO idx 13 : BINGO_KNOB
	//static int nBingoOldKnob = 0;
	//int nBingoValue = 0;
	//
	//if (nBingoOldKnob != 0)
	//{
	//	if (nBingoOldKnob < sData.SPARE0)
	//		nBingoValue = 1;
	//	else if (nBingoOldKnob > sData.SPARE0)
	//		nBingoValue = -1;
	//	else
	//		nBingoValue = 0;
	//}
	//m_stCockpit2HOST.IO2HOST.Main_Panel.Indicator.Fuel_Bingo_Knob_Value = nBingoValue;
	//nBingoOldKnob = sData.SPARE0;

}
