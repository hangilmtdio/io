#pragma once

#include "IOSWWnd.h"
#include "ImageObject.h"
#include "IOSWThread.h"

class CIOSWTitle :	public CIOSWWnd, CIOSWThread
{
public:
	CIOSWTitle();
	~CIOSWTitle();

	void LoadResource();

protected:
	DWORD ThreadProc();
	void  UpdateRender();

private:

	CImageObject*	m_pBGImage;
	CImageObject*	m_pExitBtn;
	CImageObject*	m_pMode;
	CImageObject*	m_pCurrTime;

	CFont			m_fontTime;

public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnClose();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
};

