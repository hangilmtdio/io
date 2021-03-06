/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// HeaderCtrlEx.cpp : implementation file
//

#include "stdafx.h"
#include "HeaderCtrlEx.h"

IMPLEMENT_DYNAMIC(CHeaderCtrlEx, CHeaderCtrl)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CHeaderCtrlEx
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Constructor
CHeaderCtrlEx::CHeaderCtrlEx()
{
	m_clrBack = RGB(255, 255, 255);
	m_clrText = RGB(0, 0, 0);
	m_clrLine = RGB(224, 224, 224);

	m_nHeight = 15;
	m_nLineWidth = 1;

	m_pFont = NULL;

	m_bEnableResizing = FALSE;

	m_bLBtnDown = FALSE;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Destructor
CHeaderCtrlEx::~CHeaderCtrlEx()
{
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MESSAGE MAP
BEGIN_MESSAGE_MAP(CHeaderCtrlEx, CHeaderCtrl)
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, &CHeaderCtrlEx::OnNMCustomdraw)
	ON_WM_SETCURSOR()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDBLCLK()	
	ON_MESSAGE(HDM_LAYOUT, OnLayout)	
	ON_WM_TIMER()
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 'NM_CUSTOMDRAW' message function
void CHeaderCtrlEx::OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult)
{
	*pResult = CDRF_DODEFAULT;

	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	HDC hDC = pNMCD->hdc;

	if (pNMCD->dwDrawStage == CDDS_PREPAINT)
	{
		/*CDC* pDC = CDC::FromHandle(hDC);
		if (pDC == NULL)	return;

		// Fill background color in total rectangle of header
		CRect rect = CRect();
		GetClientRect(&rect);
		pDC->FillSolidRect(&rect, m_clrBack);

		ReleaseDC(pDC);*/

		*pResult = CDRF_NOTIFYITEMDRAW;
	}
	else if (pNMCD->dwDrawStage == CDDS_ITEMPREPAINT)
	{
		CDC* pDC = CDC::FromHandle(hDC);
		if (pDC == NULL)	return;

		// Fill background color
		int nItem = int(pNMCD->dwItemSpec);
		CRect rect = pNMCD->rc;
		CPoint ptCursor;
		GetCursorPos(&ptCursor);
		ScreenToClient(&ptCursor);		
		if (nItem > 1 && rect.PtInRect(ptCursor))
		{
			if (m_bLBtnDown == TRUE)
				pDC->FillSolidRect(&rect,
					RGB(DWORD((FLOAT)GetRValue(m_clrBack) * 0.6F),
						DWORD((FLOAT)GetGValue(m_clrBack) * 0.6F),
						DWORD((FLOAT)GetBValue(m_clrBack) * 0.6F)));
			else
				pDC->FillSolidRect(&rect,
					RGB(DWORD((FLOAT)GetRValue(m_clrBack) * 0.8F),
						DWORD((FLOAT)GetGValue(m_clrBack) * 0.8F),
						DWORD((FLOAT)GetBValue(m_clrBack) * 0.8F)));
		}
		else
			pDC->FillSolidRect(&rect, m_clrBack);

		// Draw item outline
		CPen pen;
		CBrush brush;
		pen.CreatePen(PS_SOLID, m_nLineWidth, m_clrLine);
		brush.CreateStockObject(NULL_BRUSH);
		CPen *pOldPen = pDC->SelectObject(&pen);
		CBrush *pOldBrush = pDC->SelectObject(&brush);
		pDC->Rectangle(&pNMCD->rc);
		pDC->SelectObject(pOldPen);
		pDC->SelectObject(pOldBrush);

		pen.DeleteObject();
		brush.DeleteObject();

		// Draw item text
		HDITEM hditem;
		SecureZeroMemory(&hditem, sizeof(HDITEM));
		TCHAR buffer[MAX_PATH] = { 0 };
		hditem.mask = HDI_TEXT;
		hditem.pszText = buffer;
		hditem.cchTextMax = MAX_PATH;
		GetItem(int(pNMCD->dwItemSpec), &hditem);
		pDC->SetTextColor(m_clrText);
		pDC->SetBkMode(TRANSPARENT);
		if (m_pFont == NULL)	m_pFont = GetFont();
		CFont *pOldFont = pDC->SelectObject(m_pFont);
		CString strItem(buffer);
		rect.top = rect.Height() / 2 - (pDC->GetTextExtent(_T("A")).cy) / 2;
		pDC->DrawText(strItem, &rect, DT_CENTER | DT_VCENTER);
		pDC->SelectObject(pOldFont);

		ReleaseDC(pDC);

		*pResult = CDRF_SKIPDEFAULT;
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 'WM_SETCURSOR' message function
BOOL CHeaderCtrlEx::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	if (m_bEnableResizing)
		return CHeaderCtrl::OnSetCursor(pWnd, nHitTest, message);
	else
		return TRUE;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 'WM_MOUSEMOVE' message function
void CHeaderCtrlEx::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_bEnableResizing)
		CHeaderCtrl::OnMouseMove(nFlags, point);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 'WM_LBUTTONDOWN' message function
void CHeaderCtrlEx::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_bLBtnDown = TRUE;

	CHeaderCtrl::OnLButtonDown(nFlags, point);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 'WM_LBUTTONUP' message function
void CHeaderCtrlEx::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_bLBtnDown = FALSE;

	CHeaderCtrl::OnLButtonUp(nFlags, point);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 'WM_LBUTTONDBCLK' message function
void CHeaderCtrlEx::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	if (m_bEnableResizing)
		CHeaderCtrl::OnLButtonDblClk(nFlags, point);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 'HDM_LAYOUT' message function
LRESULT CHeaderCtrlEx::OnLayout(WPARAM, LPARAM lParam)
{
	// Sends HDM_LAYOUT message to the base class
	LRESULT lr = CHeaderCtrl::DefWindowProc(HDM_LAYOUT, 0, lParam);

	LPHDLAYOUT pHL = reinterpret_cast<LPHDLAYOUT>(lParam);

	// Set header height
	pHL->pwpos->cy = m_nHeight;

	// Set the item list height on the header height
	pHL->prc->top = m_nHeight;

	return lr;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 'WM_TIMER' message function
void CHeaderCtrlEx::OnTimer(UINT_PTR nIDEvent)
{
	if (m_bLBtnDown == FALSE)
		Invalidate(FALSE);

	CHeaderCtrl::OnTimer(nIDEvent);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////