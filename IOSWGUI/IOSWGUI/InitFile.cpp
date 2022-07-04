#include "stdafx.h"
#include "InitFile.h"


CInitFile::CInitFile()
{
}

CInitFile::CInitFile(LPCTSTR lpszFile)
{
	// 설정 파일명 설정
	m_strFileName = lpszFile;
}

CInitFile::~CInitFile()
{

}

/////////////////////////////////////////////////////////////////////////////
// Section을 읽어 Key 값의 갯수를 반환한다.
// 0 리턴이면 Key 값을 가지고 있지 않음.
/////////////////////////////////////////////////////////////////////////////
int CInitFile::ReadSection(LPCTSTR lpszSection)
{
	LPVOID pvData = NULL;
	HGLOBAL hGlobal = ::GlobalAlloc(GMEM_MOVEABLE, 16385);

	pvData = ::GlobalLock(hGlobal);
	int nCount = 0;

	if (::GetPrivateProfileString(lpszSection, NULL, NULL, (LPWSTR)pvData, 16384, m_strFileName))
	{
		char *P = (char*)pvData;

		while (*P != 0)
		{
			nCount++;
			P += ::strlen(P) + 1;
		}
	}

	::GlobalUnlock(hGlobal);
	::GlobalFree(hGlobal);

	return nCount;
}

/////////////////////////////////////////////////////////////////////////////
// Section에 해당 키값의 데이터를 반환한다.
/////////////////////////////////////////////////////////////////////////////
CString CInitFile::ReadData(LPCTSTR lpszSection, LPCTSTR lpszKey)
{
	wchar_t Buffer[2048];

	::GetPrivateProfileString(lpszSection, lpszKey, L"0", (LPWSTR)Buffer, sizeof(Buffer), m_strFileName);

	return CString(Buffer);
}

/////////////////////////////////////////////////////////////////////////////
// Section에 해당 키값에 데이터를 저장한다.
/////////////////////////////////////////////////////////////////////////////
BOOL CInitFile::WriteData(LPCTSTR lpszSection, LPCTSTR lpszKey, LPCTSTR lpszData)
{
	return ::WritePrivateProfileString(lpszSection, lpszKey, lpszData, m_strFileName);
}

/////////////////////////////////////////////////////////////////////////////
// File 명 설정
/////////////////////////////////////////////////////////////////////////////
void CInitFile::SetFile(LPCTSTR lpszFile)
{
	m_strFileName = lpszFile;
}

/////////////////////////////////////////////////////////////////////////////
// Section을 읽어 Key 값의 갯수를 반환한다.
// 0 리턴이면 Key 값을 가지고 있지 않음.
/////////////////////////////////////////////////////////////////////////////
int CInitFile::ReadSection(LPCTSTR lpszFile, LPCTSTR lpszSection)
{
	LPVOID pvData = NULL;
	HGLOBAL hGlobal = ::GlobalAlloc(GMEM_MOVEABLE, 16385);

	pvData = ::GlobalLock(hGlobal);
	int nCount = 0;

	if (::GetPrivateProfileString(lpszSection, NULL, NULL, (LPWSTR)pvData, 16384, lpszFile))
	{
		char *P = (char*)pvData;

		while (*P != 0)
		{
			nCount++;
			P += ::strlen(P) + 1;
		}
	}

	::GlobalUnlock(hGlobal);
	::GlobalFree(hGlobal);

	return nCount;
}

/////////////////////////////////////////////////////////////////////////////
// Section에 해당 키값의 데이터를 반환한다.
/////////////////////////////////////////////////////////////////////////////
CString CInitFile::ReadData(LPCTSTR lpszFile, LPCTSTR lpszSection, LPCTSTR lpszKey)
{
	wchar_t Buffer[2048];

	::GetPrivateProfileString(lpszSection, lpszKey, L"0", (LPWSTR)Buffer, sizeof(Buffer), lpszFile);

	return CString(Buffer);
}

/////////////////////////////////////////////////////////////////////////////
// Section에 해당 키값에 데이터를 저장한다.
/////////////////////////////////////////////////////////////////////////////
BOOL CInitFile::WriteData(LPCTSTR lpszFile, LPCTSTR lpszSection, LPCTSTR lpszKey, LPCTSTR lpszData)
{
	return ::WritePrivateProfileString(lpszSection, lpszKey, lpszData, lpszFile);
}



