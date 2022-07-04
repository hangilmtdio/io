#include "stdafx.h"
#include "IOSWDataManager.h"
#include "IOSWUtilities.h"

CIOSWDataManager::CIOSWDataManager()
{
	m_pIODevieInfoMgr = NULL;
}


CIOSWDataManager::~CIOSWDataManager()
{
}


void CIOSWDataManager::Initialize(CIODeviceInformationManager* pInfoMgr)
{
	ZeroMemory(&m_stGUI2IOSW, sizeof(m_stGUI2IOSW));
	ZeroMemory(&m_stIOSW2GUI, sizeof(m_stIOSW2GUI));

	m_stGUI2IOSW.bPowerON = true;
	m_pIODevieInfoMgr = pInfoMgr;

	// Set LCD Display 
	int nIOBoardCount = CIOSWUtilities::LoadIOConfigNumber(_T("IOBOARD_INFO"), _T("IOBOARD_COUNT"));

	for (int i = 0; i < nIOBoardCount; i++) 
	{
		
		CString strTemp;
		strTemp.Format(_T("IOBOARD_%d"), i);

		int nBoardID = CIOSWUtilities::LoadIOConfigNumber(strTemp, _T("IOBOARD_ID"));

		if (nBoardID >= 41 && nBoardID <= 49)
		{
			int nBrightness = CIOSWUtilities::LoadIOConfigNumber(strTemp, _T("DISPLAY_BRIGHTNESS"));
			int nDegree = CIOSWUtilities::LoadIOConfigNumber(strTemp, _T("DISPLAY_DEGREE"));
			int nX = CIOSWUtilities::LoadIOConfigNumber(strTemp, _T("DISPLAY_X"));
			int nY = CIOSWUtilities::LoadIOConfigNumber(strTemp, _T("DISPLAY_Y"));
			int nHor = CIOSWUtilities::LoadIOConfigNumber(strTemp, _T("DISPLAY_WIDTH"));
			int nVer = CIOSWUtilities::LoadIOConfigNumber(strTemp, _T("DISPLAY_HEIGHT"));


			m_stGUI2IOSW.sIOSW2IOBoard[nBoardID].CH0_FREQ_28V = (unsigned short)nBrightness;
			m_stGUI2IOSW.sIOSW2IOBoard[nBoardID].CH0_WIDTH_28V = (unsigned short)nDegree;
			m_stGUI2IOSW.sIOSW2IOBoard[nBoardID].CH1_FREQ_28V = (unsigned short)nX;
			m_stGUI2IOSW.sIOSW2IOBoard[nBoardID].CH1_WIDTH_28V = (unsigned short)nY;
			m_stGUI2IOSW.sIOSW2IOBoard[nBoardID].CH2_FREQ_28V = (unsigned short)nHor;
			m_stGUI2IOSW.sIOSW2IOBoard[nBoardID].CH2_WIDTH_28V = (unsigned short)nVer;

		}

	}
}

void CIOSWDataManager::GetGUI2IOSWData(IOSWGUI_to_IOSW* psData)
{
	::memcpy(psData, &m_stGUI2IOSW, sizeof(IOSWGUI_to_IOSW));
}

void CIOSWDataManager::SetGUI2IOSWData(const IOSWGUI_to_IOSW & sData)
{
	::memcpy(&m_stGUI2IOSW, &sData, sizeof(IOSWGUI_to_IOSW));
}

void CIOSWDataManager::GetIOSW2GUIData(IOSW_to_IOSWGUI* psData)
{
	::memcpy(psData, &m_stIOSW2GUI, sizeof(IOSW_to_IOSWGUI));
}

void CIOSWDataManager::SetIOSW2GUIData(const IOSW_to_IOSWGUI & sData)
{
	::memcpy(&m_stIOSW2GUI, &sData, sizeof(IOSW_to_IOSWGUI));
}

void CIOSWDataManager::GetIOSW2IOBoardData(IOSW_to_IOBOARD* psData, const int & nBoardID)
{
	::memcpy(psData, &m_stIOSW2GUI.sIOSW2IOBoard[nBoardID], sizeof(IOSW_to_IOBOARD));
}

void CIOSWDataManager::GetIOBoard2IOSWData(IOBOARD_to_IOSW* psData, const int & nBoardID)
{
	::memcpy(psData, &m_stIOSW2GUI.sIOBoard2IOSW[nBoardID], sizeof(IOBOARD_to_IOSW));
}

void CIOSWDataManager::GetMaintenanceIOBoardOutputData(IOSW_to_IOBOARD* psData, const int & nBoardID)
{
	::memcpy(psData, &m_stGUI2IOSW.sIOSW2IOBoard[nBoardID], sizeof(IOSW_to_IOBOARD));
}

void CIOSWDataManager::SetMaintenanceIOBoardOutputData(const IOSW_to_IOBOARD & sData, const int & nBoardID)
{
	::memcpy(&m_stGUI2IOSW.sIOSW2IOBoard[nBoardID], &sData, sizeof(IOSW_to_IOBOARD));
}

void CIOSWDataManager::SetMaintenaceDigialOutputData(const int & nBoardID, const int & nChannel, const int & nOnOff)
{
	IOSW_to_IOBOARD sIOSW2IOBoard;
	
	GetMaintenanceIOBoardOutputData(&sIOSW2IOBoard, nBoardID);

	SetDigitalOutputBit(nChannel, nOnOff, sIOSW2IOBoard);

	SetMaintenanceIOBoardOutputData(sIOSW2IOBoard, nBoardID);
}

void CIOSWDataManager::SetMaintenaceAnalogOutputData(const int & nBoardID, const int & nChannel, const unsigned short & usData)
{
	IOSW_to_IOBOARD sIOSW2IOBoard;

	GetMaintenanceIOBoardOutputData(&sIOSW2IOBoard, nBoardID);

	// LCD Brightness 
	if (nBoardID >= 41 && nBoardID <= 49)
	{
		switch (nChannel)
		{
		case 1:	// Brightness
			sIOSW2IOBoard.CH0_FREQ_28V = usData;
			break;
		case 2: // Degree
			sIOSW2IOBoard.CH0_WIDTH_28V = usData;
			break;
		case 3: // X Location
			sIOSW2IOBoard.CH1_FREQ_28V = usData;
			break;
		case 4: // Y Location
			sIOSW2IOBoard.CH1_WIDTH_28V = usData;
			break;
		case 5: // Horizontal
			sIOSW2IOBoard.CH2_FREQ_28V = usData;
			break;
		case 6: // Vertical
			sIOSW2IOBoard.CH2_WIDTH_28V = usData;
			break;
		default:
			break;
		}
		
	}
	else // Other AO Data 
	{
		SetAnalogOutputData(nChannel, usData, sIOSW2IOBoard);
	}

	SetMaintenanceIOBoardOutputData(sIOSW2IOBoard, nBoardID);
}

void CIOSWDataManager::SetMaintenaceCautionLightPanel(const int & nBoardID, const int & nDeviceID, const int & nChannel, const unsigned short & usData)
{
	IOSW_to_IOBOARD sIOSW2IOBoard;

	GetMaintenanceIOBoardOutputData(&sIOSW2IOBoard, nBoardID);

	if (nDeviceID == 67) // CLP
	{
		switch (nChannel)
		{
		case 1:
			sIOSW2IOBoard.CAUTION_CH0 = usData;
			break;
		case 2:
			sIOSW2IOBoard.CAUTION_CH1 = usData;
			break;
		case 3:
			sIOSW2IOBoard.CAUTION_CH2 = usData;
			break;
		case 4:
			sIOSW2IOBoard.CAUTION_CH3 = usData;
			break;
		case 5:
			sIOSW2IOBoard.CAUTION_CH4 = usData;
			break;
		case 6:
			sIOSW2IOBoard.CAUTION_CH5 = usData;
			break;
		case 7:
			sIOSW2IOBoard.CAUTION_CH6 = usData;
			break;
		case 8:
			sIOSW2IOBoard.CAUTION_CH7 = usData;
			break;
		case 9:
			sIOSW2IOBoard.CAUTION_CH8 = usData;
			break;
		case 10:
			sIOSW2IOBoard.CAUTION_CH9 = usData;
			break;
		case 11:
			sIOSW2IOBoard.CAUTION_CH10 = usData;
			break;
		case 12:
			sIOSW2IOBoard.CAUTION_CH11 = usData;
			break;
		case 13:
			sIOSW2IOBoard.CAUTION_CH12 = usData;
			break;
		case 14:
			sIOSW2IOBoard.CAUTION_CH13 = usData;
			break;
		case 15:
			sIOSW2IOBoard.CAUTION_CH14 = usData;
			break;
		case 16:
			sIOSW2IOBoard.CAUTION_CH15 = usData;
			break;
		case 17:
			sIOSW2IOBoard.CAUTION_CH16 = usData;
			break;
		case 18:
			sIOSW2IOBoard.CAUTION_CH17 = usData;
			break;
		case 19:
			sIOSW2IOBoard.CAUTION_CH18 = usData;
			break;
		case 20:
			sIOSW2IOBoard.CAUTION_CH19 = usData;
			break;
		default:
			break;
		}

	}
	else // GND TEST
	{
		switch (nChannel)
		{
		case 1:
			sIOSW2IOBoard.CAUTION_CH0 = usData;
			break;
		case 2:
			sIOSW2IOBoard.CAUTION_CH1 = usData;
			break;
		case 3:
			sIOSW2IOBoard.CAUTION_CH2 = usData;
			break;
		case 4:
			sIOSW2IOBoard.CAUTION_CH3 = usData;
			break;
		case 5:
			sIOSW2IOBoard.CAUTION_CH4 = usData;
			break;
		case 6:
			sIOSW2IOBoard.CAUTION_CH5 = usData;
			break;
		case 7:
			sIOSW2IOBoard.CAUTION_CH6 = usData;
			break;
		case 8:
			sIOSW2IOBoard.CAUTION_CH7 = usData;
			break;
		case 9:
			sIOSW2IOBoard.CAUTION_CH8 = usData;
			break;
		case 10:
			sIOSW2IOBoard.CAUTION_CH9 = usData;
			break;
		case 11:
			sIOSW2IOBoard.CAUTION_CH10 = usData;
			break;
		case 12:
			sIOSW2IOBoard.CAUTION_CH11 = usData;
			break;
		case 13:
			sIOSW2IOBoard.CAUTION_CH12 = usData;
			break;
		case 16:
			sIOSW2IOBoard.CAUTION_CH13 = usData;
			break;
		case 17:
			sIOSW2IOBoard.CAUTION_CH14 = usData;
			break;
		case 18:
			sIOSW2IOBoard.CAUTION_CH15 = usData;
			break;
		case 19:
			sIOSW2IOBoard.CAUTION_CH16 = usData;
			break;
		case 20:
			sIOSW2IOBoard.CAUTION_CH17 = usData;
			break;
		case 21:
			sIOSW2IOBoard.CAUTION_CH18 = usData;
			break;
		case 22:
			sIOSW2IOBoard.CAUTION_CH19 = usData;
			break;
		default:
			break;
		}
	}


	SetMaintenanceIOBoardOutputData(sIOSW2IOBoard, nBoardID);

}


void CIOSWDataManager::SetMaintenaceDimmingData(const int & nBoardID, const int & nChannel, const unsigned short & usData)
{
	IOSW_to_IOBOARD sIOSW2IOBoard;

	GetMaintenanceIOBoardOutputData(&sIOSW2IOBoard, nBoardID);

	SetDimmingData(nChannel, usData, sIOSW2IOBoard);

	SetMaintenanceIOBoardOutputData(sIOSW2IOBoard, nBoardID);
}

void CIOSWDataManager::SetMaintenaceIndicatorData(const int & nBoardID, const int & nChannel, const unsigned short & usData)
{
	IOSW_to_IOBOARD sIOSW2IOBoard;

	GetMaintenanceIOBoardOutputData(&sIOSW2IOBoard, nBoardID);

	SetIndicatorData(nBoardID, nChannel, usData, sIOSW2IOBoard);

	SetMaintenanceIOBoardOutputData(sIOSW2IOBoard, nBoardID);
}

void CIOSWDataManager::SetMaintenaceRudderFunctionData(const int & nBoardID, const TRIM_COMMAND & eCommand)
{
	IOSW_to_IOBOARD sIOSW2IOBoard;

	GetMaintenanceIOBoardOutputData(&sIOSW2IOBoard, nBoardID);

	switch (eCommand)
	{
	case TC_NONE:
		sIOSW2IOBoard.RUDDER_INIT = 0;
		sIOSW2IOBoard.RUDDER_LH_TRIM = 0;
		sIOSW2IOBoard.RUDDER_RH_TRIM = 0;
		break;
	case TC_INIT:
		sIOSW2IOBoard.RUDDER_INIT = 1;
		sIOSW2IOBoard.RUDDER_LH_TRIM = 0;
		sIOSW2IOBoard.RUDDER_RH_TRIM = 0;
		break;
	case TC_LEFT:
		sIOSW2IOBoard.RUDDER_INIT = 0;
		sIOSW2IOBoard.RUDDER_LH_TRIM = 1;
		sIOSW2IOBoard.RUDDER_RH_TRIM = 0;
		break;
	case TC_RIGHT:
		sIOSW2IOBoard.RUDDER_INIT = 0;
		sIOSW2IOBoard.RUDDER_LH_TRIM = 0;
		sIOSW2IOBoard.RUDDER_RH_TRIM = 1;
		break;
	default:
		break;
	}

	SetMaintenanceIOBoardOutputData(sIOSW2IOBoard, nBoardID);
}

void CIOSWDataManager::SetMaintenaceStickFunctionData(const int & nBoardID, const TRIM_COMMAND & eCommand)
{
	IOSW_to_IOBOARD sIOSW2IOBoard;

	GetMaintenanceIOBoardOutputData(&sIOSW2IOBoard, nBoardID);

	switch (eCommand)
	{
	case TC_NONE:
		sIOSW2IOBoard.STICK_INIT = 0;
		sIOSW2IOBoard.STICK_TRIM_LEFT = 0;
		sIOSW2IOBoard.STICK_TRIM_RIGHT = 0;
		sIOSW2IOBoard.STICK_TRIM_FRONT = 0;
		sIOSW2IOBoard.STICK_TRIM_REAR = 0;

		break;
	case TC_INIT:
		sIOSW2IOBoard.STICK_INIT = 1;
		sIOSW2IOBoard.STICK_TRIM_LEFT = 0;
		sIOSW2IOBoard.STICK_TRIM_RIGHT = 0;
		sIOSW2IOBoard.STICK_TRIM_FRONT = 0;
		sIOSW2IOBoard.STICK_TRIM_REAR = 0;

		break;
	case TC_LEFT:
		sIOSW2IOBoard.STICK_INIT = 0;
		sIOSW2IOBoard.STICK_TRIM_LEFT = 1;
		sIOSW2IOBoard.STICK_TRIM_RIGHT = 0;
		sIOSW2IOBoard.STICK_TRIM_FRONT = 0;
		sIOSW2IOBoard.STICK_TRIM_REAR = 0;
		break;
	case TC_RIGHT:
		sIOSW2IOBoard.STICK_INIT = 0;
		sIOSW2IOBoard.STICK_TRIM_LEFT = 0;
		sIOSW2IOBoard.STICK_TRIM_RIGHT = 1;
		sIOSW2IOBoard.STICK_TRIM_FRONT = 0;
		sIOSW2IOBoard.STICK_TRIM_REAR = 0;
		break;
	case TC_FRONT:
		sIOSW2IOBoard.STICK_INIT = 0;
		sIOSW2IOBoard.STICK_TRIM_LEFT = 0;
		sIOSW2IOBoard.STICK_TRIM_RIGHT = 0;
		sIOSW2IOBoard.STICK_TRIM_FRONT = 1;
		sIOSW2IOBoard.STICK_TRIM_REAR = 0;
		break;
	case TC_REAR:
		sIOSW2IOBoard.STICK_INIT = 0;
		sIOSW2IOBoard.STICK_TRIM_LEFT = 0;
		sIOSW2IOBoard.STICK_TRIM_RIGHT = 0;
		sIOSW2IOBoard.STICK_TRIM_FRONT = 0;
		sIOSW2IOBoard.STICK_TRIM_REAR = 1;
		break;
	default:
		break;
	}

	SetMaintenanceIOBoardOutputData(sIOSW2IOBoard, nBoardID);
}

void CIOSWDataManager::SetIOSWMode(IOSW_MODE eMode)
{
	m_stGUI2IOSW.eIOSWMode = eMode;
}

void CIOSWDataManager::UpdateIOMonitoringData()
{
	if (m_pIODevieInfoMgr == NULL)
		return;

	LIST_ID IDList;
	
	m_pIODevieInfoMgr->GetDeviceIDList(&IDList);

	for (LIST_ID_ITR itr = IDList.begin(); itr != IDList.end(); ++itr) {
		int nID = *itr;

		CIODeviceInfo* pInfo =  m_pIODevieInfoMgr->GetDeivceInfo(nID);

		if (pInfo != NULL) {

			UpdateIOBoardMonitoring(pInfo);
		}
	}
}

void CIOSWDataManager::UpdateIOBoardMonitoring(CIODeviceInfo* pInfo)
{
	LIST_ID IOIndexList;

	pInfo->GetIOIndexList(&IOIndexList);

	for (LIST_ID_ITR IOItr = IOIndexList.begin(); IOItr != IOIndexList.end(); ++IOItr) {
		int nIndex = *IOItr;

		sIOInformation* psIOInfo = pInfo->GetIOInfo(nIndex);

		if (psIOInfo != NULL) {
			UpdateIOMonitoring(psIOInfo, pInfo->GetBoardID(), pInfo->GetDeviceID());
		}
	}
}

void CIOSWDataManager::UpdateIOMonitoring(sIOInformation* psInfo, int nBoardID, int nDeivceID)
{
	IOBOARD_to_IOSW sIOBoard2IOSW;
	IOSW_to_IOBOARD	sIOSW2IOBoard;

	GetIOBoard2IOSWData(&sIOBoard2IOSW, nBoardID);
	GetIOSW2IOBoardData(&sIOSW2IOBoard, nBoardID);
//	SetMaintenanceIOBoardOutputData(sIOSW2IOBoard, nBoardID);

	switch (psInfo->eKind)
	{
	case IK_DI:
		if (nBoardID == 17 )//&& m_stGUI2IOSW.eIOSWMode == IM_MAINTENANCE)	// Rudder DI
		{
			if (psInfo->nChannel == 1) // LH
			{
				psInfo->szValue = sIOBoard2IOSW.BRAKE_LH;
			}
			else if (psInfo->nChannel == 2) //RH                     
			{
				psInfo->szValue = sIOBoard2IOSW.BRAKE_RH;
			}
			else{}

		}
		else 
		{
			if (nDeivceID >= 81 && nDeivceID <= 83)
			{
				// MPD, MPCD DI
				psInfo->szValue = (unsigned char)GetDigitalInputBit(psInfo->nChannel, sIOBoard2IOSW.SPARE0);
			}
			else
			{
				// Common DI
				psInfo->szValue = (unsigned char)GetDigitalInputBit(psInfo->nChannel, sIOBoard2IOSW);
			}

		}

		break;
	case IK_DO:
		psInfo->szValue = (unsigned char)GetDigitalOutputBit(psInfo->nChannel, sIOSW2IOBoard);
		break;
	case IK_AI:
		if (nDeivceID == 70)
		{
			if (psInfo->nChannel == 9)
				psInfo->nValue = sIOBoard2IOSW.SPARE1;
			else if(psInfo->nChannel == 10)
				psInfo->nValue = sIOBoard2IOSW.SPARE2;
			else
				psInfo->nValue = (int) GetAnalogInputData(psInfo->nChannel, sIOBoard2IOSW);
		}
		else if (nDeivceID == 73)
		{
			psInfo->nValue = sIOBoard2IOSW.SPARE0;
		}
		else if (nDeivceID == 79)
		{
			psInfo->nValue = sIOBoard2IOSW.SPARE0;
		}
		else
		{
			psInfo->nValue = (int) GetAnalogInputData(psInfo->nChannel, sIOBoard2IOSW);
		}
		break;
	case IK_AO:
	{
		switch (nDeivceID)
		{
		case 67: // Caution Light Panel
			psInfo->usValue = GetCautionLightPanel(psInfo->nChannel, sIOSW2IOBoard);
			break;
		case 68: // GND Test
			psInfo->usValue = GetGNDTestPanel(psInfo->nChannel, sIOSW2IOBoard);
			break;
		case 71:
		case 72:
		case 73:
		case 74:
		case 75:
		case 76:
		case 77:
		case 78:
		case 79:
		{
			switch (psInfo->nChannel)
			{
			case 1: // BRIGHTNESS
				psInfo->usValue = sIOSW2IOBoard.CH0_FREQ_28V;
				break;
			case 2: // DISPLAY_DEGREE
				psInfo->usValue = sIOSW2IOBoard.CH0_WIDTH_28V;
				break;
			case 3: // DISPLAY_X
				psInfo->usValue = sIOSW2IOBoard.CH1_FREQ_28V;
				break;
			case 4: // DISPLAY_Y
				psInfo->usValue = sIOSW2IOBoard.CH1_WIDTH_28V;
				break;
			case 5: // DISPLAY_HORIZONTAL
				psInfo->usValue = sIOSW2IOBoard.CH2_FREQ_28V;
				break;
			case 6: // DISPLAY_VERTICAL
				psInfo->usValue = sIOSW2IOBoard.CH2_WIDTH_28V;
				break;
			default:
				break;
			}
			break;
		}
		default:
			psInfo->usValue = GetAnalogOutputData(psInfo->nChannel, sIOSW2IOBoard);
		}
		break;
	}
	case IK_DIMMER:
		psInfo->usValue = GetDimmingData(psInfo->nChannel, sIOSW2IOBoard);
		break;
	case IK_AO_IDC:
		psInfo->fValue = (float)GetIndicatorData(nBoardID, psInfo->nChannel, sIOSW2IOBoard);
		break;
	case IK_AI_SR:
		psInfo->fValue = GetStickRudderInputData(nBoardID, psInfo->nChannel, sIOBoard2IOSW);
		break;
	default:
		break;
	}
}


int	CIOSWDataManager::GetDigitalInputBit(const int nChannel, const IOBOARD_to_IOSW & sData)
{
	int nRet = 0;

	unsigned short nData = 0;
	int nTempChannel = 0;

	if (nChannel <= 16)
	{
		nData = sData.DI_CH_LOW;
		nTempChannel = nChannel;
	}
	else if (nChannel > 32)
	{
		nData = sData.SPARE0;
		nTempChannel = nChannel - 32;
	}
	else{
		nData = sData.DI_CH_HIGH;
		nTempChannel = nChannel - 16;
	}

	switch (nTempChannel)
	{
	case 1:
		nRet = (nData & 0x01);
		break;
	case 2:
		nRet = (nData & 0x02) >> 1;
		break;
	case 3:
		nRet = (nData & 0x04) >> 2;
		break;
	case 4:
		nRet = (nData & 0x08) >> 3;
		break;
	case 5:
		nRet = (nData & 0x10) >> 4;
		break;
	case 6:
		nRet = (nData & 0x20) >> 5;
		break;
	case 7:
		nRet = (nData & 0x40) >> 6;
		break;
	case 8:
		nRet = (nData & 0x80) >> 7;
		break;
	case 9:
		nRet = (nData & 0x100) >> 8;
		break;
	case 10:
		nRet = (nData & 0x200) >> 9;
		break;
	case 11:
		nRet = (nData & 0x400) >> 10;
		break;
	case 12:
		nRet = (nData & 0x800) >> 11;
		break;
	case 13:
		nRet = (nData & 0x1000) >> 12;
		break;
	case 14:
		nRet = (nData & 0x2000) >> 13;
		break;
	case 15:
		nRet = (nData & 0x4000) >> 14;
		break;
	case 16:
		nRet = (nData & 0x8000) >> 15;
		break;
	default:
		break;
	}

	return nRet;
}

int CIOSWDataManager::GetDigitalInputBit(const int nChannel, const int n32Data)
{
	int nRet = 0;

	unsigned short nData = 0;
	int nTempChannel = 0;

	if (nChannel <= 16) {
		nData = (unsigned short)(n32Data & 0xFFFF);
		nTempChannel = nChannel;
	}
	else {
		nData = (unsigned short)((n32Data & 0xFFFF0000) >> 16);
		nTempChannel = nChannel - 16;
	}

	switch (nTempChannel)
	{
	case 1:
		nRet = (nData & 0x01);
		break;
	case 2:
		nRet = (nData & 0x02) >> 1;
		break;
	case 3:
		nRet = (nData & 0x04) >> 2;
		break;
	case 4:
		nRet = (nData & 0x08) >> 3;
		break;
	case 5:
		nRet = (nData & 0x10) >> 4;
		break;
	case 6:
		nRet = (nData & 0x20) >> 5;
		break;
	case 7:
		nRet = (nData & 0x40) >> 6;
		break;
	case 8:
		nRet = (nData & 0x80) >> 7;
		break;
	case 9:
		nRet = (nData & 0x100) >> 8;
		break;
	case 10:
		nRet = (nData & 0x200) >> 9;
		break;
	case 11:
		nRet = (nData & 0x400) >> 10;
		break;
	case 12:
		nRet = (nData & 0x800) >> 11;
		break;
	case 13:
		nRet = (nData & 0x1000) >> 12;
		break;
	case 14:
		nRet = (nData & 0x2000) >> 13;
		break;
	case 15:
		nRet = (nData & 0x4000) >> 14;
		break;
	case 16:
		nRet = (nData & 0x8000) >> 15;
		break;
	default:
		break;
	}

	return nRet;
}

int	CIOSWDataManager::GetDigitalOutputBit(const int nChannel, const IOSW_to_IOBOARD & sData)
{
	int nRet = 0;

	if (nChannel > 0 && nChannel <= 8)			// DO 28V
	{
		nRet = Get28VDigitalOutputBit(nChannel, sData);
	}
	else if (nChannel > 8  && nChannel <= 13)	// DO 24V
	{
		nRet = Get24VDigitalOutputBit(nChannel, sData);
	}
	else if (nChannel > 13 && nChannel <= 16)	// DO 5V
	{
		nRet = Get5VDigitalOutputBit(nChannel, sData);
	}

	return nRet;
}

int	CIOSWDataManager::Get28VDigitalOutputBit(const int nChannel, const IOSW_to_IOBOARD & sData)
{
	int nRet = 0;

	unsigned char szData = 0;

	szData = sData.DO_28V;

	switch (nChannel)
	{
	case 1:
		nRet = (szData & 0x01);
		break;
	case 2:
		nRet = (szData & 0x02) >> 1;
		break;
	case 3:
		nRet = (szData & 0x04) >> 2;
		break;
	case 4:
		nRet = (szData & 0x08) >> 3;
		break;
	case 5:
		nRet = (szData & 0x10) >> 4;
		break;
	case 6:
		nRet = (szData & 0x20) >> 5;
		break;
	case 7:
		nRet = (szData & 0x40) >> 6;
		break;
	case 8:
		nRet = (szData & 0x80) >> 7;
		break;
	default:
		break;
	}

	return nRet;
}

int	CIOSWDataManager::Get24VDigitalOutputBit(const int nChannel, const IOSW_to_IOBOARD & sData)
{
	int nRet = 0;

	unsigned char szData = 0;

	szData = sData.DO_24V;

	switch (nChannel)
	{
	case 9:
		nRet = (szData & 0x01);
		break;
	case 10:
		nRet = (szData & 0x02) >> 1;
		break;
	case 11:
		nRet = (szData & 0x04) >> 2;
		break;
	case 12:
		nRet = (szData & 0x08) >> 3;
		break;
	case 13:
		nRet = (szData & 0x10) >> 4;
		break;
	default:
		break;
	}

	return nRet;
}

int	CIOSWDataManager::Get5VDigitalOutputBit(const int nChannel, const IOSW_to_IOBOARD & sData)
{
	int nRet = 0;

	unsigned char szData = 0;

	szData = sData.DO_5V;

	switch (nChannel)
	{
	case 14:
		nRet = (szData & 0x01);
		break;
	case 15:
		nRet = (szData & 0x02) >> 1;
		break;
	case 16:
		nRet = (szData & 0x04) >> 2;
		break;
	default:
		break;
	}

	return nRet;
}

void CIOSWDataManager::SetDigitalOutputBit(const int nChannel, const int & nOnOff, IOSW_to_IOBOARD & sData)
{
	if (nChannel > 0 && nChannel <= 8)		 // DO 28V
	{
		Set28VDigitalOutputBit(nChannel, nOnOff, sData);
	} 
	else if (nChannel > 8 && nChannel <= 13) // DO 24V
	{
		Set24VDigitalOutputBit(nChannel, nOnOff, sData);
	}
	else if(nChannel > 13 && nChannel <= 16) // DO 5V
	{
		Set5VDigitalOutputBit(nChannel, nOnOff, sData);
	}
}

void CIOSWDataManager::Set28VDigitalOutputBit(const int nChannel, const int & nOnOff, IOSW_to_IOBOARD & sData)
{
	//unsigned char szOnOff = 0x00;

	// DO 24V
	unsigned char sz28V = sData.DO_28V;

	if (nOnOff == 0) {
		sz28V &= ~(1 << (nChannel - 1));
	}
	else
	{
		sz28V |= 0x01 << (nChannel - 1);
	}

	sData.DO_28V = sz28V;

	return;

	//unsigned char szOnOff = 0x00;

	//if (nOnOff == 1)
	//	szOnOff = 0x01;

	//// DO 28V
	//unsigned char sz28V = sData.DO_28V;

	//switch (nChannel)
	//{
	//case 1:
	//	sz28V |= szOnOff;
	//	break;
	//case 2:
	//	sz28V |= (szOnOff << 1) & 0x02;
	//	break;
	//case 3:
	//	sz28V |= (szOnOff << 2) & 0x04;
	//	break;
	//case 4:
	//	sz28V |= (szOnOff << 3) & 0x08;
	//	break;
	//case 5:
	//	sz28V |= (szOnOff << 4) & 0x10;
	//	break;
	//case 6:
	//	sz28V |= (szOnOff << 5) & 0x20;
	//	break;
	//case 7:
	//	sz28V |= (szOnOff << 6) & 0x40;
	//	break;
	//case 8:
	//	sz28V |= (szOnOff << 7) & 0x80;
	//	break;
	//default:
	//	break;
	//}

	//sData.DO_28V = sz28V;

}

void CIOSWDataManager::Set24VDigitalOutputBit(const int nChannel, const int & nOnOff, IOSW_to_IOBOARD & sData)
{
	unsigned char szOnOff = 0x00;

	// DO 24V
	unsigned char sz24V = sData.DO_24V;

	if (nOnOff == 0) {
		sz24V &= ~(1 << (nChannel - 9));
	}
	else
	{
		sz24V |=  0x01 << (nChannel - 9);
	}

	sData.DO_24V = sz24V;

	return;
	//	szOnOff = 0x01;

	//// DO 24V
	//unsigned char sz24V = sData.DO_24V;

	//switch (nChannel)
	//{
	//case 9:
	//	sz24V |= szOnOff;
	//	break;
	//case 10:
	//	sz24V |= (szOnOff << 1) & 0x02;
	//	break;
	//case 11:
	//	sz24V |= (szOnOff << 2) & 0x04;
	//	break;
	//case 12:
	//	sz24V |= (szOnOff << 3) & 0x08;
	//	break;
	//case 13:
	//	sz24V |= (szOnOff << 4) & 0x10;
	//	break;
	//default:
	//	break;
	//}

	//sData.DO_24V = sz24V;
	

}

void CIOSWDataManager::Set5VDigitalOutputBit(const int nChannel, const int & nOnOff, IOSW_to_IOBOARD & sData)
{
	unsigned char sz5V = sData.DO_5V;

	if (nOnOff == 0) {
		sz5V &= ~(1 << (nChannel - 14));
	}
	else
	{
		sz5V |= 0x01 << (nChannel - 14);
	}

	sData.DO_5V = sz5V;

	return;
	//unsigned char szOnOff = 0x00;

	//if (nOnOff == 1)
	//	szOnOff = 0x01;

	//// DO 5V
	//unsigned char sz5V = sData.DO_5V;

	//switch (nChannel)
	//{
	//case 14:
	//	sz5V |= szOnOff;
	//	break;
	//case 15:
	//	sz5V |= (szOnOff << 1) & 0x02;
	//	break;
	//case 16:
	//	sz5V |= (szOnOff << 2) & 0x04;
	//	break;
	//default:
	//	break;
	//}

	//sData.DO_5V = sz5V;
	//
}

unsigned short CIOSWDataManager::GetAnalogInputData(const int nChannel, const IOBOARD_to_IOSW & sData)
{
	if (nChannel <= 0 || nChannel > 8)
		return 0;

	unsigned short nValue = 0;

	switch (nChannel) {
	case 1:
		nValue = sData.AI_CH_0;
		break;
	case 2:
		nValue = sData.AI_CH_1;
		break;
	case 3:
		nValue = sData.AI_CH_2;
		break;
	case 4:
		nValue = sData.AI_CH_3;
		break;
	case 5:
		nValue = sData.AI_CH_4;
		break;
	case 6:
		nValue = sData.AI_CH_5;
		break;
	case 7:
		nValue = sData.AI_CH_6;
		break;
	case 8:
		nValue = sData.AI_CH_7;
		break;
	default:
		break;
	}

	return nValue;
}

unsigned short CIOSWDataManager::GetAnalogOutputData(const int nChannel, const IOSW_to_IOBOARD & sData)
{
	if (nChannel <= 0 || nChannel > 20)
		return 0;

	unsigned short nValue = 0;

	switch (nChannel) {
	case 1:
		nValue = sData.CH0_WIDTH_28V;
		break;
	case 2:
		nValue = sData.CH1_WIDTH_28V;
		break;
	case 3:
		nValue = sData.CH2_WIDTH_28V;
		break;
	case 4:
		nValue = sData.CH3_WIDTH_28V;
		break;
	case 5:
		nValue = sData.CH4_WIDTH_28V;
		break;
	case 6:
		nValue = sData.CH5_WIDTH_28V;
		break;
	case 7:
		nValue = sData.CH6_WIDTH_28V;
		break;
	case 8:
		nValue = sData.CH7_WIDTH_28V;
		break;
	case 9:
		nValue = sData.CH8_WIDTH_28V;
		break;
	case 10:
		nValue = sData.CH9_WIDTH_28V;
		break;
	case 11:
		nValue = sData.CH10_WIDTH_28V;
		break;
	case 12:
		nValue = sData.CH11_WIDTH_28V;
		break;
	case 13:
		nValue = sData.CH12_WIDTH_28V;
		break;
	case 14:
		nValue = sData.CH0_WIDTH_24V;
		break;
	case 15:
		nValue = sData.CH1_WIDTH_24V;
		break;
	case 16:
		nValue = sData.CH2_WIDTH_24V;
		break;
	case 17:
		nValue = sData.CH3_WIDTH_24V;
		break;
	case 18:
		nValue = sData.CH4_WIDTH_24V;
		break;
	case 19:
		nValue = sData.CH0_WIDTH_5V;
		break;
	case 20:
		nValue = sData.CH1_WIDTH_5V;
		break;
	default:
		break;
	}

	return nValue;
}

void CIOSWDataManager::SetAnalogOutputData(const int nChannel, const unsigned short & usData, IOSW_to_IOBOARD & sData)
{
	if (nChannel > 0 && nChannel <= 13)		  // AO 28V
	{
		Set28VAnalogOutputData(nChannel, usData, sData);
	}
	else if (nChannel > 13 && nChannel <= 18) // AO 24V
	{
		Set24VAnalogOutputData(nChannel, usData, sData);
	}
	else if (nChannel > 18 && nChannel <= 20) // AO 5V
	{
		Set5VAnalogOutputData(nChannel, usData, sData);
	}
}

void CIOSWDataManager::Set28VAnalogOutputData(const int nChannel, const unsigned short & usData, IOSW_to_IOBOARD & sData)
{
	switch (nChannel) 
	{
	case 1:
		sData.CH0_FREQ_28V = AOFREQ_28V;
		sData.CH0_WIDTH_28V = usData;
		break;
	case 2:
		sData.CH1_FREQ_28V = AOFREQ_28V;
		sData.CH1_WIDTH_28V = usData;
		break;
	case 3:
		sData.CH2_FREQ_28V = AOFREQ_28V;
		sData.CH2_WIDTH_28V = usData;
		break;
	case 4:
		sData.CH3_FREQ_28V = AOFREQ_28V;
		sData.CH3_WIDTH_28V = usData;
		break;
	case 5:
		sData.CH4_FREQ_28V = AOFREQ_28V;
		sData.CH4_WIDTH_28V = usData;
		break;
	case 6:
		sData.CH5_FREQ_28V = AOFREQ_28V;
		sData.CH5_WIDTH_28V = usData;
		break;
	case 7:
		sData.CH6_FREQ_28V = AOFREQ_28V;
		sData.CH6_WIDTH_28V = usData;
		break;
	case 8:
		sData.CH7_FREQ_28V = AOFREQ_28V;
		sData.CH7_WIDTH_28V = usData;
		break;
	case 9:
		sData.CH8_FREQ_28V = AOFREQ_28V;
		sData.CH8_WIDTH_28V = usData;
		break;
	case 10:
		sData.CH9_FREQ_28V = AOFREQ_28V;
		sData.CH9_WIDTH_28V = usData;
		break;
	case 11:
		sData.CH10_FREQ_28V = AOFREQ_28V;
		sData.CH10_WIDTH_28V = usData;
		break;
	case 12:
		sData.CH11_FREQ_28V = AOFREQ_28V;
		sData.CH11_WIDTH_28V = usData;
		break;
	case 13:
		sData.CH12_FREQ_28V = AOFREQ_28V;
		sData.CH12_WIDTH_28V = usData;
		break;
	default:
		break;
	}
}

void CIOSWDataManager::Set24VAnalogOutputData(const int nChannel, const unsigned short & usData, IOSW_to_IOBOARD & sData)
{
	switch (nChannel)
	{
	case 14:
		sData.CH0_FREQ_24V = AOFREQ_24V;
		sData.CH0_WIDTH_24V = usData;
		break;
	case 15:
		sData.CH1_FREQ_24V = AOFREQ_24V;
		sData.CH1_WIDTH_24V = usData;
		break;
	case 16:
		sData.CH2_FREQ_24V = AOFREQ_24V;
		sData.CH2_WIDTH_24V = usData;
		break;
	case 17:
		sData.CH3_FREQ_24V = AOFREQ_24V;
		sData.CH3_WIDTH_24V = usData;
		break;
	case 18:
		sData.CH4_FREQ_24V = AOFREQ_24V;
		sData.CH4_WIDTH_24V = usData;
		break;
	default:
		break;
	}
}

void CIOSWDataManager::Set5VAnalogOutputData(const int nChannel, const unsigned short & usData, IOSW_to_IOBOARD & sData)
{
	switch (nChannel)
	{
	case 19:
		sData.CH0_FREQ_5V = AOFREQ_5V;
		sData.CH0_WIDTH_5V = usData;
		break;
	case 20:
		sData.CH1_FREQ_5V = AOFREQ_5V;
		sData.CH1_WIDTH_5V = usData;
		break;
	default:
		break;
	}
}


unsigned short CIOSWDataManager::GetDimmingData(const int nChannel, const IOSW_to_IOBOARD & sData)
{
	unsigned short nValue = 0;

	if (nChannel > 0 && nChannel <= 2)
	{
		switch (nChannel) {
		case 1:
			nValue = sData.DIMM_CH0_WIDTH;
			break;
		case 2:
			nValue = sData.DIMM_CH1_WIDTH;
			break;
		default:
			break;
		}
	}
	return nValue;
}

void CIOSWDataManager::SetDimmingData(const int nChannel, const unsigned short & usData, IOSW_to_IOBOARD & sData)
{
	if (nChannel > 0 && nChannel <= 2)
	{
		switch (nChannel) 
		{
		case 1:
			sData.DIMM_CH0_FREQ = AOFREQ_DIMMER;
			sData.DIMM_CH0_WIDTH = usData;
			break;
		case 2:
			sData.DIMM_CH1_FREQ = AOFREQ_DIMMER;
			sData.DIMM_CH1_WIDTH = usData;
			break;
		default:
			break;
		}
	}
}

unsigned short CIOSWDataManager::GetIndicatorData(const int nBoardID, const int nChannel, const IOSW_to_IOBOARD & sData)
{
	unsigned short usData = 0;

	switch (nBoardID)
	{
	case 1: //PITCH_RATIO_MOTOR
		usData = sData.PITCH_RATIO_GAUGE;
		break;
	case 10:// UTIL_MOTOR
		usData = sData.UTIL_GAUGE;
		break;
	case 15: // PC1, PC2
		if (nChannel == 1)
			usData = sData.PC1_GAUGE;
		else
			usData = sData.PC2_GAUGE;

		break;
	case 30: // OXYGEN Gauge
		usData = sData.OXYGEN_GAUGE;
		break;
	default:
		break;
	}

	return usData;
}

void CIOSWDataManager::SetIndicatorData(const int nBoardID, const int nChannel, const unsigned short & usData, IOSW_to_IOBOARD & sData)
{
	switch (nBoardID)
	{
	case 1: //PITCH_RATIO_MOTOR
		sData.PITCH_RATIO_GAUGE = usData;
		break;
	case 10:// UTIL_MOTOR
		sData.UTIL_GAUGE = usData;
		break;
	case 15: // PC1, PC2
		if (nChannel == 1)
			sData.PC1_GAUGE = usData;
		else
			sData.PC2_GAUGE = usData;

		break;
	case 30: // OXYGEN Gauge
		sData.OXYGEN_GAUGE = usData;
		break;
	default:
		break;
	}

}

float CIOSWDataManager::GetStickRudderInputData(const int nBoardID, const int nChannel, const IOBOARD_to_IOSW & sData)
{
	float fSRData = 0.0f;

	switch (nBoardID)
	{
	case 17:	// Rudder
		fSRData = sData.YAW;
		break;
	case 18:	// Stick
		if (nChannel == 1)
			fSRData = sData.AHRS_PITCH;
		else
			fSRData = sData.AHRS_ROLL;
		break;
	default:
		break;
	}

	return fSRData;
}

unsigned short CIOSWDataManager::GetCautionLightPanel(const int nChannel, const IOSW_to_IOBOARD & sData)
{
	unsigned short usData = 0;

	switch (nChannel)
	{
	case 1:
		usData = sData.CAUTION_CH0;
		break;
	case 2:
		usData = sData.CAUTION_CH1;
		break;
	case 3:
		usData = sData.CAUTION_CH2;
		break;
	case 4:
		usData = sData.CAUTION_CH3;
		break;
	case 5:
		usData = sData.CAUTION_CH4;
		break;
	case 6:
		usData = sData.CAUTION_CH5;
		break;	
	case 7:
		usData = sData.CAUTION_CH6;
		break;
	case 8:
		usData = sData.CAUTION_CH7;
		break;
	case 9:
		usData = sData.CAUTION_CH8;
		break;
	case 10:
		usData = sData.CAUTION_CH9;
		break;
	case 11:
		usData = sData.CAUTION_CH10;
		break;
	case 12:
		usData = sData.CAUTION_CH11;
		break;
	case 13:
		usData = sData.CAUTION_CH12;
		break;
	case 14:
		usData = sData.CAUTION_CH13;
		break;
	case 15:
		usData = sData.CAUTION_CH14;
		break;
	case 16:
		usData = sData.CAUTION_CH15;
		break;
	case 17:
		usData = sData.CAUTION_CH16;
		break;
	case 18:
		usData = sData.CAUTION_CH17;
		break;
	case 19:
		usData = sData.CAUTION_CH18;
		break;
	case 20:
		usData = sData.CAUTION_CH19;
		break;
	default:
		break;
	}

	return usData;
}

unsigned short CIOSWDataManager::GetGNDTestPanel(const int nChannel, const IOSW_to_IOBOARD & sData)
{
	unsigned short usData = 0;

	switch (nChannel)
	{
	case 1:
		usData = sData.CAUTION_CH0;
		break;
	case 2:
		usData = sData.CAUTION_CH1;
		break;
	case 3:
		usData = sData.CAUTION_CH2;
		break;
	case 4:
		usData = sData.CAUTION_CH3;
		break;
	case 5:
		usData = sData.CAUTION_CH4;
		break;
	case 6:
		usData = sData.CAUTION_CH5;
		break;
	case 7:
		usData = sData.CAUTION_CH6;
		break;
	case 8:
		usData = sData.CAUTION_CH7;
		break;
	case 9:
		usData = sData.CAUTION_CH8;
		break;
	case 10:
		usData = sData.CAUTION_CH9;
		break;
	case 11:
		usData = sData.CAUTION_CH10;
		break;
	case 12:
		usData = sData.CAUTION_CH11;
		break;
	case 13:
		usData = sData.CAUTION_CH12;
		break;
	case 16:
		usData = sData.CAUTION_CH13;
		break;
	case 17:
		usData = sData.CAUTION_CH14;
		break;
	case 18:
		usData = sData.CAUTION_CH15;
		break;
	case 19:
		usData = sData.CAUTION_CH16;
		break;
	case 20:
		usData = sData.CAUTION_CH17;
		break;
	case 21:
		usData = sData.CAUTION_CH18;
		break;
	case 22:
		usData = sData.CAUTION_CH19;
		break;
	default:
		break;
	}

	return usData;
}
