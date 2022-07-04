#include "stdafx.h"
#include "ThrottleInterface.h"


CThrottleInterface::CThrottleInterface()
{
	m_pDataManager = NULL;
	m_pHIDConn = NULL;
	m_bInitialize = false;
	m_sThrottleDevPath = (PSP_DEVICE_INTERFACE_DETAIL_DATA)malloc(HID_MAXDEVICEPATH);
	m_sThrottleDevPath->cbSize = 0;
	m_eNetworkStatus = NS_DISCONNECTED;
	m_nBoardID = -1;

	for (int i = 0; i < MAX_IOBOARD_IO; i++) {
		ZeroMemory(&m_stIOInformation[i], sizeof(IOBOARD_INFORMATION));
	}
}

CThrottleInterface::~CThrottleInterface()
{
	if (m_pHIDConn != NULL) {
		delete m_pHIDConn;
		m_pHIDConn = NULL;
	}

//	if (m_sThrottleDevPath->cbSize > 0 && m_sThrottleDevPath->cbSize <255) 
	free(m_sThrottleDevPath);
}


bool CThrottleInterface::Initialize()
{
	m_pHIDConn = new CUSBHIDIO();

	if (m_pHIDConn == NULL)
		return false;

	bool bFind = false;
	LONG nResult = 0;
	USHORT								usNumHIDDevices;
	PSP_DEVICE_INTERFACE_DETAIL_DATA	arDetailData[HID_MAXHIDDEVICES];
	HIDD_ATTRIBUTES						arAttributes[HID_MAXHIDDEVICES];
	HIDP_CAPS							arValueCaps[HID_MAXHIDDEVICES];
	
	nResult = m_pHIDConn->GetHIDCollectionDevices(usNumHIDDevices, arDetailData, arAttributes, arValueCaps);
	
	for (int i = 0; i < usNumHIDDevices; i++) {

		if (arAttributes[i].VendorID == HID_VENDER && arAttributes[i].ProductID == HID_PRODUCT)
		{
			TRACE(_T("V ID = %x, P ID = %x\n"), arAttributes[i].VendorID, arAttributes[i].ProductID);
			// first byte is path length.
			int nPathLength = arDetailData[i]->DevicePath[0]; 
			
			m_sThrottleDevPath->cbSize = arDetailData[i]->cbSize;
			::memcpy(m_sThrottleDevPath->DevicePath, arDetailData[i]->DevicePath, nPathLength*2);
			m_sThrottleDevAttrib = arAttributes[i];
			m_sThrottleDevCaps = arValueCaps[i];

			bFind = true;
			break;
		}
	}
			
	for(int i = 0 ; i < usNumHIDDevices; i++)
		free(arDetailData[i]);

	m_bInitialize = bFind;

	return bFind;
}

void CThrottleInterface::SetDataManager(CIOSWDataManager* pManager)
{
	if (pManager != NULL) {
		m_pDataManager = pManager;
	}
}

bool CThrottleInterface::StartInterface()
{
	if (IsInitialize()) {
		StartThread();

		return true;
	}

	return false;
}

bool CThrottleInterface::StopInterface()
{
	if (IsInitialize()) {
		EndThread();

		return true;
	}

	return false;

}

void CThrottleInterface::UpdateNetworkStatus(bool bConnected)
{
	if (m_pDataManager != NULL) {
		IOSW_to_IOSWGUI stIOSW2GUI;
		m_pDataManager->GetIOSW2GUIData(&stIOSW2GUI);

		NETWORKSTATUS_TYPE eNetworkStatus = NS_ERROR;

		if (bConnected)
			eNetworkStatus = NS_CONNECTED;
	
		int nBID = GetBoardID();

		stIOSW2GUI.eIONetworkStatus[nBID] = eNetworkStatus;

		m_pDataManager->SetIOSW2GUIData(stIOSW2GUI);
	}
}

bool CThrottleInterface::UpdateValuesState(THROTTLE_IO* psInfo)
{
	LONG				lResult;

	PHIDP_VALUE_CAPS	mValueCaps = NULL;
	USHORT              numValues = 0;
	PULONG				aUsageValue = 0;
	DWORD				WaitForMsc = 100;
	__timeb64			AdquiredAt;
	bool bResult = false;

	if (m_sThrottleDevCaps.NumberInputValueCaps > 0) {

		mValueCaps = (PHIDP_VALUE_CAPS)calloc(m_sThrottleDevCaps.NumberInputValueCaps, sizeof(HIDP_VALUE_CAPS));

		lResult = m_pHIDConn->GetHIDValueCaps(m_sThrottleDevPath, HidP_Input, mValueCaps, numValues, NULL);
		aUsageValue = (PULONG)calloc(numValues, sizeof(ULONG));
		lResult = m_pHIDConn->GetHIDUsagesValues(m_sThrottleDevPath, HidP_Input, mValueCaps, numValues, aUsageValue, WaitForMsc, &AdquiredAt, NULL);

		if (lResult == HIDP_STATUS_SUCCESS) 
		{
			for (int i = 0; i < m_sThrottleDevCaps.NumberInputValueCaps; i++)
			{
				switch (mValueCaps[i].NotRange.Usage)
				{
				case 0x39:
					psInfo->usHATSwitch = (unsigned short)aUsageValue[i];
					break;
				case 0x36:
					psInfo->usSlider = (unsigned short)aUsageValue[i];
					break;
				case 0x37:
					psInfo->usDial = (unsigned short)aUsageValue[i];
					break;
				case 0x35:
					psInfo->usRotationalZ = (unsigned short)aUsageValue[i];
					break;
				case 0x34:
					psInfo->usRotationalY = (unsigned short)aUsageValue[i];
					break;
				case 0x33:
					psInfo->usRotationalX = (unsigned short)aUsageValue[i];
					break;
				case 0x32:
					psInfo->usZ = (unsigned short)aUsageValue[i];
					break;
				case 0x31:
					psInfo->usY = (unsigned short)aUsageValue[i];
					break;
				case 0x30:
					psInfo->usX = (unsigned short)aUsageValue[i];
					break;
				default:
					break;
				}
			}
			
			bResult = true;
		}

	}

	free(aUsageValue);
	free(mValueCaps);

	return bResult;
}

bool CThrottleInterface::UpdateButtonState(THROTTLE_IO* psInfo)
{
	LONG				lResult;

	PHIDP_BUTTON_CAPS	mButtonCaps = NULL;
	USHORT              numCapsLength = 0;
	USHORT				numButtons = 0;
	PUSAGE				UsageList = 0;
	PULONG				aUsageLength = 0;
	DWORD				WaitForMsc = 10000;
	__timeb64			AdquiredAt;

	if (m_sThrottleDevCaps.NumberInputValueCaps > 0) {

		mButtonCaps = (PHIDP_BUTTON_CAPS)calloc(m_sThrottleDevCaps.NumberInputButtonCaps, sizeof(HIDP_BUTTON_CAPS));

		lResult = m_pHIDConn->GetHIDButtonCaps(m_sThrottleDevPath, HidP_Input, mButtonCaps, numCapsLength, NULL);

		aUsageLength = (PULONG)calloc(m_sThrottleDevCaps.NumberInputButtonCaps, sizeof(ULONG));

		if (mButtonCaps->IsRange){
			numButtons = mButtonCaps->Range.UsageMax - mButtonCaps->Range.UsageMin + 1;
		}
		else{
			numButtons = 1;
		}

		UsageList = (PUSAGE)calloc(numButtons, sizeof(USAGE));

		lResult = m_pHIDConn->GetHIDButtonState(m_sThrottleDevPath, HidP_Input, mButtonCaps->UsagePage, UsageList, aUsageLength, WaitForMsc, &AdquiredAt, NULL);

		if (lResult == HIDP_STATUS_SUCCESS)
		{
			int tmpLegnth = aUsageLength[0];

			unsigned short usBtnLow  = 0x00;
			unsigned short usBtnHigh = 0x00;

			for (int i = 0; i < tmpLegnth; i++)
			{
				unsigned short usValue = (unsigned short) UsageList[i];
				//TRACE(_T("Throttle Button %u \n"), usValue);
				if (usValue >= 0x11) {
					SetDIState(usBtnHigh, (usValue - 0x10));
				}
				else{
					SetDIState(usBtnLow, usValue);
				}
				
			}
			
			psInfo->usDILow = usBtnLow;
			psInfo->usDIHigh = usBtnHigh;
		}
	}

	free(UsageList);
	free(aUsageLength);
	free(mButtonCaps);

	return true;
}

void  CThrottleInterface::SetDIState(unsigned short & usData, const unsigned short & usChannel)
{
	switch (usChannel)
	{
	case 1:
		usData |= 0x01;
		break;
	case 2:
		usData |= (0x01 << 1) & 0x02;
		break;
	case 3:
		usData |= (0x01 << 2) & 0x04;
		break;
	case 4:
		usData |= (0x01 << 3) & 0x08;
		break;
	case 5:
		usData |= (0x01 << 4) & 0x10;
		break;
	case 6:
		usData |= (0x01 << 5) & 0x20;
		break;
	case 7:
		usData |= (0x01 << 6) & 0x40;
		break;
	case 8:
		usData |= (0x01 << 7) & 0x80;
		break;
	case 9:
		usData |= (0x01 << 8) & 0x100;
		break;
	case 10:
		usData |= (0x01 << 9) & 0x200;
		break;
	case 11:
		usData |= (0x01 << 10) & 0x400;
		break;
	case 12:
		usData |= (0x01 << 11) & 0x800;
		break;
	case 13:
		usData |= (0x01 << 12) & 0x1000;
		break;
	case 14:
		usData |= (0x01 << 13) & 0x2000;
		break;
	case 15:
		usData |= (0x01 << 14) & 0x4000;
		break;
	case 16:
		usData |= (0x01 << 15) & 0x8000;
		break;
	default:
		break;
	}

}

bool CThrottleInterface::UpdateIOBoardState(const THROTTLE_IO & sInfo, IOBOARD_to_IOSW * psInfo)
{
	// Digital Input
	psInfo->DI_CH_LOW = sInfo.usDILow;
	psInfo->DI_CH_HIGH = sInfo.usDIHigh;

	// Analog Input
	psInfo->AI_CH_0 = ConvertAIData(m_stIOInformation[0], sInfo.usX); // Azimuth (max : 3700, min : 52, default : 2044)
	psInfo->AI_CH_1 = ConvertAIData(m_stIOInformation[1], sInfo.usY); // Range (max : 3500, min : 300, default : 2055)
	psInfo->AI_CH_2 = ConvertAIData(m_stIOInformation[2], sInfo.usZ); // Right Pos (max : 2615, min : 320)
	psInfo->AI_CH_3 = ConvertAIData(m_stIOInformation[3], sInfo.usRotationalX); // Left Pos (max : 2667, min : 685)
	psInfo->AI_CH_4 = ConvertAIData(m_stIOInformation[4], sInfo.usRotationalY); // Atenna (max : 3970, min : 0, defualt : 1453)
	psInfo->AI_CH_5 = sInfo.usRotationalZ;
	psInfo->AI_CH_6 = sInfo.usSlider;
	psInfo->AI_CH_7 = sInfo.usDial;


	return true;
}

unsigned short CThrottleInterface::ConvertAIData(const IOBOARD_INFORMATION& stInfo, const unsigned short & usData)
{
	unsigned short usValue = 0;

	if (usData <= stInfo.nMin)
		usValue = 0;
	else if (usData >= stInfo.nMax)
		usValue = 1000;
	else 
	{

		//usValue = (unsigned short)((1000 / (stInfo.nMax - stInfo.nMin)) * (usData));
		usValue = (unsigned short)((usData - stInfo.nMin) * 1000 / (stInfo.nMax - stInfo.nMin));
	}

	return usValue;
}

bool CThrottleInterface::SetBoardInformation(const int& nIndex, const IOBOARD_INFORMATION& stInfo)
{
	if (nIndex >= MAX_IOBOARD_IO)
		return false;

	memcpy(&m_stIOInformation[nIndex], &stInfo, sizeof(IOBOARD_INFORMATION));

	return true;
}

DWORD CThrottleInterface::ThreadProc()
{
	bool bResult = 1;

	DWORD nOld = GetTickCount();

	while (1)
	{
		DWORD nNew = GetTickCount();

		if (nNew - nOld >= 50) {	// 20Hz

			if (m_pHIDConn != NULL)
			{
				IOBOARD_to_IOSW stRecvData;
				THROTTLE_IO sIOInfo;

				memset(&stRecvData, 0x00, sizeof(IOBOARD_to_IOSW));
				memset(&sIOInfo, 0x00, sizeof(THROTTLE_IO));

				// AI Signal Update
				bResult = UpdateValuesState(&sIOInfo);

				// DI Signal Update
				UpdateButtonState(&sIOInfo);

				// IOBOARD data converting
				UpdateIOBoardState(sIOInfo, &stRecvData);
				stRecvData.Board_No = m_nBoardID;

				if (bResult == true)
				{
					m_pDataManager->SetIOBoard2IOSWData(stRecvData, m_nBoardID);
					m_pDataManager->DecodeIOBoardData(m_nBoardID, m_stIOInformation);
				}

				UpdateNetworkStatus((bool) m_pHIDConn->m_usDeviceDetected);
			}

			nOld = GetTickCount();
		}

		Sleep(1);

		if (m_bEndThread == TRUE) break;   // Thread 종료 조건
	}

	return bResult;
}