/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// HeaderCtrlEx.h : header file
//

#pragma once

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CHeaderCtrlEx
class CHeaderCtrlEx : public CHeaderCtrl
{
	DECLARE_DYNAMIC(CHeaderCtrlEx)

public:
	CHeaderCtrlEx();
	virtual ~CHeaderCtrlEx();

private:
	COLORREF m_clrBack;
	COLORREF m_clrText;
	COLORREF m_clrLine;

	int m_nHeight;
	int m_nLineWidth;

	CFont *m_pFont;	

	BOOL m_bEnableResizing;

	BOOL m_bLBtnDown;

public:
	void SetBkColor(COLORREF color)		{ m_clrBack = color; }
	COLORREF GetBkColor()				{ return m_clrBack; }
	void SetTextColor(COLORREF color)	{ m_clrText = color; }
	COLORREF GetTextColor()				{ return m_clrText; }
	void SetLineColor(COLORREF color)	{ m_clrLine = color; }
	COLORREF GetLineColor()				{ return m_clrLine; }

	void SetHeight(int height)		{ m_nHeight = height; }
	int GetHeight()					{ return m_nHeight; }
	void SetLineWidth(int width)	{ m_nLineWidth = width; }
	int GetLineWidth()				{ return m_nLineWidth; }

	void SetFont(CFont *font)	{ m_pFont = font; }
	CFont* GetFont()			{ return m_pFont; }
	
	void SetEnableResizing(BOOL enable)	{ m_bEnableResizing = enable; }
	BOOL GetEnableResizing()			{ return m_bEnableResizing; }

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg LRESULT OnLayout(WPARAM wparam, LPARAM lparam);	
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////