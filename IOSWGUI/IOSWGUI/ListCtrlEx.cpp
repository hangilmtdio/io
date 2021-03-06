/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ListCtrlEx.cpp : implementation file
//

#include "stdafx.h"
#include "ListCtrlEx.h"

IMPLEMENT_DYNAMIC(CListCtrlEx, CListCtrl)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CListCtrlEx
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Constructor
CListCtrlEx::CListCtrlEx()
{
	m_nItemHeight = 20;

	m_clrGrid = RGB(255, 255, 255);
	m_nGridLineWidth = 1;
	m_bGridHMode = FALSE;
	m_clrSelBk = RGB(0, 120, 215);
	m_clrSelText = RGB(255, 255, 255);

	m_bIsResizingDivider = FALSE;

	m_nSelItem = -1;

	m_bSortDir = TRUE;
	m_nSortColumn = 5;

	m_pItemTextColorArray = NULL;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Desturctor
CListCtrlEx::~CListCtrlEx()
{
	if (m_pItemTextColorArray != NULL)
		delete[] m_pItemTextColorArray;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Set the height of item
void CListCtrlEx::SetItemHeight(int height)
{
	m_nItemHeight = height;

	CImageList imagelist;
	imagelist.Create(1, m_nItemHeight, ILC_COLOR, 1, 1);
	SetImageList(&imagelist, LVSIL_SMALL);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Create array of item text color
void CListCtrlEx::CreateItemTextColorArray(int nItemCount)
{
	if (m_pItemTextColorArray != NULL)
		delete[] m_pItemTextColorArray;

	m_pItemTextColorArray = new COLORREF[nItemCount];
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Set color of item text
void CListCtrlEx::SetItemTextColor(int nItem, COLORREF clrColor)
{
	if (nItem > GetItemCount() - 1)	return;

	m_pItemTextColorArray[nItem] = clrColor;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MESSAGE MAP
BEGIN_MESSAGE_MAP(CListCtrlEx, CListCtrl)
ON_WM_PAINT()
ON_WM_CREATE()
ON_NOTIFY(HDN_BEGINTRACKA, 0, &CListCtrlEx::OnHdnBegintrack)
ON_NOTIFY(HDN_BEGINTRACKW, 0, &CListCtrlEx::OnHdnBegintrack)
ON_NOTIFY(HDN_ENDTRACKA, 0, &CListCtrlEx::OnHdnEndtrack)
ON_NOTIFY(HDN_ENDTRACKW, 0, &CListCtrlEx::OnHdnEndtrack)
ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, &CListCtrlEx::OnNMCustomdraw)
ON_WM_DESTROY()
ON_NOTIFY(HDN_ITEMCLICKA, 0, &CListCtrlEx::OnHdnItemclick)
ON_NOTIFY(HDN_ITEMCLICKW, 0, &CListCtrlEx::OnHdnItemclick)
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 'WM_CREATE' message function
int CListCtrlEx::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CListCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;

	// Set parent window handle
	m_hParentWnd = lpCreateStruct->hwndParent;

	// Subclass window of header control
	m_ctrlHeader.SubclassWindow(GetHeaderCtrl()->m_hWnd);

	// Set timer of header for invalidating
	m_ctrlHeader.SetTimer(0, 100, NULL);

	return 0;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 'WM_PAINT' message function
void CListCtrlEx::OnPaint()
{
	CListCtrl::OnPaint();

	// Draw grid lines ---------------------------------------------------------------------------------------------------------------------------------
	if ((GetStyle() & LVS_TYPEMASK) == LVS_REPORT && m_bIsResizingDivider == FALSE)
	{
		CDC *pDC = GetDC();
		if (pDC == NULL)	return;

		CRect rect;
		CPen Pen;// , BkPen;
		CPen *pOldPen = NULL;
		//CPen *pOldBkPen = NULL;

		Pen.CreatePen(PS_SOLID, m_nGridLineWidth, m_clrGrid);
		pOldPen = pDC->SelectObject(&Pen);

		// Get the start of lines (header's bottom)
		GetHeaderCtrl()->GetClientRect(&rect);
		int nStart = rect.bottom;

		// Get the end of lines (client's bottom) 
		GetClientRect(&rect);
		int nEnd = rect.bottom;

		// If horizontal mode
		/*if (m_bGridHMode == TRUE)
		{
			BkPen.CreatePen(PS_SOLID, 1, GetBkColor());
			pOldBkPen = pDC->SelectObject(&BkPen);
		}*/

		if (m_bGridHMode == FALSE)
		{
			// Draw vertical lines
			int nLineX = 0 - GetScrollPos(SB_HORZ);
			for (int i = 1; i < GetHeaderCtrl()->GetItemCount(); i++)
			{
				// Get the x-position of next line
				nLineX += GetColumnWidth(i);

				// if next border is outside client area, break out
				if (nLineX >= rect.right) break;

				// Draw the line.
				pDC->MoveTo(nLineX, nStart);
				pDC->LineTo(nLineX, nEnd);
			}
		}

		/*if (m_bGridHMode == TRUE)
		{
			pDC->SelectObject(pOldBkPen);
		}*/

		// Get 1st item rectangle
		/*if (!GetItemRect(0, &rect, LVIR_BOUNDS))
			return;*/

		// Draw horizontal lines
		/*for (int i = 1; i <= GetCountPerPage(); i++)
		{
			pDC->MoveTo(0, nStart + rect.Height() * i - 1);
			pDC->LineTo(rect.Width(), nStart + rect.Height() * i - 1);
		}*/
		for (int i = 1; i <= GetCountPerPage(); i++)
		{
			pDC->MoveTo(0, nStart + (m_nItemHeight + 1) * i - 1);
			pDC->LineTo(rect.Width(), nStart + (m_nItemHeight + 1) * i - 1);
		}

		pDC->SelectObject(pOldPen);

		Pen.DeleteObject();

		ReleaseDC(pDC);
	}
	// -------------------------------------------------------------------------------------------------------------------------------------------------
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 'HDN_BEGINTRACK' message function
void CListCtrlEx::OnHdnBegintrack(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	
	m_bIsResizingDivider = TRUE;

	*pResult = 0;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 'HDN_ENDTRACK' message function
void CListCtrlEx::OnHdnEndtrack(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);

	m_bIsResizingDivider = FALSE;
	Invalidate();

	*pResult = 0;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 'NM_CUSTOMDRAW' message function
void CListCtrlEx::OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLVCUSTOMDRAW pNMLVCD = reinterpret_cast<LPNMLVCUSTOMDRAW>(pNMHDR);

	switch (pNMLVCD->nmcd.dwDrawStage)
	{
	case CDDS_PREPAINT:
	{
		*pResult = CDRF_NOTIFYITEMDRAW;
	}
	break;

	case CDDS_ITEMPREPAINT:
	{
		*pResult = CDRF_DODEFAULT;

		POSITION pos = GetFirstSelectedItemPosition();
		int nSel = GetNextSelectedItem(pos);

		int nRow = int(pNMLVCD->nmcd.dwItemSpec);

		if (nRow == nSel)
		{
			pNMLVCD->nmcd.uItemState = CDIS_DEFAULT;

			pNMLVCD->clrTextBk = m_clrSelBk;
			//pNMLVCD->clrText = m_clrSelText;
		}
		else
		{
			pNMLVCD->clrTextBk = GetBkColor();
			//pNMLVCD->clrText = GetTextColor();
		}

		if (m_pItemTextColorArray == NULL)
			pNMLVCD->clrText = GetTextColor();
		else
			pNMLVCD->clrText = m_pItemTextColorArray[nRow];
	}
	break;

	default:
	{
		*pResult = CDRF_DODEFAULT;
	}
	break;
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 'WM_DESTROY' message function
void CListCtrlEx::OnDestroy()
{
	CListCtrl::OnDestroy();

	// Unsubclass window of header control
	m_ctrlHeader.UnsubclassWindow();
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 'WindowProc' override function
LRESULT CListCtrlEx::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == WM_VSCROLL)
	{
		// Get scroll bar code & postion
		WORD nSBCode = LOWORD(wParam);
		int nPos = HIWORD(wParam);

		if (nSBCode >= SB_LINEUP && nSBCode <= SB_PAGEDOWN)	// This is the additional code for preventing from drawing the unexpected lines
		{
			// Set index amount for moving to new item that must be shown
			int nMove = 0;
			switch (nSBCode)
			{
			case SB_LINEUP:		nMove = -1;								break;
			case SB_LINEDOWN:	nMove = GetCountPerPage();				break;
			case SB_PAGEUP:		nMove = -GetCountPerPage();				break;
			case SB_PAGEDOWN:	nMove = GetCountPerPage() * 2 - 1;		break;
			}

			// Set index of new item that must be shown
			int nNewItem = GetTopIndex() + nMove;
			if (nNewItem < 0)	nNewItem = 0;
			if (nNewItem > GetItemCount() - 1)	nNewItem = GetItemCount() - 1;

			EnsureVisible(nNewItem, TRUE);

			// Send unselecting item message to parent window
			if (GetSelectionMark() != -1 &&
				(GetSelectionMark() < GetTopIndex() || GetSelectionMark() > GetTopIndex() + GetCountPerPage() - 1))
				::SendMessage(m_hParentWnd, UM_UNSELECT_LIST_ITEM, GetDlgCtrlID(), GetSelectionMark());

			return 1;
		}
		else if (nSBCode == SB_THUMBTRACK || nSBCode == SB_THUMBPOSITION)				// This is the additional code for skinning scroll bar
		{
			// Get scroll information
			SCROLLINFO vInfo = { 0 };
			vInfo.cbSize = sizeof(SCROLLINFO);
			vInfo.fMask = SIF_ALL;
			SCROLLINFO hInfo = vInfo;
			GetScrollInfo(SB_VERT, &vInfo);
			GetScrollInfo(SB_HORZ, &hInfo);

			// Get rectangle of client
			CRect rcClient;
			GetClientRect(&rcClient);

			// Set size of all
			SIZE sizeAll;
			if (hInfo.nPage == 0)	sizeAll.cx = rcClient.right;
			else					sizeAll.cx = rcClient.right * (hInfo.nMax + 1) / hInfo.nPage;
			if (vInfo.nPage == 0)	sizeAll.cy = rcClient.bottom;
			else					sizeAll.cy = rcClient.bottom * (vInfo.nMax + 1) / vInfo.nPage;

			// Set size of scrolling
			SIZE sizeScroll = { 0, 0 };
			switch (message)
			{
			case WM_VSCROLL:
				sizeScroll.cx = sizeAll.cx * hInfo.nPos / (hInfo.nMax + 1);
				sizeScroll.cy = sizeAll.cy * (nPos - vInfo.nPos) / (vInfo.nMax + 1);
				break;

			case WM_HSCROLL:
				sizeScroll.cx = sizeAll.cx * (nPos - hInfo.nPos) / (hInfo.nMax + 1);
				sizeScroll.cy = sizeAll.cy * vInfo.nPos / (vInfo.nMax + 1);
				break;
			}

			// Scroll
			Scroll(sizeScroll);

			// Send unselecting item message to parent window
			if (GetSelectionMark() != -1 &&
				(GetSelectionMark() < GetTopIndex() || GetSelectionMark() > GetTopIndex() + GetCountPerPage() - 1))
				::SendMessage(m_hParentWnd, UM_UNSELECT_LIST_ITEM, GetDlgCtrlID(), GetSelectionMark());

			return 1;
		}
	}
	else if (message == WM_MOUSEWHEEL)
	{
		// Send unselecting item message to parent window
		if (GetSelectionMark() != -1 &&
			(GetSelectionMark() < GetTopIndex() || GetSelectionMark() > GetTopIndex() + GetCountPerPage() - 1))
			::SendMessage(m_hParentWnd, UM_UNSELECT_LIST_ITEM, GetDlgCtrlID(), GetSelectionMark());
	}
	else if (message == WM_RBUTTONDOWN || message == WM_RBUTTONUP)
	{
		return 1;
	}

	return CListCtrl::WindowProc(message, wParam, lParam);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 'HDN_ITEMCLICK' message function
void CListCtrlEx::OnHdnItemclick(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	
	if (phdr->iItem > 1)
	{
		// Set sorting column
		m_nSortColumn = phdr->iItem;

		// Set sorting direction
		m_bSortDir = !m_bSortDir;

		// Sort
		Sort();
	}

	//*pResult = 0;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Sort
void CListCtrlEx::Sort()
{
	// Sort items
	if (GetItemCount() > 1)
	{
		SortItems(SortFunc, (LPARAM)this);

		// Send sorrted message to parent window
		::SendMessage(m_hParentWnd, UM_SORT_ITEM_LIST, GetDlgCtrlID(), GetSelectionMark());
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Sort callback function
int CALLBACK CListCtrlEx::SortFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	CListCtrlEx *pListCtrl = (CListCtrlEx*)lParamSort;
	BOOL bAscending = pListCtrl->m_bSortDir;
	int nColumn = pListCtrl->m_nSortColumn;

	LVFINDINFO info1, info2;
	info1.flags = LVFI_PARAM;
	info1.lParam = lParam1;
	info2.flags = LVFI_PARAM;
	info2.lParam = lParam2;
	int irow1 = pListCtrl->FindItem(&info1, -1);
	int irow2 = pListCtrl->FindItem(&info2, -1);

	CString strItem1 = pListCtrl->GetItemText(irow1, nColumn);
	CString strItem2 = pListCtrl->GetItemText(irow2, nColumn);

	return bAscending ? _tcscmp(strItem1, strItem2) : -_tcscmp(strItem1, strItem2);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////