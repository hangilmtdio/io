#pragma once

#include "IOSWWnd.h"
#include "ImageObject.h"
#include "CommonDefine.h"


class CIOSWToolbar : 	public CIOSWWnd
{
public:
	CIOSWToolbar();
	~CIOSWToolbar();

	void LoadResource();

protected:
//	DWORD ThreadProc();
//	void  UpdateRender();

private:
	CImageObject*	m_pBGImage;
	CImageObject*	m_pLeftBtnImage;
	CImageObject*	m_pMainBtnImage;
	CImageObject*	m_pRightBtnImage;

	CImageObject*	m_pDIBtnImage;
	CImageObject*	m_pDOBtnImage;
	CImageObject*	m_pAIBtnImage;
	CImageObject*	m_pAOBtnImage;
	CImageObject*	m_pDIMMERBtnImage;

	DEVICE_POSITION		m_nCockpitType;
	IO_KIND				m_nIOType;

public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

