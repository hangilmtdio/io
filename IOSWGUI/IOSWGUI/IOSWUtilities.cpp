#include "stdafx.h"
#include "IOSWUtilities.h"
#include "InitFile.h"

CIOSWUtilities::CIOSWUtilities()
{
}


CIOSWUtilities::~CIOSWUtilities()
{
}

void CIOSWUtilities::PrepareMask(CBitmap* pBmpSource, CBitmap* pBmpMask, COLORREF clrTransColor)
{
	BITMAP bm;

	pBmpSource->GetObject(sizeof(BITMAP), &bm);

	pBmpMask->DeleteObject();
	pBmpMask->CreateBitmap(bm.bmWidth, bm.bmHeight, 1, 1, NULL);

	CDC hdcSrc, hdcDst;

	hdcSrc.CreateCompatibleDC(NULL);
	hdcDst.CreateCompatibleDC(NULL);

	CBitmap* hbmSrcT = (CBitmap*)hdcSrc.SelectObject(pBmpSource);
	CBitmap* hbmDstT = (CBitmap*)hdcDst.SelectObject(pBmpMask);

	COLORREF clrTrans;
	clrTrans = clrTransColor;

	COLORREF clrSaveBk = hdcSrc.SetBkColor(clrTrans);

	hdcDst.BitBlt(0, 0, bm.bmWidth, bm.bmHeight, &hdcSrc, 0, 0, SRCCOPY);

	COLORREF clrSaveDstText = hdcSrc.SetTextColor(RGB(255, 255, 255));
	hdcSrc.SetBkColor(RGB(255, 0, 255));

	hdcSrc.BitBlt(0, 0, bm.bmWidth, bm.bmHeight, &hdcDst, 0, 0, SRCAND);

	hdcDst.SetTextColor(clrSaveDstText);

	hdcSrc.SetBkColor(clrSaveBk);
	hdcSrc.SelectObject(hbmSrcT);
	hdcDst.SelectObject(hbmDstT);

	hdcSrc.DeleteDC();
	hdcDst.DeleteDC();
}

void CIOSWUtilities::DrawTransparentBitmap(CDC* pDC, CBitmap* pBmpMask, int nXStart, int nYStart, int nWidth, int nHeight, CDC* pTmpDC, int nXSource, int nYSource)
{
	CDC hdcMem;
	hdcMem.CreateCompatibleDC(NULL);

	CBitmap* hbmT = hdcMem.SelectObject(pBmpMask);

	pDC->BitBlt(nXStart, nYStart, nWidth, nHeight, &hdcMem, nXSource, nYSource, SRCAND);
	pDC->BitBlt(nXStart, nYStart, nWidth, nHeight, pTmpDC, nXSource, nYSource, SRCPAINT);

	hdcMem.SelectObject(hbmT);
	hdcMem.DeleteDC();
}


bool CIOSWUtilities::GetProcessPath(CString& strPath)
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

CString CIOSWUtilities::GetImagePathFile(LPCTSTR szFileName)
{
	CString strPath;
	CString strTemp;
	
	GetProcessPath(strPath);
	strTemp.Format(_T("%s\\Images\\%s"), strPath, szFileName);
	
	return strTemp;
}

void CIOSWUtilities::MtoWChar(CString strTemp, char* pszData)
{
	WideCharToMultiByte(CP_ACP, 0, strTemp, -1, pszData, strTemp.GetLength() + 1, NULL, NULL);
}

CString CIOSWUtilities::LoadConfigString(LPCTSTR lpszSection, LPCTSTR lpszName)
{
	CString strValue;

	if (GetProcessPath(strValue))
	{
		strValue.Append(_T("\\GUIConfiguration.ini"));

		CInitFile iniFile;
		iniFile.SetFile(strValue);

		strValue = iniFile.ReadData(lpszSection, lpszName);
	}

	return strValue;
}

int CIOSWUtilities::LoadConfigNumber(LPCTSTR lpszSection, LPCTSTR lpszName)
{
	CString strValue = LoadConfigString(lpszSection, lpszName);

	int nValue = _ttoi(strValue);

	return nValue;
}

CString CIOSWUtilities::LoadIOConfigString(LPCTSTR lpszSection, LPCTSTR lpszName)
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

int CIOSWUtilities::LoadIOConfigNumber(LPCTSTR lpszSection, LPCTSTR lpszName)
{
	CString strValue = LoadIOConfigString(lpszSection, lpszName);

	int nValue = _ttoi(strValue);

	return nValue;
}

bool CIOSWUtilities::SaveIOConfigString(LPCTSTR lpszSection, LPCTSTR lpszName, LPCTSTR lpszValue)
{
	CString strValue;
	bool bResult = false;

	if (GetProcessPath(strValue))
	{
		strValue.Append(_T("\\IOSWConfiguration.ini"));

		CInitFile iniFile;
		iniFile.SetFile(strValue);

		bResult = iniFile.WriteData(lpszSection, lpszName, lpszValue);
	}

	return bResult;
}

bool CIOSWUtilities::SaveIOConfigNumber(LPCTSTR lpszSection, LPCTSTR lpszName, int nValue)
{
	CString strValue;
	strValue.Format(_T("%d"), nValue);

	return SaveIOConfigString(lpszSection, lpszName, strValue);
}


string CIOSWUtilities::GetCurrentDateString() {
	time_t now = time(NULL);
	struct tm tstruct;
	char buf[40];
	tstruct = *localtime(&now);
	//format: day YYYY-MM-DD
	strftime(buf, sizeof(buf), "%Y_%m_%d", &tstruct);
	return buf;
}

string CIOSWUtilities::GetCurrentTimeString() {
	time_t now = time(NULL);
	struct tm tstruct;
	char buf[40];
	tstruct = *localtime(&now);
	//format: HH:mm:ss
	strftime(buf, sizeof(buf), "%X", &tstruct);
	return buf;
}