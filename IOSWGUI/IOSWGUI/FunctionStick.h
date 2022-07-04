#pragma once

#include "ImageObject.h"
#include "CommonDefine.h"

// CFunctionStick dialog

class CFunctionStick : public CDialogEx
{
	DECLARE_DYNAMIC(CFunctionStick)

public:
	CFunctionStick(CWnd* pParent = NULL);   // standard constructor
	virtual ~CFunctionStick();
	TRIM_COMMAND GetTrimCommand() { return m_eTrimCommand; }

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_STICK_FUNCTION };
#endif

private:
	CBitmap				m_bmpBackgound;
	CImageObject*		m_pInitObject;
	CImageObject*		m_pLeftTrimObject;
	CImageObject*		m_pRightTrimObject;
	CImageObject*		m_pFrontTrimObject;
	CImageObject*		m_pRearTrimObject;
	TRIM_COMMAND		m_eTrimCommand;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
