#include "stdafx.h"
#include "ImageObject.h"
#include "IOSWUtilities.h"

CImageObject::CImageObject()
{
	m_nXPos = 0;
	m_nYPos = 0;
	m_bOver = FALSE;
}


CImageObject::~CImageObject()
{
}

void CImageObject::SetOver(BOOL bOver)
{
	m_bOver = bOver;
}

void CImageObject::SetXPosition(int nXPos)
{
	m_nXPos = nXPos;
}

void CImageObject::SetYPosition(int nYPos)
{
	m_nYPos = nYPos;
}

BOOL CImageObject::GetOver()
{
	return m_bOver;
}

int	CImageObject::GetXPosition()
{
	return m_nXPos;
}

int	CImageObject::GetYPosition()
{
	return m_nYPos;
}

int	CImageObject::GetWidth()
{
	return m_bi[0].bmWidth;
}

int	CImageObject::GetHeight()
{
	return m_bi[0].bmHeight;
}

void CImageObject::DrawObject(CDC* pDC)
{
	if (pDC->GetSafeHdc() != NULL) {

		CDC memDC;
		CBitmap* pOldBmp;
		memDC.CreateCompatibleDC(pDC);

		if (memDC.GetSafeHdc() != NULL) {
			pOldBmp = memDC.SelectObject(&m_bitmap[0]);
			pDC->BitBlt(m_nXPos, m_nYPos, m_bi[0].bmWidth, m_bi[0].bmHeight, &memDC, 0, 0, SRCCOPY);
			memDC.SelectObject(pOldBmp);
		}

		memDC.DeleteDC();
	}
}

void CImageObject::DrawObject(CDC* pDC, int nIndex)
{
	if (pDC->GetSafeHdc() != NULL) {

		CDC memDC;
		CBitmap* pOldBmp;
		memDC.CreateCompatibleDC(pDC);

		if (memDC.GetSafeHdc() != NULL) {
			pOldBmp = memDC.SelectObject(&m_bitmap[nIndex]);

			pDC->BitBlt(m_nXPos, m_nYPos, m_bi[nIndex].bmWidth, m_bi[nIndex].bmHeight, &memDC, 0, 0, SRCCOPY);
			memDC.SelectObject(pOldBmp);
		}

		memDC.DeleteDC();
	}
}

void CImageObject::DrawObject(CDC* pDC, LPCTSTR lpszText, CFont* pFont, COLORREF clrFontColor, int nIndex, UINT nFormat)
{
	if (pDC->GetSafeHdc() != NULL) {

		CDC memDC;
		CDC bgDC;

		CBitmap memBmp;
		CBitmap* pOldBmp;
		memDC.CreateCompatibleDC(pDC);

		if (memDC.GetSafeHdc() != NULL) {
		
			memBmp.CreateCompatibleBitmap(pDC, m_bi[nIndex].bmWidth, m_bi[nIndex].bmHeight);
			pOldBmp = memDC.SelectObject(&memBmp);

			bgDC.CreateCompatibleDC(&memDC);
			bgDC.SelectObject(&m_bitmap[nIndex]);

			memDC.BitBlt(0, 0, m_bi[nIndex].bmWidth, m_bi[nIndex].bmHeight, &bgDC, 0, 0, SRCCOPY);

			int nOldMode= memDC.SetBkMode(TRANSPARENT);

			CFont * pOldFont = memDC.SelectObject(pFont);
			COLORREF clrOldTextColor = memDC.SetTextColor(clrFontColor);

			memDC.DrawText(lpszText, CRect(0, 0, m_bi[nIndex].bmWidth, m_bi[nIndex].bmHeight), nFormat);
			memDC.SetTextColor(clrOldTextColor);
			memDC.SelectObject(pOldFont);
			memDC.SetBkMode(nOldMode);
			
			pDC->BitBlt(m_nXPos, m_nYPos, m_bi[nIndex].bmWidth, m_bi[nIndex].bmHeight, &memDC, 0, 0, SRCCOPY);

			memDC.SelectObject(pOldBmp);
		
		}
		memBmp.DeleteObject();

		bgDC.DeleteDC();
		memDC.DeleteDC();

	}
}
/*
void CImageObject::DrawObject(CDC* pDC, int nIndex, COLORREF clrTransColor)
{
	if (pDC->GetSafeHdc() != NULL) {

		CDC memDC;
		CBitmap* pOldBmp;
		memDC.CreateCompatibleDC(pDC);

		if (memDC.GetSafeHdc() != NULL) {
			CBitmap maskBmp;
			CIOSWUtilities::PrepareMask(&m_bitmap[nIndex], &maskBmp, RGB(255, 0, 255));
			pOldBmp = memDC.SelectObject(&m_bitmap[nIndex]);

//			pDC->BitBlt(m_nXPos, m_nYPos, m_bi[nIndex].bmWidth, m_bi[nIndex].bmHeight, &memDC, 0, 0, SRCCOPY);
			CIOSWUtilities::DrawTransparentBitmap(pDC, &maskBmp, m_nXPos, m_nYPos, m_bi[nIndex].bmWidth, m_bi[nIndex].bmHeight, &memDC);
			memDC.SelectObject(pOldBmp);
		}
	}
}*/

void CImageObject::RegisterImage(int nIndex, LPCTSTR lpszFileName)
{
	HBITMAP  hBitmap = (HBITMAP) ::LoadImage(NULL, lpszFileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	
	m_bitmap[nIndex].Attach(hBitmap);

	if (m_bitmap[nIndex].GetSafeHandle() != NULL) {
		m_bitmap[nIndex].GetObject(sizeof(BITMAP), &m_bi[nIndex]);
	}
}

BOOL CImageObject::IsPtInRect(CPoint point)
{
	CRect rect;

	rect.left = GetXPosition();
	rect.top = GetYPosition();
	rect.right = rect.left + GetWidth();
	rect.bottom = rect.top + GetHeight();

	return PtInRect(rect, point);
}