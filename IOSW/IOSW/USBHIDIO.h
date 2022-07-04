#pragma once

#include <sys/timeb.h>
#include <setupapi.h>
#include <hidsdi.h>

#pragma comment(lib, "SetupAPI.lib")
#pragma comment(lib, "Hid.lib")

#define HID_MAXHIDDEVICES	16
#define HID_MAXDEVICEPATH	255 

class CUSBHIDIO
{
public:
	CUSBHIDIO();
	~CUSBHIDIO();

	// HID
	GUID						m_HidGuid;
	USHORT						m_usDeviceDetected;
	USHORT						m_usDetailDataFlagDone;


public:
	void CloseHandles();
	DWORD GetHIDCollectionDevices(USHORT &NumHIDDevices, PSP_DEVICE_INTERFACE_DETAIL_DATA aDetailData[HID_MAXHIDDEVICES], PHIDD_ATTRIBUTES aAttributes, HIDP_CAPS aNumValueCaps[HID_MAXHIDDEVICES]);
	DWORD GetHIDValueCaps(PSP_DEVICE_INTERFACE_DETAIL_DATA aDetailData, HIDP_REPORT_TYPE ReportType, PHIDP_VALUE_CAPS ValueCaps, USHORT &ValueCapsLength, HANDLE DeviceHandle = NULL);
	DWORD GetHIDButtonCaps(PSP_DEVICE_INTERFACE_DETAIL_DATA aDetailData, HIDP_REPORT_TYPE ReportType, PHIDP_BUTTON_CAPS ButtonCaps, USHORT &ButtonCapsLength, HANDLE DeviceHandle = NULL);
	DWORD GetHIDUsagesValues(PSP_DEVICE_INTERFACE_DETAIL_DATA aDetailData, HIDP_REPORT_TYPE ReportType, PHIDP_VALUE_CAPS ValueCaps, USHORT ValueCapsLength, PULONG UsageValue, DWORD WaitForMsc, __timeb64* pAdquiredAt, HANDLE ReadHandle = NULL);
	DWORD GetHIDButtonState(PSP_DEVICE_INTERFACE_DETAIL_DATA aDetailData, HIDP_REPORT_TYPE ReportType, USAGE UsagePage, PUSAGE UsageList, PULONG UsageLength, DWORD WaitForMsc, __timeb64* AdquiredAt, HANDLE ReadHandle = NULL);
	DWORD SetHIDLEDState(PSP_DEVICE_INTERFACE_DETAIL_DATA aDetailData, HIDP_REPORT_TYPE ReportType, USAGE UsagePage, PUSAGE UsageList, PULONG UsageLength, HANDLE WriteHandle = NULL);
	DWORD SendHIDReport(PSP_DEVICE_INTERFACE_DETAIL_DATA aDetailData, PCHAR pReport, HANDLE tmpWriteHandle = NULL);
};

