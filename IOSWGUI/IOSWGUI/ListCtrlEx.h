/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ListCtrlEx.h : header file
//

#pragma once

#include "HeaderCtrlEx.h"

#define UM_SORT_ITEM_LIST			WM_USER + 105
#define UM_UNSELECT_LIST_ITEM		WM_USER + 106
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CListCtrlEx
class CListCtrlEx : public CListCtrl
{
	DECLARE_DYNAMIC(CListCtrlEx)

public:
	CListCtrlEx();
	virtual ~CListCtrlEx();

	BOOL m_bSortDir;		// TRUE : ascending, FALSE : descending
	int m_nSortColumn;

private:
	HWND m_hParentWnd;

	int m_nItemHeight;

	COLORREF m_clrGrid;
	int m_nGridLineWidth;
	BOOL m_bGridHMode;
	COLORREF m_clrSelBk;
	COLORREF m_clrSelText;

	CHeaderCtrlEx m_ctrlHeader;

	BOOL m_bIsResizingDivider;

	int m_nSelItem;

	COLORREF* m_pItemTextColorArray;

public:
	void SetItemHeight(int height);
	int GetItemHeight()	{ return m_nItemHeight; }

	void SetGridColor(COLORREF color)		{ m_clrGrid = color; }
	COLORREF GetGridColor()					{ return m_clrGrid; }
	void SetGridLineWidth(int width)		{ m_nGridLineWidth = width; }
	int GetGridLineWidth()					{ return m_nGridLineWidth; }
	void SetGridHMode(BOOL hmode)			{ m_bGridHMode = hmode; }
	BOOL GetGridHMode()						{ return m_bGridHMode; }
	void SetSelBkColor(COLORREF color)		{ m_clrSelBk = color; }
	COLORREF GetSelBkColor()				{ return m_clrSelBk; }
	void SetSelTextColor(COLORREF color)	{ m_clrSelText = color; }
	COLORREF GetSelTextColor()				{ return m_clrSelText; }

	void SetHeaderFont(CFont *font)				{ m_ctrlHeader.SetFont(font); }
	CFont* GetHeaderFont()						{ return m_ctrlHeader.GetFont(); }
	void SetHeaderHeight(int height)			{ m_ctrlHeader.SetHeight(height); }
	int GetHeaderHeight()						{ return m_ctrlHeader.GetHeight(); }	
	void SetHeaderBkColor(COLORREF color)		{ m_ctrlHeader.SetBkColor(color); }
	COLORREF GetHeaderBkColor()					{ return m_ctrlHeader.GetBkColor(); }
	void SetHeaderTextColor(COLORREF color)		{ m_ctrlHeader.SetTextColor(color); }
	COLORREF GetHeaderTextColor()				{ return m_ctrlHeader.GetTextColor(); }
	void SetHeaderLineColor(COLORREF color)		{ m_ctrlHeader.SetLineColor(color); }
	COLORREF GetHeaderLineColor()				{ return m_ctrlHeader.GetLineColor(); }
	void SetHeaderLineWidth(int width)			{ m_ctrlHeader.SetLineWidth(width); }
	int GetHeaderLineWidth()					{ return m_ctrlHeader.GetLineWidth(); }
	void SetHeaderEnableResizing(BOOL enable)	{ m_ctrlHeader.SetEnableResizing(enable); }
	BOOL GetHeaderEnableResizing()				{ return m_ctrlHeader.GetEnableResizing(); }

	void CreateItemTextColorArray(int nItemCount);
	void SetItemTextColor(int nItem, COLORREF clrColor);

	void Sort();

private:
	static int CALLBACK SortFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnHdnBegintrack(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnHdnEndtrack(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDestroy();
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	afx_msg void OnHdnItemclick(NMHDR *pNMHDR, LRESULT *pResult);
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////