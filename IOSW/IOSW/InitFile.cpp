#include "stdafx.h"
#include "InitFile.h"


CInitFile::CInitFile()
{
}

CInitFile::CInitFile(LPCTSTR lpszFile)
{
	// ���� ���ϸ� ����
	m_strFileName = lpszFile;
}

CInitFile::~CInitFile()
{

}

/////////////////////////////////////////////////////////////////////////////
// Section�� �о� Key ���� ������ ��ȯ�Ѵ�.
// 0 �����̸� Key ���� ������ ���� ����.
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
// Section�� �ش� Ű���� �����͸� ��ȯ�Ѵ�.
/////////////////////////////////////////////////////////////////////////////
CString CInitFile::ReadData(LPCTSTR lpszSection, LPCTSTR lpszKey)
{
	wchar_t Buffer[2048];

	::GetPrivateProfileString(lpszSection, lpszKey, L"0", (LPWSTR)Buffer, sizeof(Buffer), m_strFileName);

	return CString(Buffer);
}

/////////////////////////////////////////////////////////////////////////////
// Section�� �ش� Ű���� �����͸� �����Ѵ�.
/////////////////////////////////////////////////////////////////////////////
BOOL CInitFile::WriteData(LPCTSTR lpszSection, LPCTSTR lpszKey, LPCTSTR lpszData)
{
	return ::WritePrivateProfileString(lpszSection, lpszKey, lpszData, m_strFileName);
}

/////////////////////////////////////////////////////////////////////////////
// File �� ����
/////////////////////////////////////////////////////////////////////////////
void CInitFile::SetFile(LPCTSTR lpszFile)
{
	m_strFileName = lpszFile;
}

/////////////////////////////////////////////////////////////////////////////
// Section�� �о� Key ���� ������ ��ȯ�Ѵ�.
// 0 �����̸� Key ���� ������ ���� ����.
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
// Section�� �ش� Ű���� �����͸� ��ȯ�Ѵ�.
/////////////////////////////////////////////////////////////////////////////
CString CInitFile::ReadData(LPCTSTR lpszFile, LPCTSTR lpszSection, LPCTSTR lpszKey)
{
	wchar_t Buffer[2048];

	::GetPrivateProfileString(lpszSection, lpszKey, L"0", (LPWSTR)Buffer, sizeof(Buffer), lpszFile);

	return CString(Buffer);
}

/////////////////////////////////////////////////////////////////////////////
// Section�� �ش� Ű���� �����͸� �����Ѵ�.
/////////////////////////////////////////////////////////////////////////////
BOOL CInitFile::WriteData(LPCTSTR lpszFile, LPCTSTR lpszSection, LPCTSTR lpszKey, LPCTSTR lpszData)
{
	return ::WritePrivateProfileString(lpszSection, lpszKey, lpszData, lpszFile);
}



