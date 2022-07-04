#pragma once

#include <Windows.h>
#include "IOBoard_Interface.h"
#include "IOSW_Interface.h"
#include "cockpit_enum.h"



#pragma comment(lib, "user32.lib")
#pragma comment(lib, "advapi32.lib")

bool SystemShutdown();
float	GetByte(ULARGE_INTEGER dwParam);
bool GetProcessPath(CString& strPath);
void MtoWChar(CString strTemp, char* pszData);
CString LoadConfigString(LPCTSTR lpszSection, LPCTSTR lpszName);
int		LoadConfigNumber(LPCTSTR lpszSection, LPCTSTR lpszName);


int	GetDigitalInputBit(const int nChannel, const unsigned short & nLowData, const unsigned short & nHighData);
int	GetDigitalInputBit(const int nChannel, const int & n32Data);

unsigned short GetAnalogInputData(const IOBOARD_INFORMATION & IOInfo, const int & nOldData, const IOBOARD_to_IOSW & sData);
unsigned short GetAnalogInputData(const IOBOARD_INFORMATION & IOInfo, const int & nOldData, const IOBOARD_to_IOSW & sData,
								  double dVol0, double dVol1, double dVol2, double dVol3, double dVol4, double dVol5,
								  double dVal0, double dVal1, double dVal2, double dVal3, double dVal4, double dVal5);
unsigned short GetAnalogInputData(const int nChannel, const IOBOARD_to_IOSW & sData, const int & nOldData, const unsigned short & usTolerance = 1);
unsigned short GetAnalogInputData(const IOBOARD_INFORMATION & IOInfo, const IOBOARD_to_IOSW & sData, const int & nOldData, const unsigned short & usTolerance = 60);
//void Set28VAnalogOutputData(const IOBOARD_INFORMATION & IOInfo, const ON_OFF_TYPE & eOnOff, IOSW_to_IOBOARD & sData);
//void Set28VAnalogOutputData(const IOBOARD_INFORMATION & IOInfo, const int & nLampValue, IOSW_to_IOBOARD & sData);
void		   SetAnalogOutputData(const IOBOARD_INFORMATION & IOInfo, const unsigned short & usData, IOSW_to_IOBOARD & sData);
void		   Set28VAnalogOutputData(const int nChannel, const unsigned short & usData, IOSW_to_IOBOARD & sData);
void		   Set24VAnalogOutputData(const int nChannel, const unsigned short & usData, IOSW_to_IOBOARD & sData);
void		   Set5VAnalogOutputData(const int nChannel, const unsigned short & usData, IOSW_to_IOBOARD & sData);
void		   SetDimmingData(const IOBOARD_INFORMATION & IOInfo, const int & nData, IOSW_to_IOBOARD & sData);
void		SetDigitalOutputData(const IOBOARD_INFORMATION & IOInfo, const int & nOnOff, IOSW_to_IOBOARD & sData);
void		Set28VDigitalOutputBit(const int nChannel, const int & nOnOff, IOSW_to_IOBOARD & sData);
void		Set24VDigitalOutputBit(const int nChannel, const int & nOnOff, IOSW_to_IOBOARD & sData);
void		Set5VDigitalOutputBit(const int nChannel, const int & nOnOff, IOSW_to_IOBOARD & sData);
double		Interpolation_1D_Array(const double	Input, double *A, double *B, const int	N, int *Index);
