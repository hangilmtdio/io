#pragma once

#include <list>
#include "IOSW_Interface.h"


typedef struct sIOInformation
{
	sIOInformation()
	{
		nIndex		= 0;
		eKind		= IK_UNKNOWN;
		nChannel	= 0;
		nMin		= 0;
		nMax		= 0;
		memset(szIOName, 0x00, 100);
		szValue		= 0;
		usValue		= 0;
		fValue		= 0.0f;
		nValue		= 0;
	}

	sIOInformation(const sIOInformation& sInfo)
	{
		nIndex		= sInfo.nIndex;
		eKind		= sInfo.eKind;
		nChannel	= sInfo.nChannel;
		nMin		= sInfo.nMin;
		nMax		= sInfo.nMax;
		memcpy(szIOName, sInfo.szIOName, 100);
		szValue		= sInfo.szValue;
		usValue		= sInfo.usValue;	
		fValue		= sInfo.fValue;
		nValue		= sInfo.nValue;
	}

	const sIOInformation& operator=(const sIOInformation& rhs) 
	{ 
		nIndex = rhs.nIndex, eKind = rhs.eKind, nChannel = rhs.nChannel, nMin = rhs.nMin, nMax = rhs.nMax, 
		memcpy(szIOName, rhs.szIOName, 100),
		szValue = rhs.szValue, usValue = rhs.usValue, fValue = rhs.fValue, nValue = rhs.nValue; 
		return *this; 
	}

	~sIOInformation() {}

	int				nIndex;
	IO_KIND			eKind;                             
	int				nChannel;
	int				nMin;
	int				nMax;
	char			szIOName[100];
	unsigned char	szValue;
	unsigned short	usValue;
	float			fValue;
	int				nValue;
} sIOInformation;

typedef std::list<sIOInformation*>         LIST_IOINFO;
typedef LIST_IOINFO::iterator		       LIST_IOINFO_ITR;

typedef std::list<int>					   LIST_ID;
typedef LIST_ID::iterator				   LIST_ID_ITR;

class CIODeviceInfo
{
public:
	CIODeviceInfo();
	~CIODeviceInfo();

	bool InsertIOInfo(const sIOInformation& sInfo);
	void ClearAllIOInfo();
	void SetDeviceID(int nDeviceID) { m_nDeviceID = nDeviceID; }
	int	 GetDeviceID() { return m_nDeviceID; }
	void SetBoardID(int nBoardID) { m_nBoardID = nBoardID; }
	int	 GetBoardID() { return m_nBoardID; }
	void SetDevicePosition(DEVICE_POSITION eDevicePos) { m_eDevicePos = eDevicePos; }
	DEVICE_POSITION GetDevicePosition() { return m_eDevicePos; }
	void SetDeviceName(CString strDeviceName);
	void GetDeviceName(CString& strDeviceName);
	sIOInformation* GetIOInfo(const int& nIndex);
	void GetIOIndexList(LIST_ID* pIDList);
	void GetIOIndexList(LIST_ID* pIDList, IO_KIND eKind);
	void SetDeviceImageXPosition(int nXPos) { m_nImageXPos = nXPos; }
	void SetDeviceImageYPosition(int nYPos) { m_nImageYPos = nYPos; }
	int GetDeviceImageXPosition() { return m_nImageXPos; }
	int GetDeviceImageYPosition() { return m_nImageYPos; }
	LIST_IOINFO* GetIOInfoList() { return m_pIOInfoList; }

private:
	LIST_IOINFO*	m_pIOInfoList;
	int				m_nDeviceID;
	char			m_szDeviceName[100];
	int				m_nBoardID;
	int				m_nImageXPos;
	int				m_nImageYPos;
	DEVICE_POSITION m_eDevicePos;
};

typedef std::list<CIODeviceInfo*>				 LIST_DEVICEINFO;
typedef LIST_DEVICEINFO::iterator		       LIST_DEVICEINFO_ITR;

class CIODeviceInformationManager
{
public:
	CIODeviceInformationManager();
	~CIODeviceInformationManager();

	bool LoadDeviceInfo();
	bool LoadDeviceImageInfo();
	void ClearAllIODeviceInfo();
	CIODeviceInfo* GetDeivceInfo(const int& nDeviceID);
	void GetDeviceIDList(LIST_ID* pIDList);
	void GetDeviceIDList(LIST_ID* pIDList, DEVICE_POSITION ePosition);
	LIST_DEVICEINFO* GetDeviceInforList() { return m_pDeviceInfoList; }

private:
	LIST_DEVICEINFO*		m_pDeviceInfoList;

};

