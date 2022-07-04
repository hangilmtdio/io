#include "stdafx.h"
#include "IOSWUtility.h"
#include "InitFile.h"

//#define AI_CALC 0.00007629
#define AI_CALC 0.000078678820613
//#define AI_CALC 0.00007

bool SystemShutdown()
{
	HANDLE hToken;
	TOKEN_PRIVILEGES tkp;

	// Get a token for this process. 
	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
		return false;

	// Get the LUID for the shutdown privilege. 
	LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid);

	tkp.PrivilegeCount = 1;  // one privilege to set    
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

	// Get the shutdown privilege for this process. 
	AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0);

	if (GetLastError() != ERROR_SUCCESS)
		return false;

	// Shut down the system and force all applications to close. 
	if (!ExitWindowsEx(EWX_SHUTDOWN | EWX_FORCE, SHTDN_REASON_MAJOR_OPERATINGSYSTEM | SHTDN_REASON_MINOR_UPGRADE | SHTDN_REASON_FLAG_PLANNED))
		return false;

	//shutdown was successful
	return true;
}

float	GetByte(ULARGE_INTEGER dwParam)
{
	return ((float)dwParam.u.HighPart * 4) + ((float)dwParam.u.LowPart / (1024 * 1024 * 1024));
}

bool GetProcessPath(CString& strPath)
{
	TCHAR	szPath[MAX_PATH];

	::memset(szPath, 0x00, MAX_PATH);

	// Current Module를 읽어 온다.
	HMODULE hModule = ::GetModuleHandle(NULL);

	if (hModule == NULL)
		return false;

	if (::GetModuleFileName(hModule, szPath, MAX_PATH) == NULL)
		return false;

	if (!PathRemoveFileSpec(szPath))
		return false;

	strPath = CString(szPath);

	return true;
}

void MtoWChar(CString strTemp, char* pszData)
{
	WideCharToMultiByte(CP_ACP, 0, strTemp, -1, pszData, strTemp.GetLength() + 1, NULL, NULL);
}


CString LoadConfigString(LPCTSTR lpszSection, LPCTSTR lpszName)
{
	CString strValue;

	if (GetProcessPath(strValue))
	{
		strValue.Append(_T("\\IOSWConfiguration.ini"));

		CInitFile iniFile;
		iniFile.SetFile(strValue);

		strValue = iniFile.ReadData(lpszSection, lpszName);
	}

	return strValue;
}

int LoadConfigNumber(LPCTSTR lpszSection, LPCTSTR lpszName)
{
	CString strValue = LoadConfigString(lpszSection, lpszName);

	int nValue = _ttoi(strValue);

	return nValue;
}

int	GetDigitalInputBit(const int nChannel, const unsigned short & nLowData, const unsigned short & nHighData)
{
	int nRet = 0;

	unsigned short nData = 0;
	int nTempChannel = 0;

	if (nChannel <= 16) {
		nData = nLowData;
		nTempChannel = nChannel;
	}		
	else {
		nData = nHighData;
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

int	GetDigitalInputBit(const int nChannel, const int & n32Data)
{
	int nRet = 0;

	unsigned short nData = 0;
	int nTempChannel = 0;

	if (nChannel <= 16) {
		nData = (unsigned short)(n32Data & 0xFFFF); 
		nTempChannel = nChannel;
	}
	else {
		nData = (unsigned short) ((n32Data & 0xFFFF0000) >> 16);
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

unsigned short GetAnalogInputData(const IOBOARD_INFORMATION & IOInfo, const int & nOldData, const IOBOARD_to_IOSW & sData)
{
	if (IOInfo.nChannel <= 0 || IOInfo.nChannel > 8)
		return 0;

	unsigned short nValue = 0;

	switch (IOInfo.nChannel) {
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

	double voltage_index[6];
	double value_index[6];

	voltage_index[0] = 0.0;
	value_index[0] = 0;

	// Make Interpolation
	int index = 0;

	int voltage_number = 6;	// 읽을 데이터 갯수

							//배열 0번째는 Init에서 초기화 함
	for (index = 1; index < voltage_number; index++)
	{
		//0.0, 1.0, 2.0, 3.0, 4.0, 5.0
		voltage_index[index] = voltage_index[index - 1] + 1;
//		voltage_index[1] = 0.6;
//		voltage_index[2] = 1.5;
//		voltage_index[3] = 2.5;
//		voltage_index[4] = 4;
//		voltage_index[5] = 5;
		//0, 200, 400, 600, 800, 1000
		value_index[index] = value_index[index - 1] + 200;
//		value_index[1] = 100;
//		value_index[2] = 250;
//		value_index[3] = 550;
//		value_index[4] = 850;
//		value_index[5] = 1000;
	}
	// 
//	double dVoltage = ((int)nValue) * AI_CALC;
//	dVoltage = dVoltage + 0.05;
//	dVoltage = (int)(dVoltage * 10);
//	dVoltage = dVoltage / 10;
	double dVoltage = (double) nValue / 10.0f;
	int nRet = 0;
	
	double dtemp = Interpolation_1D_Array(dVoltage, voltage_index, value_index, voltage_number, &nRet);
	
	int nAINewData = (int)dtemp;

	int  nTolValue = nOldData - nAINewData;
	nTolValue = (nTolValue > 0) ? nTolValue : -nTolValue;

	if (nTolValue <= 20)
		return nOldData;

	return nAINewData;
}

unsigned short GetAnalogInputData(const IOBOARD_INFORMATION & IOInfo, const int & nOldData, const IOBOARD_to_IOSW & sData,
	double dVol0, double dVol1, double dVol2, double dVol3, double dVol4, double dVol5,
	double dVal0, double dVal1, double dVal2, double dVal3, double dVal4, double dVal5)
{
	if (IOInfo.nChannel <= 0 || IOInfo.nChannel > 8)
		return 0;

	unsigned short nValue = 0;

	switch (IOInfo.nChannel) {
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

	double voltage_index[6];
	double value_index[6];

	voltage_index[0] = 0.0;
	value_index[0] = 0;

	// Make Interpolation
	int voltage_number = 6;	// 읽을 데이터 갯수

	voltage_index[0] = dVol0;
	voltage_index[1] = dVol1;
	voltage_index[2] = dVol2;
	voltage_index[3] = dVol3;
	voltage_index[4] = dVol4;
	voltage_index[5] = dVol5;

	value_index[0] = dVal0;
	value_index[1] = dVal1;
	value_index[2] = dVal2;
	value_index[3] = dVal3;
	value_index[4] = dVal4;
	value_index[5] = dVal5;

	double dVoltage = (double)nValue / 10.0f;
	int nRet = 0;

	double dtemp = Interpolation_1D_Array(dVoltage, voltage_index, value_index, voltage_number, &nRet);

	int nAINewData = (int)dtemp;

	int  nTolValue = nOldData - nAINewData;
	nTolValue = (nTolValue > 0) ? nTolValue : -nTolValue;

	if (nTolValue <= 20)
		return nOldData;

	return nAINewData;


}
unsigned short GetAnalogInputData(const int nChannel, const IOBOARD_to_IOSW & sData, const int & nOldData, const unsigned short & usTolerance)
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

	int  nTolValue = nOldData - nValue;
	nTolValue = (nTolValue > 0) ? nTolValue : -nTolValue;

	if (nTolValue < usTolerance)
		return (unsigned short) nOldData;

	return nValue;
}

unsigned short GetAnalogInputData(const IOBOARD_INFORMATION & IOInfo, const IOBOARD_to_IOSW & sData, const int & nOldData, const unsigned short & usTolerance /*= 60*/)
{
	unsigned short nValue = 0;

	if (IOInfo.nChannel <= 0 || IOInfo.nChannel > 8)
		return 0;

	switch (IOInfo.nChannel) {
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

//	nValue = (unsigned short)((1000 / 65535.0f) * nValue);
	if (nValue < IOInfo.nMin) return 0;
	if (nValue > IOInfo.nMax) return 1000;

	nValue = (unsigned short)((1000.0f / (IOInfo.nMax - IOInfo.nMin)) * (nValue - IOInfo.nMin));

	int  nTolValue = nOldData - nValue;
	nTolValue = (nTolValue > 0) ? nTolValue : -nTolValue;

	if (nTolValue < usTolerance)
		return nOldData;

	return nValue;
}

double Interpolation_1D_Array(const double	Input, double *A, double *B, const int	N, int *Index)
{
	int i = 0;

	while (Input > A[i] && i < N)
	{
		i++;
	}

	if (i == 0)
	{
		*Index = i; //jdk rev7
		return(B[i]);
	}
	else if (i == N)
	{
		*Index = i - 1; //jdk rev7
		return(B[i - 1]);
	}
	else
	{
		*Index = i; //jdk rev7
		return((B[i] - B[i - 1]) / (A[i] - A[i - 1]) * (Input - A[i]) + B[i]);
	}

}
//
//void Set28VAnalogOutputData(const IOBOARD_INFORMATION & IOInfo, const ON_OFF_TYPE & eOnOff, IOSW_to_IOBOARD & sData)
//{
//	if (IOInfo.nChannel <= 0 || IOInfo.nChannel > 13)
//		return;
//
//	unsigned short nAOData = IOInfo.nMax + 1;
//	if (eOnOff == ON) {
//		nAOData = IOInfo.nMin;
//	}
//	
//	switch (IOInfo.nChannel) {
//	case 1:
//		sData.CH0_FREQ_28V	= AOFREQ_28V;
//		sData.CH0_WIDTH_28V = nAOData;
//		break;
//	case 2:
//		sData.CH1_FREQ_28V = AOFREQ_28V;
//		sData.CH1_WIDTH_28V = nAOData;
//		break;
//	case 3:
//		sData.CH2_FREQ_28V = AOFREQ_28V;
//		sData.CH2_WIDTH_28V = nAOData;
//		break;
//	case 4:
//		sData.CH3_FREQ_28V = AOFREQ_28V;
//		sData.CH3_WIDTH_28V = nAOData;
//		break;
//	case 5:
//		sData.CH4_FREQ_28V = AOFREQ_28V;
//		sData.CH4_WIDTH_28V = nAOData;
//		break;
//	case 6:
//		sData.CH5_FREQ_28V = AOFREQ_28V;
//		sData.CH5_WIDTH_28V = nAOData;
//		break;
//	case 7:
//		sData.CH6_FREQ_28V = AOFREQ_28V;
//		sData.CH6_WIDTH_28V = nAOData;
//		break;
//	case 8:
//		sData.CH7_FREQ_28V = AOFREQ_28V;
//		sData.CH7_WIDTH_28V = nAOData;
//		break;
//	case 9:
//		sData.CH8_FREQ_28V = AOFREQ_28V;
//		sData.CH8_WIDTH_28V = nAOData;
//		break;	
//	case 10:
//		sData.CH9_FREQ_28V = AOFREQ_28V;
//		sData.CH9_WIDTH_28V = nAOData;
//		break;
//	case 11:
//		sData.CH10_FREQ_28V = AOFREQ_28V;
//		sData.CH10_WIDTH_28V = nAOData;
//		break;
//	case 12:
//		sData.CH11_FREQ_28V = AOFREQ_28V;
//		sData.CH11_WIDTH_28V = nAOData;
//		break;
//	case 13:
//		sData.CH12_FREQ_28V = AOFREQ_28V;
//		sData.CH12_WIDTH_28V = nAOData;
//		break;
//	default:
//		break;
//	}
//}
//
//void Set28VAnalogOutputData(const IOBOARD_INFORMATION & IOInfo, const int & nLampValue, IOSW_to_IOBOARD & sData)
//{
//	if (IOInfo.nChannel <= 0 || IOInfo.nChannel > 13)
//		return;
//
//	unsigned short nAOData = (unsigned short) ((IOInfo.nMax - IOInfo.nMin)/1000.0f) * nLampValue ;
//
//	if (nAOData < IOInfo.nMin){
//		nAOData = IOInfo.nMin;
//	}else if (nAOData > IOInfo.nMax)
//		nAOData = IOInfo.nMax;
//
//	switch (IOInfo.nChannel) {
//	case 1:
//		sData.CH0_FREQ_28V = AOFREQ_28V;
//		sData.CH0_WIDTH_28V = nAOData;
//		break;
//	case 2:
//		sData.CH1_FREQ_28V = AOFREQ_28V;
//		sData.CH1_WIDTH_28V = nAOData;
//		break;
//	case 3:
//		sData.CH2_FREQ_28V = AOFREQ_28V;
//		sData.CH2_WIDTH_28V = nAOData;
//		break;
//	case 4:
//		sData.CH3_FREQ_28V = AOFREQ_28V;
//		sData.CH3_WIDTH_28V = nAOData;
//		break;
//	case 5:
//		sData.CH4_FREQ_28V = AOFREQ_28V;
//		sData.CH4_WIDTH_28V = nAOData;
//		break;
//	case 6:
//		sData.CH5_FREQ_28V = AOFREQ_28V;
//		sData.CH5_WIDTH_28V = nAOData;
//		break;
//	case 7:
//		sData.CH6_FREQ_28V = AOFREQ_28V;
//		sData.CH6_WIDTH_28V = nAOData;
//		break;
//	case 8:
//		sData.CH7_FREQ_28V = AOFREQ_28V;
//		sData.CH7_WIDTH_28V = nAOData;
//		break;
//	case 9:
//		sData.CH8_FREQ_28V = AOFREQ_28V;
//		sData.CH8_WIDTH_28V = nAOData;
//		break;
//	case 10:
//		sData.CH9_FREQ_28V = AOFREQ_28V;
//		sData.CH9_WIDTH_28V = nAOData;
//		break;
//	case 11:
//		sData.CH10_FREQ_28V = AOFREQ_28V;
//		sData.CH10_WIDTH_28V = nAOData;
//		break;
//	case 12:
//		sData.CH11_FREQ_28V = AOFREQ_28V;
//		sData.CH11_WIDTH_28V = nAOData;
//		break;
//	case 13:
//		sData.CH12_FREQ_28V = AOFREQ_28V;
//		sData.CH12_WIDTH_28V = nAOData;
//		break;
//	default:
//		break;
//	}
//}

void SetAnalogOutputData(const IOBOARD_INFORMATION & IOInfo, const unsigned short & usData, IOSW_to_IOBOARD & sData)
{
	unsigned short nAOData =(unsigned short)(((IOInfo.nMax - IOInfo.nMin) / 1000.0f) * usData);

	if (nAOData < IOInfo.nMin) {
		nAOData = IOInfo.nMin;
	}
	else if (nAOData > IOInfo.nMax)
		nAOData = IOInfo.nMax;

	int nChannel = IOInfo.nChannel;

	if (nChannel > 0 && nChannel <= 13)		  // AO 28V
	{
		Set28VAnalogOutputData(nChannel, nAOData, sData);
	}
	else if (nChannel > 13 && nChannel <= 18) // AO 24V
	{
		Set24VAnalogOutputData(nChannel, nAOData, sData);
	}
	else if (nChannel > 18 && nChannel <= 20) // AO 5V
	{
		Set5VAnalogOutputData(nChannel, nAOData, sData);
	}
}

void Set28VAnalogOutputData(const int nChannel, const unsigned short & usData, IOSW_to_IOBOARD & sData)
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

void Set24VAnalogOutputData(const int nChannel, const unsigned short & usData, IOSW_to_IOBOARD & sData)
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

void Set5VAnalogOutputData(const int nChannel, const unsigned short & usData, IOSW_to_IOBOARD & sData)
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

void SetDimmingData(const IOBOARD_INFORMATION & IOInfo, const int & nData, IOSW_to_IOBOARD & sData)
{
	int nChannel = IOInfo.nChannel;
	unsigned short usData = (unsigned short)(((IOInfo.nMax - IOInfo.nMin) / 1000.0f) * nData);

	if (usData < IOInfo.nMin) {
		usData = IOInfo.nMin;
	}
	else if (usData > IOInfo.nMax)
		usData = IOInfo.nMax;

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

void SetDigitalOutputData(const IOBOARD_INFORMATION & IOInfo, const int & nOnOff, IOSW_to_IOBOARD & sData)
{
	int nChannel = IOInfo.nChannel;

	if (nChannel > 0 && nChannel <= 8)		 // DO 28V
	{
		Set28VDigitalOutputBit(nChannel, nOnOff, sData);
	}
	else if (nChannel > 8 && nChannel <= 13) // DO 24V
	{
		Set24VDigitalOutputBit(nChannel, nOnOff, sData);
	}
	else if (nChannel > 13 && nChannel <= 16) // DO 5V
	{
		Set5VDigitalOutputBit(nChannel, nOnOff, sData);
	}
}

void Set28VDigitalOutputBit(const int nChannel, const int & nOnOff, IOSW_to_IOBOARD & sData)
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


}

void Set24VDigitalOutputBit(const int nChannel, const int & nOnOff, IOSW_to_IOBOARD & sData)
{
	unsigned char szOnOff = 0x00;

	// DO 24V
	unsigned char sz24V = sData.DO_24V;

	if (nOnOff == 0) {
		sz24V &= ~(1 << (nChannel - 9));
	}
	else
	{
		sz24V |= 0x01 << (nChannel - 9);
	}

	sData.DO_24V = sz24V;

}

void Set5VDigitalOutputBit(const int nChannel, const int & nOnOff, IOSW_to_IOBOARD & sData)
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

}