#pragma once

#include <string>
#include "IOBoard_Interface.h"

using namespace std;

class CIOSWUtilities
{
public:
	CIOSWUtilities();
	~CIOSWUtilities();

	// Operations
	static void PrepareMask(CBitmap* pBmpSource, CBitmap* pBmpMask, COLORREF clrTransColor);
	static void DrawTransparentBitmap(CDC* pDC, CBitmap* pBmpMask, int nXStart, int nYStart, int nWidth, int nHeight, CDC* pTmpDC, int nXSource = 0, int nYSource = 0);
	static bool GetProcessPath(CString& strPath);
	static CString GetImagePathFile(LPCTSTR szFileName);
	static void MtoWChar(CString strTemp, char* pszData);
	static CString LoadConfigString(LPCTSTR lpszSection, LPCTSTR lpszName);
	static int LoadConfigNumber(LPCTSTR lpszSection, LPCTSTR lpszName);
	static CString LoadIOConfigString(LPCTSTR lpszSection, LPCTSTR lpszName);
	static int LoadIOConfigNumber(LPCTSTR lpszSection, LPCTSTR lpszName);
	static bool SaveIOConfigString(LPCTSTR lpszSection, LPCTSTR lpszName, LPCTSTR lpszValue);
	static bool SaveIOConfigNumber(LPCTSTR lpszSection, LPCTSTR lpszName, int nValue);
	static string GetCurrentDateString();
	static string GetCurrentTimeString();

};

